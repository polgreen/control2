#include <stdio.h>
typedef __CPROVER_fixedbv[32][16] __CPROVER_EIGEN_fixedbvt;

extern const __CPROVER_fixedbv[24][12] __m[2][2];

__CPROVER_EIGEN_fixedbvt __CPROVER_EIGEN_poly[3];
void __CPROVER_EIGEN_charpoly_2(void) { //m00*m11 - m10*m11 - m00*x - m11*x + x^2

  __CPROVER_EIGEN_poly[2] = __m[0][0]*__m[1][1] - __m[1][0]*__m[1][1];

  __CPROVER_EIGEN_poly[1] = -__m[0][0] - __m[1][1];
  // s^2
  __CPROVER_EIGEN_poly[0] = 1.0;
}

__CPROVER_EIGEN_fixedbvt internal_pow(__CPROVER_EIGEN_fixedbvt a, unsigned int b){

   __CPROVER_EIGEN_fixedbvt acc = 1.0;
   for (int i=0; i < b; i++){
    acc = acc*a;
   }
   return acc;
}

__CPROVER_EIGEN_fixedbvt internal_abs(__CPROVER_EIGEN_fixedbvt a){
   return a < 0 ? -a : a;
}


int check_stability(void){

#define __a __CPROVER_EIGEN_poly
#define __n 3u
   int lines = 2 * __n - 1;
   int columns = __n;
   __CPROVER_EIGEN_fixedbvt m[lines][__n];
   int i,j;

   __CPROVER_EIGEN_fixedbvt current_stability[__n];
   for (i=0; i < __n; i++){
     current_stability[i] = __a[i];
   }

   __CPROVER_EIGEN_fixedbvt sum = 0;
   for (i=0; i < __n; i++){
     sum += __a[i];
   }
   if (sum <= 0){
  printf("[DEBUG] the first constraint of Jury criteria failed: (F(1) > 0)");
     return 0;
   }

   sum = 0;
   for (i=0; i < __n; i++){
    sum += __a[i] * internal_pow(-1, __n-1-i);
   }
   sum = sum * internal_pow(-1, __n-1);
   if (sum <= 0){
    printf("[DEBUG] the second constraint of Jury criteria failed: (F(-1)*(-1)^n > 0)");
    return 0;
   }

   if (internal_abs(__a[__n-1]) > __a[0]){
     printf("[DEBUG] the third constraint of Jury criteria failed: (abs(a0) < a_{n}*z^{n})");
     return 0;
   }

   for (i=0; i < lines; i++){
    for (j=0; j < columns; j++){
     m[i][j] = 0;
    }
   }
   for (i=0; i < lines; i++){
    for (j=0; j < columns; j++){
     if (i == 0){
      m[i][j] = __a[j];
      continue;
     }
     if (i % 2 != 0 ){
       int x;
       for(x=0; x<columns;x++){
        m[i][x] = m[i-1][columns-x-1];
       }
       columns = columns - 1;
      j = columns;
     }else{
      m[i][j] = m[i-2][j] - (m[i-2][columns] / m[i-2][0]) * m[i-1][j];
     }
    }
   }
   int first_is_positive =  m[0][0] >= 0 ? 1 : 0;
   for (i=0; i < lines; i++){
    if (i % 2 == 0){
     int line_is_positive = m[i][0] >= 0 ? 1 : 0;
     if (first_is_positive != line_is_positive){
      return 0;
     }
     continue;
    }
   }
   return 1;
}

void find_eigenvalues()
{
	__CPROVER_EIGEN_fixedbvt T, det, imag, real, eig1, eig2, root;

	det = __m[0][0]*__m[1][1]  - __m[1][0]*__m[0][1];
	T = __m[0][0] +__m[1][1];
	imag = T*T/4 - det;
	__CPROVER_assume(imag >0);

	__CPROVER_assume(root*root == imag);
	eig1 = T/2 + root;
	eig2 = T/2 -root;


	__CPROVER_assume(eig1<1 && eig1 >-1);
	__CPROVER_assume(eig2<1 && eig2 >-1);
}



void multiply_matrices()
{
	__CPROVER_EIGEN_fixedbvt	x,y, xp, yp, x_test, y_test, xp_test, yp_test;

x = 1;
y = 1;
int n=10;
for(int i=0; i<n; i++)
{

	xp = __m[0][0]*x + __m[0][1]*y;
	yp = __m[1][0]*x + __m[1][1]*y;
	x = xp;
	y = yp;
	__CPROVER_assume(x<=1 && y<=1 && x>=-1 && y>=-1);
}

x = -1;
y = 1;
for(int i=0; i<n; i++)
{

	xp = __m[0][0]*x + __m[0][1]*y;
	yp = __m[1][0]*x + __m[1][1]*y;
	x = xp;
	y = yp;
	__CPROVER_assume(x<=1 && y<=1 && x>=-1 && y>=-1);
}
x = -1;
y = -1;
for(int i=0; i<n; i++)
{

	xp = __m[0][0]*x + __m[0][1]*y;
	yp = __m[1][0]*x + __m[1][1]*y;
	x = xp;
	y = yp;
	__CPROVER_assume(x<=1 && y<=1 && x>=-1 && y>=-1);
}

x = 1;
y = -1;
for(int i=0; i<n; i++)
{

	xp = __m[0][0]*x + __m[0][1]*y;
	yp = __m[1][0]*x + __m[1][1]*y;
	x = xp;
	y = yp;
	__CPROVER_assume(x<=1 && y<=1 && x>=-1 && y>=-1);
}

x_test;
y_test;
__CPROVER_assume(x_test<=1 && y_test<=1 && x_test>=-1 && y_test>=-1);
for(int i=0; i<n; i++)
{

	xp_test = __m[0][0]*x_test + __m[0][1]*y_test;
	yp_test = __m[1][0]*x_test + __m[1][1]*y_test;
	x_test = xp_test;
	y_test = yp_test;
	__CPROVER_assert(x_test<=1 && y_test<=1 && x_test>=-1 && y_test>=-1, "");
}





}


void main(void)
{
	int greaterthanone = 0;

	//__CPROVER_EIGEN_charpoly_2();
	//__CPROVER_assume(check_stability()==1);

	/*find_eigenvalues();
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<2; j++)
		{
			__CPROVER_assume(__m[i][j]<10 && __m[i][j]>-10);
			if(__m[i][j]>1 || __m[i][j] <-1 )
			{
				greaterthanone=1;
			}
		}
	}*/


__CPROVER_EIGEN_fixedbvt trace_m00 = __m[0][0];
__CPROVER_EIGEN_fixedbvt trace_m01 = __m[0][1];
__CPROVER_EIGEN_fixedbvt trace_m10 = __m[1][0];
__CPROVER_EIGEN_fixedbvt trace_m11 = __m[1][1];

multiply_matrices();
	//__CPROVER_assert(greaterthanone==0, "");



}
