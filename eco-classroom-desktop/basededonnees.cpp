#include "basededonnees.h"
#include <QDebug>
#include <QMessageBox>

/**
 * @file BaseDeDonnees.cpp
 * @brief Définition de la classe BaseDeDonnees
 * @author Thierry VAIRA
 * @version 0.1
 */

BaseDeDonnees* BaseDeDonnees::bdd     = nullptr;
int            BaseDeDonnees::nbAcces = 0;

/**
 * @brief Définition du constructeur par défaut de la classe BaseDeDonnees
 * @fn BaseDeDonnees::BaseDeDonnees
 * @details Initialise le type MySQL pour la connexion à la base de données
 */
BaseDeDonnees::BaseDeDonnees()
{
#ifdef DEBUG_BDD
    qDebug() << Q_FUNC_INFO;
#endif
    db = QSqlDatabase::addDatabase("QMYSQL");
}

/**
 * @brief Définition du destructeur de la classe BaseDeDonnees
 * @fn BaseDeDonnees::~BaseDeDonnees
 * @details Destructeur de la classe BaseDeDonnees
 */
BaseDeDonnees::~BaseDeDonnees()
{
#ifdef DEBUG_BDD
    qDebug() << Q_FUNC_INFO;
#endif
}

/**
 * @brief Définition méthode getInstance()
 * @fn BaseDeDonnees::getInstance
 * @details Permet l'instanciation d'un objet BaseDeDonnees en vérifiant qu'il
 * n'en existe pas déja un
 * @return BaseDeDonnees l'instance unique
 */
BaseDeDonnees* BaseDeDonnees::getInstance()
{
    if(bdd == nullptr)
        bdd = new BaseDeDonnees();
    nbAcces++;
#ifdef DEBUG_BDD
    qDebug() << Q_FUNC_INFO << "nbAcces" << nbAcces;
#endif

    return bdd;
}

/**
 * @brief Définition méthode detruireInstance()
 * @fn BaseDeDonnees::detruireInstance
 * @details Détruit l'instance de la BaseDeDonnees si elle existe et si personne
 * l'utilise
 */
void BaseDeDonnees::detruireInstance()
{
    if(bdd != nullptr)
    {
        nbAcces--;
#ifdef DEBUG_BDD
        qDebug() << Q_FUNC_INFO << "nbAcces" << nbAcces;
#endif
        if(nbAcces == 0)
            delete bdd;
    }
}

/**
 * @brief Définition méthode connecter()
 * @fn BaseDeDonnees::connecter
 * @details Permet de se connecter à la base de données
 * @param[in] nomBase le nom de la base de données MySQL
 * @param[in] username l'identifiant d'accès à la base de données
 * @param[in] password le mot de passe d'accès à la base de données
 * @param[in] serveur l'adresse du serveur MySQL
 * @return bool
 */
bool BaseDeDonnees::connecter(QString nomBase /*=DATABASENAME*/,
                              QString username /*=USERNAME*/,
                              QString password /*=PASSWORD*/,
                              QString serveur /*=HOSTNAME*/)
{
    if(!db.isOpen())
    {
        db.setHostName(serveur);
        db.setUserName(username);
        db.setPassword(password);
        db.setDatabaseName(nomBase);

#ifdef DEBUG_BDD
        qDebug() << Q_FUNC_INFO << "HostName" << db.hostName();
        qDebug() << Q_FUNC_INFO << "UserName" << db.userName();
        qDebug() << Q_FUNC_INFO << "DatabaseName" << db.databaseName();
#endif
        if(db.open())
        {
#ifdef DEBUG_BDD
            qDebug()
              << Q_FUNC_INFO
              << QString::fromUtf8("connexion réussie à %1").arg(db.hostName());
#endif

            return true;
        }
        else
        {
            qDebug() << Q_FUNC_INFO
                     << QString::fromUtf8("Erreur : impossible de se connecter "
                                          "à la base de données !");
            QMessageBox::critical(
              nullptr,
              QString::fromUtf8("BaseDeDonnees"),
              QString::fromUtf8(
                "Impossible de se connecter à la base de données !"));
            return false;
        }
    }
    else
        return true;
}

/**
 * @brief Retourne l'état de connexion à la base de données
 * @fn BaseDeDonnees::estConnectee
 * @details Retourne l'état de connexion à la base de données
 * @return bool true si la base de données est connectée sinon false
 */
bool BaseDeDonnees::estConnectee()
{
    return db.isOpen();
}

/**
 * @brief Exécute une requête SQL de type UPDATE, INSERT et DELETE
 * @fn bool BaseDeDonnees::executer(QString requete)
 * @details Exécute une requête SQL de type UPDATE, INSERT et DELETE
 * @param[in] requete une requête SQL de type UPDATE, INSERT et DELETE
 * @return bool true si la requête a été exécutée avec succès sinon false
 */
