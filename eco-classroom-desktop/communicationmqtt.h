/**
 * @file communicationmqtt.h
 * @brief Déclaration de la classe CommunicationMQTT
 */

#ifndef COMMUNICATIONMQTT_H
#define COMMUNICATIONMQTT_H

#include <QtMqtt/QtMqtt>
#include <QWidget>

#define IP_BROKER_MQTT   "192.168.52.7" //!< Constante pour l'ip du broker mqtt
#define PORT_BROKER_MQTT 1883 //!< Constante pour le port du broker mqtt

/**
 * @class CommunicationMQTT
 * @brief Classe permettant de gérer la communication MQTT
 */
class CommunicationMQTT
{
  public:
    CommunicationMQTT(QWidget* parent = nullptr);
    ~CommunicationMQTT();

  private:
    QMqttClient*       client;       //!< Client MQTT
    QMqttSubscription* subscription; //!< Subscription
  public slots:
    void seConnecter();
    void seDeconnecter();
    void sAbonner(QString topic);
    void connecte();
    void deconnecte();
    void recevoirMessage(const QByteArray&     message,
                         const QMqttTopicName& topic);
};

#endif // COMMUNICATIONMQTT_H
