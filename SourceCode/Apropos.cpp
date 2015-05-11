///
/// \class     Apropos
/// \author    Y.Vandecnocke & S.Ferry
/// \version   1.0
/// \date      08 Juin 2012
/// \brief     Gestion de la fenêtre d'information sur le logiciel
///
/// \details   Cette classe, fille de la classe QDialog, gère l'affichage des informations relatives au logiciel
///

#include "Apropos.h"
#include "ui_Apropos.h"

Apropos::Apropos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Apropos)
{
    ui->setupUi(this);
    /**
     * \brief    Constructeur
     * \param    parent le QWidget parent
     */
}

void Apropos::on_bOk_clicked(){
    this->close();
    /**
     * \brief    Clique sur OK
     * \details  Gère l'intéraction avec le bouton OK de l'interface graphique
     */
}

Apropos::~Apropos()
{
    delete ui;
    /**
     * \brief    Déstructeur
     */
}
