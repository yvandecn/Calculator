///
/// \class     Calculatrice
/// \author    Y.Vandecnocke & S.Ferry
/// \version   1.0
/// \date      08 Juin 2012
/// \brief     Fonctionnement de la Calculatrice
///
/// \details   Cette classe gère le fonctionnement de la calculatrice et permet de gèrer les différentes options d'affichage et de calcul
///

#include "calculatrice.h"

#define PI 3.14159265


Calculatrice::Calculatrice(bool typeComplexe, bool typeDegre, TypeConstante typeConst, unsigned int swapS, unsigned int swapE,unsigned int sum, unsigned int mean, unsigned int affiche, unsigned int currentIndexHist): _typeComplexe(typeComplexe), _typeDegre(typeDegre), _typeConst(typeConst), _indexSwapStart(swapS), _indexSwapEnd(swapE), _nbSum(sum), _nbMean(mean), _nbAffichage(affiche), _currentIndexHist(currentIndexHist)
    {
    _pile.push_back(new Pile());
    _currentIndexHist = 0;
    /**
     * \brief    Constructeur
     * \details  Permet de construire un objet de type Calculatrice
     * \param    typeComplexe bool vrai si on veut activer le mode complexe
     * \param    typeDegre bool vrai pour radian faux pour degré
     * \param    typeConst typeConstante définissant le type de nombre à utiliser
     * \param    swapS unsigned int définissant le premier indice de la fonction swap
     * \param    swapE unsigned int définissant le dernier indice de la fonction swap
     * \param    sum unsigned int définissant le nom d'élément à sommer avec la fonction somme
     * \param    mean unsigned int définissant le nom d'élément à moyenner avec la fonction moyenne
     * \param    affiche unsigned int définissant le nom d'élément à afficher
     * \param    currentIndexHist unsigned int définissant l'indice de la pile actuelle dans la liste historique
     */
}


bool Calculatrice::getTypeComplexe() const{
    return _typeComplexe;
    /**
     * \brief    Obtenir le type complexe
     * \return   bool vrai si le mode complexe est activé
     */
}

void Calculatrice::setTypeComplexe(bool val){
    _typeComplexe = val;
    /**
     * \brief    Modifier le type complexe
     * \param    val bool remplaçant le type complexe
     */
}

bool Calculatrice::getTypeDegre() const{
    return _typeDegre;
    /**
     * \brief    Obtenir le type de degré
     * \return   bool vrai si le mode de degré est radian, faux pour degré
     */
}

void Calculatrice::setTypeDegre(bool val){
    _typeDegre = val;
    /**
     * \brief    Modifier le type de degré
     * \param    val bool remplaçant le type de degré
     */
}

TypeConstante Calculatrice::getTypeConstante() const {
    return _typeConst;
    /**
     * \brief    Obtenir le type de constante
     * \return   TypeConstante déterminant le type de nombre
     */
}

Constante* Calculatrice::at(int i) const {
    return _pile.value(_currentIndexHist)->element(i);
    /**
     * \brief    Obtenir l'élément i de la pile actuelle
     * \param    i int indice
     * \return   La Constante* se trouvant à l'indice i
     */
}

unsigned int Calculatrice::getSwapStart() const {
    return _indexSwapStart;
    /**
     * \brief    Obtenir l'indice de début de swap
     * \return   unsigned int
     */
}

unsigned int Calculatrice::getSwapEnd() const {
    return _indexSwapEnd;
    /**
     * \brief    Obtenir l'indice de fin de swap
     * \return   unsigned int
     */
}

unsigned int Calculatrice::getSum() const {
    return _nbSum;
    /**
     * \brief    Obtenir le nombre d'éléments à sommer
     * \return   unsigned int
     */
}

unsigned int Calculatrice::getMean() const {
    return _nbMean;
    /**
     * \brief    Obtenir le nombre d'éléments à moyenner
     * \return   unsigned int
     */
}

