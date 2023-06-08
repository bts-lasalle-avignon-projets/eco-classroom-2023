package com.lasalle.eco_classroom_mobile;

import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

import org.eclipse.paho.android.service.MqttAndroidClient;
import org.eclipse.paho.client.mqttv3.DisconnectedBufferOptions;
import org.eclipse.paho.client.mqttv3.IMqttActionListener;
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.IMqttToken;
import org.eclipse.paho.client.mqttv3.MqttCallbackExtended;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;

/**
 * @class ClientMQTT
 * @brief Classe de communication MQTT
 */
public class ClientMQTT
{
    /**
     * Constantes
     */
    private static final String TAG = "ClientMQTT";
    // public static final String BROKER             = "192.168.52.7"; // broker mosquitto
    public static final String BROKER             = "192.168.52.7";
    public static final String TOPIC_ECOCLASSROOM = "salles/#"; // par défaut
    public static final int    BROKER_CONNECTE    = 10;
    public static final int    BROKER_DECONNECTE  = 11;
    public static final int    BROKER_MESSAGE     = 12;
    public static final int    BROKER_ERREUR      = 13;
    /**
     * Attributs
     */
    Context                  context;
    private Handler          handler           = null; // pour la communication entre classes
    public MqttAndroidClient mqttAndroidClient = null;
    String                   serverUri         = "tcp://" + BROKER + ":1883";
    String                   clientId          = "client";

    public ClientMQTT(Context context, Handler handler)
    {
        Log.d(TAG, "[MqttAndroidClient] ClientMQTT() serverUri -> " + serverUri);
        this.context = context;
        this.handler = handler;

        creer();
        // connexion automatique ?
        // connecter();
    }

    public void creer()
    {
        Log.d(TAG, "[MqttAndroidClient] creer() serverUri -> " + serverUri);
        mqttAndroidClient = new MqttAndroidClient(context, serverUri, clientId);
        mqttAndroidClient.setCallback(new MqttCallbackExtended() {
            @Override
            public void connectComplete(boolean b, String s)
            {
                Log.d(TAG, "[MqttAndroidClient] connectComplete() -> " + s + " (" + b + ")");
            }

            @Override
            public void connectionLost(Throwable throwable)
            {
                Log.d(TAG, "[MqttAndroidClient] connectionLost() -> " + throwable.toString());
                Message message = new Message();
                message.what    = BROKER_DECONNECTE;
                if(handler != null)
                    handler.sendMessage(message);
            }

            @Override
            public void messageArrived(String topic, MqttMessage mqttMessage) throws Exception
            {
                Log.d(TAG,
                      "[MqttAndroidClient] messageArrived() " + topic + " -> " +
                        mqttMessage.toString());
                Message message = new Message();
                message.what    = BROKER_MESSAGE;
                Bundle b        = new Bundle();
                b.putString("topic", topic);
                b.putString("message", mqttMessage.toString());
                message.obj = b;
                if(handler != null)
                    handler.sendMessage(message);
            }

            @Override
            public void deliveryComplete(IMqttDeliveryToken iMqttDeliveryToken)
            {
                Log.d(TAG, "[MqttAndroidClient] deliveryComplete()");
            }
        });
    }

    public void connecter()
    {
        if(estConnecte())
            deconnecter();
        Log.d(TAG, "[MqttAndroidClient] connecter() serverUri -> " + serverUri);
        MqttConnectOptions mqttConnectOptions = new MqttConnectOptions();
        mqttConnectOptions.setAutomaticReconnect(true);
        mqttConnectOptions.setCleanSession(false);

        try
        {
            mqttAndroidClient.connect(mqttConnectOptions, null, new IMqttActionListener() {
                @Override
                public void onSuccess(IMqttToken asyncActionToken)
                {
                    Log.d(TAG, "[MqttAndroidClient] connecter() onSuccess");
                    DisconnectedBufferOptions disconnectedBufferOptions =
                      new DisconnectedBufferOptions();
                    disconnectedBufferOptions.setBufferEnabled(true);
                    disconnectedBufferOptions.setBufferSize(100);
                    disconnectedBufferOptions.setPersistBuffer(false);
                    disconnectedBufferOptions.setDeleteOldestMessages(false);
                    mqttAndroidClient.setBufferOpts(disconnectedBufferOptions);
                    Message message = new Message();
                    message.what    = BROKER_CONNECTE;
                    if(handler != null)
                        handler.sendMessage(message);
                }

                @Override
                public void onFailure(IMqttToken asyncActionToken, Throwable exception)
                {
                    Log.d(TAG,
                          "[MqttAndroidClient] connecter() onFailure -> " + exception.toString());
                    Message message = new Message();
                    message.what    = BROKER_ERREUR;
                    if(handler != null)
                        handler.sendMessage(message);
                }
            });
        }
        catch(MqttException ex)
        {
            Log.e(TAG, "[MqttAndroidClient] connecter() exception");
            ex.printStackTrace();
        }
    }

