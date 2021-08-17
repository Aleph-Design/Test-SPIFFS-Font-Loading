#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPIFFS.h>

TFT_eSPI *pTft = NULL;

void listSPIFFS();

void setup() 
{
  Serial.begin(115200);
  vTaskDelay(500 / portTICK_PERIOD_MS);

  // Check for SPIFFS
  //
  if (!SPIFFS.begin()) 
  {
    Serial.println("SPIFFS initialisation failed!");
    while (1) yield(); // Stay here twiddling thumbs waiting
  }
  Serial.println("\r\nSPIFFS available!\n");

  listSPIFFS();


  // Create an instance of class TFT_eSPI and assign it's address to the
  // pointer. Now we can pass the pointer around and use methods in the
  // class TFT_eSPI.
  //
  pTft = new TFT_eSPI();

  // pTft->loadFont("/NotoSansBold-36");
  pTft->loadFont("/NotoSansBold-36", SPIFFS);   // Font file /NotoSansBold-36 not found!
  // pTft->loadFont("NotoSansBold-36", SPIFFS);   --> Guru Meditation Error: Core  1 panic'ed (StoreProhibited). Exception was unhandled.
  // pTft->loadFont("/NotoSansBold-36");          --> Font file /NotoSansBold-36 not found!
  // pTft->loadFont("/NotoSansBold-36.vlw");      --> Font file /NotoSansBold-36.vlw not found!

}

void loop() 
{
  // put your main code here, to run repeatedly:
}

/*
* This is the exact same program in Arduino.
* It gives as output:
* SPIFFS initialization succesfull
* ================================
*
* ---Dir: /:
* File name: /NotoSansBold-15.vlw
* File name: /SansSerif36.vlw
* File name: /NotoSansBold-36.vlw
*/

void listSPIFFS()
{
  Serial.printf("---Dir: /:\n");

  fs::File root = SPIFFS.open("/", "r");
  fs::File file = root.openNextFile("r");

  while(file)
  { 
      Serial.printf("File name: %s\n", file.name());
      file = root.openNextFile("r");
  }

} // end listSPIFFS() --------------------------------------------------------

