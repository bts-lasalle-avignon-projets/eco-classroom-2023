package com.lasalle.eco_classroom_mobile;

import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.recyclerview.widget.RecyclerView;

public class VueSalle extends RecyclerView.ViewHolder
{
    /**
     * Constantes
     */
    private static final String TAG              = "_SalleViewHolder_";
    private static final float  ESPACE_ETIREMENT = 4f; //<!

    /**
     * Attributs
     */
    private TextView nom;
    private TextView qualiteAir;
    private TextView confortThermique;
    private TextView etatFenetre;
    private TextView etatLumiere;
    private TextView estOccupe;
    private Salle    salle;

    /**
     * Ressources GUI
     */

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

    private void initialiserWidgets(final View vueSalle)
    {
        this.nom              = ((TextView)vueSalle.findViewById(R.id.nom));
        this.qualiteAir       = ((TextView)vueSalle.findViewById(R.id.qualiteAir));
        this.confortThermique = ((TextView)vueSalle.findViewById(R.id.confortThermique));
        this.etatFenetre      = ((TextView)vueSalle.findViewById(R.id.fenetre));
        this.etatLumiere      = ((TextView)vueSalle.findViewById(R.id.lumiere));
        this.estOccupe        = ((TextView)vueSalle.findViewById(R.id.presence));
    }

    private void configurerElementsTexte()
    {
        configurerElementTexte(this.nom);
        configurerElementTexte(this.qualiteAir);
        configurerElementTexte(this.confortThermique);
        configurerElementTexte(this.etatFenetre);
        configurerElementTexte(this.etatLumiere);
        configurerElementTexte(this.estOccupe);
    }

    private void configurerElementTexte(TextView elementTexte)
    {
        elementTexte.setGravity(Gravity.CENTER_HORIZONTAL | Gravity.CENTER_VERTICAL);
        elementTexte.setLayoutParams(
          new LinearLayout.LayoutParams(0,
                                        LinearLayout.LayoutParams.WRAP_CONTENT,
                                        ESPACE_ETIREMENT));
    }

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
