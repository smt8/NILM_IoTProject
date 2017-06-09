int N = 1000;
int count = 0;
double sum = 0.0, pf, vsq = 0.0, isq = 0.0, AcP, RP, ApP, I = 0.0, V = 0.0;

void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(9600);
  
}

void loop() {
  delay(1);
  count++;
  // read the input on analog pin 0:
  I = analogRead(A0);
  I = (((I * 0.0049) - 2.50) / 33) * 2000;
  // print out the value you read:
  V = analogRead(A4);
  V = (((V * 0.0049) - 2.50) * 122 / 22 * 230 / 9.2); // 122/22 is v-divider,2k is step up in ct
  if (count > N)
  {
    sum = sum / N;
    vsq = sqrt(vsq / N); //RMS V
    isq = sqrt(isq / N); //RMS I in mA
    pf = sum / (vsq * isq); //Power factor
    AcP = abs(V * I * pf); //Active power
    RP = abs(V * I * sqrt(1 - sq(pf))); //Reactive power
    ApP = sqrt(sq(AcP) + sq(RP)); //Apparent power
        Serial.print(vsq);
        Serial.print(";");
        Serial.print(isq);
        Serial.print(";");
        Serial.print(pf);
        Serial.print(";");
        Serial.print(AcP);
        Serial.print(";");
        Serial.print(RP);
        Serial.print(";");
        Serial.println(ApP); //ends with new line
    Serial.flush(); //Waits till all data is sent
    sum = 0.0;
    count = 0;
    vsq = 0.0;
    isq = 0.0;
    sum = sum + abs(I) * abs(V);
    vsq = vsq + sq(V);
    isq = isq + sq(I);
  }
  else
  {
    sum = sum + abs(I) * abs(V);
    vsq = vsq + sq(V);
    isq = isq + sq(I);
  }
}

