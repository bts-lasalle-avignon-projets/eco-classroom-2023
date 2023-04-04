#ifndef BASEDEDONNEES_H
#define BASEDEDONNEES_H

/**
 * @file basededonnees.h
 * @brief Déclaration de la classe BaseDeDonnees
 * @author Thierry VAIRA
 * @version 0.1
 */

#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>

//#define DEBUG_BDD

/**
 * @def INTERNET_BDD
 * @brief À définir pour l'accès distant à la base de données
 */
#define INTERNET_BDD

/**
 * @def HOSTNAME
 * @brief Définit l'adresse du serveur MySQL
 */
#ifdef INTERNET_BDD
#define HOSTNAME "www.db4free.net"
#else
#define HOSTNAME "192.168.52.7"
#endif
/**
 * @def USERNAME
 * @brief Définit le nom d'utilisateur par défaut
 */
#define USERNAME "ecoclassroom"
/**
 * @def PASSWORD
 * @brief Définit le mot de passe par défaut
 */
#define PASSWORD "ecoclassroom"
/**
 * @def DATABASENAME
 * @brief Définit le nom de la base de données par défaut
 */
#define DATABASENAME "ecoclassroom"

/**
 * @class BaseDeDonnees
 * @brief Déclaration de la classe permettant l'accès à la base de données MySQL
 * @see https://fr.wikipedia.org/wiki/Singleton_(patron_de_conception)
 * @author Thierry VAIRA
 * @version 0.1
 */
class BaseDeDonnees
{
  public:
    static BaseDeDonnees* getInstance();
    static void           detruireInstance();

    bool connecter(QString nomBase  = DATABASENAME,
                   QString username = USERNAME,
                   QString password = PASSWORD,
                   QString serveur  = HOSTNAME);
    bool estConnectee();

    /* uniquement pour les requêtes UPDATE, INSERT et DELETE */
    bool executer(QString requete);

    /* uniquement pour les requêtes SELECT */
    bool recuperer(QString requete, QString& donnees);          // 1 -> 1
    bool recuperer(QString requete, QStringList& donnees);      // 1 -> 1..*
    bool recuperer(QString requete, QVector<QString>& donnees); // 1..* -> 1
    bool recuperer(QString               requete,
                   QVector<QStringList>& donnees); // 1..* -> 1..*

  private:
    BaseDeDonnees();
    ~BaseDeDonnees();
    QSqlDatabase db; //!< pour la connexion à la base de données MySQL
    static BaseDeDonnees* bdd; //!< pointeur sur l'instance unique
    static int nbAcces; //!< compte le nombre d'accès à l'instance unique
};

#endif // BASEDEDONNEES_H
