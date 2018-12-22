
int R[] = {6,11,10,3,17,4,8,9  }; //点阵灯行引脚
int C[] = {A0,7,1,5,13,0,12,16 };  //点阵灯列引脚
 
unsigned char biglove[8][8] =       //大“心型”的数据
{
  0,0,0,0,0,0,0,0,
  0,1,1,0,0,1,1,0,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  0,1,1,1,1,1,1,0,
  0,0,1,1,1,1,0,0,
  0,0,0,1,1,0,0,0,
};
 
unsigned char smalllove[8][8] =      //小“心型”的数据
{
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,1,0,0,1,0,0,
  0,1,1,1,1,1,1,0,
  0,1,1,1,1,1,1,0,
  0,0,1,1,1,1,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,0,0,0,0,0,
};

unsigned char smile1[8][8] =       //笑脸1的数据
{
  0,0,0,0,0,0,0,0,
  0,1,0,0,0,0,1,0,
  1,0,1,0,0,1,0,1,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,1,0,0,1,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,0,0,0,0,0,
};
unsigned char sad1[8][8] =       //哭脸1的数据
{
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  1,1,1,0,0,1,1,1,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,1,1,0,0,0,
  0,0,1,0,0,1,0,0,
  0,0,0,0,0,0,0,0,
};
unsigned char sad2[8][8] =       //哭脸2的数据
{
  0,0,0,0,0,0,0,0,
  1,1,1,0,0,1,1,1,
  0,1,0,0,0,0,1,0,
  0,1,0,0,0,0,1,0,
  0,1,0,0,0,0,1,0,
  0,0,0,1,1,0,0,0,
  0,0,1,0,0,1,0,0,
  0,0,0,0,0,0,0,0,
};

unsigned char smile2[8][8] =       //笑脸2的数据
{
  0,0,0,0,0,0,0,0,
  0,1,0,0,0,0,1,0,
  1,0,1,0,0,1,0,1,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,1,0,1,1,0,1,0,
  0,0,1,0,0,1,0,0,
  0,0,0,0,0,0,0,0,
};
unsigned char smile3[8][8] =       //笑脸3的数据
{
  0,0,0,0,0,0,0,0,
  0,1,0,0,0,0,1,0,
  0,1,0,0,0,0,1,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,1,0,0,0,0,1,0,
  0,0,1,1,1,1,0,0,
  0,0,0,0,0,0,0,0,
};
 
#define SSID        "iodine" //Wi-Fi名称
#define PASSWORD    "iiiodine"//Wi-Fi密码
#define HOST_NAME   "api.heclouds.com"
#define DEVICEID    "503174997" //OneNet上的设备ID
#define PROJECTID   "184525" //OneNet上的产品ID
#define HOST_PORT   (80)
String apiKey="PurlAB9wksRuWo0cyGV42N0mm3E=";//与你的设备绑定的APIKey

#define INTERVAL_SENSOR   17000             //定义传感器采样时间间隔  597000
#define INTERVAL_NET      17000             //定义发送时间
//传感器部分================================   
#include <Wire.h>                                  //调用库  
#include <ESP8266.h>
#include <I2Cdev.h>                                //调用库  
/*******温湿度*******/
#include <Microduino_SHT2x.h>
/*******光照*******/
#define  sensorPin_1  A0
#define IDLE_TIMEOUT_MS  3000      // Amount of time to wait (in milliseconds) with no data 
                                   // received before closing the connection.  If you know the server
                                   // you're accessing is quick to respond, you can reduce this value.
#include <dht11.h>
dht11 DHT11;
#define PIN_DHT11 2//温湿度

#include "MQ135.h"
const int ANALOGPIN=4;
MQ135 gasSensor = MQ135(ANALOGPIN);//空气质量

//WEBSITE     
char buf[10];

#define INTERVAL_sensor 2000
unsigned long sensorlastTime = millis();

float tempOLED, humiOLED, lightnessOLED,waterOLED,gasOLED;

#define INTERVAL_OLED 1000

String mCottenData;
String jsonToSend;

//3,传感器值的设置 
float sensor_tem, sensor_hum, sensor_lux,sensor_water,sensor_gas;                    //传感器温度、湿度、光照   
char  sensor_tem_c[7], sensor_hum_c[7], sensor_lux_c[7] ,sensor_water_c[7],sensor_gas_c[7];    //换成char数组传输
#include <SoftwareSerial.h>
#define EspSerial mySerial
#define UARTSPEED  9600
SoftwareSerial mySerial(2, 3); /* RX:D3, TX:D2 */
ESP8266 wifi(&EspSerial);
//ESP8266 wifi(Serial1);                                      //定义一个ESP8266（wifi）的对象
unsigned long net_time1 = millis();                          //数据上传服务器时间
unsigned long sensor_time = millis();                        //传感器采样时间计时器

//int SensorData;                                   //用于存储传感器数据
String postString;                                //用于存储发送数据的字符串
//String jsonToSend;                                //用于存储发送的json格式参数

Tem_Hum_S2 TempMonitor;

