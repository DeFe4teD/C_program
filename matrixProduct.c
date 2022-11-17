#include <stdio.h>

int main(void){
    //行列のサイズ
    printf("行列のサイズを入力してください。");
    int mtrSize; scanf("%d",&mtrSize);

    int mtr1[mtrSize][mtrSize];
    int mtr2[mtrSize][mtrSize];
    int mtr3[mtrSize][mtrSize];

    //1つ目の行列の入力
    //i行目j列目
    for(int i = 0; i < mtrSize; i++){
        printf("行列1: %d行目(%d個の数字)を入力してください。", i+1, mtrSize);
        for(int j = 0; j < mtrSize; j++){
            scanf("%d",&mtr1[i][j]);
        }
    }

    //2つ目の行列の入力
    //i行目j列目
    for(int i = 0; i < mtrSize; i++){
        printf("行列2: %d行目(%d個の数字)を入力してください。", i+1, mtrSize);
        for(int j = 0; j < mtrSize; j++){
            scanf("%d",&mtr2[i][j]);
        }
    }

    //1つ目の行列の出力
    printf("行列1\n");
    for(int i = 0; i < mtrSize; i++){
        for(int j = 0; j < mtrSize; j++){
            printf("%d ",mtr1[i][j]);
        }
        printf("\n");
    }

    //2つ目の行列の出力
    printf("行列2\n");
    for(int i = 0; i < mtrSize; i++){
        for(int j = 0; j < mtrSize; j++){
            printf("%d ",mtr2[i][j]);
        }
        printf("\n");
    }

    //行列1と行列2の掛け算
    //mtr3[i][j]、i行j列に対して、その上をkが走るイメージ。
    // mtr1[i][k] , mtr2[k][j]
    for(int i = 0; i < mtrSize; i++){
        for(int j = 0; j < mtrSize; j++){
            for(int k = 0; k < mtrSize; k++){
                mtr3[i][j] += mtr1[i][k] * mtr2[k][j];
            }
        }
    }

    printf("行列1と行列2の掛け算の結果\n");
    for(int i = 0; i < mtrSize; i++){
        for(int j = 0; j < mtrSize; j++){
            printf("%d ",mtr3[i][j]);
        }
        printf("\n");
    }

}


