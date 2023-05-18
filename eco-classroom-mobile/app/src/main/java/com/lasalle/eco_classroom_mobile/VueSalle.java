/**
 * @file VueSalle.java
 * @brief Vue affichant les salles
 * @author Mercklen Jérémy
 */

package com.lasalle.eco_classroom_mobile;

import android.app.AlertDialog;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.recyclerview.widget.RecyclerView;

/**
 * @class VueSalle
 * @brief Vue affichant les salles
 */
public class VueSalle extends RecyclerView.ViewHolder implements View.OnClickListener
{
    /**
     * Constantes
     */
    private static final String TAG = "_VueSalle_"; //!< TAG pour les logs (cf. Logcat)
    private static final float  ESPACE_ETIREMENT =
      4f; //<! constante de poids pour les paramètres du TextView dans le TableRow

    /**
     * Attributs
     */
    private Salle salle; //!< une salle

    /**
     * Ressources GUI
     */
    private TextView  nom;              //!< le nom
    private TextView  qualiteAir;       //!< la qualité d'air
    private TextView  confortThermique; //!< l'indice de confort thermique
    private ImageView etatFenetre;      //!< l'état des fenêtres (ouvertes/fermées)
    private ImageView etatLumiere;      //!< l'état des lumières (allumées/éteintes)
    private ImageView estOccupe;        //!< indique l'occupation (oui/non)

    /**
     * @brief Constructeur d'initialisation
     * @param vueSalle La vue de la salle
     */
    public VueSalle(final View vueSalle)
    {
        super(vueSalle);
        Log.d(TAG, "VueSalle(final View vueSalle)");

        initialiserWidgets(vueSalle);
        configurerElementsTexte();
        configurerElementsImage();

        itemView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View vue)
            {
                new AlertDialog.Builder(itemView.getContext())
                  .setTitle(salle.getNom())
                  .setMessage(salle.getDescription() + "\nSuperficie : " + salle.getSuperficie() +
                              "m²\nTempérature : " + salle.getTemperature() +
                              "°C\nHumidité : " + salle.getHumidite() +
                              "%\nConcentration de CO₂ : " + salle.getCo2() + "ppm")
                  .show();
            }
        });
    }

    /**
     * @brief Méthode permettant d'initialiser les widgets dans la vue
     * @param vueSalle La vue de la salle
     */
    private void initialiserWidgets(final View vueSalle)
    {
        this.nom              = ((TextView)vueSalle.findViewById(R.id.nom));
        this.qualiteAir       = ((TextView)vueSalle.findViewById(R.id.qualiteAir));
        this.confortThermique = ((TextView)vueSalle.findViewById(R.id.confortThermique));
        this.etatFenetre      = ((ImageView)vueSalle.findViewById(R.id.fenetre));
        this.etatLumiere      = ((ImageView)vueSalle.findViewById(R.id.lumiere));
        this.estOccupe        = ((ImageView)vueSalle.findViewById(R.id.presence));
    }

    /**
     * @brief Méthode permettant de configurer les TextView de l'IHM via le .java
     */
    private void configurerElementsTexte()
    {
        configurerElementTexte(this.nom);
        configurerElementTexte(this.qualiteAir);
        configurerElementTexte(this.confortThermique);
    }

    /**
     * @brief Méthode permettant de configurer les ImageView de l'IHM via le .java
     */
    private void configurerElementsImage()
    {
        configurerElementImage(this.etatFenetre);
        configurerElementImage(this.etatLumiere);
        configurerElementImage(this.estOccupe);
    }

    /**
     * @brief Méthode permettant de configurer un TextView
     * @param elementTexte l'élement de texte à modifier
     */
    private void configurerElementTexte(TextView elementTexte)
    {
        elementTexte.setGravity(Gravity.CENTER_HORIZONTAL | Gravity.CENTER_VERTICAL);
        elementTexte.setLayoutParams(
          new LinearLayout.LayoutParams(0,
                                        LinearLayout.LayoutParams.WRAP_CONTENT,
                                        ESPACE_ETIREMENT));
    }

    /**
     * @brief Méthode permettant de configurer un ImageView
     * @param elementImage L'élément de l'image à configurer
     */
    private void configurerElementImage(ImageView elementImage)
    {
        elementImage.setLayoutParams(
          new LinearLayout.LayoutParams(0,
                                        LinearLayout.LayoutParams.WRAP_CONTENT,
                                        ESPACE_ETIREMENT));
    }

    /**
     * @brief Méthode permettant d'afficher les salles sur la vue
     * @param salle La salle à afficher
     */
    public void afficher(Salle salle)
    {
        Log.d(TAG, "afficher(Salle salle) nom = " + salle.getNom());
        this.salle = salle;
        nom.setText(salle.getNom());
        if(salle.getQualiteAir() >= Salle.INDICE_QUALITE_AIR_MIN &&
           salle.getQualiteAir() <= Salle.INDICE_QUALITE_AIR_MAX)
            qualiteAir.setText(Integer.toString(salle.getQualiteAir()));
        else
            qualiteAir.setText("Inconnue");
        if(salle.getConfortThermique() >= Salle.INDICE_CONFORT_THERMIQUE_MIN &&
           salle.getConfortThermique() <= Salle.INDICE_CONFORT_THERMIQUE_MAX)
            confortThermique.setText(Integer.toString(salle.getConfortThermique()));
        else
            confortThermique.setText("Inconnu");
        if(salle.getEtatFenetre())
            etatFenetre.setImageResource(R.drawable.led_rouge);
        else
            etatFenetre.setImageResource(R.drawable.led_verte);
        if(salle.getEtatLumiere())
            etatLumiere.setImageResource(R.drawable.led_rouge);
        else
            etatLumiere.setImageResource(R.drawable.led_verte);
        if(salle.getEstOccupe())
            estOccupe.setImageResource(R.drawable.led_rouge);
        else
            estOccupe.setImageResource(R.drawable.led_verte);
    }

    /**
     * @brief Méthode permettant de gérer les clics sur les objets de la vue
     * @param vue La vue où l'événement va arriver
     */
    @Override
    public void onClick(View vue)
    {
    }
}
