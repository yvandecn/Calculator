///
/// \class     Parametres
/// \author    Y.Vandecnocke & S.Ferry
/// \version   1.0
/// \date      08 Juin 2012
/// \brief     Gestion de la fenêtre de régale des Paramètres
///
/// \details   Cette classe, fille de la classe QDialog, gère l'interface utilisateur de la fenetre de réglage des paramètres
///

#include "Parametres.h"
#include "ui_Parametres.h"
#include "mainwindow.h"

Parametres::Parametres(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Parametres)
{
    ui->setupUi(this);
    MainWindow * t= dynamic_cast<MainWindow*>(this->parent());
    QStringList historique = t->getStringPileSauvegarde();
    afficheHistorique(historique);
    /**
     * \brief    Constructeur
     * \param    parent le QWidget parent
     */

}

void Parametres::afficheHistorique(QStringList historique){
    ui->pileHistorique->clear();
    foreach(QString s, historique)
        ui->pileHistorique->addItem(s);
    /**
     * \brief    Affiche la pile courante
     * \param    historique QStringList contenant la pile actuellement affichée
     */
}

void Parametres::setParametres(int swapS,int swapE,int sum, int mean, int affichage){
    ui->spSwapStart->setValue(swapS+1);
    ui->spSwapEnd->setValue(swapE+1);
    ui->spSum->setValue(sum);
    ui->spMean->setValue(mean);
    ui->spAffichage->setValue(affichage);
    /**
     * \brief    Modifier les paramètres actuels
     * \param    swapS int remplaçant l'indice actuel
     * \param    swapE int remplaçant l'indice actuel
     * \param    sum int remplaçant le nombre
     * \param    mean int remplaçant le nombre
     * \param    affichage int remplaçant le nombre
     */
}

Parametres::~Parametres(){
    delete ui;
    /**
     * \brief    Déstructeur
     */
}

void Parametres::on_bOk_clicked(){
        MainWindow * t= dynamic_cast<MainWindow*>(this->parent());
        t->setMIndexSWAP(ui->spSwapStart->value()-1,ui->spSwapEnd->value()-1);
        t->setMSum(ui->spSum->value());
        t->setMMean(ui->spMean->value());
        t->setMAffichage(ui->spAffichage->value());
        t->affichePile();
        this->close();
        /**
         * \brief    Clique sur OK
         * \details  Gère l'intéraction avec le bouton OK de l'interface graphique
         */
}