unsigned int Calculatrice::getAffichage () const {
    return _nbAffichage;
    /**
     * \brief    Obtenir le nombre d'éléments à afficher
     * \return   unsigned int
     */
}

void Calculatrice::setTypeConstante(TypeConstante type) {
    _typeConst = type;
    /**
     * \brief    Modifier le type de constante
     * \param    type TypeConstante remplaçant le type de constante
     */
}

QStringList Calculatrice::getPileSauvegardeToString() const {
    return _pile.value(_currentIndexHist)->toStringList();
    /**
     * \brief    Transformer en liste de QString
     * \return   QStringList contenant les éléments de la pile sous forme de QString
     */
}

void Calculatrice::deletePile(){
    _pile.push_back(
    new Pile());
    _currentIndexHist++;
    /**
     * \brief    Crée une nouvelle pile vide dans l'historique
     */
}

Constante * Calculatrice::getHistoriqueElement(unsigned int i) const{
    return _pile.value(_currentIndexHist)->element(i);
    /**
     * \brief    Obtenir l'élément i de la pile actuelle
     * \param    i int indice
     * \return   La Constante* se trouvant à l'indice i
     */
}

bool Calculatrice::pileEmpty() const {
    return _pile.value(_currentIndexHist)->isEmpty();
    /**
     * \brief    Tester si la pile est vide
     * \return   un bool vrai si la pile est vide
     */
}

unsigned int Calculatrice::getCurrentIndexHist() const{
    return _currentIndexHist;
    /**
     * \brief    Obtenir l'index de la pile actuelle dans la liste d'historique
     * \return   unsigned int
     */
}

int Calculatrice::countPileElement(){
    return _pile.value(_currentIndexHist)->taille();
    /**
     * \brief    Obtenir le nombre de pile dans l'historique
     * \return   int
     */
}

double Calculatrice::max(double a, double b) {
    return ((a+b+abs(a-b))/2);
    /**
     * \brief    Maximum de deux réels
     * \param    a double à tester
     * \param    b double à tester
     * \return   le maximum des deux nombres
     */
}

Constante* Calculatrice::pop(){
    if(_pile.value(_currentIndexHist)->isEmpty())
        return false;
    return _pile.value(_currentIndexHist)->pop();
    /**
     * \brief    Retire le dernier élément de la pile de calcul
     * \return   La Constante retirée
     */
}

void Calculatrice::deleteLastPile()
{
    delete _pile.value(_pile.size()-1);
    _pile.pop_back();
    _currentIndexHist--;
    /**
     * \brief    Supprime la dernière pile de l'historique
     */
}


void Calculatrice::setIndexSwap(unsigned int a,unsigned int b)
{
    if (a>=1)
        _indexSwapStart=a;
    if (b>=1)
    _indexSwapEnd=b;
    /**
     * \brief    Modifier les index de swap
     * \param    a unsigned int remplaçant l'index de début de swap
     * \param    b unsigned int remplaçant l'index de fin de swap
     */

}

void Calculatrice::setSum(unsigned int a)
{
    if (a>=2)
        _nbSum=a;
    /**
     * \brief    Modifier le nombre d'éléments à sommer
     * \param    a unsigned int remplaçant nombre d'éléments à sommer
     */
}

void Calculatrice::setMean(unsigned int a)
{
    if (a>=2)
        _nbMean=a;
    /**
     * \brief    Modifier le nombre d'éléments à moyenne
     * \param    a unsigned int remplaçant nombre d'éléments à moyenner
     */
}

void Calculatrice::setAffichage(unsigned int a)
{
    if (a>=1)
        _nbAffichage=a;
    /**
     * \brief    Modifier le nombre d'éléments à afficher
     * \param    a unsigned int remplaçant nombre d'éléments à afficher
     */
}

void Calculatrice::push(Constante * c) {
    newPile();
    _pile.value(_currentIndexHist)->push(c);

                          /**
                           * \brief    Ajoute à la fin de la pile de calcul
                           * \param  c  La Constante à ajouter à la pile
                           */
}

