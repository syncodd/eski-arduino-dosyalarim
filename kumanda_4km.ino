/*
Bu kod verici ile virtualwire kütüphanesini
kullanarak alıcıya mesaj göndermemizi sağlar. 
*/
#include <VirtualWire.h> //kütüphanemizi ekledik.
void setup()
{
vw_set_tx_pin(12);// edit okoman: bu parametre programda yoktu sonradan eklendi
vw_setup(2000); //2sn?de bir çalıştırmak için (edit okoman: yaklaşık veri trahasfer hızıdır hatalı açıklama yapılmış) virtualwire?ı başlatır.
}
void loop()
{
   send("hello");//göndereceğimiz mesaj
    delay(1000); //1sn bekle
    }
   void send (char *message) /*mesajı ulaştırmak için 
   loop kodu send fonksiyonunu çağırır ve bu da mesajın ulaştırılması 
   için bekler.*/
    {
      vw_send((uint8_t *)message, strlen(message));
       vw_wait_tx(); // mesaj gidene kadar bekle.
    }
