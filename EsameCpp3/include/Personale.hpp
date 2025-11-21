// include/Personale.hpp
#ifndef PERSONALE_HPP
#define PERSONALE_HPP

#include <string>
#include "Risorsa.hpp" // AGGIUNTO

enum class Grado {  
    SOLDATO,
    CAPORALE,
    SERGENTE,
    TENENTE,
    CAPITANO,
    MAGGIORE,
};

// Eredita pubblicamente da Risorsa
class Personale : public Risorsa { 
private:
    std::string nome;
    Grado grado;
    // id, disponibile, getId(), isDisponibile(), setDisponibile() sono in Risorsa
public:
    // Chiama il costruttore della classe base: Risorsa(id)
    Personale(int id, const std::string& nome, Grado grado);

    std::string getNome() const;
    Grado getGrado() const;
    // Metodi ereditati da Risorsa: getId(), isDisponibile(), setDisponibile()
    
    std::string gradoToString() const;
};

#endif