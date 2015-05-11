///
/// \class     mainwindow
/// \author    Y.Vandecnocke & S.Ferry
/// \version   1.0
/// \date      08 Juin 2012
/// \brief     Interface graphique utilisateur
///
/// \details   Cette classe gère les interactions de l'utilisateur avec l'interface graphique
///

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringlist>
#include <QSettings>
#include <QMessageBox>

#define FICHIER_PARAMETRES "parametre.ini"
#define FICHIER_ENTETE_PILE "pile"
#define FICHIER_EXTENSION_PILE ".ini"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),ui(new Ui::MainWindow)
    {
        ui->setupUi(this);
        connect(ui->pileAffichage->model(),SIGNAL(rowsInserted ( const QModelIndex &, int, int ) ),ui->pileAffichage,SLOT(scrollToBottom ()));
        //connect(this,SIGNAL(tabCloseRequested(int)),this,SLOT(on_Onglet_tadCloseRequested(int)));
        getAllParametres();
        getStackData();
        /**
         * \brief    Constructeur
         * \param    parent le QWidget parent
         */
    }


MainWindow::~MainWindow()
{
    delete ui;
    /**
     * \brief    Déstructeur
     */
}


bool MainWindow::isExpression(const QString& text){
    try{
    if(text == "ERREUR" || text == "")
        return false; // expression fausse
    if(text.at(0) == '"')
        if(text.at(text.length()-1) == '"')
            if(text.count('"') == 2)
                return true;

    }
    catch(std::exception const& e)
    {
        MessageErreur(e.what());
    }
    return false;
    /**
     * \brief     Vérification de l'expression
     * \details   Renvoie vrai si le QString passé en paramètre est une expression
     * \param   text Le QString à vérifier
     * \return    Un \e bool
     */
}

void MainWindow::addPileAffichage(Constante * c){
    try
    {
        ui->pileAffichage->addItem(c->toString());
    }
    catch(std::exception const& e)
    {
        MessageErreur(e.what());
    }
    /**
     * \brief     Affichage de l'élément
     * \param  c  La \e Constante à afficher
     */
}

void MainWindow::getAllParametres(){
    // chargement des parametres de la calculette
    try{
    if(!QFile::exists(FICHIER_PARAMETRES))
        QFile file(FICHIER_PARAMETRES);
    QSettings settings(FICHIER_PARAMETRES,QSettings::IniFormat,this);
    settings.beginGroup("mode");
    int nbOnglet = settings.value("nbOnglets").toInt();
    int currentOnglet = settings.value("currentOnglet").toInt();
    ui->Onglet->setCurrentIndex(settings.value("currentOnglet").toInt());
    settings.endGroup();
    for(int j = 0; j < nbOnglet; j++){
        Calculatrice* currentCalc = new Calculatrice();
        settings.beginGroup(QString::number(j));
        //Parametres de calcul (mean, sum, swap)
        currentCalc->setIndexSwap(settings.value("swaps").toInt(),settings.value("swape").toInt());
        currentCalc->setSum(settings.value("sum").toInt());
        currentCalc->setMean(settings.value("mean").toInt());
        currentCalc->setAffichage(settings.value("affichage").toInt());
        //Complexe
        currentCalc->setTypeComplexe(settings.value("complexe").toBool());
        if(j==currentOnglet){
            if(currentCalc->getTypeComplexe())
                ui->CheckComplexe->setChecked(true);
            else
                ui->CheckComplexe->setChecked(false);
            afficheBoutonComplexe(currentCalc);
            }

        //Degree
        currentCalc->setTypeDegre(settings.value("degre").toBool());
        if(j==currentOnglet){
            if(currentCalc->getTypeDegre()){
                ui->radioRadian->setChecked(true);
                }
            else{
                ui->radioDegre->setChecked(true);
                }
            }

        // Type de donnee
        if(settings.value("retour").toString() == "rationnel"){
            if(j==currentOnglet){
                ui->radioRatio->setChecked(true);
                afficheBoutonRationnel(currentCalc);
            }
            currentCalc->setTypeConstante(rationnel);
            }
        else if(settings.value("retour").toString() == "entier"){
            if(j==currentOnglet){
                ui->radioEntier->setChecked(true);
                afficheBoutonEntier(currentCalc);
            }
             currentCalc->setTypeConstante(entier);
            }
        else{
            if(j==currentOnglet){
                ui->radioReel->setChecked(true);
                afficheBoutonReel(currentCalc);
            }
            currentCalc->setTypeConstante(reel);
            }
        settings.endGroup();
        calc.push_back(currentCalc);
        if(j!=0)
            on_pushButton_clicked();
        }
    ui->Onglet->setCurrentIndex(currentOnglet);
    }
    catch(std::exception const& e)
    {
        MessageErreur(e.what());
    }
    /**
     * \brief     Chargement des paramètres
     * \details   Permet de récupérer les paramètres sauvegardés lors de la dernière session
     */
}

void MainWindow::getStackData(){
    try{
    int nbOnglet = ui->Onglet->count();
    if(calc.size() == 0)
        calc.push_back(new Calculatrice);
    for(int calcIndex = 0; calcIndex< nbOnglet; calcIndex++){
        Calculatrice* currentCalc = calc.value(calcIndex);
        QString fileName = FICHIER_ENTETE_PILE + QString::number(calcIndex) + FICHIER_EXTENSION_PILE;
        if(!QFile::exists(fileName))
            QFile file(fileName);
        QSettings settings(fileName,QSettings::IniFormat,this);
        QStringList keys = settings.childGroups();
        foreach(QString z, keys){
            settings.beginGroup(z);
            //ui->pileAffichage->addItem(z + " : " + settings.value("val").toString());
            QString a = settings.value("val").toString();
            if(isExpression(a)){
                Expression * t = new Expression(a);
                currentCalc->push(t);
            }
            else{
                double im_num = 0;
                double re_num = 0;
                double im_den = 1;
                double re_den = 1;
                QStringList list2 = a.split("$");
                QStringList list3 = list2.at(0).split("/");
                re_num = list3.at(0).toDouble();
                if(list3.count() > 1)
                    re_den = list3.at(1).toDouble();
                if(list2.count()> 1){
                    QStringList list4 = list2.at(1).split("/");
                    im_num = list4.at(0).toDouble();
                    if(list4.count() > 1)
                        im_den = list4.at(1).toDouble();
                }
                Complexe * c = new Complexe(re_num,re_den,im_num,im_den,currentCalc->getTypeComplexe(),currentCalc->getTypeConstante());
                currentCalc->push(c);
            }
        settings.endGroup();
        }
     }
    if(calc.size() == 0)
        calc.push_back(new Calculatrice);
     affichePile();
    }
    catch(std::exception const& e)
    {
        MessageErreur(e.what());
    }
ui->pileAffichage->scrollToBottom();
/**
 * \brief     Chargement des valeurs
 * \details   Permet de charger les piles de la calculatrices sauvegardées lors de la dernière session
 */
}

void MainWindow::setMIndexSWAP(int a,int b){
    try{
    int calcIndex = ui->Onglet->currentIndex();
    Calculatrice* currentCalc = calc.value(calcIndex) ;
    QSettings settings(FICHIER_PARAMETRES,QSettings::IniFormat,this);
    QStringList list = settings.allKeys();
    settings.beginGroup(QString::number(calcIndex));
    QStringList list2  = settings.childGroups();
    settings.setValue("swaps",a);
    settings.setValue("swape",b);
    settings.endGroup();
    currentCalc->setIndexSwap(a,b);
    }
    catch(std::exception const& e)
    {
        MessageErreur(e.what());
    }
    /**
     * \brief    Modifier les index de swap
     * \param    swapS int remplaçant l'indice actuel
     * \param    swapE int remplaçant l'indice actuel
     */
}

void MainWindow::setMSum(int a){
    try{
    int calcIndex = ui->Onglet->currentIndex();
    Calculatrice* currentCalc = calc.value(calcIndex) ;
    currentCalc->setSum(a);
    QSettings settings(FICHIER_PARAMETRES,QSettings::IniFormat,this);
    settings.beginGroup(QString::number(calcIndex));
    settings.setValue("sum",a);
    settings.endGroup();
    }
    catch(std::exception const& e)
    {
        MessageErreur(e.what());
    }
    /**
     * \brief    Modifier le nombre d'éléments à sommer
     * \param    swapS int remplaçant le nombre actuel
     */
}

void MainWindow::setMMean(int a){
    try{
    int calcIndex = ui->Onglet->currentIndex();
    Calculatrice* currentCalc = calc.value(calcIndex) ;
    currentCalc->setMean(a);
    QSettings settings(FICHIER_PARAMETRES,QSettings::IniFormat,this);
    settings.beginGroup(QString::number(calcIndex));
    settings.setValue("mean",a);
    settings.endGroup();
    }
    catch(std::exception const& e)
    {
        MessageErreur(e.what());
    }
    /**
     * \brief    Modifier le nombre d'éléments à moyenner
     * \param    swapS int remplaçant le nombre actuel
     */
}

