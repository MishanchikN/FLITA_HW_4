#include "main.h"

void ShellSort(int n, int mass[2][n])
{
    int i, j, step;
    int tmp;
    for (step = n / 2; step > 0; step /= 2)
        for (i = step; i < n; i++)
        {
            tmp = mass[0][i];
            for (j = i; j >= step; j -= step)
            {
                if (tmp < mass[0][j - step]){
                    mass[0][j] = mass[0][j - step];
                    mass[1][j] = mass[1][j - step];
                }
                else
                    break;
            }
            mass[0][j] = tmp;
            mass[1][j] = i+1;
        }
}

int main(int args, char *sargs[]){
    input_check(args,sargs);
    int i, j, k = 0, r = 0;
    char str[256];
    FILE *fp = fopen("matrix_of_incendence186.txt", "r");
    while(fgets(str, 256, fp) != NULL){
        r++;
    }
    if(atoi(sargs[1]) > r){
        printf("Error! There is no such vertex");
        exit(EXIT_FAILURE);
    }
    fclose(fp);
    FILE *file = fopen("matrix_of_incendence186.txt", "r");
    int matrix_inc[r][vertex_num];
    int m[vertex_num+1][r+1];
    while(fgets(str, 256, file) != NULL){
        i = 0;
        for(j = 0; j < vertex_num; j++){
            matrix_inc[k][j]=(int)str[i] % 2;
            i+=2;
            m[j][r] = 0;
        }
        k+=1;
    }
    fclose(file);
    for(i = 0; i < r; i++){
        for(j = 0; j < vertex_num; j++){
            m[j][i]=matrix_inc[i][j];
            m[j][r]+=matrix_inc[i][j];
            printf("%d ",m[j][i]);
        }
        m[vertex_num][i]+=m[j][i] = 0;
        printf("\n");
    }
    for(i = 0; i < r; i++){
        if(i == atoi(sargs[1])-1){
            for(j = 0; j < vertex_num; j++){
                if(m[j][i] == 1){
                    m[j][i]=0;
                    int trigger = 0;
                    for(int l = 0; l < r; l++){
                        if(m[j][l]==1){
                            m[j][l]=0;
                            trigger = 1;
                            m[j][r]=0;
                        }
                    }
                    if(!trigger) {
                        m[vertex_num][i] += m[j][i];
                        m[j][r]=0;
                    }
                }
                m[j][i]=0;
            }
        }
    }
    for(j = 0; j < vertex_num; j++){
        for(i = 0; i < r; i++){
            m[vertex_num][i]+=m[j][i];
            if(m[j][i] == 1 && m[j][r] == 1)
                m[vertex_num][i]+=m[j][i];
        }
    }
    for(i = 0; i <= r; i++){
        for(j = 0; j <= vertex_num; j++){
            printf("%d ",m[j][i]);
        }
        printf("\n");
    }
    FILE * fo;
    fo = fopen("g.dot","wt");
    fprintf( fo, "digraph Graf {\n");
    fprintf( fo, "  edge [dir=\"both\"] \n");
    for(i = 0; i < k; i++){
        if(m[vertex_num][i] == 0){
            fprintf( fo, " A%d\n", i+1);
        }
    }
    int x1, x2;
    for(j = 0; j < vertex_num; j++){
        if(m[j][k] == 2){
            x1 = -1;
            x2 = -1;
            for(int i1 = 0; i1 < k; i1++){
                if(m[j][i1] == 1 && x1 == -1 && m[0][i1] != -1){
                    x1 = i1;
                    //printf("101");
                }
                else if(m[j][i1] == 1 && x1 != -1 && x1 != i1 && m[0][i1]!= -1){
                    x2 = i1;
                }
            }
            if(x1 != -1 && x2!=-1){
                //printf("%d %d ",x1+1,x2+1);
                fprintf( fo, " A%d", x1+1);
                fprintf( fo, "->");
                fprintf( fo, "A%d \n", x2+1);
            }
        }
        if(m[j][k] == 1){
            x1 = -1;
            for(int i2 = 0; i2 < k; i2++) {
                if(m[j][i2] == 1 && x1 == -1 && m[0][i2] != -1){
                    x1 = i2;
                    //printf("%d", i2+1);
                }
            }
            if(x1 != -1){
                fprintf( fo, " A%d", x1+1);
                fprintf( fo, "->");
                fprintf( fo, "A%d \n", x1+1);
            }
        }
    }
    fprintf( fo, "}");
    fclose(fo);
    system("dot g.dot -Tpng -og.png");
    int array[2][r];
    for(i = 0; i < r; i++){
        array[0][i]=m[vertex_num][i];
        array[1][i]=i+1;
    }
    /*for(i = 0; i < r; i++){
        //printf("%d ", array[0][i]);
        printf("%d ", array[1][i]);
    }
    printf("\n");*/
    double time_spent = 0.0;
    clock_t begin = clock();
    ShellSort(r, array);
    clock_t end = clock();
    time_spent +=(double)(end - begin) / CLOCKS_PER_SEC;
    printf("The elapsed time is %f seconds\n", time_spent);
    /*for(i = 0; i < r; i++){
        //printf("%d ", array[0][i]);
        printf("%d ", array[1][i]);
    }*/
    return 0;
}