#define csv_use
#include "./csv.h"

int main() {
	csv_str str = csv_read("example.csv");
	csv_array arr = csv_load(str, ",");

	if (arr.len == -1) return printf("Unable to read csv file\n");

	for (int c = 0; c < arr.len; c++) printf("%s, ", arr.arr[c]);

	csv_free_str(&str);
	csv_free_array(&arr);

	return 0;
}
