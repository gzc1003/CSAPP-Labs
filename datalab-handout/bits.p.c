#line 142 "bits.c"
int bitOr(int x, int y) {

    return ~( ~x & ~y);
#line 1 "<command-line>"
#include "/usr/include/stdc-predef.h"
#line 145 "bits.c"
}
#line 152
int specialBits(void) {
    int x=  0xd7;
    int result=  x << 14;

    return ~result;
}
#line 166
int isZero(int x) {

    return !( 0 | x);
}
#line 177
int anyEvenBit(int x) {
    int a=  0x55;
    int b=  a +( a << 8);
    int c=  b +( b << 16);

    return !(!(x & c));
}
#line 191
int negate(int x) {

    return ~x + 1;
}
#line 203
int leastBitPos(int x) {
    return ((~x) + 1) & x;
}
#line 215
int rotateLeft(int x, int n) {
    int left=  x << n;
    int shift=  32 + ~n + 1;
    int tmp=  x >> shift;
    int right=  tmp +( tmp &( 1 << shift));
    return left + right;
}
#line 230
int divpwr2(int x, int n) {
    return x +(( x >> 31) &(( 1 << n) +( ~1) + 1)) >> n;
}
#line 240
int isLess(int x, int y) {

    return !!(x ^ y) &((( x & ~y + 1) >> 31 |( x + ~y + 1) >> 31) & 1);
}
#line 253
int isPower2(int x) {
    return (!((x >> 31) ^ 0)) &( !!x & !(x &( x + ~0)));
}
#line 264
int bitReverse(int x) {
    return 2;
}
#line 279
unsigned float_abs(unsigned uf) {
    unsigned x=  0x80000000;
    unsigned result=  uf;
    if (uf >> 31) 
        result = uf ^ x;
    if (((uf & 0x007fffff) > 0) &&(( uf & 0x7f800000) == 0x7f800000)) 
        result = uf;

    return result;
}
#line 298
unsigned float_i2f(int x) {
    unsigned sign=  x & 0x80000000;
    unsigned tmp;unsigned i;unsigned E;unsigned exp;unsigned frac;
    unsigned result=  0;
    if (x) 
    {
        if (sign) 
            x = -x;
        tmp = x;
        i = 0;
        while (tmp) {
            tmp >>= 1;
            i += 1;
        }
        E = i - 1;
        exp = E + 127;
        exp <<= 23;
        frac =( x -( 1 << i)) & 0x007fffff;
        result = sign + exp + frac;
        if (result & 1) 
            result += 1;
    }
    return result;
}
#line 333
unsigned float_times64(unsigned uf) {
    unsigned exp=  uf & 0x7f800000;
    unsigned sign=  uf & 0x80000000;
    unsigned frac=  uf & 0x007fffff;
    unsigned result;unsigned tmp;unsigned i;

    if (!(exp ^ 0x7f800000)) 
        result = uf;

    if (exp ^ 0x0) 
    {
        if (exp > 0x7e000000) 
            result = sign + 0x7f800000;
        if (exp < 0x7e800000) 
            result = uf + 0x03000000;
    }

    if (!(exp ^ 0x0)) 
    {
        if (frac < 0x00040000) 
            result =( frac << 6) + sign;
        if (frac > 0x0003ffff) 
        {
            tmp =( frac << 6) >> 23;
            i = 0;
            while (tmp) {
                tmp >>= 1;
                i += 1;
            }
            exp =( i-1) << 23;
            result = sign +( i << 23) +( frac >>( i - 1));
        }
    }

    return result;
}