void Calculatrice::newPile() {
    while(_pile.size() > (int)_currentIndexHist+1)
        _pile.pop_back();
    _pile.push_back(new Pile(*_pile.value(_currentIndexHist)));
    _currentIndexHist++;

                          /**
                           * \brief    Génère une nouvelle pile
                           */
}

Constante* Calculatrice::sum(){
    if(_pile.value(_currentIndexHist)->taille() < 2)
        throw Erreurs(3,"Opération impossible : nombre d'argument insuffisant");
    else {
        Constante * c1 = this->at(_pile.value(_currentIndexHist)->taille()-1);
        Constante * c2 = this->at(_pile.value(_currentIndexHist)->taille()-2);
        return c2->operator +(c1);
        }
    /**
     * \brief     Fonction d'addition de la calculatrice
     * \return    La Constante résultante
     */
}

Constante* Calculatrice::minus(){
    if(_pile.value(_currentIndexHist)->taille() < 2)
        throw Erreurs(3,"Opération impossible : nombre d'argument insuffisant");
    else {
        Constante * c1 = this->at(_pile.value(_currentIndexHist)->taille()-1);
        Constante * c2 = this->at(_pile.value(_currentIndexHist)->taille()-2);
        return c2->operator -(c1);
    }
    /**
     * \brief     Fonction de soustraction de la calculatrice
     * \return    La Constante résultante
     */
    }

Constante* Calculatrice::multiply(){
    if(_pile.value(_currentIndexHist)->taille() < 2)
        throw Erreurs(3,"Opération impossible : nombre d'argument insuffisant");
    else {
        Constante * c1 = this->at(_pile.value(_currentIndexHist)->taille()-1);
        Constante * c2 = this->at(_pile.value(_currentIndexHist)->taille()-2);
        return c2->operator *(c1);
    }
    /**
     * \brief     Fonction de multiplication de la calculatrice
     * \return    La Constante résultante
     */
    }

Constante* Calculatrice::div(){
    if(_pile.value(_currentIndexHist)->taille() < 2)
        throw Erreurs(3,"Opération impossible : nombre d'argument insuffisant");
    else {
        Constante * c1 = this->at(_pile.value(_currentIndexHist)->taille()-1);
        Constante * c2 = this->at(_pile.value(_currentIndexHist)->taille()-2);
        if(c1->isType("Complexe")){
            Complexe *y = dynamic_cast<Complexe*>(c1);
            if (y->getRe()==0 && y->getIm()==0)
            {
                this->push(c2);
                this->push(c1);
                throw Erreurs(1,"Division par 0 impossible");
            }
        }
        if (c1->isType("Complexe") && c2->isType("Complexe") && _typeConst==entier)
        {
            return(c2->operator -(c2->modulo(c1)))->operator /(c1);
        }
        return c2->operator /(c1);
    }
    /**
     * \brief     Fonction de division de la calculatrice
     * \return    La Constante résultante
     */
    }

Constante* Calculatrice::puiss(){
    if(_pile.value(_currentIndexHist)->taille() < 2)
        throw Erreurs(3,"Opération impossible : nombre d'argument insuffisant");
    else {
        Constante * c1 = this->at(_pile.value(_currentIndexHist)->taille()-1);
        Constante * c2 = this->at(_pile.value(_currentIndexHist)->taille()-2);;
        return c2->puissance(c1);
    }
    /**
     * \brief     Fonction puissance de la calculatrice
     * \return    La Constante résultante
     */
    }

Constante* Calculatrice::modul(){
    if(_pile.value(_currentIndexHist)->taille() < 2)
        throw Erreurs(3,"Opération impossible : nombre d'argument insuffisant");
    else {
        Constante * c1 = this->at(_pile.value(_currentIndexHist)->taille()-1);
        Constante * c2 = this->at(_pile.value(_currentIndexHist)->taille()-2);
        return c2->modulo(c1);
    }
    /**
     * \brief     Fonction modulo de la calculatrice
     * \return    La Constante résultante
     */
    }