void MainWindow::setMAffichage(int a){
    try{
    int calcIndex = ui->Onglet->currentIndex();
    Calculatrice* currentCalc = calc.value(calcIndex) ;
    currentCalc->setAffichage(a);
    QSettings settings(FICHIER_PARAMETRES,QSettings::IniFormat,this);
    settings.beginGroup(QString::number(calcIndex));
    settings.setValue("affichage",a);
    settings.endGroup();
    }
    catch(std::exception const& e)
    {
        MessageErreur(e.what());
    }
    /**
     * \brief    Modifier le nombre d'éléments à afficher
     * \param    swapS int remplaçant le nombre actuel
     */
}

void MainWindow::on_menuParametre_triggered(){
    try{
    Calculatrice* currentCalc = calc.value(ui->Onglet->currentIndex()) ;
    this->parametres = new Parametres(this);
    parametres->setParametres(currentCalc->getSwapStart(),currentCalc->getSwapEnd(),currentCalc->getSum(),currentCalc->getMean(), currentCalc->getAffichage());
    parametres->exec();
    parametres->close();
    delete parametres;
    }
    catch(std::exception const& e)
    {
        MessageErreur(e.what());
    }
    /**
     * \brief    Intéraction avec le bouton Paramètres du menu
     * \details  Ouverture de la fenêtre des paramètres
     */
}


void MainWindow::on_b1_clicked()
{
    QString t = ui->expression->text();
    if( t == "ERREUR" )
        ui->expression->setText("");
    ui->expression->setText(ui->expression->text() + "1");
    /**
     * \brief    Intéraction avec le bouton 1
     * \details  Ajoute 1 dans la zone de saisie
     */

}
void MainWindow::on_b2_clicked()
{
    QString t = ui->expression->text();
    if( t == "ERREUR" )
        ui->expression->setText("");
    ui->expression->setText(ui->expression->text() + "2");
    /**
     * \brief    Intéraction avec le bouton 2
     * \details  Ajoute 2 dans la zone de saisie
     */
}
void MainWindow::on_b3_clicked()
{
    QString t = ui->expression->text();
    if( t == "ERREUR" )
        ui->expression->setText("");
    ui->expression->setText(ui->expression->text() + "3");
    /**
     * \brief    Intéraction avec le bouton 3
     * \details  Ajoute 3 dans la zone de saisie
     */
}
void MainWindow::on_b4_clicked()
{
    QString t = ui->expression->text();
    if( t == "ERREUR" )
        ui->expression->setText("");
    ui->expression->setText(ui->expression->text() + "4");
    /**
     * \brief    Intéraction avec le bouton 4
     * \details  Ajoute 4 dans la zone de saisie
     */
}
void MainWindow::on_b5_clicked()
{
    QString t = ui->expression->text();
    if( t == "ERREUR" )
        ui->expression->setText("");
    ui->expression->setText(ui->expression->text() + "5");
    /**
     * \brief    Intéraction avec le bouton 5
     * \details  Ajoute 5 dans la zone de saisie
     */
}
void MainWindow::on_b6_clicked()
{
    QString t = ui->expression->text();
    if( t == "ERREUR" )
        ui->expression->setText("");
    ui->expression->setText(ui->expression->text() + "6");
    /**
     * \brief    Intéraction avec le bouton 6
     * \details  Ajoute 6 dans la zone de saisie
     */
}
void MainWindow::on_b7_clicked()
{
    QString t = ui->expression->text();
    if( t == "ERREUR" )
        ui->expression->setText("");
    ui->expression->setText(ui->expression->text() + "7");
    /**
     * \brief    Intéraction avec le bouton 7
     * \details  Ajoute 7 dans la zone de saisie
     */
}
void MainWindow::on_b8_clicked()
{
    QString t = ui->expression->text();
    if( t == "ERREUR" )
        ui->expression->setText("");
    ui->expression->setText(ui->expression->text() + "8");
    /**
     * \brief    Intéraction avec le bouton 8
     * \details  Ajoute 8 dans la zone de saisie
     */
}
void MainWindow::on_b9_clicked()
{
    QString t = ui->expression->text();
    if( t == "ERREUR" )
        ui->expression->setText("");
    ui->expression->setText(ui->expression->text() + "9");
    /**
     * \brief    Intéraction avec le bouton 9
     * \details  Ajoute 9 dans la zone de saisie
     */
}
void MainWindow::on_b0_clicked()
{
    QString t = ui->expression->text();
    if( t == "ERREUR" )
        ui->expression->setText("");
    ui->expression->setText(ui->expression->text() + "0");
    /**
     * \brief    Intéraction avec le bouton 0
     * \details  Ajoute 0 dans la zone de saisie
     */
}

void MainWindow::on_b_plus_clicked()
{
    QString t = ui->expression->text();
    if( t == "ERREUR" )
        ui->expression->setText("");
    ui->expression->setText(ui->expression->text() + "+");
    /**
     * \brief    Intéraction avec le bouton +
     * \details  Ajoute + dans la zone de saisie
     */
}
void MainWindow::on_b_moins_clicked()
{
    QString t = ui->expression->text();
    if( t == "ERREUR" )
        ui->expression->setText("");
    ui->expression->setText(ui->expression->text() + "-");
    /**
     * \brief    Intéraction avec le bouton -
     * \details  Ajoute - dans la zone de saisie
     */
}
void MainWindow::on_b_fois_clicked()
{
    QString t = ui->expression->text();
    if( t == "ERREUR" )
        ui->expression->setText("");
    ui->expression->setText(ui->expression->text() + "*");
    /**
     * \brief    Intéraction avec le bouton *
     * \details  Ajoute * dans la zone de saisie
     */
}
void MainWindow::on_b_div_clicked()
{
    QString t = ui->expression->text();
    if( t == "ERREUR" )
        ui->expression->setText("");
    ui->expression->setText(ui->expression->text() + "/");
    /**
     * \brief    Intéraction avec le bouton /
     * \details  Ajoute / dans la zone de saisie
     */
}

void MainWindow::on_b_espace_clicked()
{
    QString t = ui->expression->text();
    if( t == "ERREUR" )
        ui->expression->setText("");
    ui->expression->setText(ui->expression->text() + " ");
    /**
     * \brief    Intéraction avec le bouton _
     * \details  Ajoute _ dans la zone de saisie
     */
}

void MainWindow::on_bPow_clicked()
{
    QString t = ui->expression->text();
    if( t == "ERREUR" )
        ui->expression->setText("");
    ui->expression->setText(ui->expression->text() + "POW");
    /**
     * \brief    Intéraction avec le bouton POW
     * \details  Ajoute POW dans la zone de saisie
     */
}

void MainWindow::on_bSqr_clicked()
{
    QString t = ui->expression->text();
    if( t == "ERREUR" )
        ui->expression->setText("");
    ui->expression->setText(ui->expression->text() + "SQR");
    /**
     * \brief    Intéraction avec le bouton SQR
     * \details  Ajoute SQR dans la zone de saisie
     */
}

void MainWindow::on_bSqrt_clicked()
{
    QString t = ui->expression->text();
    if( t == "ERREUR" )
        ui->expression->setText("");
    ui->expression->setText(ui->expression->text() + "SQRT");
    /**
     * \brief    Intéraction avec le bouton SQRT
     * \details  Ajoute SQRT dans la zone de saisie
     */
}

void MainWindow::on_bCube_clicked()
{
    QString t = ui->expression->text();
    if( t == "ERREUR" )
        ui->expression->setText("");
    ui->expression->setText(ui->expression->text() + "CUBE");
    /**
     * \brief    Intéraction avec le bouton CUBE
     * \details  Ajoute CUBE dans la zone de saisie
     */
}

void MainWindow::on_bMod_clicked()
{
    QString t = ui->expression->text();
    if( t == "ERREUR" )
        ui->expression->setText("");
    ui->expression->setText(ui->expression->text() + "MOD");
    /**
     * \brief    Intéraction avec le bouton MOD
     * \details  Ajoute MOD dans la zone de saisie
     */
}

void MainWindow::on_bSin_clicked()
{
    QString t = ui->expression->text();
    if( t == "ERREUR" )
        ui->expression->setText("");
    ui->expression->setText(ui->expression->text() + "SIN");
    /**
     * \brief    Intéraction avec le bouton SIN
     * \details  Ajoute SIN dans la zone de saisie
     */
}

void MainWindow::on_bCos_clicked()
{
    QString t = ui->expression->text();
    if( t == "ERREUR" )
        ui->expression->setText("");
    ui->expression->setText(ui->expression->text() + "COS");
    /**
     * \brief    Intéraction avec le bouton COS
     * \details  Ajoute COS dans la zone de saisie
     */
}

void MainWindow::on_bTan_clicked()
{
    QString t = ui->expression->text();
    if( t == "ERREUR" )
        ui->expression->setText("");
    ui->expression->setText(ui->expression->text() + "TAN");
    /**
     * \brief    Intéraction avec le bouton TAN
     * \details  Ajoute TAN dans la zone de saisie
     */
}

void MainWindow::on_bSinh_clicked()
{
    QString t = ui->expression->text();
    if( t == "ERREUR" )
        ui->expression->setText("");
    ui->expression->setText(ui->expression->text() + "SINH");
    /**
     * \brief    Intéraction avec le bouton SINH
     * \details  Ajoute SINH dans la zone de saisie
     */
}

