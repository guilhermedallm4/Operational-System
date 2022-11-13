#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <math.h>
#include <unistd.h>
#define GRUPO 15;

float species_bank = 500000, subsidy_bank = 100000, fees_bank = 30000;
int value = 0;
int order[14], indice = 0;



typedef struct{
    float have_fees;
    float have_subsidy;
    float have_species;
    float value_imovel;
}Cliente;


Cliente cliente[15];

sem_t semaphore_thread;
sem_t recurso;

void *verification_value(void *args){
    float parcela_specie = 0, parcela_fees;
    float total_specie = 0, total_fees;
    float value_fees, value_specie, value_subsidy;
    int counter = 0;
    int i;
    sem_wait(&semaphore_thread);
    i = (int *)args;
    value_specie = cliente[i].have_species - cliente[i].have_subsidy;
    value_fees = cliente[i].have_fees;
    printf("Thread %d precisa de %.2f em especie ", i, value_specie);
    sem_post(&semaphore_thread);
    sem_wait(&recurso);
    while(value_fees > fees_bank || value_specie > species_bank || cliente[i].have_subsidy > subsidy_bank){
      printf("Thread %d aguardando recurso\n", i);
      sleep(4);
    }
    sem_post(&recurso);

    printf("\n");
    printf("\n");
    sem_wait(&semaphore_thread);
    printf("Thread %d está sendo atendido\n", i);
    
    printf("\n");
    printf("\n");
    sleep(4);
    sem_wait(&recurso);
    while(value_fees > fees_bank || value_specie > species_bank || cliente[i].have_subsidy > subsidy_bank){
      printf("Thread %d aguardando recurso\n", i);
      sleep(4);
        if(indice == 13){
        printf("Estado inseguro, encerrando processo!\n");
        return 0;
      }
      
    }
    sem_post(&recurso);
    species_bank -= value_specie;
    fees_bank -= value_fees;
    subsidy_bank -= cliente[i].have_subsidy;
    cliente[i].have_fees += value_fees;
    cliente[i].have_species += value_specie;
    while(counter < 8){
        sleep(4);
        if(counter == 0){
            parcela_specie = value_specie / 8;
            parcela_fees = value_fees / 8;
            printf("Thread %d Devolvendo em 8 parcelas o valor de %.2f em especie e %.2f em taxa\n", i, parcela_specie, parcela_fees);
            cliente[i].have_species -= parcela_specie;
            species_bank += parcela_specie;
            cliente[i].have_fees -= parcela_fees;
            fees_bank += parcela_fees;
            printf("Parcela %d: \n valor em especie: %.2f\n valor em taxa: %.2f\n", counter+1,  parcela_specie, parcela_fees);
        }
        else{
            cliente[i].have_species -= parcela_specie;
            species_bank += parcela_specie;
            cliente[i].have_fees -= parcela_fees;
            fees_bank += parcela_fees;
            printf("Thread %d Parcela %d: \n valor em especie: %.2f\n valor em taxa: %.2f\n", i, counter+1,  parcela_specie, parcela_fees);
        }    
        printf("\n");
        printf("\n");
            counter++;
    }
    subsidy_bank += cliente[i].have_subsidy;
    cliente[i].have_subsidy = 0;
    order[indice] = i;
    indice++;
    sem_post(&semaphore_thread);
    
    
}


int main(){
    int group = GRUPO;
    srand(time(NULL));
    pthread_t tid[group];
    sem_init(&semaphore_thread, 0, 4);
    sem_init(&recurso, 0, 4);
    int w = 1, back = 0, i;
    float em_especie = 0, em_taxa = 0;
    float value_species, value_subsidy, value_fees, fees_subsidy = 0.2;
    for(i = 0; i < group; i++){
        printf("\n");
        cliente[i].value_imovel = (rand() % 50000) + 450000;
        printf("Imovel: %.2f\n", cliente[i].value_imovel);
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
        em_especie += (cliente[i].value_imovel - cliente[i].have_subsidy);
        em_taxa += cliente[i].have_fees;
    }

    float subsidy_ajuste = 0;
    int ajuste = 5, initial = 0;
    while(ajuste <= 15){
     if(initial == 5){
                species_bank += (species_bank * 0.5);
                fees_bank += (fees_bank * 0.5);
                subsidy_bank += (subsidy_bank * 0.5);
                subsidy_ajuste = cliente[i].have_subsidy * 0.5;
                cliente[i].have_subsidy += subsidy_ajuste;
            }
        else if(initial == 10){
                species_bank += (species_bank * 0.5);
                fees_bank += (fees_bank * 0.5);
                subsidy_bank += (subsidy_bank * 0.5);
                subsidy_ajuste = cliente[i].have_subsidy * 0.5;
                cliente[i].have_subsidy += subsidy_ajuste;
            }
        for(i = initial; i < ajuste;i++){
            pthread_create(&tid[i], NULL, verification_value, (void *)i);
        }
        for(i = initial; i < ajuste; i++){
            pthread_join(tid[i], NULL);
        }
        initial += 5;
        ajuste += 5;
    }
    sem_destroy(&semaphore_thread);
    sem_destroy(&recurso);
    printf("\nTotal em imoveis devolvido pelos clientes: %.2f\nTotal em taxa devolvido pelos clientes: %.2f\n", em_especie, em_taxa);
    printf("\n");
    printf("Os Clientes entregaram todos os recursos, atualmente o banco possui\nEm especie: %.2f\nEm taxa: %.2f\n Em subisidu: %f", species_bank, fees_bank, subsidy_bank);
    printf("\n");
    printf("Sequência segura: \n");
    for(i = 0; i<group; i++){
        printf(" Pessoa %d ->", order[i]);
    }

}
