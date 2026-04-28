# Smartfarm with ESP32
## Description
ESP32로 간단한 Smart Farm 기능들을 구현했습니다.

<img width="40%" alt="KakaoTalk_20260428_162004375" src="https://github.com/user-attachments/assets/1b3c39e2-1fec-4a28-9e18-3daaf301a27a" />


### 제공 기능
 - 스마트팜에 필요한 기초 센싱
   - 온습도 측정
   - 토양 습도 측정
 - 측정 정보 표시 및 Cloud 전송
   - OLED Display에 정보 표시
   - Wi-Fi를 통해 측정 정보를 Thingspeak에 기록
 - 기타
   - RTC 모듈을 사용하여 Wi-Fi 연결 없이도 시각 관리 가능

### 개발 환경
이 프로젝트는  아래 환경으로 개발합니다.
 - ESP32
 - PlatformIO + VSCode

### 사용 HW 및 모델명
|종류|모델명|
|--|--|
|ESP32 보드|WROOM32(CH340)|
|온습도 센서|AHT20|
|토양 습도 센서|Unknown|
|RTC 모듈|DS1302|
|OLED 0.96"|SSD1306|

## how to use
 - [Wiki page](https://github.com/elly1000chun/smartfarm-with-esp32/wiki/How-to-setup)
