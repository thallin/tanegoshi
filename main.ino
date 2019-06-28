#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_ADS1015.h>

class Planta
{
  public:
   String nome;
   float iluminacao_min,iluminacao_max,umidade_min,umidade_max,temperatura_min,temperatura_max;
   Planta(String vnome,float viluminacao_min, float viluminacao_max, float vumidade_min, float vumidade_max, float vtemperatura_min, float vtemperatura_max){
    nome = vnome;
    iluminacao_min = viluminacao_min;
    iluminacao_max = viluminacao_max;
    umidade_min = vumidade_min;
    umidade_max = vumidade_max;
    temperatura_min = vtemperatura_min;
    temperatura_max = vtemperatura_max;
   }  
};

#define DHTPIN D6
#define DHTTYPE    DHT22    
DHT_Unified dht(DHTPIN, DHTTYPE);

const char *ssid = "Tanegoshi";
const Planta plantas[] = {Planta("Majericão",175,240,2,2.4,18,40),
                          Planta("Alecrim",175,240,1.9,2.3,18,40)};
float proximo = 0;
float agua = 0;
float temp = 0;
int plantaAtual = 99;
Adafruit_ADS1115 ads(0x48);
ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/
void handleRoot() {
  Planta p = plantas[plantaAtual];
  String html = "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\"><title>Tanegoshi</title><style>html{widht:100%;}body{width:100%;}h2{width:100%;text-align:center;}td{min-width:50px;}table{margin:auto}</style></head><body><h2>Tanegoshi</h2>";
  html += "<select>";
  for(int i=0; i<(sizeof(plantas) / sizeof(plantas[0])); i++){
    html += "<option value=\""+String(i)+"\">"+plantas[i].nome+"</option>";
  }
  html += "</select>";
  html += "<table>";
  html += "<tr><td>Temperatura:</td><td>"+String(p.temperatura_min)+"ºC</td><td>"+String(plantas[plantaAtual].temperatura_max)+"ºC</td><td>"+String(temp)+"ºC</td></tr>";
  html += "<tr><td>Umidade:</td><td>"+String(p.umidade_min)+"</td><td>"+String(plantas[plantaAtual].umidade_max)+"</td><td>"+String(agua)+"ºC</td></tr>";
  //"<tr><td><a class=\"botao\" href=\"/configuracao\">Configuração</a> "+String(agua)+"</td><td></td><td><a class=\"botao\" href=\"/dados\">Dados</a> "+String(temp)+"ºC</td></tr>
  html += "</table></body></html>";
  server.send(200, "text/html", html);
}
void handleConfig() {
  String html = "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"><title>Tanegoshi</title><style>html{widht:100%;}body{width:100%;}h2{width:100%;text-align:center;}td{min-width:50px;}table{margin:auto}</style></head><body><h2>Tanegoshi - Configurações</h2><form action=\"/envia_config\"><table><tr><td align=\"right\">SSID:</td><td><input type=\"text\" name=\"ssid\"/></td></tr><tr><td align=\"right\">Senha:</td><td><input type=\"password\" name=\"senha\"/></td></tr><tr><td colspan=\"2\"><input type=\"submit\" value=\"Enviar\" /></td></tr></table></form></body></html>";
  server.send(200, "text/html", html);
}
void handleEnvia_Config() {
  String ssid = server.arg("ssid"); 
  String senha = server.arg("senha"); 
  String html = "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"><title>Tanegoshi</title><style>html{widht:100%;}body{width:100%;}h2{width:100%;text-align:center;}td{min-width:50px;}table{margin:auto}</style></head><body><h2>Tanegoshi - Configurações</h2><form action=\"/envia_config\"><table><tr><td align=\"right\">SSID:</td><td>"+ssid+"</td></tr><tr><td align=\"right\">Senha:</td><td>"+senha+"</td></tr></table></form></body></html>";
  server.send(200, "text/html", html);
}
void checa(){
  if(agua > 0){
    if(agua < plantas[plantaAtual].umidade_min || agua > plantas[plantaAtual].umidade_max){
      vermelho();
      beep();
      return;
    }
  }
  if(temp > 0){
    if(temp < plantas[plantaAtual].temperatura_min || temp > plantas[plantaAtual].temperatura_max){
      vermelho();
      beep();
      return;
    }
  }
  verde();
}
void apaga(){
  digitalWrite(D0, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
}
void verde(){
  apaga();
  digitalWrite(D0, HIGH);
}
void azul(){
  apaga();
  digitalWrite(D4, HIGH);
}
void vermelho(){
  apaga();
  digitalWrite(D3, HIGH);
}
void beep(){
  digitalWrite(D5, HIGH);
  delay(1000);
  digitalWrite(D5, LOW);
}
void setup() {
  delay(1000);
  Serial.begin(9600);
  dht.begin();
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid);
  pinMode(D0, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.on("/configuracao", handleConfig);
  server.on("/envia_config", handleEnvia_Config);
  server.begin();
  Serial.println("HTTP server started");
  ads.begin();
  azul();
}

void loop() {
  server.handleClient();
  if(millis() > proximo){
    int16_t adc0;
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    if (isnan(event.temperature)) {
      Serial.println(F("Error reading temperature!"));
    }
    else {
      temp = event.temperature;
    }
    agua = analogRead(A0)*3.3/1023;
    proximo = millis()+60000;
    checa();
  }
}
