// demo: CAN-BUS Shield, send data
#include <mcp_can.h>
#include <SPI.h>


#include <IRremote.h>


// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 10;

MCP_CAN CAN(SPI_CS_PIN); // Set CS pin


// remote start
const int irReceiverPin = 8;
IRrecv irrecv(irReceiverPin);
decode_results results;
// remote end
unsigned long odo1 = 0;
unsigned long speed1 = 0;
unsigned long rpm1 = 0;


void setup()
{
Serial.begin(9600);

while (CAN_OK != CAN.begin(CAN_500KBPS))
{
Serial.println("CAN BUS Shield init fail");
Serial.println(" Init CAN BUS Shield again");
delay(100);
}
Serial.println("CAN BUS Shield init ok!");
}



void loop()
{
  char data;  //Recived data will get stored in this variable
  if(Serial.available()) //Here We're checking whether data is available or not
  {
    data=Serial.read(); //Data received

//power=1; //Power 0-off 1-on
//lights=1; //Lights 0-off/1-on
//doors=0;//Doors Driver=1;Passenger=2;Rear Driver=4; Rear Pass=8; Trunk=32; Example: All doors open= 1+2+4+8=15 All doors open + trunk = 1+2+4+8+32=47
//washer=0; //Washer 0-off 4-on
//reverse=0; //Reverse 0-off 2-on
//brake=0; //Hand Brake 0-off 2-on
//belt=249; //Seat Belt 249-off 233-on
//
//odo1=453;
//speed1=(321.3*200);
//rpm1=(7850*4); 
//
//odoL = (odo1&0xFF);
//odoM = ((odo1 >> 8)&0xFF);
//odoH = ((odo1 >> 16)&0xFF);
//
//speedL = (speed1&0xFF);
//speedH = ((speed1 >> 8)&0xFF);
//
//rpmL = (rpm1&0xFF);
//rpmH = ((rpm1 >> 8)&0xFF);
//
//temp = ((28+50)*2);
//volt = ((14*10)-50)*2;
//fuel = 50;//if fuel <10 liters+128 for low fuel warning light.
////if fuel=>10 liters.

//unsigned char stmp0[8] = {power, 0, 0, 0, 0, 0, 0, 0}; 
//unsigned char stmp1[8] = {lights, 0, 0, 0, 0, 0, 0, 0};
//unsigned char stmp2[8] = {0, doors, 0, 0, 0, 0, 0, 0}; 
//unsigned char stmp3[8] = {0, rpmL, rpmH, 0, 0, 0, 0, 0}; //RPM
//unsigned char stmp4[8] = {0, speedL, speedH, 0, 0, temp, 0, 0}; //Speed/Outside Temp
//unsigned char stmp5[8] = {washer, 0, 0, fuel, 0, 0, 0, 0}; 
//unsigned char stmp6[8] = {0, odoL, odoM, odoH, 0, 0, 0, 0}; //Odometer
//unsigned char stmp7[8] = {reverse, 0, brake, 0, 0, 0, 0, 0};
//unsigned char stmp8[8] = {volt, 0, 0, 0, 0, 0, 0, 0}; //Battery Voltage
//unsigned char stmp9[8] = {0, belt, 0, 0, 0, 0, 0, 0};
unsigned char stmpup[2] = {6, 0}; // Steering Control
unsigned char stmpdown[2] = {7, 0}; // Steering Control
unsigned char stmpleft[8] = {34, 34, 34, 0, 0, 0, 0, 0}; // Steering Control
unsigned char stmpright[8] = {35, 35, 34, 0, 0, 0, 0, 0}; // Steering Control
unsigned char stmpmute[8] = {43, 43, 0, 0, 0, 0, 0, 0}; // Steering Control


unsigned char stmplock[10] = {85, 85, 85, 85, 85, 0, 0, 0, 0, 0}; // door lock
unsigned char stmpunlock[10] = {170, 170, 170, 170, 170, 0, 0, 0, 0, 0}; // door unlock

unsigned char stmp13[8] = {8, 8, 8, 8, 0, 0, 0, 0}; // door lock
unsigned char stmp14[8] = {2, 2, 2, 2, 0, 0, 0, 0}; // door unlock

unsigned char stmp15[8] = {0, 0, 8, 0, 0, 0}; // trunk

//unsigned char stmpwinFRup[8] = {128 ,128, 128, 128, 128,0,0, 0}; // window

unsigned char stmpwinFRUp[8] = {32 ,00, 32, 00, 32,00,32,00}; // window
unsigned char stmpwinFRDown[8] = {128 ,00, 128, 00, 128,00,128, 00}; // window

    if(data=='1')
    {
      Serial.println(data);
      CAN.sendMsgBuf(1473, 0, 8, stmpup);
    
      data=0;
    }

       if(data=='2')
    {
      CAN.sendMsgBuf(1473, 0, 8, stmpdown);
    
      data=0;
      
    }
          if(data=='3')
    {
      CAN.sendMsgBuf(1473, 0, 2, stmpright);
     
      data=0;
    }


           if(data=='4')
    {
      CAN.sendMsgBuf(1473, 0, 2, stmpleft);
   
      data=0;
    }

            if(data=='5')
    {
     CAN.sendMsgBuf(1473, 0, 8, stmpmute);
      delay(500);
      data=0;
    }

  
        if(data=='6')
    {
      CAN.sendMsgBuf(657, 0, 8, stmplock);
       data=0;
    }

            if(data=='7')
    {
      CAN.sendMsgBuf(657, 0, 8, stmpunlock);
       data=0;
    }


              if(data=='8')
    {
      CAN.sendMsgBuf(385, 0, 8, stmpwinFRDown);
       data=0;
    }

                  if(data=='7')
    {
      CAN.sendMsgBuf(385, 0, 8, stmpwinFRUp);
    data=0;
    }





    
//// send data: id = 0x00, standrad frame, data len = 8, stmp: data buf
//CAN.sendMsgBuf(707, 0, 8, stmp0);
////delay(10); // send data per 10ms
//CAN.sendMsgBuf(1589, 0, 8, stmp1);
////delay(10); // send data per 10ms
//CAN.sendMsgBuf(1136, 0, 8, stmp2);
//delay(1); // send data per 10ms
//CAN.sendMsgBuf(859, 0, 8, stmp3);
////delay(10); // send data per 10ms
//CAN.sendMsgBuf(1319, 0, 8, stmp4);
////delay(10); // send data per 10ms
//CAN.sendMsgBuf(1569, 0, 8, stmp5);
////delay(10); // send data per 10ms
//CAN.sendMsgBuf(1629, 0, 8, stmp6);
////delay(10); // send data per 10ms
//CAN.sendMsgBuf(849, 0, 8, stmp7);
////delay(10); // send data per 10ms
//CAN.sendMsgBuf(1393, 0, 8, stmp8);
////delay(10); // send data per 10ms
//CAN.sendMsgBuf(337, 0, 8, stmp9);
////delay(100); // send data per 10ms
//CAN.sendMsgBuf(657, 0, 8, stmp11);
//delay(10000); // send data per 10ms
//CAN.sendMsgBuf(657, 0, 8, stmp12);
//delay(10000); // send data per 10ms
//CAN.sendMsgBuf(385, 0, 8, stmpup);
//delay(10000);

   // CAN.sendMsgBuf(385, 0, 8, stmpwin);
   

//
//int num =results.value;
//if(num == remoteup){
//    CAN.sendMsgBuf(1473, 0, 8, stmpup);
//    delay(500);
//  
//}
//if(num == remotedown){
//  CAN.sendMsgBuf(1473, 0, 8, stmpdown);
//  delay(500);
//}
//if(num == remoteleft){
//  CAN.sendMsgBuf(1473, 0, 8, stmpleft);
//  delay(500);
//}
//if(num == remoteright){
//  CAN.sendMsgBuf(1473, 0, 8, stmpright);
//  delay(500);
//}
//if(num == remoteok){
//  CAN.sendMsgBuf(1473, 0, 8, stmpok);
//  delay(500);
//}
//if(num == remotestar){
//  CAN.sendMsgBuf(657, 0, 8, stmpstar);
//  delay(500);
//}
//if(num == remotehash){
//  CAN.sendMsgBuf(657, 0, 8, stmphash);
//  delay(500);
//}
//irrecv.resume();
// 
delay(500);
}

}
