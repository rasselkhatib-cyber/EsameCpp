#include "../include/Risorsa.hpp"

Risorsa::Risorsa(int id) : id(id), disponibile(true) {}


int Risorsa::getId() const { return id; }

bool Risorsa::isDisponibile() const { return disponibile; }

void Risorsa::setDisponibile(bool disp) { disponibile = disp; }

