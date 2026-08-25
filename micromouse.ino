
// --- GLOBAL VARIABLES ---

// Sensor values
volatile int leftSensorValue = 0;
volatile int frontSensorValue = 0;
volatile int rightSensorValue = 0;

int leftSensor[10];
int frontSensor[10];
int rightSensor[10];

// Wall thresholds
const int LEFT_GAP = 10;
const int FRONT_WALL = 22; //30
const int RIGHT_GAP = 10;

// Encoder values
volatile long encoderValue = 0;
volatile int encoderDifference = 0; // right - left

// MPU values
volatile float heading = 0.0; // for turns
volatile float globalHeading = 0.0; // for debugging

// PD controller values
const float SENSOR_KP = 1.0; // 2.0
const float SENSOR_KD = 0.8; // 0.5
int LEFT_TARGET = 28; //24
int RIGHT_TARGET = 32; //29

// Button variables         (9 is changed to reset)
const int BUTTON_PIN = 21;
const int BUTTON_2_PIN = 10;
const int BUTTON_3_PIN = 8;

// Debug levels
#define DEBUG_NONE 0
#define DEBUG_MINIMAL 1
#define DEBUG_FULL 2

// motor pins
#define M_FORWARD   16
#define M_BACKWARD   17
#define SLP    20

// Positioning variables
int robotX = 0;
int robotY = 0;
int robotDir = 0;


int mode; // 0 unconfigured 1 print sensors 2 test distance 3 test angle 4 wall follow 5 hardcoded 6 test MPU 7 solve maze

// --- SETUP ---
void setup() {

  // Setup BLE Serial
  Serial1.begin(9600);
  initButtons();
  Serial1.println("starting initMpu");
  initMpu();
  Serial1.println("initMpu is done!");
  resetHeading();

  // Initialize components
  setup_servo();
  initMotors();
  initEncoders();

  delay(2000);

  // get config details
  Serial1.println("------mouse 2026.5.1------");
  Serial1.println();

}


void loop() {
    printSensors();
    //test_left();
    //test_right();
    //setMotors(255);
    //Serial1.println(encoderValue);
    //updateMpu();
    //buttons();
    //one_cell_forward();
    //runFinal();
};

// -- SECOND CORE (USED FOR SENSORS & MPU) --

void setup1() {
  initSensors();
}

void loop1() {
  updateSensors();
};
