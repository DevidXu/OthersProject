#include "stdafx.h"
#include "Findface.h"
#include "cv.h"
#include "highgui.h"
#include "afxdialogex.h"
#include "BeautyTell.h"
#include "BeautyTellDlg.h"


void CBeautyTellDlg::FindFace()
{
	//创建指向图像的指针
	IplImage* img;
	const char* tmp = NULL;
	std::string tempname = (LPCSTR)CStringA(FilePath);
	tmp = tempname.c_str();
	img = cvLoadImage(tmp);

	if (img == NULL)
	{
		cvReleaseImage(&img);
		return;
	}

	//选择需要部位
	CvHaarClassifierCascade* cascade = (CvHaarClassifierCascade*)cvLoad(
		"D:\\Microsoft Visual Studio 12.0\\Common7\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml",
		0, 0, 0);

	CvMemStorage* storage = cvCreateMemStorage(0);
	
	/*开始检测---注解：
	scale为检测时的缩小比例，用来减少计算量；
	cascade为检测部位的学习文件
	*/
	double scale = 1;

	static CvScalar colors[] = {
		{ { 0, 0, 255 } }, { { 0, 128, 255 } }, { { 0, 255, 255 } }, { { 0, 255, 0 } },
		{ { 255, 128, 0 } }, { { 255, 255, 0 } }, { { 255, 0, 0 } }, { { 255, 0, 255 } }
	};

	//创建灰度图，才可用于脸部识别
	IplImage* gray = cvCreateImage(cvSize(img->width, img->height), 8, 1);

	//缩小图像，减少运算处理量
	IplImage* small_img = cvCreateImage(
		cvSize(cvRound(img->width / scale), cvRound(img->height / scale)), 8, 1
		);

	cvCvtColor(img, gray, CV_BGR2GRAY);      //将img转化为灰度图存入gray
	cvResize(gray, small_img, CV_INTER_LINEAR);    //将gray修改大小存入small_img
	cvEqualizeHist(small_img, small_img);    //使灰度图象直方图均衡化

	//检测是否存在：注解：第五个参数表示检验次数，提高次数将增加准确率，并耗费更多时间
	cvClearMemStorage(storage);
	objects = cvHaarDetectObjects(
		small_img,
		cascade,
		storage,
		1.1,
		2,
		0,
		cvSize(30, 30)
		);

	//如果存在，画出所有矩形
	for (int i = 0; i < (objects ? objects->total : 0); i++)
	{
		CvRect* r = (CvRect*)cvGetSeqElem(objects, i);
		cvRectangle(
			img,
			cvPoint(r->x, r->y),
			cvPoint(r->x + r->width, r->y + r->height),
			colors[i % 8],
			4   //线条粗细
			);
	}

	cvSaveImage("D://照片//FindFace.jpg", img);
	cvReleaseImage(&gray);
	cvReleaseImage(&small_img);
	cvReleaseImage(&img);
	return;
}

