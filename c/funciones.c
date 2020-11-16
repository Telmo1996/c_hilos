#include "funciones.h"


int max(int a, int b){
	if(a > b)
		return a;
	else
		return b;
}

void bresenham(int x0, int y0, int x1, int y1, struct Point linea[], int len){
	int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = dx + dy, e2; /* error value e_xy */
	int i = 0;

	for (;;){  /* loop */
		//setPixel (x0,y0);
		//printf("%d, %d | ", x0, y0);
		linea[i].x = x0; linea[i].y = y0;
		if (x0 == x1 && y0 == y1) break;
		e2 = 2 * err;
		if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
		if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */

		i++;
	}
	if(len != i) printf("len != i");
}

double intensidad(struct Point linea[], int len, int data[][1000]){
	double inten = 0.0;
	int i;
	printf("%d\n", len);
	for(i=0; i<len; i++){
		printf("%d,%d ", linea[i].x -1, linea[i].y -1);
		inten += 255.0 - data[linea[i].x -1][linea[i].y -1];
	}
	return inten / len;

}
