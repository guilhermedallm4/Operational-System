
// 1- Papel
// 2- Tesoura
// 3- Pedra
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int vector[3];
void startJokenpo(int option, int rounds);
void showResults(int vector[4]);

void createNumberJokenpo(int option) {
	vector[option] = (rand() % 2) + 1;
}

int main() {
	int option = 0, rounds = 0;
	srand(time(NULL));
	do {
		printf("Whats amount players in playing jokenpo?\n Option disponible "
			   "is 2 Players, select one option please\n");
		scanf("%d", &option);
	} while (option != 2);
	printf("\nAmout rounds is playing? ");
	scanf("%d", &rounds);
	startJokenpo(option, rounds);
}

void startJokenpo(int option, int rounds) {
	int i = 0, auxRounds = 0, vectorResult[3], rc;
	pthread_t tid[option];
	for (i = 0; i < 3; i++) {
		vectorResult[i] = 0;
	}
	while (auxRounds < rounds) {
		for (i = 0; i < option; i++) {
			rc = pthread_create(&tid[i], NULL, createNumberJokenpo, (int *)i);
			if (rc) {
				exit(-1);
			}
		}

		for (i = 0; i < option; i++) {
			pthread_join(tid[i], NULL);
		}

		if (vector[0] == 1 && vector[1] != 2 && vector[1] != vector[0]) {
			vectorResult[0] += 1;

		} else if (vector[0] == 2 && vector[1] != 3 && vector[1] != vector[0]) {
			vectorResult[0] += 1;

		} else if (vector[0] == 3 && vector[1] != 1 && vector[1] != vector[0]) {
			vectorResult[0] += 1;

		} else if (vector[0] == vector[1]) {
			vectorResult[2] += 1;

		} else {
			vectorResult[1] += 1;
		}
		auxRounds++;
	}
	showResults(vectorResult);
}

void showResults(int vector[3]) {
	printf("Results of Jokenpo: \n");
	printf("Wins for player 1: %d\n", vector[0]);
	printf("Wins for player 2: %d\n", vector[1]);
	printf("A tie for players: %d", vector[2]);
}
