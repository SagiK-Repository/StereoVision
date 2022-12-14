문서정보 : 2022.08.28.~ 작성, 작성자 [@SAgiKPJH](https://github.com/SAgiKPJH)

# 목차
1. [Video StereoVision in Raspberry-Pi C++ & Python]
2. [Raspberry-Pi 환경 설정]
3. [Raspberry-Pi 원격 조종 설정]
4. [StereoVision 이미지 획득 - C++]
5. [StereoVision 이미지 획득 - Python]
6. [StereoVision in C++]
7. [StereoVision in Python]
8. [StereoVision 결과]

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
   - 이는 StereoVision 카메라 분배기가 I2C 통신을 하기 때문에 설정한다.  
  <img src="https://user-images.githubusercontent.com/66783849/194901722-965a700f-0603-4227-809c-93445b2d7094.png" width="300">  
2. 스트레오 비전 카메라를 라즈베리 파이에 연결한다.  
  <img src="https://user-images.githubusercontent.com/66783849/194897502-83c679e8-787d-4e5c-86ca-5f9becd3ce18.png" width="300">  
3. 다음과 같이 명령어를 입력한다.   
   ```bash
   git clone https://github.com/ArduCAM/RaspberryPi.git
   ```

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
  <img src="https://user-images.githubusercontent.com/66783849/195839241-978dc7e7-d964-4faa-8dd3-6c8f4ff6f893.png" height="400"> <img src="https://user-images.githubusercontent.com/66783849/195839071-c83f249b-7b8d-4786-8be0-c348f479080a.png" height="400">  
  <img src="https://user-images.githubusercontent.com/66783849/195847108-d9ed1b17-6278-4fe3-ab00-9193d743b946.png" width="350">
  ```bash
  > cd ~
  > cd RaspberryPi/Multi_Camera_Adapter/Multi_Adapter_Board_2Channel_uc444/shell
  > sudo chmod +x pi_cam_uc444.sh
  > sudo ./pi_cam_uc444.sh
  
  [sudo] sagijju의 암호: # 암호 입력
  
  Choose camera A
  No protocol specified
  Preview window unavailable
  [0:01:36.107728611] [2251]  INFO Camera camera_manager.cpp:293 libcamera v0.0.0+3866-0c55e522
  [0:01:36.153081243] [2252]  WARN RPI raspberrypi.cpp:1258 Mismatch between Unicam and CamHelper for embedded data usage!
  [0:01:36.154023661] [2252]  INFO RPI raspberrypi.cpp:1374 Registered camera /base/soc/i2c0mux/i2c@1/imx219@10 to Unicam device /dev/media3 and ISP device /dev/media1
  [0:01:36.154684637] [2251]  INFO Camera camera.cpp:1035 configuring streams: (0) 1640x1232-YUV420
  [0:01:36.155054134] [2252]  INFO RPI raspberrypi.cpp:761 Sensor: /base/soc/i2c0mux/i2c@1/imx219@10 - Selected sensor format: 1640x1232-SBGGR10_1X10 - Selected unicam format: 1640x1232-pBAA
  [0:01:41.301627280] [2251]  INFO Camera camera.cpp:1035 configuring streams: (0) 3280x2464-YUV420 (1) 3280x2464-SBGGR10_CSI2P
  [0:01:41.306439326] [2252]  INFO RPI raspberrypi.cpp:761 Sensor: /base/soc/i2c0mux/i2c@1/imx219@10 - Selected sensor format: 3280x2464-SBGGR10_1X10 - Selected unicam format: 3280x2464-pBAA
  Still capture image received
  
  Choose Camera B
  No protocol specified
  Preview window unavailable
  [0:01:42.070916110] [2264]  INFO Camera camera_manager.cpp:293 libcamera v0.0.0+3866-0c55e522
  [0:01:42.099557730] [2265]  WARN RPI raspberrypi.cpp:1258 Mismatch between Unicam and CamHelper for embedded data usage!
  [0:01:42.100621502] [2265]  INFO RPI raspberrypi.cpp:1374 Registered camera /base/soc/i2c0mux/i2c@1/imx219@10 to Unicam device /dev/media3 and ISP device /dev/media1
  [0:01:42.101433460] [2264]  INFO Camera camera.cpp:1035 configuring streams: (0) 1640x1232-YUV420
  [0:01:42.102049494] [2265]  INFO RPI raspberrypi.cpp:761 Sensor: /base/soc/i2c0mux/i2c@1/imx219@10 - Selected sensor format: 1640x1232-SBGGR10_1X10 - Selected unicam format: 1640x1232-pBAA
  [0:01:47.254229385] [2264]  INFO Camera camera.cpp:1035 configuring streams: (0) 3280x2464-YUV420 (1) 3280x2464-SBGGR10_CSI2P
  [0:01:47.256323988] [2265]  INFO RPI raspberrypi.cpp:761 Sensor: /base/soc/i2c0mux/i2c@1/imx219@10 - Selected sensor format: 3280x2464-SBGGR10_1X10 - Selected unicam format: 3280x2464-pBAA
  Still capture image received
  Test OK
  ```

<br>

### Python version (RaspberryPi Direct Display)

- 이 방법은 실시간으로 카메라 영상을 받을 수 있지만, 원격데스크톱과 같은 연결에서는 확인이 어렵다. 떄문에 RaspberryPi를 직접 연결한 모니터에서 테스트해본다.
1. OpenCV Library를 다운받는다.
   ```Bash
   sudo apt install -y python3-libcamera python3-kms++
   sudo apt install -y python3-prctl libatlas-base-dev ffmpeg libopenjp2-7 python3-pip
   pip3 install numpy --upgrade
   pip3 install picamera2
   ```
2. 컴파일 및 실행한다.
   ```bash
   cd ~
   cd RaspberryPi/Multi_Camera_Adapter/Multi_Adapter_Board_2Channel_uc444
   make
   python arducam_multi_adapter_uc444.py
   ```
3. For the use of remote control terminals, first specify the location of the image display
   ```Bash
   export DISPLAY=:0
   python arducam_multi_adapter_uc444.py
   ```
4. For users who directly operate locally
   ```Bash
   python arducam_multi_adapter_uc444.py
   ```
3. 다음과 같이 데모창이 나타나는지 확인한다.
- [‼ 오류 qt.qpa.xcb: could not connect to display :0]
  - 원격데스크톱의 경우, 연결이 어렵다.
  - ssh를 통해 연결하면 디스플레이 창을 window에 띄우는게 가능한데, 자세한건 다음 사이트를 참고한다.  
<img src="https://user-images.githubusercontent.com/66783849/195968466-3d5781d2-2925-46da-93d5-aac7e5173ebf.png" width="250">

<br><br>

## RaspberryPi C++, Python 실행

- RaspberryPi에서 C++, Python을 컴파일하고 실행해본다.

### C++ on RaspberryPi

- RaspberryPi에서 폴더를 열어 hello.cpp라는 파일을 만든 후 아래와 같이 작성한다.
  ```cpp
  #include <iostream>
  using namespace std;
  
  int main()
  {
     cout << "Hello RaspberryPi in C++" << endl;
     return 0;
  }
  ```
  <img src="https://user-images.githubusercontent.com/66783849/195969413-dbc2bead-4dbc-4595-916c-9975f51646c5.png" width="350">
- Terminal로 hello.cpp 를 만든 폴더 위치로 이동한 다음 다음과 같이 명령어를 입력한다.
  ```bash
  g++ -o hello hello.cpp
  ```
- 이후 만들어진 hello를 실행한다.
  ```bash
  ./hello
  ```
  <img src="https://user-images.githubusercontent.com/66783849/195969449-d520493f-e76a-469a-a7d1-680820b4e178.png" width="350">
- 참조 : [Getting Started with C++ on Raspberry Pi (Guide & examples)](https://raspberrytips.com/use-c-on-raspberry-pi/)

<br>

### Python on RaspberryPi

- Python은 커맨드로 작성이 가능하다. (또는 vi로 문서를 만든 후 실행시킨다)
- <kbd>Ctrl</kbd>+<kbd>D</kbd>를 통해 빠져나온다.
  ```bash
  $ python
  
  Python 3.9.2 (default, Mar 12 2021, 04:06:34) 
  [GCC 10.2.1 20210110] on linux
  Type "help", "copyright", "credits" or "license" for more information.
  >>> print("hello")
  hello
  >>>
  ```
  <img src="https://user-images.githubusercontent.com/66783849/195969530-f65812c9-be86-47ed-8fa9-572909f24596.png" width="400">
- 하지만 문서로 작성하여 보다 편하고 빠르게 작업한다.
- RaspberryPi에서 폴더를 열어 hello.py라는 파일을 만든 후 아래와 같이 작성한다.
  ```python
  print("Hello, RaspberryPI in Python")
  ```
  <img src="https://user-images.githubusercontent.com/66783849/195969621-e12ac22d-cf12-4661-b4cc-8e85945a1b52.png" width="350">
- Terminal로 hello.py 를 만든 폴더 위치로 이동한 다음 다음과 같이 명령어를 입력한다.
  ```bash
  $ python hello.py

  Hello, RaspberryPI in Python
  ```
  <img src="https://user-images.githubusercontent.com/66783849/195969660-356ccc06-6079-476b-afc4-2cb7e9fa6e0d.png" width="350">
- 참조 : [[라즈베리파이] 라즈비안 안에서 python 사용하기](https://m.blog.naver.com/dokkosam/221868691692)

<br><br>

## StereoVision 이미지 획득 - C++

- StereoVision의 이미지를 획득하기 위해서 기존에 진행했었던 C++, Python 코드를 GitClone하여 받아 참고하면서 만든다.
- 이때 코드는 사진을 변환하는 예제이기 때문에, 영상을 출력하는 예제로 변환하는 작업을 진행한다.

### C++ 기본

- RaspberryPi C++ 코드를 다음과 같이 작성한다.  
- 우선, 다양한 StereoVision 기법이 존재하기에, 입력별로 다른 기법이 진행될 수 있도록 다음과 같이 구성한다.
  ```cpp
  // get_argv_test.cpp

  #include <iostream>
  using namespace std;
    
  int main(int argc, char *argv[])
  {
     cout << "Hello RaspberryPi in C++" << endl;
     cout << argv[1] << endl;
     return 0;
  }
  
  // g++ -o get_argv_test "get_argv_test.cpp"
  // ./get_argv_test hello
  ```
  <img src="https://user-images.githubusercontent.com/66783849/195970125-a9012221-14d9-4b83-883f-f6b3d4607fe8.png" width="350">

<br>

### C++ OpenCV

- OpenCV를 CPP로 연동하기 위해서 다음과 같이 Linux에서 OpenCV를 구현하는 것을 활용한다.
- 다음과 같이 기본적인 환경을 설정한다. (C++ 컴파일러, git, CMake, make 등등)
  ```bash
  sudo apt install -y g++ cmake make git libgtk2.0-dev pkg-config
  ```
- [opencv git 주소](https://github.com/opencv/opencv)로 가서 git 링크를 받아온다.
- 이후 git clone을 진행한다.
  - 이때, 붙여넣기는 <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>V</kbd>를 활용한다.
  ```bash
  cd ~ && git clone https://github.com/opencv/opencv.git
  ```
- Build the source 공간을 만든다.
  ```bash
  mkdir -p build && cd build
  ```
- OpneCV를 컴파일(cmake)한다.
  ```bash
  cmake ../opencv
  make -j4
  # 상당히 오래 걸린다.
  # 만일 opencv 내부의 디렉토리의 빌드가 오래걸린다면, 디렉토리를 제외시키고(다른데 옮겨놓자) 다시빌드한다.
  ```
  <img src="https://user-images.githubusercontent.com/66783849/195997441-48e58c1d-05ef-4cb0-ac76-ee75dfb87fb4.png" width="450">
- OpenCV Package를 Install한다.
  ```bash
  sudo make install
  ```
  <img src="https://user-images.githubusercontent.com/66783849/196418075-cd29f8cf-7e9b-4cbd-a7c2-bfac2aac11d5.png" width="450">  
  <img src="https://user-images.githubusercontent.com/66783849/196418121-1575d2bd-bb78-43c5-9c02-b0c6d95a3d12.png" width="450">
- "/usr/local/include/opencv4"에 opencv4가 설치됨을 확인한다.  
  <img src="https://user-images.githubusercontent.com/66783849/196419175-c0f16a67-be48-4b53-8b1c-0bfed890b8b9.png" width="450">
- Test는 다음과 같이 진행한다.
  ```bash
  # Test를 진행할 폴더를 구성한다.
  mkdir test && cd test
  
  # cpp 문서를 만든다. (nano 또는 vi 사용)
  nano DisplayImage.cpp
  ```
- DisplayImage.cpp에 다음 내용을 <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>V</kbd>를 통해 넣는다.
  ```cpp
  #include <opencv2/opencv.hpp>
  #include <stdio.h>
  using namespace cv;
  int main(int argc, char** argv)
  {
      if (argc != 2) {
          printf("usage: DisplayImage.out <Image_Path>\n");
          return -1;
      }
      Mat image;
      image = imread(argv[1], 1);
      if (!image.data) {
          printf("No image data \n");
          return -1;
      }
      namedWindow("Display Image", WINDOW_AUTOSIZE);
      imshow("Display Image", image);
      waitKey(0);
      return 0;
  }
  ```
- 그리고 다음 CMakeLists.txt를 만들어 다음과 같은 내용을 넣는다.
  ```bash
  nano CMakeLists.txt
  ```
  ```bash
  cmake_minimum_required(VERSION 2.8)
  project( DisplayImage )
  find_package( OpenCV REQUIRED )
  include_directories( ${OpenCV_INCLUDE_DIRS} )
  add_executable( DisplayImage DisplayImage.cpp )
  target_link_libraries( DisplayImage ${OpenCV_LIBS} )
  ```
- 그리고 이어서 cmake를 통해 빌드 파일을 생성한다.
  ```bash
  cmake .
  ```
  <img src="https://user-images.githubusercontent.com/66783849/196420932-4652fdd3-1d13-44c7-bbdf-91afbeba4ec9.png" width="350">
- 마지막으로 다음 명령으로 make를 사용하여 프로그램을 빌드한다.
  ```bash
  make
  ```
  <img src="https://user-images.githubusercontent.com/66783849/196421477-da7b21fa-d9e7-4758-9f0e-b993cad0b78c.png" width="450">
- 다음 명령을 통해 이미지 띄우는 테스트를 해본다.
  ```bash
  ./DisplayImage path_of_the_image

  # 예
  ./DisplayImage path_of_the_image
  ```
- 참조
  - [How to Install opencv in C++ on Linux?](https://www.geeksforgeeks.org/how-to-install-opencv-in-c-on-linux/)



<br>

### pi_cam_uc444.sh 분석

- pi_cam_uc444.sh의 내용은 다음과 같다.
  ```bash
  #!/bin/sh
  raspi-gpio set 4 op # GPIO 4 OUTPUT
  raspi-gpio set 17 op # GPIO 17 OUTPUT
  i2cset -y 1 0x70 0x00 0x01 # I2C 통신 - 0x70에 0x00 0x01 전송
  # i2cset
  # i2cset은 I2C 버스를 통해 볼 수 있는 레지스터를 설정하는 프로그램
  # -y 대화식 모드를 비활성화
  # 1 : 스캔할 I2C 버스의 번호 또는 이름
  # 0x70 : 버스의 칩 주소를 지정
  # 0x00 : 쓸 칩의 주소를 지정
  # 0x01 : 지정된 경우 칩의 해당 위치에 쓸 값
  raspi-gpio set 17 dl #set the gpio17 low
  raspi-gpio set  4 dl #set the gpio4 low
  echo "Choose camera A"
  libcamera-still -o camera1.jpg # 촬영 (기본 5초뒤 촬영)
  i2cset -y 1 0x70 0x00 0x02
  raspi-gpio set 17 dl #set the gpio17 low
  raspi-gpio set  4 dh #set the gpio4 high
  echo "Choose Camera B"
  libcamera-still -o camera2.jpg
  echo "Test OK"
  ```
- 이를 다음과 같이 축약할 수 있다.
  ```bash
  #!/bin/sh
  raspi-gpio set 4 op dl
  raspi-gpio set 17 op dl
  i2cset -y 1 0x70 0x00 0x01 
  echo "Choose camera A"
  libcamera-still -t 1 -o camera1.jpg # 0.001초뒤 촬영
  i2cset -y 1 0x70 0x00 0x02
  raspi-gpio set  4 dh #set the gpio4 high
  echo "Choose Camera B"
  libcamera-still -t 1 -o camera2.jpg
  echo "Test OK"
  ```

<br>

### C++ OpenCV 활용한 영상 출력


<br><br>


## StereoVision 이미지 획득 - Python

<br>

### arducam_multi_adapter_uc444.py 분석

- python에서 실시간 영상에 대해서 필요한 부분만 추려내면 다음과 같다.
  ```python
  import numpy as np
  from picamera2 import Picamera2
  from PyQt5.QtGui import QImage,QPixmap
  from PyQt5.QtCore import QThread,Qt
  import RPi.GPIO as gp
  import time
  import os
  
  width = 320
  height = 240 
  
  adapter_info = {  
      "A" : {   
          "i2c_cmd":"i2cset -y 10 0x70 0x00 0x01",
          "gpio_sta":[0,0],
      }, "B" : {
          "i2c_cmd":"i2cset -y 10 0x70 0x00 0x02",
          "gpio_sta":[1,0],
      }
  }
  picam2 = Picamera2()
  
  class WorkThread(QThread):
  
      def __init__(self):
          super(WorkThread,self).__init__()
          gp.setwarnings(False)
          gp.setmode(gp.BOARD)
          gp.setup(7, gp.OUT)
          gp.setup(11, gp.OUT)
  
      def select_channel(self,index):
          channel_info = adapter_info.get(index)
          if channel_info == None:
              print("Can't get this info")
          gpio_sta = channel_info["gpio_sta"] # gpio write
          gp.output(7, gpio_sta[0])
          gp.output(11, gpio_sta[1])
  
      def init_i2c(self,index):
          channel_info = adapter_info.get(index)
          os.system(channel_info["i2c_cmd"]) # i2c write
  
      def run(self):
          global picam2
          flag = False
          for item in {"A","B"}:
              try:
                  self.select_channel(item)
                  self.init_i2c(item)
                  time.sleep(0.5) 
                  picam2.close()
                  print("init1 "+ item)
                  picam2 = Picamera2()
                  picam2.configure(picam2.create_still_configuration(main={"size": (320, 240),"format": "BGR888"},buffer_count=2)) 
                  picam2.start()
                  picam2.set_controls({"AeEnable":False,"ExposureTime":30000,"AnalogueGain":6})
                  time.sleep(2)
                  picam2.capture_array("main",wait=True)
                  time.sleep(0.1)
              except Exception as e:
                  print("except: "+str(e))
  
          while True:
              for item in {"A","B"}:
                  self.select_channel(item)
                  time.sleep(0.02)
                  try:
                      buf = picam2.capture_array("main",wait=True)
                      buf = picam2.capture_array("main",wait=True)
                      cvimg = QImage(buf, width, height,QImage.Format_RGB888)
                      pixmap = QPixmap(cvimg)
                      if item == 'A':
                          image_label.setPixmap(pixmap)
                      elif item == 'B':
                          image_label2.setPixmap(pixmap)
                  except Exception as e:
                      print("capture_buffer: "+ str(e))
  
  layout_h = QHBoxLayout()
  layout_h1= QHBoxLayout()
  image_label = QLabel()
  image_label2 = QLabel()
  
  work = WorkThread()
  
  if __name__ == "__main__":
      image_label.setFixedSize(320, 240)
      image_label2.setFixedSize(320, 240)
  
      layout_h.addWidget(image_label)    
      layout_h.addWidget(image_label2)
  
      work.start()
      
      app.exec()
      work.quit()
      picam2.close()
  ```
- 위 코드를 간단히 추리면 다음과 같다.
  ```python

  adapter_info = {  
      "A" : {   
          "i2c_cmd":"i2cset -y 10 0x70 0x00 0x01",
          "gpio_sta":[0,0],
      }, "B" : {
          "i2c_cmd":"i2cset -y 10 0x70 0x00 0x02",
          "gpio_sta":[1,0],
      }
  }

  ## raspberrypi에서 지원하는 카메라 획득 관련 객체
  picam2 = Picamera2()
  
  ## GPIO 7, 11을 OUTPUT 모드로 설정한다.
    def __init__(self):
        super(WorkThread,self).__init__()
        gp.setwarnings(False)
        gp.setmode(gp.BOARD)
        gp.setup(7, gp.OUT)
        gp.setup(11, gp.OUT)
  
  ## A번 카메라, B번 카메라에 따라 출력을 달리 한다. (00, 01) 
    def select_channel(self,index):
        ## 생략
        gp.output(7, gpio_sta[0])
        gp.output(11, gpio_sta[1])

  ## os.system을 통해 직접 cmd에 "i2cset -y 10 0x70 0x00 0x01" or "0x02"를 입력한다.
    def init_i2c(self,index):
        channel_info = adapter_info.get(index)
        os.system(channel_info["i2c_cmd"]) # i2c write

  ## Thread 실행시
    def run(self):
        global picam2
        flag = False
        for item in {"A","B"}:
            try:
                self.select_channel(item) ## GPIO 출력 설정
                self.init_i2c(item) ## i2cset 명령어 실행
                time.sleep(0.5)  ## 0.5초의 휴식기간
                picam2.close()   ## 카메라 종료
                print("init1 "+ item) 
                picam2 = Picamera2() ## 새로운 카메라 객체 선언
                picam2.configure(picam2.create_still_configuration(main={"size": (320, 240),"format": "BGR888"},buffer_count=2))  ## 카메라 속성 설정
                picam2.start() ## 카메라 시작
                picam2.set_controls({"AeEnable":False,"ExposureTime":30000,"AnalogueGain":6}) ## 카메라 제어
                time.sleep(2) ## 2ms 대기
                picam2.capture_array("main",wait=True) ## 캡쳐 테스트
                time.sleep(0.1) ## 0.1ms 대기
            except Exception as e:
                print("except: "+str(e))

        while True: ## 반복문 돌입
            for item in {"A","B"}:
                self.select_channel(item) ## GPIO 출력 설정
                time.sleep(0.02) ## 0.02초 휴식
                try:
                    buf = picam2.capture_array("main",wait=True) ## 이미지 가져오기 (캡쳐)
                    buf = picam2.capture_array("main",wait=True)
                    cvimg = QImage(buf, width, height,QImage.Format_RGB888) ## 이미지 QImage로 변환
                    pixmap = QPixmap(cvimg) ## Qimage를 QPixamap으로 전달
                    if item == 'A':
                        image_label.setPixmap(pixmap) ## A 카메라의 경우, 1번 화면에 출력
                    elif item == 'B':
                        image_label2.setPixmap(pixmap) ## B 카메라의 경우, 2번 화면에 출력
                except Exception as e:
                    print("capture_buffer: "+ str(e))
  ```
- raspberr pi에서 opencv를 설치하기 위해 다음과 같은 과정을 거친다.
  - opnecv를 설치하기 위해 sudo가 없으면 메인 계정에는 설치가 안된다.
  - 하지만 sudo pip install은 위험하다. [Sudo pip install은 안돼요!](https://medium.com/@chullino/sudo-%EC%A0%88%EB%8C%80-%EC%93%B0%EC%A7%80-%EB%A7%88%EC%84%B8%EC%9A%94-8544aa3fb0e7)
  - sudo없이 python을 실행하면, 메인 계정이 아닌 경우, RPi를 활용할 수 없다.
  - 하지만 sudo와 함께 python을 실행하면 opencv를 활용할 수 없다.
  - 따라서 user 계정에 root 권한을 주어 RPi 문제를 해결하고, opencv를 활용해보자.
  ```bash
  # 원격 연결이 아닌경우, 생략
  id ## 내 계정의 상태 알아보기
  sudo vi /etc/group # Group 설정
  ```
  ```bash
  # 원격 연결이 아닌경우, 생략
  # i2c, gpio 뒤에 username을 추가한다. (예-juhyung1021, sagijju)
  sudo:x:998:juhyung1021,sagijju
  audio:x:998:juhyung1021,sagijju
  video:x:998:juhyung1021,sagijju ## ssh 원격접근이 조금 느려진다
  i2c:x:998:juhyung1021,sagijju
  gpio:x:997:juhyung1021,sagijju
  ```
  - 다음과 같이 계정의 접근 권한을 추가를 한다.
  ```bash
  sudo -i
  # super user 리스트에 들어가기
  sudo vi /etc/sudoers

  # User Privilege specification 에 다음과 같이 작성한다.
  root      ALL=(ALL:ALL) ALL
  username  ALL=(ALL:ALL) NOPASSWD: ALL # super user로 등록
  # esc 및 ":wq!"를 입력 후 저장한다.
  ```
  - 이어서 opencv를 설치 및 실행한다.
  ```bash
  # sudo pip install opencv-python
  # root에서 실행
  # pip install opencv-contrib-python ## 메인 계정의 경우
  pip install opencv-python
  # 조금 시간이 걸린다.
  # 이후 python3를 입력후 impoty cv2를 통해 정상작동하는지 확인한다.
  ```
- picamera2 캡쳐 이미지 값을 mat로 변환하여 가져오는 방식을 알아보면 다음과 같다.
  ```python
  import cv2
  image = picam2
  image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
  cv2.imshow('image', image)
  key = cv2.waitKey(1) & 0xff
  if key == 27 :
    break
  ```
- 필요한 내용만 추려서 다음과 같이 실행할 수 있다.
  ```python
  import numpy as np
  from picamera2 import Picamera2
  import RPi.GPIO as gp
  import time
  import os
  import cv2
  
  adapter_info = {  
    "A" : {   
        "i2c_cmd":"i2cset -y 10 0x70 0x00 0x01",
        "gpio_sta":[0,0],
    }, "B" : {
        "i2c_cmd":"i2cset -y 10 0x70 0x00 0x02",
        "gpio_sta":[1,0],
    }
  }

  picam2 = Picamera2() ## raspberrypi에서 지원하는 카메라 획득 관련 객체
  
  ## GPIO 7, 11을 OUTPUT 모드로 설정한다.
  gp.setwarnings(False)
  gp.setmode(gp.BOARD)
  gp.setup(7, gp.OUT)
  gp.setup(11, gp.OUT)

  ## A번 카메라, B번 카메라에 따라 출력을 달리 한다. (00, 01) 
  def select_channel(index):
      channel_info = adapter_info.get(index)
      gpio_sta = channel_info["gpio_sta"] # gpio write
      gp.output(7, gpio_sta[0])
      gp.output(11, gpio_sta[1])

  ## os.system을 통해 직접 cmd에 "i2cset -y 10 0x70 0x00 0x01" or "0x02"를 입력한다.
  def init_i2c(index):
      channel_info = adapter_info.get(index)
      os.system(channel_info["i2c_cmd"]) # i2c write

  ## Thread 실행시
  def run():
      global picam2
      flag = False
      for item in {"A","B"}:
          try:
              select_channel(item) ## GPIO 출력 설정
              init_i2c(item) ## i2cset 명령어 실행
              time.sleep(0.5)  ## 0.5초의 휴식기간
              picam2.close()   ## 카메라 종료
              print("init1 "+ item) 
              picam2 = Picamera2() ## 새로운 카메라 객체 선언
              picam2.configure(picam2.create_still_configuration(main={"size": (320, 240),"format": "BGR888"},buffer_count=2))  ## 카메라 속성 설정
              picam2.start() ## 카메라 시작
              picam2.set_controls({"AeEnable":False,"ExposureTime":30000,"AnalogueGain":6}) ## 카메라 제어
              time.sleep(2) ## 2ms 대기
              picam2.capture_array("main",wait=True) ## 캡쳐 테스트
              time.sleep(0.1) ## 0.1ms 대기
          except Exception as e:
              print("except: "+str(e))
      while True: ## 반복문 돌입
          for item in {"A","B"}:
              select_channel(item) ## GPIO 출력 설정
              time.sleep(0.02) ## 0.02초 휴식
              try:
                  buf = picam2.capture_array("main",wait=True) ## 이미지 가져오기 (캡쳐)
                  buf = picam2.capture_array("main",wait=True)
                  buf = cv2.cvtColor(buf, cv2.COLOR_BGR2RGB)
                  if item == 'A':
                      cv2.imshow('A_image', buf)
                  elif item == 'B':
                      cv2.imshow('B_image', buf)
                  key = cv2.waitKey(1) & 0xff
                  if key == 27 :
                    break
              except Exception as e:
                  print("capture_buffer: "+ str(e))

  run()
  ```
  ```bash
  python3 python_test.py
  ```
  <img src="https://user-images.githubusercontent.com/66783849/199037541-244ed34c-176f-4b1e-ad13-5624c489294e.png" width="450">

<br>

### Python 활용한 영상 출력

- 다양한 버전별로 StereoVision을 Test한다.
  ```python
  def StereoBM(imgL,imgR, nD = 16, bS = 15) :
    imgL = cv2.cvtColor(imgL,cv2.COLOR_RGB2GRAY)
    imgR = cv2.cvtColor(imgR,cv2.COLOR_RGB2GRAY)
    stereo = cv2.StereoBM_create(nD, bS)
    stereo.setDisp12MaxDiff(25)
    stereo.setUniquenessRatio(15)
    start = time.time()
    disparity = stereo.compute(imgL,imgR)
    end = time.time()
    print(f"cal {end - start:.5f} sec")
    print(f"fps {1/(end - start):.5f} sec")
    disparity = cv2.normalize(disparity, None, 0, 255, cv2.NORM_MINMAX)
    disparity = np.uint8(disparity)
    return disparity
      
  def StereoSGBM(imgL,imgR, nD = 16, bS = 15, win_size=3) :
    imgL = cv2.cvtColor(imgL,cv2.COLOR_RGB2GRAY)
    imgR = cv2.cvtColor(imgR,cv2.COLOR_RGB2GRAY)
    stereo = cv2.StereoSGBM_create(
        numDisparities=nD,
        blockSize=bS,
        uniquenessRatio=5,
        speckleWindowSize=5,
        speckleRange=5,
        disp12MaxDiff=25,
        P1=8 * 3 * win_size ** 2,
        P2=32 * 3 * win_size ** 2,
    )
    start = time.time()
    disparity = stereo.compute(imgL,imgR)
    end = time.time()
    print(f"cal {end - start:.5f} sec")
    print(f"fps {1/(end - start):.5f} sec")
    disparity = cv2.normalize(disparity, None, 0, 255, cv2.NORM_MINMAX)
    disparity = np.uint8(disparity)
    return disparity
  
  def Census_Transform (left, right, window_size = 5, ndisp = 7):
    left = cv2.cvtColor(left,cv2.COLOR_RGB2GRAY)
    right = cv2.cvtColor(right,cv2.COLOR_RGB2GRAY)
    ct_left = norm(transform(left, window_size)) ## Census Transform
    ct_right = norm(transform(right, window_size))
    ct_costs = [] ## Result
    start = time.time()
    for exponent in range(0, 6):
        import math
        disparity = int(ndisp / math.pow(2, exponent))
        #print(math.pow(2, exponent), disparity)
        ct_costs.append(norm(cost(left, right, window_size, disparity)))
    disparity = ct_costs[0].copy()
    end = time.time()
    print(f"cal {end - start:.5f} sec")
    print(f"fps {1/(end - start):.5f} sec")
    disparity = cv2.normalize(disparity, None, 0, 255, cv2.NORM_MINMAX)
    disparity = np.uint8(disparity)
    return disparity
  ```
- 이때, 다음과 같이 time을 활용해 FPS를 측정한다.
  ```python
      start =time.time()
      while True: ## 반복문 돌입
          for item in {"A","B"}:
              select_channel(item) ## GPIO 출력 설정
              time.sleep(0.02) ## 0.02초 휴식
              try:
                  buf = picam2.capture_array("main",wait=True)
                  buf = cv2.cvtColor(buf, cv2.COLOR_BGR2RGB)
                  if item == 'A':
                      cv2.imshow('A_image', buf)
                  elif item == 'B':
                      cv2.imshow('B_image', buf)
                      endtime = time.time()-start
                      print("t : ",endtime)
                      print("FPS = ",1/endtime)
                      start = time.time()
                  key = cv2.waitKey(1) & 0xff
                  if key == 27 :
                    break
              except Exception as e:
                  print("capture_buffer: "+ str(e))
  ```
- 다음과 같이 코드를 활용해 StereoVision 이미지를 획득한다.
  ```python
      select_channel("A") 
  	  imageA = picam2.capture_array("main",wait=True)
      while True: ## 반복문 돌입
          for item in {"A","B"}:
              select_channel(item) ## GPIO 출력 설정
              time.sleep(0.02) ## 0.02초 휴식
              try:
                  buf = picam2.capture_array("main",wait=True)
                  buf = cv2.cvtColor(buf, cv2.COLOR_BGR2RGB)
                  if item == 'A':
                      cv2.imshow('A_image', buf)
                      imageA = buf
                  elif item == 'B':
                      cv2.imshow('B_image', buf)
                      cv2.imshow('stereo',StereoBM(imageA, buf, 16*4, 17))
                      # cv2.imshow('stereo',StereoSGBM(imageA, buf, 16*4, 17))
                      # cv2.imshow('stereo',Census_Transform(imageA, buf, 17, 16*4))
                      endtime = time.time()-start
                      print("t : ",endtime)
                      print("FPS = ",1/endtime)
                      start = time.time()
                  key = cv2.waitKey(1) & 0xff
                  if key == 27 :
                    break
              except Exception as e:
                  print("capture_buffer: "+ str(e))
  ```
- 다음과 같이 각도를 조절한다.
  ```python
  # 생략
  width = 320
  height = 240
  angle = -10
  M = cv2.getRotationMatrix2D((width / 2, height / 2), angle, 1)
  # 생략
  ## Thread 실행시
  def run():
      global picam2
  
      # 생략

      imageA = picam2.capture_array("main",wait=True)
      while True:
          for item in {"A","B"}:
              select_channel(item)
              time.sleep(0.002)
              try:
                  buf = picam2.capture_array("main",wait=True) 
                  buf = picam2.capture_array("main",wait=True)
                  buf = cv2.cvtColor(buf, cv2.COLOR_BGR2RGB)
                  if item == 'A':                
                      buf = cv2.warpAffine(buf, M, (width, height))
                      cv2.imshow('A_image', buf)
                      imageA = buf.copy()
                  elif item == 'B':
                      buf = cv2.warpAffine(buf, M, (width, height))
                      cv2.imshow('B_image', buf)
                      cv2.imshow('stereo',StereoBM(imageA, buf))
      #생략
  ```
  <img src="https://user-images.githubusercontent.com/66783849/199503776-6db9c32e-140b-4d72-a65a-429632546459.png" width="450">
- 이 Stereo Vision Camera에 맞는 Stereo 속성 값을 [예제](https://github.com/SagiK-Repository/StereoVision/tree/main/2%2C%203.%20Image%20StereoVision%20in%20PC%20C%2B%2B%20%26%20Python#-stereobm-stereosgbm)를 통해 얻는다.

<br><br><br>

#

##

## 참고

- [Raspberry Pi OS 설치](https://reddb.tistory.com/188)
- Raspberry-Pi 한글 설치 (입력 설치)
  - https://andjjip.tistory.com/86
  - https://jasmine125.tistory.com/1016
- [ArduCAM Multi_Adapter_Board_2Channel_uc444 pdf](https://www.uctronics.com/download/Amazon/B016601.pdf)
- [ArduCAM Multi_Adapter_Board_2Channel_uc444 Github](https://github.com/ArduCAM/RaspberryPi/tree/master/Multi_Camera_Adapter/Multi_Adapter_Board_2Channel_uc444)