#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
#include <pthread.h>
#include <time.h>


int aux_line = 0;
int aux_column = 0;
int max_size_line = 0;
int max_size_column = 0;
int aux_line_two = 0;
int aux_column_two = 0;
int max_size_line_two = 0;
int max_size_column_two = 0;
void listMatriz(int **pAux);
void **createThread(int **pAux,int size_threads, int line, int column);
void wRiteArchive(double fTemp);
int create_matriz(int **pAux){
        int i = 0, w = 0, aux = 0;
        for(i = aux_line; i<max_size_line; i++){
            for(w = aux_column-1; w<max_size_column; w++){
            aux = (rand() % 100);
            *((pAux + i) + w) = aux;
            }
        }
    }

int create_matriz_two(int **pAux){
    int i = 0, w = 0, aux = 0;
    for(i = aux_line_two;i<max_size_line_two;i++){
        for(int w = aux_column_two-1; w<max_size_column_two; w++){
            aux = (rand() % 100);
            *((pAux + i) + w) = aux;
            }
    }
}
    
    int main(){
        pthread_t tid[4];            
        int i = 0, size_threads = 0, line = 0, column = 0;
        int **pAux;
        double time_spent = 0.0;
        clock_t begin = clock();
        printf("Tell-me, whats the amount threads is request\nOptions:\n1-One thread\n2-Two Threads\n3-For threads\n Select Option: ");
        scanf("%d", &size_threads);
        printf("Tell-me, whats size your matriz\n Whats size line of matriz: ");
        scanf("%d", &line);
        printf("And Whats size column of matriz: ");
        scanf("%d", &column);
        pAux = malloc(line * sizeof(int*));
        for(i = 0; i<line;i++){
            pAux[i] = malloc(column * sizeof(int));
        }

        pAux = createThread(pAux, size_threads,line, column);
        listMatriz(pAux);
        free(pAux);
        clock_t end = clock();
        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
        printf("\nThe elapsed time is %f seconds", time_spent);
        wRiteArchive(time_spent);
        return 0;
    }
    
void listMatriz(int **pAux){
        int i = 0, w = 0;
        for(i = 0;i<max_size_line;i++){
            for(int w = 0; w<max_size_column; w++){
                    printf("%d ",  (*((pAux + i) + w)));
                }
            printf("\n");
        }
        return;
    }
    
void **createThread(int **pAux,int size_threads, int line, int column){
        pthread_t tid[4];            
        int i = 0, aux = 0, aux_line_for = 0, aux_column_for = 0;
        switch(size_threads){
            case 1:
                max_size_line = line;
                max_size_column = column;
                aux_line = line / 2;
                aux_column = column / 2;
                pthread_create(&tid[0], NULL, create_matriz, pAux);
                pthread_join(tid[0], NULL);
                for(i = 0;i<aux_line;i++){
                    for(int w = 0; w<aux_column; w++){
                        aux = (rand() % 100);
                        *((pAux + i) + w) = aux;
                    }
                }
                break;
            case 2:
                aux = line / 3;
                max_size_line = line;
                max_size_column = column;
                max_size_line_two = aux * 2; 
                max_size_column_two = aux * 2; 
                aux_column_two = aux;
                aux_line_two = aux;
                aux_line = max_size_line_two;
                aux_column = max_size_column_two;          
                pthread_create(&tid[0], NULL, create_matriz, pAux);
                pthread_create(&tid[1], NULL, create_matriz_two, pAux);
                pthread_join(tid[0], NULL);
                pthread_join(tid[1], NULL);
                for(i = 0;i<aux_line_two;i++){
                    for(int w = 0; w<aux_column_two; w++){
                        aux = (rand() % 100);
                        *((pAux + i) + w) = aux;
                    }
                }
                break;
            case 3:
                aux = line / 5;
                max_size_line = line;
                max_size_column = column;
                aux_line_for = aux * 2;
                aux_column_for = aux * 2;
                max_size_line_two = aux * 3; 
                max_size_column_two = aux * 3; 
                aux_column_two = aux * 4;
                aux_line_two = aux * 4;
                aux_line = max_size_line_two;
                aux_column = max_size_column_two;         
                pthread_create(&tid[0], NULL, create_matriz, pAux);
                pthread_create(&tid[1], NULL, create_matriz_two, pAux);
                pthread_create(&tid[2], NULL, create_matriz, pAux);
                pthread_create(&tid[3], NULL, create_matriz_two, pAux);
                pthread_join(tid[0], NULL);
                pthread_join(tid[1], NULL);
                pthread_join(tid[2], NULL);
                pthread_join(tid[3], NULL);

                for(i = 0;i<aux_line_for;i++){
                    for(int w = 0; w<aux_column_for; w++){
                        aux = (rand() % 100);
                        *((pAux + i) + w) = aux;
                    }
                }
                aux_line_for *= 5;
                aux_column_for *= 5;
                for(i = 0;i<aux_line_for;i++){
                    for(int w = 0; w<aux_column_for; w++){
                        aux = (rand() % 100);
                        *((pAux + i) + w) = aux;
                    }
                }
                break;

            default:
                printf("Option undefined");
                break;
        }
        return pAux;
}


void wRiteArchive(double fTemp){
        FILE *arq;
        arq = fopen("resultado.txt", "a");
        fprintf(arq, "\nThe elapsed time is %f seconds", fTemp);
        fclose(arq);
}
