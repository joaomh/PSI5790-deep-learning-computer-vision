//inv_ocv.cpp - usando template
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{ Mat_<uchar> a;
 a=imread("mickey.bmp",0);
 for (int l=0; l<a.rows; l++)
 for (int c=0; c<a.cols; c++)
 if (a(l,c)!=a(l,c+1) && a(l,c)!=a(l,c-1)){
   a(l,c) = a(l,c-1);
   }
 imwrite("final_result.pgm",a);
}