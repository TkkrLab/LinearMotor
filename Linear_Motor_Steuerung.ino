#include <PID_v1.h>

#define ENC_A 2
#define ENC_B 3

volatile int encoder0Pos = 0;

const int EN1 = 5;
const int EN2 = 6;
const int EN3 = 7;
 
const int IN1 = 9;
const int IN2 = 10;
const int IN3 = 11;

double Setpoint, Input, Output;
PID myPID(&Input, &Output, &Setpoint,2,5,1, DIRECT);

// SPWM (Sine Wave)
//const int pwmSin[72] = {127, 138, 149, 160, 170, 181, 191, 200, 209, 217, 224, 231, 237, 242, 246, 250, 252, 254, 254, 254, 252, 250, 246, 242, 237, 231, 224, 217, 209, 200, 191, 181, 170, 160, 149, 138, 127, 116, 105, 94, 84, 73, 64, 54, 45, 37, 30, 23, 17, 12, 8, 4, 2, 0, 0, 0, 2, 4, 8, 12, 17, 23, 30, 37, 45, 54, 64, 73, 84, 94, 105, 116 };

// SVPWM (Space Vector Wave)
const int pwmSin[] = {128, 132, 136, 140, 143, 147, 151, 155, 159, 162, 166, 170, 174, 178, 181, 185, 189, 192, 196, 200, 203, 207, 211, 214, 218, 221, 225, 228, 232, 235, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 248, 249, 250, 250, 251, 252, 252, 253, 253, 253, 254, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 254, 254, 254, 253, 253, 253, 252, 252, 251, 250, 250, 249, 248, 248, 247, 246, 245, 244, 243, 242, 241, 240, 239, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 248, 249, 250, 250, 251, 252, 252, 253, 253, 253, 254, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 254, 254, 254, 253, 253, 253, 252, 252, 251, 250, 250, 249, 248, 248, 247, 246, 245, 244, 243, 242, 241, 240, 239, 238, 235, 232, 228, 225, 221, 218, 214, 211, 207, 203, 200, 196, 192, 189, 185, 181, 178, 174, 170, 166, 162, 159, 155, 151, 147, 143, 140, 136, 132, 128, 124, 120, 116, 113, 109, 105, 101, 97, 94, 90, 86, 82, 78, 75, 71, 67, 64, 60, 56, 53, 49, 45, 42, 38, 35, 31, 28, 24, 21, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 8, 7, 6, 6, 5, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5, 6, 6, 7, 8, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 8, 7, 6, 6, 5, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5, 6, 6, 7, 8, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 21, 24, 28, 31, 35, 38, 42, 45, 49, 53, 56, 60, 64, 67, 71, 75, 78, 82, 86, 90, 94, 97, 101, 105, 109, 113, 116, 120, 124};


enum phase {PHASE1, PHASE2, PHASE3};
int phasePwmIndex[3];

/*
int *pos_U = pwmSin;
int *pos_V = pwmSin + 24;
int *pos_W = pwmSin + 48;
*/
int *pos_U, *pos_V, *pos_W;



int directionPin = 4;
int stepPin = 12;

int test;
int commutationPWMOffset = 24;

//This distance is the difference between two magnets with the same polarity.
const double phaseDistance = 27;

double position_in_mm = (encoder0Pos) / 40.00;


 
void setup() 
{
  commutationPWMOffset = sizeof(pwmSin)/sizeof(int);

  phasePwmIndex[0] = 0;
  phasePwmIndex[1] = commutationPWMOffset;
  phasePwmIndex[2] = (2*commutationPWMOffset);
  
  *pos_U = pwmSin + phasePwmIndex[0];
  *pos_V = pwmSin + phasePwmIndex[1];
  *pos_W = pwmSin + phasePwmIndex[2];

  pinMode(ENC_A, INPUT);
  pinMode(ENC_B, INPUT);

  attachInterrupt(0, isrA, CHANGE);
  attachInterrupt(1, isrB, CHANGE);

  //Increase PWM frequency to 32 kHz  (make inaudible)
  setPwmFrequency(IN1); 
  setPwmFrequency(IN2);
  setPwmFrequency(IN3);

  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(EN1, OUTPUT); 
  pinMode(EN2, OUTPUT); 
  pinMode(EN3, OUTPUT); 
 
 
  digitalWrite(EN1, HIGH);
  digitalWrite(EN2, HIGH);
  digitalWrite(EN3, HIGH);

  analogWrite(IN1,*pos_U);
  analogWrite(IN2,*pos_V);
  analogWrite(IN3,*pos_W);
  
  //wait for 2 seconds for forcer to settle in position
  delay(2000);

  encoder0Pos = 0;
  
  analogWrite(IN1,0);
  analogWrite(IN2,0);
  analogWrite(IN3,0);

  myPID.SetOutputLimits(-1000, 1000);
  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(1);
  myPID.SetTunings(15,0,0.4);
  Serial.begin(115200);
}