void MainWindow::on_bCosh_clicked()
{
    QString t = ui->expression->text();
    if( t == "ERREUR" )
        ui->expression->setText("");
    ui->expression->setText(ui->expression->text() + "COSH");
    /**
     * \brief    Intéraction avec le bouton COSH
     * \details  Ajoute COSH dans la zone de saisie
     */
}

void MainWindow::on_bTanh_clicked()
{
    QString t = ui->expression->text();
    if( t == "ERREUR" )
        ui->expression->setText("");
    ui->expression->setText(ui->expression->text() + "TANH");
    /**
     * \brief    Intéraction avec le bouton TANH
     * \details  Ajoute TANH dans la zone de saisie
     */
}

void MainWindow::on_bLn_clicked()
{
    QString t = ui->expression->text();
    if( t == "ERREUR" )
        ui->expression->setText("");
    ui->expression->setText(ui->expression->text() + "LN");
    /**
     * \brief    Intéraction avec le bouton LN
     * \details  Ajoute LN dans la zone de saisie
     */
}

void MainWindow::on_bLog_clicked()
{
    QString t = ui->expression->text();
    if( t == "ERREUR" )
        ui->expression->setText("");
    ui->expression->setText(ui->expression->text() + "LOG");
    /**
     * \brief    Intéraction avec le bouton LOG
     * \details  Ajoute LOG dans la zone de saisie
     */
}

void MainWindow::on_bInv_clicked()
{
    QString t = ui->expression->text();
    if( t == "ERREUR" )
        ui->expression->setText("");
    ui->expression->setText(ui->expression->text() + "INV");
    /**
     * \brief    Intéraction avec le bouton INV
     * \details  Ajoute INV dans la zone de saisie
     */
}

void MainWindow::on_bSign_clicked()
{
    QString t = ui->expression->text();
    if( t == "ERREUR" )
        ui->expression->setText("");
    ui->expression->setText(ui->expression->text() + "SIGN");
    /**
     * \brief    Intéraction avec le bouton SIGN
     * \details  Ajoute SIGN dans la zone de saisie
     */
}

void MainWindow::on_bFact_clicked()
{
    QString t = ui->expression->text();
    if( t == "ERREUR" )
        ui->expression->setText("");
    ui->expression->setText(ui->expression->text() + "!");
    /**
     * \brief    Intéraction avec le bouton !
     * \details  Ajoute ! dans la zone de saisie
     */
}

void MainWindow::on_bEmpty_clicked()
{
    ui->expression->setText("");
    /**
     * \brief    Intéraction avec le bouton EMPTY
     * \details  Vide la zone de saisie
     */
}


bool MainWindow::verifExpression(const QString& text){
    Calculatrice* currentCalc = calc.value(ui->Onglet->currentIndex()) ;
    if(text.count('"')%2) // Sil il y a un nombre impaire de "
        return false;
    if(text.count('"') == text.count())
        return false;
    QStringList listCharPossible;
    QStringList listStringPossible;
    listCharPossible.push_back("0");
    listCharPossible.push_back("1");
    listCharPossible.push_back("2");
    listCharPossible.push_back("3");
    listCharPossible.push_back("4");
    listCharPossible.push_back("5");
    listCharPossible.push_back("6");
    listCharPossible.push_back("7");
    listCharPossible.push_back("8");
    listCharPossible.push_back("9");
    listCharPossible.push_back("+");
    listCharPossible.push_back("-");
    listCharPossible.push_back("/");
    listCharPossible.push_back("*");
    if (currentCalc->getTypeComplexe())
        listCharPossible.push_back("$");
    else if(text.count("$")>0)
        throw Erreurs(9,"Mode complexe désactivé");
    listCharPossible.push_back(",");
    listCharPossible.push_back(".");
    listStringPossible.push_back("SQR");
    listStringPossible.push_back("SQRT");
    listStringPossible.push_back("POW");
    listStringPossible.push_back("MOD");
    listStringPossible.push_back("SIN");
    listStringPossible.push_back("COS");
    listStringPossible.push_back("TAN");
    listStringPossible.push_back("SINH");
    listStringPossible.push_back("COSH");
    listStringPossible.push_back("TANH");
    listStringPossible.push_back("LN");
    listStringPossible.push_back("LOG");
    listStringPossible.push_back("SIGN");
    listStringPossible.push_back("INV");
    listStringPossible.push_back("CUBE");
    listStringPossible.push_back("!");
    bool espace = false;
    for(int i = 0; i < text.count(); i++){ // test des espaces consecutifs
        if(text.at(i)== ' '){
            if(espace)
                return false;
            espace = true;
            }
        else
            espace = false;
    }
    QStringList t = split(text);
    foreach(QString s, t){
        if( s == "")
            return false;
        if(!isExpression(s))
        {
            bool ret=true;
            foreach(QChar z, s)
                if(!listCharPossible.contains(z))
                    ret = false;
            if(!listStringPossible.contains(s) && !ret)
                return false;
        }
        }
    if(text == "ERREUR" || text == "")
        return false;
    return true;
    /**
     * \brief     Vérification de la syntaxe
     * \details   Renvoie vrai si le QString passé en paramètre est syntaxiquement correct
     * \param   text Le QString à vérifier
     * \return    Un \e bool
     */
}

void MainWindow::addSauvegardeBinaire(Constante * c){
    int calcIndex = ui->Onglet->currentIndex();
    QString fileName = FICHIER_ENTETE_PILE + QString::number(calcIndex) + FICHIER_EXTENSION_PILE;
    QSettings settings(fileName,QSettings::IniFormat,this);
    settings.remove(QString::number(settings.childGroups().count()-1));
    addSauvegardeUnaire(c);
    /**
     * \brief   Sauvegarder l'élément
     * \param   c Constante* à sauvegarder dans le fichier
     */
}

void MainWindow::addSauvegardeUnaire(Constante * c){
    int calcIndex = ui->Onglet->currentIndex();
    QString fileName = FICHIER_ENTETE_PILE + QString::number(calcIndex) + FICHIER_EXTENSION_PILE;
    QSettings settings(fileName,QSettings::IniFormat,this);
    settings.remove(QString::number(settings.childGroups().count()-1));
    addSauvegarde(c);
    /**
     * \brief   Sauvegarder l'élément
     * \param   c Constante* à sauvegarder dans le fichier
     */
}

void MainWindow::addSauvegarde(Constante * c){
    int calcIndex = ui->Onglet->currentIndex();
    QString fileName = FICHIER_ENTETE_PILE + QString::number(calcIndex) + FICHIER_EXTENSION_PILE;
    QSettings settings(fileName,QSettings::IniFormat,this);
    settings.beginWriteArray(QString::number(settings.childGroups().count()));
    if(c->isType("Complexe") || c->isType("Rationnel"))
         settings.setValue("val",c->getValue());
    else
        settings.setValue("val",c->toString());
    /**
     * \brief   Sauvegarder l'élément
     * \param   c Constante* à sauvegarder dans le fichier
     */

}

void MainWindow::delLastElement(int i){
    int calcIndex = ui->Onglet->currentIndex();
    QString fileName = FICHIER_ENTETE_PILE + QString::number(calcIndex) + FICHIER_EXTENSION_PILE;
    QSettings settings(fileName,QSettings::IniFormat,this);
    int nbElements = settings.childGroups().count();
    for(int j = 0; j < i; j++){
        settings.remove(QString::number(nbElements-j)); // supprime dans le fichier
    //currentCalc->pop(); // supprime dans la pile
        delete ui->pileAffichage->takeItem(ui->pileAffichage->count()-1); // supprime a l'affichage
    }
    /**
     * \brief   Supprimer l'élément i de l'affichage et du fichier
     * \param   i int indice
     */

}


void MainWindow::affichePile(){
    try{
    Calculatrice* currentCalc = calc.value(ui->Onglet->currentIndex()) ;
    ui->pileAffichage->clear();
    int i = currentCalc->countPileElement()-currentCalc->getAffichage();
    if (i<0)
        i=0;
    for(int j=i; j<currentCalc->countPileElement(); j++)
        addPileAffichage(currentCalc->at(j));
    }
    catch(std::exception const& e)
    {
        MessageErreur(e.what());
    }
    /**
     * \brief     Affichage de la pile de calcul
     */
}

QStringList MainWindow::getStringPileSauvegarde() const{
    Calculatrice* currentCalc = calc.value(ui->Onglet->currentIndex()) ;
    return currentCalc->getPileSauvegardeToString();
    /**
     * \brief     Obtention de l'historique
     * \details   L'historique est renvoyé sous forme de liste
     * \return    L'historique dans une QStringList
     */
}



