#ifndef MEZZO_HPP
#define MEZZO_HPP
#include  "Ireportable.hpp"
#include <string>
#include "Risorsa.hpp" 
#include "Mezzo.hpp"

// Eredita pubblicamente da Risorsa
class Mezzo : public Risorsa, public IReportable { 
private:
    std::string tipo;
public:
    Mezzo(int id, const std::string& tipo);
    std::string getTipo() const;
    void mostraDettagli() const override;
};

#endif