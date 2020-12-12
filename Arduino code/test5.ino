

#define LED 13
#define BAUDRATE 57600
#define DEBUGOUTPUT 0
#define LED  2
#define LED1  3
#define LED2  4
#define LED3  5
#define LED4 6
#define LED5 7
#define mot1  8
#define mot2  9
#define mot3 10
#define mot4 11
#define buz 12





byte generatedChecksum = 0;
byte checksum = 0; 
int payloadLength = 0;
int raw;
int p1;
int count;
long l1;
long l2;
byte payloadData[64] = {0};
byte poorQuality = 0;
byte attention = 0;
byte meditation = 0;
int comment;
int cp=0;
int sp=0;
long z6;
long z1;
long z2;
long ini;
long initime;
long lastReceivedPacket = 0;
boolean bigPacket = false;
long z3;
long z4;
int stop1=0;
int stop2=0;
long z5;
int count4=0;

void setup() 

{
  pinMode(LED, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
    pinMode(mot1, OUTPUT);
  pinMode(mot2, OUTPUT);
  pinMode(mot3, OUTPUT);
  pinMode(mot4, OUTPUT);
  pinMode(buz, OUTPUT);



  Serial.begin(BAUDRATE); 

}


byte ReadOneByte() 

{
  int ByteRead;
  while(!Serial.available());
  ByteRead = Serial.read();

#if DEBUGOUTPUT  
  Serial.print((char)ByteRead);  
#endif

  return ByteRead;
}


void loop() 

{
  if(ReadOneByte() == 170) 
  {
    if(ReadOneByte() == 170) 
    {
        payloadLength = ReadOneByte();
      
        if(payloadLength > 169)                   
        return;
        generatedChecksum = 0;        
        for(int i = 0; i < payloadLength; i++) 
        {  
        payloadData[i] = ReadOneByte();           
        generatedChecksum += payloadData[i];
        }   

        checksum = ReadOneByte();                       
        generatedChecksum = 255 - generatedChecksum; 
        if(checksum == generatedChecksum) 
        {    
          poorQuality = 200;
          attention = 0;
          meditation = 0;

          for(int i = 0; i < payloadLength; i++) 
          {                                        
          switch (payloadData[i]) 
          {
          case 2:
            i++;            
            poorQuality = payloadData[i];
            bigPacket = true;            
            break;
          case 4:
            i++;
            attention = payloadData[i];                        
            break;
          case 5:
            i++;
            meditation = payloadData[i];
            break;
          case 0x80:
           
           short raw=(payloadData[i+2]<<8)|payloadData[i+3];

            
     
                 
                        z2=millis();
                        l1=z2-z4;
                        
                    
                          if(l1>1500 and l1< 3500){
                            if(cp==3){
                             
                              cp=2;
                            }
                            if(cp==0){
                            Serial.println("fowlwers");
                            digitalWrite(mot1,  HIGH);
                            cp=3;
                            
                            }
                             if(cp==2){
                            Serial.println(" negative fowlwers");
                            digitalWrite(mot2,  HIGH);
                            cp=0;
                           
                            }
                            count=0;
                            comment=0;
                            
                          }
                          if(l1>3800){
                            if(sp==3){
                              sp=2;
                            }
                            if(sp==0){
                            Serial.println("Knewww");
                            digitalWrite(mot3,  HIGH);
                            sp=3;
                            
                            }
                             if(sp==2){
                            Serial.println("negative knewww");
                            digitalWrite(mot4,  HIGH);
                            sp=0;
                           
                            }
                            count=0;
                            comment=0;
                          }
                          }


                        
                               
 
         
  }

                                
                   
                       p1=raw;

         
          //Serial.println(payloadData[i+2], DEC);
          //Serial.println(payloadData[i+3], DEC);

            i = i + 3;
            break;
          case 0x83:
            i = i + 25;      
            break;
          default:
            break;
          } // switch
        } // for loop

#if !DEBUGOUTPUT

        

        if(bigPacket) 
        {
          if(poorQuality == 0)
             digitalWrite(LED, HIGH);
          else
            digitalWrite(LED, LOW);
          
          //Serial.print("PoorQuality: ");
          //Serial.print(poorQuality, DEC);
          Serial.print(" Attention: ");
          Serial.print(attention, DEC);
          Serial.print(" meditation: ");
          Serial.print(meditation, DEC);
          //Serial.print(" Time since last packet: ");
          //Serial.print(millis() - lastReceivedPacket, DEC);
          lastReceivedPacket = millis();
          //Serial.print("\n");

          switch(count) 
          {
          case 0:

            digitalWrite(LED1, LOW);
            digitalWrite(LED2, LOW);
            digitalWrite(LED3, LOW);
            digitalWrite(LED4, LOW);
            digitalWrite(LED5, LOW);
           delay(30);
            break;
          case 1:

            digitalWrite(LED1,  HIGH);
            digitalWrite(LED2, LOW);
            digitalWrite(LED3, LOW);
            digitalWrite(LED4, LOW);
            digitalWrite(LED5, LOW);
  delay(30);
            break;
          case 2:

            digitalWrite(LED1, HIGH);
            digitalWrite(LED2,  HIGH);
            digitalWrite(LED3, LOW);
            digitalWrite(LED4, LOW);
            digitalWrite(LED5, LOW);
      delay(30);
            break;
          case 3:              

            digitalWrite(LED1, HIGH);              
            digitalWrite(LED2, HIGH);
            digitalWrite(LED3,  HIGH);
            digitalWrite(LED4, LOW);
            digitalWrite(LED5, LOW);
           delay(30);
            break;
          case 4:

            digitalWrite(LED1, HIGH);              
            digitalWrite(LED2, HIGH);
            digitalWrite(LED3, HIGH);
            digitalWrite(LED4,  HIGH);
            digitalWrite(LED5, LOW);
                delay(30);  
            break;
          case 5:

            digitalWrite(LED1, HIGH);              
            digitalWrite(LED2, HIGH);
            digitalWrite(LED3, HIGH);
            digitalWrite(LED4, HIGH);
            digitalWrite(LED5,  HIGH);
               delay(30);
            break;
         
          }                     
        }
#endif        
        bigPacket = false;        
      }
      else {
        // Checksum Error
      }  // end if else for checksum
    } // end if read 0xAA byte
  } // end if read 0xAA byte
}
