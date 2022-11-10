#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <math.h>
#include <unistd.h>
#define GRUPO 5;

float species_bank = 500000, subsidy_bank = 100000, fees_bank = 30000;
int value = 0;

typedef struct{
    float have_fees;
    float have_subsidy;
    float have_species;
    float value_imovel;
}Cliente;


Cliente cliente[5];

sem_t semaphore_thread;

void *verification_value(void *args){
    float parcela_specie = 0, parcela_fees;
    float total_specie = 0, total_fees;
    float value_fees, value_specie, value_subsidy;
    int counter = 0;
    int i;
    sem_wait(&semaphore_thread);
    i = (int *)args;
    printf("%d\n", i);
    value_specie = cliente[i].have_species - cliente[i].have_subsidy;
    value_fees = cliente[i].have_fees;
    printf("Thread %d precisa de %f em especie ", i, value_specie);
    sem_post(&semaphore_thread);
    
    while(value_fees > fees_bank || value_specie > species_bank || cliente[i].have_subsidy > subsidy_bank){
      printf("Thread %d aguardando recurso\n", i);
      sleep(4);
    }
    printf("\n");
    printf("\n");
    sem_wait(&semaphore_thread);
    printf("Thread %d está sendo atendido\n", i);
    
    printf("\n");
    printf("\n");
    sleep(4);
    species_bank -= value_specie;
    fees_bank -= value_fees;
    subsidy_bank -= cliente[i].have_subsidy;
    cliente[i].have_fees += value_fees;
    cliente[i].have_species += value_specie;
    while(counter < 3){
        sleep(4);
        if(counter == 0){
            parcela_specie = value_specie / 3;
            parcela_fees = value_fees / 3;
            printf("Devolvendo em 3 parcelas o valor de %f em especie e %f em taxa\n", parcela_specie, parcela_fees);
            total_specie += parcela_specie;
            total_fees += parcela_fees;
            printf("Parcela %d: \n valor em especie: %f\n valor em taxa: %f\n", counter+1,  parcela_specie, parcela_fees);
        }
        else{
            total_specie += parcela_specie;
            total_fees += parcela_fees;
            printf("Parcela %d: \n valor em especie: %f\n valor em taxa: %f\n", counter+1,  parcela_specie, parcela_fees);
        }    
        printf("\n");
        printf("\n");
            counter++;
    }
    fees_bank += cliente[i].have_fees;
    cliente[i].have_fees = 0;
    species_bank += cliente[i].have_species;
    cliente[i].have_species = 0;
    subsidy_bank = 100000;
    cliente[i].have_subsidy = 0;
    sem_post(&semaphore_thread);
    
    
}


int main(){
    int group = GRUPO;
    srand(time(NULL));
    pthread_t tid[group];
    sem_init(&semaphore_thread, 0, 1);
    int w = 1, value = 10, back = 0, i;
    float em_especie = 0, em_taxa = 0;
    float value_species, value_subsidy, value_fees;
    for(i = 0; i < group; i++){
        printf("\n");
        cliente[i].value_imovel = (rand() % 450000) + 50000;
        printf("Imovel: %f\n", cliente[i].value_imovel);
        cliente[i].have_subsidy = (rand() % 2);
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
        cliente[i].have_fees = (cliente[i].value_imovel * 0.05) * (cliente[i].have_fees/100);
        em_especie += (cliente[i].have_species);
        em_taxa += cliente[i].have_fees;
    }

    for(i = 0; i < group;i++){
        pthread_create(&tid[i], NULL, verification_value, (void *)i);
    }
//    species_bank += (species_bank * 0.5);
//    fees_bank += (fees_bank * 0.5);
    for(i = 0; i < group; i++){
        pthread_join(tid[i], NULL);
    }
    sem_destroy(&semaphore_thread);
    printf("\nTotal em imoveis devolvido pelos clientes: %f\nTotal em taxa devolvido pelos clientes: %f\n", em_especie, em_taxa);
    printf("\n");
    printf("Os Clientes entregaram todos os recursos, atualmente o banco possui\nEm especie: %f\nEm taxa: %f\nEm subisidu: %f", species_bank, fees_bank, subsidy_bank);

}
