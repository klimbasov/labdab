#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define HIGH_COND 250
#define RECEIVED_BUFFER_LENGTH 21
#define SEND_BUFFER_LENGTH 5
#define resived_massage  "data getted:"
#define sent_massage "data sent:"
#define multiplier 3

char  received_buffer [RECEIVED_BUFFER_LENGTH],
      send_buffer [SEND_BUFFER_LENGTH],
      mask;
int counter=0,
    received_buffer_size,
    redpin = A0,
    greenpin = A1,
    bluepin = A2;
unsigned short int send_value=0;
bool  flag_draw_needed = false;




void error();
void valid();
void overfloW();
void show_data(char*, int);
void draw_received_buffer();
void draw_UI();
void draw_all();
void received_data_funk();
void draw_send_buffer();

void setup() {
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  display.clearDisplay();
  display.setTextSize(1);             
  display.setTextColor(SSD1306_WHITE); 
  display.cp437(true); 
  
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  analogWrite(redpin, 0);
  analogWrite(greenpin, 0);
  analogWrite(bluepin, 0);


  draw_UI();
  display.display();
  Serial.begin(9600);
}


void loop() {
  
received_data_funk();
send_data_function();
draw_all();
delay(100);

}
void received_data_funk(){
  mask = 3;
  if(Serial.available()){
  mask = 0;
  while(Serial.available()){
    if(counter >= RECEIVED_BUFFER_LENGTH){
      mask |= 2;
      break;
    }
    received_buffer[counter]=Serial.read();
    if(received_buffer[counter]==-1){
      mask |= 1;
      break;  
    }
    ++counter;
  }
  received_buffer_size= counter;
  /*while(Serial.available()){
    Serial.read();
  }*/
  }
  if(mask==0){
    received_buffer[counter]='\0';
    flag_draw_needed = true;
    
  }
  validator(mask);
  counter =0;
}

void validator(byte mask){
  if(mask == 1)
  error();
  if(mask == 2)
  overfloW();
  if(mask == 0)
  valid();
  if(mask == 3)
  no_avail();
}

void error(){
  analogWrite(redpin, HIGH_COND);
  delay(1000);
  analogWrite(redpin, 0);
}

void valid(){
  analogWrite(greenpin, HIGH_COND);
  delay(1000);
  analogWrite(greenpin, 0);
}

void overfloW(){
  analogWrite(bluepin, HIGH_COND);
  delay(1000);
  analogWrite(bluepin, 0);
}

void no_avail(){
  analogWrite(redpin, HIGH_COND);
  analogWrite(greenpin, HIGH_COND);
  analogWrite(bluepin, HIGH_COND);
  delay(1000);
  analogWrite(redpin, 0);
  analogWrite(greenpin, 0);
  analogWrite(bluepin, 0);
}


void draw_received_buffer() {
  display.setCursor(0,8); 
  display.println(((const char*)received_buffer));
}
void draw_UI(){
  display.setCursor(0,0);
  display.println(F(resived_massage));
  display.drawLine(0, 16, display.width()-1, 16, SSD1306_WHITE);
  display.setCursor(0,18);
  display.println(F(sent_massage));
}
void draw_all(){
  if(!flag_draw_needed)
    return;
  display.clearDisplay();
  draw_received_buffer();
  draw_UI();
  draw_send_buffer();
  display.display();
  flag_draw_needed = false;
}

void send_data_function(){
    if(!flag_draw_needed)
    return;
    send_value =0;
  while(counter<=received_buffer_size){
    send_value += (unsigned short)received_buffer[counter]&255;
    ++counter;  
  }
  counter=0;
  Serial.write((byte)send_value);
  send_buffer[0]= (byte)send_value;
  Serial.write((byte)(send_value >> 8));
  send_buffer[1]= (byte)send_value >> 8;
}
void draw_send_buffer() {
  display.setCursor(0,26);
  display.println(send_value);
}

/*
 * dto 
 */
 
