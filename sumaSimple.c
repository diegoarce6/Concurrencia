/*
*
* Condiciones de carrera y exclusion mutua
*
* Este programa presenta multiples hilos intentando acceder a una variable global 
* compartida para modificarla. Para evitar condiciones de carrera e inconsistencia de datos,
* se utiliza pthread_mutex_t
* 
* Compilacion: gcc sumaSimple.c -o sumaSimple -pthread
*/

#include <stdio.h>
#include <pthread.h>
#include <stdint.h> // para mayor portabilidad :)

#define NUMERO_HILOS 5
#define MAX 1000000
pthread_mutex_t candado;
int SUMA = 0;

// Esta funcion hace incrementos a la variable compartida (SUMA) MAX veces por cada hilo
void *sumar(void *tid) {

   int id_hilo = (intptr_t) tid; // casting para compatibilidad en sistemas de 64 bits

   for (int i = 0; i < MAX; i++) {
      
      pthread_mutex_lock(&candado);

      // Region critica
      SUMA++;
      
      pthread_mutex_unlock(&candado);
   }

   printf("Hilo %d termino de sumar\n", id_hilo);

   pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

   pthread_t hilos[NUMERO_HILOS];

   pthread_mutex_init(&candado, NULL); // Inicializar candado

   // El hilo principal crea N hilos y asigna un id
   for (int i = 0; i < NUMERO_HILOS; i++){
      printf("Creando hilo %d\n", i);
      pthread_create(&hilos[i], NULL, sumar, (void *)(intptr_t) i);
   }

   // EL hilo principal espera que terminen los demas hilos
   for(int i = 0; i < NUMERO_HILOS; i++) {
      pthread_join(hilos[i], NULL);
   }

   pthread_mutex_destroy(&candado); // Destruir candado --> liberar recursos

   printf("Resultado final: %d\n", SUMA);
   
   return 0;
}