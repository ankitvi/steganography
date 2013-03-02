#include "simpleLSB.h"
int im_decode(char *ip)
{
	IplImage *stego,*hidden;
	
	uchar *data,*outdata;
	int ht,wt,hideht=0,hidewt=0,dataPos=40;

	stego=cvLoadImage(ip);
	ht=stego->height;
	wt=stego->width;

	data=(uchar *)stego->imageData;

	//extracting the height and width of the image
	for(int i=0;i<20;i++)
	{
		hideht=hideht+getBit(data[i],0)*(1<<i);
		hidewt=hidewt+getBit(data[i+20],0)*(1<<i);
	}
	printf("\nheight=%d width=%d\n",hideht,hidewt);

	//now based on height and width we will create new empty image of the size and then fill it
	hidden=cvCreateImage(cvSize(hidewt,hideht),IPL_DEPTH_8U,3);
	outdata=(uchar *)hidden->imageData;
	for(int i=0;i<hideht*hidewt*3;i++)
	{
		outdata[i]=0;
		for (int j=0;j<8;j++)
		{
			outdata[i]=outdata[i]+(getBit(data[dataPos],0)*(1<<j));
			dataPos++;
		}
	}
	cvSaveImage("hidden.png",hidden,0);		
	cvNamedWindow("hidden image",CV_WINDOW_AUTOSIZE);
	cvShowImage("hidden image",hidden);
	cvWaitKey(0);
	cvReleaseImage(&stego);
	return 0;
}
