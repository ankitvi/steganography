#include "simpleLSB.h"
int main()
{
	int choice,type;
	char inp[100],secret[100];

	printf("what would you like to hide?\n1.text\n2.image\n ");
	scanf(" %d",&type);
	if(type==1)
	{
		printf("enter choice.\n1.encode\n2.decode\n");
		scanf(" %d",&choice);
		if(choice==1)
		{
			printf("cover image file name? ");
			scanf(" %[^\n]s",inp);
			printf("enter secret message: ");
			scanf(" %[^\n]s",secret);
			text_encode(inp,secret);
		}
		else if(choice==2)
		{
			text_decode("textstego_simple.png");
		}
		else printf("enter correct choice.\n");
	}
	else if (type==2)
	{
		printf("enter choice.\n1.encode\n2.decode\n");
		scanf(" %d",&choice);
		if(choice==1)
		{
			printf("cover image file name? ");
			scanf(" %[^\n]s",inp);
			printf("enter secret image file name: ");
			scanf(" %[^\n]s",secret);
			im_encode(inp,secret);
		}
		else if(choice==2)
		{
			im_decode("stegoimage_simple.png");
		}
		else printf("enter correct choice.\n");
	}
	else printf("enter correct choice.");

	return 0;
}