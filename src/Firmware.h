/**
 * @file Firmware.h
 * @brief 펌웨어 업데이트
 * @date 2019-08-27
 * @author Janghun Lee (jhlee@sangsang.farm)
 */

#ifndef FIRMWARE_H_
#define FIRMWARE_H_

#ifdef ESP8266
#include <ESP8266httpUpdate.h>
#elif defined(ESP32)
#include <ESP32httpUpdate.h>
#endif

#include <EEPROM.h>

#ifndef EEPROM_SIZE
#define EEPROM_SIZE 4096
#endif

// Debug
#ifndef FIRMWARE_DEBUG_PORT
#define FIRMWARE_DEBUG_PORT Serial
#endif

#ifdef FIRMWARE_DEBUG
#define print(...) FIRMWARE_DEBUG_PORT.print(__VA_ARGS__)
#define printf(...) FIRMWARE_DEBUG_PORT.printf(__VA_ARGS__)
#define println(...) FIRMWARE_DEBUG_PORT.println(__VA_ARGS__)

#else
#define print(...)
#define printf(...)
#define println(...)
#endif
/**
 * @struct FIRMWAREDATA
 * @brief 펌웨어 데이터
 * @date 2019-08-27
 * @author Janghun Lee (jhlee@sangsang.farm)
 */
struct FIRMWAREDATA {
  /** 펌웨어 url */
  char url[200];
  /** 펌웨어 주소 */
  double version;
};

/**
 * @brief 펌웨어
 * @date 2019-08-27
 * @author Janghun Lee (jhlee@sangsang.farm)
 */
class Firmware {
 private:
  FIRMWAREDATA firmware_data;
  int _eeprom_delete_address = 0;

 public:
  Firmware(void);
  Firmware(char *url);
  Firmware(char *url, double version);

  void set(char *url, double version);
  void setUrl(char *url);
  void setVersion(double version);

  void setEepromDeleteAddress(int eeprom_delete_address);
  void update(int count = 0);

  void printFirmwareDataInfo(void);
  void resetEEPROM(void);
};

#endif /* FIRMWARE_H_ */