void MainWindow::affichePileBinaire(Constante * c){
    try{
    int calcIndex = ui->Onglet->currentIndex();
    QString fileName = FICHIER_ENTETE_PILE + QString::number(calcIndex) + FICHIER_EXTENSION_PILE;
    QSettings settings(fileName,QSettings::IniFormat,this);
    settings.remove(QString::number(ui->pileAffichage->count()-1));
    settings.remove(QString::number(ui->pileAffichage->count()-2));
    settings.beginWriteArray(QString::number(ui->pileAffichage->count()-2));
    if(c->isType("Complexe") || c->isType("Rationnel"))
         settings.setValue("val",c->getValue());
    else
        settings.setValue("val",c->toString());

    delete ui->pileAffichage->takeItem(ui->pileAffichage->count()-1);
    delete ui->pileAffichage->takeItem(ui->pileAffichage->count()-1);

     addPileAffichage(c);
    }
    catch(std::exception const& e)
    {
        MessageErreur(e.what());
    }
    /**
     * \brief     Affichage de la pile de calcul
     */
}

void MainWindow::affichePileUnaire(Constante * c){
    try
    {
    int calcIndex = ui->Onglet->currentIndex();
    QString fileName = FICHIER_ENTETE_PILE + QString::number(calcIndex) + FICHIER_EXTENSION_PILE;
    QSettings settings(fileName,QSettings::IniFormat,this);
    settings.remove(QString::number(ui->pileAffichage->count()-1));
    settings.beginWriteArray(QString::number(ui->pileAffichage->count()-1));
    if(c->isType("Complexe") || c->isType("Rationnel"))
         settings.setValue("val",c->getValue());
    else
        settings.setValue("val",c->toString());

    delete ui->pileAffichage->takeItem(ui->pileAffichage->count()-1);
     addPileAffichage(c);
    }
    catch(std::exception const& e)
    {
        MessageErreur(e.what());
    }
    /**
     * \brief     Affichage de la pile de calcul
     */
}

QStringList MainWindow::split(const QString& text){
    QStringList list;
    try{
        if(text.count('"') == 0)
            return text.split(" ");
        else if(!isExpression(text)){
            list = text.split(" ");
            int i = 0;
            QStringList ret;
            bool inExpression = false;
            foreach(QString c, list){
                if( c.at(0)  == '"' || c.at(c.length()-1) == '"'){
                    if(!inExpression){
                        ret.push_back(c);
                        }
                    inExpression = !inExpression;
                    if(!inExpression){
                        QString t = ret.at(i);
                        ret.pop_back();
                        ret.push_back(t + " " + c);
                        i++;
                        }
                    }
                else if(inExpression){
                    // si on est en train de lire une expression d'expression
                    QString t = ret.at(i);
                    ret.pop_back();
                    ret.push_back(t + " " + c);
                    }
                else if(!inExpression){
                    ret.push_back(c);
                    i++;
                    }
                }
            return ret;
            }
    QStringList t;
    t.push_back(text);
    return t;
       }
    catch(std::exception const& e)
    {
        MessageErreur(e.what());
    }
    /**
     * \brief     Séparation des éléments du texte pour traitement
     * \param   text Le QString à découper
     * \return    Une QStringList comprenant chaque élément de text
     */
return list;
}

