#include "../include/gestioneEccezioni.hpp"
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>



IDGenerator::IDGenerator() {

    std::srand(std::time(0)); 
}

int IDGenerator::generaID(){
   
if(id_usati.size() >= 1000){
        throw std::runtime_error("Tutti gli ID disponibili sono stati utilizzati.");
    }
   
    int id;
    
    do {
        id = (std::rand() % 1000) + 100;
    } while (id_usati.count(id) > 0); 

    id_usati.insert(id);
    return id;
}