Constante* Calculatrice::sinu(){
    if(_pile.value(_currentIndexHist)->taille() < 1)
        throw Erreurs(3,"Opération impossible : nombre d'argument insuffisant");
    else {
        Constante * c = this->at(_pile.value(_currentIndexHist)->taille()-1);
        if (this->getTypeDegre()==false && c->isType("Complexe")){
            Complexe *y = dynamic_cast<Complexe*>(c);
            y->setRe((y->getRe()*(PI/180.0)));
            return y->sinus();
        }
        else
        {
            return c->sinus();
        }

    }
    /**
     * \brief     Fonction sinus de la calculatrice
     * \return    La Constante résultante
     */
    }

Constante* Calculatrice::cosin(){
    if(_pile.value(_currentIndexHist)->taille() < 1)
        throw Erreurs(3,"Opération impossible : nombre d'argument insuffisant");
    else {
        Constante * c = this->at(_pile.value(_currentIndexHist)->taille()-1);

        if (this->getTypeDegre()==false && c->isType("Complexe")){
            Complexe *y = dynamic_cast<Complexe*>(c);
            y->setRe((y->getRe()*PI/180.0));
            return y->cosinus();
        }
        else
        {
            return c->cosinus();
        }
    }
    /**
     * \brief     Fonction cosinus de la calculatrice
     * \return    La Constante résultante
     */
    }

Constante* Calculatrice::tang(){
    if(_pile.value(_currentIndexHist)->taille() < 1)
        throw Erreurs(3,"Opération impossible : nombre d'argument insuffisant");
    else {
        Constante * c = this->at(_pile.value(_currentIndexHist)->taille()-1);
        if (this->getTypeDegre()==false && c->isType("Complexe")){
            Complexe *y = dynamic_cast<Complexe*>(c);
            y->setRe((y->getRe()*PI/180.0));
            return y->tangente();
        }
        else
            return c->tangente();
    }
    /**
     * \brief     Fonction tangente de la calculatrice
     * \return    La Constante résultante
     */
    }

Constante* Calculatrice::sinuh(){
    if(_pile.value(_currentIndexHist)->taille() < 1)
        throw Erreurs(3,"Opération impossible : nombre d'argument insuffisant");
    else {
        Constante * c = this->at(_pile.value(_currentIndexHist)->taille()-1);

        if( c == false)
               return false;

        if (this->getTypeDegre()==false && c->isType("Complexe")){
            Complexe *y = dynamic_cast<Complexe*>(c);
            y->setRe((y->getRe()*PI/180.0));
            return y->sinush();
        }
        else
            return c->sinush();
    }
    /**
     * \brief     Fonction sinus hyperbolique de la calculatrice
     * \return    La Constante résultante
     */
    }

Constante* Calculatrice::cosinh(){
    if(_pile.value(_currentIndexHist)->taille() < 1)
        throw Erreurs(3,"Opération impossible : nombre d'argument insuffisant");
    else {
        Constante * c = this->at(_pile.value(_currentIndexHist)->taille()-1);
        if (this->getTypeDegre()==false && c->isType("Complexe")){
            Complexe *y = dynamic_cast<Complexe*>(c);
            y->setRe((y->getRe()*PI/180.0));
            return y->cosinush();
        }
        else
            return c->cosinush();
    }
    /**
     * \brief     Fonction cosinus hyperbolique de la calculatrice
     * \return    La Constante résultante
     */
    }

Constante* Calculatrice::tangh(){
    if(_pile.value(_currentIndexHist)->taille() < 1)
        throw Erreurs(3,"Opération impossible : nombre d'argument insuffisant");
    else {
        Constante * c = this->at(_pile.value(_currentIndexHist)->taille()-1);
        if (this->getTypeDegre()==false && c->isType("Complexe")){
            Complexe *y = dynamic_cast<Complexe*>(c);
            y->setRe((y->getRe()*PI/180.0));
            return y->tangenteh();
        }
        else
            return c->tangenteh();
    }
    /**
     * \brief     Fonction tangente hyperbolique de la calculatrice
     * \return    La Constante résultante
     */
    }

