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
    private static final int CONFORT_FROID = -3; //<! indice correspondant au froid pour le THI
    private static final int CONFORT_FRAIS = -2; //<! indice correspondant au frais pour le THI
    private static final int CONFORT_LEGEREMENT_FRAIS =
      -1; //<! indice correspondant au légérement frais pour le THI
    private static final int CONFORT_NEUTRE = 0; //<! indice correspondant au neutre pour le THI
    private static final int CONFORT_LEGEREMENT_TIEDE =
      1; //<! indice correspondant au légérement tiède pour le THI
    private static final int CONFORT_TIEDE    = 2; //<! indice correspondant au tiède pour le THI
    private static final int CONFORT_CHAUD    = 3; //<! indice correspondant au chaud pour le THI
    private static final int AIR_EXCELLENT    = 1;
    private static final int AIR_TRES_BIEN    = 2;
    private static final int AIR_MODERE       = 3;
    private static final int AIR_MAUVAIS      = 4;
    private static final int AIR_TRES_MAUVAIS = 5;
    private static final int AIR_SEVERE       = 6;

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
                String message = genererDonneesAffichage();
                new AlertDialog.Builder(itemView.getContext())
                  .setTitle(salle.getNom())
                  .setMessage(message)
                  .show();
            }
        });
    }

    /**
     * @brief Méthode permettant de génerer ce qu'il faut afficher dans le AlertDialog
     * @return message Le message à afficher
     */
    private String genererDonneesAffichage() {
        String message = salle.getDescription() + "\n";

        if(salle.getSuperficie() > Salle.SUPERFICIE_PAR_DEFAUT)
            message += "Superficie : " + salle.getSuperficie() + " m²\n";
        else
            message += "Superficie : non connue\n";

        if(salle.getTemperature() > Salle.TEMPERATURE_PAR_DEFAUT)
            message += "Température : " + salle.getTemperature() + " °C\n";
        else
            message += "Température : non connue\n";

        if(salle.getHumidite() > Salle.HUMIDITE_PAR_DEFAUT)
            message += "Humidité : " + salle.getHumidite() + " %\n";
        else
            message += "Humidité : non connue\n";

        if(salle.getCo2() > Salle.QUALITE_AIR_PAR_DEFAUT)
            message += "Concentration de CO₂ : " + salle.getCo2() + " ppm\n";
        else
            message += "Concentration de CO₂ : non connue\n";

        return message;
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
        qualiteAir.setText(interpreterIndiceQualiteAir(salle.getQualiteAir()));
        confortThermique.setText(interpreterIndiceConfort(salle.getConfortThermique()));
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

    /**
     * @brief Méthode renvoyant à quoi correspond l'indice de confort
     */
    public String interpreterIndiceConfort(int indice)
    {
        switch(indice)
        {
            case CONFORT_FROID:
                return "Froid";
            case CONFORT_FRAIS:
                return "Frais";
            case CONFORT_LEGEREMENT_FRAIS:
                return "Légérement frais";
            case CONFORT_NEUTRE:
                return "Neutre";
            case CONFORT_LEGEREMENT_TIEDE:
                return "Légérement tiède";
            case CONFORT_TIEDE:
                return "Tiède";
            case CONFORT_CHAUD:
                return "Chaud";
        }
        return "Inconnue";
    }

    /**
     * @brief Méthode renvoyant à quoi correspond l'indice de qualitée de l'air
     */
    public String interpreterIndiceQualiteAir(int indice)
    {
        switch(indice)
        {
            case AIR_EXCELLENT:
                return "Excellent";
            case AIR_TRES_BIEN:
                return "Très bien";
            case AIR_MODERE:
                return "Modéré";
            case AIR_MAUVAIS:
                return "Mauvais";
            case AIR_TRES_MAUVAIS:
                return "Très mauvais";
            case AIR_SEVERE:
                return "Sévère";
        }
        return "Inconnu";
    }
}
