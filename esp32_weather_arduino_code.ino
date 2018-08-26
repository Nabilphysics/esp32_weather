/* 
 Originally from https://techtutorialsx.com/2018/03/17/esp32-arduino-getting-weather-data-from-api/
 Modified with JSON by
 Syed Razwanul Haque(Nabil), CEO, www.cruxbd.com 
 For IoT course at CRUX
 
 Step 1 : Create You ID at www.openweathermap.org
 Step 2 : Make sure API call is working in your browser and you have got the JSON response
 Step 3 : Use https://arduinojson.org/v5/assistant/ for JSON parsing made easy
 Step 4 : Replace API key with your own key from openweathermap
 Step 5 : Upload the code and check everything is OK
 Step 6 : Make the code efficient and help me  
 */ 

#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
//#include <string>
//#include <iostream>

 
const char* ssid = "yourSSID";
const char* password =  "SSID_Password";
 
const String endpoint = "http://api.openweathermap.org/data/2.5/weather?id=1185099&units=metric&APPID=";
const String key = "your key from openweathermap";
//http://api.openweathermap.org/data/2.5/weather?id=1185099&units=metric&APPID=54de061b9d0ea5ad5635d361df99564e
 
void setup() {
   Serial.begin(115200);
   WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 Serial.println("Connected to the WiFi network");
 }
 
void loop() {
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
 
    HTTPClient http;
 
    http.begin(endpoint + key); //Specify the URL
    int httpCode = http.GET();  //Make the request
 
    if (httpCode > 0) { //Check for the returning code
 
        String payload = http.getString();
        //Serial.println(httpCode); //200 means ok
        //Serial.println(payload); // Uncomment if you want to see JSON data
        
        const char* json = payload.c_str(); // convert "payload" string to char 
        
        StaticJsonBuffer<1300> jsonBuffer; //https://arduinojson.org/v5/assistant/  if data is 0.0 than increse it
        JsonObject& root = jsonBuffer.parseObject(json);
        //Serial.println(json);
//        if(root.success()){
//          Serial.println("json ok");
//        }
        
        JsonObject& main = root["main"];
        JsonObject& sys = root["sys"];
        float main_temp = main["temp"];
        const char* sys_country = sys["country"]; //Country : "BD"
        const char* name = root["name"];// City
        int main_humidity = main["humidity"]; // 89
        Serial.print("Country: ");
        Serial.print(sys_country);
        Serial.println("");
        
        Serial.print("City: ");
        Serial.print(name);
        Serial.println("");
        
        Serial.print("Temperature: ");
        Serial.print(main_temp);
        Serial.println(" deg Celcius");
        Serial.print("Humidity: ");
        Serial.print(main_humidity);
        Serial.println("");

        JsonObject& weather0 = root["weather"][0];
        const char* weather0_main = weather0["main"]; // "Clouds"
        const char* weather0_description = weather0["description"]; // "broken clouds"

        Serial.print("Weather Codition: ");
        Serial.print(weather0_main);
        Serial.println("");
        Serial.print("Weather Codition Details: ");
        Serial.print(weather0_description);
        Serial.println("");
        
        // Add as many info as you need
      }
 
    else {
      Serial.println("Error on HTTP request");
    }
 
    http.end(); //Free the resources
  }
 
  delay(30000); //30 Seconds Delay
}

// Using https://arduinojson.org/v5/assistant/
/* 
const size_t bufferSize = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(2) + 2*JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(7) + JSON_OBJECT_SIZE(11) + 410;
DynamicJsonBuffer jsonBuffer(bufferSize);

const char* json = "{\"coord\":{\"lon\":91.87,\"lat\":24.9},\"weather\":[{\"id\":803,\"main\":\"Clouds\",\"description\":\"broken clouds\",\"icon\":\"04d\"}],\"base\":\"stations\",\"main\":{\"temp\":26.57,\"pressure\":947.05,\"humidity\":89,\"temp_min\":26.57,\"temp_max\":26.57,\"sea_level\":1012.12,\"grnd_level\":947.05},\"wind\":{\"speed\":0.17,\"deg\":66.0002},\"clouds\":{\"all\":56},\"dt\":1535285621,\"sys\":{\"message\":0.0033,\"country\":\"BD\",\"sunrise\":1535239871,\"sunset\":1535285820},\"id\":1185099,\"name\":\"Sylhet\",\"cod\":200}";

JsonObject& root = jsonBuffer.parseObject(json);

float coord_lon = root["coord"]["lon"]; // 91.87
float coord_lat = root["coord"]["lat"]; // 24.9

JsonObject& weather0 = root["weather"][0];
int weather0_id = weather0["id"]; // 803
const char* weather0_main = weather0["main"]; // "Clouds"
const char* weather0_description = weather0["description"]; // "broken clouds"
const char* weather0_icon = weather0["icon"]; // "04d"

const char* base = root["base"]; // "stations"

JsonObject& main = root["main"];
float main_temp = main["temp"]; // 26.57
float main_pressure = main["pressure"]; // 947.05
int main_humidity = main["humidity"]; // 89
float main_temp_min = main["temp_min"]; // 26.57
float main_temp_max = main["temp_max"]; // 26.57
float main_sea_level = main["sea_level"]; // 1012.12
float main_grnd_level = main["grnd_level"]; // 947.05

float wind_speed = root["wind"]["speed"]; // 0.17
float wind_deg = root["wind"]["deg"]; // 66.0002

int clouds_all = root["clouds"]["all"]; // 56

long dt = root["dt"]; // 1535285621

JsonObject& sys = root["sys"];
float sys_message = sys["message"]; // 0.0033
const char* sys_country = sys["country"]; // "BD"
long sys_sunrise = sys["sunrise"]; // 1535239871
long sys_sunset = sys["sunset"]; // 1535285820

long id = root["id"]; // 1185099
const char* name = root["name"]; // "Sylhet"
int cod = root["cod"]; // 200
*/
