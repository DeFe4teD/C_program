// 先輩のコピー
#include <stdio.h>

int main(void)
{

    int n, k, i, j, t, l, c, e, r, g, s, tmp;
    l = 0;
    int P[100][100], Q[100][100], R[100], LP[100], LQ[100];
    int A[100] = {0}; 
    int B[100] = {0}; 
    int V[100] = {0};
    for(i=0; i<100; i++)
    {
        for(j=0; j<100; j++)
        {
            P[i][j] = 2;
            Q[i][j] = 2;
        }
    }

    printf("n = ");
    scanf("%d", &n);
    printf("k = ");
    scanf("%d", &k);

    //最大公約数gの導出
    c = n;
    e = k;

    if(c<e)
    {
        tmp = c;
        c = e;
        e = tmp;
    }

    r = c % e;

    while(r!=0)
    {
        c = e;
        e = r;
        r = c % e;
    }

    g = e;

    P[0][0] = 1;
    Q[0][0] = 0;
    LP[0] = 1; 
    LQ[0] = 1;


    A[0] = n;
    B[0] = k;
    for(i=0; i<100; i++)
    {
        R[i] = A[i] / B[i];
        A[i+1] = B[i];
        B[i+1] = A[i] - R[i] * B[i];
        if(B[i+1] == 0)
        {
            break;
        }
    }
    printf("R = %d; ", R[0]);
    for(i=1; i<100; i++)
    {
        if(R[i] == 0)
        {
            printf("\n\n");
            break;
        }
        printf("%d, ", R[i]);
    }

    if(R[0] == 1)
    {
        l = l + 1;
        //Pi+1の導出
        for(i=0; i<R[l]; i++)
        {
            for(j=0; j<LP[0]; j++)
            {
                P[1][j+i*LP[0]] = P[0][j];
            }
        }

        for(j=0; j<LQ[0]; j++)
        {
            P[1][j+LP[0]*R[l]] = Q[0][j];
        }

        //Qi+1の導出
        for(i=0; i<R[l]+1; i++)
        {
            for(j=0; j<LP[0]; j++)
            {
                Q[1][j+i*LP[0]] = P[0][j];
            }
        }

        for(j=0; j<LQ[0]; j++)
        {
            Q[1][j+LP[0]*(R[l]+1)] = Q[0][j];
        }
    }
    else
    {
        //Pi+1の導出
        for(j=0; j<LP[0]; j++)
        {
            P[1][j] = P[0][j];
        }

        for(i=0; i<R[0]-1; i++)
        {
            for(j=0; j<LQ[0]; j++)
            {
                P[1][j+LP[0]+i*LQ[0]] = Q[0][j];
            }
        }

        //Qi+1の導出
        for(j=0; j<LP[0]; j++)
        {
            Q[1][j] = P[0][j];
        }

        for(i=0; i<R[0]; i++)
        {
            for(j=0; j<LQ[0]; j++)
            {
                Q[1][j+LP[0]+i*LQ[0]] = Q[0][j];
            }
        }
    }
    //PとQの長さの導出
    for (j=0; j<2*n; j++)
    {
        if (P[1][j] != 2)
        {
            LP[1] = LP[1] +  1;
        }
        else
        {
            break;
        }
    }
    for (j=0; j<2*n; j++)
    {
        if (Q[1][j] != 2)
        {
            LQ[1] = LQ[1] + 1;
        }
        else
        {
            break;
        }
    }
    l = l + 1;

    if(R[l] != 0)
    {       
        for(i=1; i<100; i++)
        {
            if(R[l] == 1)
            {
                l = l + 1;
                //Pi+1の導出
                for(j=0; j<LP[i]; j++)
                {
                    P[i+1][j] = P[i][j];
                }

                for(t=0; t<R[l]; t++)
                {
                    for(j=0; j<LQ[i]; j++)
                    {
                        P[i+1][j+LP[i]+t*LQ[i]] = Q[i][j];
                    }
                }

                //Qi+1の導出
                for(j=0; j<LP[i]; j++)
                {
                    Q[i+1][j] = P[i][j];
                }

                for(t=0; t<R[l]+1; t++)
                {
                    for(j=0; j<LQ[i]; j++)
                    {
                        Q[i+1][j+LP[i]+t*LQ[i]] = Q[i][j];
                    }
                }
            }
            else
            {
                //Pi+1の導出
                for(t=0; t<R[l]-1; t++)
                {
                    for(j=0; j<LP[i]; j++)
                    {
                        P[i+1][j+t*LP[i]] = P[i][j];
                    }
                }

                for(j=0; j<LQ[i]; j++)
                {
                    P[i+1][j+LP[i]*(R[l]-1)] = Q[i][j];
                }
  
                //Qi+1の導出
                for(t=0; t<R[l]; t++)
                {
                    for(j=0; j<LP[i]; j++)
                    {
                        Q[i+1][j+t*LP[i]] = P[i][j];
                    }
                }

                for(j=0; j<LQ[i]; j++)
                {
                    Q[i+1][j+LP[i]*R[l]] = Q[i][j];
                }
            }
            //PとQの長さの導出
            for (j=0; j<2*n; j++)
            {
                if (P[i+1][j] !=2)
                {
                    LP[i+1] = LP[i+1] + 1;
                }
                else
                {
                    break;
                }
            }
            for (j=0; j<2*n; j++)
            {
                if (Q[i+1][j] !=2)
                {
                    LQ[i+1] = LQ[i+1] + 1;
                }
                else
                {
                    break;
                }
            }

            l = l + 1;
            if(R[l] == 0)
            {
                s = i + 1;
                break;    
            }
        }
    }
    else
    {
        s = 1;
    }

    //P,Q;syuturyoku
    for(i=1; i<=s; i++)
    {
        printf("P[%d] = ", i);
        for(j=0; j<LP[i]; j++)
        {
            printf("%d", P[i][j]);
        }
        printf("\nLP[%d] = %d\n", i, LP[i]);
    }
    for(i=1; i<=s; i++)
    {
        printf("\nQ[%d] = ", i);
        for(j=0; j<LQ[i]; j++)
        {
            printf("%d", Q[i][j]);
        }
        printf("\nLQ[%d] = %d", i, LQ[i]);
    }
    printf("\n\n");

    //g,s;syuturyoku
    printf("g = %d\n", g);
    printf("s = %d\n", s);

    //Vの導出
    for(t=0; t<g; t++)
    {
        for(i=0; i<LP[s]; i++)
        {
            V[i+t*LP[s]] = P[s][i];
        }
    }
    printf("\nV =  ");
    for(i=0; i<LP[s]*g; i++)
    {
        printf("%d", V[i]);
    }
    printf("\n\n");

    return 0;
}