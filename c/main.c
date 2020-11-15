#include <stdio.h>
#include <stdlib.h>
#include <json-c/json.h>

int main(int argc, char *argv[]){
	FILE *fp;
	char buffer[1024];

	struct json_object *parsed_json;
	struct json_object *jinfo;
	struct json_object *jwidth;
	struct json_object *jheight;
	struct json_object *jdata;

	int width, height;

	/*if(argc != 2){
		exit(1);
	}*/

	fp = fopen("out.json", "r");
	fread(buffer, 1024, 1, fp);
	fclose(fp);

	parsed_json = json_tokener_parse(buffer);

	json_object_object_get_ex(parsed_json, "iinfo", &jinfo);
	json_object_object_get_ex(parsed_json, "data", &jdata);

	json_object_object_get_ex(jinfo, "width", &jwidth);
	json_object_object_get_ex(jinfo, "height", &jheight);

	width = json_object_get_int(jwidth);
	height = json_object_get_int(jheight);


	printf("%d, %d\n", width, height);


	return 0;
}
