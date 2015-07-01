#include "typedefs.h"

void Delay_ms(uint32_t nCount)
{
	nCount*=16000;
	for(nCount=nCount; nCount != 0; nCount--)
	{
		
	}
}

void Delay_us(uint32_t nCount)
{
	nCount*=16;
	for(nCount=nCount; nCount != 0; nCount--)
	{
		
	}
}

