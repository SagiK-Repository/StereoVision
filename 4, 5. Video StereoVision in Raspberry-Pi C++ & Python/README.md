문서정보 : 2022.08.28.~ 작성, 작성자 [@SAgiKPJH](https://github.com/SAgiKPJH)

# 목차
1. [Video StereoVision in Raspberry-Pi C++ & Python]
2. [Raspberry-Pi 환경 설정]
3. [Raspberry-Pi 원격 조종 설정]
4. [StereoVision 이미지 획득]
5. [StereoVision in C++]
6. [StereoVision in Python]
7. [StereoVision 결과]

<br><br><br>

# 1. Video StereoVision in Raspberry-Pi C++ & Python

Left, Right Image를 통해 C++ & Python 각각의 언어를 활용하여 Raspberry-Pi에서 StereoVision을 진행하는 것이 목표이다.  
이를 위한 PC 환경은 다음과 같다.  
- 두 환경 공통적으로 OpenCV 라이브러리를 활용한다.
- StereoVision 이미지 획득을 위해서 StereoVision Camera를 사용한다.

<br>

### ◆ 사용 장비

- 라즈베리 파이로 스트레오비전을 제어하기 위해서 다음과 같은 부품을 준비한다.
  - [3D 스테레오 카메라 모듈 IMX219-83 8MP](https://www.devicemart.co.kr/goods/view?no=13008080)  
    <img src="https://user-images.githubusercontent.com/66783849/187056296-254ea736-2c20-41d9-82d6-f4c9b4f71b63.png" width="30%">
    - 가격 : 73,700원
    - FOV : 83/73/50 degree (diagonal/horizontal/vertical)
    - 초점거리 : 2.6mm
    - 해상도 : 3280 × 2464
  - [Multi Camera Adapter Doubleplexer Stereo Module V2 for Raspberry Pi](https://www.devicemart.co.kr/goods/view?no=12231996)  
    <img src="https://user-images.githubusercontent.com/66783849/187056476-c0e7b858-d937-4c69-a62d-3a5ad0cdd741.png" width="30%">
    - 가격 : 38,000원
    - 2개의 5MP 또는 8MP 카메라 연결 가능
  - Raspberry Pi 4  
    <img src="https://user-images.githubusercontent.com/66783849/187056546-f6e57380-7b9f-4fbc-8552-96f0d3610119.png" width="30%">
    - 80,000원
    - 용량 4GB
    - [참고 사이트](https://www.devicemart.co.kr/goods/view?no=12234534)
  - 라즈베리 파이 microSD Card
  - [라즈베리파이 화면 모니터(5인치 800x480 HDMI LCD 모니터)](https://www.devicemart.co.kr/goods/view?no=1382229)
    - 가격 : 48,000원
    - 해상도 : 800x400 (5인치)
  - 모니터 전원 어댑터 및 라즈베리파이 전원 어댑터 (Micro-USB 5P타입,  USB C타입)
    - 가격 : 5,800원 * 2
    - 정격 출력 : DC 5V 4A
  - 케이블(microHDMI to HDMI)
    - 가격 : 3,000원

<br><br><br>


# 2. Raspberry-Pi 환경설정

- 라즈베리 파이를 실행시키기 위해서는, 준비한 micro-SD카드에 Raspberry-Pi의 OS를 설치한다.
  1. [라즈베리 홈페이지](https://www.raspberrypi.com/software/)로 이동한다.
  2. [Download for Windows](https://downloads.raspberrypi.org/imager/imager_latest.exe)를 눌러 imager를 설치한다.
  3. Raspberry Pi Imager를 실행하여 저장소 선택 후 운영체제(Raspberry-Pi OS FULL(32-BIT))를 선택한다.
     <img src="https://user-images.githubusercontent.com/66783849/194845184-58765031-2643-4d51-ada9-581398405b0d.png" width="60%">  
  4. 쓰기 버튼을 눌러 OS를 설치한다. 쓰기가 완료되었다는 창이 나오면 sd카드를 뺀다.
     <img src="https://user-images.githubusercontent.com/66783849/194847248-0b3d6b3d-134d-464a-b493-5b16c720f9a7.png" width="60%">  
  5. 이후 micro SD카드를 연결하여 raspberry-Pi를 킨다.
     <img src="https://user-images.githubusercontent.com/66783849/194858561-c4af5380-2209-4970-8c45-825c17583e2d.png" width="60%">  
  6. 각종 설정 이후 Rspberry-Pi를 재시작 한다. 다음과 같은 화면이 나타나면, 성공이다.
     <img src="https://user-images.githubusercontent.com/66783849/194858561-c4af5380-2209-4970-8c45-825c17583e2d.png" width="60%">  
- 한국어가 깨진 상태이면 다음과 같이 설정한다. 또한 한글 입력도 가능하도록 설정한다.
  1. 다음과 같이 터미널(<kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>T</kbd>)을 열고 명령창을 실행한다.
  2. 다음 명령어를 입력한다.
     ```bash
     sudo apt install fonts-unfonts-core   # 한글 폰트 설치

     # 경우에 따라 apt-get 기반일 수 있다.
     sudo apt-get install fonts-unfonts-core   # 한글 폰트 설치
     ```
  3. 왼쪽 상단 라즈베리 파이 아이콘 > Preferences -> Raspberry pi Configuration 실행 -> Localisation -> Set Locale... -> Language, Character Set을 각각 ko(Korean), UTF-8로 선택 되어있는지 확인한다.
  4. 한국어 입력을 위해서 다음과 같이 명령어를 입력한다.
     ```bash
     sudo apt install ibus-hangul
     sudo apt install fonts-unfonts-core

     # 경우에 따라 apt-get 기반일 수 있다.
     sudo apt-get install ibus-hangul
     sudo apt-get install fonts-unfonts-core
     ```
  5. 라즈베리파이 Reboot를 하여 한글이 잘 나타나는지 확인한다.



<br><br><br>

## 참고

- [Raspberry Pi OS 설치](https://reddb.tistory.com/188)
- Raspberry-Pi 한글 설치 (입력 설치)
  - https://andjjip.tistory.com/86
  - https://jasmine125.tistory.com/1016
