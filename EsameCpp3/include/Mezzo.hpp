// include/Mezzo.hpp
#ifndef MEZZO_HPP
#define MEZZO_HPP

#include <string>
#include "Risorsa.hpp" 

// Eredita pubblicamente da Risorsa
class Mezzo : public Risorsa { 
private:
    std::string tipo;
    int posti;
    // id, disponibile, getId(), isDisponibile(), setDisponibile() sono in Risorsa
public:
    // Chiama il costruttore della classe base: Risorsa(id)
    Mezzo(int id, const std::string& tipo);

    std::string getTipo() const;
    int getPosti() const;
    void setPosti(int p);
    // Metodi ereditati da Risorsa: getId(), isDisponibile(), setDisponibile()
    // Ritorna la capienza / numero di posti del mezzo
    void capienza();
        // Implementazione specifica per Mez


};

#endif