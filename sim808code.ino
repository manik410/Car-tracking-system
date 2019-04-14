String in;
String lon,lat;
int key=0,index[3];
boolean b = false;
void setup() {
  Serial.begin(9600);
  Serial.begin(9600);
  Serial.println("AT+CMGF=1"); //entering into sms reading mode.
  delay(100);
  Serial.println("AT+CNMT=2,2,0,0,0"); //tells sim808 to send any message received to serial.
  delay(100);
}

void loop() 
{
  if(!in.equals(""))
  {
    if(in.indexOf("latlng")>-1)
    {
      Serial.println("AT+SAPBR=3,1,\"APN\",\"www\"");  //turning on data connection.
      delay(1000);
      Serial.println("AT+SAPBR=1,1");
      delay(5000);
      Serial.println("AT+CIPGSMLOC=1,1");  //getting location.
      delay(1000);
      in="";
      b=true;
    }
    else if(in.indexOf(":")>-1 && b)
    {
      Serial.println("AT+CGATT=0");
      delay(1000);
      for(int i=0;i<in.length();i++)  //filtering out the latitude and longitude from the string.
      {
        if(key==3)break;
        if(in.charAt(i)==',')
        {
          index[key]=i;
          key++;
        }
      }
      lon=in.substring(index[0]+1,index[1]);
      lat=in.substring(index[0]+1,index[2]);
      Serial.println(lat);
      Serial.println(lon);
      Serial.println("AT+CMGS=\"9041035777\"");  //entering the no on which location is to be send.
      delay(1000);
      Serial.print("http://maps.google.com/maps?q=loc:" + lat + "," + lon);  //writing the message.
      delay(1000);
      Serial.write(26); //pressing send button.
      delay(5000);
      Serial.println("AT+CMGDA=\"DEL ALL\""); //deleting all previous messages.
      delay(1000);
      lat="";
      lon="";
      in="";
      b = false;
    }
  }
}
void serialEvent1()
{
  while(Serial.available()>0)
  in=Serial.readString();
}
