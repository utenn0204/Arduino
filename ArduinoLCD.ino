#include <Wire.h> 
#include <LiquidCrystal_I2C.h>    
LiquidCrystal_I2C LCD(0x27,20,4); //設定LCD顯示器位置0x27,設定LCD大小為20*4

#include <DS3231.h>
DS3231 rtc(6,7);               //設定時間模組SDA,SCL位置為Arduino第6,7腳
Time t;                       //t為時間模組time的變數

#include <DHT.h>
DHT dht(2,DHT11);            //設定溫溼度感測器DHT接腳位置為Arduino第2腳

#include <Ultrasonic.h>
#define TRIG_PIN 10          //設定超音波距離感測器trig接角位置為Arduino第10腳
#define ECHO_PIN 11         //設定超音波距離感測器echo接角位置為Arduino第11腳
Ultrasonic us(TRIG_PIN,ECHO_PIN);
int dist;

void setup() 
{
  LCD.init();
  LCD.backlight();
  LCD.clear();
  rtc.begin();
  dht.begin();
  delay(500);
  pinMode(5,OUTPUT);//蜂鳴器IN接腳位置為Arduino第5腳
}

void displayTime()
{
  t=rtc.getTime();// t函數從時間模組提取時間
  LCD.setCursor(0,0);//在LCD第1行第1個字輸入(0為第1行、第1個字)
  LCD.print("Time: ");
  LCD.print(t.hour);
  LCD.print(":");
  LCD.print(t.min);
  LCD.print(":");
  LCD.print(t.sec);
  LCD.print("   ");
}
void loop() 
{ 
  delay(100);
  displayTime();
  
  float h = dht.readHumidity(); //濕度值輸入到h函數裡
  float t = dht.readTemperature(); //攝氏值輸入到t函數裡
  LCD.setCursor(0,1); //在LCD第2行第1個字輸入
  LCD.print("Hum ");
  LCD.print(h);
  LCD.print(" % ");
  LCD.print(t);
  LCD.print(" C    ");
   
  dist=us.read(CM);//超音波距離輸入到dist函數裡
  LCD.setCursor(0,2); //在LCD第3行第1個字輸入
  LCD.print("Distance: ");
  LCD.print(dist);
  LCD.print(" cm");
  LCD.print("   ");
  
  if (dist<10)//判斷超音波感測距離是否位於10公分內
  {
    LCD.setCursor(3,3); //在LCD第4行第4個字輸入
    LCD.print("** WARNING **");
    tone(5,500); //蜂鳴器響起
    delay(300);
    noTone(5); //關閉蜂鳴器
  }
  else
  {
    LCD.setCursor(3,3);
    LCD.print("             ");
  }
} 
