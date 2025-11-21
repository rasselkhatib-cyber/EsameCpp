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
        Risorsa(int id ) :id(id),disponibile(true){}
        int getId()const{return id;}
        bool isDisponibile()const{return disponibile;}
        void setDisponibile(bool disp){disponibile=disp;}       

};

#endif