/* File generated by DarkEdifPostBuildTool, part of DarkEdif SDK. 
   DarkEdif license is available at its online repository location.
   Copyright of the Bluewing Server extension and all rights reserved by creator of Bluewing Server.
   
   A native extension needs a Java file to generate a Java class. The class is empty,
   and a native is assumed by presence of CRunBluewing_Server in the assets folder.
   This file is required. The Bluewing Server creator may modify the copyright to suit their wishes,
   if they retain the DarkEdif notice (third line).
*/

package Extensions;
import android.util.Log;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.io.InputStream;
import java.io.IOException;
import Services.CBinaryFile;
import Runtime.MMFRuntime;
import Objects.CExtension;
import RunLoop.CCreateObjectInfo;
import Conditions.CCndExtension;
import Expressions.CExpExtension;
import Actions.CActExtension;
import Expressions.CValue;
import Expressions.CNativeExpInstance;
import RunLoop.CRun;

public class CRunBluewing_Server extends CRunExtension
{
	private class ShutdownThread extends Thread
	{
		public void run()
		{
			CRunBluewing_Server.darkedif_EndApp();
		}
	}

	private static boolean inited = false;
	private long cptr;
	public static ShutdownThread shutdownThreadClass;
	public static Thread shutdownThread;
	public CRunBluewing_Server()
	{
		if (!inited)
		{
			String libName = "Bluewing_Server";
			try
			{
				android.util.Log.v("Bluewing_Server", "Loading Bluewing Server extension from \"app/main/jniLibs/" + MMFRuntime.inst.ABI + "/lib" + libName + ".so\"...");
				System.loadLibrary(libName);

				android.util.Log.v("Bluewing_Server", "Loaded Bluewing Server extension OK!");
				
				inited = true;
			}
			catch (UnsatisfiedLinkError e)
			{
				android.util.Log.e("Bluewing_Server", "Couldn't load extension Bluewing Server, library lib" + libName + ".so couldn't be loaded: " + e.toString());
			}
			
			// Set up JavaVM shutdown handler
			if (inited)
			{
				shutdownThreadClass = new ShutdownThread();
				shutdownThread = new Thread(shutdownThreadClass);
				Runtime.getRuntime().addShutdownHook(shutdownThread);
			}
		}
	}
	
	@Override
	public int getNumberOfConditions()
	{
		return darkedif_getNumberOfConditions(cptr);
	}
	public native int darkedif_getNumberOfConditions(long cptr);
	
	@Override
	public boolean createRunObject(CBinaryFile file, CCreateObjectInfo cob, int version)
	{
		// No need to request Internet or AccessNetworkState perms at runtime:
		// https://developer.android.com/training/basics/network-ops/connecting#:~:text=%20both%20the%20internet%20and%20access_network_state%20
		
		// CRunNativeExtension's createRunObject() does not expect "file" to be non-null all the time,
		// so this function doesn't either.
		
		// Also, Fusion's Android runtime doesn't prepend eHeader to EDITDATA, so we'll reconstruct it ourselves.
		int eHeaderSize = 20; // 32-bit pointers
		int dataSize = eHeaderSize + (file != null ? file.data.length : 0);
		ByteBuffer edPtr = ByteBuffer.allocateDirect(dataSize);
		
		// Java defaults to big-endian, but the CPUs default to little-endian
		edPtr.order(ByteOrder.LITTLE_ENDIAN);
		
		// create eHeader; ocPtr is not accessible here, which is sad cos it contains everything.
		edPtr.putInt(dataSize); 	  // extSize
		edPtr.putInt(dataSize);		  // dummy - extMaxSize not read by CObjectCommon file reader
		edPtr.putInt(version);		  // extVersion
		edPtr.putInt(0);			  // dummy - extID read by CObjectCommon file reader, but not passed
		edPtr.putInt(ho.privateData); // extPrivateData stored in CRunExtension, 
		
		// Add EDITDATA, if available
		if (file != null)
			edPtr.put(file.data);
		
		edPtr.position(0); // Reset to start for C++ reader
		cptr = darkedif_createRunObject(edPtr, cob, version);
		if (cptr == 0)
			android.util.Log.e("Bluewing_Server", "Bluewing Server's createRunObject returned NULL!");
		
		return cptr != 0;
	}
	public native long darkedif_createRunObject(ByteBuffer edPtr, CCreateObjectInfo cob, int version);
	
	@Override
	public int handleRunObject()
	{
		return (int)darkedif_handleRunObject(cptr);
	}
	public native short darkedif_handleRunObject(long cptr);
		
	@Override
	public void displayRunObject()
	{
		darkedif_displayRunObject(cptr);
	}
	public native short darkedif_displayRunObject(long cptr);
	
	@Override
	public void destroyRunObject(boolean bFast)
	{
		darkedif_destroyRunObject(cptr, bFast);
	}
	public native void darkedif_destroyRunObject(long cptr, boolean fast);
	
	@Override
	public void pauseRunObject()
	{
		darkedif_pauseRunObject(cptr);
	}
	public native short darkedif_pauseRunObject(long cptr);
	
	@Override
	public void continueRunObject()
	{
		darkedif_continueRunObject(cptr);
	}
	public native short darkedif_continueRunObject(long cptr);
	
	@Override
	public boolean condition(int num, CCndExtension cnd)
	{
		// Currently, as of SDK v11, you will need to program comparison conditions manually,
		// by checking num and the return of Bluewing_Server_conditionJump, which is either a 32-bit integer,
		// 32-bit float, or a UTF-8 string pointer. For now, this is sufficient to check non-bool.
		// Use cnd.compareValues() or cnd.compareTime() as appropriate.
		return darkedif_conditionJump(cptr, num, cnd) != 0;
	}
	public native long darkedif_conditionJump(long cptr, int num, CCndExtension cnd);
	
	@Override
	public void action(int num, CActExtension act)
	{
		darkedif_actionJump(cptr, num, act);
	}
	public native void darkedif_actionJump(long cptr, int num, CActExtension act);
	
	@Override
	public CValue expression (int num)
	{
		CNativeExpInstance exp = new CNativeExpInstance(this.ho);
		darkedif_expressionJump(cptr, num, exp);
		return exp.result;
	}
	private native void darkedif_expressionJump(long cptr, int num, CNativeExpInstance exp);
	
	// JavaVM shutdown handler. Fusion doesn't appear to have a way of notifying native exts if app is closing down.
	public static native void darkedif_EndApp();
	
	
	// Methods accessed from C++ side of DarkEdif via JNI:
	
	public int darkedif_jni_getCurrentFusionEventNum()
	{
		return this.rh.rhEvtProg.rhEventGroup.evgLine;
	}
}
