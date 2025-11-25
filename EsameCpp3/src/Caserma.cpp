#include "../include/Caserma.hpp"
#include <iostream>
#include <memory>
Personale* Caserma::trovaPersonalePerId(int id){
    for(auto& p : personale){
        if(p->getId() == id){
            return p.get();
        }
    }
        
    return nullptr;
} 
Mezzo* Caserma::trovaMezzoPerId(int id){
    for(auto& m : mezzi)
        if(m->getId() == id){
            return m.get();
        }
    return nullptr;
    
}
void Caserma::aggiungiPersonale(std::unique_ptr<Personale> p) {
    personale.push_back(std::move(p)); //Aggiunta del personale al vettore
}

void Caserma::aggiungiMezzo(std::unique_ptr<Mezzo> m) {
    mezzi.push_back(std::move(m)); //Aggiunta del mezzo al vettore
}

void Caserma::creaMissione(const std::string& descrizione,
                           const std::vector<int>& idPersonale,
                           const std::vector<int>& idMezzi,
                           const std::map<int, std::vector<int>>& assegnamentiMezzi) {
    int id = missioni.size() + 1;
    auto missione = std::make_unique<Missione>(id, descrizione);
    bool controlloDisponibilita = true;

    if (idPersonale.empty() || idMezzi.empty()) {
        std::cerr << "Deve essere selezionato almeno un personale e un mezzo per creare una missione.\n";
        return;
    }

    // Build sets for quick lookup
    std::set<int> personaleSet(idPersonale.begin(), idPersonale.end());
    std::set<int> mezziSet(idMezzi.begin(), idMezzi.end());
    std::set<int> personaleAssegnatoGlobale;

    // Validate assignments per mezzo
    for (const auto& kv : assegnamentiMezzi) {
        int idMezzo = kv.first;
        const auto& persone = kv.second;

        if (mezziSet.count(idMezzo) == 0) {
            std::cerr << "Mezzo con ID " << idMezzo << " non è stato selezionato per la missione.\n";
            controlloDisponibilita = false;
            continue;
        }

        Mezzo* mezzoPtr = trovaMezzoPerId(idMezzo);
        if (!mezzoPtr) {
            std::cerr << "Mezzo con ID " << idMezzo << " non trovato.\n";
            controlloDisponibilita = false;
            continue;
        }
        if (!mezzoPtr->isDisponibile()) {
            std::cerr << "Mezzo con ID " << idMezzo << " non disponibile.\n";
            controlloDisponibilita = false;
        }

        if (persone.size() < 2 || persone.size() > 6) {
            std::cerr << "Il mezzo con ID " << idMezzo << " deve avere almeno 2 e massimo 6 persone assegnate.\n";
            controlloDisponibilita = false;
        }
        if (persone.size() > static_cast<size_t>(mezzoPtr->getPosti())) {
            std::cerr << "Il mezzo con ID " << idMezzo << " non ha abbastanza posti: capienza " << mezzoPtr->getPosti() << ".\n";
            controlloDisponibilita = false;
        }

        for (int pid : persone) {
            if (personaleSet.count(pid) == 0) {
                std::cerr << "Personale con ID " << pid << " non è stato selezionato per la missione.\n";
                controlloDisponibilita = false;
            }
            if (personaleAssegnatoGlobale.count(pid) > 0) {
                std::cerr << "Personale con ID " << pid << " è già assegnato ad un altro mezzo.\n";
                controlloDisponibilita = false;
            }
            personaleAssegnatoGlobale.insert(pid);
        }
    }

    // Validate global personnel and mezzi availability
    for (int pid : idPersonale) {
        Personale* p = trovaPersonalePerId(pid);
        if (!p) {
            std::cerr << "Personale con ID " << pid << " non trovato.\n";
            controlloDisponibilita = false;
            continue;
        }
        if (!p->isDisponibile()) {
            std::cerr << "Personale con ID " << pid << " non disponibile.\n";
            controlloDisponibilita = false;
        }
    }

    for (int mid : idMezzi) {
        Mezzo* m = trovaMezzoPerId(mid);
        if (!m) {
            std::cerr << "Mezzo con ID " << mid << " non trovato.\n";
            controlloDisponibilita = false;
            continue;
        }
        if (!m->isDisponibile()) {
            std::cerr << "Mezzo con ID " << mid << " non disponibile.\n";
            controlloDisponibilita = false;
        }
    }

    if (!controlloDisponibilita) {
        std::cout << "Non è stato possibile creare una missione." << std::endl;
        return;
    }

    // All validations passed: perform assignments
    for (int pid : idPersonale) {
        if (Personale* p = trovaPersonalePerId(pid)) {
            missione->assegnaPersonale(p);
        }
    }

    for (int mid : idMezzi) {
        if (Mezzo* m = trovaMezzoPerId(mid)) {
            missione->assegnaMezzo(m);
        }
    }

    for (const auto& kv : assegnamentiMezzi) {
        int mid = kv.first;
        Mezzo* m = trovaMezzoPerId(mid);
        if (!m) continue;
        for (int pid : kv.second) {
            if (Personale* p = trovaPersonalePerId(pid)) {
                missione->assegnaPersonalealMezzo(p, m);
            }
        }
    }

    missioni.push_back(std::move(missione));
    std::cout << "Missione creata!\n";
}

void Caserma::mostraPersonale() const {
    std::cout << "\n--- Personale ---\n";
    for (const auto& p : personale)
        std::cout << p->getId() << " - " << p->getNome() << " (" << p->gradoToString()
                  << ") [" << (p->isDisponibile() ? "Disponibile" : "In missione") << "]\n";
}

void Caserma::mostraMezzi() const {
    std::cout << "\n--- Mezzi ---\n";
    for (const auto& m : mezzi)
        std::cout << m->getId() << " - " << m->getTipo()
                  << " (" << m->getPosti() << " posti)"
                  << " [" << (m->isDisponibile() ? "Disponibile" : "In missione") << "]\n";
}

void Caserma::mostraMissioni() const {
    std::cout << "\n=== Elenco Missioni ===\n";
    for (const auto& m : missioni)
        m->mostraDettagli();
}
