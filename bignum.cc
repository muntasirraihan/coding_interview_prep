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

void initialize_bignum(bignum *n) {
	memset(n->digits, (char)0, MAX_DIGITS);
	n->sign_bit = PLUS;
	n->last_digit = 0;
}

// adjust last_digit
void zero_justify(bignum *n) {
	int i = n->last_digit;
	while (i > 0 && n->digits[i] == 0) --i;
	n->last_digit = i;
	if (n->digits[n->last_digit] == 0) {
		n->sign_bit = PLUS;
	}
}

void int_to_bignum(int s, bignum *n) {
	initialize_bignum(n);
	if (s == 0) return;
	if (s < 0) {
		n->sign_bit = MINUS;
		s = -s;
	}

	int digit = 0;
	while (s > 0) {
		n->digits[digit++] = s % 10;
		s = s / 10;
		if (digit > MAX_DIGITS) {
			cerr << "OVERFLOW" << endl;
			exit(1);
		}
	}
	n->last_digit = digit - 1;
}

// test if a < b
int compare_bignum(bignum *a, bignum *b) {
	// a and b have different sign bits
	if (a->sign_bit > b->sign_bit) return -1;
	if (b->sign_bit > a->sign_bit) return 1;

	// a and b have the same sign bits
	if (a->last_digit > b->last_digit) {
		return (-1 * a->sign_bit);
	} else if (b->last_digit > a->last_digit) {
		return (1 * a->sign_bit);
	} else {
		// same number of digits
		for (int i = a->last_digit; i >= 0; --i) {
			if (a->digits[i] > b->digits[i]) {
				return (-1 * a->sign_bit);
			}
			if (b->digits[i] > a->digits[i]) {
				return (1 * a->sign_bit);
			}
		}
	}
	return 0;
}


void print_bignum(bignum *n) {
	if (n->sign_bit == MINUS) {
		printf("-");
	}
	for (int i = n->last_digit; i >= 0; --i) {
		printf("%c", '0' + n->digits[i]);
	}
	cout << endl;
}

void add_bignum(bignum *a, bignum *b, bignum *c);
void subtract_bignum(bignum *a, bignum *b, bignum *c);

void add_bignum(bignum *a, bignum *b, bignum *c) {

	// set bignum struct
	initialize_bignum(c);

	// handle negative bignum case; a and b have different signs
	if (a->sign_bit > b->sign_bit) {
		b->sign_bit = PLUS;
		subtract_bignum(a, b, c);
		b->sign_bit = MINUS;
		return;
	} else if (b->sign_bit > a->sign_bit) {
		a->sign_bit = PLUS;
		subtract_bignum(b, a, c);
		a->sign_bit = MINUS;
		return;
	}

	// handle additions
	int carry = 0;
	int t;
	int max_last_digit = (a->last_digit > b->last_digit) ? a->last_digit : b->last_digit;
	for (int i = 0; i <= max_last_digit; ++i) {
		t = carry + a->digits[i] + b->digits[i];
		c->digits[i] = t % 10;
		carry = t / 10;
	}
	c->last_digit = max_last_digit;
	
	// if extra carry
	if (carry > 0) {
		c->last_digit += 1;
		// last_digit is zero-based
		if (c->last_digit + 1 > MAX_DIGITS) {
			cerr << "OVERFLOW" << endl;
			exit(1);
		}
		c->digits[c->last_digit] = 1;
	}

	// same sign as a and b
	c->sign_bit = a->sign_bit;
	zero_justify(c);
}

