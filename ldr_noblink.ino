//ldr dengan indikator LED
int hasilSensorLDDR; //variable untuk sensor LDR
void setup() {
  Serial.begin(9600); //serial monitor
  pinMode(6,OUTPUT); //set pin 6 sebagai output
}

void loop() {
  hasilSensorLDR=analogRead(0); //Hasil LDR = Hasil input pada pin 0
  if (hasilSesorLDR<10) // jika output dari ldr kurang dari 10
  {
    digitalWrite(6,HIGH); //aktifkan relay atau LED
  }
  else digitalWrite(6,LOW); //jika tidak, matika relay/LED
  Serial.println(hasilSensorLDR); //print hasil LDR ke serial mnitor
  delay(500); //delay setengah detik
}
