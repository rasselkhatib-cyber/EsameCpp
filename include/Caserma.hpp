#ifndef CASERMA_HPP
#define CASERMA_HPP

#include "Personale.hpp"
#include "Mezzo.hpp"
#include "Missione.hpp"
#include <vector>
#include <memory>

class Caserma {
private:
    std::vector<std::unique_ptr<Personale>> personale;
    std::vector<std::unique_ptr<Mezzo>> mezzi;
    std::vector<std::unique_ptr<Missione>> missioni;

    Personale* trovaPersonalePerId(int id);
    Mezzo* trovaMezzoPerId(int id);
    
public:
    void aggiungiPersonale(std::unique_ptr<Personale> p);

    void aggiungiMezzo(std::unique_ptr<Mezzo> m);
    void creaMissione(const std::string& descrizione,
                      const std::vector<int>& idPersonale,
                      const std::vector<int>& idMezzi);

    void mostraPersonale() const;
    void mostraMezzi() const;
    void mostraMissioni() const;
};

#endif
