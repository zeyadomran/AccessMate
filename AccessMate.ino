#include<LiquidCrystal.h>

#define JOYSTICK_VRX  A1
#define JOYSTICK_VRY  A0 
const int BUTTON_PIN = 2;
int buttonState = 0;

const int US_TRIG_PIN = 9;
const int US_ECHO_PIN = 8;    

const int LED_PIN = 7;

const int BUZZER_PIN = 5;

const int DISPLAY_1 = 4;
const int DISPLAY_2 = 6;
const int DISPLAY_3 = 10;
const int DISPLAY_4 = 11;
const int DISPLAY_5 = 12;
const int DISPLAY_6 = 13;
const int DISPLAY_CONTRAST = 3;


LiquidCrystal lcd(DISPLAY_1, DISPLAY_2, DISPLAY_3, DISPLAY_4, DISPLAY_5, DISPLAY_6);
int DISPLAY_CONTRAST_VALUE = 30;

String mode = "message";
String input;

int sleep = 0;

void printMessage(String message) {
  lcd.clear();
  if(message.length() >= 17) lcd.print(message.substring(0, 16) + " " + message.substring(17, message.length()));
  else lcd.print(message);
  Serial.println(message);
}

const blink(int duration) {
  digitalWrite(LED_PIN, HIGH);
  delay(duration);
  digitalWrite(LED_PIN, LOW);
}

void setup() {
  Serial.begin(9600) ;
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(US_TRIG_PIN, OUTPUT);
  pinMode(US_ECHO_PIN, INPUT);
  lcd.begin(16 , 2);
  lcd.clear();
  analogWrite(3, DISPLAY_CONTRAST_VALUE);
  printMessage("AccessMate       - Zeyad, Amr, Mohammed");
  delay(500);
  printMessage("Mode: " + mode);
}

void joystickInput() {
  int y_raw = analogRead(JOYSTICK_VRY);
  int x_raw = analogRead(JOYSTICK_VRX);
  int y = (y_raw - 512) / 2;
  int x = (x_raw - 512) / 2; 
  if (x < -200 && mode == "settings") {
    if(DISPLAY_CONTRAST_VALUE - 5 < 0) return;
    DISPLAY_CONTRAST_VALUE = DISPLAY_CONTRAST_VALUE - 5;
    analogWrite(3, DISPLAY_CONTRAST_VALUE);
    delay(100);
  } else if (x > 200 && mode == "settings") {
    if(DISPLAY_CONTRAST_VALUE + 5 > 100) return;
    DISPLAY_CONTRAST_VALUE = DISPLAY_CONTRAST_VALUE + 5;
    analogWrite(3, DISPLAY_CONTRAST_VALUE);
    delay(100);
  }
   if (y < -200) {
    if (mode == "sensor") {
      mode = "message";
    } else if (mode == "message") {
      mode = "settings";
    } else {
      mode = "sensor";
    } 
    printMessage("Mode: " + mode);
    delay(100);
  } else if (y > 200) {
    if (mode == "settings") {
      mode = "message";
    } else if (mode == "message") {
      mode = "sensor";
    } else {
      mode = "settings";
    }
    printMessage("Mode: " + mode);
    delay(100);
  }
}

void buttonInput() {
  buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == LOW) {
    if (sleep == 0) {
      sleep = 1;
      lcd.noDisplay();
    } else {
      sleep = 0;
      lcd.display();
    }
    delay(100);
  }
}
void dash() {
  digitalWrite(BUZZER_PIN, HIGH);
  tone(BUZZER_PIN, 523.251, 200);
  digitalWrite(BUZZER_PIN, LOW);
  delay(300);           
  blink(300);
}

void dot() {
  digitalWrite(BUZZER_PIN, HIGH);
  tone(BUZZER_PIN, 523.251, 66.6);
  digitalWrite(BUZZER_PIN, LOW); 
  delay(200);   
  blink(200);
         
}

void letterspace() {
  delay(100);
  blink(100);
}

void wordspace() {
  delay(600);
  blink(600);
}

