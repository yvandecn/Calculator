#ifndef PILE_H
#define PILE_H

#include <QVector>
#include "Complexe.h"
#include <QStringList>
class Pile{
    private :
        QVector<Constante *> _maPile;

    public :
        Pile() : _maPile(){}

        void vider();
        Constante* pop();
        void push(Constante * val);
        int taille() const;
        bool isEmpty() const;
        void permute(int a, int b);
        Pile(const Pile& p);
        Pile& operator=(const Pile& p);

        Constante* element(int i) const;
        QStringList toStringList() const;

        ~Pile();
    };

#endif // PILE_H
