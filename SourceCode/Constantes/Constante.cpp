///
/// \class     Constante
/// \author    Y.Vandecnocke & S.Ferry
/// \version   1.0
/// \date      08 Juin 2012
/// \brief     Données manipulées par la calculatrice
///
/// \details   Cette classe virtuelle pure contient les fonctions génériques de manipulation et de calcul des données de la calculatrice.
///

#include "Constante.h"

QString Constante::getValue() const{
    return this->toString();
    /**
    * \brief    Obtenir le contenu
    * \return   Un QString contenant le contenu de la Constante
    */
}
