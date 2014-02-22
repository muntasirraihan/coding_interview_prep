#include <cstdio>
#include <cstring>

void delete_substring(char *substr, char *string) {
	char *cpy_ptr = string;
	char *scan_ptr = string;
	char *restore_ptr = string;
	char *substr_ptr = substr;
	int num_char_matched = 0;
	int substr_len = strlen(substr);

	// scan through the string`
	while (*scan_ptr != '\0') {
		if (*scan_ptr == *substr) {
			// match the first substr character
			// record restore point
			restore_ptr = cpy_ptr;
			// reset
			num_char_matched = 0;
			substr_ptr = substr;
		}
		printf("scan_ptr = %c\n", *(scan_ptr));
		printf("cpy_ptr = %c\n", *(cpy_ptr));
		printf("substr_ptr = ---%c\n", *(substr_ptr));
		printf("restore_ptr = ------%c\n", *(restore_ptr));

		if (*scan_ptr == *substr_ptr) {
			// match substr character
			num_char_matched++;
			substr_ptr++;

			// entire substring matched
			if (num_char_matched == substr_len) {
				cpy_ptr = restore_ptr;

				scan_ptr++;
				// reset
				num_char_matched = 0;
				substr_ptr = substr;
				continue;
			}
		} else {
			// mismatch
			// reset
			num_char_matched = 0;
			substr_ptr = substr;
		}

		// increment scan
		*cpy_ptr = *scan_ptr; 
		cpy_ptr++;
		scan_ptr++;
	}
	// NULL terminate the string
	*cpy_ptr = '\0';
}

int main() {
	char string[] = "worldworldwordworld, world is not this world.";
	char substr[] = "world";
	printf("original string = %s\n", string);
	delete_substring(substr, string);
	printf("after deletion = %s\n", string);
}