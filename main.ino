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
const Planta plantas[] = {Planta("Selecione uma planta",0,0,0,0,0,0),
                          Planta("Majericão",175,240,2,2.4,18,40),
                          Planta("Alecrim",175,240,1.9,2.3,18,40)};
float proximo = 0;
float agua = 0;
float temp = 0;
float luz = 0;
int plantaAtual = 0;
Adafruit_ADS1115 ads(0x48);
ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/
void handleRoot() {
  if(server.arg("planta")!="") plantaAtual = server.arg("planta").toInt();
  Planta p = plantas[plantaAtual];
  String html = "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\"><title>Tanegoshi</title><style>html{widht:100%;}body{width:100%;}h2{width:100%;text-align:center;}td{min-width:50px;}table{margin:auto}</style></head><body><h2>Tanegoshi</h2>";
  html += "<form action=\"/\"><table><tr><td><select name = \"planta\">";
  for(int i=0; i<(sizeof(plantas) / sizeof(plantas[0])); i++){
    html += "<option value=\""+String(i)+"\" "+(i==plantaAtual?"selected":"")+">"+plantas[i].nome+"</option>";
  }
  html += "</select></td><td><input type=\"submit\" value=\"Enviar\" /></td></tr></table></form>";
  if(plantaAtual > 0){
    int nivel_agua = 1;
    if(agua > 0){
      if(agua < plantas[plantaAtual].umidade_min)nivel_agua=0;
      if(agua > plantas[plantaAtual].umidade_max)nivel_agua=2;
    }
    int nivel_temp = 1;
    if(temp > 0){
      if(temp < plantas[plantaAtual].temperatura_min)nivel_temp=0;
      if(temp > plantas[plantaAtual].temperatura_max)nivel_temp=2;
    }

    int nivel_sol = 1;
    if(luz > 0){
      if(luz < plantas[plantaAtual].iluminacao_min)nivel_sol=0;
      if(luz > plantas[plantaAtual].iluminacao_max)nivel_sol=2;
    }else{
      nivel_sol = 3;
    }
    html += "<table>";
    
    if(nivel_temp != 1)
      html += "<tr><td><div style=\"width:48px;height:48px;border-radius:24px;background-color:#FF6063;text-align:center;border:solid 1px black;\">";
    else
      html += "<tr><td><div style=\"width:48px;height:48px;border-radius:24px;background-color:#079e00;text-align:center;border:solid 1px black;\">";
    html += "<img style=\"margin-top:6px;\" src=\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACQAAAAkCAYAAADhAJiYAAAAGXRFWHRTb2Z0d2FyZQBBZG9iZSBJbWFnZVJlYWR5ccllPAAAAyJpVFh0WE1MOmNvbS5hZG9iZS54bXAAAAAAADw/eHBhY2tldCBiZWdpbj0i77u/IiBpZD0iVzVNME1wQ2VoaUh6cmVTek5UY3prYzlkIj8+IDx4OnhtcG1ldGEgeG1sbnM6eD0iYWRvYmU6bnM6bWV0YS8iIHg6eG1wdGs9IkFkb2JlIFhNUCBDb3JlIDUuMy1jMDExIDY2LjE0NTY2MSwgMjAxMi8wMi8wNi0xNDo1NjoyNyAgICAgICAgIj4gPHJkZjpSREYgeG1sbnM6cmRmPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5LzAyLzIyLXJkZi1zeW50YXgtbnMjIj4gPHJkZjpEZXNjcmlwdGlvbiByZGY6YWJvdXQ9IiIgeG1sbnM6eG1wPSJodHRwOi8vbnMuYWRvYmUuY29tL3hhcC8xLjAvIiB4bWxuczp4bXBNTT0iaHR0cDovL25zLmFkb2JlLmNvbS94YXAvMS4wL21tLyIgeG1sbnM6c3RSZWY9Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC9zVHlwZS9SZXNvdXJjZVJlZiMiIHhtcDpDcmVhdG9yVG9vbD0iQWRvYmUgUGhvdG9zaG9wIENTNiAoV2luZG93cykiIHhtcE1NOkluc3RhbmNlSUQ9InhtcC5paWQ6RTFGNjE0OTA5OUMwMTFFOUFFREZGOTg3NUE3NTA4ODIiIHhtcE1NOkRvY3VtZW50SUQ9InhtcC5kaWQ6RTFGNjE0OTE5OUMwMTFFOUFFREZGOTg3NUE3NTA4ODIiPiA8eG1wTU06RGVyaXZlZEZyb20gc3RSZWY6aW5zdGFuY2VJRD0ieG1wLmlpZDpFMUY2MTQ4RTk5QzAxMUU5QUVERkY5ODc1QTc1MDg4MiIgc3RSZWY6ZG9jdW1lbnRJRD0ieG1wLmRpZDpFMUY2MTQ4Rjk5QzAxMUU5QUVERkY5ODc1QTc1MDg4MiIvPiA8L3JkZjpEZXNjcmlwdGlvbj4gPC9yZGY6UkRGPiA8L3g6eG1wbWV0YT4gPD94cGFja2V0IGVuZD0iciI/Pj1qY1cAAAaKSURBVHjaxFh7TFNX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\"/>";
    html += "</div></td><td>";
    html += (nivel_temp==0?"Temperatura abaixo do aceitavel":(nivel_temp==2?"Temperatura acima do aceitavel":"Temperatura OK"));
    html += "</td></tr>";
    
    if(nivel_agua != 1)
      html += "<tr><td><div style=\"width:48px;height:48px;border-radius:24px;background-color:#FF6063;text-align:center;border:solid 1px black;\">";
    else
      html += "<tr><td><div style=\"width:48px;height:48px;border-radius:24px;background-color:#079e00;text-align:center;border:solid 1px black;\">";
    html += "<img style=\"margin-top:6px;\" src=\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACQAAAAkCAYAAADhAJiYAAAAGXRFWHRTb2Z0d2FyZQBBZG9iZSBJbWFnZVJlYWR5ccllPAAAAyJpVFh0WE1MOmNvbS5hZG9iZS54bXAAAAAAADw/eHBhY2tldCBiZWdpbj0i77u/IiBpZD0iVzVNME1wQ2VoaUh6cmVTek5UY3prYzlkIj8+IDx4OnhtcG1ldGEgeG1sbnM6eD0iYWRvYmU6bnM6bWV0YS8iIHg6eG1wdGs9IkFkb2JlIFhNUCBDb3JlIDUuMy1jMDExIDY2LjE0NTY2MSwgMjAxMi8wMi8wNi0xNDo1NjoyNyAgICAgICAgIj4gPHJkZjpSREYgeG1sbnM6cmRmPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5LzAyLzIyLXJkZi1zeW50YXgtbnMjIj4gPHJkZjpEZXNjcmlwdGlvbiByZGY6YWJvdXQ9IiIgeG1sbnM6eG1wPSJodHRwOi8vbnMuYWRvYmUuY29tL3hhcC8xLjAvIiB4bWxuczp4bXBNTT0iaHR0cDovL25zLmFkb2JlLmNvbS94YXAvMS4wL21tLyIgeG1sbnM6c3RSZWY9Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC9zVHlwZS9SZXNvdXJjZVJlZiMiIHhtcDpDcmVhdG9yVG9vbD0iQWRvYmUgUGhvdG9zaG9wIENTNiAoV2luZG93cykiIHhtcE1NOkluc3RhbmNlSUQ9InhtcC5paWQ6ODBGOEM1RTc5OUJGMTFFOTkxQkVFRENEMUE4MkI1NUIiIHhtcE1NOkRvY3VtZW50SUQ9InhtcC5kaWQ6ODBGOEM1RTg5OUJGMTFFOTkxQkVFRENEMUE4MkI1NUIiPiA8eG1wTU06RGVyaXZlZEZyb20gc3RSZWY6aW5zdGFuY2VJRD0ieG1wLmlpZDo4MEY4QzVFNTk5QkYxMUU5OTFCRUVEQ0QxQTgyQjU1QiIgc3RSZWY6ZG9jdW1lbnRJRD0ieG1wLmRpZDo4MEY4QzVFNjk5QkYxMUU5OTFCRUVEQ0QxQTgyQjU1QiIvPiA8L3JkZjpEZXNjcmlwdGlvbj4gPC9yZGY6UkRGPiA8L3g6eG1wbWV0YT4gPD94cGFja2V0IGVuZD0iciI/PtO/eA0AAAwwSURBVHjapFgJVFTn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\"/>";
    html += "</div></td><td>";
    html += (nivel_agua==0?"Umidade abaixo do aceitavel":(nivel_temp==2?"Umidade acima do aceitavel":"Umidade OK"));
    html += "</td></tr>";

    if(nivel_sol==3)
      html += "<tr><td><div style=\"width:48px;height:48px;border-radius:24px;background-color:#0808f3;text-align:center;border:solid 1px black;\">";
    else if(nivel_sol != 1)
      html += "<tr><td><div style=\"width:48px;height:48px;border-radius:24px;background-color:#FF6063;text-align:center;border:solid 1px black;\">";
    else
      html += "<tr><td><div style=\"width:48px;height:48px;border-radius:24px;background-color:#079e00;text-align:center;border:solid 1px black;\">";
    html += "<img style=\"margin-top:6px;\" src=\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACQAAAAkCAYAAADhAJiYAAAAGXRFWHRTb2Z0d2FyZQBBZG9iZSBJbWFnZVJlYWR5ccllPAAAAyJpVFh0WE1MOmNvbS5hZG9iZS54bXAAAAAAADw/eHBhY2tldCBiZWdpbj0i77u/IiBpZD0iVzVNME1wQ2VoaUh6cmVTek5UY3prYzlkIj8+IDx4OnhtcG1ldGEgeG1sbnM6eD0iYWRvYmU6bnM6bWV0YS8iIHg6eG1wdGs9IkFkb2JlIFhNUCBDb3JlIDUuMy1jMDExIDY2LjE0NTY2MSwgMjAxMi8wMi8wNi0xNDo1NjoyNyAgICAgICAgIj4gPHJkZjpSREYgeG1sbnM6cmRmPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5LzAyLzIyLXJkZi1zeW50YXgtbnMjIj4gPHJkZjpEZXNjcmlwdGlvbiByZGY6YWJvdXQ9IiIgeG1sbnM6eG1wPSJodHRwOi8vbnMuYWRvYmUuY29tL3hhcC8xLjAvIiB4bWxuczp4bXBNTT0iaHR0cDovL25zLmFkb2JlLmNvbS94YXAvMS4wL21tLyIgeG1sbnM6c3RSZWY9Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC9zVHlwZS9SZXNvdXJjZVJlZiMiIHhtcDpDcmVhdG9yVG9vbD0iQWRvYmUgUGhvdG9zaG9wIENTNiAoV2luZG93cykiIHhtcE1NOkluc3RhbmNlSUQ9InhtcC5paWQ6OEMzNDcwMUM5QTE4MTFFOThEMkNEQjE1Nzg3QzhGODgiIHhtcE1NOkRvY3VtZW50SUQ9InhtcC5kaWQ6OEMzNDcwMUQ5QTE4MTFFOThEMkNEQjE1Nzg3QzhGODgiPiA8eG1wTU06RGVyaXZlZEZyb20gc3RSZWY6aW5zdGFuY2VJRD0ieG1wLmlpZDo4QzM0NzAxQTlBMTgxMUU5OEQyQ0RCMTU3ODdDOEY4OCIgc3RSZWY6ZG9jdW1lbnRJRD0ieG1wLmRpZDo4QzM0NzAxQjlBMTgxMUU5OEQyQ0RCMTU3ODdDOEY4OCIvPiA8L3JkZjpEZXNjcmlwdGlvbj4gPC9yZGY6UkRGPiA8L3g6eG1wbWV0YT4gPD94cGFja2V0IGVuZD0iciI/PrqiHWQAAAcuSURBVHjatFhrbFRF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\"/>";
    html += "</div></td><td>";
    html += (nivel_agua==0?"Iluminação abaixo do aceitavel":(nivel_temp==2?"Iluminação acima do aceitavel":(nivel_sol==3?"Sem Dados":"Iluminação OK")));
    html += "</td></tr>";
    //"<tr><td><a class=\"botao\" href=\"/configuracao\">Configuração</a> "+String(agua)+"</td><td></td><td><a class=\"botao\" href=\"/dados\">Dados</a> "+String(temp)+"ºC</td></tr>
    html += "</table>";
  }
  html += "</body></html>";
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
  if(plantaAtual == 0) return;
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
