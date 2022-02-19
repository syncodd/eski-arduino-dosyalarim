void setup() {  
  // Arduino Çalıştığında :  
    
  pinMode(13, OUTPUT);  
  // 13. pini çııkış olarak tanımlıyoruz.  
}  
  
void loop() {  
  // Arduino Çalıştığı sürece :  
    
  digitalWrite(13, HIGH);  
  // 13. pine elektrik gönder.  
    
  delay(1000);  
  // 1 saniye bekle.  
    
  digitalWrite(13, LOW);  
  // 13. pine giden elektriği kes.  
    
  delay(1000);  
  // 1 saniye bekle.  
} 
