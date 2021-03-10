package com.example.a180953212_app;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import java.util.Objects;

public class MainActivity extends AppCompatActivity {
    public static final String EXTRA_MESSAGE = "com.example.180953212_app.MESSAGE";

    @Override
    protected void onCreate(Bundle savedInstanceState) {


        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Button login;
        login = findViewById(R.id.login);
        login.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){
                EditText username, password;

                username=findViewById(R.id.username);
                String usernameText = username.getText().toString();
                password=findViewById(R.id.password);
                String passwordText = password.getText().toString();
                Log.d("User_logs",  "Username: "+usernameText);
                Log.d("User_logs", "Password: " + passwordText);
                if(usernameText.equals(passwordText))
                {
                    Toast.makeText(MainActivity.this,"No Auth for you!",Toast.LENGTH_LONG).show();
                }else
                {
                    Intent intent = new Intent(MainActivity.this, DisplayActivity.class);
//                    EditText editText = (EditText) findViewById(R.id.editText);

                    String message = usernameText;
                    intent.putExtra(EXTRA_MESSAGE, message);
                    startActivity(intent);
                }

            }
        });
    }
}