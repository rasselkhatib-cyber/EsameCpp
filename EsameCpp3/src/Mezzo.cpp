#include "../include/Mezzo.hpp"
#include <stdexcept>
#include <cstdlib>
#include <iostream>

// Chiama il costruttore di Risorsa(id) nella initializer list
Mezzo::Mezzo(int id, const std::string& tipo)
    : Risorsa(id), tipo(tipo)
{
    // Assegna un numero di posti standard tra 2 e 6
    posti = (std::rand() % 5) + 2; // 2..6
}

std::string Mezzo::getTipo() const { return tipo; }

int Mezzo::getPosti() const { return posti; }

void Mezzo::setPosti(int p) {
    if (p < 2 || p > 6) {
        throw std::invalid_argument("Numero di posti non valido: deve essere tra 2 e 6.");
    }
    posti = p;
}

void Mezzo::capienza() {
    std::cout << "Posti: " << posti << std::endl;
}

