/**
 * @file basededonnees.cpp
 * @brief Définition de la classe BaseDeDonnees
 */
#include "basededonnees.h"
#include <QDebug>
#include <QMessageBox>

BaseDeDonnees* BaseDeDonnees::baseDeDonnees = nullptr;
QString        BaseDeDonnees::typeBase      = TYPE_BDD;
int            BaseDeDonnees::nbAcces       = 0;

BaseDeDonnees::BaseDeDonnees(QString type)
{
    qDebug() << Q_FUNC_INFO << type;
    db       = QSqlDatabase::addDatabase(type);
    typeBase = type;
}

BaseDeDonnees::~BaseDeDonnees()
{
    qDebug() << Q_FUNC_INFO;
}

BaseDeDonnees* BaseDeDonnees::getInstance(QString type)
{
    if(baseDeDonnees == nullptr)
        baseDeDonnees = new BaseDeDonnees(type);

    nbAcces++;
    qDebug() << Q_FUNC_INFO << "nbAcces" << nbAcces;

    return baseDeDonnees;
}

void BaseDeDonnees::detruireInstance()
{
    if(baseDeDonnees != nullptr)
    {
        if(nbAcces > 0)
            nbAcces--;

        qDebug() << Q_FUNC_INFO << "nbAcces restants" << nbAcces;

        if(nbAcces == 0)
        {
            delete baseDeDonnees;
            baseDeDonnees = nullptr;
        }
    }
}

