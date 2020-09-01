// Open loop motor control example 
 #include <SimpleFOC.h>

// motor instance
BLDCMotor motor = BLDCMotor(3, 10, 6, 11, 7);

void setup() {
  
  // power supply voltage
  // default 12V
  motor.voltage_power_supply = 12;

  // init motor hardware
  motor.init();

  Serial.begin(115200);
  Serial.println("Motor ready!");
  _delay(1000);
}

float target_position = 0; // rad/s
float target_velocity= 10; // rad/s
float target_voltage = 3; // V

void loop() {
  // set angle in open loop
  // - angle - rad
  // - velocity - rad/s
  // - voltage  - V
  motor.angleOpenloop(target_position, target_velocity, target_voltage);

  // a bit of delay
  _delay(1);

  // receive the used commands from serial
  serialReceiveUserCommand();
}

// utility function enabling serial communication with the user to set the target values
// this function can be implemented in serialEvent function as well
void serialReceiveUserCommand() {
  
  // a string to hold incoming data
  static String received_chars;
  
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the string buffer:
    received_chars += inChar;
    // end of user input
    if (inChar == '\n') {
      
      // change the motor target
      target_position = received_chars.toFloat();
      Serial.print("Target position: ");
      Serial.println(target_position);
      
      // reset the command buffer 
      received_chars = "";
    }
  }
}