void subtract_bignum(bignum *a, bignum *b, bignum *c) {

	// set bignum struct
	initialize_bignum(c);

	// handle negative bignum case; a and b have different signs
	if (a->sign_bit > b->sign_bit) {
		b->sign_bit = PLUS;
		add_bignum(a, b, c);
		b->sign_bit = MINUS;
		return;
	} else if (b->sign_bit > a->sign_bit) {
		a->sign_bit = PLUS;
		add_bignum(a, b, c);
		a->sign_bit = MINUS;
		c->sign_bit = MINUS;
		return;
	}

	// handle subtractions for same signs
	bignum *larger, *smaller;
	// test a < b
	if (compare_bignum(a, b) == 1) {
		larger = b;
		smaller = a;
	} else {
		larger = a;
		smaller = b;
	}

	int borrowed = 0;
	for (int i = 0; i <= larger->last_digit; ++i) {
		int v = larger->digits[i] - borrowed - smaller->digits[i];
		if (v >= 0) {
			c->digits[i] = v;
			borrowed = 0;
		} else {
			c->digits[i] = v + 10;
			borrowed = 1;
		}
	}
	// same sign as a and b
	if (larger == b) {
		c->sign_bit = MINUS;
	} else {
		c->sign_bit = PLUS;	
	}
	c->last_digit = larger->last_digit;
	zero_justify(c);

}


void multiply_bignum(bignum *a, bignum *b, bignum *c) {

	// assume a is longer than b
	if (b->last_digit > a->last_digit) {
		multiply_bignum(b, a, c);
		return;
	}

	// set bignum struct
	initialize_bignum(c);

	// handle additions
	int carry = 0;
	int t;

	for (int i = 0; i <= b->last_digit; ++i) {
		for (int j = 0; j <= a->last_digit; ++j) {
			// last_digit is zero-based
			if (j + i + 1 > MAX_DIGITS) {
				cerr << "OVERFLOW" << endl;
				exit(1);
			}

			t = carry + a->digits[i] * b->digits[j] + c->digits[j + i];
			// offset c by i
			c->digits[j + i] = t % 10;

			carry = t / 10;
		}
		
		c->last_digit = a->last_digit + i;
		// if extra carry
		if (carry > 0) {
			c->digits[a->last_digit + i + 1] += carry;
			c->last_digit = a->last_digit + i + 1;
			carry = 0;
		}

	}

	c->sign_bit = a->sign_bit * b->sign_bit;
	zero_justify(c);
}

void left_shift(bignum *n, int d) {
	if (n->last_digit == 0 && n->digits[0] == 0)
		return;

	for (int i = n->last_digit + d; i >= d; --i) {
		n->digits[i] = n->digits[i - d];
	}

	for (int i = d - 1; i >= 0; --i) {
		n->digits[i] = 0;
	}

	n->last_digit += d;
}

void divide_bignum(bignum *a, bignum *b, bignum *c) {
// a / b

	// set bignum struct
	initialize_bignum(c);

	// if a < b, we get 0
	if (compare_bignum(a, b) == 1) {
		return;
	}

	// remove signs
	int asign = a->sign_bit;
	int bsign = b->sign_bit;
	a->sign_bit = PLUS;
	b->sign_bit = PLUS;

	// handle additions
	bignum row;
	bignum tmp;
	initialize_bignum(&row);
	initialize_bignum(&tmp);

	for (int i = a->last_digit; i >= 0; --i) {
		print_bignum(&row);
		left_shift(&row, 1);
		row.digits[0] = a->digits[i];
		c->digits[i] = 0;
		// if divisor < row
		while (compare_bignum(b, &row) != -1) {
			subtract_bignum(&row, b, &tmp);
			row = tmp;
			c->digits[i]++;
		}

	}

	// restore signs
	a->sign_bit = asign;
	b->sign_bit = bsign;
	c->sign_bit = a->sign_bit * b->sign_bit;

	c->last_digit = a->last_digit;
	zero_justify(c);
}

int main() {
	bignum *a = new bignum();
	int_to_bignum(11119, a);
	print_bignum(a);


	bignum *b = new bignum();
	int_to_bignum(91111, b);
	print_bignum(b);

	bignum *c = new bignum();
	add_bignum(a, b, c);
	print_bignum(c);

	bignum *d = new bignum();
	subtract_bignum(a, b, d);
	print_bignum(d);

	bignum *e = new bignum();
	multiply_bignum(a, b, e);
	print_bignum(e);

	// left_shift(a, 3);
	// print_bignum(a);

	bignum *f = new bignum();
	divide_bignum(a, b, f);
	print_bignum(f);
}