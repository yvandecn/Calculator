#ifndef ERREURS_H
#define ERREURS_H

#include <exception>
#include <string>

using namespace std;

class Erreurs : public exception
{

public:
    Erreurs(int numero=0, string const& phrase="") throw();

    virtual const char* what() const throw();

    virtual ~Erreurs() throw();

private:
    int m_numero;               // Numéro de l'erreur.
    string m_phrase;            // Description de l'erreur.
};


#endif // ERREURS_H