void MainWindow::textToComplexePush(const QString& text){
    try{
    Calculatrice* currentCalc = calc.value(ui->Onglet->currentIndex()) ;
    if(!isExpression(text)){
           QStringList list = this->split(text);
           bool modeComplexe = false;
           double im_num = 0;
           double re_num = 0;
           double im_den = 1;
           double re_den = 1;
           int indexList = 0;
           foreach(QString c, list){
               indexList++;
               if(isExpression(c)){
                   Expression * e = new Expression(c);
                   currentCalc->push(e);
                   //if(indexList == list.count()) // Si dernier element de la liste
                   //    currentCalc->pushHistorique(new Expression("="));
                   addSauvegarde(e);
               }
               else{
                   if(c != ""){
                       //Somme
                       if( c == "+"){
                           Constante * c = currentCalc->sum();
                           //if(indexList == list.count()) // Si dernier element de la liste
                           //    currentCalc->pushHistorique(new Expression("="));
                           currentCalc->push(c);
                           currentCalc->operationBinaire();
                           delLastElement(2);
                           this->affichePile();
                           addSauvegardeBinaire(c);
                           }

                       //Soustraction
                       else if( c == "-" && c.length() == 1){
                           Constante * c = currentCalc->minus();
                           //if(indexList == list.count()) // Si dernier element de la liste
                           //    currentCalc->pushHistorique(new Expression("="));
                           currentCalc->push(c);
                           currentCalc->operationBinaire();
                           delLastElement(2);
                           this->affichePile();
                           addSauvegardeBinaire(c);
                           }

                       //Multiplication
                       else if( c == "*"){
                           Constante * c = currentCalc->multiply();
                           //if(indexList == list.count()) // Si dernier element de la liste
                           //    currentCalc->pushHistorique(new Expression("="));
                           currentCalc->push(c);
                           currentCalc->operationBinaire();
                           delLastElement(2);
                           this->affichePile();
                           addSauvegardeBinaire(c);
                           }

                       //Division
                       else if( c == "/"){
                           Constante * c = currentCalc->div();
                           //if(indexList == list.count()) // Si dernier element de la liste
                           //    currentCalc->pushHistorique(new Expression("="));
                           currentCalc->push(c);
                           currentCalc->operationBinaire();
                           delLastElement(2);
                           this->affichePile();
                           addSauvegardeBinaire(c);
                           }

                       //Puissance
                       else if( c == "POW"){
                           if(currentCalc->getTypeComplexe()==true)
                               throw Erreurs(5,"Opération non autoriséee dans ce mode");
                           else
                           {
                               Constante * c = currentCalc->puiss();
                               //if(indexList == list.count()) // Si dernier element de la liste
                               //    currentCalc->pushHistorique(new Expression("="));
                               currentCalc->push(c);
                               currentCalc->operationBinaire();
                               delLastElement(2);
                               this->affichePile();
                               addSauvegardeBinaire(c);
                           }
                       }

                       //Modulo
                       else if( c == "MOD"){
                           if(currentCalc->getTypeComplexe()==true || currentCalc->getTypeConstante()!=entier)
                               throw Erreurs(5,"Opération non autoriséee dans ce mode");
                           else
                           {
                               Constante * c = currentCalc->modul();
                               //if(indexList == list.count()) // Si dernier element de la liste
                               //    currentCalc->pushHistorique(new Expression("="));
                               currentCalc->push(c);
                               currentCalc->operationBinaire();
                               delLastElement(2);
                               this->affichePile();
                               addSauvegardeBinaire(c);
                           }
                       }
                           
                       //Sinus
                       else if( c == "SIN"){
                           if(currentCalc->getTypeComplexe()==true || currentCalc->getTypeConstante()==entier)
                               throw Erreurs(5,"Opération non autoriséee dans ce mode");
                           else
                           {
                               Constante * c = currentCalc->sinu();
                               //if(indexList == list.count()) // Si dernier element de la liste
                               //    currentCalc->pushHistorique(new Expression("="));
                               currentCalc->push(c);
                               currentCalc->operationUnaire();
                               delLastElement(1);
                               this->affichePile();
                               addSauvegardeUnaire(c);
                           }
                           }

                       //Cosinus
                       else if( c == "COS"){
                           if(currentCalc->getTypeComplexe()==true || currentCalc->getTypeConstante()==entier)
                                throw Erreurs(5,"Opération non autoriséee dans ce mode");
                           else
                           {
                               Constante * c = currentCalc->cosin();
                               //if(indexList == list.count()) // Si dernier element de la liste
                               //    currentCalc->pushHistorique(new Expression("="));
                               currentCalc->push(c);
                               currentCalc->operationUnaire();
                               delLastElement(1);
                               this->affichePile();
                               addSauvegardeUnaire(c);
                           }
                           }

                       //Tangente
                       else if( c == "TAN"){
                           if(currentCalc->getTypeComplexe()==true || currentCalc->getTypeConstante()==entier)
                               throw Erreurs(5,"Opération non autoriséee dans ce mode");
                           else
                           {
                               Constante * c = currentCalc->tang();
                               //if(indexList == list.count()) // Si dernier element de la liste
                               //    currentCalc->pushHistorique(new Expression("="));
                               currentCalc->push(c);
                               currentCalc->operationUnaire();
                               delLastElement(1);
                               this->affichePile();
                               addSauvegardeUnaire(c);
                           }
                           }

                       //SinusHyperbolique
                       else if( c == "SINH"){
                           if(currentCalc->getTypeComplexe()==true || currentCalc->getTypeConstante()==entier)
                               throw Erreurs(5,"Opération non autoriséee dans ce mode");
                           else
                           {
                               Constante * c = currentCalc->sinuh();
                               //if(indexList == list.count()) // Si dernier element de la liste
                               //    currentCalc->pushHistorique(new Expression("="));
                               currentCalc->push(c);
                               currentCalc->operationUnaire();
                               delLastElement(1);
                               this->affichePile();
                               addSauvegardeUnaire(c);
                           }
                           }

                       //CosinusHyperbolique
                       else if( c == "COSH"){
                           if(currentCalc->getTypeComplexe()==true || currentCalc->getTypeConstante()==entier)
                               throw Erreurs(5,"Opération non autoriséee dans ce mode");
                           else
                           {
                               Constante * c = currentCalc->cosinh();
                               //if(indexList == list.count()) // Si dernier element de la liste
                               //    currentCalc->pushHistorique(new Expression("="));
                               currentCalc->push(c);
                               currentCalc->operationUnaire();
                               delLastElement(1);
                               this->affichePile();
                               addSauvegardeUnaire(c);
                           }
                           }

                       //TangenteHyperbolique
                       else if( c == "TANH"){
                           if(currentCalc->getTypeComplexe()==true || currentCalc->getTypeConstante()==entier)
                               throw Erreurs(5,"Opération non autoriséee dans ce mode");
                           else
                           {
                               Constante * c = currentCalc->tangh();
                               //if(indexList == list.count()) // Si dernier element de la liste
                               //    currentCalc->pushHistorique(new Expression("="));
                               currentCalc->push(c);
                               currentCalc->operationUnaire();
                               delLastElement(1);
                               this->affichePile();
                               addSauvegardeUnaire(c);
                           }
                           }

                       //Logarithme Népérien
                       else if( c == "LN"){
                           if(currentCalc->getTypeComplexe()==true || currentCalc->getTypeConstante()==entier)
                               throw Erreurs(5,"Opération non autoriséee dans ce mode");
                           else
                           {
                               Constante * c = currentCalc->logn();
                               //if(indexList == list.count()) // Si dernier element de la liste
                               //    currentCalc->pushHistorique(new Expression("="));
                               currentCalc->push(c);
                               currentCalc->operationUnaire();
                               delLastElement(1);
                               this->affichePile();
                               addSauvegardeUnaire(c);
                           }
                           }

                       //Logarithme Décimal
                       else if( c == "LOG"){
                           if(currentCalc->getTypeComplexe()==true || currentCalc->getTypeConstante()==entier)
                               throw Erreurs(5,"Opération non autoriséee dans ce mode");
                           else
                           {
                               Constante * c = currentCalc->logd();
                               //if(indexList == list.count()) // Si dernier element de la liste
                               //    currentCalc->pushHistorique(new Expression("="));
                               currentCalc->push(c);
                               currentCalc->operationUnaire();
                               delLastElement(1);
                               this->affichePile();
                               addSauvegardeUnaire(c);
                           }
                           }

                       //Opposé
                       else if( c == "SIGN"){
                           Constante * c = currentCalc->signe();
                           //if(indexList == list.count()) // Si dernier element de la liste
                           //    currentCalc->pushHistorique(new Expression("="));
                           currentCalc->push(c);
                           currentCalc->operationUnaire();
                           delLastElement(1);
                           this->affichePile();
                           addSauvegardeUnaire(c);
                       }

                       //Inverse
                       else if( c == "INV"){
                           if(currentCalc->getTypeComplexe()==true || currentCalc->getTypeConstante()==entier)
                               throw Erreurs(5,"Opération non autoriséee dans ce mode");
                           else
                           {
                               Constante * c = currentCalc->inv();
                               //if(indexList == list.count()) // Si dernier element de la liste
                               //    currentCalc->pushHistorique(new Expression("="));
                               currentCalc->push(c);
                               currentCalc->operationUnaire();
                               delLastElement(1);
                               this->affichePile();
                               addSauvegardeUnaire(c);
                           }
                           }

                       //Inverse
                       else if( c == "SQRT"){
                           if(currentCalc->getTypeComplexe()==true)
                               throw Erreurs(5,"Opération non autoriséee dans ce mode");
                           else
                           {
                               Constante * c = currentCalc->racinecarre();
                               currentCalc->push(c);
                               currentCalc->operationUnaire();
                               delLastElement(1);
                               //if(indexList == list.count()) // Si dernier element de la liste
                               //    currentCalc->pushHistorique(new Expression("="));
                               this->affichePile();
                               addSauvegardeUnaire(c);
                           }
                           }

                       //Inverse
                       else if( c == "SQR"){
                           Constante * c = currentCalc->sqr();
                           //if(indexList == list.count()) // Si dernier element de la liste
                           //    currentCalc->pushHistorique(new Expression("="));
                           currentCalc->push(c);
                           currentCalc->operationUnaire();
                           delLastElement(1);
                           this->affichePile();
                           addSauvegardeUnaire(c);
                           }

                       //Inverse
                       else if( c == "CUBE"){
                           Constante * c = currentCalc->puissancetrois();
                           //if(indexList == list.count()) // Si dernier element de la liste
                           //    currentCalc->pushHistorique(new Expression("="));
                           currentCalc->push(c);
                           currentCalc->operationUnaire();
                           delLastElement(1);
                           this->affichePile();
                           addSauvegardeUnaire(c);
                           }

                       //Factorielle
                       else if( c == "!"){
                           if(currentCalc->getTypeComplexe()==true || currentCalc->getTypeConstante()!=entier)
                               throw Erreurs(5,"Opération non autoriséee dans ce mode");
                           else
                           {
                               Constante * c = currentCalc->fact();
                               //if(indexList == list.count()) // Si dernier element de la liste
                               //    currentCalc->pushHistorique(new Expression("="));
                               currentCalc->push(c);
                               currentCalc->operationUnaire();
                               delLastElement(1);
                               this->affichePile();
                               addSauvegardeUnaire(c);
                           }
                           }

                       else{
                           modeComplexe = false;
                           im_num = 0;
                           re_num = 0;
                           im_den = 1;
                           re_den = 1;
                           QStringList list2 = c.split("$");
                           QStringList list3 = list2.at(0).split("/");
                           if(list3.at(0).toDouble()==0 && list3.at(0)!="0")
                               throw Erreurs(2,"Synthaxe incorrecte");
                           else
                               re_num = list3.at(0).toDouble();

                           if(list3.count() > 1)
                               if(list3.at(1).toDouble()==0 && list3.at(1)!="0")
                                   throw Erreurs(2,"Synthaxe incorrecte");
                               else
                                   re_den = list3.at(1).toDouble();
                           if(list2.count()> 1){
                               QStringList list4 = list2.at(1).split("/");
                               if(list4.at(0).toDouble()==0 && list4.at(0)!="0")
                                   throw Erreurs(2,"Synthaxe incorrecte");
                               else
                                   im_num = list4.at(0).toDouble();
                               if(list4.count() > 1)
                                   if(list4.at(1).toDouble()==0 && list4.at(1)!="0")
                                       throw Erreurs(2,"Synthaxe incorrecte");
                                   else
                                       im_den = list4.at(1).toDouble();
                           }
                           Complexe * c = new Complexe(re_num,re_den,im_num,im_den,currentCalc->getTypeComplexe(),currentCalc->getTypeConstante());
                           //if(indexList == list.count()) // Si dernier element de la liste
                           //    currentCalc->pushHistorique(new Expression("="));
                           currentCalc->push(c);
                           this->affichePile();
                           addSauvegarde(c);
                       }

                       }
                   }
             }
        }
    else{

        Expression * e = new Expression(text);
        currentCalc->push(e);
        addSauvegarde(e);
        this->affichePile();
        }
    }
    catch(std::exception const& e)
    {
        MessageErreur(e.what());
    }
    /**
     * \brief     Ajout de l'élément à la pile
     * \details   Permet de traiter l'élément passé en paramètre et d'effectuer l'opération qui convient
     * \param   text Le QString à traiter
     */
    }


void MainWindow::on_egal_clicked(){
    try{
    QString text(ui->expression->text());
    text.replace('\'','"');
    if(verifExpression(text)){
        ui->expression->setText("");
        textToComplexePush(text);
        }
    else if (text.isEmpty()){
        on_bDup_clicked();
    }
    else
        throw Erreurs(2,"Syntaxe incorrecte");
    }
    catch(std::exception const& e)
    {
        MessageErreur(e.what());
    }
    /**
     * \brief    Intéraction avec le bouton =
     * \details  Ajout de la zone de saisie à la pile
     */

}

void MainWindow::on_bClear_clicked(){
    try{
    int calcIndex = ui->Onglet->currentIndex();
    Calculatrice* currentCalc = calc.value(calcIndex);
    QString fileName = FICHIER_ENTETE_PILE + QString::number(calcIndex) + FICHIER_EXTENSION_PILE;
    QSettings settings(fileName,QSettings::IniFormat,this);
    settings.remove(QString::number(ui->pileAffichage->count()-1));
    delete ui->pileAffichage->takeItem(ui->pileAffichage->count()-1);
    currentCalc->pop();
    //currentCalc->pushHistorique(new Expression("CLEAR"));
    }
    catch(std::exception const& e)
    {
        MessageErreur(e.what());
    }
    /**
     * \brief    Intéraction avec le bouton CLEAR
     * \details  Supprime le dernier élément de la pile
     */
}

void MainWindow::on_bClearAll_clicked(){
    try{
        int calcIndex = ui->Onglet->currentIndex();
        Calculatrice* currentCalc = calc.value(calcIndex);
        QString fileName = FICHIER_ENTETE_PILE + QString::number(calcIndex) + FICHIER_EXTENSION_PILE;
        QSettings settings(fileName,QSettings::IniFormat,this);
        QStringList keys = settings.childGroups();
        foreach(QString key, keys)
            settings.remove(key);
        ui->pileAffichage->clear();
        currentCalc->deletePile();
        //currentCalc->pushHistorique(new Expression("CLEAR ALL"));
    }
    catch(std::exception const& e)
    {
        MessageErreur(e.what());
    }
    /**
     * \brief    Intéraction avec le bouton CLEAR ALL
     * \details  Vide la pile
     */
}

