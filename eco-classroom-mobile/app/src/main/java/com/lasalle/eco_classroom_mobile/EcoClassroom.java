/**
 * @file EcoClassroom.java
 * @brief Déclaration de l'activité principale EcoClassroom
 * @author Mercklen Jérémy
 */

package com.lasalle.eco_classroom_mobile;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.NotificationCompat;
import androidx.core.app.NotificationManagerCompat;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.annotation.SuppressLint;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.widget.Toast;

import java.util.Vector;

/**
 * @class EcoClassroom
 * @brief L'activité principale
 */
public class EcoClassroom extends AppCompatActivity
{
    /**
     * Constantes
     */
    private static final String TAG = "_EcoClassroom_"; //!< TAG pour les logs (cf. Logcat)
    private static final int    DEPASSEMENT_TEMPERATURE =
      0;                                               //!< un dépassement de seuil de température
    private static final int DEPASSEMENT_HUMIDITE = 1; //!< un dépassement de seuil d'humiditée
    private static final int DEPASSEMENT_CO2      = 2; //!< un dépassement de seuil de CO2

    /**
     * Attributs
     */
    private Vector<Salle>       salles = null;              //!< les salles
    private BaseDeDonnees       baseDeDonnees;              //!< accès à la base de données
    private Handler             handler             = null; //<! le handler utilisé par l'activité
    private NotificationManager notificationManager = null; //<! le gestionnaire de notifications
    private int                 idNotification      = 1;    //<! l'identifiant de notification

    /**
     * Ressources GUI
     */
    private RecyclerView               vueSalles;              //!< la vue
    private RecyclerView.Adapter       adaptateurSalle = null; //!< l'adaptateur
    private RecyclerView.LayoutManager layoutVueSalles;        //!< le gestionnaire de mise en page

