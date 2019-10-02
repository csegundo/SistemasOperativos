/****************************
*	CREATED BY:				*
*		- Héctor Ullate		*
*		- Carlos Segundo	*
*****************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>
#include <pthread.h>

int total_sum = 0;
sem_t sem_suma; // Semaforo para la implementacion del ejercicio

void * partial_sum(char * arg) {
  int j = 0;
  int ni = ((int*)arg)[0];
  int nf = ((int*)arg)[1];

  for (j = ni; j <= nf; ++j){
    sem_wait( &sem_suma );
    total_sum = total_sum + j;
    sem_post( &sem_suma );
  }

  pthread_exit(0);
}

int main(int argc, char *argv[]) {

  pthread_t hilos[(int)argv[1]]; // Numero de hilos que pone el usuario

  sem_init(&sem_suma, 0, 0); // Inicializamos el semaforo y shared = 0 (para hilos)

  // Creamos y lanzamos todos los hilos
  int i;
  for(i = 0; i < (int)argv[1]; ++i)
    pthread_create(&hilos[i], NULL, partial_sum, ((int)argv[2]/(int)argv[1]));

  for (i = 0; i < (int)argv[1]; ++i)
    pthread_join(&hilos[i], NULL);

  printf("total_sum=%d and it should be 50005000\n", total_sum);

  return 0;
}
