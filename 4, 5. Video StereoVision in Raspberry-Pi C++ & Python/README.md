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

- 라즈베리 파이


<br><br><br>


## 참고
