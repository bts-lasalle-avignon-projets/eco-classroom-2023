/**
 * @file communicationmqtt.h
 * @brief Déclaration de la classe CommunicationMQTT
 */

#ifndef COMMUNICATIONMQTT_H
#define COMMUNICATIONMQTT_H

#include <QtMqtt/QtMqtt>
#include <QObject>

/**
 * @def IP_BROKER_MQTT
 * @brief L'ip du broker MQTT (raspeberry pi zero)
 */
#define IP_BROKER_MQTT "192.168.52.7"
//#define IP_BROKER_MQTT "127.0.0.1"

/**
 * @def PORT_BROKER_MQTT
 * @brief Le port par défaut du broker MQTT
 */
#define PORT_BROKER_MQTT 1883

/**
 * @def TOPIC_RACINE
 * @brief La racine des topics pour l'abonnement
 */
//#define TOPIC_RACINE       "salles/#"
#define TOPIC_SONDE_SALLES "salles/+/sonde/#"

/**
 * @class CommunicationMQTT
 * @brief Classe permettant de gérer la communication MQTT
 */
class CommunicationMQTT : public QObject
{
    Q_OBJECT
  public:
    CommunicationMQTT(QObject* parent = nullptr);
    ~CommunicationMQTT();

    QMqttClient* getClient() const;

  private:
    QMqttClient*       client;       //!< Client MQTT
    QMqttSubscription* subscription; //!< Subscription

  public slots:
    void seConnecter();
    void seDeconnecter();
    void sAbonner(QString topic);
    void demarrer();
    void arreter();
};

#endif // COMMUNICATIONMQTT_H
