
 
/*
 * Sketch: ESP8266_Part8_04_AutoUpdate_DHT11
 * Intended to be run on an ESP8266
 */
 
String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
 
String html_1 = R"=====(
<!DOCTYPE html>
<html>
 <head>
  <meta name='viewport' content='width=device-width, initial-scale=1.0'/>
  <meta charset='utf-8'>
  
  <style>
html { font-family: Helvetica; display: inline-block; text-align: center;}
body{background-position:center;background: url('https://s1.best-wallpaper.net/wallpaper/m/1801/Underground-parking_m.webp');background-size: cover;background-repeat: no-repeat; background-attachment: fixed;}
@media screen and (max-width: 1000px){body{height:40%;width:auto;}}

h2{ text-align: center;z-index: 10000;color:red;}
.boit{ margin-top:10%;text-align: center;z-index:1000;}
#V1{z-index:1000; width:10%;height:15%; padding: 2%;display: inline-block;margin:2%;text-align: center;box-shadow:1px 1px 3px grey; border-radius: 40%;  font-size: 25px; color: white; text-align: center;}
#Val1{visibility: hidden;}
#V2{z-index:1000; width:10%;height:15%;padding: 2%;display: inline-block;margin:2%;text-align: center;box-shadow:1px 1px 3px grey; border-radius: 40%;  font-size: 25px; color: white; text-align: center;}
#Val2{visibility: hidden;}
#V3{z-index:1000; width:10%;height:15%; padding: 2%;display: inline-block;margin:2%;text-align: center;box-shadow:1px 1px 3px grey; border-radius: 40%;  font-size: 25px; color: white; text-align: center;}
#Val3{visibility: hidden;}
#V4{z-index:1000; width:10%;height:15%; padding: 2%;display: inline-block;margin:2%;text-align: center;box-shadow:1px 1px 3px grey; border-radius: 40%;  font-size: 25px; color: white; text-align: center;}
#Val4{visibility: hidden;color: #fff;}
#txt{color: #fff;}
h4{position:absolute;color: rgb(255, 255, 255);margin-top:-5%;font-size: 20px}
h3{text-align: center;margin:0%;margin-bottom:2%; padding:10px 0;}
#txt2{ width:auto ;display: inline-block;margin:3%;text-align: center;padding:0.1%;color: #fff;}
#Val0{visibility: hidden;}

