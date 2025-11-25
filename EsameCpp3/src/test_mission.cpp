#include "../include/Caserma.hpp"
#include "../include/gestioneEccezioni.hpp"
#include <iostream>
#include <map>

int main() {
    Caserma caserma;
    IDGenerator gen;
    
    int id1 = gen.generaID();
    int id2 = gen.generaID();
    int id3 = gen.generaID();

    caserma.aggiungiPersonale(std::make_unique<Personale>(id1, "Mario", Grado::SOLDATO));
    caserma.aggiungiPersonale(std::make_unique<Personale>(id2, "Luigi", Grado::SOLDATO));
    caserma.aggiungiPersonale(std::make_unique<Personale>(id3, "Gino", Grado::SOLDATO));

    int mid1 = gen.generaID();
    caserma.aggiungiMezzo(std::make_unique<Mezzo>(mid1, "Jeep"));
    int mid2 = gen.generaID();
    caserma.aggiungiMezzo(std::make_unique<Mezzo>(mid2, "Humvee"));

    std::vector<int> personaleIds = {id1, id2, id3};
    std::vector<int> mezziIds = {mid1};
    std::vector<int> mezziIds2 = {mid2};
    std::map<int, std::vector<int>> assegnamenti;
    assegnamenti[mid1] = {id1, id2};

    std::cout << "Creating mission with 2 per mezzo (should succeed)" << std::endl;
    caserma.creaMissione("Missione Test", personaleIds, mezziIds, assegnamenti);

    // Try to assign 1 person to mezzo (should fail)
    std::map<int, std::vector<int>> assegnamenti2;
    assegnamenti2[mid2] = {id3};
    std::cout << "Creating mission with 1 per mezzo (should fail)" << std::endl;
    caserma.creaMissione("Missione Fallita", personaleIds, mezziIds2, assegnamenti2);

    // Try to assign 3 persons to mezzo but mezzo only has 2 seats (if assigned)
    // To ensure capienza test, adjust num to exceed getPosti.
    // Try to assign 7 people to mezzo (should fail since >6)
    std::map<int, std::vector<int>> assegnamenti3;
    assegnamenti3[mid2] = {id1, id2, id3, id1, id2, id3, id1};
    std::cout << "Creating mission with more personnel than posti (should fail)" << std::endl;
    caserma.creaMissione("Missione Over", personaleIds, mezziIds2, assegnamenti3);

    return 0;
}
