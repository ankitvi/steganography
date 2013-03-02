#include "simpleLSB.h"
IplImage* display(IplImage *im)
{
	//IplImage *test=cvCreateImage(cvGetSize(im),im->depth,im->nChannels);
	IplImage *test=cvCloneImage(im);
	//cvResize(im,test);
	IplImage *copyright=cvLoadImage("bisag.jpg");
	IplImage *out=cvCreateImage(cvSize(100,100),copyright->depth,copyright->nChannels);
	cvResize(copyright,out);
	cvSetImageROI(test,cvRect(0,0,100,100));
	cvAddWeighted(test,1.0,out,0.5,1.0,test);
	cvResetImageROI(test);
	return test;
	
}
IplImage* zoom_in(IplImage *orig,int level)
{
	IplImage *im=cvCloneImage(orig);
	int height=im->height,width=im->width;
	IplImage *imnew=cvCreateImage(cvSize(width,height),8,3);
	
	int half_height=height/2;
	int half_width=width/2;
	int x1=half_height/level,x2=height-x1;
	int y1=half_width/level,y2=width-y1;
	cvSetImageROI(im,cvRect(x1,y1,y2-y1,x2-x1));
	
	cvResize(im,imnew);
	return imnew;
}
int main()
{
	IplImage *im=cvLoadImage("kolkata.jpg");
	
	IplImage *dumdum=display(im);
	cvNamedWindow("test",CV_WINDOW_AUTOSIZE);
	cvShowImage("test",dumdum);
	int zoom_level=11;
	IplImage *imnew,*tada;
	int choice=0;
	while(1)
	{
		choice=cvWaitKey(0);
		if(choice==38 || choice==27)
		{
			zoom_level--;
			if(zoom_level<2) 
				continue;
		
			imnew=zoom_in(im,zoom_level);
			tada=display(imnew);
			cvShowImage("test",tada);
		}
		else if (choice==40 || choice==37)
		{
			zoom_level++;
			if(zoom_level>10) continue;
			imnew=zoom_in(im,zoom_level);
			tada=display(imnew);
			cvShowImage("test",tada);
		}
	}
	cvDestroyWindow("test");
		
	return 0;
}
