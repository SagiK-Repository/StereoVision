문서정보 : 2022.08.25.~28. 작성, 작성자 [@SAgiKPJH](https://github.com/SAgiKPJH)

# 목차
1. [Image StereoVision in PC C++ & Python](https://github.com/SagiK-Repository/StereoVision/tree/main/2%2C%203.%20Image%20StereoVision%20in%20PC%20C%2B%2B%20%26%20Python#1-image-stereovision-in-pc-c--python)
2. [OpneCV](https://github.com/SagiK-Repository/StereoVision/tree/main/2%2C%203.%20Image%20StereoVision%20in%20PC%20C%2B%2B%20%26%20Python#2-opencv)
3. [StereoVision 이미지 획득](https://github.com/SagiK-Repository/StereoVision/tree/main/2%2C%203.%20Image%20StereoVision%20in%20PC%20C%2B%2B%20%26%20Python#3-stereovision-%EC%9D%B4%EB%AF%B8%EC%A7%80-%ED%9A%8D%EB%93%9D)
4. [StereoVision in PC C++](https://github.com/SagiK-Repository/StereoVision/tree/main/2%2C%203.%20Image%20StereoVision%20in%20PC%20C%2B%2B%20%26%20Python#4-stereovision-in-pc-c)
5. [StereoVision in PC Python](https://github.com/SagiK-Repository/StereoVision/tree/main/2%2C%203.%20Image%20StereoVision%20in%20PC%20C%2B%2B%20%26%20Python#5-stereovision-in-pc-python)
6. [Image StereoVision 결과](https://github.com/SagiK-Repository/StereoVision/tree/main/2%2C%203.%20Image%20StereoVision%20in%20PC%20C%2B%2B%20%26%20Python#6-image-stereovision-%EA%B2%B0%EA%B3%BC)

<br>

```mermaid
flowchart LR

subgraph G_1["1. Image StereoVision<br> in PC C++ & Python"]
A_1["PC C++ 환경"] ---> A_1_1["Visual Studio"] 
A_2["PC Python 환경"] ---> A_2_1["Anaconda - Jupyter"] 
end

subgraph G_2["2. OpenCV"]
A_1_1 ---> B_1["OpenCV <br> Visual Studio C++ 연동"]
A_2_1 ---> B_2["OpenCV <br> Python 연동"]
end

G_3{{"3. StreoImage 획득"}}
G_3 ---> D_1_1
G_3 ---> D_2_1

subgraph G_4["4. StreoVision in PC C++"]
B_1 ---> D_1_1["C++<br> StreoBM<br>StreoSGBM"] ---> D_1_3["C++<br> Census/Rank Transform"] ---> D_1_5["C++<br> SGM"]
end

subgraph G_5["5. StreoVision in PC Python"]
B_2 ---> D_2_1["Python<br> StreoBM<br>StreoSGBM"] --->  D_2_3["Python<br> Census Transform"] ---> D_2_4["Python<br> SGM"]
end

subgraph G_6["6. ImageStreoVision 결과"]
end

D_1_5 & D_2_4 ---> G_6

```

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
- [StreoVision Image](https://github.com/SagiK-Repository/StereoVision/tree/main/2%2C%203.%20Image%20StereoVision%20in%20PC%20C%2B%2B%20%26%20Python/OpenCV%20Stereo%20Vision%20C%2B%2B/image)



<br><br><br>

# 4. StereoVision in PC C++

- [2. OpenCV] 항목을 참고하여 Visual Studio에 OpenCV를 연동한다.
  - Visual Studio 시작 > `새 프로젝트 만들기` > "빈 프로젝트" > 프로젝트 명 지정 후 생성
  - 이후 OpenCV 항목을 참고
- Stereo Vision C++을 위한 과정은 다음과 같다.
  - 이미지 로딩 및 출력
  - sbm, sgbm
  - Census, Rank transform
  - Semi-Global-Matching, Patch-Match-Stereo
  - (HMI-SGM, Layered stereo, Belief prop, GC+occl)
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
(사진의 위에 5개는 StereoBM, 아래 5개는 StereoSGBM이다.)  
 
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
  //...//

		cv::Ptr<cv::StereoSGBM> stereo = cv::StereoSGBM::create(SGBMndisparities, SGBMblocksize);
  //...//
		stereo->compute(images[i], images[i + 1], StereoVision_Result_image);
		normalize(StereoVision_Result_image, StereoVision_Result_image, 0, 255, NORM_MINMAX, CV_8U);

  //...//
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


### ◆ Census Transform, Rank Transform

- 온라인상에서 Census Transform 프로그램 코드를 획득할 수 있다.
- 함수형식으로 개조하여 사용할 수 있도록 한다.
- 자세한 코드 내용은 Repository를 참고한다.
  ```cpp
  int max_disparity = 16 * 4;
	int win_size = 20;
	int tranwin_size = 2;
  // Census Transform stereo match
  StereoVision_Result_image = CTSM(images[i], images[i + 1], win_size, max_disparity, tranwin_size);
  //...//
  //Rank Transform Stereo Matching
  StereoVision_Result_image = RTSM(images[i], images[i + 1], win_size, max_disparity, tranwin_size);
  ```

<br>

#### ◆ Census Transform, Rank Transform 결과

<img src="https://user-images.githubusercontent.com/66783849/186896280-83ef1f51-e76b-4e46-8f51-860d7c6b6fcc.png"> (win_size = 20)  

<img src="https://user-images.githubusercontent.com/66783849/186897702-f4dfc2bb-135f-4454-8b2c-228e37989f51.png"> (위 : Census, 아래 : Rank ,win_size = 7)  

- win_size = 20
  - Census Transform : 3.3292s
  - Rank Transform : 2.5628s
- win_size = 7
  - Census Transform : 0.4008s
  - Rank Transform : 0.3266s



<br>


### ◆ Semi-Global Matching (SGM)

<img src="https://user-images.githubusercontent.com/66783849/186927592-f8792318-10e1-4262-8e79-8f7837e9ada6.png">

- [SGM](https://github.com/gishi523/semi-global-matching)을 토대로 작성하였다.
- Repository를 통해 그 파일위치를 확인할 수 있다.
- 결과 : 평균 0.1462s


<br><br>

## ◆ Stereo Vision C++ 종합 결과

  | 평균시간 | Fast
-- | -- | --
StereoBM | 0.004 |  
StereoSGBM | 0.075 |  
Census T | 3.3292 | 0.4008
Rank T | 2.5628 | 0.3266
Semi-Global M | 0.1462 |  


<br><br><br>

# 5. StereoVision in PC Python

- Jupyter 및 Colab을 통한 Python 코딩을 진행한다.
- Stereo Vision Python을 위한 과정은 다음과 같다.
  - 이미지 로딩 및 출력
  - sbm, sgbm
  - Census, Rank transform
  - Semi-Global-Matching, Patch-Match-Stereo
  - (HMI-SGM, Layered stereo, Belief prop, GC+occl)
  - 결과


<br>

### ◆ 이미지 로딩 및 출력

- 배열을 통해 OpenCV 이미지를 쉽게 출력할 수 있도록 구성한다.
  ```python
  image_name = ["img/ambush_5_L.jpg",
  "img/ambush_5_R.jpg",
  "img/arc_L.jpg",
  "img/arc_R.jpg",
  "img/bike_L.png",
  "img/bike_R.png",
  "img/toy_L.png",
  "img/toy_R.png",
  "img/toys_L.png",
  "img/toys_R.png"]
  print(image_name[0])
  print(image_name[7])

  img = []
  for i in image_name:
      img.append(cv2.imread(i,0))

  cv2.imshow("TEST",img[0])
  cv2.waitKey(0)
  cv2.destroyAllWindows()
  ```

<br>

### ◆ StereoBM, StereoSGBM, Census Transform, Semi-Global-Matching

- 이미지만 입력하면 쉽게 출력결과가 나올 수 있도록 함수화하여 구성한다.
  ```python
  def StereoBM(imgL,imgR, nD = 16, bS = 15) :
      stereo = cv2.StereoBM_create(nD, bS)
      stereo.setDisp12MaxDiff(25)
      stereo.setUniquenessRatio(15)
      start = time.time()
      disparity = stereo.compute(imgL,imgR)
      end = time.time()
      print(f"{end - start:.5f} sec")
      plt.imshow(disparity,'gray')
      plt.colorbar()
      plt.show()
  
  def StereoSGBM(imgL,imgR, nD = 16, bS = 15, win_size=3) :
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
      print(f"{end - start:.5f} sec")
      plt.imshow(disparity,'gray')
      plt.colorbar()
      plt.show()
  
  def Census_Transform (left, right, window_size = 5, ndisp = 7):
      ct_left = norm(transform(left, window_size)) ## Census Transform
      ct_right = norm(transform(right, window_size))
  
      ct_costs = [] ## Result
      for exponent in range(0, 6):
          import math
          disparity = int(ndisp / math.pow(2, exponent))
          #print(math.pow(2, exponent), disparity)
          ct_costs.append(norm(cost(left, right, window_size, disparity)))
      #plt.imshow(ct_left, 'gray')
      plt.imshow(ct_costs[0], 'gray') ## 'costs'
      plt.colorbar()
      plt.show()
  
  def SGM(left, right, papram):
      paths = Paths()
      left_cost_volume, right_cost_volume = compute_costs(left, right, parameters)
  
      print('\nStarting left aggregation computation...')
      left_aggregation_volume = aggregate_costs(left_cost_volume, parameters, paths)
      print('\nStarting right aggregation computation...')
      right_aggregation_volume = aggregate_costs(right_cost_volume, parameters, paths)
  
      print('\nSelecting best disparities...')
      left_disparity_map = np.uint8(normalize(select_disparity(left_aggregation_volume), parameters))
      right_disparity_map = np.uint8(normalize(select_disparity(right_aggregation_volume), parameters))
  
      print('\nApplying median filter...')
      left_disparity_map = cv2.medianBlur(left_disparity_map, parameters.bsize[0])
      
      plt.imshow(left_disparity_map, 'gray') ## 'costs'
      plt.colorbar()
      plt.show()
  
  ```
- 다음과 같이 활용한다.
  ```python
  for i in range(0,10,2) :
      StereoBM(img[i], img[i+1], 16*4, 17)
  
  for i in range(0,10,2) :
      StereoSGBM(img[i], img[i+1], 16*4, 17)    
  
  for i in range(0,10,2) :
      start = time.time()
      Census_Transform(img[i], img[i+1], 17, 16*4)
      end = time.time()
      print(f"{end - start:.5f} sec")
  
  parameters = Parameters(max_disparity=64, P1=10, P2=120, csize=(7, 7), bsize=(3, 3))
  for i in range(0,10,2) :
      start = time.time()
      SGM(img[i], img[i+1], parameters)
      end = time.time()
      print(f"{end - start:.5f} sec")
  ```


<br>

#### ◆ StereoBM, StereoSGBM, Census Transform, Semi-Global-Matching 결과

<img src="https://user-images.githubusercontent.com/66783849/187015786-5f5a30fd-8b72-40fb-ba59-fea6b534ef21.png">

- StereoBM : 0.0074s
- StereoSGBM : 0.033s
- Census Transform : 0.67s
- Semi-Global-Matching : 133s


<br><br><br>

# 6. Image StereoVision 결과

  | C++ | python
-- | -- | --
StereoBM | 0.004s | 0.0074s
StereoSGBM | 0.075s | 0.033s
Census Transform | 3.3292s | 0.67s
Semi-Global-Matching | 0.1462s | 133s


<br><br><br>


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
  - https://hangyinuml.wordpress.com/2012/09/08/census-transform-c-implementation/
- Stereo Vision Matching
  - [Semi-Global-Matching](https://github.com/ethan-li-coding/SemiGlobalMatching)
  - [Patch-Match-Stereo](https://github.com/ethan-li-coding/PatchMatchStereo)
  - [SGM](https://github.com/gishi523/semi-global-matching)
  - [Semi-Global-Matching, Slanted Plane Smoothing (SPS)](https://github.com/WanchaoYao/SGM)
  - [Semi-Global Matching on the GPU](https://github.com/dhernandez0/sgm)
- Stereo Vision Python 코드
  - http://daplus.net/python-opencv-%EB%B3%B4%EC%A0%95%EB%90%98%EC%A7%80-%EC%95%8A%EC%9D%80-%EC%8A%A4%ED%85%8C%EB%A0%88%EC%98%A4-%EC%8B%9C%EC%8A%A4%ED%85%9C%EC%9D%98-%EA%B9%8A%EC%9D%B4-%EB%A7%B5/
  - https://leechamin.tistory.com/362
  - https://learnopencv.com/depth-perception-using-stereo-camera-python-c/
  - (Census Transform - Python) https://stackoverflow.com/questions/38265364/census-transform-in-python-opencv
