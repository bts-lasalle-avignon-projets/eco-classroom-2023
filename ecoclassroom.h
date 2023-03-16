#ifndef ECOCLASSROOM_H
#define ECOCLASSROOM_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class ecoClassroom; }
QT_END_NAMESPACE

class ecoClassroom : public QWidget
{
    Q_OBJECT

public:
    ecoClassroom(QWidget *parent = nullptr);
    ~ecoClassroom();
    void afficheSalles();
    void afficheUneSalle();
    void afficheMesures();
    void afficheEtats();
    void afficheTHI();
    void afficheIADI();
    void afficheICONE();
    void filtrerSalles();
    void detailsSalles();
    void afficheGraphiques();

private:
    Ui::ecoClassroom *ui;
};
#endif // ECOCLASSROOM_H