    public void deconnecter()
    {
        if(!estConnecte())
            return;
        Log.d(TAG, "[MqttAndroidClient] deconnecter()");
        Thread deconnexion = new Thread(new Runnable() {
            public void run()
            {
                try
                {
                    mqttAndroidClient.disconnect();
                    IMqttToken disconToken = mqttAndroidClient.disconnect();
                    disconToken.setActionCallback(new IMqttActionListener() {
                        @Override
                        public void onSuccess(IMqttToken asyncActionToken)
                        {
                            Log.d(TAG, "[MqttAndroidClient] deconnecter() onSuccess");
                            Message message = new Message();
                            message.what    = BROKER_DECONNECTE;
                            if(handler != null)
                                handler.sendMessage(message);
                        }

                        @Override
                        public void onFailure(IMqttToken asyncActionToken, Throwable exception)
                        {
                            Log.d(TAG,
                                  "[MqttAndroidClient] deconnecter() onFailure -> " +
                                    exception.toString());
                            Message message = new Message();
                            message.what    = BROKER_ERREUR;
                            if(handler != null)
                                handler.sendMessage(message);
                        }
                    });
                }
                catch(MqttException e)
                {
                    e.printStackTrace();
                    Log.e(TAG, "MqttAndroidClient : deconnecter -> exception");
                }
            }
        });
        // Démarrage
        deconnexion.start();
    }

    public boolean estConnecte()
    {
        Log.d(TAG, "[MqttAndroidClient] estConnecte() " + mqttAndroidClient.isConnected());
        return mqttAndroidClient.isConnected();
    }

    public void souscrire(String topic)
    {
        if(mqttAndroidClient == null || !mqttAndroidClient.isConnected())
            return;
        if(topic.isEmpty())
            topic = TOPIC_ECOCLASSROOM;
        Log.d(TAG, "[MqttAndroidClient] souscrire() topic -> " + topic);
        try
        {
            mqttAndroidClient.subscribe(topic, 0, null, new IMqttActionListener() {
                @Override
                public void onSuccess(IMqttToken asyncActionToken)
                {
                    Log.d(TAG, "[MqttAndroidClient] souscrire() onSuccess");
                }

                @Override
                public void onFailure(IMqttToken asyncActionToken, Throwable exception)
                {
                    Log.d(TAG,
                          "[MqttAndroidClient] souscrire() onFailure -> " + exception.toString());
                    Message message = new Message();
                    message.what    = BROKER_ERREUR;
                    if(handler != null)
                        handler.sendMessage(message);
                }
            });
        }
        catch(MqttException ex)
        {
            Log.d(TAG, "[MqttAndroidClient] souscrire() -> exception");
            ex.printStackTrace();
        }
    }

    public boolean desabonner(String topic)
    {
        if(mqttAndroidClient == null || !mqttAndroidClient.isConnected())
        {
            return false;
        }
        if(topic.isEmpty())
            topic = TOPIC_ECOCLASSROOM;
        Log.d(TAG, "[MqttAndroidClient] desabonner() topic -> " + topic);
        try
        {
            final boolean[] retour = { false };
            mqttAndroidClient.unsubscribe(topic, null, null);
            return retour[0];
        }
        catch(MqttException e)
        {
            Log.d(TAG, "[MqttAndroidClient] desabonner() exception");
            e.printStackTrace();
            return false;
        }
    }
}