void MainWindow::on_Aapropos_triggered(){
    Apropos fenetre(this);
    fenetre.exec();
    /**
     * \brief    Intéraction avec le bouton A Propos du menu
     * \details  Ouverture de la fenêtre d'information
     */
}

void MainWindow::on_menuActivClavier_triggered(){
    if(ui->menuActivClavier->isChecked())
    {
        this->setMinimumHeight(620);
        this->setMaximumHeight(620);
    }
    else
    {
        this->setMinimumHeight(440);
        this->setMaximumHeight(440);
    }
    /**
     * \brief    Intéraction avec le bouton Clavier Visuel du menu
     * \details  Afficher/Masquer le clavier
     */
}




void MainWindow::on_menuAide_triggered(){
    Aide fenetre(this);
    fenetre.exec();
    /**
     * \brief    Intéraction avec le bouton Aide du menu
     * \details  Ouverture de la fenêtre d'aide
     */
}

void MainWindow::afficheBoutonComplexe(Calculatrice * currentCalc){
    if(ui->CheckComplexe->isChecked()){
           ui->bDollar->setEnabled(true);
           ui->bSign->setEnabled(true);
           ui->bSqr->setEnabled(true);
           ui->bCube->setEnabled(true);
           ui->bPow->setEnabled(false);
           ui->bMod->setEnabled(false);
           ui->bSin->setEnabled(false);
           ui->bSinh->setEnabled(false);
           ui->bCos->setEnabled(false);
           ui->bCosh->setEnabled(false);
           ui->bTan->setEnabled(false);
           ui->bTanh->setEnabled(false);
           ui->bLn->setEnabled(false);
           ui->bLog->setEnabled(false);
           ui->bInv->setEnabled(false);
           ui->bSqrt->setEnabled(false);
           ui->bFact->setEnabled(false);

           }
    else {
         ui->bDollar->setEnabled(false);
         ui->bSign->setEnabled(true);
         ui->bSqr->setEnabled(true);
         ui->bCube->setEnabled(true);
         ui->bPow->setEnabled(true);
         ui->bSqrt->setEnabled(true);
         if (currentCalc->getTypeConstante()==entier)
         {
            ui->bInv->setEnabled(false);
            ui->bMod->setEnabled(true);
            ui->bFact->setEnabled(true);
            ui->bSin->setEnabled(false);
            ui->bSinh->setEnabled(false);
            ui->bCos->setEnabled(false);
            ui->bCosh->setEnabled(false);
            ui->bTan->setEnabled(false);
            ui->bTanh->setEnabled(false);
            ui->bLn->setEnabled(false);
            ui->bLog->setEnabled(false);
         }
         else
         {
            ui->bMod->setEnabled(false);
            ui->bSin->setEnabled(true);
            ui->bSinh->setEnabled(true);
            ui->bCos->setEnabled(true);
            ui->bCosh->setEnabled(true);
            ui->bTan->setEnabled(true);
            ui->bTanh->setEnabled(true);
            ui->bLn->setEnabled(true);
            ui->bLog->setEnabled(true);
            ui->bInv->setEnabled(true);
            ui->bFact->setEnabled(false);
         }
         }
    /**
     * \brief    Modifier l'affichage pour le mode complexe
     * \param    currentCalc Calculatrice* à modifier
     */
}

void MainWindow::on_CheckComplexe_clicked(){
    int calcIndex = ui->Onglet->currentIndex();
    Calculatrice* currentCalc = calc.value(calcIndex) ;
    QSettings settings(FICHIER_PARAMETRES,QSettings::IniFormat,this);
    settings.beginGroup(QString::number(calcIndex));
    if(ui->CheckComplexe->isChecked()){
           settings.setValue("complexe",1);
           currentCalc->setTypeComplexe(true);
           settings.endGroup();
    }
    else{
        settings.setValue("complexe",0);
        currentCalc->setTypeComplexe(false);
        settings.endGroup();
        on_bClearAll_clicked();
        ui->pileAffichage->clear();
    }
    afficheBoutonComplexe(currentCalc);
    /**
     * \brief    Intéraction avec le bouton Complexe
     * \details  Active/Désactive le mode complexe
     */

}

void MainWindow::on_radioDegre_clicked(){
    int calcIndex = ui->Onglet->currentIndex();
    Calculatrice* currentCalc = calc.value(calcIndex) ;
    QSettings settings(FICHIER_PARAMETRES,QSettings::IniFormat,this);
    settings.beginGroup(QString::number(calcIndex));
    settings.setValue("degre",0);
    settings.endGroup();
    currentCalc->setTypeDegre(false);
    /**
     * \brief    Intéraction avec le bouton radio Degré
     * \details  Passe en mode degré
     */
}

void MainWindow::on_radioRadian_clicked(){
    int calcIndex = ui->Onglet->currentIndex();
    Calculatrice* currentCalc = calc.value(calcIndex) ;
    QSettings settings(FICHIER_PARAMETRES,QSettings::IniFormat,this);
    settings.beginGroup(QString::number(calcIndex));
    settings.setValue("degre",1);
    settings.endGroup();
    currentCalc->setTypeDegre(true);
    /**
     * \brief    Intéraction avec le bouton radio Radian
     * \details  Passe en mode radian
     */
}

void MainWindow::afficheBoutonReel(Calculatrice * currentCalc){
    if(currentCalc->getTypeConstante() == reel){
           ui->bMod->setEnabled(false);
           ui->bFact->setEnabled(false);
           if (currentCalc->getTypeComplexe()==false)
           {
               ui->bInv->setEnabled(true);
               ui->bSin->setEnabled(true);
               ui->bSinh->setEnabled(true);
               ui->bCos->setEnabled(true);
               ui->bCosh->setEnabled(true);
               ui->bTan->setEnabled(true);
               ui->bTanh->setEnabled(true);
               ui->bLn->setEnabled(true);
               ui->bLog->setEnabled(true);
           }
           else
           {
                ui->bInv->setEnabled(false);
                ui->bSin->setEnabled(false);
                ui->bSinh->setEnabled(false);
                ui->bCos->setEnabled(false);
                ui->bCosh->setEnabled(false);
                ui->bTan->setEnabled(false);
                ui->bTanh->setEnabled(false);
                ui->bLn->setEnabled(false);
                ui->bLog->setEnabled(false);
           }
     }
    /**
     * \brief    Modifier l'affichage pour le mode réel
     * \param    currentCalc Calculatrice* à modifier
     */
}



void MainWindow::on_radioReel_clicked(){
    int calcIndex = ui->Onglet->currentIndex();
    Calculatrice* currentCalc = calc.value(calcIndex) ;
    QSettings settings(FICHIER_PARAMETRES,QSettings::IniFormat,this);
    settings.beginGroup(QString::number(calcIndex));
    settings.setValue("retour","reel");
    settings.endGroup();
    currentCalc->setTypeConstante(reel);
    afficheBoutonReel(currentCalc);
    currentCalc->deletePile();
    on_bClearAll_clicked();
    /**
     * \brief    Intéraction avec le bouton radio Réel
     * \details  Passe en mode réel
     */
}
void MainWindow::afficheBoutonEntier(Calculatrice * currentCalc){
    if(currentCalc->getTypeConstante() == entier){
           if (currentCalc->getTypeComplexe()==false)
           {
                ui->bMod->setEnabled(true);
                ui->bFact->setEnabled(true);

           }
           else
           {
                ui->bFact->setEnabled(false);
                ui->bMod->setEnabled(false);

           }
           ui->bInv->setEnabled(false);
           ui->bSin->setEnabled(false);
           ui->bCos->setEnabled(false);
           ui->bTan->setEnabled(false);
           ui->bSinh->setEnabled(false);
           ui->bCosh->setEnabled(false);
           ui->bTanh->setEnabled(false);
           ui->bLn->setEnabled(false);
           ui->bLog->setEnabled(false);
           }
    /**
     * \brief    Modifier l'affichage pour le mode entier
     * \param    currentCalc Calculatrice* à modifier
     */
}

void MainWindow::on_radioEntier_clicked(){
    int calcIndex = ui->Onglet->currentIndex();
    QSettings settings(FICHIER_PARAMETRES,QSettings::IniFormat,this);
    settings.beginGroup(QString::number(calcIndex));
    settings.setValue("retour","entier");
    settings.endGroup();
    Calculatrice* currentCalc = calc.value(calcIndex) ;
    currentCalc->setTypeConstante(entier);
    afficheBoutonEntier(currentCalc);
    currentCalc->deletePile();
    on_bClearAll_clicked();
    /**
     * \brief    Intéraction avec le bouton radio Entier
     * \details  Passe en mode entier
     */
}

