package com.lasalle.eco_classroom_mobile;

import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.recyclerview.widget.RecyclerView;

/**
 * @class VueSalle
 * @brief Vue affichant les salles
 */
public class VueSalle extends RecyclerView.ViewHolder
{
    /**
     * Constantes
     */
    private static final String TAG = "_SalleViewHolder_"; //!< TAG pour les logs (cf. Logcat)
    private static final float  ESPACE_ETIREMENT =
      4f; //<! constante de poids pour les paramètres du TextView

    /**
     * Attributs
     */
    private Salle salle; //!< une salle

    /**
     * Ressources GUI
     */
    private TextView nom;              //!< le nom
    private TextView qualiteAir;       //!< la qualité d'air
    private TextView confortThermique; //!< l'indice de confort thermique
    private TextView etatFenetre;      //!< l'état des fenêtres (ouvertes/fermées)
    private TextView etatLumiere;      //!< l'état des lumières (allumées/éteintes)
    private TextView estOccupe;        //!< indique l'occupation (oui/non)

    /**
     * @brief Constructeur d'initialisation
     */
    public VueSalle(final View vueSalle)
    {
        super(vueSalle);
        Log.d(TAG, "SalleViewHolder(final View itemView)");

        initialiserWidgets(vueSalle);
        configurerElementsTexte();
    }

    /**
     * @brief Méthode permettant d'initialiser les widgets dans la vue
     */
    private void initialiserWidgets(final View vueSalle)
    {
        this.nom              = ((TextView)vueSalle.findViewById(R.id.nom));
        this.qualiteAir       = ((TextView)vueSalle.findViewById(R.id.qualiteAir));
        this.confortThermique = ((TextView)vueSalle.findViewById(R.id.confortThermique));
        this.etatFenetre      = ((TextView)vueSalle.findViewById(R.id.fenetre));
        this.etatLumiere      = ((TextView)vueSalle.findViewById(R.id.lumiere));
        this.estOccupe        = ((TextView)vueSalle.findViewById(R.id.presence));
    }

    /**
     * @brief Méthode permettant de configurer les TextView de l'IHM via le .java
     */
    private void configurerElementsTexte()
    {
        configurerElementTexte(this.nom);
        configurerElementTexte(this.qualiteAir);
        configurerElementTexte(this.confortThermique);
        configurerElementTexte(this.etatFenetre);
        configurerElementTexte(this.etatLumiere);
        configurerElementTexte(this.estOccupe);
    }

    /**
     * @brief Méthode permettant de configurer un TextView
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
     * @brief Méthode permettant d'afficher les salles sur les vue
     */
    public void afficher(Salle salle)
    {
        this.salle = salle;

        nom.setText(salle.getNom());
        qualiteAir.setText(Integer.toString(salle.getQualiteAir()));
        confortThermique.setText(Integer.toString(salle.getconfortThermique()));
        etatFenetre.setText(Boolean.toString(salle.getEtatFenetre()));
        etatLumiere.setText(Boolean.toString(salle.getEtatLumiere()));
        estOccupe.setText(Boolean.toString(salle.getEstOccupe()));
    }
}
