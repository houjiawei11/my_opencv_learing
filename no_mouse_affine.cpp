#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

Rect select;
int LB_FLAG = 0;

Mat src_img;

void onMouse(int event, int x, int y, int, void*)
{
    if(event==CV_EVENT_LBUTTONDOWN)
    {
        select.x=x;
        select.y=y;
		//x1 = x;
		//y1 = y;
		LB_FLAG = 1;
    }
    else if(event==CV_EVENT_LBUTTONUP && LB_FLAG)
    {
        select.width=x-select.x;//以下2行计算出来的值要么都大于0，要么都小于0
        select.height=y-select.y;
		//x2 = x;
		//y2 = y;
		LB_FLAG = 2;
    }
	if (LB_FLAG == 2)
		rectangle(src_img, select, Scalar(0, 0, 255));
}


int main(int argc, char** argv)
{

	int  x1, y1, x2, y2;
	//namedWindow("image", WINDOW_AUTOSIZE);
	src_img = imread("121.jpg");
	Mat dst_img = Mat::zeros(300, 400, CV_8UC3);

	Point2f srcTri[3];
	Point2f dstTri[3];

	Mat warp_mat(2, 3, CV_32FC1);


	//setMouseCallback("image", onMouse, 0);
	x1 = src_img.cols / 2 - 400 ;
	y1 = src_img.rows / 2 - 300 ;
	x2 = x1 + 400;
	y2 = y1 + 300;

	select.x = x1;
	select.y = y1;
	select.width = x2 - x1;
	select.height = y2 - y1;

	//rectangle(src_img, select, Scalar(0, 0, 255));
	//waitKey(0);
	

	for (int i = 0; i < 41; i++)
	{
		imshow("image", src_img);

		srcTri[0] = Point2f(select.x * i/40.0, select.y * i / 40.0);
		srcTri[1] = Point2f(src_img.cols - 1 - (src_img.cols - x2 )*i / 40.0, select.y * i / 40.0);
		srcTri[2] = Point2f(select.x * i / 40.0, src_img.rows - 1 - (src_img.rows - y2)*i / 40.0);

		dstTri[0] = Point2f(0, 0);
		dstTri[1] = Point2f(dst_img.cols - 1, 0);
		dstTri[2] = Point2f(0, dst_img.rows - 1);

		warp_mat = getAffineTransform(srcTri, dstTri);

		warpAffine(src_img, dst_img, warp_mat,dst_img.size());
		imshow("affine", dst_img);
		waitKey(100);
	}

	char ff=waitKey(0);
	if(ff==' ')
	return 0;

}