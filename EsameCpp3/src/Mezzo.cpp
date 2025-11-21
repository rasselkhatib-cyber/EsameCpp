#include "../include/Mezzo.hpp"

// Chiama il costruttore di Risorsa(id)
Mezzo::Mezzo(int id, const std::string& tipo)
    : Risorsa(id), tipo(tipo) {}

// I metodi getId(), isDisponibile(), setDisponibile() sono stati rimossi e sono ereditati.
std::string Mezzo::getTipo() const { return tipo; }