void charToMorse(char c) {
  switch (c) {       //turns the variable i into whatever the input code was, only works with int, and char data types
    case 'A':          // if the input is the character A, perform the following:
      dot();         //from the fuctions declared earlier
      dash();
      letterspace(); //small pause between letters
      break;             //this function is to indicate the end of the case
    case 'B':          // if the input is the character B, perform the following:
      dash();          //from the fuctions declared earlier
      dot();
      dot();
      dot();
      letterspace();   //small pause between letters
      break;
    case 'C':          //and so on...
      dash();
      dot();
      dash();
      dot();
      letterspace();
      break;
    case 'D':
      dash();
      dot();
      dot();
      letterspace();
      break;
    case 'E':
      dot();
      letterspace();
      break;
    case 'F':
      dot();
      dot();
      dash();
      dot();
      letterspace();
      break;
    case 'G':
      dash();
      dash();
      dot();
      letterspace();
      break;
    case 'H':
      dot();
      dot();
      dot();
      dot();
      letterspace();
      break;
    case 'I':
      dot();
      dot();
      letterspace();
      break;
    case 'J':
      dot();
      dash();
      dash();
      dash();
      letterspace();
      break;
    case 'K':
      dash();
      dot();
      dash();
      letterspace();
      break;
    case 'L':
      dot();
      dash();
      dot();
      dot();
      letterspace();
      break;
    case 'M':
      dash();
      dash();
      letterspace();
      break;
    case 'N':
      dash();
      dot();
      letterspace();
    case 'O':
      dash();
      dash();
      dash();
      letterspace();
      break;
    case 'P':
      dot();
      dash();
      dash();
      dot();
      letterspace();
      break;
    case 'Q':
      dash();
      dash();
      dot();
      dash();
      letterspace();
      break;
    case 'R':
      dot();
      dash();
      dot();
      letterspace();
      break;
    case 'S':
      dot();
      dot();
      dot();
      letterspace();
      break;
    case 'T':
      dash();
      letterspace();
      break;
    case 'U':
      dot();
      dot();
      dash();
      letterspace();
      break;
    case 'V':
      dot();
      dot();
      dot();
      dash();
      letterspace();
      break;
    case 'W':
      dot();
      dash();
      dash();
      letterspace();
      break;
    case 'X':
      dash();
      dot();
      dot();
      dash();
      letterspace();
      break;
    case 'Y':
      dash();
      dot();
      dash();
      dash();
      letterspace();
    case 'Z':
      dash();
      dash();
      dot();
      dot();
      letterspace();
      break;
    case '1': //After letters there are numbers, same concept
      dot();
      dash();
      dash();
      dash();
      dash();
      letterspace();
      break;
    case '2':
      dot();
      dot();
      dash();
      dash();
      dash();
      letterspace();
      break;
    case '3':
      dot();
      dot();
      dot();
      dash();
      dash();
      letterspace();
      break;
    case '4':
      dot();
      dot();
      dot();
      dot();
      dash();
      letterspace();
      break;
    case '5':
      dot();
      dot();
      dot();
      dot();
      dot();
      letterspace();
      break;
    case '6':
      dash();
      dot();
      dot();
      dot();
      dot();
      letterspace();
      break;
    case '7':
      dash();
      dash();
      dot();
      dot();
      dot();
      letterspace();
      break;
    case '8':
      dash();
      dash();
      dash();
      dot();
      dot();
      letterspace();
      break;
    case '9':
      dash();
      dash();
      dash();
      dash();
      dot();
      letterspace();
      break;
    case '0':
      dash();
      dash();
      dash();
      dash();
      dash();
      letterspace();
      break;
    case '_': //then there's a function for a space, same concept
      wordspace();
  }
}

void ultrasonicInput() {
  digitalWrite(US_TRIG_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(US_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(US_TRIG_PIN, LOW);

  long duration = pulseIn(US_ECHO_PIN, HIGH);
  long distance = duration * 0.034 / 2;
   if (distance > 100) {
    tone(BUZZER_PIN, 520, 500);
  } else if (distance < 100 && distance > 50) {
    tone(BUZZER_PIN, 1000, 500);
    blink(distance);
  } else if(distance < 25) {
    tone(BUZZER_PIN, 1500, 1000);
    blink(10);
  } else {
    tone(BUZZER_PIN, 1500, 500);
    blink(distance);
  }
  printMessage("Distance: " + String(distance) + "cm");
  delay(500);
 
}


void loop() {
  joystickInput();
  buttonInput();
  if (mode == "sensor" && sleep == 0) {
    ultrasonicInput();
  } else if (mode == "message" && sleep == 0) {
    while(Serial.available()) {
      input = Serial.readString();
      char inputCharArr[input.length()];
      input.toCharArray(inputCharArr, input.length());
      inputCharArr[input.length()-1] = '\0';
      printMessage(inputCharArr);
      for(int i = 0; i < strlen(inputCharArr); i++) {
        charToMorse(inputCharArr[i] & ~(0x20));
        Serial.println(inputCharArr[i] & ~(0x20));
      }
    }
  } else if (mode == "settings" && sleep == 0) {
    printMessage("Contrast: " + String(DISPLAY_CONTRAST_VALUE));
  }
}
