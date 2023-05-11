/**
 * @file communicationmqtt.h
 * @brief Déclaration de la classe CommunicationMQTT
 */

#ifndef COMMUNICATIONMQTT_H
#define COMMUNICATIONMQTT_H

#include <QtMqtt/QtMqtt>
#include <QObject>

#define IP_BROKER_MQTT   "192.168.52.7" //!< Constante pour l'ip du broker mqtt
#define PORT_BROKER_MQTT 1883       //!< Constante pour le port du broker mqtt
#define TOPIC_RACINE     "salles/#" //!< Constante pour le topic des salles

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
