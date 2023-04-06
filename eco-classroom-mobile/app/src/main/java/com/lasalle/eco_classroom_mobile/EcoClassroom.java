/**
 * @file EcoClassroom.java
 * @brief Déclaration de l'activité principale EcoClassroom
 * @author Mercklen Jérémy
 */

package com.lasalle.eco_classroom_mobile;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.os.Bundle;
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

    /**
     * Attributs
     */
    private Vector<Salle> salles = null;

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

        chargerSalles();
        afficherSalles();

        initialiserVueSalles();
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

    public void initialiserVueSalles()
    {
        vueSalles = (RecyclerView)findViewById(R.id.listeSalles);
        vueSalles.setHasFixedSize(true);

        layoutVueSalles = new LinearLayoutManager(this);
        vueSalles.setLayoutManager(layoutVueSalles);

        adaptateurSalle = new AdaptateurSalle(salles);
        vueSalles.setAdapter(adaptateurSalle);
    }

    public void afficherSalles()
    {
        for(int i = 0; i < salles.size(); i++)
        {
            Log.d(TAG, "afficherSalles() salle : nom = " + salles.get(i).getNom());
        }
    }

    public void ajouterSalle(String nom, String description, double superficie)
    {
        salles.add(new Salle(nom, superficie, description));
    }

    public void chargerSalles()
    {
        salles = new Vector<Salle>();
        ajouterSalle("B11", "Salle de cours", 18);
        ajouterSalle("B20", "Salle de TP", 65);
        ajouterSalle("B21", "Salle de Physiques", 40);
    }
}
