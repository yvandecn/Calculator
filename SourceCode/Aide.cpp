///
/// \class     Aide
/// \author    Y.Vandecnocke & S.Ferry
/// \version   1.0
/// \date      08 Juin 2012
/// \brief     Gestion de la fenêtre d'aide
///
/// \details   Cette classe, fille de la classe QDialog, gère l'affichage de la fenêtre d'aide
///

#include "Aide.h"
#include "ui_aide.h"

Aide::Aide(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Aide)
{
    ui->setupUi(this);
    /**
     * \brief    Constructeur
     * \param    parent le QWidget parent
     */
}


void Aide::on_bOkAide_clicked()
{
    this->close();
    /**
     * \brief    Clique sur OK
     * \details  Gère l'intéraction avec le bouton OK de l'interface graphique
     */
}

Aide::~Aide()
{
    delete ui;
    /**
     * \brief    Déstructeur
     */
}
