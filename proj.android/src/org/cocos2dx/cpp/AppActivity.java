/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

//import java.util.UUID;

import org.cocos2dx.lib.Cocos2dxActivity;

//import android.content.Context;
import android.os.Bundle;
//import android.os.Handler;
import android.provider.Settings;
import android.util.Log;
//import android.widget.Toast;

//import com.meowroll.nkisdk.NhiAPI;

public class AppActivity extends Cocos2dxActivity {
	
	private static final int nRequestCode = 12345;
	public static AppActivity payActivity = null;  

    @Override  
    protected void onCreate(Bundle savedInstanceState)  
    {  
        // TODO Auto-generated method stub  
        super.onCreate(savedInstanceState);       
        payActivity = this;  
    }  
      
    //返回实例  
    public static Object getInstance()  
    {  
        if (payActivity == null)  
        {  
            payActivity = new AppActivity();  
        }  
        return payActivity;  
    }  
    
	public static String getUUID()
	{
		/*
		final TelephonyManager tm = (TelephonyManager) getContext().getSystemService(Context.TELEPHONY_SERVICE);
	   final String tmDevice, tmSerial, androidId;
	  
	   tmDevice = "" + tm.getDeviceId();
	   tmSerial = "" + tm.getSimSerialNumber();

	   androidId = "" + android.provider.Settings.Secure.getString(getContext().getContentResolver(), android.provider.Settings.Secure.ANDROID_ID);
	  
	   UUID deviceUuid = new UUID(androidId.hashCode(), ((long)tmDevice.hashCode() << 32) | tmSerial.hashCode());
	   String uniqueId = deviceUuid.toString();

	   return uniqueId;
	   */
		String BuildSERIAL = android.os.Build.SERIAL;

        if (Settings.Secure.getString(getContext().getContentResolver(), Settings.Secure.ANDROID_ID) != null
                && !Settings.Secure.getString(getContext().getContentResolver(), Settings.Secure.ANDROID_ID).equals("")
                ) {
            BuildSERIAL = BuildSERIAL + "," + Settings.Secure.getString(getContext().getContentResolver(), Settings.Secure.ANDROID_ID);
        } else {
            BuildSERIAL = BuildSERIAL + ",NULL";
        }
        Log.v("BuildSERIAL","BuildSERIAL="+ BuildSERIAL  );
        
        //NhiAPI api= new NhiAPI();
        //payHandler.sendEmptyMessage(1);
        //api.login(payActivity, nRequestCode, new NhiAPI.LoginCompletion());
        
        //02-06 17:05:07.913 29736-30475/? V/doInBackground: StrAccount=d121146818; StrPassword=d121146818;_deviceNumber=F5NKCY010699,cad244603e0368ea;sResponse={"IsProcessOK":true,"ReturnCode":"0000","Message":"正確","Token":"W28f0161827620441A2s681j320J02034FnB2d72e5GL2a92X","Account":null,"InsType":null}

        return BuildSERIAL;
	}
}
