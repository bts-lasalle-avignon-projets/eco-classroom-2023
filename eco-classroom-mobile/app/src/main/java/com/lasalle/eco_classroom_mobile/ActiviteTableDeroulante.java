package com.lasalle.eco_classroom_mobile;

import android.app.Activity;
import android.view.View;
import android.widget.AdapterView;

/**
 * @class ActiviteTableDeroulante
 * @brief Gestionnaire d'événement de la table déroulante
 */
public class ActiviteTableDeroulante extends Activity implements AdapterView.OnItemSelectedListener
{
    public void onItemSelected(AdapterView<?> parent, View vue,
                               int position, long id)
    {
        parent.getItemAtPosition(position);
    }

    public void onNothingSelected(AdapterView<?> parent)
    {
    }


}
