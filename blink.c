#include "pico/stdlib.h"
#include "hardware/timers.h"

#define LED_VERMELHO 15
#define LED_AMARELO 14
#define LED_VERDE 13

enum estado_semaforo {
    VERMELHO,
    AMARELO,
    VERDE
};

enum estado_semaforo estado_atual = VERMELHO;

bool repeating_timer_callback(struct repeating_timer *t) {
    // Alterar o estado do semáforo
    switch (estado_atual) {
        case VERMELHO:
            gpio_put(LED_VERMELHO, 0);   // Desliga o LED vermelho
            gpio_put(LED_AMARELO, 0);    // Desliga o LED amarelo
            gpio_put(LED_VERDE, 1);      // Liga o LED verde
            estado_atual = VERDE;        // Próximo estado
            break;
        case VERDE:
            gpio_put(LED_VERMELHO, 0);   // Desliga o LED vermelho
            gpio_put(LED_AMARELO, 1);    // Liga o LED amarelo
            gpio_put(LED_VERDE, 0);      // Desliga o LED verde
            estado_atual = AMARELO;      // Próximo estado
            break;
        case AMARELO:
            gpio_put(LED_VERMELHO, 1);   // Liga o LED vermelho
            gpio_put(LED_AM
