// front motor (motor on the left when looking at H-Bridge driver with pins towards you) with OUT1 == GND and OUT2 == VLT:
// motorF_IN1 == HIGH and motorF_IN2 == LOW --> clockwise rotation (rolls to the right)
// motorF_IN1 == LOW and motorF_IN2 == HIGH --> counter clockwise rotation (rolls to the left)
int motorF_IN1 = 8;
int motorF_IN2 = 7;
int motorF_ENA = 9;

// back motor (motor on the right when looking at H-Bridge driver with pins towards you) with OUT3 == VLT and OUT4 == GND:
// motorB_IN3 == HIGH and motorB_IN4 == LOW --> clockwise rotation (rolls to the right)
// motorB_IN3 == LOW and motorB_IN4 == HIGH --> counter clockwise rotation (rolls to the left)
int motorB_IN3 = 5;
int motorB_IN4 = 4;
int motorB_ENB = 3;

// lead screw motor (with PIN3 == VLT and PIN7 == GND):
// motor_IN1 == HIGH and motorL_IN2 == LOW --> clockwise rotation (goes up)
// motor_IN2 == LOW and motorL_IN2 == HIGH --> counter clockwise rotation (goes down)
int motorL_EN12 = 11;
int motorL_IN1 = 12;
int motorL_IN2 = 13;

// infrared sensor for front (right) and back motor (back)
// above threshold == detecting edge --> stop, under threshold == detecting desk--> go
int sensorF_IN = 1;
int sensorB_IN = 0;
//infrared sensor for lead screw motor (up and down)
// above threshold == no white/no lead screw block detected --> go, under threshold == white/lead screw detected --> stop
int sensorU_IN = 2;
int sensorD_IN = 3;

int threshold = 500;

// read IR sensor input
int checkF = 0;
int checkB = 0;
int checkU = 0;
int checkD = 0;

String input_data;


void setup() {
  // put your setup code here, to run once:
  pinMode(sensorF_IN, INPUT);   // OUTPUT??
  pinMode(sensorB_IN, INPUT);   // OUTPUT??

  pinMode(sensorU_IN, INPUT);
  pinMode(sensorD_IN, INPUT);

  pinMode(motorF_IN1, OUTPUT);
  pinMode(motorF_IN2, OUTPUT);
  pinMode(motorF_ENA, OUTPUT);
  
  pinMode(motorB_IN3, OUTPUT);
  pinMode(motorB_IN4, OUTPUT);
  pinMode(motorB_ENB, OUTPUT);

  pinMode(motorL_EN12, OUTPUT);
  pinMode(motorL_IN1, OUTPUT);
  pinMode(motorL_IN2, OUTPUT);

  Serial.begin(115200);
  Serial.setTimeout(1);
}

void loop() {

  checkF = analogRead(sensorF_IN); 
  checkB = analogRead(sensorB_IN);
  checkU = analogRead(sensorU_IN); 
  checkD = analogRead(sensorD_IN);
  
  //set motor speed 
  analogWrite(motorF_ENA, 150);  //60
  analogWrite(motorB_ENB, 150);  //40
  analogWrite(motorL_EN12, 255);
  
  while (!Serial.available());
  input_data = Serial.readString();

  if (input_data == "(-1,-1)"){
    // robot needs to move left and up
    move_left();
    move_up();
    Serial.println("MOVE LEFT AND UP");
  }
    
  else if (input_data == "(0,-1)"){
    // robot needs to move up
    dont_move_horizontally();
    move_up();
    Serial.println("MOVE UP");
  }

  else if (input_data == "(1,-1)"){
    // robot needs to move right and up
    move_right();
    move_up();
    Serial.println("MOVE RIGHT AND UP");
  }
  
  else if (input_data == "(-1,0)"){
    // robot needs to move left
    dont_move_vertically();
    move_left();
    Serial.println("MOVE LEFT");
  }
    
  else if (input_data == "(0,0)"){
    // robot needs to stop / does not need to move
    stand_still();
    Serial.println("DON'T MOVE");
  }

  else if (input_data == "(1,0)"){
    // robot needs to move right
    dont_move_vertically();
    move_right();
    Serial.println("MOVE RIGHT");
  }

  else if (input_data == "(-1,1)"){
    // robot needs to move left and down
    move_left();
    move_down();
    Serial.println("MOVE LEFT AND DOWN");
  }

  else if (input_data == "(0,1)"){
    // robot needs to move down
    dont_move_horizontally();
    move_down();
    Serial.println("MOVE DOWN");
  }

  else if (input_data == "(1,1)"){
    // robot needs to move right and down
    move_right();
    move_down();
    Serial.println("MOVE RIGHT AND DOWN");
  }

  else {
    // no need to move as face is centered
    stand_still();
  }
}



