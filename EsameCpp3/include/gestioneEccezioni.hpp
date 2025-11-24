// Header per IDGenerator
#ifndef GESTIONE_ECCEZIONI_HPP
#define GESTIONE_ECCEZIONI_HPP

#include <set>
#include <stdexcept>

class IDGenerator {
private:
    std::set<int> id_usati;
public:
    IDGenerator();
    int generaID();
};

#endif // GESTIONE_ECCEZIONI_HPP
