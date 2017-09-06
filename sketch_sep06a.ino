/*
SparkFun Inventor's Kit for Arduino
Example sketch 12

SparkFun Motor Driver

Use the SparkFun Motor Driver to control the speed and direction of a motor

This sketch was written by SparkFun Electronics,
with lots of help from the Arduino community.
This code is completely free for any use.
Visit http://learn.sparkfun.com/products/2 for SIK information.
Visit http://www.arduino.cc to learn more about Arduino.
*/

//define the two direction logic pins and the speed / PWM pin
const int DIR_A = 5;
const int DIR_B = 4;
const int PWM = 6;

int state = 0;
int current_speed = 255;
int last_pos = 0;

// include the library code:
//#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup()
{
//set all pins as output
Serial.begin(9600);
pinMode(DIR_A, OUTPUT);
pinMode(DIR_B, OUTPUT);
pinMode(PWM, OUTPUT);
//lcd.begin(16, 2);
Serial1.begin(9600);           // start serial for output

}

char buf[16] = "Speed is     ";

void set_speed(int sp)
{
  if (sp < 0 || sp > 255)
  {
    Serial.println("impossible speed!");
    return;
  }
  current_speed = sp;
  if (sp > 0){
    state = 1;
    move_forward();
  }
  else
    stop_moving();
  
}

void move_forward()
{
  //drive forward at full speed by pulling DIR_A High
 //and DIR_B low, while writing a full 255 to PWM to 
 //control speed
 digitalWrite(DIR_A, HIGH);
 digitalWrite(DIR_B, LOW);
 analogWrite(PWM, current_speed);
 

 //wait 1 second
 //delay(1000);
}

void stop_moving()
{
 //Brake the motor by pulling both direction pins to 
 //the same state (in this case LOW). PWM doesn't matter
 //in a brake situation, but set as 0.
 digitalWrite(DIR_A, LOW);
 digitalWrite(DIR_B, LOW);
 analogWrite(PWM, 0);
 current_speed = 0;
  
 //wait 1 second
 delay(1000);
}


void loop()
{
  //lcd.write("Hello");
  // when characters arrive over the serial port...
  if (Serial.available()) {
    // wait a bit for the entire message to arrive
    delay(100);
    // clear the screen
    // lcd.clear();
    // read all the available characters
    while (Serial.available() > 0) {
      // display each character to the LCD
      char byte = Serial.read();
      Serial.write(byte);
      if (byte == 'e'){
        state = 1;
        current_speed = 255;
      }
      if (byte == 's'){
        state = 0;
        current_speed = 0;
      }
      if (byte == 'c')
      {
        int sp = Serial.parseInt();
        set_speed(sp);
      }
      itoa(current_speed, buf + 9, 10);
      //Serial1.println(buf.size());
      Serial1.println(buf);
      if (state == 1)
        move_forward();
      else
        stop_moving();
    }
  }
}









