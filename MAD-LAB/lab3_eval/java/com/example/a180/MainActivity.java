package com.example.a180;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Button vowel, count;
        vowel = findViewById(R.id.button1);
        count = findViewById(R.id.button2);
        vowel.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                EditText inputText;
                TextView textOutput;
                textOutput = findViewById(R.id.textView2);
                inputText = findViewById(R.id.textView1);
                String Text = inputText.getText().toString();
                Log.i("inputText","Text:" + Text);
                Text = Text.toLowerCase();
                char arr[] = Text.toCharArray();
                String str ="";
                for(int i =0;i<Text.length();i++){
                    if(arr[i] == 'a'||arr[i] == 'e'||arr[i] == 'i'||arr[i] == 'o'||arr[i] == 'u'){
                        str = str + arr[i];
                    }
                }
                Log.i("Concat Vowels","Vowels:" + str);
                textOutput.setText(str);
            }
        });
        count.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                EditText inputText;
                inputText = findViewById(R.id.textView1);
                String Text = inputText.getText().toString();
                Log.i("inputText","Text:" + Text);
                Text = Text.toLowerCase();
                int[] freq = new int[Text.length()];
                int i, j;

                char string[] = Text.toCharArray();

                for(i = 0; i <Text.length(); i++) {
                    freq[i] = 1;
                    for(j = i+1; j <Text.length(); j++) {
                        if(string[i] == string[j]) {
                            freq[i]++;

                            string[j] = '0';
                        }
                    }
                }
                for(i = 0; i <freq.length; i++) {
                    if(string[i] != ' ' && string[i] != '0')
                        Toast.makeText(MainActivity.this,string[i] + "-" + freq[i],Toast.LENGTH_LONG).show();
//                    System.out.println(string[i] + "-" + freq[i]);
                }
            }
        });
    }
}