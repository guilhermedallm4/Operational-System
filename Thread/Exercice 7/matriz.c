#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
#include <pthread.h>

int aux_line = 0;
int aux_column = 0;
int max_size_line = 0;
int max_size_column = 0;
void listMatriz(int **pAux);

void create_matriz(int **pAux){
    int i = 0, w = 0, aux = 0;
    for(i = aux_line;i<max_size_line;i++){
        for(int w = aux_column-1; w<max_size_column; w++){
            aux = (rand() % 100);
            *((pAux + i) + w) = aux;
            }
    }
}

int main(){
    int i = 0, size_threads = 0, line = 0, column = 0;
    int **pAux;
    printf("Tell-me, whats the amount threads is request\nOptions:\n1-One thread\n2-Two Threads\n3-Three threads\n4-For threads\n Select Option: ");
    scanf("%d", &size_threads);
    switch(size_threads){
        case 1:
            printf("Tell-me, whats size your matriz\n Whats size line of matriz> ");
            scanf("%d", &line);
            printf("And Whats size column of matriz: ");
            scanf("%d", &column);
            pAux = malloc(max_size_line * sizeof(int*));
            max_size_line = line;
            max_size_column = column;
            aux_line = line / 2;
            aux_column = column / 2;
            int aux = 0;
            for(i = 0; i<max_size_line;i++){
                pAux[i] = malloc(max_size_column * sizeof(int));
            }
            pthread_t tid;            
            pthread_create(&tid, NULL, create_matriz, pAux);
            pthread_join(tid, NULL);
            for(i = 0;i<aux_line;i++){
                for(int w = 0; w<aux_column; w++){
                   // printf("Entrei fora da Thread %d\n", i);
                    aux = (rand() % 100);
                    *((pAux + i) + w) = aux;
                }
            }
            break;
        //case 2:

        //case 3:

        //case 4:
        
        //default:
         //       printf("Option undefined");
          //      break;
    }/*
    pthread_exit(NULL);
    for(i = 0;i<max_size_line;i++){
        for(int w = 0; w<max_size_column; w++){
                    printf("%d ", matriz_thread[i][w]);
                }
                printf("\n");
            }*/
    listMatriz(pAux);
    free(pAux);
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

/*void createThread(int **pAux, int size_thread){

}*/