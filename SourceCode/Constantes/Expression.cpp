///
/// \class     Expression
/// \author    Y.Vandecnocke & S.Ferry
/// \version   1.0
/// \date      08 Juin 2012
/// \brief     Gestion des expressions
///
/// \details   Cette classe, fille de la classe Constante gère la manipulation des données entrées par l'utilisateur sous forme d'expression entre guillemets. Exemple : "2 2 +".
///

#include "Expression.h"


Expression::Expression(const QString& t):Constante(), _expression(t)
    {
        if(_expression.at(0)=='"')
            _expression.remove(0,1);
        if(_expression.at(_expression.length()-1)=='"')
            _expression.remove(_expression.length()-1,1);
        /**
        * \brief    Constructeur
        * \details  Permet de construire un objet de type Expression
        * \param    t Un const QString&
        */
    }

QString Expression::getExpression(bool guillemets) const {
        if (guillemets)
            return ('"'+_expression+'"');
        else
            return _expression;
        /**
         * \brief    Obtenir l'expression dans un QString
         * \param guillemet  Booléen déterminant la présence de guillemet dans la chaine de retour
         * \return   Un QString contenant l'expression
         */
}

void Expression::setExpression(const QString& t){
    _expression=t;
    /**
    * \brief    Modifier l'expression
    * \param    t const QString& remplaçant l'a partie imaginaire'expression
    */
}

QString Expression::toString() const{
    return this->getExpression(true);
    /**
     * \brief    Obtenir l'expression dans un QString avec guillemets
     * \return   Un QString contenant l'expression
     */
}

void Expression::insert(int i, const QString& s){
    _expression.insert(i,s);
    /**
     * \brief    Insérer une chaine à l'indice i
     * \param    i int indice de l'insertion
     * \param    s la chaine à insérer
     */
}

int Expression::size(){
    return _expression.size();
    /**
     * \brief    Taille de l'expression
     * \return   Un int indiquant la taille de l'expression
     */
}

QString Expression::getValue() const{
    return getExpression(false);
    /**
     * \brief    Obtenir l'expression dans un QString sans guillemets
     * \return   Un QString contenant l'expression
     */
}

Constante* Expression::operator+(Constante* c){
    Expression * tmp = new Expression(this->getValue());
    if(c->isType("Complexe")){
        tmp->insert(0,c->getValue()+" ");
        tmp->insert(tmp->size()," +");
        }
    else if(c->isType("Expression")){
        tmp->insert(tmp->size()," " + c->getValue());
        tmp->insert(tmp->size()," + ");
        }
    return tmp;
    /**
     * \brief    Somme
     * \details  Surcharge de l'opérateur + permettant de sommer une Expression avec une Constante
     * \param c  La Constante à sommer
     * \return   La Constante résultant de la somme
     */
}

Constante* Expression::operator-(Constante* c){
    Expression * tmp = new Expression(this->getValue());
    if(c->isType("Complexe")){
        tmp->insert(tmp->size()," "+c->getValue());
        tmp->insert(tmp->size()," -");
        }
    else if(c->isType("Expression")){
        tmp->insert(tmp->size()," " + c->getValue());
        tmp->insert(tmp->size()," - ");
        }
    return tmp;

    /**
     * \brief    Soustraction
     * \details  Surcharge de l'opérateur - permettant de soustraire une Expression avec une Constante
     * \param c  La Constante à soustraire
     * \return   La Constante résultant de la soustraction
     */
}

Constante* Expression::operator*(Constante* c){
    Expression * tmp = new Expression(this->getValue());
    if(c->isType("Complexe")){
        tmp->insert(0,c->getValue()+" ");
        tmp->insert(tmp->size()," *");
        }
    else if(c->isType("Expression")){
        tmp->insert(tmp->size()," " + c->getValue());
        tmp->insert(tmp->size()," * ");
        }
    return tmp;
    /**
     * \brief    Multiplication
     * \details  Surcharge de l'opérateur * permettant de multiplier une Expression avec une Constante
     * \param c  La Constante à multiplier
     * \return   La Constante résultant de la multiplication
     */
}

Constante* Expression::operator/(Constante* c){
    Expression * tmp = new Expression(this->getValue());
    if(c->isType("Complexe")){
        tmp->insert(tmp->size()," " + c->getValue());
        tmp->insert(tmp->size()," /");
        }
    else if(c->isType("Expression")){
        tmp->insert(tmp->size()," " + c->getValue());
        tmp->insert(tmp->size()," / ");
        }
    return tmp;
    /**
     * \brief    Division
     * \details  Surcharge de l'opérateur / permettant de diviser une Expression avec une Constante
     * \param c  La Constante à diviser
     * \return   La Constante résultant de la division
     */
}

Constante* Expression::puissance(Constante* c){
    Expression * tmp = new Expression(this->getValue());
    if(c->isType("Complexe")){
        tmp->insert(0,c->getValue()+" ");
        tmp->insert(tmp->size()," POW");
        }
    else if(c->isType("Expression")){
        tmp->insert(tmp->size()," " + c->getValue());
        tmp->insert(tmp->size()," POW ");
        }
    return tmp;
    /**
     * \brief    Puissance
     * \details  Fonction puissance de l'Expression par une Constante
     * \param c  La Constante exposante à l'Expression
     * \return   La Constante résultant de la puissance
     */
}