@media screen and (min-width: 1000px)and (max-width: 1400px){#txt2{width:55%;}}
@media screen and (max-width: 1000px){#txt2{width:80%;}}


@media screen and (max-width: 700px){ #V1{margin-left:38%;display:block;max-width:200px;min-width:100px;}#V2{margin-left:38%;display:block;max-width:200px;min-width:100px;}#V3{margin-left:38%;display:block;max-width:200px;min-width:100px;}#V4{margin-left:38%;display:block;max-width:200px;min-width:100px;}}
  </style>
   <script> 

 
  function updateTime() 
{  
   var d = new Date();
   var t = "";
   t = d.toLocaleTimeString();
   document.getElementById('P_time').innerHTML = t;
}

    function updateTemp() 
    {  
       ajaxLoad('getTemp'); 
    }
 
    var ajaxRequest = null;
    if (window.XMLHttpRequest)  { ajaxRequest =new XMLHttpRequest(); }
    else                        { ajaxRequest =new ActiveXObject("Microsoft.XMLHTTP"); }
 
    function ajaxLoad(ajaxURL)
    {
      if(!ajaxRequest){ alert('AJAX is not supported.'); return; }
 
      ajaxRequest.open('GET',ajaxURL,true);
      ajaxRequest.onreadystatechange = function()
      {
        if(ajaxRequest.readyState == 4 && ajaxRequest.status==200)
        {
          var ajaxResult = ajaxRequest.responseText;
          var tmpArray = ajaxResult.split(",");
          
          document.getElementById('Val').innerHTML = tmpArray[4];
          document.getElementById('Val1').innerHTML = tmpArray[0];
          document.getElementById('Val2').innerHTML = tmpArray[1];
          document.getElementById('Val3').innerHTML = tmpArray[2];
          document.getElementById('Val4').innerHTML = tmpArray[3];
        

         
            if( tmpArray[4] == 0){
                document.getElementById("txt").innerHTML = "il n y a pas de place ";
                    
                      if( tmpArray[0] == 1){
                    document.getElementById('V1').style.backgroundColor = "green";
                    
                  }
                  else{
                    document.getElementById('V1').style.backgroundColor = "red";
                  }
                  if( tmpArray[1] == 1){
                    document.getElementById('V2').style.backgroundColor = "green";
                  }
                  else{
                    document.getElementById('V2').style.backgroundColor = "red";
                  }
                  if( tmpArray[2] == 1){
                    document.getElementById('V3').style.backgroundColor = "green";
                  }
                  else{
                    document.getElementById('V3').style.backgroundColor = "red";
                  }
                  if( tmpArray[3] == 1){
                    document.getElementById('V4').style.backgroundColor = "green";
                  }
                  else{
                    document.getElementById('V4').style.backgroundColor = "red";
                  }
            }
            else
            {
                    if( tmpArray[0] == 1){
                    document.getElementById('V1').style.backgroundColor = "green";
                    
                  }
                  else{
                    document.getElementById('V1').style.backgroundColor = "red";
                  }
                  if( tmpArray[1] == 1){
                    document.getElementById('V2').style.backgroundColor = "green";
                  }
                  else{
                    document.getElementById('V2').style.backgroundColor = "red";
                  }
                  if( tmpArray[2] == 1){
                    document.getElementById('V3').style.backgroundColor = "green";
                  }
                  else{
                    document.getElementById('V3').style.backgroundColor = "red";
                  }
                  if( tmpArray[3] == 1){
                    document.getElementById('V4').style.backgroundColor = "green";
                  }
                  else{
                    document.getElementById('V4').style.backgroundColor = "red";
                  }
            }
         



        
          }
        
      }
    
      ajaxRequest.send();
    }
    
 
    var myVar1 = setInterval(updateTemp, 100);  
  var myVar2 = setInterval(updateTime, 100);
     

 
  </script>
 
 
  <title>Smart Parking</title>
 </head>
 
 <body>

     <h2 style="font-size: 70px; color: rgb(255, 255, 255);">Smart Parking</h2>

     <div class="boit">
     
      <div  id="V1">Voie 1 <span id="Val1"></span></div>
       <div  id="V2"> Voie 2<span id="Val2"></span></div>
       <div  id="V3"> Voie 3<span  id="Val3"></span></div>
        <div  id="V4">Voie 4<span id="Val4"></span></div>
        </div>
    
  <h3 id ="txt">le nombre de place vide est  <span id='Val'>...</span></h3>

 </body>
 
</html>
)====="; 
 
#include <ESP8266WiFi.h>

// change these values to match your network
char ssid[] = "iPhone hamza1";       //  your network SSID (name)
char pass[] = "123456789";            //  your network password
 
int LED1 = 0;// led connected to D0
int LED2 = 4;// led connected to D1
int LED3 = 5;// led connected to D2
int LED4 = 16;// led connected to D3
int LED0 = 9;
WiFiServer server(80);
String request = "";
 
 
void setup() 
{
    Serial.begin(115200);
    Serial.println();
    Serial.println("Serial started at 115200");
    Serial.println();
  pinMode(LED1, INPUT);
  pinMode(LED2, INPUT);
  pinMode(LED3, INPUT);
  pinMode(LED4, INPUT);
 
 
    // Connect to a WiFi network
    Serial.print(F("Connecting to "));  Serial.println(ssid);
    WiFi.begin(ssid, pass);
 
    while (WiFi.status() != WL_CONNECTED) 
    {
        Serial.print(".");
        delay(500);
    }
 
    Serial.println("");
    Serial.println(F("[CONNECTED]"));
    Serial.print("[IP ");              
    Serial.print(WiFi.localIP()); 
    Serial.println("]");
 
    // start a server
    server.begin();
    Serial.println("Server started");
 
} // void setup()
 
 
void loop() 
{
    WiFiClient client = server.available();     // Check if a client has connected
    if (!client)  {  return;  }
 
    request = client.readStringUntil('\r');     // Read the first line of the request
 
    Serial.println(request);
    Serial.println("");
 
    if ( request.indexOf("getTemp") > 0 )
     { 
          Serial.println("getTemp received");
           int val1;
           int val2;
           int val3;
           int val4;
           int val;
           


 val1=digitalRead(LED1);
        val2=digitalRead(LED2);
          val3=digitalRead(LED3);
         val4=digitalRead(LED4);
          
       


          
  val=val1+val2+val3+val4;
           
          
 
          // Reading temperature or humidity takes about 250 milliseconds!
          // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
   // Read temperature as Fahrenheit (isFahrenheit = true)

 
          if ( !isnan(val1) && !isnan(val2) && !isnan(val3) && !isnan(val4)&& !isnan(val))
          {
              client.print( header );
              client.print( val1 );   client.print( "," );  client.print( val2 );   client.print( "," );  client.print( val3 );  client.print( "," ); client.print( val4 );   client.print( "," ); client.print( val);
              Serial.println("data sent");
          }
          else
          {
              Serial.println("Error reading the sensor");
          }
     }
 
     else
     {
        client.flush();
        client.print( header );
        client.print( html_1 ); 
        Serial.println("New page served");
     }
 
    delay(5);
 
 
  // The client will actually be disconnected when the function returns and the 'client' object is destroyed
 
} // void loop()
