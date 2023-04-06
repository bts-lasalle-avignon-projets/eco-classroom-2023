package com.lasalle.eco_classroom_mobile;

import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.util.Vector;

public class SalleAdapter extends RecyclerView.Adapter<SalleViewHolder>
{
    /**
     * Constantes
     */
    private static final String TAG = "_SalleAdapter_";

    private Vector<Salle> salles = null;

    /**
     * @brief Constructeur d'initialisation
     */
    public SalleAdapter(Vector<Salle> salles)
    {
        Log.d(TAG, "SalleAdapter(Vector<Salle> salles)");
        if(salles != null)
        {
            this.salles = salles;
        }
    }

    @NonNull
    @Override
    public SalleViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType)
    {
        LayoutInflater inflater = LayoutInflater.from(parent.getContext());
        View view = inflater.inflate(R.layout.salle, parent, false);
        return new SalleViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull SalleViewHolder holder, int position)
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
