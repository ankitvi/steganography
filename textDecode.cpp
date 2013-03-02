#include "simpleLSB.h"
int text_decode(char *ip)
{
	IplImage *stego;
	char outdata[10000];
	uchar *data;
	int ht,wt,hidelen=0,dataPos=20;

	stego=cvLoadImage(ip);
	ht=stego->height;
	wt=stego->width;

	data=(uchar *)stego->imageData;

	//extracting the height and width of the image
	for(int i=0;i<20;i++)
	{
		hidelen=hidelen+getBit(data[i],0)*(1<<i);
	}
	printf("hiding message of length= %d\n",hidelen);
	//now based on height and width we will create new empty image of the size and then fill it
	for(int i=0;i<hidelen;i++)
	{
		outdata[i]=0;
		for (int j=0;j<8;j++)
		{
			outdata[i]=outdata[i]+(getBit(data[dataPos],0)*(1<<j));
			dataPos++;
		}
	}
	outdata[hidelen]='\0';
	printf("\nhidden message= %s \n",outdata);
	while(1);
	cvReleaseImage(&stego);
	return 0;
}