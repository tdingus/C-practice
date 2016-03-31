/*
  Implemented 64-bit CLA adder in C
  (less gate delay than a ripple adder)
 */

#include <stdio.h>

// 64-bit adder
long add(long x, long y) {
  int x_array[64];
  int y_array[64];
  int c_array[64];

  int g_array[64];
  int p_array[64];

  int gg_array[16];
  int gp_array[16];

  int sg_array[4];
  int sp_array[4];
  int sc_array[4];

  int gc_array[16];

  int i;
  for (i = 0; i < 64; i++) { // first fill out x, y, g and p
    x_array[i] = x%2;
    y_array[i] = y%2;
    x -= x%2; x /= 2;
    y -= y%2; y /= 2;

    g_array[i] = x_array[i]*y_array[i];
    p_array[i] = (x_array[i]+y_array[i])%2; // p = 0 if xi and yi = 1
  }
  
  for (i = 0; i < 16; i++) { // then fill gg and gp
    gg_array[i] = (g_array[4*i+3] + p_array[4*i+3]*g_array[4*i+2] + p_array[4*i+3]*p_array[4*i+2]*g_array[4*i+1] +
		   p_array[4*i+3]*p_array[4*i+2]*p_array[4*i+1]*g_array[4*i])%2;
    gp_array[i] = (p_array[4*i+3]*p_array[4*i+2]*p_array[4*i+1]*p_array[4*i])%2;
  }

  for (i = 0; i < 4; i++) { // fill sg and sp
    sg_array[i] = (gg_array[4*i+3] + gp_array[4*i+3]*gg_array[4*i+2] + gp_array[4*i+3]*gp_array[4*i+2]*gp_array[4*i+1]*gg_array[4*i])%2;
    sp_array[i] = (gp_array[4*i+3]*gp_array[4*i+2]*gp_array[4*i+1]*gp_array[4*i])%2;
    sc_array[i] = sg_array[i];
    if (i > 0) sc_array[i] += sp_array[i]*sc_array[i-1];
    sc_array[i] = sc_array[i]%2;
    // printf("%d,", sc_array[i]);
  }
  //printf("\n");

  for (i = 0; i < 16; i++) { // create gc array
    gc_array[i] = gg_array[i];
    if (i%4 == 0) {
      if (i > 0) gc_array[i] += gp_array[i] * sc_array[(i-4)/4];
    }
    else gc_array[i] += gp_array[i] * gc_array[i-1];
    gc_array[i] %= 2;
  }

  for (i = 0; i < 64; i++) { // fill c
    c_array[i] = g_array[i];
    if (i%4 == 0) {
      if (i > 0) c_array[i] += p_array[i]*gc_array[(i-4)/4];
    }
    else c_array[i] += p_array[i]*c_array[i-1];
    c_array[i] %= 2;
  }

  long result = 0;
  int multiplier = 1;
  for (i = 0; i < 64; i++) { // bring it all back together
    if (i == 0) result += ((x_array[i] + y_array[i])%2) * multiplier;
    else result += ((x_array[i] + y_array[i] + c_array[i-1])%2) * multiplier;
    multiplier *= 2;
  }
  return result;
}

int main()
{
  printf("%li\n%li\n%li", add(2380,2380),add(1230,3210), add(369963123, 12312398));
}
