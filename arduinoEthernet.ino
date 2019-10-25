
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress server(192, 168, 1, 100);

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 1, 177);
EthernetServer HTTPserver(80);
EthernetClient HTTPclient;


unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;
String readString;
bool Auto = false;

int temp = 0;
char fan[5];
String data;
char OFF[] = "OFF";
char ON[] = "ON";
char Mode[] = "manual";

void fanON()
{
  char ON[] = "ON";
  digitalWrite(LED_BUILTIN, LOW);
  sprintf(fan, ON);
}

void fanOFF()
{
  char OFF[] = "OFF";
  digitalWrite(LED_BUILTIN, HIGH);
  sprintf(fan, OFF);
}

void modeAuto() {
  memset(Mode,NULL,sizeof(Mode));
  char temp[] = "auto";
  sprintf(Mode,temp);
}

void modeManual() {
  memset(Mode,NULL,sizeof(Mode));
  char temp[] = "manual";
  sprintf(Mode,temp);
}

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start the Ethernet connection:

  // try to congifure using IP address instead of DHCP:
  Ethernet.begin(mac, ip);
  HTTPserver.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.print("connecting to ");
  Serial.print(server);
  Serial.println("...");


  beginMicros = micros();
}

void loop() {
  temp++;
  temp += 2;
  if (temp > 500)
    temp = 0;

  if(strcmp(Mode,"auto")) {
      if (temp > 250) fanON();
      else fanOFF();
  }

  if (HTTPclient.connect(server, 3000)) {
    //    Serial.println("Sending to Server: ");
    HTTPclient.println("POST /data HTTP/1.1");
    Serial.print("POST /data HTTP/1.1");
    HTTPclient.println("Host: 192.168.1.177");
    HTTPclient.println("Content-Type: application/x-www-form-urlencoded");
    HTTPclient.println("Connection: close");
    HTTPclient.println("User-Agent: Arduino/1.0");
    HTTPclient.print("Content-Length: ");

    data = "fan=" + String(fan) + "&temp=" + String(temp) + "&mode=" + String(Mode);
    HTTPclient.println(data.length());
    //    Serial.println(data.length());
    HTTPclient.println();
    //    Serial.println(data);
    HTTPclient.print(data);
    HTTPclient.println();

  } else {
    //    Serial.println("connection failed");
  }

  // if the server's disconnected, stop the client:
  if (!HTTPclient.connected()) {
    endMicros = micros();
    //    Serial.println();
    //    Serial.println("disconnecting.");
    HTTPclient.stop();
  }

  EthernetClient client = HTTPserver.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (readString.length() < 50)
          readString += c;

        HTTPserver.write(c);
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of each analog input pin
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");
          }
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");

    if (readString.indexOf("mode=manual") > 0){
      modeManual();
      if (readString.indexOf("fan=ON") > 0) //checks for on
      {
        fanON();
        Serial.println("Fan is ON!");
      }
      else if (readString.indexOf("fan=OFF") > 0) //checks for off
      {
        fanOFF();
        Serial.println("Fan is OFF!");
      }
    }
    else if (readString.indexOf("mode=auto") > 0)
      modeAuto();

    Serial.println(readString);
    readString = "";
  }
}
