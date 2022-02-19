/*
Arduino?ya bağladığımız alıcıda görünen 
vericiden gönderilmiş mesajı serial monitorde
görüntülemek için 
*/
#include <VirtualWire.h> // Kütüphaneyi ekledik.
byte message[VW_MAX_MESSAGE_LEN]; // gelen mesajları tutmak için 
byte msgLength = VW_MAX_MESSAGE_LEN; // mesaj boyutu
void setup()
{
Serial.begin(9600);
Serial.println("Ready"); //Serial Monitor?de gözükecek mesaj 
vw_setup(2000); /*2sn?de bir çalıştırmak için (edit okoman: yaklaşık veri trahasfer hızıdır hatalı açıklama yapılmış)virtualwire?ı başlatır.*/ 
vw_rx_start(); // Alıcı başlat 
} 
void loop() { 
if (vw_get_message(message, &msgLength)) /*mesaj hazır ise tamam ve mesaj serial monitorde gözükür*/ 
{ Serial.print("Got: "); 
for (int i = 0; i < msgLength; i++){ 
Serial.write(message[i]); 
} 
Serial.println(); 
} 
}
