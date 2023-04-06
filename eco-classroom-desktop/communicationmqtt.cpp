/**
 * @file communicationmqtt.cpp
 * @brief Définition de la classe CommunicationMQTT
 */
#include "communicationmqtt.h"
#include <QDebug>

/**
 * @fn Communication::CommunicationMQTT
 * @brief Constructeur par défaut de la classe CommunicationMQTT
 */
CommunicationMQTT::CommunicationMQTT()
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @fn Communication::CommunicationMQTT
 * @brief Destructeur de la classe CommunicationMQTT
 */
CommunicationMQTT::~CommunicationMQTT()
{
    qDebug() << Q_FUNC_INFO;
}