////////////// UTILITY FUNCTIONS //////////////////

bool edge_detection() {
//checks if sensorF and/or sensorB detect edge
  if ((checkF > threshold) || (checkB > threshold)){
    return true;
  }
  else {
    return false;
  }
}

bool top_detection(){
//checks if sensorU detects top
  if (checkU < threshold){
    return true;
  }
  else {
    return false;
  }
}

bool bottom_detection(){
//checks if sensorD detects bottom
  if (checkD < threshold){
    return true;
  }
  else {
    return false;
  }
}

void dont_move_horizontally() {
// stops motorF and motorB
  digitalWrite(motorF_IN1, LOW);
  digitalWrite(motorF_IN2, LOW);

  digitalWrite(motorB_IN3, LOW);
  digitalWrite(motorB_IN4, LOW);
}

void dont_move_vertically(){
// stops motorL
  digitalWrite(motorL_IN1, LOW);
  digitalWrite(motorL_IN2, LOW);
}

void stand_still() {
// stops motorF, motorB and motorL
  digitalWrite(motorF_IN1, LOW);
  digitalWrite(motorF_IN2, LOW);

  digitalWrite(motorB_IN3, LOW);
  digitalWrite(motorB_IN4, LOW);

  digitalWrite(motorL_IN1, LOW);
  digitalWrite(motorL_IN2, LOW);
  Serial.println("NO NEED TO MOVE");
}


void move_left() {
  Serial.println(edge_detection());
  if (not edge_detection()){
    digitalWrite(motorF_IN1, LOW);
    digitalWrite(motorF_IN2, HIGH);

    digitalWrite(motorB_IN3, LOW);
    digitalWrite(motorB_IN4, HIGH);
    Serial.println("MOVE LEFT");  
  }
  else {
    dont_move_horizontally();
    Serial.println("CANNOT MOVE LEFT --> DETECTED EDGE");
  }
}

void move_right() {
  if (not edge_detection()){
    Serial.println("IF");
    digitalWrite(motorF_IN1, HIGH);
    digitalWrite(motorF_IN2, LOW);
  
    digitalWrite(motorB_IN3, HIGH);
    digitalWrite(motorB_IN4, LOW);
    Serial.println("MOVE RIGHT");
  }
  else {
    Serial.println("ELSE");
    dont_move_horizontally();
    Serial.println("CANNOT MOVE RIGHT --> DETECTED EDGE");
  }
}

void move_up() {
  if (not top_detection()){
    digitalWrite(motorL_IN1, HIGH);
    digitalWrite(motorL_IN2, LOW);
    Serial.println("MOVE UP");
  }
  else {
    dont_move_vertically();
    Serial.println("CANNOT MOVE UP --> REACHED TOP");
  }
}

void move_down() {
  if (not bottom_detection()) {
    digitalWrite(motorL_IN1, LOW);
    digitalWrite(motorL_IN2, HIGH);
    Serial.println("MOVE DOWN");
  }
  else {
    dont_move_vertically();
    Serial.println("CANNOT MOVE DOWN --> REACHED BOTTOM");
  }
}
