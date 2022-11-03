#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <time.h>
#include <opencv2/gapi/cpu/stereo.hpp>
#include "ValueI.h"
#include "OpenCV.h"
#include "SGM.h"

using namespace cv;  // cv 안써도 됨
using namespace std; //std 안써도 됨

#pragma warning (disable:4819) //경고 메시지 숨기기
#pragma warning (disable:4996) //경고 메시지 숨기기

//Trackbar
cv::Ptr<cv::StereoBM> stereot0 = cv::StereoBM::create();
cv::Ptr<cv::StereoSGBM> stereot1 = cv::StereoSGBM::create();

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

static void on_trackbar1(int, void*)
{
	stereot0->setNumDisparities(numDisparities * 16);
	stereot1->setNumDisparities(numDisparities * 16);
	numDisparities = numDisparities * 16;
}

static void on_trackbar2(int, void*)
{
	stereot0->setBlockSize(blockSize * 2 + 5);
	stereot1->setBlockSize(blockSize * 2 + 5);
	blockSize = blockSize * 2 + 5;
}

static void on_trackbar3(int, void*)
{
	stereot0->setPreFilterType(preFilterType);
	//stereot1->setPreFilterType(preFilterType);
}

static void on_trackbar4(int, void*)
{
	stereot0->setPreFilterSize(preFilterSize * 2 + 5);
	//stereot1->setPreFilterSize(preFilterSize * 2 + 5);
	preFilterSize = preFilterSize * 2 + 5;
}

static void on_trackbar5(int, void*)
{
	stereot0->setPreFilterCap(preFilterCap);
	stereot1->setPreFilterCap(preFilterCap);
}

static void on_trackbar6(int, void*)
{
	stereot0->setTextureThreshold(textureThreshold);
	//stereot1->setTextureThreshold(textureThreshold);
}

static void on_trackbar7(int, void*)
{
	stereot0->setUniquenessRatio(uniquenessRatio);
	stereot1->setUniquenessRatio(uniquenessRatio);
}

static void on_trackbar8(int, void*)
{
	stereot0->setSpeckleRange(speckleRange);
	stereot1->setSpeckleRange(speckleRange);
}

static void on_trackbar9(int, void*)
{
	stereot0->setSpeckleWindowSize(speckleWindowSize * 2);
	stereot1->setSpeckleWindowSize(speckleWindowSize * 2);
	speckleWindowSize = speckleWindowSize * 2;
}

static void on_trackbar10(int, void*)
{
	stereot0->setDisp12MaxDiff(disp12MaxDiff);
	stereot1->setDisp12MaxDiff(disp12MaxDiff);
}

static void on_trackbar11(int, void*)
{
	stereot0->setMinDisparity(minDisparity);
	stereot1->setMinDisparity(minDisparity);
}


int main() {

	//Image Load
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
	image_names.push_back("../image/LL.png");
	image_names.push_back("../image/RR.png");

	Mat images[12];
	for (int i = 0; i < image_names.size(); i++) {
		images[i] = imread(image_names[i], 0);
		CV_Assert(images[i].data);
		resize(images[i], images[i], Size(450, 375));
	}
	cout << " 이미지 " << image_names.size() << " 개 로딩 성공!" << endl << endl;

	// Trackbar (Esc Key Next)
	if (1) { 
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

		int n = 10;
		while (1) {

			//stereot0->compute(images[n], images[n + 1], StereoVision_Result_image);
			stereot1->compute(images[n], images[n + 1], StereoVision_Result_image);
			normalize(StereoVision_Result_image, StereoVision_Result_image, 0, 255, NORM_MINMAX, CV_8U);

			imshow("disparity", StereoVision_Result_image);

			if (waitKey(100) == 27) break; //esc key
		}

	}

	// StereoBM
	if (1) {
		int BMndisparities = 16 * 4;
		int BMblocksize = 17;
		int BMdisp12MaxDiff = 25; // 큰 틈 사이 제거
		int BMuniquenessRatio = 0; // 작은 틈 사이 제거
		int BMtextureThreshold = 25; // 배경 제거

		int a = 0; Mat StereoVision_Result_image;

		for (int i = a; i < image_names.size(); i += 2) {

			//Size ImgSize = images[i].size();

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


			//imshow("Image_L", images[i]); imshow("Image_R", images[i + 1]);
			imshow("Result", StereoVision_Result_image); waitKey(0);

			imwrite("IMG_StereoVision_BM_Result" + to_string(i) + ".png", StereoVision_Result_image);

		}

	}
	
	// StereoSGBM
	if (1) {
		int SGBMndisparities = 16 * 4;
		int SGBMblocksize = 17;
		int SGBMdisp12MaxDiff = 25; // 큰 틈 사이 제거
		int SGBMuniquenessRatio = 0; // 작은 틈 사이 제거

		int a = 0; Mat StereoVision_Result_image;

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

	}

	// Census Transform
	if (1) {

		int max_disparity = 16 * 4;
		int win_size = 7;
		int tranwin_size = 7;
		int a = 0; Mat StereoVision_Result_image;

		for (int i = a; i < image_names.size(); i += 2) {

			cout << image_names[i] << " Streovision Census Transform" << endl;

			clock_t startTime, endTime; endTime = clock();

			startTime = clock();

			StereoVision_Result_image = CTSM(images[i], images[i + 1], win_size, max_disparity, tranwin_size);

			printf("-----%fs----- \n\n", (double)(clock() - startTime) / CLOCKS_PER_SEC);

			//imshow("Image_L", images[i]); imshow("Image_R", images[i + 1]);
			imshow("Result", StereoVision_Result_image); waitKey(0);

			imwrite("IMG_StereoVision_CTSM_Result_" + to_string(i) + ".png", StereoVision_Result_image);

		}

	}

	// Rank Transform
	if (1) {

		int max_disparity = 16 * 4;
		int win_size = 7;
		int tranwin_size = 2;
		int a = 0; Mat StereoVision_Result_image;

		for (int i = a; i < image_names.size(); i += 2) {

			cout << image_names[i] << " Streovision Rank Transform" << endl;

			clock_t startTime, endTime; endTime = clock();

			startTime = clock();

			StereoVision_Result_image = RTSM(images[i], images[i + 1], win_size, max_disparity, tranwin_size);

			printf("-----%fs----- \n\n", (double)(clock() - startTime) / CLOCKS_PER_SEC);

			//imshow("Image_L", images[i]); imshow("Image_R", images[i + 1]);
			imshow("Result", StereoVision_Result_image); waitKey(0);

			imwrite("IMG_StereoVision_RTSM_Result_" + to_string(i) + ".png", StereoVision_Result_image);

		}

	}

	// Semi-Global Matching
	if (1) {

		int a = 0;

		for (int i = a; i < image_names.size(); i += 2) {

			cout << image_names[i] << " Streovision Semi-Global Matching" << endl;

			clock_t startTime, endTime; endTime = clock();

			startTime = clock();


			SGM::Parameters param;
			SGM sgm(param);

			Mat D1, D2;
			sgm.compute(images[i], images[i+1], D1, D2);
			normalize(D1, D1, 0, 255, NORM_MINMAX, CV_8UC1);

			printf("-----%fs----- \n\n", (double)(clock() - startTime) / CLOCKS_PER_SEC);

			//imshow("Image_L", images[i]); imshow("Image_R", images[i + 1]);
			imshow("Result", D1); waitKey(0);

			imwrite("IMG_StereoVision_SGM_Result_" + to_string(i) + ".png", D1);

		}
	}


	waitKey();

	return 0;

}