    /**
     * @brief Méthode appelée à la création de l'activité
     */
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.ecoclassroom);
        Log.d(TAG, "onCreate()");

        initialiserHandler();
        initialiserVueSalles();
        initialiserBaseDeDonnees();
    }

    /**
     * @brief Méthode appelée au démarrage après le onCreate() ou un restart
     * après un onStop()
     */
    @Override
    protected void onStart()
    {
        super.onStart();
        Log.d(TAG, "onStart()");
    }

    /**
     * @brief Méthode appelée après onStart() ou après onPause()
     */
    @Override
    protected void onResume()
    {
        super.onResume();
        Log.d(TAG, "onResume()");
        baseDeDonnees.setHandler(handler);
        chargerSalles();
    }

    /**
     * @brief Méthode appelée après qu'une boîte de dialogue s'est affichée (on
     * reprend sur un onResume()) ou avant onStop() (activité plus visible)
     */
    @Override
    protected void onPause()
    {
        super.onPause();
        Log.d(TAG, "onPause()");
    }

    /**
     * @brief Méthode appelée lorsque l'activité n'est plus visible
     */
    @Override
    protected void onStop()
    {
        super.onStop();
        Log.d(TAG, "onStop()");
    }

    /**
     * @brief Méthode appelée à la destruction de l'application (après onStop()
     * et détruite par le système Android)
     */
    @Override
    protected void onDestroy()
    {
        super.onDestroy();
        Log.d(TAG, "onDestroy()");
    }

    /**
     * @brief Méthode permettant d'initialiser les attributs pour RecyclerView
     */
    public void initialiserVueSalles()
    {
        vueSalles = (RecyclerView)findViewById(R.id.listeSalles);
        vueSalles.setHasFixedSize(true);

        layoutVueSalles = new LinearLayoutManager(this);
        vueSalles.setLayoutManager(layoutVueSalles);
    }

    /**
     * @brief Méthode permettant d'afficher les salles dans les logs
     * @param salles Les salles
     */
    public void afficherSalles(Vector<Salle> salles)
    {
        Log.d(TAG, "afficherSalles() Nb salles = " + salles.size());
        /*
        for(int i = 0; i < salles.size(); i++)
        {
            Log.d(TAG, "afficherSalles() salle : nom = " + salles.get(i).getNom());
        }*/
        this.salles = salles;
        if(this.adaptateurSalle == null)
        {
            adaptateurSalle = new AdaptateurSalle(salles);
            vueSalles.setAdapter(adaptateurSalle);
        }
        // Force le rafraichissement de la liste des salles
        this.adaptateurSalle.notifyDataSetChanged();
    }

    /**
     * @brief Méthode permettant d'ajouter une salle dans l'attribut salles
     * @param nom Le nom de la salle
     * @param description Le type de salle
     * @param superficie La superficie de la salle en m²
     */
    public void ajouterSalle(String nom, String description, double superficie)
    {
        salles.add(new Salle(nom, superficie, description));
    }

    /**
     * @brief Méthode permettant de simuler un ajout de plusieurs salles
     */
    public void chargerSalles()
    {
        Log.d(TAG, "chargerSalles()");
        baseDeDonnees.chargerSalles();
    }

    /**
     * @brief Méthode qui permet de récupérer l'instance de BaseDeDonnees
     */
    private void initialiserBaseDeDonnees()
    {
        baseDeDonnees = BaseDeDonnees.getInstance(handler);
    }

    /**
     * @brief Initialise la gestion des messages en provenance des threads
     */
    private void initialiserHandler()
    {
        this.handler = new Handler(this.getMainLooper()) {
            @Override
            public void handleMessage(@NonNull Message message)
            {
                Log.d(TAG, "[Handler] id message = " + message.what);
                Log.d(TAG, "[Handler] message = " + message.obj.toString());

                switch(message.what)
                {
                    case BaseDeDonnees.CONNEXION_OK:
                        Log.d(TAG, "[Handler] CONNEXION_OK");
                        break;
                    case BaseDeDonnees.CONNEXION_ERREUR:
                        Log.d(TAG, "[Handler] CONNEXION_ERREUR");
                        break;
                    case BaseDeDonnees.DECONNEXION_OK:
                        Log.d(TAG, "[Handler] DECONNEXION_OK");
                        break;
                    case BaseDeDonnees.DECONNEXION_ERREUR:
                        Log.d(TAG, "[Handler] DECONNEXION_ERREUR");
                        break;
                    case BaseDeDonnees.REQUETE_SQL_OK:
                        Log.d(TAG, "[Handler] REQUETE_SQL_OK");
                        break;
                    case BaseDeDonnees.REQUETE_SQL_ERREUR:
                        Log.d(TAG, "[Handler] REQUETE_SQL_ERREUR");
                        break;
                    case BaseDeDonnees.REQUETE_SQL_SELECT_SALLES:
                        Log.d(TAG, "[Handler] REQUETE_SQL_SELECT_SALLES");
                        afficherSalles((Vector<Salle>)message.obj);
                        alerterDepassementSeuil();
                }
            }
        };
    }

    /**
     * @brief Méthode permettant de vérifier et de notifier lors d'un dépassement de seuil dans une
     * salle
     */
    public void alerterDepassementSeuil()
    {
        for(int i = 0; i < salles.size(); i++)
        {
            Log.d(TAG, "alerterDepassementSeuil() salle : " + salles.get(i).getNom());
            Salle salle = salles.get(i);
            if(salle.getTemperature() < salle.getSeuils().getTemperatureMin() ||
               salle.getTemperature() > salle.getSeuils().getTemperatureMax())
            {
                notifierDepassement(salle, DEPASSEMENT_TEMPERATURE);
            }
            if(salle.getHumidite() < salle.getSeuils().getHumiditeMin() ||
               salle.getHumidite() > salle.getSeuils().getHumiditeMax())
            {
                notifierDepassement(salle, DEPASSEMENT_HUMIDITE);
            }
            if(salle.getCo2() >= salle.getSeuils().getCo2Max())
            {
                notifierDepassement(salle, DEPASSEMENT_CO2);
            }
        }
    }

    /**
     * @brief Méthode permettant d'envoyer une notification pour alerter d'un dépassement de seuil
     * @param salle La salle où il y a un dépassement de seuil
     * @param typeDepassement Indique le type de dépassement de seuil
     */
    public void notifierDepassement(Salle salle, int typeDepassement)
    {
        Log.d(TAG,
              "alerterDepassementSeuil() salle : " + salle.getNom() + " -> " + typeDepassement);
        String titre   = "Dépassement de seuil : " + salle.getNom();
        String message = "";

        switch(typeDepassement)
        {
            case DEPASSEMENT_TEMPERATURE:
                message = "Température";
                break;
            case DEPASSEMENT_HUMIDITE:
                message = "Humidité";
                break;
            case DEPASSEMENT_CO2:
                message = "CO2";
                break;
            default:
                return;
        }

        // cf. https://developer.android.com/develop/ui/views/notifications/build-notification#java
        NotificationCompat.Builder notification =
          new NotificationCompat.Builder(this, "ecoChannelID")
            .setSmallIcon(R.drawable.ic_launcher_background)
            .setContentTitle(titre)
            .setContentText(message)
            .setPriority(NotificationCompat.PRIORITY_DEFAULT);

        // Si API26
        if(android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O)
        {
            CharSequence        name        = getString(R.string.app_name);
            String              description = "Notification EcoClassroom";
            int                 importance  = NotificationManager.IMPORTANCE_DEFAULT;
            NotificationChannel channel = new NotificationChannel("EcoClassroom", name, importance);
            channel.setDescription(description);
            // notificationManager =
            // (NotificationManager)getSystemService(Context.NOTIFICATION_SERVICE);
            notificationManager = (NotificationManager)getSystemService(NotificationManager.class);
            notificationManager.createNotificationChannel(channel);
        }
        Intent intent = new Intent(this, EcoClassroom.class);
        // intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK);
        PendingIntent pendingIntent =
          PendingIntent.getActivity(this,
                                    0,
                                    new Intent(this, EcoClassroom.class),
                                    PendingIntent.FLAG_UPDATE_CURRENT);
        // PendingIntent pendingIntent = PendingIntent.getActivity(this, 0, new Intent(this,
        // EcoClassroom.class), PendingIntent.FLAG_IMMUTABLE);
        // notification.setContentIntent(pendingIntent);
        notification.setFullScreenIntent(pendingIntent, true);
        notification.setAutoCancel(true);
        // Si API26
        if(android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O)
        {
            notificationManager.notify(idNotification++, notification.build());
        }
        else
        {
            NotificationManagerCompat.from(this).notify(idNotification++, notification.build());
            // NotificationManagerCompat.from(this).notify(typeDepassement, notification.build());
        }

        Toast toast =
          Toast.makeText(getApplicationContext(),
                         "Salle " + salle.getNom() + " : dépassement de seuil " + message,
                         Toast.LENGTH_SHORT);
        toast.show();
    }
}
