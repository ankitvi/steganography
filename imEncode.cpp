#include "simpleLSB.h"
int im_encode(char *ip,char *hid)
{
	IplImage *input;  //cover image
	IplImage *hide;   // image to hide
	IplImage *output; // stego image
	
	uchar *data;
	uchar *inputdata;
	uchar *hidedata;

	int messageChar;
	int i=0,j=0,dataPos=40;
	int height,width,nchannels;
	int hideHeight,hideWidth,hideNchannels;
	
	input=cvLoadImage(ip,-1);
	hide=cvLoadImage(hid,-1);
	
	height=input->height;
	width=input->width;
	nchannels=input->nChannels;
	
	hideHeight=hide->height;
	hideWidth=hide->width;
	hideNchannels=hide->nChannels;
	
	if((nchannels*height*width) < (hideNchannels*8*hideHeight*hideWidth+40))
	{
		printf("cover image should be of larger size");
		exit(1);
	}
	
	printf("Hiding image of size %d X %d in image of size %d X %d\n", hideHeight, hideWidth, height, width);

	//now we will make an empty image of same size as original
	output=cvCreateImage(cvSize(width,height),IPL_DEPTH_8U,nchannels);
	data=(uchar *)output->imageData;
	inputdata=(uchar *)input->imageData;
	hidedata=(uchar *)hide->imageData;
	
	//so we save the height and width of image in output image. 20 bits for height and 20 for width

	for (i=0;i<20;i++)
	{
		data[i]=inputdata[i] & 254;
		data[i]=data[i]+getBit(hideHeight,i);
		data[i+20]=inputdata[i+20] & 254;
		data[i+20]=data[i+20]+getBit(hideWidth,i);
	}
	// so now we start saving the message from the 48th pixel i=dataPos=48
	for ( i=0;i<hideHeight*hideWidth*hideNchannels;i++)
	{
		messageChar =hidedata[i]; //each pixel value of hide image
		//printf("%d",messageChar);
		for ( j=0;j<8;j++)
		{
			data[dataPos]=inputdata[dataPos] & 254;
			data[dataPos]=data[dataPos]+getBit(messageChar,j);
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
	cvSaveImage("stegoimage_simple.png",output,0);
	cvNamedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Hidden Message Image", CV_WINDOW_AUTOSIZE);
	cvShowImage("Original Image", input);
	cvShowImage("Hidden Message Image", output);

	cvWaitKey(0);

	cvReleaseImage(&input);
	cvReleaseImage(&output);
	cvReleaseImage(&hide);
	cvDestroyWindow("Original Image");
	cvDestroyWindow("Hidden Message Image");
	
	return 0;
}

