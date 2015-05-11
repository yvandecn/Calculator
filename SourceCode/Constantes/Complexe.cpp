///
/// \class     Complexe
/// \author    Y.Vandecnocke & S.Ferry
/// \version   1.0
/// \date      08 Juin 2012
/// \brief     Gestion des nombres Complexes
///
/// \details   Cette classe, fille de la classe Constante gère la manipulation des nombres Complexes, et donc également des réels, des rationnels et des entiers.
///


#include "Complexe.h"


Complexe::Complexe(Rationnel r, Rationnel i, bool modeC ) : Constante(), _re(r), _im(i), _modeComplexe(modeC)
{/**
 * \brief    Constructeur
 * \details  Permet de créer un objet de type Complexe
 * \param    r Un Rationnel qui sera la partie réelle du Complexe
 * \param    i Un Rationnel qui sera la partie imaginaire du Complexe
 * \param    modeC Un bool déterminant l'activation du mode complexe
 */}
Complexe::Complexe(double num1, double den1, double num2, double den2, bool modeC, TypeConstante modeR) : Constante(), _re(num1,den1,modeR), _im(num2,den2,modeR), _modeComplexe(modeC)
    {/**
     * \brief    Constructeur
     * \details  Permet de créer un objet de type Complexe
     * \param    num1 Un double qui sera le numérateur de la partie réelle du Complexe
     * \param    den1 Un double qui sera le dénominateur de la partie imaginaire du Complexe
     * \param    num2 Un double qui sera le numérateur de la partie réelle du Complexe
     * \param    den2 Un double qui sera le dénominateur de la partie imaginaire du Complexe
     * \param    modeC Un bool déterminant l'activation du mode complexe
     */}

Rationnel Complexe::getIm() const{
    return _im;
    /**
    * \brief    Obtenir la partie imaginaire
    * \return   La partie imaginaire du Complexe
    */
}

Rationnel Complexe::getRe() const{
    return _re;
    /**
    * \brief    Obtenir la partie réelle
    * \return   La partie réelle du Complexe
    */
}

bool Complexe::getModeComplexe() const {
    return _modeComplexe;
    /**
    * \brief    Obtenir le mode Complexe
    * \return   Un bool, vrai si le mode est activé
    */
}

Complexe* Complexe::getConjuguer() const{
    return new Complexe(_re,_im.getOppose(),_modeComplexe);
    /**
    * \brief    Obtenir le complexe conjugué
    * \return   Le Complexe conjugué
    */
}

bool Complexe::isType(const char *t) const{
    QString s(typeid(this).name());
    return(s.contains(t));
    /**
    * \brief    Vérification du type
    * \param    t Une chaine de caractère
    * \return   Un bool, vrai si t est égal à "Complexe"
    */
}

void Complexe::setIm(Rationnel val){
    _im = val;
    /**
    * \brief    Modifier la partie imaginaire
    * \param    val Rationnel remplaçant la partie imaginaire
    */
}

void Complexe::setRe(Rationnel val){
    _re = val;
    /**
    * \brief    Modifier la partie rélle
    * \param    val Rationnel remplaçant la partie réelle
    */
}

void Complexe::setIm(double num){
    _im.setNum(num);
    _im.setDen(1);
    /**
    * \brief    Modifier la partie imaginaire
    * \param    num double remplaçant la partie imaginaire
    */
}

void Complexe::setRe(double num){
    _re.setNum(num);
    _im.setDen(1);
    /**
    * \brief    Modifier la partie réelle
    * \param    num double remplaçant la partie réelle
    */
}

QString Complexe::toString()const{
    QString t(_re.toString());
    if(_modeComplexe)
        t +=" + "+_im.toString()+"i";
    return t;

    /**
     * \brief     Transforme le Complexe en chaine de caractères
     * \return    Le Complexe sous la forme d'un QString
     */
}

QString Complexe::getValue() const{
    QString t(_re.getValue());
    if(_modeComplexe)
        t+="$"+_im.getValue();
    return t;
    /**
     * \brief    Transforme le Complexe en chaine de caractère sous la notation RE$IM
     * \return   Le Complexe noté RE$IM sous la forme d'un QString
     */
}

