/**
 * @file AdaptateurSalle.java
 * @brief Lien entre les données et les vues (RecyclerView)
 * @author Mercklen Jérémy
 */

package com.lasalle.eco_classroom_mobile;

import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.util.Vector;

/**
 * @class AdaptateurSalle
 * @brief Lien entre les données et les vues (RecyclerView)
 */
public class AdaptateurSalle extends RecyclerView.Adapter<VueSalle>
{
    /**
     * Constantes
     */
    private static final String TAG = "_AdaptateurSalle_"; //!< TAG pour les logs (cf. Logcat)

    /**
     * Attributs
     */
    private Vector<Salle> salles = null;

    /**
     * @brief Constructeur d'initialisation
     */
    public AdaptateurSalle(Vector<Salle> salles)
    {
        Log.d(TAG, "AdaptateurSalle(Vector<Salle> salles)");
        if(salles != null)
        {
            this.salles = salles;
        }
    }

    /**
     * @brief Méthode appelée à la création de l'activité
     */
    @NonNull
    @Override
    public VueSalle onCreateViewHolder(@NonNull ViewGroup parent, int viewType)
    {
        LayoutInflater inflater = LayoutInflater.from(parent.getContext());
        View           view     = inflater.inflate(R.layout.salle, parent, false);
        return new VueSalle(view);
    }

    @Override
    public void onBindViewHolder(@NonNull VueSalle holder, int position)
    {
        Salle salle = salles.get(position);
        holder.afficher(salle);
    }

    @Override
    public int getItemCount()
    {
        if(salles != null)
            return salles.size();
        return 0;
    }
}
