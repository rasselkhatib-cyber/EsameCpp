#include "../include/Missione.hpp"
#include <iostream>
#include <algorithm>

Missione::Missione(int id, const std::string& descrizione)
    : id(id), descrizione(descrizione) {}

void Missione::assegnaPersonale(Personale* p) {
    // Avoid duplicate person in the mission's personale list
    if (std::find(personaleAssegnato.begin(), personaleAssegnato.end(), p) == personaleAssegnato.end())
        personaleAssegnato.push_back(p);
    p->setDisponibile(false);
}

void Missione::assegnaMezzo(Mezzo* m) {
    // Avoid duplicate mezzo
    if (std::find(mezziAssegnati.begin(), mezziAssegnati.end(), m) == mezziAssegnati.end())
        mezziAssegnati.push_back(m);
    m->setDisponibile(false);
}

void Missione::assegnaPersonalealMezzo(Personale* p, Mezzo* m) {
    // Assicurati che il personale sia inserito nella lista generale
    if (std::find(personaleAssegnato.begin(), personaleAssegnato.end(), p) == personaleAssegnato.end())
        personaleAssegnato.push_back(p);
    // Assicura che il mezzo sia nella lista dei mezzi e che abbia la sua voce nella mappa
    if (std::find(mezziAssegnati.begin(), mezziAssegnati.end(), m) == mezziAssegnati.end())
        mezziAssegnati.push_back(m);
    // Aggiungi il personale al mezzo nella mappa
    personalePerMezzo[m].push_back(p);
    p->setDisponibile(false);
    m->setDisponibile(false);
}

void Missione::mostraDettagli() const {
    std::cout << "=== Missione " << id << " ===\n";
    std::cout << "Descrizione: " << descrizione << "\n";
    std::cout << "Personale assegnato:\n";
    for (auto p : personaleAssegnato)
        std::cout << " - " << p->getNome() << " (" << p->gradoToString() << ")\n";

    std::cout << "Mezzi assegnati e il personale per mezzo:\n";
    for (auto& kv : personalePerMezzo) {
        Mezzo* m = kv.first;
        std::cout << " - " << m->getTipo() << " (" << m->getPosti() << " posti):\n";
        for (auto p : kv.second) {
            std::cout << "    - " << p->getNome() << " (" << p->gradoToString() << ")\n";
        }
    }
}
