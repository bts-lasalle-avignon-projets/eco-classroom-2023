#ifndef ECOCLASSROOM_H
#define ECOCLASSROOM_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class EcoClassroom; }
QT_END_NAMESPACE

class EcoClassroom : public QWidget
{
    Q_OBJECT

public:
    EcoClassroom(QWidget *parent = nullptr);
    ~EcoClassroom();
    void afficherSalles();
    void afficherUneSalle();
    void afficherMesures();
    void afficherEtats();
    void afficherTHI();
    void afficherIADI();
    void afficherICONE();
    void filtrerSalles();
    void afficherDetailsSalles();
    void afficherGraphiques();

private:
    Ui::EcoClassroom *ui;
};

#endif // ECOCLASSROOM_H
