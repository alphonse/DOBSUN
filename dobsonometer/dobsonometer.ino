 /*
    Combined Dobson meter-sun photometer
    Copyright (c) 2014, Al Fischer
  ----------------------------------------------------------------------------------------- 
    Portions of this code have been adapted and/or reprinted from adafruit.com and 
    playground.arduino.cc; for more information see the readme.
    
    https://learn.adafruit.com/adafruit-color-sensors/overview
    http://playground.arduino.cc/Code/EEPROMReadWriteLong
    
    This work is released under GPLv3.  http://www.gnu.org/copyleft/gpl.html
  ------------------------------------------------------------------------------------------
*/

  #include <EEPROM.h>
  #include <Wire.h>
  #include "Adafruit_TCS34725.h"
  
  String intTime = "24";
  boolean echo = false;
  char inChar[16];
  int i = 0;
  String inCharStr;
  boolean err = false;
  String noAvgStr;
  int noAvg;
  float aVolt;
  float totalVolt;
  String dataStr = "";
  
  // function for writing long values to EEPROM
  // Kevin Elsenberger, arduino.cc
  void EEPROMWritelong(int address, long value)
      {
      //Decomposition from a long to 4 bytes by using bitshift.
      //One = Most significant -> Four = Least significant byte
      byte four = (value & 0xFF);
      byte three = ((value >> 8) & 0xFF);
      byte two = ((value >> 16) & 0xFF);
      byte one = ((value >> 24) & 0xFF);

      //Write the 4 bytes into the eeprom memory.
      EEPROM.write(address, four);
      EEPROM.write(address + 1, three);
      EEPROM.write(address + 2, two);
      EEPROM.write(address + 3, one);
      }
  
  // function for reading long values from EEPROM
  // Kevin Elsenberger, arduino.cc  
  long EEPROMReadlong(long address)
      {
      //Read the 4 bytes from the eeprom memory.
      long four = EEPROM.read(address);
      long three = EEPROM.read(address + 1);
      long two = EEPROM.read(address + 2);
      long one = EEPROM.read(address + 3);

      //Return the recomposed long by using bitshift.
      return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
      }
  
  // initialize RGB sensor
  Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_24MS, TCS34725_GAIN_1X);

  // ------------------------------------------------------------------------------------------------------------
  
  void setup() {
    Serial.begin(9600);
  }

  // ------------------------------------------------------------------------------------------------------------
  
  void loop() {
    // get RGB sensor data
    uint16_t c, r, g, b, a, total;
    tcs.getRawData(&r, &g, &b, &c);
    
    // get UV sensor data
    a = analogRead(A0);
    aVolt = a * (5000.0 / 1023.0);
  
    total = analogRead(A1);
    totalVolt = total * (5000.0 / 1023.0);
    
    // listen for serial commands and write to string
    while (Serial.available() > 0) {
      inChar[i] = Serial.read();
      i++;
    }
    if (i > 0) {
      inCharStr = String(inChar);
    }
    
    // identify self when asked (or be elusive) -------------------------------------
    if (inCharStr == "*IDN?\n") {
      Serial.println("I'm a Dobson meter and sun photometer!");
      Serial.println("v1.0, (c.c.) Al Fischer 2014");
    }
    
    // set integration time (for N ms) ----------------------------------------------
    if (inCharStr.startsWith("intTime.")) {
      intTime = inCharStr.substring(8);
      if (intTime.startsWith("2.5")) {
        tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_2_4MS);
      }
      else if(intTime.startsWith("25")) {
        tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_24MS);
      }
      else if(intTime.startsWith("50")) {
        tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_50MS);
      }
      else if(intTime.startsWith("100")) {
        tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_101MS);
      }
      else if(intTime.startsWith("150")) {
        tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_154MS);
      }
      else if(intTime.startsWith("700")) {
        tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_700MS);
      }
      else {
         err = true;
         Serial.println("Error. Choose from 2.5, 25, 50, 100, 150, or 700!\n");
       }
      if (echo == true & err == false) {
        Serial.println("Integration Time Set: " + String(intTime) + " ms");
      }
      err == false;
  }
  if (inCharStr.startsWith("intTime?")) {
      intTime.trim();
      dataStr = intTime + " ms";
  }
  
  // take reading (for N averages and write to EEPROM) ----------------------------
  else if (inCharStr.startsWith("getMeas")) {
    noAvgStr = inCharStr.substring(8, 10);
    noAvgStr.trim();
    noAvg = noAvgStr.toInt();
    unsigned long rd = 0;
    unsigned long gr = 0;
    unsigned long bl = 0;
    unsigned long cl = 0;
    a = 0;
    total = 0;
    for (i = 0; i < noAvg; i++) {
       tcs.getRawData(&r, &g, &b, &c); 
       rd += r;
       gr += g;
       bl += b;
       cl += c;
       a += analogRead(A0);
       total += analogRead(A1);
       Serial.println("Averaging: " + String(i+1));
       if (i == (noAvg-1)) {
         int addr = EEPROM.read(0);
         r = rd/noAvg;
         g = gr/noAvg;
         b = bl/noAvg;
         c = cl/noAvg;
         aVolt = (a/noAvg) * (5000.0 / 1023.0);
         unsigned long aVoltMem = aVolt * 100;
         totalVolt = (total/noAvg) * (5000.0 / 1023.0);
         unsigned long totalVoltMem = totalVolt * 100;
         EEPROMWritelong(addr, c); 
         EEPROMWritelong(addr + 4, r);
         EEPROMWritelong(addr + 8, g);
         EEPROMWritelong(addr + 12, b);
         EEPROMWritelong(addr + 16, aVoltMem);
         EEPROMWritelong(addr + 20, totalVoltMem);
         addr = addr + 24;
         EEPROM.write(0, addr);
         if (echo = true) {
            Serial.print("Data saved at "); Serial.print(addr - 24); Serial.print(" through "); Serial.println(addr - 1);
        }
    }
    }
    i = 0;

  }
  
  // read data from EEPROM ----------------------------------------------
  else if (inCharStr.startsWith("displayMeas")) {
     int n = 1;
     int addr = EEPROM.read(0);
     for (i = 1; i < addr; i = i + 4) {
       if (n == 1) {
         dataStr = String(EEPROMReadlong(i)) + ", ";
       }
       else if (n % 6 == 0) {
         dataStr = dataStr + String(EEPROMReadlong(i)) + '\n';
       }
       else{dataStr = dataStr + String(EEPROMReadlong(i)) + ", ";}
       n = n++;
     }
     Serial.print('\n');
  }
  
  // (re)set beginning memory location for writing data -------------------
  else if (inCharStr.startsWith("memAddr.")) {
    String addrStr = inCharStr.substring(8, 10);
    addrStr.trim();
    int addr = addrStr.toInt();
    EEPROM.write(0, addr);
    if (echo = true) {
      Serial.println("Address set to: " + addrStr);
    }
  }
  // retrieve next save location -------------------------------------------
  else if (inCharStr.startsWith("memAddr?")) {
    int memPos = EEPROM.read(0);
    dataStr = "Current Memory Posistion: " + String(memPos);
  }
  
  // turn echo on or off ---------------------------------------------------
  else if (inCharStr.startsWith("echo")) {
    if (inCharStr == "echo.1\n"){
      echo = true;
      Serial.println("echo = true!");
    }
    else {echo = false;}
  }
  
  // print answers to serial port if there's been a request ----------------
  if (dataStr != " ") {
      Serial.println(dataStr);
       dataStr = " ";
  }
  
  // real-time/continuous data stream ---------------------------------------
  Serial.print(c); Serial.print(", "); Serial.print(r); Serial.print(", "); Serial.print(g); Serial.print(", "); Serial.print(b); Serial.print(", ");
  Serial.print(aVolt); Serial.print(", ");
  Serial.print(totalVolt); Serial.print('\n');
  
  // reset values for next go 'round ----------------------------------------
  i = 0;
  inCharStr = "";
  memset(inChar, 0, sizeof(inChar));
  
  delay(500);
  
  }
