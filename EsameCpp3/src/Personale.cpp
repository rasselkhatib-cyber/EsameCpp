#include "../include/Personale.hpp"

// Chiama il costruttore di Risorsa(id)
Personale::Personale(int id, const std::string& nome, Grado grado)
    : Risorsa(id), nome(nome), grado(grado) {}

// I metodi getId(), isDisponibile(), setDisponibile() sono stati rimossi e sono ereditati.
//int Personale::getId() const { return Risorsa::getId(); } // Opzionale: puoi lasciare solo getNome(), getGrado(), etc.
std::string Personale::getNome() const { return nome; }
Grado Personale::getGrado() const { return grado; }
// ... il resto del codice è invariato

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