void setup(void)     //初始化函数  
{ 
  //循环定义行列PIN 为输出模式
  for(int i = 0;i<8;i++)
  {
    pinMode(R[i],OUTPUT);
    pinMode(C[i],OUTPUT);
  }    
  //以上为点阵灯初始化
  //初始化串口波特率  
    Wire.begin();
    Serial.begin(115200);
    while (!Serial); // wait for Leonardo enumeration, others continue immediately
    Serial.print(F("setup begin\r\n"));
    delay(100);
    pinMode(sensorPin_1, INPUT);

  WifiInit(EspSerial, UARTSPEED);

  Serial.print(F("FW Version:"));
  Serial.println(wifi.getVersion().c_str());

  if (wifi.setOprToStationSoftAP()) {
    Serial.print(F("to station + softap ok\r\n"));
  } else {
    Serial.print(F("to station + softap err\r\n"));
  }

  if (wifi.joinAP(SSID, PASSWORD)) {
    Serial.print(F("Join AP success\r\n"));

    Serial.print(F("IP:"));
    Serial.println( wifi.getLocalIP().c_str());
  } else {
    Serial.print(F("Join AP failure\r\n"));
  }

  if (wifi.disableMUX()) {
    Serial.print(F("single ok\r\n"));
  } else {
    Serial.print(F("single err\r\n"));
  }

  Serial.print(F("setup end\r\n"));
    
  
}
void loop(void)     //循环函数  
{   
  if (sensor_time > millis())  sensor_time = millis();  
    
  if(millis() - sensor_time > INTERVAL_SENSOR)              //传感器采样时间间隔  
  {  
    getSensorData();                                        //读串口中的传感器数据
    sensor_time = millis();
  }  

    
  if (net_time1 > millis())  net_time1 = millis();
  
  if (millis() - net_time1 > INTERVAL_NET)                  //发送数据时间间隔
  {                
    updateSensorData();                                     //将数据上传到服务器的函数
    net_time1 = millis();
  }
    float tem = TempMonitor.getTemperature();  //温度
    float hum = TempMonitor.getHumidity();     //湿度
    float lux = analogRead(A0);                //亮度
    float water = analogRead(A5);              //水位
    float gas = gasSensor.getRZero();          //空气质量
    if(lux<400&&gas>1000)
    for(int i = 0 ; i < 100 ; i++)        //循环显示100次
  {
    Display(sad2);                   //显示哭脸2
  }
  if(lux>=400&&gas>1000)
    for(int i = 0 ; i < 100 ; i++)        //循环显示100次
  {
    Display(smile3);                   //显示笑脸3
  }
  if(lux>=400&&gas<1000)
    for(int i = 0 ; i < 100 ; i++)        //循环显示100次
  {
    Display(smile1);                   //显示笑脸1
  }
   if(lux<400&&gas<1000)
    for(int i = 0 ; i < 100 ; i++)        //循环显示100次
  {
    Display(sad1);                   //显示哭脸1
  }
}

void getSensorData(){  
    sensor_tem = TempMonitor.getTemperature();  //温度
    sensor_hum = TempMonitor.getHumidity();   //湿度
    sensor_lux = analogRead(A0);//光照
    sensor_water = analogRead(A5);   //水位
    sensor_gas = gasSensor.getRZero(); //空气质量
    delay(1000);
    dtostrf(sensor_tem, 2, 1, sensor_tem_c);
    dtostrf(sensor_hum, 2, 1, sensor_hum_c);
    dtostrf(sensor_lux, 3, 1, sensor_lux_c);
    dtostrf(sensor_water, 3, 1, sensor_water_c);
     dtostrf(sensor_gas, 3, 1, sensor_gas_c);
}
void updateSensorData() {
  if (wifi.createTCP(HOST_NAME, HOST_PORT)) { //建立TCP连接，如果失败，不能发送该数据
    Serial.print("create tcp ok\r\n");

jsonToSend="{\"Temperature\":";
    dtostrf(sensor_tem,1,2,buf);
    jsonToSend+="\""+String(buf)+"\"";
    jsonToSend+=",\"Humidity\":";
    dtostrf(sensor_hum,1,2,buf);
    jsonToSend+="\""+String(buf)+"\"";
    jsonToSend+=",\"Light\":";
    dtostrf(sensor_lux,1,2,buf);
     jsonToSend+="\""+String(buf)+"\"";
    jsonToSend+=",\"water\":";
    dtostrf(sensor_water,1,2,buf);
     jsonToSend+="\""+String(buf)+"\"";
    jsonToSend+=",\"gas\":";
    dtostrf(sensor_gas,1,2,buf);
    jsonToSend+="\""+String(buf)+"\"";
    jsonToSend+="}";



    postString="POST /devices/";
    postString+=DEVICEID;
    postString+="/datapoints?type=3 HTTP/1.1";
    postString+="\r\n";
    postString+="api-key:";
    postString+=apiKey;
    postString+="\r\n";
    postString+="Host:api.heclouds.com\r\n";
    postString+="Connection:close\r\n";
    postString+="Content-Length:";
    postString+=jsonToSend.length();
    postString+="\r\n";
    postString+="\r\n";
    postString+=jsonToSend;
    postString+="\r\n";
    postString+="\r\n";
    postString+="\r\n";

  const char *postArray = postString.c_str();                 //将str转化为char数组
  Serial.println(postArray);
  wifi.send((const uint8_t*)postArray, strlen(postArray));    //send发送命令，参数必须是这两种格式，尤其是(const uint8_t*)
  Serial.println("send success");   
     if (wifi.releaseTCP()) {                                 //释放TCP连接
        Serial.print("release tcp ok\r\n");
        } 
     else {
        Serial.print("release tcp err\r\n");
        }
      postArray = NULL;                                       //清空数组，等待下次传输数据
  
  } else {
    Serial.print("create tcp err\r\n");
  }
}
void Display(unsigned char dat[8][8])   //点阵灯显示函数
{
  for(int c = 0; c<8;c++)
  {
    digitalWrite(C[c],LOW);//选通第c列
 
    //循环
    for(int r = 0;r<8;r++)
    {
      digitalWrite(R[r],dat[r][c]);
    }
    delay(1);
    Clear();  //清空显示去除余晖
  }
}
 
void Clear()                          //点阵灯清空显示
{
  for(int i = 0;i<8;i++)
  {
    digitalWrite(R[i],LOW);
    digitalWrite(C[i],HIGH);
  }
}
