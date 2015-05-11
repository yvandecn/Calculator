///
/// \class     Rationnel
/// \author    Y.Vandecnocke & S.Ferry
/// \version   1.0
/// \date      08 Juin 2012
/// \brief     Gestion des nombres Rationnels
///
/// \details   Cette classe gère la manipulation des nombres Rationnels
///

#include "Rationnel.h"


Rationnel::Rationnel(double n, double d, TypeConstante type, bool razentier): _num(n), _den(d), _type(type)
{
    if (_den==0)
        throw Erreurs(1,"Division par 0 impossible");
    else
    {
        if (_type==reel)
        {
            _num=(_num/_den);
            _den=1;
        }
        else if (_type==entier && razentier == true)
        {
            double rez = _num/_den;
            if (floor(rez+0.5) == floor(rez))
                rez=floor(rez);
            else
                rez=ceil(rez);
            _num=rez;
            _den=1;
         }
        else
            simplifier(_num,_den);
    }
    /**
     * \brief    Constructeur de Rationnel
     * \details  Construit un rationnel en tenant compte du type de nombre
     * \param n double à passer en numérateur
     * \param d double à passer en dénominateur
     * \param type TypeConstante du rationnel à créer
     * \param razentier bool déterminant si le rationnel créé en mode entier doit être arrondie
     */
}

Rationnel Rationnel::getOppose() const {
    Rationnel t(-_num,_den,_type);
    return t;
    /**
     * \brief    Obtenir l'opposé
     * \return   Le Rationnel opposé
     */
}

void Rationnel::setOppose() {
    this->setNum(-_num); this->setDen(_den);
    /**
     * \brief    Transforme en l'opposé
     */
}

void Rationnel::setInverse() {
    double n = _num; this->setNum(_den); this->setDen(n);
    /**
     * \brief    Transforme en l'inverse
     */
}

void Rationnel::setNum(double val){
    _num = val;
    /**
     * \brief    Modifier le numérateur
     * \param    val le double remplaçant le numérateur
     */
}

void Rationnel::setDen(double val){
    _den = val;
    /**
     * \brief    Modifier le dénominateur
     * \param    val le double remplaçant le dénominateur
     */
}

double Rationnel::getNum() const{
    return _num;
    /**
     * \brief    Obtenir le numérateur
     * \return   Le numérateur sous forme de double
     */
}

double Rationnel::getDen() const{
    return _den;
    /**
     * \brief    Obtenir le dénominateur
     * \return   Le dénominateur sous forme de double
     */
}

TypeConstante Rationnel::getType() const {
    return _type;
    /**
     * \brief    Obtenir le type de nombre
     * \return   Le type de nombre sous forme de TypeConstante
     */
}

QString Rationnel::toString() const{
    QString t;
    t+=(QString::number(_num));
    if (_type==rationnel && _den!=1)
        t+= " / " + QString::number(_den);
    return t;
    /**
     * \brief    Convertit le rationnel en QString
     * \return  Un QString contenant le Rationnel destiné à être affiché
     */

}

QString Rationnel::getValue() const
{
    QString t;
    t+=(QString::number(_num));
    if (_type==rationnel)
        t+= "/" + QString::number(_den);
    return t;
    /**
     * \brief    Convertit le rationnel en QString
     * \return  Un QString contenant le Rationnel destiné à ne pas être affiché
     */
}

int Rationnel::pgcd(int a, int b)
{
    while (b != 0)
    {
        const int t = b;
        b = a%b;
        a=t;
    }
    return a;
    /**
     * \brief    PGCD de deux entiers
     * \param a integer
     * \param b integer
     * \return Un integer PGCD des paramètres

     */
}

void Rationnel::simplifier(double& a, double& b)
{
    while(floor(a)!=a || floor(b)!=b)
    {
        a*=10;
        b*=10;
    }
    int num = (int) a;
    int den = (int) b;
    int div=pgcd(num, den);
    if( div > 0){
        num/=div;
        den/=div;
        if ((num>0 && den<0) || (num<0 && den<0))
        {
            num*=-1;
            den*=-1;
        }
        a=num;
        b=den;
    }
    /**
     * \brief    Simplification d'une fraction
     * \param a double numérateur
     * \param b double dénomiateur
     */
}

