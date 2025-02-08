#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial BT(10, 11);

#define LEFT_MOTOR_FORWARD 2
#define LEFT_MOTOR_BACKWARD 3
#define RIGHT_MOTOR_FORWARD 4
#define RIGHT_MOTOR_BACKWARD 5

Servo stairServo;
#define SERVO_PIN 6

#define TRIG_PIN 7
#define ECHO_PIN 8

void setup() {
    Serial.begin(9600);
    BT.begin(9600);
    pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
    pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);
    pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
    pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    stairServo.attach(SERVO_PIN);
}

void loop() {
    if (BT.available()) {
        char command = BT.read();
        executeCommand(command);
    }
}

void executeCommand(char command) {
    switch (command) {
        case 'F': moveForward(); break;
        case 'B': moveBackward(); break;
        case 'L': turnLeft(); break;
        case 'R': turnRight(); break;
        case 'S': stopMotors(); break;
        case 'U': climbStairs(); break;
    }
}

void moveForward() {
    digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
    digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
    digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
    digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
}

void moveBackward() {
    digitalWrite(LEFT_MOTOR_BACKWARD, HIGH);
    digitalWrite(RIGHT_MOTOR_BACKWARD, HIGH);
    digitalWrite(LEFT_MOTOR_FORWARD, LOW);
    digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
}

void turnLeft() {
    digitalWrite(LEFT_MOTOR_FORWARD, LOW);
    digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
}

void turnRight() {
    digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
    digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
}

void stopMotors() {
    digitalWrite(LEFT_MOTOR_FORWARD, LOW);
    digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
    digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
    digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
}

void climbStairs() {
    stairServo.write(90); // Adjust angle for lifting the wheels
    delay(1000);
    moveForward();
    delay(2000);
    stopMotors();
    stairServo.write(0); // Reset servo position
}
