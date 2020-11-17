#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <json-c/json.h>
#include "funciones.h"


int main(int argc, char *argv[]){
	FILE *fp;
	char buffer[1024*1024*4];

	struct json_object *parsed_json;
	struct json_object *jinfo;
	struct json_object *jwidth;
	struct json_object *jheight;
	struct json_object *jdata;
	struct json_object *jdata_row;

	int width, height;
	int i, j;
	const int n = 180;
	const int nHilos = 5000;


	//Leer out.json
	fp = fopen("out.json", "r");
	fread(buffer, 1024*1024*4, 1, fp);
	fclose(fp);

	//Parse del json
	parsed_json = json_tokener_parse(buffer);

	json_object_object_get_ex(parsed_json, "info", &jinfo);
	json_object_object_get_ex(parsed_json, "data", &jdata);

	json_object_object_get_ex(jinfo, "width", &jwidth);
	json_object_object_get_ex(jinfo, "height", &jheight);

	width = json_object_get_int(jwidth);
	height = json_object_get_int(jheight);

	//Guardar data
	int *data[width];
	for(i=0; i<width; i++){
		data[i] = (int *)malloc(height * sizeof(int));
	}

	for(j=0; j<height; j++){
		jdata_row = json_object_array_get_idx(jdata, j);
		for(i=0; i<width; i++){
			data[j][i] = json_object_get_int(
				json_object_array_get_idx(jdata_row, i)
			);
		}
	}

	printf("Json leido con exito.\n");


	//Crear agujas
	struct Point agujas[n];
	int r = width/2;
	double alpha;
	for(i=0; i<n; i++){
		alpha = 2.0*M_PI/n * i;
		agujas[i].x = width/2.0 + r * cos(alpha);
		agujas[i].y = height/2.0 + r * sin(alpha);
	}


	//Bucle principal
	int currAguja = 0, nextAguja;
	int hilos[nHilos+1];
	int maxIntensidad, x0, y0, x1, y1, len;
	double inten;
	struct Point linea[2000];
	hilos[0] = 0;
	for(i=0; i<nHilos; i++){
		maxIntensidad = 0;
		for(j=0; j<n; j++){
			x0 = agujas[currAguja].x; y0 = agujas[currAguja].y;
			x1 = agujas[j].x; y1 = agujas[j].y;
			len = max(abs(x0-x1),abs(y0-y1));
			//printf("len: %d, ", len);
			bresenham(x0, y0, x1, y1, linea, len);
			inten = intensidad(linea, len, data);
			//printf("%f", inten); exit(0);
			if(inten > maxIntensidad){
				maxIntensidad = inten;
				nextAguja = j;
			}
		}
		x0 = agujas[currAguja].x; y0 = agujas[currAguja].y;
		x1 = agujas[nextAguja].x; y1 = agujas[nextAguja].y;
		bresenham(x0, y0, x1, y1, linea, len);
		blanquear(linea, len, data);
		/*Aqui iria la tonteria del break*/
		currAguja = nextAguja;
		hilos[i+1] = currAguja;
	}

	
	for(i=0; i<nHilos; i++){
		printf("%d ", hilos[i]);
	}
	

	return 0;
}
