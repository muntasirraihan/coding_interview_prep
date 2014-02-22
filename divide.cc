#include <stdio.h>
#include <stdlib.h>


/* Assumes num, denom are positive; denom != 0 */

int divide(int num, int denom)
{
  int a=0, b=0;
  int i= 31; // CAREFUL: works only on int=32-bit machine!
  /* Work from leftmost to rightmost bit in numerator */
  while(i>=0) {
    /* appends one bit from numerator to a */
    a = (a << 1) + ((num & (1 << i)) >> i); 
    b = b << 1;
    printf("After shifting a=%d and b=%d\n",a,b);
    if (a >= denom) {
      a -= denom;
      b++;
    }
    printf("After subtraction a=%d and b=%d\n",a,b);
  i--;
  }
  return b;
}

int main() {

  int a=4723;
  int b=36;
  int c = divide(a,b);
  printf("%d divided by %d is %d.\n", a,b,c);
  return 0;
}