Constante* Calculatrice::logn(){
    if(_pile.value(_currentIndexHist)->taille() < 1)
        throw Erreurs(3,"Opération impossible : nombre d'argument insuffisant");
    else {
        Constante * c = this->at(_pile.value(_currentIndexHist)->taille()-1);
        if(c->isType("Complexe")){
            Complexe *y = dynamic_cast<Complexe*>(c);
            if (y->getRe()<=0)
            {
                this->push(c);
                throw Erreurs(6,"Fonction logarithme impossible sur un nombre négatif");
            }
        }
            return c->logarithmen();
        }
    /**
     * \brief     Fonction logarithme népérien de la calculatrice
     * \return    La Constante résultante
     */
    }

Constante* Calculatrice::logd(){
    if(_pile.value(_currentIndexHist)->taille() < 1)
        throw Erreurs(3,"Opération impossible : nombre d'argument insuffisant");
    else {
        Constante * c = this->at(_pile.value(_currentIndexHist)->taille()-1);
        if(c->isType("Complexe")){
            Complexe *y = dynamic_cast<Complexe*>(c);
            if (y->getRe()<0)
            {
                this->push(c);
                throw Erreurs(6,"Fonction logarithme impossible sur un nombre négatif");
            }
        }
            return c->logarithmen();
    }
    /**
     * \brief     Fonction logarithme décimal de la calculatrice
     * \return    La Constante résultante
     */
}

Constante* Calculatrice::signe(){
    if(_pile.value(_currentIndexHist)->taille() < 1)
        throw Erreurs(3,"Opération impossible : nombre d'argument insuffisant");
    else {
        Constante * c = this->at(_pile.value(_currentIndexHist)->taille()-1);
            return c->oppose();
    }
    /**
     * \brief     Fonction d'inversion de signe de la calculatrice
     * \return    La Constante résultante
     */
    }

Constante* Calculatrice::inv(){
    if(_pile.value(_currentIndexHist)->taille() < 1)
        throw Erreurs(3,"Opération impossible : nombre d'argument insuffisant");
    else {
        Constante * c = this->at(_pile.value(_currentIndexHist)->taille()-1);
            return c->inverse();
    }
    /**
     * \brief     Fonction inverse de la calculatrice
     * \return    La Constante résultante
     */
    }

Constante* Calculatrice::racinecarre(){
    if(_pile.value(_currentIndexHist)->taille() < 1)
        throw Erreurs(3,"Opération impossible : nombre d'argument insuffisant");
    else {
        Constante * c = this->at(_pile.value(_currentIndexHist)->taille()-1);
        if(c->isType("Complexe")){
            Complexe *y = dynamic_cast<Complexe*>(c);
            if (y->getRe()<0)
            {
                this->push(c);
                throw Erreurs(6,"Fonction racine impossible sur un nombre négatif");
            }
        }
            return c->racine();
    }
    /**
     * \brief     Fonction racine carrée de la calculatrice
     * \return    La Constante résultante
     */
    }

Constante* Calculatrice::sqr(){
    if(_pile.value(_currentIndexHist)->taille() < 1)
        throw Erreurs(3,"Opération impossible : nombre d'argument insuffisant");
    else {
        Constante * c = this->at(_pile.value(_currentIndexHist)->taille()-1);
            return c->carre();
        }
    /**
     * \brief     Fonction carré de la calculatrice
     * \return    La Constante résultante
     */
    }

Constante* Calculatrice::puissancetrois(){
    if(_pile.value(_currentIndexHist)->taille() < 1)
        throw Erreurs(3,"Opération impossible : nombre d'argument insuffisant");
    else {
        Constante * c = this->at(_pile.value(_currentIndexHist)->taille()-1);
            return c->cube();
            /**
             * \brief     Fonction cube de la calculatrice
             * \return    La Constante résultante
             */
    }
    }

