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

public class ClientMQTT
{
    private static final String TAG = "ClientMQTT";
    Context                     context;
    private Handler             handler           = null; // pour la communication entre classes
    public MqttAndroidClient    mqttAndroidClient = null;
    String                      serverUri         = "tcp://192.168.52.7:1883";
    String                      clientId          = "client";
    String                      username          = "";
    String                      password          = "";

    public ClientMQTT(Context context, Handler handler)
    {
        this.context = context;
        this.handler = handler;

        creer();
        // connecter();
    }

    public void creer()
    {
        Log.w(TAG, "MqttAndroidClient.creer : serverUri -> " + serverUri);
        mqttAndroidClient = new MqttAndroidClient(context, serverUri, clientId);
        mqttAndroidClient.setCallback(new MqttCallbackExtended() {
            @Override
            public void connectComplete(boolean b, String s)
            {
                Log.w(TAG, "MqttAndroidClient : connectComplete -> " + s + " (" + b + ")");
            }

            @Override
            public void connectionLost(Throwable throwable)
            {
                Log.w(TAG, "MqttAndroidClient : connectionLost");
            }

            @Override
            public void messageArrived(String topic, MqttMessage mqttMessage) throws Exception
            {
                Log.w(TAG, "MqttAndroidClient : messageArrived -> " + mqttMessage.toString());
                Message message = Message.obtain();
                Log.d(TAG, "message : " + message);
                handler.sendMessage(message);
            }

            @Override
            public void deliveryComplete(IMqttDeliveryToken iMqttDeliveryToken)
            {
                Log.w(TAG, "MqttAndroidClient : deliveryComplete");
            }
        });
    }

    public void connecter()
    {
        if(estConnecte())
            deconnecter();
        Log.w(TAG, "MqttAndroidClient : connecter() serverUri -> " + serverUri);
        MqttConnectOptions mqttConnectOptions = new MqttConnectOptions();
        mqttConnectOptions.setAutomaticReconnect(true);
        mqttConnectOptions.setCleanSession(false);
        // mqttConnectOptions.setUserName(username);
        // mqttConnectOptions.setPassword(password.toCharArray());

        try
        {
            mqttAndroidClient.connect(mqttConnectOptions, null, new IMqttActionListener() {
                @Override
                public void onSuccess(IMqttToken asyncActionToken)
                {
                    Log.w(TAG, "connecter : onSuccess");
                    DisconnectedBufferOptions disconnectedBufferOptions =
                      new DisconnectedBufferOptions();
                    disconnectedBufferOptions.setBufferEnabled(true);
                    disconnectedBufferOptions.setBufferSize(100);
                    disconnectedBufferOptions.setPersistBuffer(false);
                    disconnectedBufferOptions.setDeleteOldestMessages(false);
                    mqttAndroidClient.setBufferOpts(disconnectedBufferOptions);
                }

                @Override
                public void onFailure(IMqttToken asyncActionToken, Throwable exception)
                {
                    Log.w(TAG, "connecter : onFailure -> " + serverUri + exception.toString());
                }
            });
        }
        catch(MqttException ex)
        {
            ex.printStackTrace();
            Log.e(TAG, "connecter : exception");
        }
    }

    public void deconnecter()
    {
        Log.w(TAG, "MqttAndroidClient : deconnecter");
        Thread deconnexion = new Thread(new Runnable() {
            public void run()
            {
                try
                {
                    mqttAndroidClient.disconnect();
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
        Log.w(TAG, "MqttAndroidClient : estConnecte -> " + mqttAndroidClient.isConnected());
        return mqttAndroidClient.isConnected();
    }

    public void souscrire()
    {
        String topic = "salles/#";
        try
        {
            mqttAndroidClient
              .subscribe(topic, 0, null, new IMqttActionListener() {
                  @Override
                  public void onSuccess(IMqttToken asyncActionToken)
                  {
                      Log.w(TAG, "souscrire : onSuccess");
                      Log.d(TAG, "topic : " + topic);
                  }

                  @Override
                  public void onFailure(IMqttToken asyncActionToken, Throwable exception)
                  {
                      Log.w(TAG, "souscrire : onFailure");
                  }
              });
        }
        catch(MqttException ex)
        {
            Log.e(TAG, "souscrire : exception");
            ex.printStackTrace();
        }
    }
}