#ifndef EXPRESSION_H
#define EXPRESSION_H

#include"Constante.h"
#include<QString>

class Expression : public Constante
{
private:
    QString _expression;

public:
    Expression(const QString& t);
    QString getExpression(bool guillemets) const;
    void setExpression(const QString& t);
    QString toString() const;
    void insert(int i, const QString& s);
    int size();
    QString getValue() const;

    //Operateurs binaires
    Constante* operator+(Constante* c);
    Constante* operator-(Constante* c);
    Constante* operator*(Constante* c);
    Constante* operator/(Constante* c);
    Constante* puissance(Constante* c);
    Constante* modulo(Constante* c);

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

    bool isType(const char *t) const;



};

#endif // EXPRESSION_H
