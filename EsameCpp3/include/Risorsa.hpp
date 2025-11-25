#ifndef RISORSA_HPP
#define RISORSA_HPP


#include <iostream>
#include <set>
#include <stdexcept>
#include <cstdlib>

class Risorsa {

    private:
        int id ;
        bool disponibile;
    public:
        Risorsa(int id);
        int getId() const;
        bool isDisponibile() const;
        void setDisponibile(bool disp);

};

#endif