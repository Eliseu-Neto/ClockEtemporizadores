#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "hardware/i2c.h"
#include "ssd1306.h"

// Definição dos pinos
#define LED_RED 11
#define LED_GREEN 12
#define LED_BLUE 13
#define BUTTON_JOYSTICK 22
#define BUTTON_A 5
#define JOYSTICK_X 26
#define JOYSTICK_Y 27
#define I2C_SDA 14
#define I2C_SCL 15

// Variáveis globais
bool led_green_state = false;
bool led_pwm_enabled = true;
uint8_t border_style = 0;
uint8_t square_x = 60, square_y = 28;

// Configuração do display SSD1306
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
ssd1306_t oled;

// Configuração do PWM
uint slice_red, slice_blue;
uint channel_red, channel_blue;

// Função para mapear valores (ex: ADC → PWM)
uint16_t map_value(uint16_t value, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max) {
    return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Atualiza os LEDs PWM com base nos valores do joystick
void update_leds(uint16_t x, uint16_t y) {
    if (!led_pwm_enabled) return;
    uint16_t brightness_red = abs(2048 - x) * 255 / 2048;  
    uint16_t brightness_blue = abs(2048 - y) * 255 / 2048;  
    pwm_set_gpio_level(LED_RED, brightness_red * brightness_red);
    pwm_set_gpio_level(LED_BLUE, brightness_blue * brightness_blue);
}

// Atualiza a posição do quadrado no display
void update_display(uint16_t x, uint16_t y) {
    ssd1306_clear(&oled);
    square_x = map_value(x, 0, 4095, 0, SCREEN_WIDTH - 8);
    square_y = map_value(y, 0, 4095, 0, SCREEN_HEIGHT - 8);
    ssd1306_draw_rect(&oled, square_x, square_y, 8, 8);
    if (border_style % 2 == 1) ssd1306_draw_rect(&oled, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    ssd1306_show(&oled);
}

// Interrupção do botão do joystick
void joystick_button_irq(uint gpio, uint32_t events) {
    static uint64_t last_press = 0;
    uint64_t time_now = time_us_64();
    if (time_now - last_press < 200000) return; // Debouncing (200ms)
    last_press = time_now;
    led_green_state = !led_green_state;
    gpio_put(LED_GREEN, led_green_state);
    border_style++;
}

// Interrupção do botão A
void button_a_irq(uint gpio, uint32_t events) {
    static uint64_t last_press = 0;
    uint64_t time_now = time_us_64();
    if (time_now - last_press < 200000) return; // Debouncing (200ms)
    last_press = time_now;
    led_pwm_enabled = !led_pwm_enabled;
}

// Configuração do PWM para LEDs RGB
void setup_pwm(uint gpio, uint *slice, uint *channel) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    *slice = pwm_gpio_to_slice_num(gpio);
    *channel = pwm_gpio_to_channel(gpio);
    pwm_set_wrap(*slice, 255);
    pwm_set_chan_level(*slice, *channel, 0);
    pwm_set_enabled(*slice, true);
}

// Configuração inicial
void setup() {
    stdio_init_all();

    // Configuração de GPIOs
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    
    // Configuração PWM para LEDs RGB
    setup_pwm(LED_RED, &slice_red, &channel_red);
    setup_pwm(LED_BLUE, &slice_blue, &channel_blue);

    // Configuração do ADC
    adc_init();
    adc_gpio_init(JOYSTICK_X);
    adc_gpio_init(JOYSTICK_Y);

    // Configuração dos botões com interrupção
    gpio_set_irq_enabled_with_callback(BUTTON_JOYSTICK, GPIO_IRQ_EDGE_FALL, true, &joystick_button_irq);
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &button_a_irq);

    // Configuração do display SSD1306
    i2c_init(i2c0, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    ssd1306_init(&oled, 128, 64, 0x3C, i2c0);
}

// Loop principal
void loop() {
    adc_select_input(0);
    uint16_t x_value = adc_read();
    
    adc_select_input(1);
    uint16_t y_value = adc_read();

    update_leds(x_value, y_value);
    update_display(x_value, y_value);

    sleep_ms(50); // Atualização suave
}

// Programa principal
int main() {
    setup();
    while (1) {
        loop();
    }
}