Constante* Expression::modulo(Constante* c){
    Expression * tmp = new Expression(this->getValue());
    if(c->isType("Complexe")){
        tmp->insert(0,c->getValue()+" ");
        tmp->insert(tmp->size()," MOD");
        }
    else if(c->isType("Expression")){
        tmp->insert(tmp->size()," " + c->getValue());
        tmp->insert(tmp->size()," MOD ");
        }
    return tmp;
    /**
     * \brief    Modulo
     * \details  Fonction modulo de l'Expression avec une Constante
     * \param c  La Constante modulo à l'Expression
     * \return   La Constante résultant du moduloe
     */
}

Constante* Expression::sinus(){
    Expression * tmp;
    if(this->isType("Expression"))
        tmp = new Expression(this->getValue()+" SIN");
    return tmp;
    /**
     * \brief    Sinus
     * \details  Fonction sinus de l'Expression
     * \return   La Constante résultant du sinus
     */
}

Constante* Expression::cosinus(){
    Expression * tmp;
    if(this->isType("Expression"))
        tmp = new Expression(this->getValue()+" COS");
    return tmp;
    /**
     * \brief    Cosinus
     * \details  Fonction cosinus de l'Expression
     * \return   La Constante résultant du cosinus
     */
}

Constante* Expression::tangente(){
    Expression * tmp;
    if(this->isType("Expression"))
        tmp = new Expression(this->getValue()+" TAN");
    return tmp;
    /**
     * \brief    Tangente
     * \details  Fonction tangente de l'Expression
     * \return   La Constante résultant de la tengante
     */
}

Constante* Expression::sinush(){
    Expression * tmp;
    if(this->isType("Expression"))
        tmp = new Expression(this->getValue()+" SINH");
    return tmp;
    /**
     * \brief    Sinus hyperbolique
     * \details  Fonction sinus hyperbolique de l'Expression
     * \return   La Constante résultant du sinus hyperbolique
     */
}

Constante* Expression::cosinush(){
    Expression * tmp;
    if(this->isType("Expression"))
        tmp = new Expression(this->getValue()+" COSH");
    return tmp;
    /**
     * \brief    Cosinus hyperbolique
     * \details  Fonction cosinus hyperbolique de l'Expression
     * \return   La Constante résultant du sinus
     */
}

Constante* Expression::tangenteh(){
    Expression * tmp;
    if(this->isType("Expression"))
        tmp = new Expression(this->getValue()+" TANH");
    return tmp;
    /**
     * \brief    Tangente hyperbolique
     * \details  Fonction tangente hyperbolique de l'Expression
     * \return   La Constante résultant de la tangente hyperbolique
     */
}

Constante* Expression::logarithmen(){
    Expression * tmp;
    if(this->isType("Expression"))
        tmp = new Expression(this->getValue()+" LN");
    return tmp;
    /**
     * \brief    Logarithme népérien
     * \details  Fonction logarithme népérien de l'Expression
     * \return   La Constante résultant du logarithme népérien
     */
}

Constante* Expression::logarithmed(){
    Expression * tmp;
    if(this->isType("Expression"))
        tmp = new Expression(this->getValue()+" LOG");
    return tmp;
    /**
     * \brief    Logarithme décimal
     * \details  Fonction logarithme décimal de l'Expression
     * \return   La Constante résultant du logarithme décimal
     */
}

Constante* Expression::oppose(){
    Expression * tmp;
    if(this->isType("Expression"))
        tmp = new Expression(this->getValue()+" SIGN");
    return tmp;
    /**
     * \brief    Opposé
     * \details  Fonction opposée de l'Expression
     * \return   La Constante opposée
     */
}

Constante* Expression::inverse(){
    Expression * tmp;
    if(this->isType("Expression"))
        tmp = new Expression(this->getValue()+" INV");
    return tmp;
    /**
     * \brief    Inverse
     * \details  Fonction inverse de l'Expression
     * \return   La Constante inverse
     */
}

Constante* Expression::racine(){
    Expression * tmp;
    if(this->isType("Expression"))
        tmp = new Expression(this->getValue()+" SQRT");
    return tmp;
    /**
     * \brief    Racine carrée
     * \details  Fonction racine carrée de l'Expression
     * \return   La Constante racine de l'Expression
     */
}

Constante* Expression::carre(){
    Expression * tmp;
    if(this->isType("Expression"))
        tmp = new Expression(this->getValue()+" SQR");
    return tmp;
    /**
     * \brief    Carré
     * \details  Fonction carré de l'Expression
     * \return   La Constante résultant du carré
     */
}

Constante* Expression::cube(){
     Expression * tmp;
    if(this->isType("Expression"))
       tmp = new Expression(this->getValue()+" CUBE");
    return tmp;
    /**
     * \brief    Cube
     * \details  Fonction cube de l'Expression
     * \return   La Constante résultant du cube
     */
}

Constante* Expression::factorielle(){
    Expression * tmp;
    if(this->isType("Expression"))
        tmp = new Expression(this->getValue()+" !");
    return tmp;
    /**
     * \brief    Factorielle
     * \details  Fonction factorielle de l'Expression
     * \return   La Constante résultant du factorielle
     */
}

bool Expression::isType(const char *t) const
{
    QString s(typeid(this).name());
    return(s.contains(t));
    /**
    * \brief    Vérification du type
    * \param    t Une chaine de caractère
    * \return   Un bool, vrai si t est égal à "Expression"
    */
}
