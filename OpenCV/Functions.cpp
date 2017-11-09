#include "Functions.h"


/****************************************************************************************************************
*    Date    : 2017/11/08 11:04
*
*    Author  : Smile
*    Contact : smile@illidan.org
*
*    Brief   : ����ͼƬ����ɫֵ��ʹ��ָ����ɡ�
*
****************************************************************************************************************/
//void ColorReduce(const Mat& image, Mat& outImage, int div)
//{
//	// ������ԭͼ��ȳߴ��ͼ��    
//	outImage.create(image.size(), image.type());
//	int nr = image.rows;
//	// ��3ͨ��ת��Ϊ1ͨ��    
//	int nl = image.cols*image.channels();
//	for (int k = 0; k < nr; k++)
//	{
//		// ÿһ��ͼ���ָ��    
//		const uchar* inData = image.ptr<uchar>(k);
//		uchar* outData = outImage.ptr<uchar>(k);
//		for (int i = 0; i < nl; i++)
//		{
//			outData[i] = inData[i] / div*div + div / 2;
//		}
//	}
//}

/****************************************************************************************************************
*    Date    : 2017/11/08 10:40
*
*    Author  : Smile
*    Contact : smile@illidan.org
*
*    Brief   : ����ͼƬ����ɫֵ��ʹ��ָ����ɡ�

1.isContinuous()�ж�ͼƬ�������Ƿ����������������ͼƬ����һ�У��Ż�����

*
****************************************************************************************************************/
//void ColorReduce(const Mat& image, Mat& outImage, int div)
//{
//	int nr = image.rows;
//	int nc = image.cols;
//	outImage.create(image.size(), image.type());
//	if (image.isContinuous() && outImage.isContinuous())
//	{
//		nr = 1;
//		nc = nc*image.rows*image.channels();
//	}
//	for (int i = 0; i < nr; i++)
//	{
//		const uchar* inData = image.ptr<uchar>(i);
//		uchar* outData = outImage.ptr<uchar>(i);
//		for (int j = 0; j < nc; j++)
//		{
//			*outData++ = *inData++ / div*div + div / 2;
//		}
//	}
//}

/****************************************************************************************************************
*    Date    : 2017/11/08 11:26
*
*    Author  : Smile
*    Contact : smile@illidan.org
*
*    Brief   : ����ͼƬ����ɫֵ��ʹ��at()������
*
****************************************************************************************************************/
//void ColorReduce(const Mat& image, Mat& outImage, int div)
//{
//	outImage.create(image.size(), image.type());
//	for (int i = 0; i < image.rows; ++i)
//	{
//		for (int j = 0; j < image.cols; ++j)
//		{
//			outImage.at<Vec3b>(i, j)[0] = image.at<Vec3b>(i, j)[0] / div * div + div / 2;
//			outImage.at<Vec3b>(i, j)[1] = image.at<Vec3b>(i, j)[1] / div * div + div / 2;
//			outImage.at<Vec3b>(i, j)[2] = image.at<Vec3b>(i, j)[2] / div * div + div / 2;
//		}
//	}
//}

/****************************************************************************************************************
*    Date    : 2017/11/08 11:50
*
*    Author  : Smile
*    Contact : smile@illidan.org
*
*    Brief   : ����ͼƬ��ɫֵ��ʹ�õ�������
*
****************************************************************************************************************/
//void ColorReduce(const Mat& image, Mat& outImage, int div)
//{
//	outImage.create(image.size(), image.type());
//
//	MatConstIterator_<Vec3b> srcIterStart = image.begin<Vec3b>();
//	MatConstIterator_<Vec3b> srcIterEnd = image.end<Vec3b>();
//
//	MatIterator_<Vec3b> desIterStart = outImage.begin<Vec3b>();
//	MatIterator_<Vec3b> desIterEnd = outImage.end<Vec3b>();
//
//	while (srcIterStart != srcIterEnd)
//	{
//		(*desIterStart)[0] = (*srcIterStart)[0] / div * div + div / 2;
//		(*desIterStart)[1] = (*srcIterStart)[1] / div * div + div / 2;
//		(*desIterStart)[2] = (*srcIterStart)[2] / div * div + div / 2;
//
//		++srcIterStart;
//		++desIterStart;
//	}
//}

/****************************************************************************************************************
*    Date    : 2017/11/08 11:56
*
*    Author  : Smile
*    Contact : smile@illidan.org
*
*    Brief   : ����ͼƬ��ɫֵ��ȫ��档
*
****************************************************************************************************************/
void ColorReduce(const Mat& image, Mat& outImage, int div)
{
	CV_Assert(image.depth() != sizeof(uchar));
	const int channels = image.channels();
	switch (channels)
	{
	case 1:
	{
		outImage.create(image.size(), image.type());

		MatConstIterator_<uchar> srcIterStart = image.begin<uchar>();
		MatConstIterator_<uchar> srcIterEnd = image.end<uchar>();

		MatIterator_<uchar> desIterStart = outImage.begin<uchar>();
		MatIterator_<uchar> desIterEnd = outImage.end<uchar>();

		while (srcIterStart != srcIterEnd)
		{
			*desIterStart = *srcIterStart / div * div + div / 2;

			++srcIterStart;
			++desIterStart;
		}
	}
	break;
	case 3:
	{
		outImage.create(image.size(), image.type());

		MatConstIterator_<Vec3b> srcIterStart = image.begin<Vec3b>();
		MatConstIterator_<Vec3b> srcIterEnd = image.end<Vec3b>();

		MatIterator_<Vec3b> desIterStart = outImage.begin<Vec3b>();
		MatIterator_<Vec3b> desIterEnd = outImage.end<Vec3b>();

		while (srcIterStart != srcIterEnd)
		{
			(*desIterStart)[0] = (*srcIterStart)[0] / div * div + div / 2;
			(*desIterStart)[1] = (*srcIterStart)[1] / div * div + div / 2;
			(*desIterStart)[2] = (*srcIterStart)[2] / div * div + div / 2;

			++srcIterStart;
			++desIterStart;
		}
	}
	break;
	}
}

/****************************************************************************************************************
*    Date    : 2017/11/09 13:51
*
*    Author  : Smile
*    Contact : smile@illidan.org
*
*    Brief   : ��ɫ
*
****************************************************************************************************************/
void InverseColor(const Mat& image, Mat& outImage)
{
	// ����LUT��ɫtable    
	cv::Mat lookUpTable(1, 256, CV_8U);
	uchar* pData = lookUpTable.data;
	for (int i = 0; i < 256; ++i)
		pData[i] = 255 - i;

	outImage.create(image.size(), image.type());
	LUT(image, lookUpTable, outImage);
}

/****************************************************************************************************************
*    Date    : 2017/11/09 13:40
*
*    Author  : Smile
*    Contact : smile@illidan.org
*
*    Brief   : ƽ��
*
****************************************************************************************************************/
void TranslateTransform(const Mat& image, Mat& outImage, int offsetX, int offsetY)
{
	outImage.create(image.size(), image.type());

	for (int i = 0; i < outImage.rows; i++)
	{
		Vec3b *pRow = outImage.ptr<Vec3b>(i);
		for (int j = 0; j < outImage.cols; j++)
		{
			//ƽ�ƺ�����ӳ�䵽ԭͼ��  
			int x = j - offsetX;
			int y = i - offsetY;
			//��֤ӳ����������ԭͼ��Χ��  
			if (x >= 0 && y >= 0 && x < image.cols && y < image.rows)
				pRow[j] = image.ptr<Vec3b>(y)[x];
		}
	}
}