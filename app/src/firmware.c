#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

#include <stdint.h>

#define LED_PORT (GPIOA)
#define LED_PIN (GPIO5)

static void rcc_setup(void) {
    rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_3V3_84MHZ]);
}

static void gpio_setup(void) {
    rcc_periph_clock_enable(RCC_GPIOA);
    gpio_mode_setup(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_PIN);
}

static void delay_cycle(uint32_t cycles) {
    for (uint32_t i = 0; i < cycles; i++) {
        __asm__("nop"); // No operation, just a delay
    }
}

int main(void) {
    rcc_setup();
    gpio_setup();

    while (1) {
        gpio_toggle(LED_PORT, LED_PIN);
        delay_cycle(48000000 / 4);
    }

    // Never return
    return 0;
}
