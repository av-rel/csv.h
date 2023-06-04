#ifndef __csv__
#define __csv__

typedef struct { char* lit; int len; } csv_str;
typedef struct { char** arr; int len; } csv_array;

#ifndef csv_use
csv_str csv_read(char* path);
csv_array csv_load(csv_str str, char* delimiter);
inline void csv_free_array(csv_array* arr);
inline void csv_free_str(csv_str* str);
#endif

#ifdef csv_use
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

csv_str csv_read(char* path) {
	FILE *fp = fopen(path, "r");
	if (!fp) {
		fclose(fp);
		return (csv_str) {.lit = 0,.len = -1};
	}

	fseek(fp, 0, SEEK_END);
	int len = ftell(fp);
	rewind(fp);
	if (len == 0) {
		fclose(fp);
		return (csv_str){.lit = (char*)"",.len = 0};
	}

	char* con = (char*)malloc(len);
	fread(con, len, sizeof(char), fp);
	con[len - 1] = '\0';

	fclose(fp);

	return (csv_str){ .lit = con, .len = len};
}

csv_array csv_load(csv_str str, char* delimiter) {
	if (str.len == -1) return (csv_array){.arr = 0, .len = -1};

	char** tokens = (char**)malloc(0);
	int toklen = 0;
	char* tok = strtok(str.lit, delimiter);

	while (tok) {
		tokens = (char**)realloc(tokens, sizeof(char*) * (toklen + 1));
		tokens[toklen++] = tok;
		tok = strtok(0, delimiter);
	}

	return (csv_array){.arr = tokens, .len = toklen};
}

inline void csv_free_array(csv_array* arr) {
	if (arr->len > 0) free(arr->arr);
	arr->len = -1;
}

inline void csv_free_str(csv_str* str) {
	if (str->len > 0) free(str->lit);
	str->len = -1;
}
#endif

#endif
