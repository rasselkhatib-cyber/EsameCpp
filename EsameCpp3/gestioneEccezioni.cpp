#include <iostream>
#include <set>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

class IDGenerator{

    private:
        std::set<int> id_usati;   //per tenere traccia degli id usati 

    public:
        IDGenerator() {
            std::srand(std::time(0)); // inizializza il generatore di numeri casuali
        }

        int generaID(){
           
            if(id_usati.size() >= 1000){
                throw std::runtime_error("Tutti gli ID disponibili sono stati utilizzati.");
            }
           
            int id = (std::rand() % 1000) +100;

            if(id_usati.count(id) > 0){
                throw std::runtime_error("ID già esistnete.");
            }

            id_usati.insert(id);   // per inserire nel set o "container"
            return id;
        }
    };
