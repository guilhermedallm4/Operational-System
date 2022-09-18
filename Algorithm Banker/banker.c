#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int possui;
    int precisa;
} Cliente;

int banqueiro = 0;

int main(){
    int value = 0;
    int max = 0, aux = 0, total = 0;
    srand(time(NULL));
    printf("Digite quantos clientes ira ter: ");
    scanf("%d", &value);
    Cliente cliente[value], *initial; 
    int i;
    for(i=0;i<value;i++){
            cliente[i].possui = (rand() % 10) + 1;
            cliente[i].precisa = cliente[i].possui + (rand() % 3) + 1;
            banqueiro = (rand() % 6) + 1;
    }
    printf("Banqueiro possui: %d\n", banqueiro);
    for(i=0;i<value;i++){
        printf("Cliente %d:\n", i);
        printf("Possui: %d \n Precisa: %d\n", cliente[i].possui, cliente[i].precisa);
    }
    printf("Total que se precisa %d\n", aux);
    aux = 0;
    i = 0;
    while(max < value){
        if(i == value){
            i = 0;
        }
        if((cliente[i].precisa - cliente[i].possui) <= banqueiro){
            if(cliente[i].precisa != 0 && cliente[i].possui != 0){
                aux = cliente[i].precisa - cliente[i].possui; 
                banqueiro -= aux;
                cliente[i].possui += aux;
                printf("Banqueiro possui: %d\n", banqueiro);
                printf("E emprestou %d para o %d\n", aux, i);
                sleep(3);
                banqueiro += cliente[i].precisa;
                printf("Retornou %d\n", cliente[i].precisa);
                printf("total Banqueiro: %d\n", banqueiro);
                cliente[i].possui = 0;
                cliente[i].precisa = 0;
                max++;
            }
            
        }
        i++;

    }


    
    for(i=0;i<value;i++){
        printf("Cliente %d:\n", i);
        printf("Possui: %d \n Precisa: %d\n", cliente[i].possui, cliente[i].precisa);
    }
    printf("Total possui: %d\n", total);

}
