//LostGhost-2020.06.03

int latch = 3;  //74HC595  pin 9 STCP
int clock1 = 4; //74HC595  pin 10 SHCP
int data = 2;   //74HC595  pin 8 DS

unsigned char table[]=
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c
,0x39,0x5e,0x79,0x71,0x00};//Display digital data

const int nbrDigits= 4; // the number of digits in the LED display
                             //dig 1 2 3 4
const int digitPins[nbrDigits] = { 5,6,7,8};

//int lightPin = A0; //LDR

void setup() {
  //Configuring output pins for the 74HC595
  pinMode(latch,OUTPUT);
  pinMode(clock1,OUTPUT);
  pinMode(data,OUTPUT);
  //pinMode(lightPin,INPUT);

  //Configuring output pins for commun cathod of each 7 segment digit
  for(int i=0; i < nbrDigits; i++)
  {
     pinMode(digitPins[i], OUTPUT);
     digitalWrite(digitPins[i],HIGH);
  }
}
int k=0000;
void loop() {
  //int digitalReading  = analogRead(lightPin);
  DisplayNumber(k);
  if(k==9999) k=0000;
  k+=1111;
  delay(1000);
  
}

//Function to display a nmuber on 4 digit 7 segments (maximum 9999)
void DisplayNumber( int number) {
  if(number == 0)
    DisplayDigit( 0, nbrDigits-1) ; // display 0 in the rightmost digit
  else
  {
    // display the value corresponding to each digit
    // leftmost digit is 0, rightmost is one less than the number of places
    for( int digit = nbrDigits-1; digit >= 0; digit--)
    {
      if(number > 0)
      {
        DisplayDigit( number % 10, digit) ;
        number = number / 10;
      }
    }
  }
}

//Function to display on one seven segments digit
void DisplayDigit(unsigned char num, int digit) {
  digitalWrite(latch,LOW);
  shiftOut(data,clock1,MSBFIRST,~(table[num]));
  digitalWrite(latch,HIGH);
  
  digitalWrite( digitPins[digit], LOW );
  delay(10);
  digitalWrite( digitPins[digit], HIGH );
}
