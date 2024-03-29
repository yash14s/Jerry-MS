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
float dist_front;
float dist_back;
float dist_left;
float dist_right;
float dist_min = 20.00;
String command = "";

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
  Serial.print("Front");
  Serial.print(",");
  Serial.print("Back");
  Serial.print(",");
  Serial.print("Left");
  Serial.print(",");
  Serial.print("Right");
  Serial.print(",");
  Serial.println("Command");
}

void loop()
{
  dist_front = dist_calc(trig_front, echo_front);
  dist_back = dist_calc(trig_back, echo_back);
  dist_left = dist_calc(trig_left, echo_left);
  dist_right = dist_calc(trig_right, echo_right);
  
  algorithm();
  print_csv();
  //print_serial();
  delay(10);
}

float dist_calc(int trig, int echo)
{
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  time = pulseIn(echo,HIGH);
  dist = (0.034*time)/2.0;
  return dist;
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
  if((dist_front > dist_min) && (dist_left > dist_min-5) && (dist_right > dist_min-5))
  {
    move_front();
    command = "front";
  }
  
  else if((dist_left < (dist_min + 5)) && (dist_right < (dist_min + 5)) && (dist_back > dist_min))
  {
    move_back();
    command = "back";
    delay(1000);
    
    if(dist_left > dist_right)
    {
      move_left();
      command = "left";
    }
    else
    {
      move_right();
      command = "right";
    }
    
    delay(500);
  }
  
  else if(dist_left > dist_min)
  {
    move_left();
    command = "left";
  }
  else if(dist_right > dist_min)
  {
    move_right();
    command = "right";
  }

  else if(dist_back > dist_min)
  {
    move_back();
    command = "back";
  }
  
  
  else{
    stop();
    command = "stop";
  }
}

void print_csv()
{
  Serial.print(dist_front);
  Serial.print(",");
  Serial.print(dist_back);
  Serial.print(",");
  Serial.print(dist_left);
  Serial.print(",");
  Serial.print(dist_right);
  Serial.print(",");
  Serial.println(command);
}

void print_serial()
{
  Serial.print("Front: ");
  Serial.println(dist_front);
  Serial.print("Back: ");
  Serial.println(dist_back);
  Serial.print("Left: ");
  Serial.println(dist_left);
  Serial.print("Right: ");
  Serial.println(dist_right);
  Serial.print("Command: ");
  Serial.println(command);               
  Serial.println("***********");
}
