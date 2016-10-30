#include "stdafx.h"
#include "Findface.h"
#include "cv.h"
#include "highgui.h"
#include "afxdialogex.h"
#include "BeautyTell.h"
#include "BeautyTellDlg.h"


void CBeautyTellDlg::FindFace()
{
	//����ָ��ͼ���ָ��
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

	//ѡ����Ҫ��λ
	CvHaarClassifierCascade* cascade = (CvHaarClassifierCascade*)cvLoad(
		"D:\\Microsoft Visual Studio 12.0\\Common7\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml",
		0, 0, 0);

	CvMemStorage* storage = cvCreateMemStorage(0);
	
	/*��ʼ���---ע�⣺
	scaleΪ���ʱ����С�������������ټ�������
	cascadeΪ��ⲿλ��ѧϰ�ļ�
	*/
	double scale = 1;

	static CvScalar colors[] = {
		{ { 0, 0, 255 } }, { { 0, 128, 255 } }, { { 0, 255, 255 } }, { { 0, 255, 0 } },
		{ { 255, 128, 0 } }, { { 255, 255, 0 } }, { { 255, 0, 0 } }, { { 255, 0, 255 } }
	};

	//�����Ҷ�ͼ���ſ���������ʶ��
	IplImage* gray = cvCreateImage(cvSize(img->width, img->height), 8, 1);

	//��Сͼ�񣬼������㴦����
	IplImage* small_img = cvCreateImage(
		cvSize(cvRound(img->width / scale), cvRound(img->height / scale)), 8, 1
		);

	cvCvtColor(img, gray, CV_BGR2GRAY);      //��imgת��Ϊ�Ҷ�ͼ����gray
	cvResize(gray, small_img, CV_INTER_LINEAR);    //��gray�޸Ĵ�С����small_img
	cvEqualizeHist(small_img, small_img);    //ʹ�Ҷ�ͼ��ֱ��ͼ���⻯

	//����Ƿ���ڣ�ע�⣺�����������ʾ�����������ߴ���������׼ȷ�ʣ����ķѸ���ʱ��
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

	//������ڣ��������о���
	for (int i = 0; i < (objects ? objects->total : 0); i++)
	{
		CvRect* r = (CvRect*)cvGetSeqElem(objects, i);
		cvRectangle(
			img,
			cvPoint(r->x, r->y),
			cvPoint(r->x + r->width, r->y + r->height),
			colors[i % 8],
			4   //������ϸ
			);
	}

	cvSaveImage("D://��Ƭ//FindFace.jpg", img);
	cvReleaseImage(&gray);
	cvReleaseImage(&small_img);
	cvReleaseImage(&img);
	return;
}

