#include "cv.h"
#include "highgui.h"
#include "afxdialogex.h"

struct FACE
{
	int Brow;
	int NoseL;
	int NoseR;
	int SkinPoint;
};

struct ColorPoint
{
	int AverageRed;
	int AverageGreen;
	int AverageBlue;
};

ColorPoint SkinPoint(IplImage*);