void Rationnel::simplifier(Rationnel& r)
{
    double a = r.getNum();
    double b = r.getDen();
    simplifier(a,b);
    r.setNum(a);
    r.setDen(b);
    /**
     * \brief    Simplification d'une fraction
     * \param r Rationnel à simplifier

     */
}

void Rationnel::simplifier()
{
    simplifier(*this);
    /**
     * \brief    Simplification de la fraction
     */
}


Rationnel Rationnel::getInverse() const
{
    double num = this->getNum();
    double den = this->getDen();
    Rationnel t(den, num, this->getType(), false);
    return t;
    /**
     * \brief   Inverse d'une fraction
     * \return  Le rationnel inverse
     */
}

int Rationnel::toInt(){
    if(floor((getNum()/getDen()+0.5))> floor(getNum()/getDen()))
        return floor((getNum()/getDen()));
    else
        return ceil((getNum()/getDen()));
    /**
     * \brief    Conversion en entier
     * \return   Un integer, arrondi de la valeur de la fraction
     */
}

double Rationnel::toDouble(){
    return _num/_den;
    /**
     * \brief    Conversion en réel
     * \return   Un double, approché de la valeur de la fraction
     */
}

Rationnel Rationnel::racine(){
    Rationnel t(sqrt(_num),sqrt(_den),_type);
    return t;
    /**
     * \brief    Racnie carrée
     * \return   Le Rationnel racine carrée
     */
}


Rationnel Rationnel::operator+(Rationnel c){
    double nA = this->_num;
    double nB = c.getNum();
    double dA = this->_den;
    double dB = c.getDen();
    Rationnel r(nA*dB+nB*dA,dA*dB,this->_type);
    if (_type == rationnel)
        simplifier(r);
    return r;
    /**
     * \brief    Somme
     * \details  Surcharge de l'opérateur + permettant de sommer deux rationnels
     * \param    c Le Rationnel à sommer
     * \return   Le Rationnel résultant de la somme
     */
    }

Rationnel Rationnel::operator-(Rationnel c){
    double nA = this->_num;
    double nB = c.getNum();
    double dA = this->_den;
    double dB = c.getDen();
    Rationnel r(nA*dB-nB*dA,dA*dB,this->_type);
    if (_type == rationnel)
        simplifier(r);
    return r;
    /**
     * \brief    Soustraction
     * \details  Surcharge de l'opérateur - permettant de soustraire deux rationnels
     * \param    c Le Rationnel à soustraire
     * \return   Le Rationnel résultant de la soustraction
     */
    }
Rationnel Rationnel::operator*(Rationnel c){
    double nA = this->_num;
    double nB = c.getNum();
    double dA = this->_den;
    double dB = c.getDen();
    Rationnel r(nA*nB,dA*dB,this->_type);
    if (_type == rationnel)
        simplifier(r);
    return r;
    /**
     * \brief    Multiplication
     * \details  Surcharge de l'opérateur * permettant de multiplier deux rationnels
     * \param    c Le Rationnel à multiplier
     * \return   Le Rationnel résultant de la multiplication
     */
    }

Rationnel Rationnel::operator*(double d){
    double num = this->_num;
    double den = this->_den;
    Rationnel r(num*d,den,this->_type);
    if (_type == rationnel)
        simplifier(r);
    return r;
    /**
     * \brief    Multiplication
     * \details  Surcharge de l'opérateur * permettant de multiplier un rationnel et un réel
     * \param    d Le double à multiplier
     * \return   Le Rationnel résultant de la multiplication
     */
    }

