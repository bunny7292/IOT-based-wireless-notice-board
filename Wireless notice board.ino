
//IOT based Wireless Smart Notice Board

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);



AsyncWebServer server(80);
 
const char* ssid = "realme GT Master Edition";  //wifi ssid
const char* password = "gotohell";   //wifi password
 
const char* PARAM_INPUT_1 = "input1";
 
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
    <title>IOT Based Wireless Notice Board</title>
    <meta name="viewport" content="width=device-width, initial-scale=5">
    <script src="https://cdn.tailwindcss.com"></script>
    <link rel = "icon" href = 
"https://upload.wikimedia.org/wikipedia/en/d/d4/Asansol_Engineering_College_Logo.png" 
        type = "image/x-icon">
    </head><body>


<div class="flex min-h-full flex-col justify-center px-6 py-12 lg:px-8">
  <div class="sm:mx-auto sm:w-full sm:max-w-sm">
    <img class="mx-auto h-10 w-auto" src="https://upload.wikimedia.org/wikipedia/en/thumb/d/d4/Asansol_Engineering_College_Logo.png/220px-Asansol_Engineering_College_Logo.png" alt="Your Company">
    <h2 class="mt-10 text-center text-2xl font-bold leading-9 tracking-tight text-gray-900">IOT Based Wireless Notice Board</h2>
  </div>

  <div class="mt-10 sm:mx-auto sm:w-full sm:max-w-sm">
    <form class="space-y-6" action="/get">
      <div>
        <label for="email" class="block text-sm font-medium leading-6 text-gray-900">Enter the text to Display :</label>
        <div class="mt-2">
          <input type="text" name="input1" required class="block w-full rounded-md border-0 py-1.5 text-gray-900 shadow-sm ring-1 ring-inset ring-gray-300 placeholder:text-gray-400 focus:ring-1 focus:ring-inset focus:ring-indigo-400 sm:text-sm sm:leading-6">
        </div>
      </div>

      <div>
        <button type="submit" value="Send" class="flex w-full justify-center rounded-md bg-indigo-600 px-3 py-1.5 text-sm font-semibold leading-6 text-white shadow-sm hover:bg-indigo-500 focus-visible:outline focus-visible:outline-2 focus-visible:outline-offset-2 focus-visible:outline-indigo-600">Display</button>
      </div>
    </form>
</div>

<div class="bg-white py-24 sm:py-32">
  <div class="mx-auto grid max-w-7xl gap-x-8 gap-y-20 px-6 lg:px-8 xl:grid-cols-3">
    <div class="max-w-2xl">
      <h2 class="text-3xl font-bold tracking-tight text-gray-900 sm:text-4xl">Meet our Team</h2>
    </div>
    <ul role="list" class="grid gap-x-8 gap-y-12 sm:grid-cols-2 sm:gap-y-16 xl:col-span-2">
      <li>
        <div class="flex items-center gap-x-6">
          <div>
            <h3 class="text-base font-semibold leading-7 tracking-tight text-gray-900">Partha Sarathi Pal</h3>
            <p class="text-sm font-semibold leading-6 text-indigo-600">ECE Sec-A Roll- 1080321120</p>
            <h3 class="text-base font-semibold leading-7 tracking-tight text-gray-900">Swarnali Mukherjee</h3>
            <p class="text-sm font-semibold leading-6 text-indigo-600">ECE Sec-A Roll- 1080321121</p>
            <h3 class="text-base font-semibold leading-7 tracking-tight text-gray-900">Suvam Sadhu</h3>
            <p class="text-sm font-semibold leading-6 text-indigo-600">ECE Sec-A Roll- 1080320008</p>
            <h3 class="text-base font-semibold leading-7 tracking-tight text-gray-900">Ritwick Bhattacharya</h3>
            <p class="text-sm font-semibold leading-6 text-indigo-600">ECE Sec-A Roll- 108032119</p>

          </div>
</div>


</body>
</html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  lcd.begin(16,2);
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("System Booted");
  delay(500);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  lcd.clear();
  lcd.print("Connecting to Wifi...");
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!");
    lcd.clear();
    lcd.print("Faliure!!");
    
    return;
  }
  else
      { 
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print("Established");
        delay(500);
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print("Starting");
        delay(500);
      }
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Waiting..");
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
 
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });
 
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String message;
    String inputParam;
    if (request->hasParam(PARAM_INPUT_1)) {
      message = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
       lcd.clear();
       lcd.setCursor(0,0);
      
      lcd.print(message);
    }
    else {
      message = "No message sent";
      inputParam = "none";
    }
    Serial.println(message);
   
  request->send(200, "text/html", index_html);
  });
  server.onNotFound(notFound);
  server.begin();
}

void loop()
{
    for (int positionCounter = 0; positionCounter < 29; positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(500);
  }
}
