#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;
#define hashi 5

int hashisDisponible = 5;
int hashisInUse = 0;

void *utilizandoHashi(int filosofo){

        if(hashisDisponible > 1 && (hashisInUse + 2) <= 4){
            sem_wait(&mutex);
            hashisDisponible -= 2;
            hashisInUse += 2;
            while(hashisDisponible <= 1 && hashisInUse >= 4){
                printf("Filosofo %d, Wating of Hashi is disponible\n", filosofo);
                sleep(4);
            }
            printf("I filoso %d rungry\n", filosofo);
            printf("Filoso %d in pensament\n", filosofo);
            printf("Finalized\n");
            printf("Filosofo: %d\nHashisDisponible: %d\nHashisUsed: %d\n", filosofo, hashisDisponible, hashisInUse);
            hashisDisponible+=2;
            hashisInUse -= 2;
            printf("Filosofo: %d\nHashisDisponible: %d\nHashisUsed: %d\n", filosofo, hashisDisponible, hashisInUse);
            sleep(4);
            sem_post(&mutex);
        }
        else{
            while(hashisDisponible <= 1 && hashisInUse >= 4){
                printf("Filosofo %d, Wating of Hashi is disponible\n", filosofo);
                sleep(4);
            }
            sem_wait(&mutex);
            hashisInUse += 2;
            hashisDisponible -= 2;
            printf("I filoso %d rungry\n", filosofo);
            printf("Filoso %d in pensament\n", filosofo);
            printf("Finalized\n");
            printf("Filosofo: %d\nHashisDisponible: %d\nHashisUsed: %d\n", filosofo, hashisDisponible, hashisInUse);
            hashisDisponible+=2;
            hashisInUse -= 2;
            printf("Filosofo: %d\nHashisDisponible: %d\nHashisUsed: %d\n", filosofo, hashisDisponible, hashisInUse);
            sleep(4);
            sem_post(&mutex);
        }


    
}

int main (){

    int i;
    pthread_t tid[hashi];
    sem_init(&mutex, 0, 5);
    for(i = 0; i<5;i++){
        pthread_create(&tid[i], NULL, utilizandoHashi, i);
    }
    for(i = 0;i<5;i++){
        pthread_join(tid[i], NULL);
    }
    sem_destroy(&mutex);
}