bool BaseDeDonnees::connecter(QString nomBase,
                              QString username,
                              QString password,
                              QString serveur)
{
    if(typeBase != "QMYSQL")
        return false;
    QMutexLocker verrou(&mutex);
    if(!db.isOpen())
    {
        db.setHostName(serveur);
        db.setUserName(username);
        db.setPassword(password);
        db.setDatabaseName(nomBase);

#ifdef DEBUG_BASEDEDONNEES
        qDebug() << Q_FUNC_INFO;
        qDebug() << "HostName : " << db.hostName();
        qDebug() << "UserName : " << db.userName();
        qDebug() << "DatabaseName : " << db.databaseName();
#endif
        if(db.open())
        {
#ifdef DEBUG_BASEDEDONNEES
            qDebug()
              << Q_FUNC_INFO
              << QString::fromUtf8("Connexion réussie à %1").arg(db.hostName());
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

bool BaseDeDonnees::estConnecte()
{
    QMutexLocker verrou(&mutex);
    return db.isOpen();
}

bool BaseDeDonnees::ouvrir(QString fichierBase)
{
    if(typeBase != "QSQLITE")
        return false;
    QMutexLocker verrou(&mutex);
    if(!db.isOpen())
    {
        db.setDatabaseName(fichierBase);

        qDebug() << Q_FUNC_INFO << db.databaseName();

        if(db.open())
        {
            qDebug() << Q_FUNC_INFO
                     << QString::fromUtf8("Ouverture réussie à %1")
                          .arg(db.databaseName());

            return true;
        }
        else
        {
            qDebug() << Q_FUNC_INFO
                     << QString::fromUtf8(
                          "Erreur : impossible d'ouvrir la base de données !");
            QMessageBox::critical(
              nullptr,
              QString::fromUtf8("BaseDeDonnees"),
              QString::fromUtf8("Impossible d'ouvrir la base de données !"));
            return false;
        }
    }
    else
        return true;
}

bool BaseDeDonnees::estOuvert()
{
    QMutexLocker verrou(&mutex);
    return db.isOpen();
}

bool BaseDeDonnees::executer(QString requete)
{
    QMutexLocker verrou(&mutex);
    QSqlQuery    r;
    bool         retour;

    if(db.isOpen())
    {
        if(requete.contains("UPDATE") || requete.contains("INSERT") ||
           requete.contains("DELETE"))
        {
            retour = r.exec(requete);
            qDebug() << Q_FUNC_INFO
                     << QString::fromUtf8("Retour %1 pour la requete : %2")
                          .arg(QString::number(retour))
                          .arg(requete);
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

bool BaseDeDonnees::recuperer(QString requete, QString& donnees)
{
    QMutexLocker verrou(&mutex);
    QSqlQuery    r;
    bool         retour;

    if(db.isOpen())
    {
        if(requete.contains("SELECT"))
        {
            retour = r.exec(requete);
            qDebug() << Q_FUNC_INFO
                     << QString::fromUtf8("Retour %1 pour la requete : %2")
                          .arg(QString::number(retour))
                          .arg(requete);
            if(retour)
            {
                r.first();

                if(!r.isValid())
                {
                    qDebug() << Q_FUNC_INFO
                             << QString::fromUtf8("Résultat non valide !");
                    return false;
                }

                if(r.isNull(0))
                {
                    qDebug()
                      << Q_FUNC_INFO << QString::fromUtf8("Aucun résultat !");
                    return false;
                }
                donnees = r.value(0).toString();
                qDebug() << Q_FUNC_INFO << "Enregistrement -> " << donnees;
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

bool BaseDeDonnees::recuperer(QString requete, QStringList& donnees)
{
    QMutexLocker verrou(&mutex);
    QSqlQuery    r;
    bool         retour;

    if(db.isOpen())
    {
        if(requete.contains("SELECT"))
        {
            retour = r.exec(requete);
            qDebug() << QString::fromUtf8(
                          "<BaseDeDonnees::recuperer(QString, QStringList)> "
                          "retour %1 pour la requete : %2")
                          .arg(QString::number(retour))
                          .arg(requete);
            if(retour)
            {
                r.first();

                if(!r.isValid())
                {
                    qDebug() << Q_FUNC_INFO
                             << QString::fromUtf8("Résultat non valide !");
                    return false;
                }

                for(int i = 0; i < r.record().count(); i++)
                    if(!r.isNull(i))
                        donnees << r.value(i).toString();
                qDebug() << Q_FUNC_INFO << "Enregistrement -> " << donnees;
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

bool BaseDeDonnees::recuperer(QString requete, QVector<QString>& donnees)
{
    QMutexLocker verrou(&mutex);
    QSqlQuery    r;
    bool         retour;
    QString      data;

    if(db.isOpen())
    {
        if(requete.contains("SELECT"))
        {
            retour = r.exec(requete);
            qDebug() << Q_FUNC_INFO
                     << QString::fromUtf8("Retour %1 pour la requete : %2")
                          .arg(QString::number(retour))
                          .arg(requete);
            if(retour)
            {
                while(r.next())
                {
                    data = r.value(0).toString();

                    qDebug() << Q_FUNC_INFO << "Enregistrement -> " << data;

                    donnees.push_back(data);
                }
                qDebug() << Q_FUNC_INFO << "Enregistrement -> " << donnees;
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

bool BaseDeDonnees::recuperer(QString requete, QVector<QStringList>& donnees)
{
    QMutexLocker verrou(&mutex);
    QSqlQuery    r;
    bool         retour;
    QStringList  data;

    if(db.isOpen())
    {
        if(requete.contains("SELECT"))
        {
            retour = r.exec(requete);
            qDebug() << Q_FUNC_INFO
                     << QString::fromUtf8("Retour %1 pour la requete : %2")
                          .arg(QString::number(retour))
                          .arg(requete);
            if(retour)
            {
                while(r.next())
                {
                    for(int i = 0; i < r.record().count(); i++)
                        data << r.value(i).toString();

                    qDebug() << Q_FUNC_INFO << "Enregistrement -> " << data;
                    for(int i = 0; i < r.record().count(); i++)
                        qDebug() << r.value(i).toString();

                    donnees.push_back(data);

                    data.clear();
                }
                qDebug() << Q_FUNC_INFO << "Enregistrement -> " << donnees;
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