Constante* Complexe::operator+(Constante* c){
    if(c->isType("Expression")){
        Expression * tmp = new Expression(this->getValue());
        tmp->insert(tmp->size()," "+ c->getValue()+" +");
        return tmp;
        }
    else if(c->isType("Complexe")){
            Complexe *d = dynamic_cast<Complexe*>(c);
            Complexe *ret = new Complexe(0,0, d->_modeComplexe);
            ret->setRe(this->getRe().operator +(d->getRe()));
            ret->setIm(this->getIm().operator +(d->getIm()));
            return ret;
    }
return this;

/**
 * \brief      Somme
 * \details    Surcharge de l'opérateur + permettant de sommer un Complexe avec une Constante
 * \param    c La Constante à sommer au Complexe
 * \return   La Constante résultant de la somme
 */
}


Constante* Complexe::operator-(Constante* c){
    if(c->isType("Expression")){
        Expression * tmp = new Expression(this->getValue());
        tmp->insert(tmp->size()," "+ c->getValue()+" -");
        return tmp;
        }
    else if(c->isType("Complexe")){
            Complexe *d = dynamic_cast<Complexe*>(c);
            Complexe *ret = new Complexe(0,0, d->_modeComplexe);
            ret->setRe(this->getRe().operator-(d->getRe()));
            ret->setIm(this->getIm().operator-(d->getIm()));
            return ret;
    }
return this;

/**
 * \brief      Soustraction
 * \details    Surcharge de l'opérateur - permettant de soustraire un Complexe avec une Constante
 * \param    c La Constante à soustraire au Complexe
 * \return   La Constante résultant de la soustraction
 */
}


Constante* Complexe::operator*(Constante* c){
    if(c->isType("Expression")){
        Expression * tmp = new Expression(this->getValue());
        tmp->insert(tmp->size()," "+ c->getValue()+" -");
        return tmp;
        }
    else if(c->isType("Complexe")){
            Complexe *d = dynamic_cast<Complexe*>(c);
            Complexe *ret = new Complexe(0,0, d->_modeComplexe);
            ret->setRe(this->getRe().operator *(d->getRe()).operator -(this->getIm().operator *(d->getIm())));
            ret->setIm(this->getRe().operator *(d->getIm()).operator +(this->getIm().operator *(d->getRe())));
            return ret;
    }
return this;

/**
 * \brief      Multiplication
 * \details    Surcharge de l'opérateur * permettant de multiplier un Complexe avec une Constante
 * \param    c La Constante à multiplier au Complexe
 * \return   La Constante résultant de la multiplication
 */
}

Constante* Complexe::operator/(Constante* c){
    if(c->isType("Expression")){
        Expression * tmp = new Expression(this->getValue());
        tmp->insert(tmp->size()," "+ c->getValue()+" /");
        return tmp;
        }
    else if(c->isType("Complexe")){
            Complexe *y = dynamic_cast<Complexe*>(c);
            Complexe *ret = new Complexe(0,0, y->_modeComplexe);
            Rationnel a = this->getRe();
            Rationnel b = this->getIm();
            Rationnel c = y->getRe();
            Rationnel d = y->getIm();
            Rationnel tmp1 = (a*c+b*d);
            Rationnel tmp2 = (c*c+d*d);
            Rationnel tmp3 = tmp1/tmp2;
            Rationnel tmp4 = (a*d-b*c);
            Rationnel tmp5 = (c*c+d*d);
            Rationnel tmp6 = tmp4/tmp5;
            ret->setRe((a*c+b*d)/(c*c+d*d));
            ret->setIm(((a*d-b*c)/(c*c+d*d)).getOppose());
            return ret;

    }
return this;

/**
 * \brief      Division
 * \details    Surcharge de l'opérateur / permettant de diviser un Complexe avec une Constante
 * \param    c La Constante à diviser au Complexe
 * \return   La Constante résultant de la division
 */
}

