문서정보 : 2022.08.25.~ 작성, 작성자 [@SAgiKPJH](https://github.com/SAgiKPJH)

# 목차
1. [Image StereoVision in PC C++ & Python]
2. [OpneCV]
3. [StereoVision 이미지 획득]
4. [StereoVision in PC C++]
4. [StereoVision in PC Python]
5. [Image StereoVision 결과]

<br><br><br>

# 1. Image StereoVision in PC C++ & Python

Left, Right Image를 통해 C++ & Python 각각의 언어를 활용하여 PC에서 StereoVision을 진행하는 것이 목표이다.  
이를 위한 PC 환경은 다음과 같다.  
- PC C++ 환경 : Windows10 - Visual Studio
- PC Python 환경 : Windows10 - Anaconda3 - Jupyter (Python 3.8.8v), Google Colab (Python 3.7.13v)
- 두 환경 공통적으로 OpenCV 라이브러리를 활용한다.


<br><br><br>

# 2. OpenCV

<img src="https://user-images.githubusercontent.com/66783849/186481810-4badd25d-bb67-4d26-b6ef-c74ecba02e5c.png" width="19%">

- OpenCV(Open Source Computer Vision)은 실시간 컴퓨터 비전을 목적으로한 프로그래밍 라이브러리이다.
- C++와 Python에서 연동 사용 가능하다.
- OpenCV 4.5.3 버전 사용

<br>

### ◆ Visual Studio C++에서의 연동 방법

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



<br><br><br>

# 3. StereoVision 이미지 획득

<img src="https://user-images.githubusercontent.com/66783849/186562543-390c72d1-c068-490f-b3cc-51cb47d8441f.png" width="69%">

- Stereo Vision을 위한 이미지 샘플을 획득한다.




<br><br><br>

# 4. StereoVision in PC C++

- [2. OpenCV] 항목을 참고하여 Visual Studio에 OpenCV를 연동한다.
  - Visual Studio 시작 > `새 프로젝트 만들기` > "빈 프로젝트" > 프로젝트 명 지정 후 생성
  - 이후 OpenCV 항목을 참고
- Stereo Vision을 위한 과정은 다음과 같다.
  - 이미지 로딩 및 출력
  - sbm, sgbm
  - Census, HMI-SGM
  - Layered stereo, Belief prop, GC+occl
  - 결과

<br>

### ◆ 이미지 로딩 및 출력

- OpenCV를 통해 이미지를 쉽게 로딩 및 출력할 수 있도록 구성한다.
  ```cpp
  vector<string> image_names;
	image_names.push_back("../image/ambush_5_L.jpg");
	image_names.push_back("../image/ambush_5_R.jpg");
	image_names.push_back("../image/arc_L.jpg");
	image_names.push_back("../image/arc_R.jpg");
	image_names.push_back("../image/bike_L.png");
	image_names.push_back("../image/bike_R.png");
	image_names.push_back("../image/toy_L.png");
	image_names.push_back("../image/toy_R.png");
	image_names.push_back("../image/toys_L.png");
	image_names.push_back("../image/toys_R.png");

	Mat images[10];
	for (int i = 0; i < image_names.size(); i++) {
		images[i] = imread(image_names[i], 0);
		CV_Assert(images[i].data);
		resize(images[i], images[i], Size(450, 375));
	}
	cout << " 이미지 " << image_names.size() << " 개 로딩 성공!" << endl << endl;
  ```

<br>

### ◆ StereoBM, StereoSGBM

<img src="https://user-images.githubusercontent.com/66783849/186613743-e4d71935-a849-457a-8837-a199ebd1e031.png" width="69%">

- 사진의 위에 5개는 StereoBM, 아래 5개는 StereoSGBM이다.
- StereoBM과 StereoSGBM은 각각 OpenCV에서 제공하는 전역 정합(Global Matching) 방법이랑, 지역 정합(Local Matching) 방법이다.
- StereoBM 기능을 활용한 StereoVision 코드를 구성한다.
  ```cpp
  int BMndisparities = 16 * 4;
  int BMblocksize = 17; //홀수
	int BMdisp12MaxDiff = 25;
	int BMuniquenessRatio = 0;
	int BMtextureThreshold = 25;
  for (int i = a; i < image_names.size(); i += 2) {

		cout << image_names[i] << " Streovision BM" << endl;

		clock_t startTime, endTime; endTime = clock();

		cv::Ptr<cv::StereoBM> stereo = cv::StereoBM::create(BMndisparities, BMblocksize);
    stereo->setNumDisparities(BMndisparities);
		stereo->setBlockSize(BMblocksize);
		stereo->setPreFilterType(1);
		stereo->setPreFilterSize(1 * 2 + 5);
		stereo->setPreFilterCap(31);
		stereo->setTextureThreshold(BMtextureThreshold);
		stereo->setUniquenessRatio(0);
		stereo->setSpeckleRange(0);
		stereo->setSpeckleWindowSize(0 * 2);
		stereo->setDisp12MaxDiff(BMdisp12MaxDiff); // 틈
		stereo->setMinDisparity(BMuniquenessRatio);

		startTime = clock();
		stereo->compute(images[i], images[i + 1], StereoVision_Result_image);
		normalize(StereoVision_Result_image, StereoVision_Result_image, 0, 255, NORM_MINMAX, CV_8U);


		printf("-----%fs----- \n\n", (double)(clock() - startTime) / CLOCKS_PER_SEC);


		imshow("Image_L", images[i]); imshow("Image_R", images[i + 1]);
		imshow("Result", StereoVision_Result_image); waitKey(0);

		imwrite("IMG_StereoVision_BM_Result" + to_string(i) + ".png", StereoVision_Result_image);

	}
  ```
- 마찬가지로 StereoSGBM도 마찬가지이다.
  ```cpp
  int SGBMndisparities = 16 * 4;
	int SGBMblocksize = 17;
	int SGBMdisp12MaxDiff = 25;
	int SGBMuniquenessRatio = 0;
  for (int i = a; i < image_names.size(); i += 2) {

		cout << image_names[i] << " Streovision SGBM" << endl;

		clock_t startTime, endTime; endTime = clock();

		cv::Ptr<cv::StereoSGBM> stereo = cv::StereoSGBM::create(SGBMndisparities, SGBMblocksize);
		stereo->setNumDisparities(SGBMndisparities);
		stereo->setBlockSize(SGBMblocksize);
		stereo->setPreFilterCap(31);
		stereo->setUniquenessRatio(0);
		stereo->setSpeckleRange(0);
		stereo->setSpeckleWindowSize(0 * 2);
		stereo->setDisp12MaxDiff(SGBMdisp12MaxDiff); // 틈
		stereo->setMinDisparity(SGBMuniquenessRatio);

		startTime = clock();
		stereo->compute(images[i], images[i + 1], StereoVision_Result_image);
		normalize(StereoVision_Result_image, StereoVision_Result_image, 0, 255, NORM_MINMAX, CV_8U);

		printf("-----%fs----- \n\n", (double)(clock() - startTime) / CLOCKS_PER_SEC);

		//imshow("Image_L", images[i]); imshow("Image_R", images[i + 1]);
		imshow("Result", StereoVision_Result_image); waitKey(0);

		imwrite("IMG_StereoVision_SGBM_Result" + to_string(i) + ".png", StereoVision_Result_image);

	}
  ```
- OpenCV의 Track 기능을 활용하여 실시간으로 요소를 변경하면서 확인할 수 있도록 한다.  
  <img src="https://user-images.githubusercontent.com/66783849/186610378-fa867f8c-787a-4017-a412-6495bbf39549.png" width="69%">  
  ```cpp
  cv::Ptr<cv::StereoBM> stereot0 = cv::StereoBM::create();
  
  int numDisparities = 8;
  int blockSize = 5;
  int preFilterType = 1;
  int preFilterSize = 1;
  int preFilterCap = 31;
  int minDisparity = 0;
  int textureThreshold = 10;
  int uniquenessRatio = 15;
  int speckleRange = 0;
  int speckleWindowSize = 0;
  int disp12MaxDiff = -1;

  static void on_trackbar1(int, void*) {
  	stereot0->setNumDisparities(numDisparities * 16);
  	stereot1->setNumDisparities(numDisparities * 16);
	  numDisparities = numDisparities * 16;
  }
  
  static void on_trackbar2(int, void*) {
	  stereot0->setBlockSize(blockSize * 2 + 5);
	  stereot1->setBlockSize(blockSize * 2 + 5);
	  blockSize = blockSize * 2 + 5;
  }
  //...//
  static void on_trackbar11(int, void*) {
  	stereot0->setMinDisparity(minDisparity);
	  stereot1->setMinDisparity(minDisparity);
  }

  //...//
  // main문 내부//
  //...//

  cout << "ESC Key to Next" << endl;

	Mat StereoVision_Result_image;

	// Creating a named window to be linked to the trackbars
	namedWindow("disparity", WINDOW_NORMAL);
	resizeWindow("disparity", 600, 600);

	// Creating trackbars to dynamically update the StereoBM parameters
	createTrackbar("numDisparities", "disparity", &numDisparities, 18, on_trackbar1);
	createTrackbar("blockSize", "disparity", &blockSize, 50, on_trackbar2);
	createTrackbar("preFilterType", "disparity", &preFilterType, 1, on_trackbar3);
	createTrackbar("preFilterSize", "disparity", &preFilterSize, 25, on_trackbar4);
	createTrackbar("preFilterCap", "disparity", &preFilterCap, 62, on_trackbar5);
	createTrackbar("textureThreshold", "disparity", &textureThreshold, 100, on_trackbar6);
	createTrackbar("uniquenessRatio", "disparity", &uniquenessRatio, 100, on_trackbar7); //0
	createTrackbar("speckleRange", "disparity", &speckleRange, 100, on_trackbar8);
	createTrackbar("speckleWindowSize", "disparity", &speckleWindowSize, 25, on_trackbar9);
	createTrackbar("disp12MaxDiff", "disparity", &disp12MaxDiff, 25, on_trackbar10);
	createTrackbar("minDisparity", "disparity", &minDisparity, 25, on_trackbar11);

	int n = 0;
	while (1) {

		//stereot0->compute(images[n], images[n + 1], StereoVision_Result_image);
		stereot1->compute(images[n], images[n + 1], StereoVision_Result_image);
		normalize(StereoVision_Result_image, StereoVision_Result_image, 0, 255, NORM_MINMAX, CV_8U);
	
  	imshow("disparity", StereoVision_Result_image);
	
  	if (waitKey(10) == 27) break; //esc
  }
  ```

<br>

#### ◆ StereoBM, StereoSGBM 결과

<img src="https://user-images.githubusercontent.com/66783849/186617499-d3d0f7ab-2da8-47c0-b939-cb7a7288bfcd.png">

 - 이미지크기 450*375를 기준으로,  
   StereoBM은 평균 4ms,  
   StereoSGBM은 평균 30.6ms가 나왔다.  
 - 이미지크기 1024*1454를 기준으로,  
   StereoBM은 75ms,  
   StereoSGBM은 1323ms가 나왔다.  


<br>


### ◆ Census Transform, HMI-SGM (  - Layered stereo, Belief prop, GC+occl)

<br><br><br>

# 4. StereoVision in PC Python



## 참고

- OpenCV
  - https://ko.wikipedia.org/wiki/OpenCV
- Stereo Vision
  - http://mccormickml.com/2014/01/10/stereo-vision-tutorial-part-i/
- Stereo Matching 방법
  - https://m.blog.naver.com/PostView.naver?blogId=dldlsrb45&logNo=220879295400&targetKeyword=&targetRecommendationCode=1
- Steroe Vision 비용 방법 비교 논문
  - Evaluation of Cost Functions for Stereo Matching
  - A Taxonomy and Evaluation of Dense Two-Frame Stereo Correspondence Algorithms
- Stereo Vision 코드
  - https://adioshun.gitbooks.io/gitbook_from_github/content/Image_Process_ch15.html
  - https://eehoeskrap.tistory.com/103
- StereoBM 코드
  - https://learnopencv.com/depth-perception-using-stereo-camera-python-c/
  - https://docs.opencv.org/3.1.0/d3/d14/tutorial_ximgproc_disparity_filtering.html
  - https://makepluscode.tistory.com/105
  - https://leechamin.tistory.com/362
- Stereo Vision Image DataSource 제공
  - https://vision.middlebury.edu/stereo/data/
- Stereo Vision Census Transform
  - https://docs.opencv.org/4.x/d2/d7f/namespacecv_1_1stereo.html