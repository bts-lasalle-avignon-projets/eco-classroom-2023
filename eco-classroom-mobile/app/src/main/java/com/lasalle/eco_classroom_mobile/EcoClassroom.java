/**
 * @file EcoClassroom.java
 * @brief Déclaration de l'activité principale EcoClassroom
 * @author Mercklen Jérémy
 */

package com.lasalle.eco_classroom_mobile;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

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
    private static final int DEPASSEMENT_TEMPERATURE = 0; //!< Chiffre corréspondant à un dépassement de seuil de température
    private static final int DEPASSEMENT_HUMIDITE = 1; //!< Chiffre corréspondant à un dépassement de seuil d'humiditée
    private static final int DEPASSEMENT_CO2 = 2; //!< Chiffre corréspondant à un dépassement de seuil de CO2

    /**
     * Attributs
     */
    private Vector<Salle> salles = null;  //!< les salles
    private BaseDeDonnees baseDeDonnees;  //!< accès à la base de données
    private Handler       handler = null; //<! Le handler utilisé par l'activité

    /**
     * Ressources GUI
     */
    private RecyclerView               vueSalles;       //!< la vue
    private RecyclerView.Adapter       adaptateurSalle; //!< l'adaptateur
    private RecyclerView.LayoutManager layoutVueSalles; //!< le gestionnaire de mise en page

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
        initialiserBaseDeDonnees();

        chargerSalles();
        initialiserVueSalles();
        afficherSalles();
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

        adaptateurSalle = new AdaptateurSalle(salles);
        vueSalles.setAdapter(adaptateurSalle);
    }

    /**
     * @brief Méthode permettant d'afficher les salles dans les logs
     */
    public void afficherSalles()
    {
        Log.d(TAG, "afficherSalles() Nb salles = " + salles.size());
        /*
        for(int i = 0; i < salles.size(); i++)
        {
            Log.d(TAG, "afficherSalles() salle : nom = " + salles.get(i).getNom());
        }*/
        // Force le rafraichissement de la liste des salles
        this.adaptateurSalle.notifyDataSetChanged();
    }

    /**
     * @brief Méthode permettant d'ajouter une salle dans l'attribut salles
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
        salles = baseDeDonnees.chargerSalles();
        /*
        salles = new Vector<Salle>();
        ajouterSalle("B11", "Salle de cours", 18);
        ajouterSalle("B20", "Salle de TP", 65);
        ajouterSalle("B21", "Salle de Physiques", 40);

        // Pour les tests
        for(int i = 0; i < salles.size(); i++)
        {
            if(i % 2 == 0)
                salles.get(i).setEstOccupe(true);
        }
        */
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
                        /**
                         * Exemples de requêtes
                         *
                         * baseDeDonnees.executerRequete("UPDATE Salle SET estFavori = '1'
                         * WHERE Salle.idSalle = '1'");
                         *
                         * Pour selectionner() -> réponse dans REQUETE_SQL_SELECT
                         * baseDeDonnees.selectionner("SELECT * FROM Salle");
                         */
                        afficherSalles();
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
                    case BaseDeDonnees.REQUETE_SQL_SELECT:
                        Log.d(TAG, "[Handler] REQUETE_SQL_SELECT");
                        /**
                         * Exemple de traitement d'une requête SELECT
                         *
                         * ResultSet resultatRequete = (ResultSet)message.obj;
                         * try
                         * {
                         *    while(resultatRequete.next())
                         *    {
                         *        int numero = resultatRequete.getRow();
                         *        Log.v(TAG, "[Handler] resultatRequete numéro = " + numero);
                         *    }
                         * }
                         * catch(SQLException e)
                         * {
                         *    e.printStackTrace();
                         * }
                         */
                        break;
                    case BaseDeDonnees.REQUETE_SQL_SELECT_SALLES:
                        Log.d(TAG,
                              "[Handler] REQUETE_SQL_SELECT_SALLES Nb salles = " +
                                message.obj.toString());
                        afficherSalles();
                }
            }
        };
    }

    public void depassementSeuil(Salle salle)
    {
        if(salle.getTemperature() > BaseDeDonnees.selectionner("SELECT temperatureMin FROM SeuilsAlerte") && salle.getTemperature() > BaseDeDonnees.selectionner("SELECT temperatureMax FROM SeuilsAlerte"))
        {
            notifierDepassement(salle, DEPASSEMENT_TEMPERATURE);
        }
        else if(salle.getHumidite() > BaseDeDonnees.selectionner("SELECT humiditeMin FROM SeuilsAlerte") && salle.getHumidite() > BaseDeDonnees.selectionner("SELECT humiditeMax FROM SeuilsAlerte"))
        {
            notifierDepassement(salle, DEPASSEMENT_HUMIDITE);
        }
        else if(salle.getCo2() > BaseDeDonnees.selectionner("SELECT co2Min FROM SeuilsAlerte") && salle.getHumidite() > BaseDeDonnees.selectionner("SELECT co2eMax FROM SeuilsAlerte"))
        {
            notifierDepassement(salle, DEPASSEMENT_CO2);
        }
    }

    public void notifierDepassement(Salle salle, int typeDepassement)
    {
    }
}
