#ifndef APROPOS_H
#define APROPOS_H

#include <QDialog>

namespace Ui {
class Apropos;
}

class Apropos : public QDialog
{
    Q_OBJECT
    
public:
    explicit Apropos(QWidget *parent = 0);
    ~Apropos();
    
private:
    Ui::Apropos *ui;

private slots:
    void on_bOk_clicked();
};

#endif // APROPOS_H
