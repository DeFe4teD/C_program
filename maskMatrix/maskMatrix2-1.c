// nを最大31まで回すプログラム。 32桁までの0と1の系列を表現できる。余計な部分を削除。
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <string.h>
#include <stdbool.h>

// 連分数展開を行う関数。numeratorが分子, denominatorが分母。,fracSeriesに数列表記を配列で、sは数列表記の要素数。
void continued_fraction(int numerator, int denominator, int *fracSeries, int *s) {
    int index = 0;

    // 連分数展開の計算。ユークリッド互除法
    while (denominator != 0) {
        fracSeries[index++] = numerator / denominator;
        int temp = numerator;
        numerator = denominator;
        denominator = temp % denominator;
    }

    // 連分数展開の数列表記を出力。
    for (int i = 0; i < index; i++) {
        if (i < index - 1) {
        }
    }
    *s = index - 1;
}

// 最大公約数を求める関数
int gcd(int input1, int input2){

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
	return input2;
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
    int ans = 0;
    // ↓ Aを2進数変換した場合の桁数。
    int Adigits = binary_digit_count(A);
    // 1シフトにつき2進数表示の桁数だけシフト演算を行う。
    // シフト演算の回数についてはCon(A,x; B,y)のxだけシフト演算を行う。
    for(int i = 0; i < x; i++){
        ans = (ans << Adigits); //桁数だけシフト。
        ans += A; //シフトした後、同じ値を足す。これでCon(A,x; )の部分の操作を表す。
    }

    //Con( ; B,y)の部分についても同じ。
    int Bdigits = binary_digit_count(B);
    for(int i = 0; i < y; i++){
        ans = (ans << Bdigits);
        ans += B;
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

// ----------------------------------------------ここからスタート----------------------------------------------
int main(){
    for(int n = 2; n < 32; n++){ // nを2から最大31まで回す。
        for(int k = 1; k < n; k++){ // kを1から最大n-1まで回す。
            // nとkの最大公約数
            int g = gcd(n,k);
            // P,Qを配列で用意。P[0] = 1, Q[0] =0
            int P[200];
            int Q[200];
            P[0] = 1; Q[0] = 0;
            int i = 0; int j = 0;

//------------------------- step1 n/kの連分数展開(数列表記)を求める。----------------------------------------------
            // 連分数展開の数列表記を配列で用意。
            int fracSeries[200];
            // s: 連分数展開がどこで終わるか。次の関数でsに具体的な値が代入される。
            int s = 0;
            continued_fraction(n,k,fracSeries,&s);

//------------------------- step2 rho(=ρ0のこと),P1,Q1を求める。---------------------------------------------------
            // 配列P,Qには10進数(int型)で保存して、必要な時に2進数に変換する。
            if(fracSeries[0] == 1){ //(2a : x0 = 1の時)
                j = j + 1;
                int rho = fracSeries[1];
                P[1] = concatenate(P[0], rho,   Q[0], 1);
                Q[1] = concatenate(P[0], rho+1, Q[0], 1);
                // j == s であれば終了。

            }else{ //(2b : x0 > 1 の時)
                int rho = fracSeries[0] - 1;
                P[1] = concatenate(P[0], 1, Q[0], rho);
                Q[1] = concatenate(P[0], 1, Q[0], rho+1);
            }
            if(j == s){
//------------------------- ↓ step2 で終わる場合　↓ --------------------------------------------------------------------------------------
                // P = P1としてstep4へ
                
                // v = P^gを求める。P = P_i+1のこと
                int v = concatenate(P[i+1], g, 0, 0);

                int count = 0; // countにはP[i+1]が2進数表示で何ビット分かを保存する。 
                // P[i+1]の2進数表示で1である要素数をfind_set_bit関数を用いて代入する。
                int set_bits[200]; // P[i+1]の2進数表示で何ビット目が立っているか、find_set_bit関数を用いて順次格納する。
                find_set_bits(v, set_bits, &count);

                // vの立っているビットに対応する循環行列の行成分を抜き出す。
                // 循環行列A: n-k+1個の連続する成分が1,残りのk-1個の連続する成分が0である長さnのベクトルaに対するn×n循環行列Aのこと。
                // 循環行列Aの作成、2次元配列で
                int A[n][n];
                int a[n];
                // n - k + 1のこと。ベクトルaの連続する1の数。
                int one_bits_length = n - k + 1;

                for(int i = 0; i < one_bits_length; i++){
                    a[i] = 1;
                }
                
                for(int i = one_bits_length; i < n; i++){
                    a[i] = 0;
                }

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

                int mask_matrix[k][n];
                for(int i = count - 1; i >= 0; i--) {
                    for(int j = 0; j < n; j++){
                        mask_matrix[k-1-i][j] = A[n - 1 - set_bits[i]][j];
                    }
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

                int b_floor = floor(((double)k*(n-k+1))/n);
                int b_ceil = ceil(((double)k*(n-k+1))/n);
                
                // 各列の重みがb_floorかb_ceilになっているか確認。
                for(int i = 0; i < n; i++){
                    if(columnWeights[i] != b_floor && columnWeights[i] != b_ceil){
                        printf("%d,%d \t失敗。\n",n,k);
                        return 0;
                    }
                }

                printf("%d,%d \t成功。\n",n,k);
                continue;

            }
//------------------------- ↑ step2 で終わる場合-----------------------------------------------------------------------------------

            // j != s であれば i = i + 1, j = j + 1 としてstep3へ
            i++;
            j++;

//------------------------- step3 rho(=ρiのこと), P_i+1, Q_i+1 を求める。-----------------------------------------------
            while(1){ // j == sになるまで繰り返し。
                if(fracSeries[j] == 1){ //(3a : xj = 1の時)
                j = j + 1;
                int rho = fracSeries[j];
                // // printf("%d",r);
                P[i+1] = concatenate(P[i], 1,   Q[i], rho);
                Q[i+1] = concatenate(P[i], 1, Q[i], rho+1);

                }else{ //(3b : xj > 1 の時)
                    int rho = fracSeries[j] - 1;
                    // // printf("r = %d\n",r);
                    P[i+1] = concatenate(P[i], rho, Q[i], 1);
                    Q[i+1] = concatenate(P[i], rho+1, Q[i], 1);
                }
                if(j == s){
                    // P = P_i+1としてstep4へ
                    break;
                }
                // j != s であれば i = i + 1, j = j + 1 としてstep3へ(繰り返し)
                i ++;
                j ++;
            }

//------------------------- step4 --------------------------------------------------------------------------------
            int v = concatenate(P[i+1], g, 0, 0);

            int count = 0; // countにはP[i+1]が2進数表示で何ビット分かを保存する。 
            // P[i+1]の2進数表示で1である要素数をfind_set_bit関数を用いて代入する。
            int set_bits[200]; // P[i+1]の2進数表示で何ビット目が立っているか、find_set_bit関数を用いて順次格納する。
            find_set_bits(v, set_bits, &count);

            // vの立っているビットに対応する循環行列の行成分を抜き出す。
            // 循環行列A: n-k+1個の連続する成分が1,残りのk-1個の連続する成分が0である長さnのベクトルaに対するn×n循環行列Aのこと。
            // 循環行列Aの作成、2次元配列で
            int A[n][n];
            int a[n];
            // n - k + 1のこと。ベクトルaの連続する1の数。
            int one_bits_length = n - k + 1;

            for(int i = 0; i < one_bits_length; i++){
                a[i] = 1;
            }
            
            for(int i = one_bits_length; i < n; i++){
                a[i] = 0;
            }

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

            int mask_matrix[k][n];
            for(int i = count - 1; i >= 0; i--) {
                for(int j = 0; j < n; j++){
                    mask_matrix[k-1-i][j] = A[n - 1 - set_bits[i]][j];
                }
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

            int b_floor = floor(((double)k*(n-k+1))/n);
            int b_ceil = ceil(((double)k*(n-k+1))/n);
            
            // 各列の重みがb_floorかb_ceilになっているか確認。
            for(int i = 0; i < n; i++){
                if(columnWeights[i] != b_floor && columnWeights[i] != b_ceil){
                    printf("%d,%d \t失敗。\n",n,k);
                    return 0;
                }
            }

            printf("%d,%d \t成功。\n",n,k);
            continue;

        }
    }
    return 0;
    
}