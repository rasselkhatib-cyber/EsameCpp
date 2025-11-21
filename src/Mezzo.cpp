#include "../include/Mezzo.hpp"
#include <iostream>


Mezzo::Mezzo(int id, const std::string& tipo)
    : Risorsa(id), tipo(tipo) {}
std::string Mezzo::getTipo() const { return tipo; }

void Mezzo::mostraDettagli() const {
    std::cout << "ID Mezzo: " << getId() << " - Tipo: " << getTipo() << " Stato: [" << (isDisponibile() ? "Disponibile" : "In Missione") << "]" << std::endl;}