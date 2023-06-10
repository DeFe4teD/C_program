#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <string.h>
#include <stdbool.h>

// 連分数展開を行う関数。numeratorが分子, denominatorが分母。,fracSeriesに数列表記を配列で、sは数列表記の要素数。
void continued_fraction(int numerator, int denominator, int *fracSeries, int *s) {
    int index = 0;
    printf("%d/%dの連分数展開の数列表記: [",numerator ,denominator);

    // 連分数展開の計算。ユークリッド互除法？
    while (denominator != 0) {
        fracSeries[index++] = numerator / denominator;
        int temp = numerator;
        numerator = denominator;
        denominator = temp % denominator;
    }

    // 連分数展開の数列表記を出力。
    for (int i = 0; i < index; i++) {
        printf("%d", fracSeries[i]);
        if (i < index - 1) {
            printf(", ");
        }
    }
    printf("]\n");
    // printf("%d\n",index);
    *s = index - 1;
}

// 最大公約数を求める関数
int gcd(int input1, int input2){
    int initialInput1 = input1;
    int initialInput2 = input2;
    if(input1 > input2){
        int temp = input1;
        input1 = input2;
        input2 = temp;
    }

    //input2が割られる数、input1が割る数
    //ユークリッド互助法
    int remainder = 1;
    while(remainder > 0){
        remainder = input2 % input1;
        input2 = input1;
        input1 = remainder;
    }

    printf("%dが%dと%dの最大公約数\n",input2, initialInput1, initialInput2);

	return input2;
}

// 入力した10進数を2進数で表示するプログラム。
void decimal_to_binary(int n) {
    // sizeof演算子は指定した型またはオブジェクトのサイズ(バイト単位)を返します。31ビット目から0ビット目まで。
    unsigned mask = 1 << (sizeof(int) * 8 - 1); // 高位からビットを調べるためのマスクを設定

    printf("%dの2進数表記: ", n);

    // mask >>= 1 は maskを右に1ビットシフトしたものを再びmaskに代入してるということ。÷2と一緒。
    for (; mask; mask >>= 1) { // maskを右シフトして、順に各ビットを調べる
        printf("%d", (n & mask) ? 1 : 0); // ビットが立っていれば1、そうでなければ0を出力
    }

    printf("\n");
}

// 2進数表示したときの桁数を求めるプログラム。
int binary_digit_count(int n) {
    // 値が0の時は、桁数1を返す。
    if(n == 0){
        return 1;
    }

    int count = 0;
    while(n) {
        n /= 2;
        count++;
    }
    return count;
}

// Con(A,x ; B,y) = A^xB^yの操作を行う関数。
int concatenate(int A, int x, int B, int y){
    // printf("A = %d\n",A);
    // printf("B = %d\n",B);
    int ans = 0;
    // ↓ Aを2進数変換した場合の桁数。
    int Adigits = binary_digit_count(A);
    // 1シフトにつき2進数表示の桁数だけシフト演算を行う。
    // シフト演算の回数についてはCon(A,x; B,y)のxだけシフト演算を行う。
    for(int i = 0; i < x; i++){
        ans = (ans << Adigits); //桁数だけシフト。
        ans += A; //シフトした後、同じ値を足す。これでCon(A,x; )の部分の操作を表す。
        // printf("ans = %d\n",ans);
    }

    //Con( ; B,y)の部分についても同じ。
    int Bdigits = binary_digit_count(B);
    for(int i = 0; i < y; i++){
        ans = (ans << Bdigits);
        ans += B;
        // printf("ans = %d\n",ans);
    }

    // 求めたい値の10進数表示を返す。
    return ans;
}

// 立っているビットの位置を配列に格納する関数
void find_set_bits(int n, int set_bits[], int *count) {
    *count = 0;
    int pos = 0;
    
    while(n > 0) {
        // 最下位ビットが立っているかチェック
        if(n & 1) {
            set_bits[*count] = pos;
            (*count)++;
        }

        // 次のビットへ移動
        n >>= 1;
        pos++;
    }
}

// 各列の重みを計算する関数。 引数は2次元配列[k][n] x行y列はx*n+yと指定
// bool calculateColumnWeights(int *maskMatrix, int *columnWeights){

// }

