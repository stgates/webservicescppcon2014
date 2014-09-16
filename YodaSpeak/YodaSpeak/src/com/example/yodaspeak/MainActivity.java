package com.example.yodaspeak;

import android.os.Bundle;
import android.os.Handler;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;


public class MainActivity extends ActionBarActivity {
	
	static  {
		System.loadLibrary("iconv");
		System.loadLibrary("cpprest");
		System.loadLibrary("YodaSpeak");
	}
	
	private native String convertToYoda(String text);
	private native String checkGrammar(String text);
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        // Setup translate button.
        Button translateButton = (Button)findViewById(R.id.translateButton);
        translateButton.setOnClickListener(new OnClickListener() {
        	public void onClick(View v) {
        		final Handler uiHandler = new Handler();
        		
        		// This could be improved by making the convertToYoda function asynchronous.
        		Thread yodaThread = new Thread(new Runnable() {
        			@Override
        			public void run() {
        				TextView startingField = (TextView)findViewById(R.id.startingTextField);
        				final String yodaText = convertToYoda(startingField.getText().toString());
        				
        				uiHandler.post(new Runnable() {
        					
        					@Override
        					public void run() {
        						TextView yodaField = (TextView)findViewById(R.id.yodaTextField);
                				yodaField.setText(yodaText);
        					}
        				});
        			}
        		});
        		yodaThread.start();
        	}
        });
        
        // Setup ability to make grammar functionality appear.
        View yodaField = findViewById(R.id.yodaTextField);
        yodaField.setOnClickListener(new OnClickListener() {
        	public void onClick(View v) {
				// Make grammar checking visible.
				View grammarButton = findViewById(R.id.grammarButton);
				View grammarTextField = findViewById(R.id.grammarTextField);
				grammarButton.setVisibility(View.VISIBLE);
				grammarTextField.setVisibility(View.VISIBLE);
        	}
        });
        
        // Setup grammar button.
        Button grammarButton = (Button)findViewById(R.id.grammarButton);
        grammarButton.setOnClickListener(new OnClickListener() {
        	public void onClick(View v) {
        		final Handler uiHandler = new Handler();
        		
        		// This could be improved by making the checkGrammar function asynchronous.
        		Thread grammarThread = new Thread(new Runnable() {
        			@Override
        			public void run() {
        				TextView yodaTextField = (TextView)findViewById(R.id.yodaTextField);
        				final String yodaText = (String)yodaTextField.getText();
        				final String grammarText = (String)checkGrammar(yodaText);
        				
        				uiHandler.post(new Runnable() {
        					
        					@Override
        					public void run() {
        						TextView grammarTextField = (TextView)findViewById(R.id.grammarTextField);
        						grammarTextField.setText(grammarText);
        					}
        				});
        			}
        		});
        		grammarThread.start();
        	}
        });
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }
}
