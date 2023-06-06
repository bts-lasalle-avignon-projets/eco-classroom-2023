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
import androidx.swiperefreshlayout.widget.SwipeRefreshLayout;

import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Spinner;
import android.widget.Toast;

import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallbackExtended;
import org.eclipse.paho.client.mqttv3.MqttMessage;

import java.util.Vector;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

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
    // Les filtres
    private static final int TOUTES = 0; //!< la position de "Toutes" dans la liste déroulante
    private static final int SALLES_LIBRES = 1; //!< choix du filtre des salles "Libres"
    private static final int DEPASSEMENT_DE_SEUIL =
      2; //!< choix du filtre des salles "Dépassement de seuil"
    private static final int INTERVENTION = 3; //!< choix du filtre des salles "Intervention"

    /**
     * Attributs
     */
    private Vector<Salle>       salles          = null;     //!< les salles
    private Vector<Salle>       sallesAffichees = null;     //!< les salles à afficher
    private BaseDeDonnees       baseDeDonnees;              //!< accès à la base de données
    private ClientMQTT          clientMQTT;                 //!< permet la connexion MQTT
    private Handler             handler             = null; //<! le handler utilisé par l'activité
    private NotificationManager notificationManager = null; //<! le gestionnaire de notifications
    private int                 idNotification      = 1;    //<! l'identifiant de notification
    private int                 choixFiltrage       = TOUTES; //<! le choix de filtrage des salles

    /**
     * Ressources GUI
     */
    private RecyclerView               vueSalles;              //!< la vue
    private RecyclerView.Adapter       adaptateurSalle = null; //!< l'adaptateur
    private RecyclerView.LayoutManager layoutVueSalles;        //!< le gestionnaire de mise en page
    private SwipeRefreshLayout         actualisationSalles;    //!< le pull to refresh

    /**
     * @brief Méthode appelée à la création de l'activité
     */
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.ecoclassroom);
        Log.d(TAG, "onCreate()");

        initialiserActualisationSalles();
        initialiserHandler();
        initialiserVueSalles();
        initialiserBaseDeDonnees();
        initialiserMQTT();
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
     * @brief Méthode permettant de mettre à jour les données des salles avec un pull to refresh
     */
    private void initialiserActualisationSalles()
    {
        /**
         * @todo Modifier pour mettre à jour que les indices
         */
        actualisationSalles = (SwipeRefreshLayout)findViewById(R.id.swipeRefreshLayout);
        actualisationSalles.setOnRefreshListener(new SwipeRefreshLayout.OnRefreshListener() {
            @Override
            public void onRefresh()
            {
                chargerSalles();
                actualisationSalles.setRefreshing(false);
                for(int i = 0; i < salles.size(); i++)
                    recevoirDonneesSalle(salles.elementAt(i));
            }
        });
    }

    /**
     * @brief Méthode permettant d'initialiser les attributs pour RecyclerView
     */
    private void initialiserVueSalles()
    {
        this.salles          = new Vector<Salle>();
        this.sallesAffichees = new Vector<Salle>();
        vueSalles            = (RecyclerView)findViewById(R.id.listeSalles);
        vueSalles.setHasFixedSize(true);

        layoutVueSalles = new LinearLayoutManager(this);
        vueSalles.setLayoutManager(layoutVueSalles);

        initialiserListeDeroulante();
    }

    /**
     * @brief Méthode permettant de mettre à jours les mesures et états de la salle
     * @param salle La salle dont on veut les mesures et états
     */
    void recevoirDonneesSalle(Salle salle)
    {
        String donneesSalle;
    }

    /**
     * @brief Mutateur de l'attribut salles
     * @param salles Les salles
     */
    public void setSalles(Vector<Salle> salles)
    {
        this.salles.clear();
        this.salles.addAll(salles);
    }

    /**
     * @brief Méthode permettant d'afficher les salles dans les logs
     * @param salles Les salles
     */
    public void afficherSalles(Vector<Salle> salles)
    {
        Log.d(TAG, "afficherSalles() Nb salles = " + salles.size());
        this.sallesAffichees.clear();
        this.sallesAffichees.addAll(salles);
        if(this.adaptateurSalle == null)
        {
            adaptateurSalle = new AdaptateurSalle(this.sallesAffichees);
            vueSalles.setAdapter(adaptateurSalle);
        }
        // Force le rafraichissement de la liste des salles
        this.adaptateurSalle.notifyDataSetChanged();
    }

    /**
     * @brief Méthode permettant d'effacer l'affichage des salles
     */
    public void effacerSalles()
    {
        this.sallesAffichees.clear();
        if(this.adaptateurSalle != null)
        {
            // Force le rafraichissement de la liste des salles
            this.adaptateurSalle.notifyDataSetChanged();
        }
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
     * @brief Méthode qui permet de filtrer les salles à afficher
     */
    public void filtrerSalles(int choix)
    {
        if(salles != null)
            Log.d(TAG,
                  "filtrerSalles() choix : " + choix + " Nb salles totales  : " + salles.size());
        if(salles == null || salles.size() == 0)
            return;
        Vector<Salle> sallesFiltrees = new Vector<Salle>();
        switch(choix)
        {
            case TOUTES:
                sallesFiltrees.addAll(salles);
                break;
            case SALLES_LIBRES:
                for(int indice = 0; indice < salles.size(); indice++)
                {
                    Salle salle = salles.get(indice);
                    if(!salle.getEstOccupe())
                        sallesFiltrees.add(salle);
                }
                break;
            case DEPASSEMENT_DE_SEUIL:
                for(int indice = 0; indice < salles.size(); indice++)
                {
                    Salle salle = salles.get(indice);
                    if(salle.estSeuilTemperatureDepasse() || salle.estSeuilHumiditeDepasse() ||
                       salle.estSeuilCo2Depasse())
                        sallesFiltrees.add(salle);
                }
                break;
            case INTERVENTION:
                for(int indice = 0; indice < salles.size(); indice++)
                {
                    Salle salle = salles.get(indice);
                    if((salle.getEtatFenetre() || salle.getEtatLumiere()) && !salle.getEstOccupe())
                        sallesFiltrees.add(salle);
                }
                break;
            default:
                return;
        }
        Log.d(TAG,
              "filtrerSalles() choix : " + choix +
                " Nb salles filtrées : " + sallesFiltrees.size());
        afficherSalles(sallesFiltrees);
    }

    private void initialiserMQTT()
    {
        clientMQTT = new ClientMQTT(getApplicationContext(), handler);
        if(clientMQTT != null)
        {
            clientMQTT.connecter();
        }
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
                // Log.d(TAG, "[Handler] message = " + message.obj.toString());

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
                        setSalles((Vector<Salle>)message.obj);
                        afficherSalles((Vector<Salle>)message.obj);
                        filtrerSalles(choixFiltrage);
                        alerterDepassementSeuil();
                    case ClientMQTT.BROKER_CONNECTE:
                        Log.d(TAG, "[Handler] BROKER_CONNECTE");
                        clientMQTT.souscrire(ClientMQTT.TOPIC_ECOCLASSROOM);
                        /**
                         * @todo Signaler la connexion au broker dans l'IHM
                         */
                        break;
                    case ClientMQTT.BROKER_DECONNECTE:
                        Log.d(TAG, "[Handler] BROKER_DECONNECTE");
                        /**
                         * @todo Signaler la déconnexion au broker dans l'IHM
                         */
                        break;
                    case ClientMQTT.BROKER_MESSAGE:
                        Log.d(TAG, "[Handler] BROKER_MESSAGE");
                        Bundle bundle      = (Bundle)message.obj;
                        String topicMQTT   = bundle.getString("topic");
                        String messageMQTT = bundle.getString("message");
                        Log.d(TAG, "[Handler] " + topicMQTT + " -> " + messageMQTT);
                        /**
                         * @todo Gérer les messages MQTT reçus
                         */
                        traiterMessageMQTT(topicMQTT, messageMQTT);
                        break;
                    case ClientMQTT.BROKER_ERREUR:
                        Log.d(TAG, "[Handler] BROKER_ERREUR");
                        /**
                         * @todo Signaler l'erreur dû au broker dans l'IHM
                         */
                        break;
                }
            }
        };
    }

    /**
     * @brief Méthode permettant d'initialiser la liste déroulante (spinner)
     */
    public void initialiserListeDeroulante()
    {
        Spinner                    listeDeroulante = (Spinner)findViewById(R.id.choixFiltre);
        ArrayAdapter<CharSequence> adaptateur =
          ArrayAdapter.createFromResource(this,
                                          R.array.listeChoix,
                                          android.R.layout.simple_spinner_item);
        adaptateur.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        listeDeroulante.setAdapter(adaptateur);

        listeDeroulante.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> adaptateur, View vue, int position, long id)
            {
                choixFiltrage = position;
                filtrerSalles(position);
            }
            @Override
            public void onNothingSelected(AdapterView<?> arg0)
            {
            }
        });
    }

    /**
     * @brief Méthode permettant de mettre les données MQTT recue dans les salles
     */
    public void traiterMessageMQTT(String topicMQTT, String messageMQTT)
    {
        String nomSalle   = null;
        String typeModule = null;
        String grandeur   = null;

        Pattern topicPattern = Pattern.compile("(.+?)/(.+?)/(.+?)/(.+)");
        Matcher topicMatcher = topicPattern.matcher(topicMQTT);
        if(topicMatcher.find())
        {
            nomSalle   = topicMatcher.group(2);
            typeModule = topicMatcher.group(3);
            grandeur   = topicMatcher.group(4);
            Log.d(TAG,
                  "nomSalle : " + nomSalle + "; typeModule : " + typeModule +
                    "; grandeur : " + grandeur);
        }

        Salle.Grandeur g = Salle.retournerGrandeur(grandeur);
        for(int i = 0; i < salles.size(); ++i)
        {
            Log.d(TAG,
                  "salle : " + salles.elementAt(i).getNom() + "; nomSalle : " + nomSalle +
                    "; meme nom : " + (nomSalle.compareTo(salles.elementAt(i).getNom()) == 0));
            if(nomSalle.compareTo(salles.elementAt(i).getNom()) == 0)
            {
                switch(g)
                {
                    case TEMPERATURE:
                        salles.elementAt(i).setTemperature(Double.valueOf(messageMQTT));
                        this.adaptateurSalle.notifyDataSetChanged();
                        Log.d(TAG,
                              "salle : " + salles.elementAt(i).getNom() +
                                "; temperature : " + salles.elementAt(i).getTemperature());
                        break;
                    case HUMIDITE:
                        salles.elementAt(i).setHumidite(Integer.valueOf(messageMQTT));
                        this.adaptateurSalle.notifyDataSetChanged();
                        break;
                    case CO2:
                        salles.elementAt(i).setCo2(Integer.valueOf(messageMQTT));
                        this.adaptateurSalle.notifyDataSetChanged();
                        break;
                    case PRESENCE:
                        if(messageMQTT.compareTo("0") == 0)
                            salles.elementAt(i).setEstOccupe(false);
                        else
                            salles.elementAt(i).setEstOccupe(true);
                        this.adaptateurSalle.notifyDataSetChanged();
                        break;
                    case FENETRE:
                        if(messageMQTT.compareTo("0") == 0)
                            salles.elementAt(i).setEtatFenetre(false);
                        else
                            salles.elementAt(i).setEtatFenetre(true);
                        this.adaptateurSalle.notifyDataSetChanged();
                        break;
                    case LUMIERE:
                        if(messageMQTT.compareTo("0") == 0)
                            salles.elementAt(i).setEtatLumiere(false);
                        else
                            salles.elementAt(i).setEtatLumiere(true);
                        this.adaptateurSalle.notifyDataSetChanged();
                        break;
                }
            }
        }
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
            if(salle.estSeuilTemperatureDepasse())
            {
                notifierDepassement(salle, DEPASSEMENT_TEMPERATURE);
            }
            if(salle.estSeuilHumiditeDepasse())
            {
                notifierDepassement(salle, DEPASSEMENT_HUMIDITE);
            }
            if(salle.estSeuilCo2Depasse())
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