bool BaseDeDonnees::executer(QString requete)
{
    QSqlQuery r;
    bool      retour;

    if(db.isOpen())
    {
        if(requete.contains("UPDATE") || requete.contains("INSERT") ||
           requete.contains("DELETE"))
        {
            retour = r.exec(requete);
#ifdef DEBUG_BDD
            qDebug() << Q_FUNC_INFO
                     << QString::fromUtf8("Retour %1 pour la requete : %2")
                          .arg(QString::number(retour))
                          .arg(requete);
#endif
            if(retour)
            {
                return true;
            }
            else
            {
                qDebug() << Q_FUNC_INFO
                         << QString::fromUtf8("Erreur : %1 pour la requête %2")
                              .arg(r.lastError().text())
                              .arg(requete);
                return false;
            }
        }
        else
        {
            qDebug() << Q_FUNC_INFO
                     << QString::fromUtf8("Erreur : requête %1 non autorisée !")
                          .arg(requete);
            return false;
        }
    }
    else
        return false;
}

/**
 * @brief Exécute une requête SQL de type SELECT et récupère un champ d'un seul
 * enregistrement
 * @fn bool BaseDeDonnees::recuperer(QString requete, QString &donnees)
 * @param[in] requete une requête SQL de type SELECT
 * @param[out] donnees le champ QString récupéré
 * @return bool true si la requête a été exécutée avec succès sinon false
 */
bool BaseDeDonnees::recuperer(QString requete, QString& donnees)
{
    QSqlQuery r;
    bool      retour;

    if(db.isOpen())
    {
        if(requete.contains("SELECT"))
        {
            retour = r.exec(requete);
#ifdef DEBUG_BDD
            qDebug() << Q_FUNC_INFO
                     << QString::fromUtf8("Retour %1 pour la requete : %2")
                          .arg(QString::number(retour))
                          .arg(requete);
#endif
            if(retour)
            {
                // on se positionne sur l'enregistrement
                r.first();

                // on vérifie l'état de l'enregistrement retourné
                if(!r.isValid())
                {
#ifdef DEBUG_BDD
                    qDebug() << Q_FUNC_INFO
                             << QString::fromUtf8("Résultat non valide !");
#endif
                    return false;
                }

                // on récupère sous forme de QString la valeur du champ
                if(r.isNull(0))
                {
#ifdef DEBUG_BDD
                    qDebug()
                      << Q_FUNC_INFO << QString::fromUtf8("Aucun résultat !");
#endif
                    return false;
                }
                donnees = r.value(0).toString();
#ifdef DEBUG_BDD
                qDebug() << Q_FUNC_INFO << "Enregistrement -> " << donnees;
#endif
                return true;
            }
            else
            {
                qDebug() << Q_FUNC_INFO
                         << QString::fromUtf8("Erreur : %1 pour la requête %2")
                              .arg(r.lastError().text())
                              .arg(requete);
                return false;
            }
        }
        else
        {
            qDebug() << Q_FUNC_INFO
                     << QString::fromUtf8("Erreur : requête %1 non autorisée !")
                          .arg(requete);
            return false;
        }
    }
    else
        return false;
}

/**
 * @brief Exécute une requête SQL de type SELECT et récupère plusieurs champs
 * d'un seul enregistrement
 * @fn bool BaseDeDonnees::recuperer(QString requete, QStringList &donnees)
 * @param[in] requete une requête SQL de type SELECT
 * @param[out] donnees plusieurs champs d'un seul enregistrement dans un
 * QStringList
 * @return bool true si la requête a été exécutée avec succès sinon false
 */
bool BaseDeDonnees::recuperer(QString requete, QStringList& donnees)
{
    QSqlQuery r;
    bool      retour;

    if(db.isOpen())
    {
        if(requete.contains("SELECT"))
        {
            retour = r.exec(requete);
#ifdef DEBUG_BDD
            qDebug() << QString::fromUtf8("Retour %1 pour la requete : %2")
                          .arg(QString::number(retour))
                          .arg(requete);
#endif
            if(retour)
            {
                // on se positionne sur l'enregistrement
                r.first();

                // on vérifie l'état de l'enregistrement retourné
                if(!r.isValid())
                {
#ifdef DEBUG_BDD
                    qDebug() << Q_FUNC_INFO
                             << QString::fromUtf8("Résultat non valide !");
#endif
                    return false;
                }

                // on récupère sous forme de QString la valeur de tous les
                // champs sélectionnés et on les stocke dans une liste de
                // QString
                for(int i = 0; i < r.record().count(); i++)
                    if(!r.isNull(i))
                        donnees << r.value(i).toString();
#ifdef DEBUG_BDD
                qDebug() << Q_FUNC_INFO << "Enregistrement -> " << donnees;
#endif
                return true;
            }
            else
            {
                qDebug() << Q_FUNC_INFO
                         << QString::fromUtf8("Erreur : %1 pour la requête %2")
                              .arg(r.lastError().text())
                              .arg(requete);
                return false;
            }
        }
        else
        {
            qDebug() << Q_FUNC_INFO
                     << QString::fromUtf8("Erreur : requête %1 non autorisée !")
                          .arg(requete);
            return false;
        }
    }
    else
        return false;
}

