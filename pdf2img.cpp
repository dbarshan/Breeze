#include <QTextStream>
#include <QImage>
#include <poppler-qt4.h>
#include <opencv2/opencv.hpp>

cv::Mat qimage_to_mat_ref(QImage &img, int format)
{
    return cv::Mat(img.height(), img.width(), format, img.bits(), img.bytesPerLine());
}

cv::Mat QImage2Mat(QImage const& src)
{
     cv::Mat tmp(src.height(),src.width(),CV_8UC4,(uchar*)src.bits(),src.bytesPerLine());
     cv::Mat result; // deep copy just in case (my lack of knowledge with open cv)
	//cvtColor(tmp, result,CV_BGR2RGB);
     return tmp;
}

int main()
{
	QString filename="./progit-en.1084.pdf";
	QTextStream(stdout) << "Hello QT" << endl;
	Poppler::Document* document = Poppler::Document::load(filename);
	if (document == 0) 
	{
			QTextStream(stdout) << "Error can not open pdf" << endl;
			return -1;
	}
	Poppler::Page* pdfPage = document->page(26);
	if (pdfPage == 0)
	{
		QTextStream(stdout) << "Error can not read page" << endl;
		return -1;
	}
	QImage image = pdfPage->renderToImage(300,300, -1, -1, 2100,2750,Poppler::Page::Rotate0);
	//QImage image = pdfPage->renderToImage();
	if ( image.isNull())
	{
		QTextStream(stdout) << "Error can not convert page to image" << endl;
		return -1;
	}
	cv::Mat cvImage = QImage2Mat(image) ;
	cv::imwrite( "./test.png", cvImage);
	cv::Size size(414,586);
	cv::Mat dst;
	cv::resize(cvImage,dst,size);//resize image
	cv::imshow("PDF",dst);
	cv::waitKey(0);

	delete pdfPage;
	delete document;
	return 0;
}