void MainWindow::afficheBoutonRationnel(Calculatrice * currentCalc){
    if(currentCalc->getTypeConstante() == rationnel){
           ui->bMod->setEnabled(false);
           ui->bFact->setEnabled(false);
           if (currentCalc->getTypeComplexe()==false)
           {
               ui->bInv->setEnabled(true);
               ui->bSin->setEnabled(true);
               ui->bSinh->setEnabled(true);
               ui->bCos->setEnabled(true);
               ui->bCosh->setEnabled(true);
               ui->bTan->setEnabled(true);
               ui->bTanh->setEnabled(true);
               ui->bLn->setEnabled(true);
               ui->bLog->setEnabled(true);
           }
           else
           {
                ui->bInv->setEnabled(false);
                ui->bSin->setEnabled(false);
                ui->bSinh->setEnabled(false);
                ui->bCos->setEnabled(false);
                ui->bCosh->setEnabled(false);
                ui->bTan->setEnabled(false);
                ui->bTanh->setEnabled(false);
                ui->bLn->setEnabled(false);
                ui->bLog->setEnabled(false);
           }
     }
    /**
     * \brief    Modifier l'affichage pour le mode rationnel
     * \param    currentCalc Calculatrice* à modifier
     */
}

void MainWindow::on_radioRatio_clicked(){
    int calcIndex = ui->Onglet->currentIndex();
    Calculatrice* currentCalc = calc.value(calcIndex) ;
    QSettings settings(FICHIER_PARAMETRES,QSettings::IniFormat,this);
    settings.beginGroup(QString::number(calcIndex));
    settings.setValue("retour","rationnel");
    settings.endGroup();
    currentCalc->setTypeConstante(rationnel);
    afficheBoutonRationnel(currentCalc);
    currentCalc->deletePile();
    on_bClearAll_clicked();
    /**
     * \brief    Intéraction avec le bouton radio Rationnel
     * \details  Passe en mode rationnel
     */
}

 void MainWindow::on_bErase_clicked(){
     QString t = ui->expression->text();
     if( t == "ERREUR" )
         ui->expression->setText("");
     else{
        t.remove(t.length()-1,1);
        ui->expression->setText(t);
     }
     /**
      * \brief    Intéraction avec le bouton <-
      * \details  Efface un caractère de la zone de saisie
      */
 }

 void MainWindow::on_bDollar_clicked(){
     QString t = ui->expression->text();
     if( t == "ERREUR" )
         ui->expression->setText("");
     ui->expression->setText(ui->expression->text() + "$");
     /**
      * \brief    Intéraction avec le bouton $
      * \details  Ajoute $ à la zone de saisie
      */
 }

 void MainWindow::on_bGui_clicked(){
     QString t = ui->expression->text();
     if( t == "ERREUR" )
         ui->expression->setText("");
     ui->expression->setText(ui->expression->text() + "\"");
     /**
      * \brief    Intéraction avec le bouton "
      * \details  Ajoute "
      */
 }

 void MainWindow::on_bComa_clicked(){
     QString t = ui->expression->text();
     if( t == "ERREUR" )
         ui->expression->setText("");
     ui->expression->setText(ui->expression->text() + ",");
     /**
      * \brief    Intéraction avec le bouton ,
      * \details  Ajoute , à la zone de saisie
      */
 }

 void MainWindow::on_bEval_clicked()
{
    try{
    Calculatrice* currentCalc = calc.value(ui->Onglet->currentIndex()) ;
    QString text(ui->expression->text());
    if (text.isEmpty())
    {
        text.replace('\'','"');
        Constante* c = currentCalc->pop();
        if(c->isType("Expression"))
        {
            delete ui->pileAffichage->takeItem(ui->pileAffichage->count()-1);
            Expression * e = dynamic_cast<Expression*>(c);
            this->textToComplexePush(e->getExpression(false));
        }
        else
        {
            currentCalc->push(c);
            throw Erreurs(7,"L'élement à évaluer n'est pas une expression");
        }

    }

    else
    {
        text.replace('\'','"');
        if(isExpression(text))
        {
            ui->expression->setText("");
            Expression * e = new Expression(text);
            this->textToComplexePush(e->getExpression(false));
        }
        else
            throw Erreurs(7,"L'élement à évaluer n'est pas une expression");
    }
     }
     catch(std::exception const& e)
     {
         MessageErreur(e.what());
     }
     /**
      * \brief    Intéraction avec le bouton EVAL
      * \details  Evalue l'expression de la zone de saisie, ou de la pile
      */
}


 void MainWindow::on_bMean_clicked()
 {
     try{
     int calcIndex = ui->Onglet->currentIndex();
     Calculatrice* currentCalc = calc.value(calcIndex);
     Constante *c = currentCalc->moyenne();
     if (c!=false)
     {
         QString fileName = FICHIER_ENTETE_PILE + QString::number(calcIndex) + FICHIER_EXTENSION_PILE;
         QSettings settings(fileName,QSettings::IniFormat,this);

         for (unsigned int i(0); i<currentCalc->getMean(); i++)
            settings.remove(QString::number(ui->pileAffichage->count()-1));
         currentCalc->push(c);
         for (unsigned int i(0); i<currentCalc->getMean(); i++)
            currentCalc->operationUnaire();
         genererFichierPile();
         //addSauvegarde(c);
         this->affichePile();

     }
     else
         ui->expression->setText("ERREUR");
     }
     catch(std::exception const& e)
     {
         MessageErreur(e.what());
     }
     /**
      * \brief    Intéraction avec le bouton MEAN
      * \details  Moyenne les x derniers éléments de la pile
      */
 }

 void MainWindow::on_bSum_clicked()
 {
     try{
     int calcIndex = ui->Onglet->currentIndex();
     Calculatrice* currentCalc = calc.value(calcIndex);
     QString fileName = FICHIER_ENTETE_PILE + QString::number(calcIndex) + FICHIER_EXTENSION_PILE;
     QSettings settings(fileName,QSettings::IniFormat,this);
     Constante *c = currentCalc->somme();

     if (c!=false)
     {
         for (unsigned int i(0); i<currentCalc->getSum(); i++)
            settings.remove(QString::number(ui->pileAffichage->count()-1));
         currentCalc->push(c);
         for (unsigned int i(0); i<currentCalc->getMean(); i++)
            currentCalc->operationUnaire();
         genererFichierPile();
         //addSauvegarde(c);
         this->affichePile();

     }
     else
         ui->expression->setText("ERREUR");
     }
     catch(std::exception const& e)
     {
         MessageErreur(e.what());
     }
     /**
      * \brief    Intéraction avec le bouton SUM
      * \details  Somme les x derniers éléments de la pile
      */

 }

 void MainWindow::on_bDup_clicked()
 {
     try{
     int calcIndex = ui->Onglet->currentIndex();
     Calculatrice* currentCalc = calc.value(calcIndex);
     QString fileName = FICHIER_ENTETE_PILE + QString::number(calcIndex) + FICHIER_EXTENSION_PILE;
     QSettings settings(fileName,QSettings::IniFormat,this);
     Constante *c = currentCalc->duplique();
     if (c!=false)
     {
         ui->pileAffichage->addItem(c->toString());
         settings.beginWriteArray(QString::number(ui->pileAffichage->count()-1));
         if(c->isType("Complexe") || c->isType("Rationnel"))
              settings.setValue("val",c->getValue());
         else
             settings.setValue("val",c->toString());
     }
     else
         ui->expression->setText("ERREUR");
     }
     catch(std::exception const& e)
     {
         MessageErreur(e.what());
     }
     /**
      * \brief    Intéraction avec le bouton DUP
      * \details  Duplique le dernier élément de la pile
      */
 }

void MainWindow::on_bSwap_clicked()
 {
    Calculatrice* currentCalc = calc.value(ui->Onglet->currentIndex()) ;
    currentCalc->newPile();
     try{
     if(currentCalc->swap()==true)
     {         
         int indexD = currentCalc->getSwapStart();
         int indexF = currentCalc->getSwapEnd();

         if (indexD>indexF)
         {
             int tmp=indexD;
             indexD=indexF;
             indexF=tmp;
         }

         if (indexD==indexF)
            {}
         else
             {
             Constante* c1 = currentCalc->at(indexD);
             Constante* c2 = currentCalc->at(indexF);
             int calcIndex = ui->Onglet->currentIndex();
             QString fileName = FICHIER_ENTETE_PILE + QString::number(calcIndex) + FICHIER_EXTENSION_PILE;
             QSettings settings(fileName,QSettings::IniFormat,this);

             settings.remove(QString::number(indexD));
             QListWidgetItem* tmp1 = ui->pileAffichage->takeItem(indexD);
             ui->pileAffichage->insertItem(indexF, tmp1);

             settings.remove(QString::number(indexF));
             QListWidgetItem* tmp2 = ui->pileAffichage->takeItem(indexF-1);
             ui->pileAffichage->insertItem(indexD, tmp2);

             settings.beginWriteArray(QString::number(indexD));
             if(c1->isType("Complexe") || c1->isType("Rationnel"))
                  settings.setValue("val",c1->getValue());
             else
                 settings.setValue("val",c1->toString());

             settings.endArray();

             settings.beginWriteArray(QString::number(indexF));
             if(c2->isType("Complexe") || c2->isType("Rationnel"))
                  settings.setValue("val",c2->getValue());
             else
                 settings.setValue("val",c2->toString());
         }

     }
     else
        currentCalc->deleteLastPile();
    }
    catch(std::exception const& e)
    {
        currentCalc->deleteLastPile();
        MessageErreur(e.what());

    }
    /**
     * \brief    Intéraction avec le bouton SWAP
     * \details  Echange les éléments x et y de la pile
     */
 }

