#include <iostream>

using namespace std;

#define MAX_DIGITS 100

#define PLUS 1
#define MINUS -1

typedef struct {
	char digits[MAX_DIGITS];
	int sign_bit;
	int last_digit;	// index of the high-order digit
} bignum;

void print_bignum(bignum *n) {
	if (n->sign_bit == MINUS) {
		cout << "-";
	}
	for (int i = n->last_digit; i >= 0; --i) {
		cout << n->digits[i];
	}
	cout << endl;
}


void initialize_bignum(bignum *n) {
	memset(n->digits, '0', MAX_DIGITS);
	n->sign_bit = PLUS;
	n->last_digit = 0;
}

int main() {
	cout << "hello";
	bignum *a = new bignum();
	initialize_bignum(a);
	a->digits[0] = '1';
	a->digits[1] = '0';
	a->digits[2] = '0';
	a->digits[3] = '1';
	a->sign_bit = PLUS;
	a->last_digit = 3;


	print_bignum(a);

	bignum *b = new bignum();;
	initialize_bignum(b);
	b->digits[0] = '1';
	b->digits[1] = '0';
	b->digits[2] = '0';
	b->digits[3] = '1';
	b->sign_bit = PLUS;
	b->last_digit = 3;


}