Constante* Complexe::puissance(Constante* c){
    if(c->isType("Expression")){
        Expression * tmp = new Expression(this->getValue());
        tmp->insert(tmp->size()," "+ c->getValue()+" POW");
        return tmp;
        }
    else if(c->isType("Complexe")){

            Complexe *y = dynamic_cast<Complexe*>(c);
            Complexe *ret = new Complexe(0,0, y->_modeComplexe);
            Rationnel a = this->getRe();
            Rationnel c = y->getRe();

            ret->setRe(a.puissance(c));
            ret->setIm(0);

            return ret;

    }
return this;
/**
 * \brief      Puissance
 * \details    Puissance d'un complexe par une Constante
 * \param    c La Constante exposante au Complexe
 * \return   La Constante résultant de la puissance
 */
}

Constante* Complexe::modulo(Constante* c){
    if(c->isType("Expression")){
        Expression * tmp = new Expression(this->getValue());
        tmp->insert(tmp->size()," "+ c->getValue()+" MOD");
        return tmp;
        }
    else if(c->isType("Complexe")){

            Complexe *y = dynamic_cast<Complexe*>(c);
            Complexe *ret = new Complexe(0,0, y->_modeComplexe);
            Rationnel a = this->getRe();
            Rationnel c = y->getRe();
            int b = a.toInt();
            int d = c.toInt();
            ret->setRe(b%d);
            ret->setIm(0);

            return ret;

    }
return this;
/**
 * \brief      Modulo
 * \details    Modulo d'un Complexe par une Constante
 * \param    c La Constante modulo au Complexe
 * \return   La Constante résultant du modulo
 */
}

Constante* Complexe::sinus(){
    if(this->isType("Complexe")){
        Complexe *ret = new Complexe(0,1,0,1, this->_modeComplexe, _re.getType());
            double a = this->getRe().toDouble();
            ret->setRe(sin(a));
            return ret;
    }
return this;
/**
 * \brief      Sinus
 * \details    Fonction sinus du Complexe
 * \return   La Constante résultant du sinus
 */
}

Constante* Complexe::cosinus(){
    if(this->isType("Complexe")){
            Complexe *ret = new Complexe(0,1,0,1, this->_modeComplexe, _re.getType());
            double a = this->getRe().toDouble();
            ret->setRe(cos(a));
            return ret;
    }
return this;
/**
 * \brief      Cosinus
 * \details    Fonction cosinus du Complexe
 * \return   La Constante résultant du cosinus
 */
}

Constante* Complexe::tangente(){
    if(this->isType("Complexe")){
            Complexe *ret = new Complexe(0,1,0,1, this->_modeComplexe, _re.getType());
            double a = this->getRe().toDouble();
            ret->setRe(tan(a));
            return ret;
    }
return this;
/**
 * \brief      Tangente
 * \details    Fonction tangente du Complexe
 * \return   La Constante résultant de la tangente
 */
}

Constante* Complexe::sinush(){
    if(this->isType("Complexe")){
            Complexe *ret = new Complexe(0,1,0,1, this->_modeComplexe, _re.getType());
            double a = this->getRe().toDouble();
            ret->setRe(sinh(a));
            return ret;
    }
return this;
/**
 * \brief      Sinus hyperbolique
 * \details    Fonction sinus hyperbolique du Complexe
 * \return   La Constante résultant du sinus hyperbolique
 */
}

Constante* Complexe::cosinush(){
    if(this->isType("Complexe")){
            Complexe *ret = new Complexe(0,1,0,1, this->_modeComplexe, _re.getType());
            double a = this->getRe().toDouble();
            ret->setRe(cosh(a));
            return ret;
    }
return this;
/**
 * \brief      Cosinus hyperbolique
 * \details    Fonction cosinus hyperbolique du Complexe
 * \return   La Constante résultant du cosinus hyperbolique
 */
}

