//16進数を10進数に
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void){
    char hexCode[16] = {"0123456789ABCDEF"};
    int ans = 0;
    int count = 0;

    printf("16進数を入力してください。\n");
    char input[1000]; scanf("%s", input);
    int len = strlen(input);

    //小文字を大文字に変換。またおかしな入力がないか確認。
    for(int i = 0; i < len; i++){
        if('a' <= input[i] && input[i] <= 'f'){
            input[i] = input[i] - 32;
        }

        if((input[i] < 48 || 57 < input[i]) && (input[i] < 65 || 70 < input[i])){
            printf("入力がおかしいです。\n");
            return 0;
        }
    }

    // //確認、
    // for(int i = 0; i < len; i++){
    //     printf("%c", input[i]);
    // }
    // printf("\n");

    for(int i = len - 1; i >= 0; i--){
        for(int j = 0; j < 16; j++){
            if(hexCode[j] == input[i]){
                ans += (pow(16, (len - 1) - i) * j);
                break;
            }
        }
        printf("%d\n",ans);
    }

    printf("%d\n",ans);
    
}


