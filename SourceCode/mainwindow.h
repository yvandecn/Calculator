#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Apropos.h"
#include "Calculatrice.h"
#include "Constantes/Expression.h"
#include <QString>
#include "Constantes/Rationnel.h"
#include "Parametres.h"
#include "Aide.h"
#include <QFile>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setMIndexSWAP(int a,int b);
    void setMSum(int a);
    void setMMean(int a);
    void setMAffichage(int a);
    void MessageErreur(const char* message);
    QStringList getStringPileSauvegarde() const;
    void affichePile();

private slots:
    //Clavier
    void on_b1_clicked();
    void on_b2_clicked();
    void on_b3_clicked();
    void on_b4_clicked();
    void on_b5_clicked();
    void on_b6_clicked();
    void on_b7_clicked();
    void on_b8_clicked();
    void on_b9_clicked();
    void on_b0_clicked();
    void on_b_moins_clicked();
    void on_b_div_clicked();
    void on_b_plus_clicked();
    void on_b_fois_clicked();
    void on_b_espace_clicked();
    void on_egal_clicked();
    void on_bClear_clicked();
    void on_bClearAll_clicked();
    void on_Aapropos_triggered();
    void on_CheckComplexe_clicked();
    void on_radioReel_clicked();
    void on_radioEntier_clicked();
    void on_radioRatio_clicked();
    void on_radioDegre_clicked();
    void on_radioRadian_clicked();
    void on_bErase_clicked();
    void on_bDollar_clicked();
    void on_bGui_clicked();
    void on_bComa_clicked();
    void on_bPow_clicked();
    void on_bSqr_clicked();
    void on_bSqrt_clicked();
    void on_bCube_clicked();
    void on_bMod_clicked();
    void on_bSin_clicked();
    void on_bCos_clicked();
    void on_bTan_clicked();
    void on_bSinh_clicked();
    void on_bCosh_clicked();
    void on_bTanh_clicked();
    void on_bLn_clicked();
    void on_bLog_clicked();
    void on_bInv_clicked();
    void on_bSign_clicked();
    void on_bFact_clicked();
    void on_bEmpty_clicked();
    void on_bEval_clicked();
    void on_bMean_clicked();
    void on_bSum_clicked();
    void on_bDup_clicked();
    void on_bSwap_clicked();
    void on_menuParametre_triggered();
    void on_menuAide_triggered();
    void on_menuActivClavier_triggered();
    void on_actionAnnuler_triggered();
    void on_actionRetablir_triggered();
    void on_Onglet_currentChanged();
    void on_actionQuitter_triggered();

    void on_Onglet_tabCloseRequested(int index);

    void on_pushButton_clicked();

    void on_bPlusEgal_clicked();

    void on_bDelOnglet_clicked();

private:
    Ui::MainWindow *ui;
    Parametres * parametres;
    bool isExpression(const QString& text);
    void addPileAffichage(Constante * c);
    bool verifExpression(const QString& text);
    void textToComplexePush(const QString& text);
    void affichePileBinaire(Constante *);
    void affichePileUnaire(Constante *);
    QStringList split(const QString&);
    void getAllParametres();
    void getStackData();
    void afficheBoutonReel(Calculatrice * currentCalc);
    void afficheBoutonRationnel(Calculatrice * currentCalc);
    void afficheBoutonEntier(Calculatrice * currentCalc);
    void afficheBoutonComplexe(Calculatrice * currentCalc);
    void genererFichierParametres();
    void delLastElement(int);
    void genererFichierPile();


    void addSauvegardeBinaire(Constante * c);
    void addSauvegardeUnaire(Constante * c);
    void addSauvegarde(Constante * c);
    QVector<Calculatrice*> calc;
};

#endif // MAINWINDOW_H
