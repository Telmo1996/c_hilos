#include <stdlib.h>
#include <stdio.h>

struct Point{
	int x;
	int y;
};

int max(int, int);
void bresenham(int, int, int, int, struct Point[], int);
