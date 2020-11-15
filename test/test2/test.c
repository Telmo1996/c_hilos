#include <stdio.h>
#include <json-c/json.h>

int main(int argc, char **argv){
	FILE *fp;
	char buffer[1024];

	struct json_object *parsed_json;
	struct json_object *jinfo;
	struct json_object *jdata;

	struct json_object *jdata_row;

	size_t n_rows;
	size_t i;

	fp=fopen(argv[1], "r");
	fread(buffer, 1024, 1, fp);
	fclose(fp);

	parsed_json = json_tokener_parse(buffer);

	json_object_object_get_ex(parsed_json, "info", &jinfo);
	json_object_object_get_ex(parsed_json, "data", &jdata);

	printf("info: %s\n", json_object_get_string(jinfo));

	n_rows = json_object_array_length(jdata);
	printf("Found %lu rows\n", n_rows);

	for(i=0;i<n_rows;i++){
		jdata_row = json_object_array_get_idx(jdata, i);
		printf("%lu. %s\n", i+1, json_object_get_string(jdata_row));
	}

	return 0;

}
