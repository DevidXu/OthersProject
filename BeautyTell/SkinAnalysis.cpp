#include "stdafx.h"
#include "cv.h"
#include "highgui.h"
#include "afxdialogex.h"
#include "BeautyTell.h"
#include "BeautyTellDlg.h"
#include "SkinAnalysis.h"


void CBeautyTellDlg::SkinAnalysis()
{
	//����ָ��ͼ���ָ��
	IplImage* img;
	const char* tmp = NULL;
	std::string tempname = (LPCSTR)CStringA(FilePath);
	tmp = tempname.c_str();
	img = cvLoadImage(tmp);

	//�洢��������ֵ��������ɫ�Ķ�Ӧ��ֵ
	ColorPoint p;

	//��ÿ�ż���������м���
	for (int i = 0; i < (objects ? objects->total : 0); i++)
	{
		CvRect* r = (CvRect*)cvGetSeqElem(objects, i);

		//�ɼ���ͷ��������Ϊ��Ȥ����
		cvSetImageROI(img,
			cvRect((int)r->x + r->width * 11 / 24,
			(int)r->y + r->height * 3 / 20,
			(int)r->width / 10,
			(int)r->height / 10));        
		p = SkinPoint(img);      //���ؾ�ֵ����
		face[i].Brow = (int)(abs(p.AverageRed - 235)*0.391 + abs(p.AverageGreen - 199)*0.363
			+ abs(p.AverageBlue - 175)*0.256);     //��ͳ�Ʊ����ó����

		//�ɼ��Ǽ��������Ϊ��Ȥ����
		cvSetImageROI(img,
			cvRect((int)r->x + r->width * 7 / 25,
			(int)r->y + r->height * 8 / 15,
			(int)r->width / 30,
			(int)r->height / 30));        //�ɼ��Ǽ��������Ϊ��Ȥ����
		p = SkinPoint(img);
		face[i].NoseL = (int)(abs(p.AverageRed - 222)*0.319 + abs(p.AverageGreen - 172)*0.381
			+ abs(p.AverageBlue - 147)*0.301);

		//�ɼ��Ǽ��Ҳ�Ϊ��Ȥ����
		cvSetImageROI(img,
			cvRect((int)r->x + r->width * 17 / 25,
			(int)r->y + r->height * 8 / 15,
			(int)r->width / 30,
			(int)r->height / 30));        //�ɼ���ͷ��������Ϊ��Ȥ����
		p = SkinPoint(img);
		face[i].NoseR = (int)(abs(p.AverageRed - 229)*0.407 + abs(p.AverageGreen - 183)*0.324
			+ abs(p.AverageBlue - 161)*0.269);
	}

	//����face[i]�Ķ�Ӧ����
	for (int i = 0; i < (objects ? objects->total : 0); i++)
		face[i].SkinPoint = (int)(face[i].Brow*0.6 + face[i].NoseL*0.2 + face[i].NoseR*0.2);
	
	cvResetImageROI(img);
	cvReleaseImage(&img);
	return;
}

ColorPoint SkinPoint(IplImage* img)
{
	CvScalar s;
	double SumRed = 0, SumBlue = 0, SumGreen = 0;   //��ʼ�ռ�����
	for (int y = 0; y < img->roi->height; y++)
	{
		for (int x = 0; x < img->roi->width; x++)
		{
			s = cvGet2D(img, y, x);
			SumRed += s.val[2];
			SumGreen += s.val[1];
			SumBlue += s.val[0];
		}
	}
	ColorPoint p;
	p.AverageRed = (int)(SumRed / (img->roi->height*img->roi->width));
	p.AverageGreen = (int)(SumGreen / (img->roi->height*img->roi->width));
	p.AverageBlue = (int)(SumBlue / (img->roi->height*img->roi->width));
	return p;
}