void MainWindow::genererFichierPile(){
    int calcIndex = ui->Onglet->currentIndex();
    Calculatrice* currentCalc = calc.value(calcIndex);
    QString fileName = FICHIER_ENTETE_PILE + QString::number(calcIndex) + FICHIER_EXTENSION_PILE;
    QSettings settings(fileName,QSettings::IniFormat,this);
    QFile::remove(fileName);
    for(int i = 0; i < currentCalc->countPileElement(); i++){
        settings.beginWriteArray(QString::number(i));
        Constante * c = currentCalc->at(i);
        if(c->isType("Complexe") || c->isType("Rationnel"))
             settings.setValue("val",c->getValue());
        else
            settings.setValue("val",c->toString());
        settings.endArray();
       }
    /**
     * \brief    Création d'un fichier de sauvegarde de la pile
     */
}


void MainWindow::MessageErreur(const char* message)
{
    QMessageBox::warning(this, "Erreur", message);
    /**
     * \brief     Affichage d'un message d'erreur
     * \param   message Le QString à afficher comme message d'erreur
     */
}

void MainWindow::on_actionAnnuler_triggered(){
    Calculatrice* currentCalc = calc.value(ui->Onglet->currentIndex()) ;
    currentCalc->setCurrentIndexHist(currentCalc->getCurrentIndexHist()-1);
    genererFichierPile();
    affichePile();
    /**
     * \brief    Intéraction avec le bouton Annuler du menu
     * \details  Annule la dernière opération
     */
}

void MainWindow::on_actionRetablir_triggered(){
    Calculatrice* currentCalc = calc.value(ui->Onglet->currentIndex()) ;
    currentCalc->setCurrentIndexHist(currentCalc->getCurrentIndexHist()+1);
    genererFichierPile();
    affichePile();
    /**
     * \brief    Intéraction avec le bouton Rétablir du menu
     * \details  Annule la dernière annulation
     */
}

 void  MainWindow::on_Onglet_currentChanged(){
   ui->pileAffichage->clear();
   affichePile();
   int calcIndex = ui->Onglet->currentIndex();
   Calculatrice* currentCalc = calc.value(calcIndex) ;
   QSettings settings(FICHIER_PARAMETRES,QSettings::IniFormat,this);
   settings.beginWriteArray("mode");
   settings.setValue("currentOnglet",calcIndex);
   settings.endArray();
   ui->CheckComplexe->setChecked(currentCalc->getTypeComplexe());
   if(currentCalc->getTypeDegre())
       ui->radioRadian->setChecked(true);
   else
       ui->radioDegre->setChecked(true);
   ui->radioEntier->setChecked(currentCalc->getTypeConstante()==entier);
   ui->radioRatio->setChecked(currentCalc->getTypeConstante()==rationnel);
   ui->radioReel->setChecked(currentCalc->getTypeConstante()==reel);

   if(currentCalc->getTypeComplexe())
       afficheBoutonComplexe(currentCalc);
   if(currentCalc->getTypeConstante()==reel)
       afficheBoutonReel(currentCalc);
   else if(currentCalc->getTypeConstante()==rationnel)
           afficheBoutonRationnel(currentCalc);
   else
       afficheBoutonEntier(currentCalc);
   /**
    * \brief    Changement d'onglet
    */
 }

 void MainWindow::genererFichierParametres(){
     QSettings settings(FICHIER_PARAMETRES,QSettings::IniFormat,this);
     settings.clear();// On vide le fichier

     settings.beginWriteArray("mode");
     settings.setValue("nbOnglets",calc.size());
     settings.setValue("currentOnglet",ui->Onglet->currentIndex());
     settings.endArray();
     for(int i = 0; i <calc.size();i++){
         Calculatrice* currentCalc = calc.value(i) ;
         settings.beginWriteArray(QString::number(i));
         if(currentCalc->getTypeComplexe())
            settings.setValue("complexe",1);
         else
            settings.setValue("complexe",0);
         if(currentCalc->getTypeDegre())
             settings.setValue("degre",1);
         else
             settings.setValue("degre",0);
         if(currentCalc->getTypeConstante()==entier)
             settings.setValue("retour","entier");
         else if(currentCalc->getTypeConstante()==rationnel)
             settings.setValue("retour","rationnel");
         else
             settings.setValue("retour","reel");
         settings.setValue("swaps",currentCalc->getSwapStart());
         settings.setValue("swape",currentCalc->getSwapEnd());
         settings.setValue("sum",currentCalc->getSum());
         settings.setValue("mean",currentCalc->getMean());
         settings.setValue("affichage",currentCalc->getAffichage());
         settings.endArray();
     }
     /**
      * \brief    Création d'un fichier de sauvegarde des paramètres
      */
 }

void MainWindow::on_Onglet_tabCloseRequested(int i){
   ui->Onglet->removeTab(i);
   Calculatrice * c = calc.value(i);
   if(c != 0){ // si l'onglet existe en memoire
       calc.remove(i);
   }
   for(int a = 0; a < calc.size(); a++){
       QString text("Calc " + QString::number(a+1));
       ui->Onglet->setTabText(a,text);
   }
   QString fileName = FICHIER_ENTETE_PILE + QString::number(i) + FICHIER_EXTENSION_PILE;
   QFile::remove(fileName);
   for(int j = i; j <= calc.size(); j++){
       QString oldFileName = FICHIER_ENTETE_PILE + QString::number(j) + FICHIER_EXTENSION_PILE;
       QString newFileName = FICHIER_ENTETE_PILE + QString::number(j-1) + FICHIER_EXTENSION_PILE;
       QFile::rename(oldFileName,newFileName);
       //Modification des paramatres
   }
   if(calc.size() == 1){
       ui->Onglet->setTabsClosable(false);
   }
   else{
       ui->Onglet->setTabsClosable(true);
   }
   if(i+1 > ui->Onglet->count())
        ui->Onglet->setCurrentIndex( ui->Onglet->count()-1);
   else
       ui->Onglet->setCurrentIndex(i);
   affichePile();
   genererFichierParametres();
   /**
    * \brief    Fermer l'onglet
    */
}

void MainWindow::on_pushButton_clicked()
{
    int i = ui->Onglet->count()+1;
    QString text("Calc " + QString::number(i));
    ui->Onglet->addTab(new QWidget(),text);
    ui->Onglet->setCurrentIndex(i);
    if(calc.value(i-1) == 0){
            calc.insert(i-1,new Calculatrice());
    }
    if(calc.size() == 1)
        ui->Onglet->setTabsClosable(false);
    else
        ui->Onglet->setTabsClosable(true);
    QSettings settings(FICHIER_PARAMETRES,QSettings::IniFormat,this);
    settings.beginWriteArray("mode");
    settings.setValue("nbOnglets",calc.size());
    settings.endArray();
    ui->Onglet->setCurrentIndex(ui->Onglet->count()-1);
    /**
     * \brief    Nouvel onglet
     */
}

void MainWindow::on_bPlusEgal_clicked()
{
    int calcIndex = ui->Onglet->currentIndex();
    Calculatrice* currentCalc = calc.value(calcIndex) ;
    int i = ui->Onglet->count()+1;
    QString text("Calc " + QString::number(i));
    ui->Onglet->addTab(new QWidget(),text);
    ui->Onglet->setCurrentIndex(i);
    if(calc.value(i-1) == 0){
            calc.insert(i-1,new Calculatrice(*currentCalc));
    }
    if(calc.size() == 1)
        ui->Onglet->setTabsClosable(false);
    else
        ui->Onglet->setTabsClosable(true);
    QSettings settings(FICHIER_PARAMETRES,QSettings::IniFormat,this);
    settings.beginWriteArray("mode");
    settings.setValue("nbOnglets",calc.size());
    settings.endArray();
    if(currentCalc->getTypeComplexe())
        afficheBoutonComplexe(currentCalc);
    if(currentCalc->getTypeConstante()==reel)
        afficheBoutonReel(currentCalc);
    else if(currentCalc->getTypeConstante()==rationnel)
            afficheBoutonRationnel(currentCalc);
    else
        afficheBoutonEntier(currentCalc);
    ui->Onglet->setCurrentIndex(ui->Onglet->count()-1);
    genererFichierParametres();
    genererFichierPile();
    affichePile();
    /**
     * \brief    Copie de l'onglet courant
     */
}

void MainWindow::on_bDelOnglet_clicked(){
    if(ui->Onglet->count() > 1)
        on_Onglet_tabCloseRequested(ui->Onglet->currentIndex());
    /**
     * \brief    Suppression d'onglet
     */
}

void MainWindow::on_actionQuitter_triggered() {
    this->close();
}
