#include <ArduinoBLE.h>
#include <Arduino_LSM6DS3.h>

#define BLE_UUID_GYROSCOPE_SERVICE "1101"
#define BLE_UUID_GYROSCOPE_X "2101"
#define BLE_UUID_GYROSCOPE_Y "2102"
#define BLE_UUID_GYROSCOPE_Z "2103"

#define BLE_DEVICE_NAME "Elfo"
#define BLE_LOCAL_NAME "Elfo"

BLEService gyroscopeService(BLE_UUID_GYROSCOPE_SERVICE);

BLEFloatCharacteristic gyroscopeCharacteristicX("2101", BLERead | BLENotify);
BLEFloatCharacteristic gyroscopeCharacteristicY(BLE_UUID_GYROSCOPE_Y, BLERead | BLENotify);
BLEFloatCharacteristic gyroscopeCharacteristicZ(BLE_UUID_GYROSCOPE_Z, BLERead | BLENotify);

float x, y, z;

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;

  // initialize IMU
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1)
      ;
  }

  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println("Hz");

  // initialize BLE
  if (!BLE.begin()) {
    Serial.println("Starting Bluetooth® Low Energy module failed!");
    while (1)
      ;
  }

  // set advertised local name and service UUID
  BLE.setLocalName(BLE_LOCAL_NAME);
  BLE.setAdvertisedService(gyroscopeService);

  // add characteristics and service
  gyroscopeService.addCharacteristic(gyroscopeCharacteristicX);
  gyroscopeService.addCharacteristic(gyroscopeCharacteristicY);
  gyroscopeService.addCharacteristic(gyroscopeCharacteristicZ);  
  BLE.addService(gyroscopeService);
    
  if (gyroscopeService.hasCharacteristic("2101"))
    Serial.print("yes");

  // start advertising
  BLE.advertise();

  Serial.println("BLE Gyroscope Peripheral");
}

void loop() {
  BLEDevice central = BLE.central();
  // obtain and write gyroscope data
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());

    // while the central is still connected to peripheral:
    while (central.connected()) {
      float x, y, z;

      if (IMU.gyroscopeAvailable()) {
        IMU.readGyroscope(x, y, z);

        gyroscopeCharacteristicX.setValue(x);
        gyroscopeCharacteristicY.setValue(y);
        gyroscopeCharacteristicZ.setValue(z);
      }

    }
  }
}