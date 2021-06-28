int trig_front = 2;
int echo_front = 3;
int trig_back = 12;
int echo_back = 11;
int trig_left = 7;
int echo_left = 6;
int trig_right = 8;
int echo_right = 9;

int LF = A1;
int LB = A0;
int RF = A3;
int RB = A2;

float time;
float dist;
int dist_front;
int dist_back;
int dist_left;
int dist_right;
float dist_min = 20.00;
String data_received = "";
String data_str = "";
char command = 's';

int interval;

void setup()
{
  Serial.begin(9600);
  pinMode(trig_front, OUTPUT);
  pinMode(echo_front, INPUT);
  pinMode(trig_back, OUTPUT);
  pinMode(echo_back, INPUT);
  pinMode(trig_left, OUTPUT);
  pinMode(echo_left, INPUT);
  pinMode(trig_right, OUTPUT);
  pinMode(echo_right, INPUT);
  pinMode(LF, OUTPUT);
  pinMode(LB, OUTPUT);
  pinMode(RF, OUTPUT);
  pinMode(RB, OUTPUT);
}

void loop()
{
  dist_front = dist_calc(trig_front, echo_front);
  dist_back = dist_calc(trig_back, echo_back);
  dist_left = dist_calc(trig_left, echo_left);
  dist_right = dist_calc(trig_right, echo_right);
  
  send_data();
  delay(2);
  receive_data();
  //Serial.println(command);
  algorithm();
}

void send_data()
{
  Serial.print(dist_front);
  Serial.print(",");
  Serial.print(dist_back);
  Serial.print(",");
  Serial.print(dist_left);
  Serial.print(",");
  Serial.println(dist_right);
}

void receive_data()
{
  if (Serial.available() > 0)
  {
    data_received = Serial.readStringUntil('\n');
    command = data_received.charAt(data_received.length()-1);
  }
}

int dist_calc(int trig, int echo)
{
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  time = pulseIn(echo,HIGH);
  dist = (0.034*time)/2.0;
  return (int)dist;
}

void move_front()
{
  digitalWrite(LF, HIGH);
  digitalWrite(LB, LOW);
  digitalWrite(RF, HIGH);
  digitalWrite(RB, LOW);
}

void move_back()
{
  digitalWrite(LF, LOW);
  digitalWrite(LB, HIGH);
  digitalWrite(RF, LOW);
  digitalWrite(RB, HIGH);
}

void move_left()
{
  digitalWrite(LF, LOW);
  digitalWrite(LB, HIGH);
  digitalWrite(RF, HIGH);
  digitalWrite(RB, LOW);
}

void move_right()
{
  digitalWrite(LF, HIGH);
  digitalWrite(LB, LOW);
  digitalWrite(RF, LOW);
  digitalWrite(RB, HIGH);
}

void stop()
{
  digitalWrite(LF, LOW);
  digitalWrite(LB, LOW);
  digitalWrite(RF, LOW);
  digitalWrite(RB, LOW);
}

void algorithm()
{
  interval = 2;
  
  if(command == 'f')
  {
    move_front();
    delay(interval);
  }
  
  else if(command == 'b')
  {
    move_back();
    delay(interval);
  }
  
  else if(command == 'l')
  {
    move_left();
    delay(interval);
  }
  
  else if(command == 'r')
  {
    move_right();
    delay(interval);
  }
  
  else
  {
    stop();
    delay(interval);
  }
}

