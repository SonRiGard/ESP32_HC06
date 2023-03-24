// #include <SoftwareSerial.h>

// SoftwareSerial BTSerial(16, 17); // RX | TX

// void setup() {
//   Serial.begin(9600);
//   BTSerial.begin(9600);
// }

// void loop() {
//   // if (BTSerial.available()) {
//   //   Serial.write(BTSerial.read());
//   // }
//   // if (Serial.available()) {
//   //   BTSerial.write(Serial.read());
//   // }
//    BTSerial.write("a/n");
// }

#include "BluetoothSerial.h"
#include "string.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(9600);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  // String str = "";

  // char charBuf[str.length() + 1];

  // str.toCharArray(charBuf, str.length() + 1);

  // // if (Serial.available()) {
  // //   SerialBT.write(Serial.read());
  // // }
  // // if (SerialBT.available()) {
  // //   Serial.write(SerialBT.read());
  // // }
  // // delay(20);
  // SerialBT.write(3);

    String str = "1.23,4.56,7.89";
  
  // Chuyển đổi chuỗi thành mảng ký tự
  char charBuf[str.length() + 1];
  str.toCharArray(charBuf, str.length() + 1);

  // Chuyển đổi mảng ký tự thành mảng các giá trị số
  double values[3];
  char *pch;
  pch = strtok(charBuf, ",");
  int i = 0;
  while (pch != NULL && i < 3) {
    values[i] = strtod(pch, NULL);
    pch = strtok(NULL, ",");
    i++;
  }

  // Chuyển đổi mảng các giá trị số thành mảng các byte
  uint8_t byteBuf[3 * sizeof(double)];
  memcpy(byteBuf, &values, 3 * sizeof(double));

  // Truyền mảng các byte qua SerialBT.write()
  SerialBT.write(byteBuf, 3 * sizeof(double));
  
  delay(1000);
  
}