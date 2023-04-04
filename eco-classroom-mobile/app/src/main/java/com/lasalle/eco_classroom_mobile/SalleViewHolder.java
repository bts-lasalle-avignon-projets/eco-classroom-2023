package com.lasalle.eco_classroom_mobile;

import android.util.Log;
import android.view.View;
import android.widget.TextView;

public class SalleViewHolder
{
    /**
     * Constantes
     */
    private static final String   TAG = "_SalleViewHolder_";

    /**
     * Constantes
     */
    private final TextView nom;
    private final TextView qualiteAir;
    private final TextView confortThermique;
    private final TextView fenetre;
    private final TextView lumiere;
    private final TextView presence;
    private Salle salle;

    /**
     * Ressources GUI
     */

    /**
     * @brief Constructeur d'initialisation
     */
    public SalleViewHolder(final View itemView)
    {
        Log.d(TAG, "SalleViewHolder()");
        nom = ((TextView)itemView.findViewById(R.id.nom));
        qualiteAir = ((TextView)itemView.findViewById(R.id.qualiteAir));
        confortThermique = ((TextView)itemView.findViewById(R.id.confortThermique));
        fenetre = ((TextView)itemView.findViewById(R.id.fenetre));
        lumiere = ((TextView)itemView.findViewById(R.id.lumiere));
        presence = ((TextView)itemView.findViewById(R.id.presence));
    }
}