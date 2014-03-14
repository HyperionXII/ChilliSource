/**
 *  CSActivity.java
 *  ChilliSource
 *
 *  Created by Ian Copland on 14/08/2012.
 *  Copyright 2012 Tag Games. All rights reserved.
 *
 */

package com.chillisource.core;
import android.app.Activity;
import android.content.Intent;
import android.content.res.Configuration;
import android.os.Bundle;
import android.view.Window;
import android.view.WindowManager;
import com.chillisource.input.KeyboardNativeInterface;
import com.chillisource.social.ContactInformationProviderNativeInterface;
import com.chillisource.networking.HttpConnectionNativeInterface;
import com.chillisource.social.SMSCompositionNativeInterface;
import com.chillisource.core.SharedPreferencesNativeInterface;
import com.chillisource.social.TwitterAuthenticationViewNativeInterface;
import com.chillisource.web.WebViewNativeInterface;
import com.chillisource.core.CSPowerManager;

import org.fmod.FMODAudioDevice;

/**
 * The main activity for Chilli Source apps.
 * This feeds Android lifecycle events to the application
 *
 * @author I Copland
 */
public class CSActivity extends Activity 
{
	private FMODAudioDevice m_FMODAudioDevice = new FMODAudioDevice();
	private Renderer m_renderer;
	private Surface m_surface;
	
	/**
	 * Triggered when the activity is first created (i.e. on app launch).
	 * 
	 * @author I Copland
	 * 
	 * @param Saved instance state (Not used)
	 */
    @Override public void onCreate(Bundle savedInstanceState) 
    {	
        super.onCreate(savedInstanceState);
        try
        {
        	//go full screen!
        	requestWindowFeature(Window.FEATURE_NO_TITLE);
        	getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        
        	m_renderer = new Renderer();
    		m_surface = new Surface(this, m_renderer);
        
        	CSApplication app = new CSApplication();
        	app.create(this);
        	
        	CSApplication.get().activityIntent(getIntent());
    		
          	//initialise the old style native interfaces (These should be removed over time as each of these is changed over to the new system!)
        	HttpConnectionNativeInterface.Setup(this);
        	SharedPreferencesNativeInterface.Setup(this);
        	SMSCompositionNativeInterface.Setup(this);
        	ContactInformationProviderNativeInterface.Setup(this);
            WebViewNativeInterface.Setup(this);
            CSPowerManager.Setup(this);
            TwitterAuthenticationViewNativeInterface.Setup(this);
        }
        catch (Exception e)
        {
        	CSLogging.logError("Activity.onCreate has thrown an exception: " + e.toString());
        	e.printStackTrace();
        }
    }
	/**
	 * Triggered when the activity becomes visible
	 * 
	 * @author I Copland
	 */
    @Override protected void onResume() 
    {
    	super.onResume();
    	
        m_FMODAudioDevice.start();
        m_surface.onResume();

        CSPowerManager.RequestWakeLock(CSPowerManager.LOCK_TYPE.SCREEN_DIM_LOCK);
        
        CSApplication.get().resume();
    }
	/**
	 * Triggered when the window focus changes (i.e. the activity is no
	 * longer the top of the view stack or becomes the top of the view stack).
	 * The order of this in relation to resume and stop is not defined
	 * 
	 * @author I Copland
	 * 
	 * @param Whether the window has focus or not
	 */
    @Override public void onWindowFocusChanged(boolean in_hasFocus)
    {
    	if(in_hasFocus == true)
    	{
    		super.onWindowFocusChanged(in_hasFocus);
    		CSApplication.get().foreground();
    	}
    	else
    	{
    		CSApplication.get().background();
    		super.onWindowFocusChanged(in_hasFocus);
    	}
    }
	/**
	 * Triggered when the activity is no longer wholly visible.
	 * 
	 * @author I Copland
	 */
    @Override public void onPause() 
    {
    	m_surface.onPause();
    	m_FMODAudioDevice.stop();
        CSPowerManager.ReleaseLock(CSPowerManager.LOCK_TYPE.SCREEN_DIM_LOCK);
        
        CSApplication.get().suspend();
        super.onPause();
    }
	/**
	 * Triggered when the activity is no longer visible.
	 * 
	 * @author I Copland
	 */
    @Override public void onStop()
    {
	    super.onStop();
    }
	/**
	 * Triggered when the activity is no active. This is the end of the app
	 * 
	 * @author I Copland
	 */
    @Override public void onDestroy()
    {
    	CSApplication.get().destroy();
	    super.onDestroy();
    }
	/**
	 * Triggered when the activity receives a new intent either on launch
	 * or by having it passed by another activity
	 * 
	 * @author I Copland
	 * 
	 * @param Intent
	 */
    @Override public void onNewIntent(Intent inIntent)
    {
    	setIntent(inIntent);
    	CSApplication.get().activityIntent(inIntent);
    	super.onNewIntent(inIntent);
    }
	/**
	 * Triggered when the activity exits.
	 * 
	 * @author I Copland
	 * 
	 * @param Request code that it started with
	 * @param Result code it returned
	 * @param Any additional data returned
	 */
    @Override protected void onActivityResult(int in_requestCode, int in_resultCode, Intent in_data) 
    {
    	CSApplication.get().activityResult(in_requestCode, in_resultCode, in_data);
	}
	/**
	 * Triggered when the activity config changes such as orientation,
	 * hardware keyboards, etc.
	 * 
	 * @author I Copland
	 * 
	 * @param New config
	 */
    @Override public void onConfigurationChanged(Configuration newConfig) 
    {     
    	super.onConfigurationChanged(newConfig);
    	
    	// Checks whether a hardware keyboard is available    
    	if (newConfig.hardKeyboardHidden == Configuration.HARDKEYBOARDHIDDEN_NO) 
    	{   
    		KeyboardNativeInterface keyboardNI = (KeyboardNativeInterface)CSApplication.get().getSystem(KeyboardNativeInterface.InterfaceID);
    		if (keyboardNI != null)
    		{
    			keyboardNI.SetHardwareKeyboardOpen();
    		}
    	} 
    	else if (newConfig.hardKeyboardHidden == Configuration.HARDKEYBOARDHIDDEN_YES) 
    	{
    		KeyboardNativeInterface keyboardNI = (KeyboardNativeInterface)CSApplication.get().getSystem(KeyboardNativeInterface.InterfaceID);
    		if (keyboardNI != null)
    		{
    			keyboardNI.SetHardwareKeyboardClosed();
    		}
    	}
    }
	/**
	 * Triggered when the activity receives an event from the hard-key back button.
	 * This then forwards the event to the application
	 * 
	 * @author I Copland
	 */
    @Override public void onBackPressed() 
    {
    	//create the task to be run on the rendering thread
		Runnable task = new Runnable()
		{
			@Override public void run() 
			{
				//TODO: Handle back button
			}
		};
		
		//run the task.
		m_surface.queueEvent(task);
    }
	/**
	 * @author I Copland
	 * 
	 * @return Activity surface
	 */
    public Surface getSurface()
    {
    	return m_surface;
    }
	/**
	 * @author S Downie
	 * 
	 * @return Renderer
	 */
    public Renderer getRenderer()
    {
    	return m_renderer;
    } 
}