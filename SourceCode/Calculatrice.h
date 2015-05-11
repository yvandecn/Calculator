#ifndef CALCULATRICE_H
#define CALCULATRICE_H

#ifndef TYPECONSTANTE
#define TYPECONSTANTE
typedef enum tc {entier, rationnel, reel} TypeConstante;
/**
 * \typedef TypeConstante : Type de nombres
 * \brief Enumération des types de nombres disponibles pour la calculatrice
 */
#endif


#include <QStack>
#include <Qstring>
#include "Constantes/Constante.h"
#include "Constantes/Complexe.h"
#include "Constantes/Pile.h"
#include <QStringList>

class Calculatrice
{
    QVector<Pile*> _pile;
    bool _typeComplexe;
    bool _typeDegre; //0:degré, 1:radiant
    TypeConstante _typeConst; // A l'affichage
    unsigned int _indexSwapStart;
    unsigned int _indexSwapEnd;
    unsigned int _nbSum;
    unsigned int _nbMean;
    unsigned int _nbAffichage;
    unsigned int _currentIndexHist;

public:
    Calculatrice(bool typeComplexe = false, bool typeDegre = false, TypeConstante typeConst = reel, unsigned int swapS = 0, unsigned int swapE = 1,unsigned int sum = 2, unsigned int mean = 2, unsigned int affiche=10, unsigned int currentIndexHist=0);


    bool getTypeComplexe() const;
    void setTypeComplexe(bool val);
    bool getTypeDegre() const;
    void setTypeDegre(bool val);
    TypeConstante getTypeConstante() const;
    void setIndexSwap(unsigned int a,unsigned int b);
    void setSum(unsigned int a);
    void setMean(unsigned int a);
    void setAffichage(unsigned int a);
    Constante* at(int i) const;
    unsigned int getSwapStart() const;
    unsigned int getSwapEnd() const ;
    unsigned int getSum() const;
    unsigned int getMean() const;
    unsigned int getAffichage () const;
    void setTypeConstante(TypeConstante type);
    QStringList getPileSauvegardeToString() const;
    void deletePile();
    void push(Constante * c);
    void newPile();
    void deleteLastPile();
    void operationBinaire();
    void operationUnaire();
    Constante* pop();
    Constante * getHistoriqueElement(unsigned int i) const;
   // Constante * popHistorique() { return _pileSauvegarde.pop(); }
    void setCurrentIndexHist(int indice);

    //void pushHistorique(Constante * c) { _pileSauvegarde.push(c);}
    //int countPileHistorique() const { return _pile.value(_currentIndexHist)->taille();}
    bool pileEmpty() const;

    unsigned int getCurrentIndexHist() const;
    int countPileElement();

    static double max(double a, double b);

    Constante* moyenne();
    Constante* somme();
    Constante* duplique();
    bool swap();

    Constante* sum();
    Constante* minus();
    Constante* multiply();
    Constante* div();
    Constante* puiss();
    Constante* modul();
    Constante* sinu();
    Constante* cosin();
    Constante* tang();
    Constante* sinuh();
    Constante* cosinh();
    Constante* tangh();
    Constante* logn();
    Constante* logd();
    Constante* signe();
    Constante* inv();
    Constante* racinecarre();
    Constante* sqr();
    Constante* puissancetrois();
    Constante* fact();
    ~Calculatrice(){
        foreach(Pile * p, _pile)
            delete p;
    }

};

#endif // CALCULATRICE_H
