#include <stdio.h>
#include <stdlib.h>


/* Assumes num, denom are positive; denom != 0 */

int divide(int num, int denom) {
  int quotient = 0;
  int num_buf = 0;
  for (int i = 31; i >= 0; --i) {
    num_buf = (num_buf << 1) + ((num & (1 << i)) >> i);
    quotient <<= 1;
    while (num_buf > denom) {
      num_buf -= denom;
      quotient += 1;
    }
  }

  return quotient;
}

int main() {

  int a=4723;
  int b=36;
  int c = divide(a,b);
  printf("%d divided by %d is %d.\n", a,b,c);
  return 0;
}
