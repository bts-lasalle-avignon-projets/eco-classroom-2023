package com.lasalle.eco_classroom_mobile;

import android.util.Log;
import android.view.View;
import android.widget.TextView;

import androidx.recyclerview.widget.RecyclerView;

public class SalleViewHolder extends RecyclerView.ViewHolder
{
    /**
     * Constantes
     */
    private static final String TAG = "_SalleViewHolder_";

    /**
     * Attributs
     */
    private final TextView nom;
    private final TextView qualiteAir;
    private final TextView confortThermique;
    private final TextView etatFenetre;
    private final TextView etatLumiere;
    private final TextView estOccupe;
    private Salle          salle;

    /**
     * Ressources GUI
     */

    /**
     * @brief Constructeur d'initialisation
     */
    public SalleViewHolder(final View itemView)
    {
        super(itemView);

        Log.d(TAG, "SalleViewHolder(final View itemView)");

        this.nom              = ((TextView)itemView.findViewById(R.id.nom));
        this.qualiteAir       = ((TextView)itemView.findViewById(R.id.qualiteAir));
        this.confortThermique = ((TextView)itemView.findViewById(R.id.confortThermique));
        this.etatFenetre      = ((TextView)itemView.findViewById(R.id.fenetre));
        this.etatLumiere      = ((TextView)itemView.findViewById(R.id.lumiere));
        this.estOccupe        = ((TextView)itemView.findViewById(R.id.presence));
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
        estOccupe.setText(Boolean.toString(salle.getEstOccupe()));
    }
}