String inString = "";

void loop()
{
  //Read Setpoint from serial communication
  if(Serial.available() > 0)
  {
    int inChar = Serial.read();
    if (isDigit(inChar))
    {
      inString += (char)inChar;
    }
    if (inChar == '\n')
    {
      Setpoint = inString.toInt();
      Serial.print("SetPoint");
      Serial.println(Setpoint);
      inString = "";
    }
  }
  Input = encoder0Pos / 40.00;
  myPID.Compute();
  drive(Output/1000);
}

void drive(double scale_factor)
{
  if(scale_factor < 0.00)
  {
    double  temp = -scale_factor;
    //linear scale Y = x * (ymax - ymin)/(xmax - xmin) + offset
    temp = (temp - 0.00) * (1.0 - 0.1) / (1.00 - 0.00) + 0.1;
    
    test = -(phasePwmIndex[0] - berechne() + commutationPWMOffset);
    shift(&pos_U, test, 72, PHASE1);
    shift(&pos_V, test, 72, PHASE2);
    shift(&pos_W, test, 72, PHASE3);
  
    analogWrite(IN1,*pos_U * temp);
    analogWrite(IN2,*pos_V * temp);
    analogWrite(IN3,*pos_W * temp);
  }
  else if(scale_factor > 0.00)
  {
    test = (phasePwmIndex[0] + berechne() + commutationPWMOffset);
    scale_factor = (scale_factor - 0.00) * (1.0 - 0.1) / (1.00 - 0.00) + 0.1;
    shift(&pos_U, test, 72, PHASE1);
    shift(&pos_V, test, 72, PHASE2);
    shift(&pos_W, test, 72, PHASE3);
    
    analogWrite(IN1,*pos_U * scale_factor);
    analogWrite(IN2,*pos_V * scale_factor);
    analogWrite(IN3,*pos_W * scale_factor);
  }
}

int berechne()
{
  double position_in_mm = encoder0Pos / 40.00;
  int multiple = position_in_mm / phaseDistance;
  double phaseshift_mm = position_in_mm - (multiple * phaseDistance);
  return ((phaseshift_mm - 0) * (72 - 0) / (phaseDistance - 0) + 0);
}

//######################## Shift-Array########################
void shift(int **pwm_sin, int shift_distance, int array_size, phase phase_number)
{
  if(shift_distance != array_size)
  {
    if(shift_distance > 0)
    {
      if(phasePwmIndex[phase_number] + shift_distance < array_size)
      {
        *pwm_sin = *pwm_sin + shift_distance;
         phasePwmIndex[phase_number] += shift_distance;
      }
      else
      {
        int temp =phasePwmIndex[phase_number] + shift_distance - array_size;
        *pwm_sin = *pwm_sin - phasePwmIndex[phase_number];
        *pwm_sin = *pwm_sin + temp;
        phasePwmIndex[phase_number] = temp;
      }
    }
    else if(shift_distance < 0)
    {
      int temp_distance = array_size + shift_distance;
      shift(pwm_sin, temp_distance , array_size, phase_number);
    }
  }
}


//########################### ENCODER-INTERRUPT#########################################
void isrA()
{
  if (bitRead(PIND, ENC_B) != bitRead(PIND, ENC_A))
  {
    encoder0Pos++;
  }
  else
  {
    encoder0Pos--;
  }
}

void isrB()
{
  if (bitRead(PIND, ENC_A) == bitRead(PIND, ENC_B))
  {
    encoder0Pos++;
  }
  else
  {
    encoder0Pos--;
  }
}

//#################### PWM-Motor#######################
void setPwmFrequency(int pin) {
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | 0x01;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | 0x01;
    }
  }
  else if(pin == 3 || pin == 11) {
    TCCR2B = TCCR2B & 0b11111000 | 0x01;
  }
}
