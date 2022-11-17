#include <stdio.h>
#include <math.h>

//掃き出し法
//参考URL: https://daeudaeu.com/c-mat-inverse/

// 許容する誤差
#define MAX_ERR 1e-10 

// 行列と逆行列の積が単位行列となっているかどうか。逆行列が正しく計算できているかどうかを確認する関数。
// 引数の型が1次元配列だが、実際は2次元配列。
int checkMatrix(double mat[], double inv[], int matSize){
    double checkMat[matSize][matSize];

    for(int i = 0; i < matSize; i++){
        for(int j = 0; j < matSize; j++){
            double inner_product = 0;
            for(int k = 0; k < matSize; k++){
                // 本来2次元配列だが、1次元配列の形で引数を指定しているので、行を表す変数に対してmatSizeを掛ける
                inner_product += mat[i * matSize + k] * inv[k * matSize + j];
            }
            checkMat[i][j] = inner_product;

            //単位行列[i][j]
            double ans = (i == j) ? 1 : 0;
            //積と単位行列の差が限りなく0に近ければ問題ない。
            double diff = ans - inner_product;
            if(fabs(diff) > MAX_ERR) return 0;
        }
        
    }
    
    printf("行列と逆行列の積↓\n");
    for(int i = 0; i < matSize; i++){
        for(int j = 0; j < matSize; j++){
            printf("%6.3f, ",checkMat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    return 1;
}


int main(void){
    //行列サイズ入力
    printf("行列のサイズを入力してください。");
    //行列のサイズ
    int matsize; scanf("%d",&matsize);

    //逆行列を求める対象となる正方行列
    double mat[matsize][matsize];
    //逆行列
    double inv[matsize][matsize];
    //掃き出し法の操作を行う配列
    double sweep[matsize][matsize * 2];

    //逆行列を求めたい正方行列の入力
    for(int i = 0; i < matsize; i++){
        printf("%d行目の数字を入力してください。(%d個の数字)", i + 1, matsize);
        for(int j = 0; j < matsize; j++){
            scanf("%lf",&mat[i][j]);
        }
    }

    //配列sweepの初期設定
    for(int i = 0; i < matsize; i++){
        for(int j = 0; j < matsize; j++){
            //sweepの左側には、逆行列を求めたい行列をセット
            sweep[i][j] = mat[i][j];
            //sweepの右側には、単位行列をセット
            sweep[i][matsize + j] = (i == j) ? 1 : 0;
        }
    }

    //sweepの出力
    printf("掃き出し法を行う行列です↓\n");
    for(int i = 0; i < matsize; i++){
        for(int j = 0; j < matsize * 2; j++){
            printf("%8.4f, ",sweep[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    //掃き出し法
    // k は対角成分の位置, sweep[k][k]で対角成分
    for(int k = 0; k < matsize; k++){
        // 対角成分を1にする処理をする前に、対角成分が0の場合ゼロ除算が発生する。
        // それを防ぐためk列目で絶対値の最も大きい値のある行を探し、k行目とその行を入れ替える。(行基本変形)

        // とりあえず対角成分をk列目の中で最も絶対値の大きい値として仮定。
        double mx = fabs(sweep[k][k]);
        // max_i は絶対値の最も大きい値のある行を指す。
        int max_i = k;

        //k列目のなかでもっとも絶対値の大きい行を探す。
        for(int i = k + 1; i < matsize; i++){
            if(fabs(sweep[i][k]) > mx){
                mx = fabs(sweep[i][k]);
                max_i = i;
            }
        }
        
        // 行入れ替えの結果、対角成分が0のときは逆行列を求められない。
        if(mx <= MAX_ERR){
            printf("逆行列は求められません。\n");
            printf("入力した行列を見直してください。");
            return 0;
        }

        //行を入れ替える。
        if(k != max_i){
            for(int i = 0; i < matsize * 2; i++){
                double temp = sweep[k][i];
                sweep[k][i] = sweep[max_i][i];
                sweep[max_i][i] = temp;
            }
        }

        //sweep[k][k]にそれ自身の逆数をかけることで、1にしたい。そのための変数aを用意。
        //定数倍用の変数 a
        double a = 1 / sweep[k][k];

        //k行目の全ての値に対して、上で求めた逆数aをかける。(行基本変形)
        for(int j = 0; j < matsize * 2; j++){
            sweep[k][j] *= a;
        }

        //k列目で、対角成分のあるk行目以外の行(i行目)を0にしていく。(sweepの左半分を単位行列にするため)
        for(int i = 0; i < matsize; i++){
            // k行目は1のままにしたいので無視。
            if(i == k) continue;

            // k行目以外を0にしていく。
            // i行目k列目を0にするための値 b。これをi行全体にかけていく。(行基本変形)
            // k行目k列目を１にしたので、それを利用している。
            double b = -sweep[i][k];

            for(int j = 0; j < matsize * 2; j++){
                //これによりsweep[i][k]が0になる。(もちろんsweep[k][k]以外の)
                //行基本変形なのでi行全体にして加算減算が行われている。
                // k行目k列目を１にしたので、それを利用している。
                sweep[i][j] += sweep[k][j] * b;
            }
        }
    }

    //sweepの出力
    printf("掃き出し法を終了しました↓\n");
    for(int i = 0; i < matsize; i++){
        for(int j = 0; j < matsize * 2; j++){
            printf("%8.4f, ",sweep[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    //sweepの右半分が逆行列に変換されているはずなので、取り出す。
    for(int i = 0; i < matsize; i++){
        for(int j = 0; j < matsize; j++){
            inv[i][j] = sweep[i][j + matsize];
        }
    }

    printf("逆行列です↓\n");
    for(int i = 0; i < matsize; i++){
        for(int j = 0; j < matsize; j++){
            printf("%8.4f, ", inv[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    //検算
    if(checkMatrix(*mat, *inv, matsize)){
        printf("invはmatの逆行列です。\n");
    }else{
        printf("invはmatの逆行列になっていません。\n");
    }


}