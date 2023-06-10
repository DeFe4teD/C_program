// C言語ポインタ完全制覇 1章

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<complex.h>
#include <string.h>

/* 
p42
    intへのポインタ型や、doubleへのポインタ型など、他の型からの派生でポインタ型が作られる。
    ポインタ型の変数とポインタ型の値がある。
p45
    ポインタ型の値をprintf()で表示する場合は、%pを使います。
    %pに対しては、voidへのポインタを指定することになっているので、p44プログラムのところでは、void*にキャストしている。
p47
    point
    ・変数に&演算子を適用すると、その変数のアドレスが取得できる。このアドレスのことをその変数へのポインタと呼ぶ。
    ・ポインタ変数hoge_pが別の変数hogeへのポインタを保持しているとき、「hoge_pがhogeを指している」という。
    ・ポインタに*演算子を適用すると、そのポインタの指している先のものをあらわすようになる。hoge_pがhogeを指しているなら、
        *hoge_pは,hogeと同じものを表す。
p48
    宣言の時の*や[]は、式の中に現れる演算子の*や[]とは、まったくの別物です。
    *a = 5の*は間接演算子、int *hoge_p;の*区切り子の範疇に入る。
p52
    ポインタ型と整数型は同じではない？
    void* どんなデータ型でもお構いなしに指せるポインタ型。
    どんな型かわからないので、指している値はそのままではとりだせない。→ 〇〇へのポインタにキャストすることで取り出せる。


*/


int main(){
    // ------↓ p44 プログラム ↓------

    // int hoge = 5;
    // int piyo = 10;
    // int *hoge_p; // intへのポインタ型 hoge_p

    // // それぞれの変数のアドレスを表示。ここで表示している「アドレス」がすなわち「ポインタ型の値」そのもの(?)
    // printf("&hoge..%p\n", (void*)&hoge);
    // printf("&piyo..%p\n", (void*)&piyo);
    // printf("&hoge_p..%p\n", (void*)&hoge_p); // この時点で未設定。

    // // ポインタ変数hoge_pにhogeのアドレスを代入
    // hoge_p = &hoge;
    // printf("hoge_p..%p\n", (void*)hoge_p);

    // // hoge_pを経由してhogeの値を表示する。
    // printf("&hoge_p..%d\n", *hoge_p);

    // // hoge_pを経由してhogeの値を変更する。
    // *hoge_p = 10;
    // printf("hoge..%d\n",hoge);

    // return 0;

    // ------↑ p44 プログラム ↑------

/*
p56
    Cではポインタに1加算すると、、そのアドレスは "そのポインタが指す型のサイズだけ" 増加します。
    intのサイズが4なので、1加算すると4バイト、3加算すると12バイト進みました。
*/

    // ------↓ p55 プログラム ↓------(ポインタ演算: ポインタに整数を足し引きしたり、ポインタ同士で引き算を行う機能。)

    int hoge;
    int *hoge_p;

    hoge_p = &hoge;
    printf("hoge_p..%p\n", (void*)hoge_p);
    hoge_p++; // hoge_pに1を加算。
    printf("hoge_p..%p\n", (void*)hoge_p);
    printf("hoge_p..%p\n", (void*)(hoge_p + 3)); // hoge_pに3加算した値を表示。

    return 0;

    
}