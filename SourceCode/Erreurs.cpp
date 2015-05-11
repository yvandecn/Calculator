///
/// \class     Erreurs
/// \author    Y.Vandecnocke & S.Ferry
/// \version   1.0
/// \date      08 Juin 2012
/// \brief     Gestion des exceptions
///
/// \details   Cette classe, fille de la classe standard exception permet le traitement des Erreurs
///

#include "Erreurs.h"

Erreurs::Erreurs(int numero, string const& phrase) throw():m_numero(numero),m_phrase(phrase){}

const char* Erreurs::what() const throw(){
    return m_phrase.c_str();
}

Erreurs::~Erreurs() throw() {}
