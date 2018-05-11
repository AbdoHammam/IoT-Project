package com.example.abdelrahman.sendlocation;
import android.location.Location;
import android.util.Log;

import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;

import static android.content.ContentValues.TAG;

public class TcpClient {

    public static String SERVER_IP ;
    public static  int SERVER_PORT ;
    private String mServerMessage;
    private OnMessageReceived mMessageListener = null;
    private boolean mRun = false;
    private PrintWriter mBufferOut;
    private Location currentLocation;
    private String boardNum;
    private BufferedReader mBufferIn;

    public TcpClient(OnMessageReceived listener) {
        mMessageListener = listener;
    }

    /**
     * Sends the message entered by client to the server
     *
     * @param message text entered by client
     */
    public void sendMessage(final String message) {
        Runnable runnable = new Runnable() {
            @Override
            public void run() {
                if (mBufferOut != null) {
                    Log.d(TAG, "Sending: " + message);
                    mBufferOut.println(message);
                    mBufferOut.flush();
                }
            }
        };
        Thread thread = new Thread(runnable);
        thread.start();
    }

    /**
     * Close the connection and release the members
     */
    public void stopClient() {

        mRun = false;

        if (mBufferOut != null) {
            mBufferOut.flush();
            mBufferOut.close();
        }

        mMessageListener = null;
        mBufferIn = null;
        mBufferOut = null;
        mServerMessage = null;
    }

    public void run() {

        Runnable runnable = new Runnable() {
            @Override
            public void run() {
                mRun = true;

                try {
                    InetAddress serverAddr = InetAddress.getByName(SERVER_IP);

                    Socket socket = new Socket(serverAddr, SERVER_PORT);
                    Log.e("TCP Client", "C: Connecting...");

                    try {

                        mBufferOut = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket.getOutputStream())), true);

                        mBufferIn = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                                JSONObject jsonObject = new JSONObject();
                                jsonObject.put("Board",Integer.parseInt(boardNum));
                                jsonObject.put("Latitude",currentLocation.getLatitude());
                                jsonObject.put("Longitude",currentLocation.getLongitude());
                                sendMessage(String.valueOf(jsonObject.toString()));

//                        Log.e("RESPONSE FROM SERVER", "S: Received Message: '" + mServerMessage + "'");

                    } catch (Exception e) {

                        Log.e("TCP", "S: Error", e);

                    } finally {

                        socket.close();
                    }

                } catch (Exception e) {

                    Log.e("TCP", "C: Error", e);

                }
            }
        };

        Thread thread = new Thread(runnable);
        thread.start();

    }

    public interface OnMessageReceived {
        public void messageReceived(String message);
    }
    public void setLocation(String boardNumber ,Location location){
        currentLocation = location;
        boardNum = boardNumber;
    }
}
