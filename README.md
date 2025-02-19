Leitura do Joystick (ADC - Conversor Analógico-Digital)

Captura os valores dos eixos X e Y do joystick através dos pinos GPIO26 e GPIO27 (ADC).
O valor varia de 0 a 4095, onde 2048 é a posição central.

##Controle de LEDs RGB via PWM

O brilho do LED Azul é ajustado conforme o eixo Y.
O brilho do LED Vermelho é ajustado conforme o eixo X.
Usa PWM (Modulação por Largura de Pulso) para suavizar a transição do brilho.
O LED Verde pode ser ligado/desligado ao pressionar o botão do joystick.

##Exibição do Quadrado no Display OLED SSD1306 (I2C)

O display SSD1306 (128x64 pixels) recebe comandos via I2C (GPIO14 e GPIO15).
Um quadrado 8x8 pixels é desenhado e se move conforme a posição do joystick.
A borda do display alterna o estilo ao pressionar o botão do joystick.

##Interrupções (IRQ) para Botões

Botão do Joystick (GPIO22): Alterna o LED Verde e a borda do display a cada pressionamento.
Botão A (GPIO5): Liga/desliga os LEDs RGB controlados por PWM.
Debouncing via software evita leituras falsas ao pressionar os botões rapidamente.

##Código Otimizado e Estruturado

Implementação modular, com funções organizadas e bem comentadas.
Atualização suave com tempo de resposta rápido.


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
