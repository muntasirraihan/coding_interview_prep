#include <cstdio>
#include <cstring>

int find_palindrome_span_with_center(char *string, int center) {
	int size = strlen(string);
	int span = 1;
	while (center - span >= 0 && center + span <= size
			&& string[center - span] == string[center + span])
		span++;
	return span - 1;
}

void find_longest_palindrome(char *string, int *longest_palindrome_index, int *palindrome_size) {
	int size = strlen(string);
	// transform the string
	char *padded_string = new char[2 * size + 1 + 1];
	for (int i = 0; i < size; ++i) {
		padded_string[2 * i] = '#';
		padded_string[2 * i + 1] = string[i];
	}
	padded_string[2 * size] = '#';
	padded_string[2 * size + 1] = '\0';
	size = 2 * size + 1;
	// p[i] stores the longest palindrome length centered at i;
	int *p = new int[size];
	int center = 0;

	while (center < size) {
		int palindrome_span = find_palindrome_span_with_center(padded_string, center);
		p[center] = palindrome_span;
		for (int right_offset = 1; right_offset <= palindrome_span; ++right_offset) {
			p[center + right_offset] = p[center - right_offset];
			if (p[center + right_offset] >= palindrome_span - right_offset) {
				center = center + right_offset;
				break;
			}
		}
		if (palindrome_span == 0)
			center++;
	}

	// return the solution
	int max = 0;
	int max_index = 0;
	for (int i = 0; i < size; ++i) {
		printf("%d-", p[i]);
		if (p[i] >= max) {
			max = p[i];
			max_index = i;
		}
	}
	printf("\n");
	*longest_palindrome_index = (max_index - max) / 2;
	if (max % 2 == 0) {
		*palindrome_size = max + 1;
	} else {
		*palindrome_size = 2 * (max / 2) + 1;
	}
	delete[] p;
}

int main() {
	// char string[] = "abcbabcbabcba";
	// char string[] = "ABCBAHELLOHOWRACECARAREYOUIAMAIDOINGGOOD";
	char string[] = "abba";
	printf("original string = %s\n", string);
	int size;
	int longest_palindrome;
	find_longest_palindrome(string, &longest_palindrome, &size);
	printf("longest_palindrome = ");
	for (int i = longest_palindrome; i < longest_palindrome + size; ++i) {
		printf("%c", string[i]);
	}
	printf("\n");
}

// original string = abcbabcbabcba
// 0-0-2-0-4-0-6-0-4-0-2-0-0-
// longest_palindrome = abcbabcbabcba