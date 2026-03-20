volatile uint8_t count;

void setup() {
  Serial.begin(9600);

  // from EEPROM initialization
  // check if EEPROM is busy before reading
    while (EECR & 0x02);
      // select eeprom address 0
      EEAR = 0;
      // set the read enable bit
      EECR |= 0x01;
      // move the data from the eeprom data register to our variable
      count = EEDR;

  Serial.println("Count started from memory:");
  Serial.println(count);
}

void loop() {

  delay(1000);
  
  uint8_t a, b;

  asm volatile (
    "lds r24, count \n" // load the count variable from sram
    "inc r24 \n"        // increment the value in register 24
    "sts count, r24 \n" // store the new value back into sram
  );

  Serial.print("Count:");
  Serial.println(count);

  if (Serial.available()) {
    char command = Serial.read();
    if (command == 'S' || command == 's') {

      // wait for any previous eeprom write to finish
      while (EECR & 0x02);    

      // set target address and data to be saved
      EEAR = 0;
      EEDR = count;
      // set master write enable bit
      EECR |= 0x04;
      // set write enable bit to start the actual save
      EECR |= 0x02;

      Serial.println(">> Progress Saved to EEPROM.");

    } 

    else if (command == 'R') { 

      count = 0;

      Serial.println(">> Counter Reset to 0.");

    }
  }
} 