// ----------------------------------------------ここからスタート----------------------------------------------
int main(){
    // step0 初期値を設定する。
    printf("---------------------------------------------------------------\n");
    printf("        ↓ step0 ↓\n");
    int n,k;    
    printf("n = ");
    scanf("%d",&n);
    printf("k = ");
    scanf("%d",&k);
    printf("%d %d\n",n,k);
    // nとkの最大公約数
    int g = gcd(n,k);
    // P,Qを配列で用意。P[0] = 1, Q[0] =0
    int P[200];
    int Q[200];
    P[0] = 1; Q[0] = 0;
    int i = 0; int j = 0;

    // step1 n/kの連分数展開(数列表記)を求める。
    printf("---------------------------------------------------------------\n");
    printf("        ↓ step1 ↓\n");
    // 連分数展開の数列表記を配列で用意。
    int fracSeries[200];
    // s: 連分数展開がどこで終わるか。次の関数でsに具体的な値が代入される。
    int s = 0;
    continued_fraction(n,k,fracSeries,&s);
    printf("連分数展開の数列表記は0から数えて%d番目まである。s = %d\n",s,s);
    // for(int i = 0; i < 10; i++){
    //     printf("%d ",fracSeries[i]);
    // }

    // step2 r(=ρ0のこと),P1,Q1を求める。
    printf("---------------------------------------------------------------\n");
    printf("        ↓ step2 ↓\n");
    // 配列P,Qには10進数(int型)で保存して、必要な時に2進数に変換する。
    if(fracSeries[0] == 1){ //(2a : x0 = 1の時)
        j = j + 1;
        int r = fracSeries[1];
        // printf("%d",r);
        P[1] = concatenate(P[0], r,   Q[0], 1);
        Q[1] = concatenate(P[0], r+1, Q[0], 1);
        // j == s であれば終了。

    }else{ //(2b : x0 > 1 の時)
        int r = fracSeries[0] - 1;
        // printf("r = %d\n",r);
        P[1] = concatenate(P[0], 1, Q[0], r);
        Q[1] = concatenate(P[0], 1, Q[0], r+1);
    }
    if(j == s){
        // P = P1としてstep4へ
        // P = P_i+1としてstep4へ
        printf("P = %d\n", P[i+1]);
        printf("Q = %d\n", Q[i+1]);
        decimal_to_binary(P[i+1]);
        decimal_to_binary(Q[i+1]);

    // step2 で終わる場合　↓ --------------------------------------------------------------------------------------
    printf("---------------------------------------------------------------\n");
    printf("        ↓ step4 ↓\n");
    // v = P^gを求める。P = P_i+1のこと
    int v = concatenate(P[i+1], g, 0, 0);
    printf("v = %d\n",v);
    decimal_to_binary(v);

    int count = 0; // countにはP[i+1]が2進数表示で何ビット分かを保存する。 
    // P[i+1]の2進数表示で1である要素数をfind_set_bit関数を用いて代入する。
    int set_bits[200]; // P[i+1]の2進数表示で何ビット目が立っているか、find_set_bit関数を用いて順次格納する。
    find_set_bits(v, set_bits, &count);
    printf("vの2進数表示の内で、0ビットから数えて何ビット目が立っているか: ");
    for(int i = 0; i < count; i++) {
        printf("%d ", set_bits[i]);
    }
    printf("\n");

    // vの立っているビットに対応する循環行列の行成分を抜き出す。
    // 循環行列A: n-k+1個の連続する成分が1,残りのk-1個の連続する成分が0である長さnのベクトルaに対するn×n循環行列Aのこと。
    // 循環行列Aの作成、2次元配列で
    int A[n][n];
    int a[n];
    // n - k + 1のこと。ベクトルaの連続する1の数。
    int one_bits_length = n - k + 1;
    // k - 1のこと。ベクトルaの連続する0の数。
    int zero_bits_length = k - 1;


    for(int i = 0; i < one_bits_length; i++){
        a[i] = 1;
    }
    
    for(int i = one_bits_length; i < n; i++){
        a[i] = 0;
    }

    // ベクトルaを作成。
    printf("ベクトルa (循環行列を求めるのに使う) :");
    for(int i = 0; i < n; i++){
        printf("%d ",a[i]);
    }
    printf("\n");

    // Aの一行目
    for(int i = 0; i < n; i++){
        A[0][i] = a[i];
    }

    int startPos = 0; // ベクトルaのどこから代入し始めるかを表す変数。
    for(int i = 1; i < n; i++){
        startPos ++;
        for(int j = 0; j < n; j++){
            A[i][j] = a[(j + startPos) % n];
        }
    }
    printf("n x n の循環行列: (連続する1の成分はn-k+1個、連続する0の成分はk-1個)\n");
    for(int i = 1; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ",A[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    int mask_matrix[k][n];
    for(int i = count - 1; i >= 0; i--) {
        for(int j = 0; j < n; j++){
            mask_matrix[k-1-i][j] = A[n - 1 - set_bits[i]][j];
        }
    }

    // マスク行列の出力
    printf("求めたマスク行列 ↓\n");
    for(int i = 0; i < k; i++){
        for(int j = 0; j < n; j++){
            printf("%d ",mask_matrix[i][j]);
        }
        printf("\n");
    }

    // // bfである要素がm個、bcである要素がn-m個であるような長さnのベクトルb。実際にbが計算できるか
    // // vA = bの計算 (v = p[i+1], Aは循環行列)
    // int b[n];
    // for(int i = 0; i < n; i++){ 
    //     b[i] = 0;
    // }

    // for(int k = 0; k < n; k++){ // iはAの何列目と積をとっているかを示す。
    //     for(int l = 0; l < n; l++){ // jはAの何行目かを指定。
    //         b[k] += P[i+1] * A[k][l];
    //     }
    // }

    // printf("配列b:\n");
    // for(int i = 0; i < n; i++){ 
    //     printf("%d ",b[i]);
    // }

    // マスク行列の各列の重みを計算する。
    int columnWeights[n];
    for(int i = 0; i < n; i++){
        columnWeights[i] = 0; 
    }

    for(int i = 0; i < k; i++){
        for(int j = 0; j < n; j++){
            if(mask_matrix[i][j] == 1){
                columnWeights[j]++;
            }
        }
    }

    printf("各列の重み: ");
    for(int i = 0; i < n; i++){
        printf("%d ", columnWeights[i]);
    }
    printf("\n");

    int b_floor = floor(((double)k*(n-k+1))/n);
    int b_ceil = ceil(((double)k*(n-k+1))/n);

    printf("b_floor: %d, b_ceil: %d\n", b_floor, b_ceil);
    
    // 各列の重みがb_floorかb_ceilになっているか確認。
    for(int i = 0; i < n; i++){
        if(columnWeights[i] != b_floor && columnWeights[i] != b_ceil){
            printf("各列の重みが正しくないマスク行列です。\n");
            return 0;
        }
    }

    printf("各列の重みが正しいマスク行列です。\n");
    return 0;

    }
    // ↑ step2 で終わる場合-----------------------------------------------------------------------------------

    // j != s であれば i = i + 1, j = j + 1 としてstep3へ
    i++;
    j++;
    
    // テスト P1,Q1とかを出力できるかどうか。
    printf("i = %d\n",i);
    printf("j = %d\n",j);
    printf("%d\n",binary_digit_count(1));
    printf("P0 = %d\n", P[0]);
    printf("Q0 = %d\n", Q[0]);
    printf("P1 = %d\n", P[1]);
    printf("Q1 = %d\n", Q[1]);
    decimal_to_binary(P[1]);
    decimal_to_binary(Q[1]);

    // step3 r(=ρiのこと), P_i+1, Q_i+1 を求める。
    printf("---------------------------------------------------------------\n");
    printf("        ↓ step3 ↓\n");
    while(1){ // j == sになるまで繰り返し。
        if(fracSeries[j] == 1){ //(3a : xj = 1の時)
        j = j + 1;
        int r = fracSeries[j];
        // printf("%d",r);
        P[i+1] = concatenate(P[i], 1,   Q[i], r);
        Q[i+1] = concatenate(P[i], 1, Q[i], r+1);

        }else{ //(3b : xj > 1 の時)
            int r = fracSeries[j] - 1;
            // printf("r = %d\n",r);
            P[i+1] = concatenate(P[i], r, Q[i], 1);
            Q[i+1] = concatenate(P[i], r+1, Q[i], 1);
        }
        if(j == s){
            // P = P_i+1としてstep4へ
            printf("P = %d\n", P[i+1]);
            printf("Q = %d\n", Q[i+1]);
            decimal_to_binary(P[i+1]);
            decimal_to_binary(Q[i+1]);
            break;
        }
        // j != s であれば i = i + 1, j = j + 1 としてstep3へ(繰り返し)
        i ++;
        j ++;
    }

    printf("---------------------------------------------------------------\n");
    printf("        ↓ step4 ↓\n");
    // v = P^gを求める。P = P_i+1のこと
    int v = concatenate(P[i+1], g, 0, 0);
    printf("v = %d\n",v);
    decimal_to_binary(v);

    int count = 0; // countにはP[i+1]が2進数表示で何ビット分かを保存する。 
    // P[i+1]の2進数表示で1である要素数をfind_set_bit関数を用いて代入する。
    int set_bits[200]; // P[i+1]の2進数表示で何ビット目が立っているか、find_set_bit関数を用いて順次格納する。
    find_set_bits(v, set_bits, &count);
    printf("vの2進数表示の内で、0ビットから数えて何ビット目が立っているか: ");
    for(int i = 0; i < count; i++) {
        printf("%d ", set_bits[i]);
    }
    printf("\n");

    // vの立っているビットに対応する循環行列の行成分を抜き出す。
    // 循環行列A: n-k+1個の連続する成分が1,残りのk-1個の連続する成分が0である長さnのベクトルaに対するn×n循環行列Aのこと。
    // 循環行列Aの作成、2次元配列で
    int A[n][n];
    int a[n];
    // n - k + 1のこと。ベクトルaの連続する1の数。
    int one_bits_length = n - k + 1;
    // k - 1のこと。ベクトルaの連続する0の数。
    int zero_bits_length = k - 1;


    for(int i = 0; i < one_bits_length; i++){
        a[i] = 1;
    }
    
    for(int i = one_bits_length; i < n; i++){
        a[i] = 0;
    }

    // ベクトルaを作成。
    printf("ベクトルa (循環行列を求めるのに使う) :");
    for(int i = 0; i < n; i++){
        printf("%d ",a[i]);
    }
    printf("\n");

    // Aの一行目
    for(int i = 0; i < n; i++){
        A[0][i] = a[i];
    }

    int startPos = 0; // ベクトルaのどこから代入し始めるかを表す変数。
    for(int i = 1; i < n; i++){
        startPos ++;
        for(int j = 0; j < n; j++){
            A[i][j] = a[(j + startPos) % n];
        }
    }

    printf("n x n の循環行列: (連続する1の成分はn-k+1個、連続する0の成分はk-1個)\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ",A[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    int mask_matrix[k][n];
    for(int i = count - 1; i >= 0; i--) {
        for(int j = 0; j < n; j++){
            mask_matrix[k-1-i][j] = A[n - 1 - set_bits[i]][j];
        }
    }

    // マスク行列の出力
    printf("求めたマスク行列 ↓\n");
    for(int i = 0; i < k; i++){
        for(int j = 0; j < n; j++){
            printf("%d ",mask_matrix[i][j]);
        }
        printf("\n");
    }

    // マスク行列の各列の重みを計算する。
    int columnWeights[n];
    for(int i = 0; i < n; i++){
        columnWeights[i] = 0; 
    }

    for(int i = 0; i < k; i++){
        for(int j = 0; j < n; j++){
            if(mask_matrix[i][j] == 1){
                columnWeights[j]++;
            }
        }
    }

    printf("各列の重み: ");
    for(int i = 0; i < n; i++){
        printf("%d ", columnWeights[i]);
    }
    printf("\n");

    int b_floor = floor(((double)k*(n-k+1))/n);
    int b_ceil = ceil(((double)k*(n-k+1))/n);

    printf("b_floor: %d, b_ceil: %d\n", b_floor, b_ceil);
    
    // 各列の重みがb_floorかb_ceilになっているか確認。
    for(int i = 0; i < n; i++){
        if(columnWeights[i] != b_floor && columnWeights[i] != b_ceil){
            printf("各列の重みが正しくないマスク行列です。\n");
            return 0;
        }
    }

    printf("各列の重みが正しいマスク行列です。\n");
    return 0;
}