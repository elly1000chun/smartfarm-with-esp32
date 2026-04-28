# Smartfarm with ESP32
## Description
작성전

## how to setup
### Thingspeak setup
- Thingspeak 계정 만들기
	- https://thingspeak.mathworks.com/
- 신규 채널 생성
	- 채널 이름은 아무거나
	- 필드 3개를 활성화하고 아래와 같이 설정
		- Field 1: Temperature
		- Field 2: Humidity
		- Field3: Soil Dryness
### Install ESP32 driver
 - ESP32 보드를 PC에 연결
	 - 데이터 전송 가능한 USB-C cable 사용해야 함
 - CH340 driver 설치
	 - [참고](https://m.blog.naver.com/bpcode/223358194067)
###  소스코드 개발 환경 구성
 - VS Code 설치 [Link](https://code.visualstudio.com/)
 - VS Code Extension 화면에서 PlatformIO 검색해서 설치
 - 소스코드 체크아웃
 - VS Code로 소스코드 폴더 오픈
 - config 폴더 아래에 secrets.ini 파일 생성하고 wi-fi SSID, wi-fi password, Thingspeak Write API Key 기입
	 - secrets.ini.base 참고. 값에 " "는 불필요
 - VS Code 재시작
	 - 재시작하면서 각종 라이브러리가 자동으로 설치됨
 - VS Code 하단 파란색 바의 ✓ 버튼 클릭해서 정상적으로 빌드되는지 확인
 - VS Code 하단 파란색 바의  → 버튼 클릭해서 업로드
