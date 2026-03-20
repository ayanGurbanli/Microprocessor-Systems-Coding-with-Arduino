
void setup() {
Serial.begin(9600);
Serial.println("Enter two numbers to subtract:");
}

void loop() {

  if (Serial.available() > 0) {
  uint8_t a, b;
  

  a = Serial.parseInt();
  b = Serial.parseInt();

  // check if eeprom is busy before reading
  while(Serial.available() > 0) Serial.read();

  uint8_t status;
  uint8_t sreq_value;

  asm volatile (
    "MOV r15, %[a]\n" // load value of a into register 15
    "MOV r16, %[b]\n" // load value of b into register 16
    "SUB r15, r16\n" // subtract register 16 from 15
    "IN %[sr], __SREG__ \n" // read the status register into the status variable
    "MOV %[res], R15" // move the math result into the res variable
    : [res] "=r" (sreq_value),
      [sr] "=r" (status)
    : [a] "r" (a),
      [b] "r" (b)
    : "r15", "r16" // tell the compiler these registers are being used
  );


  // extract the zero flag (bit 1) and carry flag (bit 0) from the status byte (SREG)
  int zerof = (status >> 1) & 1;  
  int carryf = (status >> 0) & 0x1;

  

  Serial.print("Operation: "); Serial.print(a); Serial.print(" - "); Serial.println(b);
    Serial.print("Result: "); Serial.println(sreq_value);
    Serial.print("Zero Flag: "); Serial.println(zerof);
    Serial.print("Carry Flag: "); Serial.println(carryf);

  if (carryf) {
      Serial.println("Evidence: Carry is SET. This is an unsigned underflow (a < b).");
    }

  
  Serial.println("Enter two numbers again to subtract:");
  }

}

