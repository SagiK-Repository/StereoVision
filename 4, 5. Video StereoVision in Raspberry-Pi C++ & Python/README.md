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
     <img src="https://user-images.githubusercontent.com/66783849/194889251-6c6db724-4e51-4560-aa4a-48a5d71c15b9.png" width="60%">  
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
     <img src="https://user-images.githubusercontent.com/66783849/194889663-b416b717-6f43-475e-a389-ccb6fee2d22d.png" width="40%">

<br><br><br>

# 3. Raspberry-Pi 원격 조종 설정

- 라즈베리 파이를 원격으로 조종하기 위한 설정을 진행한다.
  1. 왼쪽 상단 라즈베리 파이 아이콘 > Preferences -> Raspberry pi Configuration 실행 -> Interfaces -> SSH -> Enable 선택
  2. 터미널 창에 들어가 다음 명령어를 입력한다.
     ```bash
     sudo apt install xrdp   # 원격 데스크톱 연결
     
     # 경우에 따라 apt-get 기반일 수 있다.
     sudo apt-get install xrdp
     ```
  3. 이후 터미널에 다음 명령어를 입력하여 IP주소를 확인한다.
     ```bash
     hostname -I
     ```
     결과
     ```bash
     192.168.0.69
     ```
  4. 원격 데스크톱에서 연결할 컴퓨터에서 "원격 데스크톱"을 실행한다.  
     <img src="https://user-images.githubusercontent.com/66783849/194879592-e5a59d93-3c8e-470e-b41e-6b8de34cc57b.png" width="50%">  
     IP 주소를 입력 후 "옵션 표시(O)"를 클릭하여 자세한 사항을 설정한다.  
     <img src="https://user-images.githubusercontent.com/66783849/194879459-bd7fb4b5-f5cd-4927-aeb1-d2cdbc8968f8.png" width="50%">  
  5. 원격 데스크톱 연결할 대상에 Raspberry-Pi 사용자 이름을 넣는다.
  6. 이후 연결을 눌러 비밀번호를 눌러 원격 접속이 됨을 확인한다.  
     <img src="https://user-images.githubusercontent.com/66783849/194880213-dd565dcf-edc1-4b5b-b84c-fcda5bf98df2.png" width="50%">
     [‼만일 실패하거나 이상이 있을 경우 30초 정도가 지난 뒤에 나타나니, 기다려보자]
- 다음 에러와 같이 한 아이디로 여러 기기에서 동시 접속불가능한 경우 유저 아이디를 만든다.  
  <img src="https://user-images.githubusercontent.com/66783849/194885388-6adf58c6-dde0-404d-b699-6389cad8d55c.png" width="40%">  
  1. 다음 명령어를 터미널에 입력하여 아이디를 만든다.
     ```bash
     sudo adduser sagijju
     ```
     이후 패스워드 및 다양한 정보를 추가하여 아이디를 만든다.
  2. 새로 생성된 아이디로 원격데스크톱에 접속한다.
- 다음과 같이 접속에 성공한 화면을 확인한다.  
  <img src="https://user-images.githubusercontent.com/66783849/194887254-3d7cd188-88cf-4e80-bf85-a2c614cf8694.png" width="70%">  



<br><br><br>

# 4. StereoVision 이미지 획득

- StereoVision 이미지를 획득하기 위해서 StereoVision Camera를 통해 이미지를 획득할 수 있도록 한다.
- 3D 스테레오 카메라 모듈 IMX219-83 8MP을 Raspberry Pi와 연결하여 카메라 이미지를 획득해본다.
- 모듈에 대한 자세한 사용 방법을 [Arducam에서 제공하는 pdf](https://www.uctronics.com/download/Amazon/B016601.pdf)를 통해 확인한다.
- 또는 Arducam에서 제공하는 [ArduCAM Github](https://github.com/ArduCAM/RaspberryPi/tree/master/Multi_Camera_Adapter/Multi_Adapter_Board_2Channel_uc444) Tutorial을 확인한다.

<br>

## 스트레오 카메라 연결 및 환경설정

1. 왼쪽 상단 라즈베리 파이 아이콘 > Preferences -> Raspberry pi Configuration 실행 -> Interfaces -> I2C: -> Enable 선택  
   <img src="https://user-images.githubusercontent.com/66783849/194901722-965a700f-0603-4227-809c-93445b2d7094.png" width="300">  
2. 스트레오 비전 카메라를 라즈베리 파이에 연결한다.  
  <img src="https://user-images.githubusercontent.com/66783849/194897502-83c679e8-787d-4e5c-86ca-5f9becd3ce18.png" width="300">  
3. 다음과 같이 명령어를 입력한다.
   ```bash
   git clone https://github.com/ArduCAM/RaspberryPi.git
   ```
- 2가지 방법으로 이미지를 획득한다.

<br>

### Terminal 방법

1. 다음과 같이 Terminal에 입력한다.
   ```bash
   cd /tmp
   wget https://project-downloads.drogon.net/wiringpi-latest.deb
   sudo dpkg -i wiringpi-latest.deb
   ```
2. 다음과 같이 스크립트를 실행한다.
   ```bash
   cd ~
   cd RaspberryPi/Multi_Camera_Adapter/Multi_Adapter_Board_2Channel_uc444/shell
   sudo chmod +x pi_cam_uc444.sh
   sudo ./pi_cam_uc444.sh
   ```
3. 다음과 같이 Demo를 실행한다.
   ```bash
   sudo ./pi_cam_uc444.sh
   ```
- 이를 통해 카메라의 인식 여부를 확인한다.

<br>


### C++ 방법

1. OpenCV Library를 다운받는다.
   ```bash
   sudo apt install libopencv-dev
   ```
2. 컴파일 및 실행한다.
   ```bash
   cd RaspberryPi/Multi_Camera_Adapter/Multi_Adapter_Board_2Channel_uc444
   python arducam_multi_adapter_uc444.py
   ```
3. 다음과 같이 데모창이 나타나는지 확인한다.

<br><br><br>

## 참고

- [Raspberry Pi OS 설치](https://reddb.tistory.com/188)
- Raspberry-Pi 한글 설치 (입력 설치)
  - https://andjjip.tistory.com/86
  - https://jasmine125.tistory.com/1016
- [ArduCAM Multi_Adapter_Board_2Channel_uc444 pdf](https://www.uctronics.com/download/Amazon/B016601.pdf)
- [ArduCAM Multi_Adapter_Board_2Channel_uc444 Github](https://github.com/ArduCAM/RaspberryPi/tree/master/Multi_Camera_Adapter/Multi_Adapter_Board_2Channel_uc444)