#include "../include/Personale.hpp"

// Chiama il costruttore di Risorsa(id) nella initializer list
Personale::Personale(int id, const std::string& nome, Grado grado)
    : Risorsa(id), nome(nome), grado(grado) 
{
    // Il corpo del costruttore può essere vuoto
}

std::string Personale::getNome() const { return nome; }

Grado Personale::getGrado() const { return grado; }

std::string Personale::gradoToString() const {
        
    
    switch (grado) {
        case Grado::SOLDATO: return "Soldato";
        case Grado::CAPORALE: return "Caporale";
        case Grado::SERGENTE: return "Sergente";
        case Grado::TENENTE: return "Tenente";
        case Grado::CAPITANO: return "Capitano";
        case Grado::MAGGIORE: return "Maggiore";
        default: return "Sconosciuto";
    }
}