/**
 * @file Firmware.cpp
 * @brief 펌웨어 업데이트
 * @date 2019-08-27
 * @author Janghun Lee (jhlee@sangsang.farm)
 */

#include <Firmware.h>

/**
 * @fn Firmware::Firmware(void)
 * @brief 펌웨어 클래스 생성자
 * @return 펌웨어 클래스
 * @date 2019-08-27
 * @author Janghun Lee (jhlee@sangsang.farm)
 */
Firmware::Firmware(void) {}
/**
 * @fn Firmware::Firmware(char *url)
 * @brief 펌웨어 클래스 생성자
 * @param url 펌웨어 url
 * @return 펌웨어 클래스
 * @date 2019-08-27
 * @author Janghun Lee (jhlee@sangsang.farm)
 */
Firmware::Firmware(char *url) { setUrl(url); }

/**
 * @fn Firmware::Firmware(char *url, double version)
 * @brief 펌웨어 클래스 생성자
 * @param url 펌웨어 url
 * @param version 펌웨어 version
 * @return 펌웨어 클래스
 * @date 2019-08-27
 * @author Janghun Lee (jhlee@sangsang.farm)
 */
Firmware::Firmware(char *url, double version) {
  setUrl(url);
  setVersion(version);
}

/**
 * @fn void Firmware::set(char *url, double version)
 * @brief 펌웨어 url, 버전 설정
 * @param url 펌웨어 url
 * @param version 펌웨어 version
 * @return void
 * @date 2019-08-27
 * @author Janghun Lee (jhlee@sangsang.farm)
 */
void Firmware::set(char *url, double version) {
  setUrl(url);
  setVersion(version);
}

/**
 * @fn void Firmware::setUrl(char *url)
 * @brief 펌웨어 url 설정
 * @param url 펌웨어 url
 * @return void
 * @date 2019-08-27
 * @author Janghun Lee (jhlee@sangsang.farm)
 */
void Firmware::setUrl(char *url) {
  memcpy(firmware_data.url, url, sizeof(firmware_data.url));
}

/**
 * @fn void Firmware::setVersion(double version)
 * @brief 펌웨어 version 설정
 * @param version 펌웨어 version
 * @return void
 * @date 2019-08-27
 * @author Janghun Lee (jhlee@sangsang.farm)
 */
void Firmware::setVersion(double version) { firmware_data.version = version; }

/**
 * @fn void Firmware::setEepromDeleteAddress(int eeprom_delete_address)
 * @brief 펌웨어 EEPROM 주소 설정
 * @param eeprom_delete_address 설정할 EEPROM 주소
 * @return void
 * @date 2019-08-27
 * @author Janghun Lee (jhlee@sangsang.farm)
 */
void Firmware::setEepromDeleteAddress(int eeprom_delete_address) {
  _eeprom_delete_address = eeprom_delete_address;
}

/**
 * @fn void Firmware::printFirmwareDataInfo(void)
 * @brief 펌웨어 정보 보여줌
 * @return void
 * @date 2019-08-27
 * @author Janghun Lee (jhlee@sangsang.farm)
 */
void Firmware::printFirmwareDataInfo(void) {
  print(F("[Firmware] url: "));
  println(firmware_data.url);
  print(F("version: "));
  println(firmware_data.version, 4);
}

/**
 * @fn void Firmware::update(int count)
 * @brief 펌웨어 업데이트 총 10번 시도함.
 * @param count 업데이트 시도한 횟수
 * @return void
 * @date 2019-08-27
 * @author Janghun Lee (jhlee@sangsang.farm)
 */
void Firmware::update(int count) {
  if (count > 10) return;
  t_httpUpdate_return ret = ESPhttpUpdate.update(String(firmware_data.url));

  switch (ret) {
    case HTTP_UPDATE_FAILED:
      printf("[Firmware] HTTP_UPDATE_FAILED Error (%d): %s\n",
             ESPhttpUpdate.getLastError(),
             ESPhttpUpdate.getLastErrorString().c_str());
      update(count + 1);
      break;

    case HTTP_UPDATE_NO_UPDATES:
      println(F("[Firmware] HTTP_UPDATE_NO_UPDATES"));
      update(count + 1);
      break;

    case HTTP_UPDATE_OK:
      println(F("[Firmware] HTTP_UPDATE_OK"));
      break;
  }
}
// 영구 저장 주소전까지의 EEPROM 리셋

/**
 * @fn void Firmware::resetEEPROM(void)
 * @brief 영구 저장 주소전까지의 EEPROM 리셋
 * @return void
 * @date 2019-08-27
 * @author Janghun Lee (jhlee@sangsang.farm)
 */
void Firmware::resetEEPROM(void) {
  EEPROM.begin(EEPROM_SIZE);
  println(F("[Firmware] EEPORM reset"));
  for (int i = 0; i < _eeprom_delete_address; i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
  EEPROM.end();
}