Constante* Calculatrice::fact(){
    if(_pile.value(_currentIndexHist)->taille() < 1)
        throw Erreurs(3,"Opération impossible : nombre d'argument insuffisant");
    else {
        Constante * c = this->at(_pile.value(_currentIndexHist)->taille()-1);
            return c->factorielle();
    }
    /**
     * \brief     Fonction factorielle de la calculatrice
     * \return    La Constante résultante
     */
}

Constante* Calculatrice::moyenne()
{
    if (_pile.value(_currentIndexHist)->taille() < (int)_nbMean)
    {
        throw Erreurs(3,"Opération impossible : nombre d'argument insuffisant");
    }
    else
    {
        Constante * c = this->at(_pile.value(_currentIndexHist)->taille()-1);
        Complexe* diviseur = new Complexe(_nbMean,0, _typeComplexe);
        for (unsigned int i(1); i<_nbMean; i++)
        {
            //if(c->isType("Complexe"))
                c=c->operator+(this->at(_pile.value(_currentIndexHist)->taille()-i-1));
            //else
        }
        c=c->operator/(diviseur);
        return c;
    }
    /**
     * \brief     Fonction moyenne de la calculatrice
     * \return    La Constante résultante
     */
}

Constante* Calculatrice::somme()
{
    if (_pile.value(_currentIndexHist)->taille() < (int)_nbSum)
    {
        throw Erreurs(3,"Opération impossible : nombre d'argument insuffisant");
    }
    else
    {
        Constante * c = this->at(_pile.value(_currentIndexHist)->taille()-1);
        for (unsigned int i(1); i<_nbSum; i++)
        {
                c=c->operator+(this->at(_pile.value(_currentIndexHist)->taille()-i-1));
        }
        return c;
    }
    /**
     * \brief     Fonction somme de la calculatrice
     * \return    La Constante résultante
     */
}


bool Calculatrice::swap()
{
    if (_pile.value(_currentIndexHist)->taille() > Calculatrice::max(_indexSwapStart, _indexSwapEnd))
    {
       _pile.value(_currentIndexHist)->permute(_indexSwapStart, _indexSwapEnd);
        return true;
    }
    else
        throw Erreurs(4,"Aucun élément à la position demandée");
    /**
     * \brief     Fonction permutation de la calculatrice
     * \details    Echange les éléments présents aux indicesspécifiés dans les paramètres de la calculatrice
     * \return    La Constante résultante
     */
}

Constante* Calculatrice::duplique()
{
    if (_pile.value(_currentIndexHist)->isEmpty())
        throw Erreurs(5,"Aucun élément à dupliquer");
    else
    {
        Constante * c = this->at(_pile.value(_currentIndexHist)->taille()-1);
        _pile.value(_currentIndexHist)->push(c);
        _pile.value(_currentIndexHist)->push(c);
        return c;
    }
    /**
     * \brief     Fonction duplication de la calculatrice
     * \return    La Constante résultante
     */

}

void Calculatrice::setCurrentIndexHist(int indice){
    if( indice < 0)
        indice = 0;
    else if( indice > _pile.size()-1)
        indice = _pile.size()-1;
    _currentIndexHist = indice;
    /**
     * \brief    Modifier l'indice de la pile actuelle dans la liste d'historique
     * \param    indice int remplaçant l'indice de la pile actuelle dans la liste d'historique
     */
}

void Calculatrice::operationBinaire()
{
    Constante * t = _pile.value(_currentIndexHist)->pop();
    _pile.value(_currentIndexHist)->pop();
    _pile.value(_currentIndexHist)->pop();
    _pile.value(_currentIndexHist)->push(t);
    /**
     * \brief    Modifie la pile après une opération binaire
     */
}

void Calculatrice::operationUnaire()
{
    Constante * t = _pile.value(_currentIndexHist)->pop();
    _pile.value(_currentIndexHist)->pop();
    _pile.value(_currentIndexHist)->push(t);
    /**
     * \brief    Modifie la pile après une opération unaire
     */
}
