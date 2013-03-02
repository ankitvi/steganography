#include "simpleLSB.h"
int getBit(int n,int i)
{
	if(n&(1<<i))
		return 1;
	else
		return 0;
}