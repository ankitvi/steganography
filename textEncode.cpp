#include "simpleLSB.h"
int text_encode(char *ip,char *hide)
{
	IplImage *input;  //cover image
	IplImage *output; // stego image
	
	uchar *data;
	uchar *inputdata;
	
	int msglen=strlen(hide);
	int i=0,j=0,dataPos=20;
	int height,width,nchannels;
	
	input=cvLoadImage(ip,-1);
	
	height=input->height;
	width=input->width;
	nchannels=input->nChannels;

	if((nchannels*height*width) < (msglen+20))
	{
		printf("cover image should be of larger size");
		exit(1);
	}
	

	//now we will make an empty image of same size as original
	output=cvCreateImage(cvSize(width,height),IPL_DEPTH_8U,nchannels);
	data=(uchar *)output->imageData;
	inputdata=(uchar *)input->imageData;
	//so we save the height and width of image in output image. 20 bits for height and 20 for width

	for (i=0;i<20;i++)
	{
		data[i]=inputdata[i] & 254;
		data[i]=data[i]+getBit(msglen,i);
	}
	// so now we start saving the message from the 48th pixel i=dataPos=48
	for ( i=0;i<msglen;i++)
	{
		for ( j=0;j<8;j++)
		{
			data[dataPos]=inputdata[dataPos] & 254;
			data[dataPos]=data[dataPos]+getBit(hide[i],j);
			dataPos++;
		}
		//printf("%d\t",data[dataPos]);
	}
	//hiding of image completes
	//now the rest of the output image should be equal to input image.
	for(j=dataPos;j<height*width*nchannels;j++)
	{
		data[j]=inputdata[j];
	}
	
	//now showing cover and stego images
	cvSaveImage("textstego_simple.png",output,0);
	cvNamedWindow("Hidden Message Image", CV_WINDOW_AUTOSIZE);
	cvShowImage("Hidden Message Image", output);

	cvWaitKey(0);

	cvReleaseImage(&input);
	cvReleaseImage(&output);
	cvDestroyWindow("Original Image");
	cvDestroyWindow("Hidden Message Image");
	
	return 0;
}
