// ビット計算を使わず、int型の配列で考える。
// nとkをfor文で回す。
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// 連分数展開を行う関数。numeratorが分子, denominatorが分母。,fracSeriesに数列表記を配列で、sは数列表記の要素数。
void continued_fraction(long long numerator, long long denominator, long long *fracSeries, long long *s) {
    long long index = 0;

    // 連分数展開の計算。ユークリッド互除法
    while (denominator != 0) {
        fracSeries[index++] = numerator / denominator;
        long long temp = numerator;
        numerator = denominator;
        denominator = temp % denominator;
    }

    *s = index - 1;
}

// 最大公約数を求める関数
long long gcd(long long input1, long long input2){

    if(input1 > input2){
        long long temp = input1;
        input1 = input2;
        input2 = temp;
    }

    //input2が割られる数、input1が割る数
    //ユークリッド互助法 余りが1になれば終了。
    long long remainder = 1;
    while(remainder > 0){
        remainder = input2 % input1;
        input2 = input1;
        input1 = remainder;
    }
	return input2;
}

int main(void){
// ------ step 0 および step 1 (初期値の設定、n/kの連分数展開の計算) ------
    long long n,k;
    printf("n = ");
    scanf("%lld",&n);
    printf("k = ");
    scanf("%lld",&k);
    
    long long g = gcd(n,k);
    int i = 0;
    int j = 0;
    long long fracSeries[300]; // 連分数展開の数列表記を保存。
    long long s; // 数列表記の項数(0から数えて)。
    continued_fraction(n, k, fracSeries, &s);   

    int* ptrToPQ[s+2][2]; // 各ステップごとのPとQを格納する1次元配列へのポインタを格納する。[][0]にはP,[][1]にはQを
    for(int k = 0; k < s + 2; k++){
        ptrToPQ[k][0] = NULL;
        ptrToPQ[k][1] = NULL;
    }

// ------ step2 ------
    // 各ステップごとにPとQを格納するのに必要な長さを計算する。
    int PQlen[s+2][2]; // 各ステップごと(1つ目の添え字)に、PとQに必要な長さを格納する。2つ目の添え字[0]にはPの長さ、[1]にはQの長さ
    PQlen[0][0] = 1; PQlen[0][1] =  1;
    ptrToPQ[0][0] = (int*)malloc(sizeof(int) * 1); // P0を表す配列へのポインタ
    ptrToPQ[0][1] = (int*)malloc(sizeof(int) * 1); // Q0を表す配列へのポインタ
    *ptrToPQ[0][0] = 1; // P0 = 1
    *ptrToPQ[0][1] = 0; // Q0 = 0

    if(fracSeries[0] == 1){ // (2a) x0 == 1 のとき
        j = j + 1;
        int rho_0 = fracSeries[1]; // rho_0 = x1
        PQlen[1][0] = rho_0 + 1; // P1 = Con(P0, rho_0     ; Q0, 1)
        PQlen[1][1] = rho_0 + 2; // Q1 = Con(P0, rho_0 + 1 ; Q0, 1)
        ptrToPQ[1][0] = (int*)malloc(sizeof(int) * PQlen[1][0]);
        ptrToPQ[1][1] = (int*)malloc(sizeof(int) * PQlen[1][1]);

    }else{ // (2b) x0 > 1 のとき
        int rho_0 = fracSeries[0] - 1; // rho0 = x0 - 1
        PQlen[1][0] = rho_0 + 1; // P1 = Con(P0, 1 ; Q0, rho_0)
        PQlen[1][1] = rho_0 + 2; // Q1 = Con(P0, 1 ; Q0, rho_0 + 1)
        ptrToPQ[1][0] = (int*)malloc(sizeof(int) * PQlen[1][0]);
        ptrToPQ[1][1] = (int*)malloc(sizeof(int) * PQlen[1][1]);
    }

// ------ step3 ------
    if(j != s){
        i++; j++;
        while(1){
            if(fracSeries[j] == 1){ //(3a : xj = 1の時)
                j = j + 1;
                int rho_i = fracSeries[j];
                PQlen[i + 1][0] = PQlen[i][0] * 1 + PQlen[i][1] * rho_i; // P_i+1 =Con(P_i, 1 ; Q_i, rho_i)
                PQlen[i + 1][1] = PQlen[i][0] * 1 + PQlen[i][1] * (rho_i + 1); // P_i+1 =Con(P_i, 1 ; Q_i, rho_i + 1)
                ptrToPQ[i + 1][0] = (int*)malloc(sizeof(int) * PQlen[i + 1][0]);
                ptrToPQ[i + 1][1] = (int*)malloc(sizeof(int) * PQlen[i + 1][1]);
            }else{ //(3b : xj > 1 の時)
                int rho_i = fracSeries[j] - 1;
                PQlen[i + 1][0] = PQlen[i][0] * rho_i       + PQlen[i][1] * 1; // P_i+1 =Con(P_i, 1 ; Q_i, rho_i)
                PQlen[i + 1][1] = PQlen[i][0] * (rho_i + 1) + PQlen[i][1] * 1; // P_i+1 =Con(P_i, 1 ; Q_i, rho_i + 1)
                ptrToPQ[i + 1][0] = (int*)malloc(sizeof(int) * PQlen[i + 1][0]);
                ptrToPQ[i + 1][1] = (int*)malloc(sizeof(int) * PQlen[i + 1][1]);
            }
            if(j == s){
                // P = P_i+1としてstep4へ
                break;
            }
            // j != s であれば i = i + 1, j = j + 1 としてstep3へ(繰り返し)
            i ++;
            j ++;
        }
    }

// ------ テスト ------
    // printf("i = %d, j = %d, s = %lld\n",i ,j ,s);
    
    for(int k = 0; k < i + 2; k++){
        printf("P[%d]の長さ: %d, Q[%d]の長さ: %d",k ,PQlen[k][0], k, PQlen[k][1] );
        printf("\n");
    }

    printf("P[0] = %d\n",*ptrToPQ[0][0]);
    printf("Q[0] = %d\n",*ptrToPQ[0][1]);
// --------------------

    i = 0; j = 0; //　元に戻す。

// 実際に1と0の系列を計算する。
// ------ step2 ------
    if(fracSeries[0] == 1){ // (2a) x0 == 1 のとき
        // P1 = Con(P0, rho_0     ; Q0, 1)

        // printf("%p \n",(void*)(ptrToPQ[1][0])); // ptrToPQ[1][0]のアドレス出力
        j = j + 1;
        int rho_0 = fracSeries[1]; // rho_0 = x1
        int count = 0;

        for(int k = 0; k < rho_0; k++){ // Con(P0, rho_0 ;)、連結操作を何回おこなうか
            for(int l = 0; l < PQlen[0][0]; l++){ // 1回の連結につき、P0の長さだけ連結する。
                *(ptrToPQ[1][0] + count) = *(ptrToPQ[0][0] + l); // ポインタ演算
                count = count + 1;
            }
        }
        for(int k = 0; k < 1; k++){ // Con(; Q0, 1)、連結操作を何回おこなうか
            for(int l = 0; l < PQlen[0][1]; l++){ // 1回の連結につき、Q0の長さだけ連結する。
                *(ptrToPQ[1][0] + count) = *(ptrToPQ[0][1] + l); // ポインタ演算 int型なので1足せば4バイトずれる。
                count = count + 1;
            }
        }

        // Q1 = Con(P0, rho_0 + 1 ; Q0, 1)
        count = 0;

        for(int k = 0; k < rho_0 + 1; k++){ // Con(P0, rho_0 + 1 ;)、連結操作を何回おこなうか
            for(int l = 0; l < PQlen[0][0]; l++){ // 1回の連結につき、P0の長さだけ連結する。
                *(ptrToPQ[1][1] + count) = *(ptrToPQ[0][0] + l); // ポインタ演算 int型なので1足せば4バイトずれる。
                count = count + 1;  
            }
        }
        for(int k = 0; k < 1; k++){ // Con(; Q0, 1)、連結操作を何回おこなうか
            for(int l = 0; l < PQlen[0][1]; l++){ // 1回の連結につき、Q0の長さだけ連結する。
                *(ptrToPQ[1][1] + count) = *(ptrToPQ[0][1] + l); // ポインタ演算
                count = count + 1;
            }
        }

    }else{ // (2b) x0 > 1 のとき
        // P1 = Con(P0, 1 ; Q0, rho_0)
        int rho_0 = fracSeries[0] - 1; // rho0 = x0 - 1
        int count = 0;

        // printf("%p \n",(void*)(ptrToPQ[1][0])); // ptrToPQ[1][0]のアドレス出力

        for(int k = 0; k < 1; k++){ // Con(P0, rho_0 ;)、連結操作を何回おこなうか
            for(int l = 0; l < PQlen[0][0]; l++){ // 1回の連結につき、P0の長さだけ連結する。
                // printf("%p \n",(void*)(ptrToPQ[1][0] + (k * PQlen[0][0] + l))); // ポインタのアドレスの確認
                *(ptrToPQ[1][0] + count) = *(ptrToPQ[0][0] + l); // ポインタ演算
                count = count + 1;
            }
        }
        for(int k = 0; k < rho_0; k++){ // Con(; Q0, 1)、連結操作を何回おこなうか
            for(int l = 0; l < PQlen[0][1]; l++){ // 1回の連結につき、Q0の長さだけ連結する。
                *(ptrToPQ[1][0] + count) = *(ptrToPQ[0][1] + l); // ポインタ演算 int型なので1足せば4バイトずれる。
                count = count + 1;
            }
        }

        // Q1 = Con(P0, 1 ; Q0, rho_0 + 1)
        count = 0;

        for(int k = 0; k < 1; k++){ // Con(P0, rho_0 + 1 ;)、連結操作を何回おこなうか
            for(int l = 0; l < PQlen[0][0]; l++){ // 1回の連結につき、P0の長さだけ連結する。
                *(ptrToPQ[1][1] + count) = *(ptrToPQ[0][0] + l); // ポインタ演算 int型なので1足せば4バイトずれる。
                count = count + 1;
            }
        }
        for(int k = 0; k < rho_0 + 1; k++){ // Con(; Q0, 1)、連結操作を何回おこなうか
            for(int l = 0; l < PQlen[0][1]; l++){ // 1回の連結につき、Q0の長さだけ連結する。
                *(ptrToPQ[1][1] + count) = *(ptrToPQ[0][1] + l); // ポインタ演算
                count = count + 1;
            }
        }

    }

// ------ テスト ------
    printf("i = %d, j = %d, s = %lld\n",i ,j ,s);
    printf("P[1] = ");
    for(int a = 0; a < PQlen[1][0]; a++){
        printf("%d ",*(ptrToPQ[1][0] + a));
    }
    printf("\n");
    printf("Q[1] = ");
    for(int a = 0; a < PQlen[1][1]; a++){
        printf("%d ",*(ptrToPQ[1][1] + a));
    }
    printf("\n");
// --------------------

    if(j == s){
        // P^g
        int v[PQlen[1][0]*g];
        for(int k = 0; k < g; k++){
            for(int l = 0; l < PQlen[1][0]; l++){
                v[l + PQlen[1][0] * k] = *(ptrToPQ[1][0] + l);
            }
        }

        printf("ベクトルv = ");
        for(int k = 0; k < PQlen[1][0]*g; k++){
            printf("%d ",v[k]);
        }
        printf("\n");

        // vの立っているビットに対応する循環行列の行成分を抜き出す。
        // 循環行列A: n-k+1個の連続する成分が1,残りのk-1個の連続する成分が0である長さnのベクトルaに対するn×n循環行列Aのこと。
        // 循環行列Aの作成、2次元配列で
        long long **A;
        A = (long long**)malloc(sizeof(long long*)*n);
        for(int a = 0; a < n; a++){
            A[a] = (long long*)malloc(sizeof(long long)*n);
        }  
        long long a[n];
        // n - k + 1のこと。ベクトルaの連続する1の数。
        long long one_bits_length = n - k + 1;

        for(long long i = 0; i < one_bits_length; i++){
            a[i] = 1;
        }
        for(long long i = one_bits_length; i < n; i++){
            a[i] = 0;
        }

        // Aの一行目
        for(long long i = 0; i < n; i++){
            A[0][i] = a[i];
        }

        long long startPos = 0; // ベクトルaのどこから代入し始めるかを表す変数。
        for(long long i = 1; i < n; i++){
            startPos ++;
            for(long long j = 0; j < n; j++){
                A[i][j] = a[(j + startPos) % n];
            }
        }

        printf("循環行列:\n");
        for(long long i = 0; i < n; i++){
            for(long long j = 0; j < n; j++){
                printf("%lld ",A[i][j]);
            }
            printf("\n");
        }
        printf("\n");

        int maskMatrix[k][n];
        int count = 0;
        for(int k = 0; k < PQlen[1][0]*g; k++){
            if(v[k] == 1){
                for(int l = 0; l < n; l++){
                    maskMatrix[count][l] = A[k][l];
                }
                count++;
            }
        }

        // マスク行列の出力
        printf("マスク行列の出力:\n");
        for(int t = 0; t < k; t++){
            for(int u = 0; u < n; u++){
                printf("%d ",maskMatrix[t][u]);
            }
            printf("\n");
        }

        // マスク行列の各列の重みを計算する。
        long long columnWeights[n];
        for(long long i = 0; i < n; i++){
            columnWeights[i] = 0; 
        }

        for(long long i = 0; i < k; i++){
            for(long long j = 0; j < n; j++){
                if(maskMatrix[i][j] == 1){
                    columnWeights[j]++;
                }
            }
        }

        long long b_floor = floor(((double)k*(n-k+1))/n);
        long long b_ceil = ceil(((double)k*(n-k+1))/n);
        
        // 各列の重みがb_floorかb_ceilになっているか確認。
        for(long long i = 0; i < n; i++){
            if(columnWeights[i] != b_floor && columnWeights[i] != b_ceil){
                printf("%lld,%lld \t失敗。",n,k);
                // printf("各列の重み: ");
                // for(long long i = 0; i < k; i++){
                //     printf("%lld ",columnWeights[i]);
                // }
                printf(" bf = %lld, bc = %lld\t\n", b_floor, b_ceil);
                return 0;
            }
        }

        printf("%lld,%lld \t成功。",n,k);
        // printf("各列の重み: ");
        // for(long long i = 0; i < k; i++){
        //     printf("%lld ",columnWeights[i]);
        // }
        printf(" bf = %lld, bc = %lld\t\n", b_floor, b_ceil);
        
        // 確保したメモリ領域の開放
        for(int k = 0; k < s + 2; k++){
            free(ptrToPQ[k][0]);
            free(ptrToPQ[k][1]);
        }
        free(A);
    
        return 0;
    }

// ------ step3 ------
    i++; j++;

    while(1){
        if(fracSeries[j] == 1){ // (3a) xj == 1 のとき
            // Pi+1 = Con(Pi, 1 ; Qi, rho_i)

            // printf("%p \n",(void*)(ptrToPQ[1][0])); // ptrToPQ[1][0]のアドレス出力
            j = j + 1;
            int rho_i = fracSeries[j]; // rho_i = xi
            int count = 0;

            for(int k = 0; k < 1; k++){ // Con(Pi, 1 ;)、連結操作を1回おこなう
                for(int l = 0; l < PQlen[i][0]; l++){ // 1回の連結につき、Piの長さだけ連結する。
                    *(ptrToPQ[i+1][0] + count) = *(ptrToPQ[i][0] + l); // ポインタ演算
                    // printf("%p ",(void*)(ptrToPQ[i+1][0] + count));
                    count = count + 1;
                }
            }
            // printf("\n");
            for(int k = 0; k < rho_i; k++){ // Con(; Qi, rho_i)、連結操作をrho_i回おこなう
                for(int l = 0; l < PQlen[i][1]; l++){ // 1回の連結につき、Qiの長さだけ連結する。
                    *(ptrToPQ[i+1][0] + count) = *(ptrToPQ[i][1] + l); // ポインタ演算 int型なので1足せば4バイトずれる。
                    // printf("%p ",(void*)(ptrToPQ[i+1][0] + count));
                    count = count + 1;
                }
            }
            // printf("\n");

            // printf("P[%d] = ",i+1);
            // for(int a = 0; a < PQlen[i+1][0]; a++){
            //     printf("%p ",(void*)(ptrToPQ[i+1][0] + a));
            // }
            // printf("\n");
            
            // Qi+1 = Con(Pi, 1 ; Qi, rho_i + 1)

            count = 0;
            for(int k = 0; k < 1; k++){ // Con(Pi, 1 ;)、連結操作を1回おこなう
                for(int l = 0; l < PQlen[i][0]; l++){ // 1回の連結につき、Piの長さだけ連結する。
                    *(ptrToPQ[i+1][1] + count) = *(ptrToPQ[i][0] + l); // ポインタ演算 int型なので1足せば4バイトずれる。
                    count = count + 1;
                }
            }
            for(int k = 0; k < rho_i + 1; k++){ // Con(; Q0, rho_i + 1)、連結操作を rho_i + 1 回おこなう
                for(int l = 0; l < PQlen[i][1]; l++){ // 1回の連結につき、Qiの長さだけ連結する。
                    *(ptrToPQ[i+1][1] + count) = *(ptrToPQ[i][1] + l); // ポインタ演算
                    // printf("%p ",(void*)(ptrToPQ[i+1][0] + count));
                    count = count + 1;
                }
            }

        }else{ // (3b) xj > 1 のとき
            int rho_i = fracSeries[j] - 1; // rho_i = xi
            // Pi+1 = Con(Pi, rho_i ; Qi, 1)
            int count = 0;

            for(int k = 0; k < rho_i; k++){ // Con(Pi, rho_i ;)、連結操作を rho_i 回おこなう
                for(int l = 0; l < PQlen[i][0]; l++){ // 1回の連結につき、Piの長さだけ連結する。
                    *(ptrToPQ[i+1][0] + count) = *(ptrToPQ[i][0] + l); // ポインタ演算
                    // printf("%p ",(void*)(ptrToPQ[i+1][0] + count));
                    count = count + 1;
                }
            }
            for(int k = 0; k < 1; k++){ // Con(; Qi, 1)、連結操作を1回おこなう
                for(int l = 0; l < PQlen[i][1]; l++){ // 1回の連結につき、Qiの長さだけ連結する。
                    *(ptrToPQ[i+1][0] + count) = *(ptrToPQ[i][1] + l); // ポインタ演算 int型なので1足せば4バイトずれる。
                    // printf("%p ",(void*)(ptrToPQ[i+1][0] + count));
                    count = count + 1;
                }
            }
            printf("\n");

            // Qi+1 = Con(Pi, rho_i + 1 ; Qi, 1)
            count = 0;
            for(int k = 0; k < rho_i + 1; k++){ // Con(Pi, rho_i + 1 ;)、連結操作を rho_i + 1 回おこなう
                for(int l = 0; l < PQlen[i][0]; l++){ // 1回の連結につき、Piの長さだけ連結する。
                    *(ptrToPQ[i+1][1] + count) = *(ptrToPQ[i][0] + l); // ポインタ演算 int型なので1足せば4バイトずれる。
                    count = count + 1;
                }
            }
            for(int k = 0; k < 1; k++){ // Con(; Qi, 1)、連結操作を 1 回おこなう
                for(int l = 0; l < PQlen[i][1]; l++){ // 1回の連結につき、Qiの長さだけ連結する。
                    *(ptrToPQ[i+1][1] + count) = *(ptrToPQ[i][1] + l); // ポインタ演算
                    count = count + 1;
                }
            }
        }

// ------ テスト ------
    printf("i = %d, j = %d, s = %lld\n",i ,j ,s);
    printf("P[%d] = ",i+1);
    for(int a = 0; a < PQlen[i+1][0]; a++){
        printf("%d ",*(ptrToPQ[i+1][0] + a));
    }
    printf("\n");
    printf("Q[%d] = ",i+1);
    for(int a = 0; a < PQlen[i+1][1]; a++){
        printf("%d ",*(ptrToPQ[i+1][1] + a));
    }
    printf("\n");
// --------------------

        if(j == s){
            // P^g
            int v[PQlen[i+1][0]*g];
            for(int k = 0; k < g; k++){
                for(int l = 0; l < PQlen[i+1][0]; l++){
                    v[l + PQlen[i+1][0] * k] = *(ptrToPQ[i+1][0] + l);
                }
            }

            printf("ベクトルv = ");
            for(int k = 0; k < PQlen[i+1][0]*g; k++){
                printf("%d ",v[k]);
            }
            printf("\n");

            // vの立っているビットに対応する循環行列の行成分を抜き出す。
            // 循環行列A: n-k+1個の連続する成分が1,残りのk-1個の連続する成分が0である長さnのベクトルaに対するn×n循環行列Aのこと。
            // 循環行列Aの作成、2次元配列で
            long long **A;
            A = (long long**)malloc(sizeof(long long*)*n);
            for(int a = 0; a < n; a++){
                A[a] = (long long*)malloc(sizeof(long long)*n);
            }  
            long long a[n];
            // n - k + 1のこと。ベクトルaの連続する1の数。
            long long one_bits_length = n - k + 1;

            for(long long i = 0; i < one_bits_length; i++){
                a[i] = 1;
            }
            for(long long i = one_bits_length; i < n; i++){
                a[i] = 0;
            }

            // Aの一行目
            for(long long i = 0; i < n; i++){
                A[0][i] = a[i];
            }

            long long startPos = 0; // ベクトルaのどこから代入し始めるかを表す変数。
            for(long long i = 1; i < n; i++){
                startPos ++;
                for(long long j = 0; j < n; j++){
                    A[i][j] = a[(j + startPos) % n];
                }
            }

            printf("循環行列:\n");
            for(long long i = 0; i < n; i++){
                for(long long j = 0; j < n; j++){
                    printf("%lld ",A[i][j]);
                }
                printf("\n");
            }
            printf("\n");

            int maskMatrix[k][n];
            int count = 0;
            for(int k = 0; k < PQlen[i+1][0]*g; k++){
                if(v[k] == 1){
                    for(int l = 0; l < n; l++){
                        maskMatrix[count][l] = A[k][l];
                    }
                    count++;
                }
            }

            // マスク行列の出力
            printf("マスク行列:\n");
            for(int t = 0; t < k; t++){
                for(int u = 0; u < n; u++){
                    printf("%d ",maskMatrix[t][u]);
                }
                printf("\n");
            }

            // マスク行列の各列の重みを計算する。
            long long columnWeights[n];
            for(long long i = 0; i < n; i++){
                columnWeights[i] = 0; 
            }

            for(long long i = 0; i < k; i++){
                for(long long j = 0; j < n; j++){
                    if(maskMatrix[i][j] == 1){
                        columnWeights[j]++;
                    }
                }
            }

            long long b_floor = floor(((double)k*(n-k+1))/n);
            long long b_ceil = ceil(((double)k*(n-k+1))/n);
            
            // 各列の重みがb_floorかb_ceilになっているか確認。
            for(long long i = 0; i < n; i++){
                if(columnWeights[i] != b_floor && columnWeights[i] != b_ceil){
                    printf("%lld,%lld \t失敗。",n,k);
                    // printf("各列の重み: ");
                    // for(long long i = 0; i < k; i++){
                    //     printf("%lld ",columnWeights[i]);
                    // }
                    printf(" bf = %lld, bc = %lld\t\n", b_floor, b_ceil);
                    return 0;
                }
            }

            printf("%lld,%lld \t成功。",n,k);
            // printf("各列の重み: ");
            // for(long long i = 0; i < k; i++){
            //     printf("%lld ",columnWeights[i]);
            // }
            printf(" bf = %lld, bc = %lld\t\n", b_floor, b_ceil);

            // 確保したメモリ領域の開放
            for(int k = 0; k < s + 2; k++){
                free(ptrToPQ[k][0]);
                free(ptrToPQ[k][1]);
            }
            free(A);    

            break;
            
        }

        i++; j++;
    }

    // ------ テスト ------
        // printf("P[1] = ");

        // for(int k = 0; k < PQlen[1][0]; k++){
        //     printf("%d ",*(ptrToPQ[1][0] + k));
        // }
        // printf("\n");
        // printf("ptrToPQ[1][0]に格納されているアドレスを順次見ると、");
        // for(int k = 0; k < PQlen[1][0]; k++){
        //     printf("%p ",(void*)(ptrToPQ[1][0] + k)); //　prtToPQ[1][0] の指す1次元配列のアドレスを各要素ごとに見る。
        // }
        // printf("\n");

        // printf("Q[1] = ");
        // for(int k = 0; k < PQlen[1][1]; k++){
        //     printf("%d ",*(ptrToPQ[1][1] + k));
        // }
        // printf("\n");
        // printf("ptrToPQ[1][1]に格納されているアドレスを順次見ると、");
        // for(int k = 0; k < PQlen[1][1]; k++){
        //     printf("%p ",(void*)(ptrToPQ[1][1] + k)); //　prtToPQ[1][1] の指す1次元配列のアドレスを各要素ごとに見る。
        // }
        // printf("\n");
        // printf("Q[0] = %d\n",*ptrToPQ[0][1]);
    // --------------------

    return 0;
}