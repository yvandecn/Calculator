#ifndef RATIONNEL_H
#define RATIONNEL_H

//#include "Constante.h"
//#include "Calculatrice.h"
#include <math.h>
#include<QString>
#include"Erreurs.h"

#ifndef TYPECONSTANTE
#define TYPECONSTANTE
typedef enum tc {entier, rationnel, reel} TypeConstante;
#endif

class Rationnel{
private:
    double _num;
    double _den;
    TypeConstante _type;


    void simplifier(double&, double&);
    //bool isSequence(double a, int& b);
    //QString getFraction(double c);

public:
    void simplifier(Rationnel& r);
    void simplifier();
    static int pgcd(int a, int b);

    //static QString reel(double c);
    Rationnel(double n, double d = 1, TypeConstante type = reel, bool razentier=true);


    QString toString() const;
    QString getValue() const;
    Rationnel getOppose() const;
    Rationnel getInverse() const;
    double getNum() const;
    double getDen() const;
    TypeConstante getType() const;
    void setOppose();
    void setInverse();
    void setNum(double val);
    void setDen(double val);

    int toInt();
    double toDouble();

    Rationnel racine();
    Rationnel operator+(Rationnel c);
    Rationnel operator-(Rationnel c);
    Rationnel operator*(Rationnel c);
    Rationnel operator*(double d);
    Rationnel operator/(Rationnel c);
    bool operator==(double d);
    bool operator<(double d);
    bool operator<=(double d);
    Rationnel puissance(const Rationnel& a);
};


#endif
