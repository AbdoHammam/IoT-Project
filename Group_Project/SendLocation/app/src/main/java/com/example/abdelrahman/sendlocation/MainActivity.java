package com.example.abdelrahman.sendlocation;

import android.Manifest;
import android.content.Context;
import android.content.pm.PackageManager;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    private TextView longitude;
    private TextView latitude;
    private EditText serverIP;
    private EditText portNumber;
    private EditText boardNumber;
    private Button send;
    TcpClient mTcpClient;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        longitude = (TextView) findViewById(R.id.longitude);
        latitude = (TextView) findViewById(R.id.latitude);
        serverIP = (EditText) findViewById(R.id.serverIP);
        portNumber = (EditText) findViewById(R.id.portNumber);
        boardNumber = (EditText) findViewById(R.id.boardNumber);
        send = (Button) findViewById(R.id.sendLocation);
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED && ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(MainActivity.this, new String[]{Manifest.permission.ACCESS_FINE_LOCATION}, 1);
            return;
        }
        LocationManager locationManager = (LocationManager) this.getSystemService(Context.LOCATION_SERVICE);
        locationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, 6000, 2, locationListener);
        Location loc1 = locationManager.getLastKnownLocation(LocationManager.GPS_PROVIDER);
        locationManager.requestLocationUpdates(LocationManager.NETWORK_PROVIDER, 6000, 2, locationListener);
        Location loc2 = locationManager.getLastKnownLocation(LocationManager.NETWORK_PROVIDER);
        locationManager.requestLocationUpdates(LocationManager.NETWORK_PROVIDER, 6000, 2, locationListener);
        Location loc3 = locationManager.getLastKnownLocation(LocationManager.PASSIVE_PROVIDER);
        Location lastKnownLocation = locationManager.getLastKnownLocation(LocationManager.PASSIVE_PROVIDER);
        if(lastKnownLocation == null){
            if(loc1 != null)
                lastKnownLocation = loc1;
            else if(loc2 != null)
                lastKnownLocation = loc2;
            else
                lastKnownLocation = loc3;
        }
        if(lastKnownLocation!=null){
            longitude.setText("Longitude : "+String.valueOf(lastKnownLocation.getLongitude()));
            latitude.setText("Latitude : "+String.valueOf(lastKnownLocation.getLatitude()));
        }
        else {

            Toast.makeText(MainActivity.this,"Location = null",Toast.LENGTH_LONG).show();
        }
        final Location finalLastKnownLocation = lastKnownLocation;
        send.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (mTcpClient == null) {
                    mTcpClient = new TcpClient(new TcpClient.OnMessageReceived() {
                        @Override
                        public void messageReceived(String message) {
                            Log.i("MainActivity","messageReceived: "+message);
                        }
                    });
                }
                mTcpClient.stopClient();
                TcpClient.SERVER_IP = serverIP.getText().toString();
                TcpClient.SERVER_PORT=Integer.parseInt(portNumber.getText().toString());
                mTcpClient.run();
                if(finalLastKnownLocation != null)
                    mTcpClient.setLocation(boardNumber.getText().toString(), finalLastKnownLocation);
                else
                    Toast.makeText(MainActivity.this,"Can't get current location",Toast.LENGTH_LONG).show();
            }
        });
    }
    LocationListener locationListener = new LocationListener() {
        public void onLocationChanged(Location location) {
            longitude.setText("Longitude : "+String.valueOf(location.getLongitude()));
            latitude.setText("Latitude : "+String.valueOf(location.getLatitude()));
            if(mTcpClient != null)
                mTcpClient.setLocation(boardNumber.getText().toString(),location);
        }
        public void onStatusChanged(String provider, int status, Bundle extras) {}

        public void onProviderEnabled(String provider) {}

        public void onProviderDisabled(String provider) {}
    };

}
