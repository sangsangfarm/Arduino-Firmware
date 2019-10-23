# Arduino-Firmware

Arduino firmware update.

## Support platform

- esp8226
- esp32

## Usage

```cpp
char* url = "http://myFirmware.Url";
double version = 1.0;
Firmware firmware = Firmware(url, version);
firmware.update();
```

OR

```cpp
char* url = "http://myFirmware.Url";
double version = 1.0;
Firmware firmware = Firmware();
firmware.setUrl(url);
firmware.setVersion(1.0);
firmware.update();
```
