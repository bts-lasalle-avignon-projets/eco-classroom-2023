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
CommunicationMQTT::CommunicationMQTT(QWidget* parent) : QWidget(parent)
{
    qDebug() << Q_FUNC_INFO;
    client = new QMqttClient(this);
    client->setHostname(IP_BROKER_MQTT);
    client->setPort(PORT_BROKER_MQTT);

    connect(client, SIGNAL(connected()), this, SLOT(connecte()));
    connect(client, SIGNAL(disconnected()), this, SLOT(deconnecte()));
    connect(client,
            SIGNAL(messageReceived(const QByteArray&, const QMqttTopicName&)),
            this,
            SLOT(recevoirMessage(const QByteArray&, const QMqttTopicName&)));

    seConnecter();
}

/**
 * @fn CommunicationMQTT::CommunicationMQTT
 * @brief Destructeur de la classe CommunicationMQTT
 */
CommunicationMQTT::~CommunicationMQTT()
{
    qDebug() << Q_FUNC_INFO;
    seDeconnecter();
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
    QMqttSubscription* subscription;
    subscription = client->subscribe(topic);
    if(!subscription)
    {
        qDebug() << Q_FUNC_INFO << "erreur subscription";
        return;
    }
}

/**
 * @fn CommunicationMQTT::connecte
 */
void CommunicationMQTT::connecte()
{
    qDebug() << Q_FUNC_INFO;
    sAbonner("salles/#");
}

/**
 * @fn CommunicationMQTT::deconnecte
 */
void CommunicationMQTT::deconnecte()
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @fn CommunicationMQTT::messageRecu
 * @param message
 * @param topic
 */
void CommunicationMQTT::recevoirMessage(const QByteArray&     message,
                                        const QMqttTopicName& topic)
{
    qDebug() << QDateTime::currentDateTime().toString() << topic.name()
             << message;
}