Rationnel Rationnel::operator/(Rationnel c){
    Rationnel tmp = c.getInverse();
    Rationnel r = this->operator*(tmp);
    if (_type == rationnel)
        simplifier(r);
    return r;
    /**
     * \brief    Division
     * \details  Surcharge de l'opérateur / permettant de diviser deux rationnels
     * \param    c Le Rationnel à diviser
     * \return   Le Rationnel résultant de la division
     */
    }

bool Rationnel::operator==(double d)
{
    if((_num/_den)==d)
        return true;
    else
        return false;
    /**
     * \brief    Comparaison
     * \details  Surcharge de l'opérateur == permettant de comparer un rationnel à un réel
     * \param    d Le double à comparer
     * \return   Un bool égale à true si le Rationnel et le double sont égaux
     */
}

bool Rationnel::operator<(double d)
{
    if((_num/_den)<d)
        return true;
    else
        return false;
    /**
     * \brief    Comparaison
     * \details  Surcharge de l'opérateur < permettant de comparer un rationnel à un réel
     * \param    d Le double à comparer
     * \return   Un bool égale à true si le Rationnel est strictement inférieur au double
     */
}

Rationnel Rationnel::puissance(const Rationnel& a)
{
    double numA=this->getNum();
    double denA=this->getDen();
    double numB=a.getNum();
    double denB=a.getDen();
    Rationnel ret(pow(numA, numB/denB), pow(denA, numB/denB), this->getType());
    if (_type == rationnel)
        simplifier(ret);
    return ret;
    /**
     * \brief    Puissance
     * \details  Puissance d'un rationnel par un autre
     * \param    a Le Rationnel exposant
     * \return   Le Rationnel résultant de la puissance
     */
}





/*QString Rationnel::getFraction(double a)
{
    QString nombre = QString::number(a, 'g', 16);
    int index = nombre.indexOf(".");
    //nombre.remove(nombre.size()-2,index+1);
    //a = nombre.toDouble();
    int x;
    double den;
    if(isSequence(a,x))
        den=(pow(10,x)-1);
    else
        den=(pow(10,x));
    double num=den*a;
    do{
        QString nombre = QString::number(num, 'g', 16);
        num = nombre.toDouble();
        index = nombre.indexOf(".");
        if( index > 0){
            num = nombre.toDouble();
        }
        if( index > 0){
            num*=10;
            den*=10;
            }
       }
    while(index > 0);
    int numInt=(int)num;
    int denInt=(int)den;
    simplifier(numInt,denInt);
    QString retour(QString::number(numInt)+"/"+QString::number(denInt));
    return retour;
}

QString Rationnel::reel(double c)
{
    QString retour=getFraction(c);
    return retour;
}


bool Rationnel::isSequence(double a, int& b)
{
    QString nombre = QString::number(a, 'g', 16);

    QString seq="";
    QString tmp="";

    int index = nombre.indexOf(".");
    if( index > 0){
        nombre.remove(0,index+1);
        int j=0;
        seq+=nombre.at(0);
        for (int i(1); i<nombre.size(); i++)
        {
            if(seq==tmp && seq!="")
                i=nombre.size(); //Sortir de la boucle...
            else if(nombre.at(i)==seq.at(j))
            {
                j++;
                tmp+=nombre.at(i);
            }
            else if (j>0)
            {
                seq+=tmp;
                tmp.clear();
                j=0;
            }
            else
            {
                seq+=nombre.at(i);
            }

        }
        if(nombre.count(seq)>1){
            b=seq.size();
            return true;
        }
        else{
            QString nombre = QString::number(a, 'g', 16);
            int index = nombre.indexOf(".");
            nombre.remove((index+1),1);
            a = nombre.toDouble();
            return isSequence(a,b);
        }
    }
    b = nombre.size();
    return false;
}*/

 bool Rationnel::operator<=(double d){
     if((_num/_den)<=d)
         return true;
     else
         return false;
     /**
      * \brief    Comparaison
      * \details  Surcharge de l'opérateur <= permettant de comparer un rationnel à un réel
      * \param    d Le double à comparer
      * \return   Un bool égale à true si le Rationnel est inférieur au double
      */
 }
