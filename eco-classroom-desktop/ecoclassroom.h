#ifndef ECOCLASSROOM_H
#define ECOCLASSROOM_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui
{
class EcoClassroom;
}
QT_END_NAMESPACE

class EcoClassroom : public QWidget
{
    Q_OBJECT

  public:
    EcoClassroom(QWidget* parent = nullptr);
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
    Ui::EcoClassroom* ui;
    QWidget*          affichageGlobaleSalles;
    QPushButton*      boutonB11;
    QPushButton*      boutonB20;
    QPushButton*      boutonB21;
    QLabel*           texteIADI;
    QLabel*           texteICONE;
    QLabel*           texteLumiere;
    QLabel*           textePresence;
    QLabel*           texteFenetre;
};

#endif // ECOCLASSROOM_H
