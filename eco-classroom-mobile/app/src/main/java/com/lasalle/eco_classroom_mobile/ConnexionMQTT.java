package com.lasalle.eco_classroom_mobile;

import android.util.Log;

import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;

public class ConnexionMQTT
{
    /**
     * Constantes
     */
    private static final String TAG       = "_ConnexionMQTT_";
    private static final String TOPIC     = "salles/";
    private static final String BROKER    = "tcp://192.168.52.7:1883";
    private static final String CLIENT_ID = "client";
    private static final int QOS = 2;

    /**
     * Attibuts
     */
    MemoryPersistence persistance;
    String            contenue;

    ConnexionMQTT()
    {
        persistance = new MemoryPersistence();
    }

    /*void sAbonner(String nomSalle)
    {
                try {
                    MqttClient client = new MqttClient(BROKER, CLIENT_ID, new MemoryPersistence());
                    // connect options
                    MqttConnectOptions options = new MqttConnectOptions();
                    options.setConnectionTimeout(60);
                    options.setKeepAliveInterval(60);
                    // setup callback
                    client.setCallback(new MqttCallback()
                    {

                        public void connexionPerdue(Throwable cause)
                        {
                            Log.d(TAG, "connexionPerdue: " + cause.getMessage());
                        }

                        public void messageArrive(String topic, MqttMessage message)
                        {
                            Log.d(TAG, "topic: " + topic);
                            Log.d(TAG, "Qos: " + message.getQos());
                            Log.d(TAG, "contenu du message: " + new String(message.getPayload()));

                        }

                        public void deliveryComplete(IMqttDeliveryToken token) {
                            Log.d(TAG, "deliveryComplete---------" + token.isComplete());
                        }

                    });
                    client.connect(options);
                    client.subscribe(TOPIC + nomSalle + "/#", QOS);
                }
                catch (Exception e)
                {
                    e.printStackTrace();
                }
    }*/
}
