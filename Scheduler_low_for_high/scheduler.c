/*Code for the Operating Systems discipline, where the tasks come from the tarefas.txt file and are distributed to the processors*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TIME (sizeof(int))
#define CARAC (sizeof(char)* 100)
#define AMARRADO  (sizeof(void **))

int verificationSizeLines(FILE *arq);
void *alocMemoryDinamic(void *pBuffer, int lines);
void *readArchive(void *pBuffer, FILE *arq, int lines);
void *listBuffer(void *pBuffer, int lines);
void *selectionSort(void *pBuffer, int end);
void *wRiteArchive(void *pBuffer, int initial, int processador, int lines);

int main(){
    void *pBuffer;
    FILE *arq;
    int processador = 0;
    arq = fopen("tarefas.txt", "r");
    int lines = verificationSizeLines(arq);
    pBuffer = alocMemoryDinamic(pBuffer, lines);
    pBuffer = readArchive(pBuffer, arq, lines);
    selectionSort(pBuffer, lines);
    listBuffer(pBuffer, lines);
    printf("Digite a quantidade de processadores disponíveis para uso:  ");
    scanf("%d", &processador);
    //printf("Quantidade de processos por processador: %d - %d = %d", lines, processador, media);
    for(int w=1; w <= processador;w++){
        wRiteArchive(pBuffer, w, processador, lines);
    }
    fclose(arq);
    free(pBuffer);
    exit(1);
}

int verificationSizeLines(FILE *arq){
    int counter = 0;
    char letra[2] = "\n";
    char str[30];
    while(fgets(str, 30, arq)!= NULL){
        counter++;
    }
    rewind(arq);
    return counter;
}

void *alocMemoryDinamic(void *pBuffer, int lines){
    pBuffer = malloc(sizeof((((CARAC ) + TIME + AMARRADO) * lines)));
    return pBuffer;
}

void *readArchive(void *pBuffer, FILE *arq, int lines){
    int counter = 1;
    int  aux = 0;
    while(counter <=lines){
      fscanf(arq,"%s %d",  (char *)(pBuffer + (CARAC * counter)), &aux);
      *(int *)(pBuffer + ((CARAC + TIME) * counter)) = aux;
      counter++;
    }
    
    return pBuffer;
}

void *listBuffer(void *pBuffer, int lines){
    int counter = 1;
    int aux = 0;
    while(counter <=lines){
        printf("%s", (char *)(pBuffer + ((CARAC * counter))));  
        printf(" %d\n", *(int *)(pBuffer + ((CARAC + TIME) * counter)));
        //printf("%s\n", (char*)*(void **)(pBuffer + ((CARAC + TIME + AMARRADO) * counter))); Cassting do ponteiro para o a amarração
      counter++;
    }
    return pBuffer;
}

void *selectionSort(void *pBuffer, int end){
    int i = 1, varAux, w, p;
    int temp;
    int verify = 1;
    void *pAux = malloc(sizeof(CARAC));
    void *pTemp = malloc(sizeof(CARAC));
    do{

    for(w = i;w<=end;w++){
        if(w == 1){
            varAux = *(int *)(pBuffer + ((CARAC + TIME) * w));
        }
        if(varAux >= *(int *)(pBuffer + ((CARAC + TIME) * w))){
            varAux = *(int *)(pBuffer + ((CARAC + TIME) * w));
            strcpy((char *)pAux + (CARAC), (char *)pBuffer + CARAC * w);
            p = w;
        }
    }
        
        strcpy((char *)pTemp + (CARAC), (char *)pBuffer + CARAC * i);
        strcpy((char *)pBuffer + CARAC * i, (char *)pAux + (CARAC));
        strcpy((char *)pBuffer + CARAC * p, (char *)pTemp + (CARAC));
        temp = *(int *)(pBuffer + ((CARAC + TIME) * i));
        *(int *)(pBuffer + ((CARAC + TIME) * i))= varAux;
        *(int *)(pBuffer + ((CARAC + TIME) * p)) = temp;
        i++;
        varAux = *(int *)(pBuffer + ((CARAC + TIME) * i));
    }while(i <=end);
    return pBuffer;
}

void *wRiteArchive(void *pBuffer, int initial, int processador, int lines){
        FILE *read;
        read = fopen("executando.txt", "a");
        int aux = 0, i = initial;
        fprintf(read, "Processador %d:\n", initial);
        while(i<=lines){
            fprintf(read ,"%s;%d;%d\n", (char *)(pBuffer + ((CARAC * i))), aux,*(int *)(pBuffer + ((CARAC + TIME) * i)));
            aux += *(int *)(pBuffer + ((CARAC + TIME) * i));
            i+= processador;
            if(i>lines){
                fprintf(read, "Total: %d\n", aux);
            }
        }
        fprintf(read,"\n");
    fclose(read);

}