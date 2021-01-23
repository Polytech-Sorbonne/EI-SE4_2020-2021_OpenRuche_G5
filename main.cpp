#include "mbed.h"
#include "DHT.h"
#include "DS1820.h"
#include "HX711.h"

#define   DHT1_DATA_PIN  D6
#define   DHT2_DATA_PIN  D9

DS1820      ds1820_1(D2);  // substitute D8 with the actual pin name connected to the DS1820 sensor
DS1820      ds1820_2(D3);
DS1820      ds1820_3(D4);
DS1820      ds1820_4(D5);
AnalogIn Batterie(A6);
float       temp1 = 0;
float       temp2 = 0;
float       temp3 = 0;
float       temp4 = 0;
int         result = 0;
int batterie_level = 0;

DHT sensor1(DHT1_DATA_PIN, DHT22);                    //DHT(PinName pin, eType DHTtype)
DHT sensor2(DHT2_DATA_PIN, DHT22);                    //DHT(PinName pin, eType DHTtype)
HX711 loadcell(D12, D11);

Serial pc(USBTX, USBRX); // tx, rx
Serial device(D1, D0); // tx, rx

int main()
{
    float x =0.0f;;
    int error1 = 0;
    int error2 = 0;
    float h_int = 0.0f, c_int = 0.0f,h_ext = 0.0f,c_ext =0.0f;
    float balance=0.2f;
    pc.baud(9600);
    device.baud(9600);
    
    if (!ds1820_1.begin()){
        pc.printf("No DS1820 sensor found!\r\n");
        for(int i=0; i<10; i++)
        {
            ThisThread::sleep_for(250);
            if(ds1820_1.begin())
            {
                pc.printf("DS1820 sensor found on %d try\r\n", i+2);
                break;
            }
        }
    }
    else{
        pc.printf("DS1820 sensor found!\r\n");
    }
    
    if (!ds1820_2.begin()){
        pc.printf("No DS1820 sensor found!\r\n");
        for(int i=0; i<10; i++)
        {
            ThisThread::sleep_for(250);
            if(ds1820_2.begin())
            {
                pc.printf("DS1820 sensor found on %d try\r\n", i+2);
                break;
            }
        }
    }
    else{
        pc.printf("DS1820 sensor found!\r\n");
    }
    if (!ds1820_3.begin()){
        pc.printf("No DS1820 sensor found!\r\n");
        for(int i=0; i<10; i++)
        {
            ThisThread::sleep_for(250);
            if(ds1820_3.begin())
            {
                pc.printf("DS1820 sensor found on %d try\r\n", i+2);
                break;
            }
        }
    }
    else{
        pc.printf("DS1820 sensor found!\r\n");
    }
    if (!ds1820_4.begin()){
        pc.printf("No DS1820 sensor found!\r\n");
        for(int i=0; i<10; i++)
        {
            ThisThread::sleep_for(250);
            if(ds1820_4.begin())
            {
                pc.printf("DS1820 sensor found on %d try\r\n", i+2);
                break;
            }
        }
    }
    else{
        pc.printf("DS1820 sensor found!\r\n");
    }

    while(1) {
        x=Batterie.read();

        if (x > 0.81 )
        {
            batterie_level = 75;  
        }
        else if (x > 0.75 )
        {
            batterie_level = 50;  
        }
        else if (x > 0.70 )
        {
            batterie_level = 25;  
        }
        else 
        {
            batterie_level = 0;
        }

        int balance = ((loadcell.getValue() - 8469461)/21.5);
        pc.printf("Weight = %d\r\n", balance);
        
        ds1820_1.startConversion();   // start temperature conversion from analog to digital
        ds1820_2.startConversion();   // start temperature conversion from analog to digital
        ds1820_3.startConversion();   // start temperature conversion from analog to digital
        ds1820_4.startConversion();   // start temperature conversion from analog to digital

        ThisThread::sleep_for(1000);// let DS1820 complete the temperature conversion
        
        result = ds1820_1.read(temp1); // read temperature from DS1820 and perform cyclic redundancy check (CRC)
        result = ds1820_2.read(temp2);
        result = ds1820_3.read(temp3);
        result = ds1820_4.read(temp4);
        
        error1 = sensor1.readData();                  //read error value
        error2 = sensor2.readData();                  //read error value
            
        c_int   = sensor1.ReadTemperature(CELCIUS);
        h_int   = sensor1.ReadHumidity();
       
        c_ext   = sensor2.ReadTemperature(CELCIUS);
        h_ext   = sensor2.ReadHumidity();
        
        pc.printf("test 2\r\n\n");
        
        pc.printf("DHT1_temp = %4.2f\r\n", c_int);  // on affiche les valeurs sur teraTerm pour debug
        pc.printf("DHT1_h = %4.2f\r\n", h_int);
        pc.printf("DHT2_temp = %4.2f\r\n", c_ext);
        pc.printf("DHT2_h = %4.2f\r\n", h_ext);
        pc.printf("ds1 = %4.2f\r\n", temp1);
        pc.printf("ds2 = %4.2f\r\n", temp2);
        pc.printf("ds3 = %4.2f\r\n", temp3);
        pc.printf("ds4 = %4.2f\r\n", temp4);
        pc.printf("batterie = %d\r\n", batterie_level);
        
        device.printf("AT$SF=%02X%02X%02X%02X%02X%02X%02X%02X%04X\r\n",(char) c_ext,(char) h_ext, (char) c_int, (char) h_int,(char) temp1,(char) temp2,(char) temp3,(char) temp4, balance);
        pc.printf("AT$SF=%02X%02X%02X%02X%02X%02X%02X%02X%04X%02X\r\n",(char) c_ext,(char) h_ext, (char) c_int, (char) h_int,(char) temp1,(char) temp2,(char) temp3,(char) temp4, balance, (char) batterie_level);

        ThisThread::sleep_for(600000);
    }
}
