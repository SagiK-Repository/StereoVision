문서정보 : 2022.08.25.~ 작성, 작성자 [@SAgiKPJH](https://github.com/SAgiKPJH)

# 목차
1. [Image StereoVision in PC C++ & Python]
2. [OpneCV]
3. [StereoVision 이미지 획득]
4. [StereoVision in PC C++]
4. [StereoVision in PC Python]
5. [Image StereoVision 결과]

<br>

# 1. Image StereoVision in PC C++ & Python

Left, Right Image를 통해 C++ & Python 각각의 언어를 활용하여 PC에서 StereoVision을 진행하는 것이 목표이다.  
이를 위한 PC 환경은 다음과 같다.  
- PC C++ 환경 : Windows10 - Visual Studio 2022
- PC Python 환경 : Windows10 - Anaconda3 - Jupyter (Python 3.8.8v), Google Colab (Python 3.7.13v)
- 두 환경 공통적으로 OpenCV 라이브러리를 활용한다.


<br>

# 2. OpenCV

<img src="https://user-images.githubusercontent.com/66783849/186481810-4badd25d-bb67-4d26-b6ef-c74ecba02e5c.png" width="19%">

- OpenCV(Open Source Computer Vision)은 실시간 컴퓨터 비전을 목적으로한 프로그래밍 라이브러리이다.
- C++와 Python에서 연동 사용 가능하다.
- OpenCV 4.5.3 버전 사용

<br>

### ◆ Visual Studio 2022 C++에서의 연동 방법

1. OpenCV 설치 후 MFC 빈프로젝트 제작 (글쓴이의 경우 OpenCV 4.5.3v 사용)
2. x64 Debug 또는 Release 모드, 두 가지 각각 opencv_world453d.lib 또는 opencv_world453.lib 다르게 속성 설정 진행한다.
3. 프로젝트 속성 설정 (<kbd>Alt</kbd>+<kbd>Enter</kbd>)  
   프로젝트 속성 | 기입내용
   :--: | :--
   구성관리자 | 64비트를 선택한다
   VC++->포함 디렉터리 | C:\opencv453\build\include
   라이브러리 디렉터리 | C:\opencv453\build\x64\vc15\lib
   링커->입력->추가종속성 | opencv_world453d.lib or opencv_world453.lib
   디버깅->환경 | PATH=C:\opencv453\build\x64\vc15\bin;%PATH%
4. 아래 내용을 cpp 코딩 또는 헤더에 넣고 디버깅되면 사용준비 끝이다.  
   ```cpp
   #include <opencv2/opencv.hpp>
   using namespace cv; 
   using namespace std;
   ```

<br>

### ◆ Python에서의 연동 방법

- 기본적으로 Anaconda3에는 OpenCV가 깔려있다. (글쓴이의 경우 Jupyter - OpenCV 4.5.4v, Colab - OpenCV 4.6.0v 사용)
- OpenCV 버전 확인은 다음과 같이 한다. `print(cv2.__version__)`
- OpenCV를 설치할 경우 다음과 같이 cmd에 입력한다. `python -m pip install opencv-python` (Jupyter, Colab에 입력할 경우 맨 앞에 '!'를 붙인다.)
- 아래 코드를 작성하여 정상 작동하여 사용준비를 마무리한다.
  ```python
  import cv2
  
  image = cv2.imread("1.jpg",cv2.IMREAD_COLOR)
  cv2.imshow("TEST",image)
  cv2.waitKey(0)
  cv2.destroyAllWindows()
  ```



<br>

# 3. StereoVision 이미지 획득

- Stereo Vision을 위한 이미지 샘플을 획득한다.



## 참고

- OpenCV
  - https://ko.wikipedia.org/wiki/OpenCV



- Stereo Matching 방법
  - https://m.blog.naver.com/PostView.naver?blogId=dldlsrb45&logNo=220879295400&targetKeyword=&targetRecommendationCode=1
- Steroe Vision 비용 방법 비교 논문
  - Evaluation of Cost Functions for Stereo Matching
  - A Taxonomy and Evaluation of Dense Two-Frame Stereo Correspondence Algorithms
- Stereo Vision 코드
  - https://adioshun.gitbooks.io/gitbook_from_github/content/Image_Process_ch15.html
  - https://eehoeskrap.tistory.com/103
- Steteo Vision Image DataSource 제공
  - https://vision.middlebury.edu/stereo/data/
  - 