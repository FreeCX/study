package com.example.button;

import android.app.Activity;
import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.Toast;

public class MainActivity extends Activity implements OnClickListener {
    private Button switchToGreen; 
    private Button switchToRed; 
    private Button switchToBlue; 
    private LinearLayout screenLayout; 
    private Toast informationToast;

    @Override public void onCreate( Bundle savedInstanceState ) { 
        super.onCreate( savedInstanceState );
        setContentView( R.layout.activity_main );
        // init buttons
        switchToBlue  = ( Button ) findViewById( R.id.switchBlue ); 
        switchToGreen = ( Button ) findViewById( R.id.switchGreen ); 
        switchToRed   = ( Button ) findViewById( R.id.switchRed ); 
        screenLayout  = ( LinearLayout ) findViewById( R.id.layout );
        // setup listeners
        switchToBlue.setOnClickListener( this );
        switchToRed.setOnClickListener( this );
        switchToGreen.setOnClickListener( this );
        informationToast = Toast.makeText( this, "", Toast.LENGTH_SHORT );
    }
    public void onClick( View view ) {
        if ( switchToBlue.equals( view ) ) {
            screenLayout.setBackgroundColor( Color.BLUE ); 
            show_text( "Hello from blue button!" );
        } else if ( switchToRed.equals( view ) ) {
            screenLayout.setBackgroundColor( Color.RED );
            show_text( "Hello from red button!" );
        } else if ( switchToGreen.equals( view ) ) {
            screenLayout.setBackgroundColor( Color.GREEN );
            show_text( "Hello from green button!" );
        }
    }
    private void show_text( String text ) { 
        informationToast.setText( text ); 
        informationToast.show();
    }
}
