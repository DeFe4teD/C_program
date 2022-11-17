// 二次方程式の解
// 参考URL ↓
// c, c++で複素数:
// http://nalab.mind.meiji.ac.jp/~mk/labo/text/complex-c.pdf
// C言語 math.hをコンパイルする時に-lmが必要ないとき:
// https://hacknote.jp/archives/53903/

#include <stdio.h>
#include <math.h>
#include <complex.h>

// プログラム1
// ↓ math.hのみ。判別式の値に応じて場合分け ↓
// -------------------------------------------------------------------------------------------------

// int main(void){
//     double a, b, c, re, im;
//     scanf("%lf %lf %lf", &a, &b, &c);

//     double d = b * b - 4 * a * c;

//     re = - b / (2 * a);

//     if(d < 0){
//         double im = sqrt(-d) / (2 * a);
//         printf("解: %f ± %fi\n", re, im);
//     }else if(d > 0){
//         double im = sqrt(d) / (2 * a);
//         printf("解: %f ± %fi\n", re, im);
//     }else{
//         printf("解: %f\n", re);
//     }
    
// }

// -------------------------------------------------------------------------------------------------


// プログラム2 
// ↓ complex.hを使わずに。↓ 複素数の宣言: (floatとかdoubleとか型宣言) _Complex (変数名);
// 実部にアクセスするときは、__real__ (変数名), 虚部には__imag__ (変数名)
// 複素数aとbを足し、複素数cに代入。　
// -------------------------------------------------------------------------------------------------

// int main(void){
//     double _Complex a,b,c;
//     a = 1+2i;
//     printf("input Re b and Im b:");
//     scanf("%lf%lf", &__real__ b, &__imag__ b);
//     c = a + b;

// // 虚部が書式指定%fの前には、+を入れる。 %+f
//     printf("%f%+fi\n", __real__ c, __imag__ c);
//     return 0;
// }

// -------------------------------------------------------------------------------------------------


// プログラム3
// ↓ complex.hを使って。↓ 複素数の宣言: (floatとかdoubleとか型宣言) complex (変数名); complex.hを使わない場合と比べて、下線がなく、頭文字も小文字となる。
// 実部にアクセスするときは、creal(変数名)、虚部にはcimag(変数名)
// complex.hを使わない場合と比べて、下線がなく、頭文字も小文字。虚数単位使う時は I。
// -------------------------------------------------------------------------------------------------

// int main(void){
//     double complex a, b, c;
//     double re_b, im_b;
//     a = 1 + 2i;
    
//     printf("input Re b and Im b:");
//     scanf("%lf %lf", &re_b, &im_b);

//     b = re_b + im_b * I;

//     c = a - b;

//     //虚部が書式指定%fの前には、+を入れる。 %+f
//     printf("%f%+fi\n", creal(c), cimag(c));
//     return 0;
    
// }

// -------------------------------------------------------------------------------------------------