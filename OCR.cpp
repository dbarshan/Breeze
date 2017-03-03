#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
	cv::Mat image = cv::imread("./test.png");
	cv::Mat orig_image;
	image.copyTo(orig_image);
	cv::cvtColor(image, image,CV_BGR2GRAY);
	cv::threshold( image, image, 127, 255,0);

	cv::vector<cv::vector<cv::Point>> contours;
	cv::vector<cv::Vec4i> hierarchy;
	cv::findContours(image, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, cv::Point(0,0));

	cv::vector<cv::vector<cv::Point>> contours_poly(contours.size());
	cv::vector<cv::Rect> boundRect ( contours.size());

	for( size_t i=0; i< contours.size(); i++)
	{
		approxPolyDP (cv::Mat(contours[i]),contours_poly[i], 3,true);
		boundRect[i] = cv::boundingRect( cv::Mat(contours_poly[i]));
	}

	cv::Mat drawing = cv::Mat(image.size(), CV_8UC3,cv::Scalar(255,255,255));
	for( size_t i=0;i< contours.size(); i++)
	{
		cv::drawContours(drawing, contours,(int)i, cv::Scalar(0,0,0),2,8,hierarchy,0, cv::Point());
		cv::rectangle(orig_image,boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0,255,0), 1);
	}

	
	cv::imwrite("./test2.png",orig_image);
	cv::resize(orig_image, orig_image, cv::Size(640,700));
	cv::imshow("Image", orig_image);
	cv::waitKey(0);
	return 0;
}

//	Mat canny_output;
//  vector<vector<Point> > contours;
//  vector<Vec4i> hierarchy;
//  Canny( src_gray, canny_output, thresh, thresh*2, 3 );
//  findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
//  Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
//  for( int i = 0; i< contours.size(); i++ )
//     {
//       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
//       drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
//     }


