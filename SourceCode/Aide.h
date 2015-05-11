#ifndef AIDE_H
#define AIDE_H

#include <QDialog>

namespace Ui {
class Aide;
}

class Aide : public QDialog
{
    Q_OBJECT

public:
    explicit Aide(QWidget *parent = 0);
    ~Aide();

private:
    Ui::Aide *ui;

private slots:
    void on_bOkAide_clicked();
};

#endif // AIDE_H