Constante* Complexe::tangenteh(){
    if(this->isType("Complexe")){
            Complexe *ret = new Complexe(0,1,0,1, this->_modeComplexe, _re.getType());
            double a = this->getRe().toDouble();
            ret->setRe(tanh(a));
            return ret;
    }
return this;
/**
 * \brief      Tangente hyperbolique
 * \details    Fonction tangente hyperbolique du Complexe
 * \return   La Constante résultant de la tangente hyperbolique
 */
}

Constante* Complexe::logarithmen(){
    if(this->isType("Complexe")){
            Complexe *ret = new Complexe(0,1,0,1, this->_modeComplexe, _re.getType());
            double a = this->getRe().toDouble();
            ret->setRe(log(a));
            return ret;
    }
return this;
/**
 * \brief      Logarithme népérien
 * \details    Fonction logarithme népéreien du Complexe
 * \return   La Constante résultant du logarithme népérien
 */
}

Constante* Complexe::logarithmed(){
    if(this->isType("Complexe")){
            Complexe *ret = new Complexe(0,1,0,1, this->_modeComplexe, _re.getType());
            double a = this->getRe().toDouble();
            ret->setRe(log10(a));
            return ret;
    }
return this;
/**
 * \brief      Logarithme décimal
 * \details    Fonction logarithme décimal du Complexe
 * \return   La Constante résultant du logarithme décimal
 */
}

Constante* Complexe::oppose(){
    if(this->isType("Complexe")){
            Complexe *ret = new Complexe(0,1,0,1, this->_modeComplexe, _re.getType());
            Rationnel a = this->getRe();
            Rationnel b = this->getIm();
            ret->setRe(a.getOppose());
            ret->setIm(b.getOppose());
            return ret;
    }
return this;
/**
 * \brief      Opposé
 * \details    Fonction opposé du Complexe
 * \return   La Constante opposée au Complexe
 */
}

Constante* Complexe::inverse(){
    if(this->isType("Complexe")){
            Complexe *ret = new Complexe(0,1,0,1, this->_modeComplexe, _re.getType());
            Rationnel a = this->getRe();
            ret->setRe(a.getInverse());
            return ret;
    }
return this;
/**
 * \brief      Inverse
 * \details    Fonction inverse du Complexe
 * \return   La Constante inverse du Complexe
 */
}

Constante* Complexe::racine(){
    if(this->isType("Complexe")){
            Complexe *ret = new Complexe(0,1,0,1, this->_modeComplexe, _re.getType());
            Rationnel a = this->getRe();
            ret->setRe(a.racine());

            return ret;
    }
return this;
/**
 * \brief      Racine carrée
 * \details    Fonction racine carrée du Complexe
 * \return   La Constante racine du Complexe
 */
}

Constante* Complexe::carre(){
    if(this->isType("Complexe")){
            Constante *ret = new Complexe(this->getRe(),this->getIm(), this->_modeComplexe);
            ret=ret->operator*(ret);
            return ret;
    }
return this;
/**
 * \brief      Carré
 * \details    Fonction carré du complexe
 * \return   La Constante carré du Complexe
 */
}

Constante* Complexe::cube(){
    if(this->isType("Complexe")){
        Constante *ret = new Complexe(this->getRe(),this->getIm(), this->_modeComplexe);
        Constante * val = new Complexe(this->getRe(),this->getIm(), this->_modeComplexe);
        ret=ret->carre();
        ret=ret->operator*(val);
        return ret;
    }
return this;
/**
 * \brief      Cube
 * \details    Fonction cube du complexe
 * \return   La Constante cube du Complexe
 */
}

Constante* Complexe::factorielle(){
    if(this->isType("Complexe")){
        Complexe *ret = new Complexe(0,0, this->_modeComplexe);
        int a=this->getRe().toInt();
        if (a<0)
            a*=-1;
        unsigned int resultat=1;
        if (a==0 || a==1)
            ret->setRe(resultat);
        else
            for(int i(1); i<=a; i++)
                resultat*=i;
        ret->setRe(resultat);
        return ret;
    }
return this;
/**
 * \brief      Factorielle
 * \details    Fonction factorielle du complexe
 * \return   La Constante factorielle du Complexe
 */
}
