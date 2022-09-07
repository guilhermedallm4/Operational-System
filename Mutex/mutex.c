#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void createNumberVector(int *vector, int maxVector);
void showVector(int vector[], int maxVector);
void changeValue(int idThread, int maxThread);
void *pThreadSomatorio(int *pAuxVector);

int acumulador = 0;
int initial = 0;
int sizeFinal = 0;
int division = 0;
int parOrImpar = 0;
int counter = 0;
int aux_Thread = 0;
int sizeThread = 0;
int aux_increment = 0;
int sizeVector = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *pThreadSomatorio(int *pAuxVector){
    pthread_mutex_lock(&m);
    
    if(counter == 0){
        initial = 0;
        sizeFinal = division;
        counter++;
    }
    else{
        initial += division;
        sizeFinal += division;
        counter++;
        if(sizeFinal + aux_increment == sizeVector){
          sizeFinal = sizeFinal + aux_increment;
      }
    }
    printf("initial: %d\n", initial);
    if(counter == 0){
    for(int i = initial; i<sizeFinal;i++){
      acumulador += *(pAuxVector + i);
    }
    }   
    else{
      for(int i = initial+1; i<=sizeFinal;i++){
      acumulador += *(pAuxVector + i);
     }
    }
    printf("\nValor do acumulador é: %d\n", acumulador);
    pthread_mutex_unlock(&m);
    
}

int main() {
	int *pAuxVector;
	printf("Digite o tamanho do vetor: ");
	scanf("%d", &sizeVector);
	printf("\nDigite a quantidade de threads: ");
	scanf("%d", &sizeThread);
	printf("\n");
	int vector[sizeVector];
	pAuxVector = vector;
	createNumberVector(pAuxVector, sizeVector);
    showVector(vector,sizeVector);
    pthread_t tid[sizeThread];
    if(sizeVector%2 == 1){
        parOrImpar = 1;
    }
    division = sizeVector / sizeThread;
    printf("Divisão: %d\n", division);
    aux_Thread = sizeVector;
    aux_increment = (sizeVector - (division * sizeThread));
    for(int i = 0; i<sizeThread;i++){
      pthread_create(&tid[i], NULL, &pThreadSomatorio, pAuxVector);
    }
    for(int i = 0; i<sizeThread; i++){
        pthread_join(tid[i], NULL);
    }
}

void createNumberVector(int *vector, int maxVector) {
	for (int i = 0; i <= maxVector; i++) {
		*(vector + i) = i;
	}
}

void showVector(int vector[], int maxVector) {
	for (int i = 0; i <= maxVector; i++) {
		printf(" %d ", vector[i]);
	}
	printf("\n");
}
