#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

#define numero_hilos 10

// Imprimir saludo con el id del hilo
void *imprimir_hola_mundo(void *id_hilo) {
    int id = (intptr_t) id_hilo; // Para sistemas de 64 bits
    printf("Hola mundo. Desde hilo %d\n", id);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

    pthread_t hilos[numero_hilos];

    // El hilo principal crea N hilos
    for(int i = 0; i < numero_hilos; i++) {
        printf("Hilo principal. Creando hilo %d\n", i);
        pthread_create(&hilos[i], NULL, imprimir_hola_mundo, (void *)(intptr_t) i);
    }

    // El hilo principal espera a los demas hilos
    for(int i = 0; i < numero_hilos; i++) {
        pthread_join(hilos[i], NULL);
    }

    return 0;
}