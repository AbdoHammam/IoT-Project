package com.example.abdelrahman.sendlocationhttp;

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

import com.android.volley.AuthFailureError;
import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;
import com.google.android.gms.location.FusedLocationProviderClient;
import com.google.android.gms.location.LocationServices;
import com.google.android.gms.tasks.OnSuccessListener;

import org.json.JSONObject;

import java.util.HashMap;
import java.util.Map;

public class MainActivity extends AppCompatActivity {

    TextView longitude;
    TextView latitude;
    EditText portNumber;
    EditText boardNumber;
    Button sendBtn;
    private FusedLocationProviderClient mFusedLocationClient;
    Location lastKnownLocation;
    RequestQueue queue;
    JsonObjectRequest postRequest;
    String url = "http://193.227.14.15:";
    Map<String, String> data = new HashMap<>();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        longitude = (TextView) findViewById(R.id.longitude);
        latitude = (TextView) findViewById(R.id.latitude);
        portNumber = (EditText) findViewById(R.id.portNumber);
        boardNumber = (EditText) findViewById(R.id.boardNumber);
        sendBtn = (Button) findViewById(R.id.sendLocation);
        queue  = Volley.newRequestQueue(this);
        mFusedLocationClient = LocationServices.getFusedLocationProviderClient(this);
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED && ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(MainActivity.this, new String[]{Manifest.permission.ACCESS_FINE_LOCATION}, 1);
            return;
        }
        mFusedLocationClient.getLastLocation()
                .addOnSuccessListener(this, new OnSuccessListener<Location>() {
                    @Override
                    public void onSuccess(Location location) {
                        if (location !=null){
                            longitude.setText("Longitude : "+String.valueOf(location.getLongitude()));
                            latitude.setText("Latitude : "+String.valueOf(location.getLatitude()));
                            lastKnownLocation = location;
                        }
                        else {
                            Toast.makeText(MainActivity.this,"Location = null",Toast.LENGTH_LONG).show();
                        }
                    }
                });
        if(lastKnownLocation == null){
            LocationManager locationManager = (LocationManager) this.getSystemService(Context.LOCATION_SERVICE);
            locationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, 5000, 2, locationListener);
            Location loc1 = locationManager.getLastKnownLocation(LocationManager.GPS_PROVIDER);
            locationManager.requestLocationUpdates(LocationManager.NETWORK_PROVIDER, 5000, 2, locationListener);
            Location loc2 = locationManager.getLastKnownLocation(LocationManager.NETWORK_PROVIDER);
            locationManager.requestLocationUpdates(LocationManager.NETWORK_PROVIDER, 5000, 2, locationListener);
            Location loc3 = locationManager.getLastKnownLocation(LocationManager.PASSIVE_PROVIDER);
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
        sendBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                url = "http://138.197.178.93:" + portNumber.getText().toString();
                data.put("Board",boardNumber.getText().toString());
                data.put("Latitude",String.valueOf(lastKnownLocation.getLatitude()));
                data.put("Longitude",String.valueOf(lastKnownLocation.getLongitude()));
                postRequest = new JsonObjectRequest( Request.Method.POST, url,
                        new JSONObject(data),
                        new Response.Listener<JSONObject>() {
                            @Override
                            public void onResponse(JSONObject response) {
                                Toast.makeText(MainActivity.this,"POST",Toast.LENGTH_LONG).show();
                            }
                        },
                        new Response.ErrorListener() {
                            @Override
                            public void onErrorResponse(VolleyError error) {
//                                Toast.makeText(MainActivity.this,error.networkResponse.statusCode,Toast.LENGTH_LONG).show();
                            }
                        }) {
                    @Override
                    public Map<String, String> getHeaders() {
                        HashMap<String, String> headers = new HashMap<>();
//                        headers.put("Content-Type", "application/json; charset=utf-8");
//                        headers.put("User-agent", System.getProperty("http.agent"));
                        return headers;
                    }
                };
                queue.add(postRequest);
                queue.start();
            }
        });

    }
    LocationListener locationListener = new LocationListener() {
        public void onLocationChanged(Location location) {
            longitude.setText("Longitude : "+String.valueOf(location.getLongitude()));
            latitude.setText("Latitude : "+String.valueOf(location.getLatitude()));
        }
        public void onStatusChanged(String provider, int status, Bundle extras) {}
        public void onProviderEnabled(String provider) {}
        public void onProviderDisabled(String provider) {}
    };

}
