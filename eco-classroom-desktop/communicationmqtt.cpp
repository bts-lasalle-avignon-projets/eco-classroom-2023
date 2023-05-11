/**
 * @file communicationmqtt.cpp
 * @brief Définition de la classe CommunicationMQTT
 */
#include "communicationmqtt.h"
#include <QDebug>

/**
 * @fn CommunicationMQTT::CommunicationMQTT
 * @brief Constructeur par défaut de la classe CommunicationMQTT
 */
CommunicationMQTT::CommunicationMQTT(QObject* parent) : QObject(parent)
{
    qDebug() << Q_FUNC_INFO;
    client = new QMqttClient(this);
    client->setHostname(IP_BROKER_MQTT);
    client->setPort(PORT_BROKER_MQTT);

    connect(client, SIGNAL(connected()), this, SLOT(demarrer()));
    connect(client, SIGNAL(disconnected()), this, SLOT(arreter()));

    seConnecter();
}

/**
 * @fn CommunicationMQTT::CommunicationMQTT
 * @brief Destructeur de la classe CommunicationMQTT
 */
CommunicationMQTT::~CommunicationMQTT()
{
    seDeconnecter();
    qDebug() << Q_FUNC_INFO;
}

QMqttClient* CommunicationMQTT::getClient() const
{
    return client;
}

/**
 * @fn CommunicationMQTT::seConnecter
 */
void CommunicationMQTT::seConnecter()
{
    qDebug() << Q_FUNC_INFO;
    client->connectToHost();
}

/**
 * @fn CommunicationMQTT::seDeconnecter
 */
void CommunicationMQTT::seDeconnecter()
{
    qDebug() << Q_FUNC_INFO;
    client->disconnectFromHost();
}

/**
 * @fn CommunicationMQTT::sAbonner
 * @param topic
 */
void CommunicationMQTT::sAbonner(QString topic)
{
    qDebug() << Q_FUNC_INFO << "topic" << topic;
    QMqttSubscription* subscription;
    subscription = client->subscribe(topic);
    if(!subscription)
    {
        qDebug() << Q_FUNC_INFO << "erreur subscription";
        return;
    }
}

/**
 * @fn CommunicationMQTT::demarrer
 */
void CommunicationMQTT::demarrer()
{
    qDebug() << Q_FUNC_INFO;
    sAbonner(TOPIC_RACINE);
}

/**
 * @fn CommunicationMQTT::arreter
 */
void CommunicationMQTT::arreter()
{
    qDebug() << Q_FUNC_INFO;
}
