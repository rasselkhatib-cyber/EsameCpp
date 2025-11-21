#include "../include/Personale.hpp"
#include <iostream>

Personale::Personale(int id, const std::string& nome, Grado grado)
    : Risorsa(id), nome(nome), grado(grado) {}


std::string Personale::getNome() const { return nome; }
Grado Personale::getGrado() const { return grado; }

std::string Personale::gradoToString() const    {
    
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
       
    void Personale::mostraDettagli() const {
    std::cout << "ID Personale: " << getId() << " - Nome: " << getNome()
              << " - Grado: " << gradoToString()
              << " - Disponibile: " << (isDisponibile() ? "Si" : "No") << std::endl;

}
