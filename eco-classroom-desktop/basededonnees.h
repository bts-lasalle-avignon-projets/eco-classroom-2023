/**
 * @file basededonnees.h
 * @brief Déclaration de la classe BaseDeDonnees
 */

#ifndef BASEDEDONNEE_H
#define BASEDEDONNEE_H

#include <QObject>
#include <QtSql/QtSql>
#include <QSqlDatabase>
#include <QMutex>
#include <QString>

/**
 * @def TYPE_BDD
 * @brief Définit le type de base de données QSQLITE ou QMYSQL
 */
#define TYPE_BDD ""
//#define TYPE_BDD "QMYSQL"
//#define TYPE_BDD "QSQLITE"

/**
 * @class BaseDeDonnees
 * @brief Classe permettant de s'interfacer avec la base de données
 */
class BaseDeDonnees : public QObject
{
    Q_OBJECT
  private:
    static BaseDeDonnees* baseDeDonnees; //!< objet base de données
    static QString typeBase; //!< type de base de données (MySQL, SQLite, ...)
    static int nbAcces; //!< le nombre d'accès en cours à la base de données
    QSqlDatabase db;    //!< connexion avec la base de données
    QMutex       mutex; //!< protection multi-thread

    BaseDeDonnees(QString type);
    ~BaseDeDonnees();

  public:
    static BaseDeDonnees* getInstance(QString type = TYPE_BDD);
    static void           detruireInstance();

    // MySQL
    bool connecter(QString nomBase,
                   QString username,
                   QString password,
                   QString serveur);
    bool estConnecte();
    // SQLite
    bool ouvrir(QString fichierBase);
    bool estOuvert();

    /**
     * @brief Exécuter une requête de type INSERT, UPDATE ou DELETE
     * @param requete
     * @return bool
     */
    bool executer(QString requete);

    /**
     * @brief Récuperer un champ d'un enregistrement
     * @param requete SELECT
     * @param donnees
     * @return bool
     */
    bool recuperer(QString requete, QString& donnees);
    /**
     * @brief Récuperer plusieurs champs d'un enregistrement
     * @param requete SELECT
     * @param donnees
     * @return bool
     */
    bool recuperer(QString requete, QStringList& donnees);
    /**
     * @brief Récuperer un champs de plusieurs enregistrements
     * @param requete SELECT
     * @param donnees
     * @return bool
     */
    bool recuperer(QString requete, QVector<QString>& donnees);
    /**
     * @brief Récuperer plusieurs champs de plusieurs enregistrements
     * @param requete SELECT
     * @param donnees
     * @return bool
     */
    bool recuperer(QString requete, QVector<QStringList>& donnees);

  signals:

  public slots:
};

#endif // BASEDEDONNEE_H
