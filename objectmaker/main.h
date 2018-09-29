#pragma once

int main(int argc, char * argv[])
{
	printf("����������ͼ�񴰿��л����Եõ�Ŀ������Ĵ���λ��.\
		   \nȻ����a,s,d,w�ƶ���ѡ������1��2,3,5�Ŵ����С֮\
		   \n����opencv�м�����Ӧ����������Ӧ�����еķ������shift����ctrl��\
		   \n������tab���л�״̬���Ŵ����С��\
		   \nѡ���������enter������\
		   \n�����f�ɽ�ԭͼƬˮƽ��ת\
		   \n�����g�ɽ�ԭͼƬתΪ�Ҷ�ͼ\
		   \n��Esc���˳���");

	char img_path[80] = "F:\\face_recognition_database\\Images\\010A18.jpg";
	char save_path[80] = "F:\\face_recognition_database\\Images_cut\\010A18\\25.jpg";

	IplImage* img = cvLoadImage(img_path);
	IplImage* img2 = cvLoadImage(img_path);
	IplImage* img3 = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);//��ԭͼ��ָ�봴����ͼ��
	IplImage* img_show = cvCloneImage(img);

	cvNamedWindow("img", CV_WINDOW_AUTOSIZE);
	cvSetMouseCallback("img", cvMouseCallback);

	bool shift_on = false;

	char text[80];
	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_PLAIN, 1.0, 1.0);
	while (true)
	{
		cvCopy(img, img_show);
		cvRectangle(img_show, pt1, pt2, cvScalar(255, 255, 255));
		sprintf(text, "roi = cvRect(%d,%d,%d,%d)", pt1.x, pt1.y, std::abs(pt2.x - pt1.x), std::abs(pt2.y - pt1.y));
		cvPutText(img_show, text, cvPoint(10, 20), &font, cvScalar(0, 0, 255));

		cvShowImage("img", img_show);
		char key = cvWaitKey(10);
		switch (key)
		{
		case '\t':
			shift_on = !shift_on; break;

		case 'a':
			pt1.x--; pt2.x--; break;
		case 's':
			pt1.y++; pt2.y++; break;
		case 'd':
			pt1.x++; pt2.x++; break;
		case 'w':
			pt1.y--; pt2.y--; break;

		case '1':
			if (shift_on) pt1.x--;
			else pt2.x--;
			break;
		case '2':
			if (shift_on) pt2.y++;
			else pt1.y++;
			break;
		case '3':
			if (shift_on) pt2.x++;
			else pt1.x++;
			break;
		case '5':
			if (shift_on) pt1.y--;
			else pt2.y--;
			break;

		case '\r':
			cvSetImageROI(img, cvRect(pt1.x, pt1.y, std::abs(pt2.x - pt1.x), std::abs(pt2.y - pt1.y)));
			cvResize(img, img2, CV_INTER_LINEAR);
			cvSaveImage(save_path, img2);
			cvResetImageROI(img);
			break;
		case 'f':
			cvFlip(img2, img2, 1);//flip_mode=0Ϊ��ֱ��ת��>0Ϊˮƽ��ת
			cvSaveImage(save_path, img2);
			break;
		case 'g':
			cvCvtColor(img2, img3, CV_BGR2GRAY);
			cvSaveImage(save_path, img3);
			break;
		};

		if (key == 27) break;
	}

	cvReleaseImage(&img);
	cvReleaseImage(&img_show);
	return 0;
}
