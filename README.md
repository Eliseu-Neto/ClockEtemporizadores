Explicação do Código
Pinos GPIO: A configuração dos pinos GPIO (15, 14, 13) é feita utilizando gpio_init() e gpio_set_dir(). 
O estado dos LEDs será controlado utilizando gpio_put() para acionar e desligar os LEDs.

Timer: O timer repetitivo de 3000 ms (3 segundos) é configurado com add_repeating_timer_ms(), que chama a função repeating_timer_callback a cada 3 segundos.
Dentro dessa função, o estado do semáforo é alterado com base no estado atual (Vermelho, Amarelo, Verde).

Callback: A função repeating_timer_callback() altera o estado dos LEDs, alternando entre vermelho, amarelo e verde. 
Cada vez que a função é chamada, a sequência do semáforo é atualizada, e uma mensagem é impressa na porta serial.

Loop Principal: No loop principal, a função tight_loop_contents() mantém o processador ativo, permitindo que o timer funcione corretamente. 
Não há necessidade de um loop explícito, pois a função de callback lida com a temporização.


No Wokwi (LED RGB)
Na plataforma Wokwi, você pode substituir os três LEDs vermelhos, amarelos e verdes por um LED RGB conectado aos pinos GPIO 11, 12 e 13, 
respectivamente. A lógica de controle do código permanece a mesma.
