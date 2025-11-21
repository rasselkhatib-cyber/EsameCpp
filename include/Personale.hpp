#ifndef PERSONALE_HPP
#define PERSONALE_HPP
#include "Ireportable.hpp"
#include "Personale.hpp"
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
class Personale : public Risorsa, public IReportable { 
private:
    std::string nome;
    Grado grado;
    
public:
    Personale(int id, const std::string& nome, Grado grado);

    std::string getNome() const;
    Grado getGrado() const;
    
    std::string gradoToString() const;

    void mostraDettagli() const override;
};

#endif