#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;
#define hashi 5

int hashisDisponible = 5;
int hashisInUse = 0;

void *utilizandoHashi(int filosofo){
    if(hashisInUse < hashi && hashisDisponible != 4){
        sem_wait(&mutex);
        hashisInUse += 2;
        hashisDisponible -= 2;
        printf("I filoso %d rungry\n", filosofo);
        //sleep(4);
        printf("Filoso %d in pensament\n", filosofo);
        //sleep(4);
        printf("Finalized");
        hashisDisponible+=2;
        hashisInUse -= 2;
        sem_post(&mutex);
    } 
    else{
        printf("%d", hashisDisponible);
        while(hashisDisponible == 1){
            printf("Filoso %d Aguardando hashi", filosofo);
        }
        sem_wait(&mutex);
        hashisInUse += 2;
        hashisDisponible -= 2;
        printf("I filoso %d rungry\n", filosofo);
        //sleep(4);
        printf("Filoso %d in pensament\n", filosofo);
        //sleep(4);
        printf("Finalized");
        hashisDisponible+=2;
        hashisInUse -= 2;
        sem_post(&mutex);

    }

}

int main (){

    int i;
    pthread_t tid[hashi];
    for(i = 0; i<5;i++){
        pthread_create(&tid[i], NULL, utilizandoHashi, i);
    }
    for(i = 0;i<5;i++){
        pthread_join(&tid[i], NULL);
    }
}

