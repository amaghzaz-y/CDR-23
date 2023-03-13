#include <types/Steps.h>

Steps::Steps(long m1, long m2, long m3)
{
	M1 = m1;
	M2 = m2;
	M3 = m3;
}

long *Steps::Positions()
{
	long *pos = new long[3];
	pos[0] = M1;
	pos[1] = M2;
	pos[2] = M3;
	return pos;
}