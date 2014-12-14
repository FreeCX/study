package com.example.graph;

import android.app.Activity; 
import android.graphics.Color;
import android.graphics.drawable.AnimationDrawable;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.Button;
import android.widget.ImageView;

public class MainActivity extends Activity implements OnClickListener {
    private Button start_frame_anim; 
    private Button start_transform_anim; 
    private Button cancel_anim; 
    private ImageView animation_view;

    @Override public void onCreate( Bundle savedInstanceState ) { 
        super.onCreate( savedInstanceState ); 
        setContentView( R.layout.activity_main );
        start_frame_anim     = ( Button ) findViewById( R.id.frameAnimationStart ); 
        start_transform_anim = ( Button ) findViewById( R.id.transformAnimationStart ); 
        cancel_anim          = ( Button ) findViewById( R.id.cancelAnimation ); 
        animation_view       = ( ImageView ) findViewById( R.id.animationView );
        start_frame_anim.setOnClickListener( this ); 
        start_transform_anim.setOnClickListener( this ); 
        cancel_anim.setOnClickListener( this );
    }
    public void onClick( View v ) {
        if ( start_frame_anim.equals( v ) ) {
            animation_view.setBackgroundResource( R.anim.frame_anim ); 
            AnimationDrawable animation = ( AnimationDrawable ) animation_view.getBackground(); 
            animation.start();
        } else if ( start_transform_anim.equals( v ) ) {
            animation_view.setBackgroundResource( R.drawable.ic_launcher ); 
            Animation transform_animation = AnimationUtils.loadAnimation( this, R.anim.transform_anim );
            animation_view.startAnimation( transform_animation );
        } else if ( cancel_anim.equals( v ) ) {
            animation_view.setBackgroundColor( Color.BLACK );
        }
    }
}
