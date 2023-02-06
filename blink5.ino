int flashingFrequency = 500; //this is the time to delay while playing patterns
int BUTTON = 13; /* Arduino pin for the push button*/
int SHORT_TIME = 400; /* Time that will be considered as the short press time */
int previousState = LOW; /* Setting the initial state of push button HIGH as we are using the INPUT_PULLUP mode */
int presentState;  /* Variable that will store the present state if the button*/
unsigned long press_Time = 0; /* Time at which the button was pressed */
unsigned long release_Time = 0;/*Time at which the button is released */
int patternCount = 0; //store which pattern number we are at
int frequencyCount = 0; //store which frequency we are flasjing at 
bool patternloop = false;

void setup(){  Serial.begin(9600);
   for(int i=3; i<=9; i++){
    pinMode(i,OUTPUT); // set our LEDS from pin 3 to 9 as output
   }
   pinMode(BUTTON, INPUT_PULLUP); //set our button as a input_pullup
}

  
void loop() {
  PushButton();
 }
  
void pat1()
{
  while(patternloop == true && patternCount == 0) 
   {
     axio();  
  for(int i=3; i<=9; i++) 
    {
      axio();
      buttonispressed(); 
      digitalWrite(i,HIGH);
      delay(flashingFrequency);
      digitalWrite(i,LOW);
 
    }
    axio();
    for(int i=9; i>3; i--)
     {
      axio();       
      digitalWrite(i,HIGH);
      delay(flashingFrequency);
      digitalWrite(i,LOW);
    }
   }    
} 


void pat2()
{
  while(patternloop ==true && patternCount == 1) 
   {
  axio();
     for(int i=3; i<=9; i++)
    {
      axio();
      digitalWrite(i,HIGH);
      digitalWrite(i-1,HIGH);
      digitalWrite(i+1,HIGH);
      delay(flashingFrequency);
      digitalWrite(i,LOW);
      digitalWrite(i-1,LOW);
      digitalWrite(i+1,LOW);
    }
    axio();
    
    for(int i=9; i>3; i--) 
    {
      axio();
      digitalWrite(i,HIGH);
      digitalWrite(i-1,HIGH);
      digitalWrite(i+1,HIGH);
      delay(flashingFrequency);
      digitalWrite(i,LOW);
      digitalWrite(i-1,LOW);
      digitalWrite(i+1,LOW);
    }
  }       
}

void pat3()
{
  while(patternloop ==true && patternCount == 2) 
   {
     axio();
  for(int i=3; i<=9; i=i+2) 
  {
axio();       
      digitalWrite(i,HIGH);
      delay(flashingFrequency);
      digitalWrite(i,LOW);
 
  }
  axio();
    
    for(int i=9; i>=3; i=i-2) 
    {
      axio();
      buttonispressed();
      digitalWrite(i,HIGH);
      delay(flashingFrequency);
      digitalWrite(i,LOW);
    }
  }           
}

void pat4()
{
  while(patternloop ==true && patternCount == 3) 
   { 
     axio();
    for(int i=3; i<=9; i++)
    {
      axio();
      digitalWrite(i,HIGH);
      delay(flashingFrequency);
    }
    axio();
    for(int i=9; i>=2; i--) 
    {
      axio();
      digitalWrite(i,HIGH);
      delay(flashingFrequency);
      digitalWrite(i,LOW);
    }
  }    
}

void pat5()
{
  while(patternloop ==true && patternCount == 4) 
   {
   axio();
    for(int i=3; i<=9; i++) 
    {
      axio();
      digitalWrite(i,HIGH);
    }
    delay(flashingFrequency);
    axio();
    for(int i=3; i<=9; i++) 
    {
      axio();
      digitalWrite(i,LOW);
    }
    axio();
    delay(flashingFrequency);  
    }
}

void setLedsOff(){
  for (int i = 3; i < 9; i++) 
  {
    digitalWrite(i, LOW);
  }
}    

void setLedOn(){
  for (int i = 3; i < 9; i++) 
  {
    digitalWrite(i, HIGH);
  }
} 


void button(int presentState)
{

//presentState = digitalRead(BUTTON);  
   /* Getting the present state of the push button */


  if(previousState == HIGH && presentState == LOW) /* If button is pressed */
    press_Time = millis();/* Save the time in milliseconds using the Millis function */
 
  else if(previousState == LOW && presentState == HIGH) { /*  If button is released*/
    release_Time = millis();/* save the time at which the button was released */

    long ON_TIME = release_Time - press_Time;/* calculating the time for which the button remained in the LOW state*/
   
    if( ON_TIME > SHORT_TIME ){ /* comparing the value of time for which the button is pressed to the value for short press time*/
      Serial.println("Long Press");
      LongP();      
     }
      
    else
    {
      Serial.println("Short Press");
      ShortP();
      //here button was short pressed 
    } 

} 
previousState = presentState;/* saving the present value in the previous value */
delay(10);
}

void ShortP()
{

   if(flashingFrequency >= 100){
        // reduce flashing frequency to make leds light up faster
        flashingFrequency = flashingFrequency - 100;
      }else{
        // if the frequency is at 10 milliseconds
        // set flashing frequency to original value of 50
        flashingFrequency = 500;
      }

  switch(patternCount)
      {
        case 0:
          pat1();
          patternloop = true;
          break;
        case 1:
          pat2();
          patternloop = true;
          break;
        case 2:
          pat3();
          patternloop = true;
          break;
        case 3:
          pat4();
          patternloop = true;
          break;
        case 4:
          pat5();
          patternloop = true;
          break;
      }
  
} 

void LongP()
{
      switch(patternCount)
      {
        case 0:
          pat1();
          patternloop = true;
          break;
        case 1:
          pat2();
          patternloop = true;
          break;
        case 2:
          pat3();
          patternloop = true;
          break;
        case 3:
          pat4();
          patternloop = true;
          break;
        case 4:
          pat5();
          patternloop = true;
          break;
      }

      
      if(patternCount == 4)
      {
        //set pattern back to the first one
        patternCount = 0; 

      }else
      {
        //increase our patternCount so next time we play a different pattern
        patternCount++; 
      }

} 

bool buttonispressed()
{
   return digitalRead(BUTTON);   
}

void axio()
{
  presentState = digitalRead(BUTTON);
if (presentState == LOW)
{
  patternloop = false;
  button(presentState);
}else
{
patternloop = true;  
}
}

void PushButton()
{
  presentState = digitalRead(BUTTON);
  button(presentState);
}
        

  
 