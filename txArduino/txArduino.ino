// Define the sensor pin
const int sensorPin = A0; // Change to the correct pin for your sensor

void setup() {
  // Initialize Serial Communication
  Serial.begin(9600); // Set baud rate to 9600
  pinMode(sensorPin, INPUT); // Set the sensor pin as input
}

void loop() {
  // Read sensor data
  int sensorValue = analogRead(sensorPin); // Use digitalRead() for digital sensors
  
  // Send sensor data to the serial port
  Serial.println(sensorValue); // Sends the data as a line of text
  
  // Add a delay (optional, to avoid flooding the serial port)
  delay(100); // 100ms delay
}
