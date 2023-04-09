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
CommunicationMQTT::CommunicationMQTT()
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @fn CommunicationMQTT::CommunicationMQTT
 * @brief Destructeur de la classe CommunicationMQTT
 */
CommunicationMQTT::~CommunicationMQTT()
{
    qDebug() << Q_FUNC_INFO;
}
