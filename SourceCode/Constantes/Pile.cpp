///
/// \class     Pile
/// \author    Y.Vandecnocke & S.Ferry
/// \version   1.0
/// \date      08 Juin 2012
/// \brief     Pile de calcul
///
/// \details   Cette classe gère la manipulation de la pile, qui permet le stockage des données
///

#include "Pile.h"

Pile::~Pile(){
    foreach(Constante * c, _maPile)
        delete c;
    /**
     * \brief    Déstructeur
     */
}

Pile::Pile(const Pile& p){
    for(int i = 0; i < p.taille(); i++){
        Constante * c = p.element(i);
        if(c->isType("Expression")){
            Expression * d = dynamic_cast<Expression*>(c);
            _maPile.push_back(new Expression(*d));
        }
        else if(c->isType("Complexe")){
            Complexe* d = dynamic_cast<Complexe*>(c);
            _maPile.push_back(new Complexe(*d));
        }
    }
    /**
     * \brief    Constructeur par recopie
     * \details  Permet de construire une pile à partir d'une autre
     * \param    p une const Pile& à recopier
     */
}

Pile& Pile::operator=(const Pile& p){
    if(&p != this){
        _maPile.clear();
        for(int i = 0; i < p.taille(); i++){
            Constante * c = p.element(i);
            if(c->isType("Expression")){
                Expression * d = dynamic_cast<Expression*>(c);
                _maPile.push_back(new Expression(*d));
            }
            else if(c->isType("Complexe")){
                Complexe* d = dynamic_cast<Complexe*>(c);
                _maPile.push_back(new Complexe(*d));
            }
        }
    }
return *this;
/**
 * \brief    Opérateur d'affectation
 * \details  Permet d'affecter à une pile la valeur d'une autre pile passée en paramètre
 * \param    p une const Pile& à recopier
 * \return   Une référence sur une pile
 */
}

Constante* Pile::element(int i) const {
    return _maPile.value(i);
    /**
     * \brief    Elément numéro i
     * \param    i un int représentant la position de l'élément à renvoyé
     * \return   La Constante* située à l'indice i
     */
}

void Pile::vider(){
    _maPile.clear();
    /**
     * \brief    Vider
     * \details  Vide la pile
     */
}

QStringList Pile::toStringList() const{
    QStringList list;
    QList<Constante*> listConstante = _maPile.toList();
    foreach(Constante * s, listConstante){
        if( s != 0 && s != false)
            list.push_back(s->toString());
    }
    return list;
    /**
     * \brief    Conversion en liste
     * \details  Convertie la pile en liste de \e QString
     * \return   une \e QStringList contenant les éléments de la pile
     */
}

Constante* Pile::pop(){
    if(this->isEmpty())
        return false;
    else{
        Constante* t = _maPile.at(_maPile.size()-1);
        _maPile.pop_back();
        return t;
        }
    /**
     * \brief    Retire le dernier élément de la pile
     * \return   La \e Constante retirée
     */
    }

void Pile::push(Constante * val){
    if(val != 0 && val != false)
        _maPile.push_back(val);
    /**
     * \brief    Ajoute à la fin de la pile
     * \param  val  La \e Constante à ajouter à la pile
     */
}

void Pile::permute(int a, int b)
{
    if (a>b)
    {
        int tmp = a;
        a = b;
        b = tmp;
    }

    if (a==b)
    {}

    else
    {
        Constante* tmp1 = _maPile.at(a);
        Constante* tmp2 = _maPile.at(b);
        _maPile.remove(a);
        _maPile.insert(a, tmp2);
        _maPile.remove(b);
        _maPile.insert(b, tmp1);
    }
    /**
     * \brief    Permute les éléments a et b
     * \param   a \e integer
     * \param   b \e integer
     */
}

int Pile::taille() const {
    return _maPile.size();
    /**
     * \brief    Taille de la Pile
     * \return   La taille sous forme d'int
     */
}

bool Pile::isEmpty() const {
    return _maPile.isEmpty();
    /**
     * \brief    Tester si la pile est vide
     * \return   un bool vrai si la pile est vide
     */
}
