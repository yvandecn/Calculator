#ifndef COMPLEXE_H
#define COMPLEXE_H

#include "Constante.h"
#include <iostream>
#include <typeinfo>
#include "Expression.h"
#include "Constantes/Rationnel.h"

class Complexe : public Constante{

    private :
        Rationnel _re;
        Rationnel _im;
        bool _modeComplexe;

    public :
        Complexe(Rationnel r, Rationnel i, bool modeC = false);
        Complexe(double num1, double den1, double num2, double den2, bool modeC = false, TypeConstante modeR = reel);

        QString toString()const;
        QString getValue() const;

        Rationnel getIm() const;
        Rationnel getRe() const;
        bool getModeComplexe() const;
        Complexe* getConjuguer() const;

        bool isType(const char *t) const;

        Constante* operator/(Constante* c);

        void setIm(Rationnel val);
        void setRe(Rationnel val);
        void setIm(double num);
        void setRe(double num);

        //Operateurs binaires
        Constante* operator+(Constante* c);
        Constante* operator-(Constante* c);
        Constante* operator*(Constante* c);
        Constante* puissance(Constante* c1);
        Constante* modulo(Constante* c1);

        //Fonctions unaires
        Constante* sinus();
        Constante* cosinus();
        Constante* tangente();
        Constante* sinush();
        Constante* cosinush();
        Constante* tangenteh();
        Constante* logarithmen();
        Constante* logarithmed();
        Constante* oppose();
        Constante* inverse();
        Constante* racine();
        Constante* carre();
        Constante* cube();
        Constante* factorielle();
};

#endif
