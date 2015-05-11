#ifndef CONSTANTE_H
#define CONSTANTE_H

#include <iostream>
#include "Erreurs.h"
#include <typeinfo>
#include <QString>
#include <cmath>


class Constante{
public:
    //Fonctions binaire
    virtual Constante* operator+(Constante* c)=0;
    virtual Constante* operator-(Constante* c)=0;
    virtual Constante* operator*(Constante* c)=0;
    virtual Constante* operator/(Constante* c)=0;
    virtual Constante* puissance(Constante* c)=0;
    virtual Constante* modulo(Constante* c)=0;

    //Fonctions unaires
    virtual Constante* sinus()=0;
    virtual Constante* cosinus()=0;
    virtual Constante* tangente()=0;
    virtual Constante* sinush()=0;
    virtual Constante* cosinush()=0;
    virtual Constante* tangenteh()=0;
    virtual Constante* logarithmen()=0;
    virtual Constante* logarithmed()=0;
    virtual Constante* oppose()=0;
    virtual Constante* inverse()=0;
    virtual Constante* racine()=0;
    virtual Constante* carre()=0;
    virtual Constante* cube()=0;
    virtual Constante* factorielle()=0;

    virtual QString toString() const = 0;
    virtual bool isType(const char * t) const = 0;
    virtual QString getValue() const;


protected:
    Constante(){}


};

#endif
