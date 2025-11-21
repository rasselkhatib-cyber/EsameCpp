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
                           const std::vector<int>& idMezzi) {
    int id = missioni.size() + 1;
    auto missione = std::make_unique<Missione>(id, descrizione);
    bool controlloDisponibilita = true;
    std::cout << idPersonale.size() << std::endl;

    if (idPersonale.size() > 0 || idMezzi.size() > 0){
        for (int idP : idPersonale) {
      if(auto p = trovaPersonalePerId(idP)) //Controllo se il personale esiste (p non è nullptr)
        {
        std::cout << p << "Questo è p" << std::endl;   
        if(p->isDisponibile()){  
            missione->assegnaPersonale(p);
        }
        else{  
            std::cerr << "Personale con ID " << idP << " non disponibile.\n";
            controlloDisponibilita=false;
        }
        } else{ 
            std::cerr << "Personale con ID " << idP << " non trovato.\n";
            controlloDisponibilita=false;
        }       

        for (int idM :idMezzi){
        if(auto m = trovaMezzoPerId(idM))
        {
            if(m->isDisponibile()){
                missione->assegnaMezzo(m);
            }
            else{
                std::cerr << "Mezzo con ID " << idM << " non disponibile.\n";
            controlloDisponibilita=false;
            }
        } else {
            std::cerr << "Mezzo con ID " << idM << " non trovato.\n";
            controlloDisponibilita=false;
        }

    }
}
        if(controlloDisponibilita){
            missioni.push_back(std::move(missione));
            std::cout << "Missione creata!\n";  //trasferito dal main e controllo eseguito traminte bool
        }else{
            std::cout << "Non è stato possibile creare una missione." <<  std::endl;   //Aggiunta della missione al vettore"
        }

    
}}

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
                  << " [" << (m->isDisponibile() ? "Disponibile" : "In missione") << "]\n";
}

void Caserma::mostraMissioni() const {
    std::cout << "\n=== Elenco Missioni ===\n";
    for (const auto& m : missioni)
        m->mostraDettagli();
}
