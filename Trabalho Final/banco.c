#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <math.h>
#include <unistd.h>

int i = 0;
// sem_t mutex;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

float species_bank = 500000, subsidy_bank = 100000, fees_bank = 30000;


typedef struct{
    float have_fees;
    float have_subsidy;
    float have_species;
    float value_imovel;
}Cliente;


void *verification_value(Cliente *pClient){
    Cliente thread;
    thread = *pClient;
    float value_fees = (thread.value_imovel * 0.05) - thread.have_fees;
    float value_species = thread.value_imovel - value_species;
    
    while(value_fees > fees_bank && value_species > species_bank && thread.have_subsidy > subsidy_bank)
    {
        printf("Aguardando liberação de recursos\n");
        //pthread_mutex_lock(&m);
    }
        //sem_wait(&mutex);
        pthread_mutex_lock(&m);
        printf("Disponibilizando o valor %f em especie\n", value_species);
        printf("Disponibilizando o valor %f em taxa\n", value_fees);
        printf("Disponibilizando o valor %f em Subisidio\n", thread.have_subsidy);
        thread.have_fees += value_fees;
        thread.have_species += (value_species - thread.have_subsidy);
        //thread.have_subsidy += subsidy_bank;
        fees_bank -= value_fees;
        species_bank -= value_species;
        subsidy_bank -= thread.have_subsidy;
        printf("Iniciando a devolver valores emprestados\n");
        sleep(3);
        fees_bank += thread.have_fees;
        species_bank += thread.have_species;
        subsidy_bank += thread.have_subsidy;
        pthread_mutex_unlock(&m);
       // sem_post(&mutex);
    //printf("%f, %f, %f, %f\n", thread.have_fees, thread.have_species, thread.have_subsidy, thread.value_imovel);
}


int main(){
    srand(time(NULL));
    int groups = 2;
    float value_species, value_subsidy, value_fees, fees_TBI = 0.05, fees_subsidy = 0.2;
    Cliente cliente[groups];
    pthread_t tid[groups];
    Cliente *pClient;
    //sem_init(&mutex, 0, 2);
    for(int i = 0; i < groups;i++){
        printf("Digite o valor do imóvel que deseja comprar: ");
        scanf("%f", &cliente[i].value_imovel);
        printf("\n");
        cliente[i].have_subsidy = (rand() % 1) + 2;
        if(cliente[i].have_subsidy == 0){
            cliente[i].have_subsidy = cliente[i].value_imovel * 0.05;
        }
        else if(cliente[i].have_subsidy == 1){
            cliente[i].have_subsidy = cliente[i].value_imovel * 0.10;
        }
        else{
            cliente[i].have_subsidy = cliente[i].value_imovel * 0.20;
        }

        cliente[i].have_species = (rand() % 30) + 41;
        printf("%f\n", cliente[i].have_species);
        cliente[i].have_species = cliente[i].value_imovel * (cliente[i].have_species/100);

        cliente[i].have_fees = (rand() % 50) + 51;
        printf("%f\n", cliente[i].have_fees);
        cliente[i].have_fees = (cliente[i].value_imovel * fees_TBI) * (cliente[i].have_fees/100);
    //}
    //for(int i = 0; i < groups;i++){
        *pClient = cliente[i];
        pthread_create(&tid[i], NULL, verification_value, pClient);
    }


    for(int i = 0; i< groups; i++){
        pthread_join(tid[i], NULL);
    }
    //sem_destroy(&mutex);

}
