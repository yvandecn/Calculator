#ifndef PARAMETRES_H
#define PARAMETRES_H

#include <QDialog>

namespace Ui {
class Parametres;
}

class Parametres : public QDialog
{
    Q_OBJECT
    
public:
    explicit Parametres(QWidget *parent = 0);
    void setParametres(int swapS = 1,int swapE = 1,int sum = 1,int mean = 1, int affichage = 1);
    ~Parametres();
private slots:
    void on_bOk_clicked();
    
private:
    Ui::Parametres *ui;
    void afficheHistorique(QStringList historique);


};

#endif // PARAMETRES_H