/**
 * @brief Exécute une requête SQL de type SELECT et récupère un seul champ de
 * plusieurs enregistrements
 * @fn bool BaseDeDonnees::recuperer(QString requete, QVector<QString> &donnees)
 * @param[in] requete une requête SQL de type SELECT
 * @param[out] donnees un seul champ de plusieurs enregistrements dans un
 * QVector de QString
 * @return bool true si la requête a été exécutée avec succès sinon false
 */
bool BaseDeDonnees::recuperer(QString requete, QVector<QString>& donnees)
{
    QSqlQuery r;
    bool      retour;
    QString   data;

    if(db.isOpen())
    {
        if(requete.contains("SELECT"))
        {
            retour = r.exec(requete);
#ifdef DEBUG_BDD
            qDebug() << Q_FUNC_INFO
                     << QString::fromUtf8("Retour %1 pour la requete : %2")
                          .arg(QString::number(retour))
                          .arg(requete);
#endif
            if(retour)
            {
                // pour chaque enregistrement
                while(r.next())
                {
                    // on récupère sous forme de QString la valeur du champs
                    // sélectionné
                    data = r.value(0).toString();

#ifdef DEBUG_BDD
// qDebug() << Q_FUNC_INFO << "Enregistrement -> " << data;
#endif

                    // on stocke l'enregistrement dans le QVector
                    donnees.push_back(data);
                }
#ifdef DEBUG_BDD
                qDebug() << Q_FUNC_INFO << "Enregistrement -> " << donnees;
#endif
                return true;
            }
            else
            {
                qDebug() << Q_FUNC_INFO
                         << QString::fromUtf8("Erreur : %1 pour la requête %2")
                              .arg(r.lastError().text())
                              .arg(requete);
                return false;
            }
        }
        else
        {
            qDebug() << Q_FUNC_INFO
                     << QString::fromUtf8("Erreur : requête %1 non autorisée !")
                          .arg(requete);
            return false;
        }
    }
    else
        return false;
}

/**
 * @brief Exécute une requête SQL de type SELECT et récupère plusieurs champs de
 * plusieurs enregistrements
 * @param[in] requete une requête SQL de type SELECT
 * @param[out] donnees : plusieurs champs de plusieurs enregistrements dans un
 * QVector de QStringList
 * @return bool true si la requête a été exécutée avec succès sinon false
 */
bool BaseDeDonnees::recuperer(QString requete, QVector<QStringList>& donnees)
{
    QSqlQuery   r;
    bool        retour;
    QStringList data;

    if(db.isOpen())
    {
        if(requete.contains("SELECT"))
        {
            retour = r.exec(requete);
#ifdef DEBUG_BDD
            qDebug() << Q_FUNC_INFO
                     << QString::fromUtf8("Retour %1 pour la requete : %2")
                          .arg(QString::number(retour))
                          .arg(requete);
#endif
            if(retour)
            {
                // pour chaque enregistrement
                while(r.next())
                {
                    // on récupère sous forme de QString la valeur de tous les
                    // champs sélectionnés et on les stocke dans une liste de
                    // QString
                    for(int i = 0; i < r.record().count(); i++)
                        data << r.value(i).toString();

#ifdef DEBUG_BDD
// qDebug() << Q_FUNC_INFO << "Enregistrement -> " << data;
/*for(int i=0;i<r.record().count();i++)
    qDebug() << r.value(i).toString();*/
#endif

                    // on stocke l'enregistrement dans le QVector
                    donnees.push_back(data);

                    // on efface la liste de QString pour le prochain
                    // enregistrement
                    data.clear();
                }
#ifdef DEBUG_BDD
                qDebug() << Q_FUNC_INFO << "Enregistrement -> " << donnees;
#endif
                return true;
            }
            else
            {
                qDebug() << Q_FUNC_INFO
                         << QString::fromUtf8("Erreur : %1 pour la requête %2")
                              .arg(r.lastError().text())
                              .arg(requete);
                return false;
            }
        }
        else
        {
            qDebug() << Q_FUNC_INFO
                     << QString::fromUtf8("Erreur : requête %1 non autorisée !")
                          .arg(requete);
            return false;
        }
    }
    else
        return false;
}
