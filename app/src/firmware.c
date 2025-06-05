#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

#include <stdint.h>

#define CPU_FREQ (84000000) // 84 MHz
#define SYSTICK_FREQ (1000) // 1 kHz

#define LED_PORT (GPIOA)
#define LED_PIN (GPIO5)

volatile uint64_t ticks = 0;

static void rcc_setup(void) {
    rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_3V3_84MHZ]);
}

static void gpio_setup(void) {
    rcc_periph_clock_enable(RCC_GPIOA);
    gpio_mode_setup(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_PIN);
}

static void systick_setup(void) {
    systick_set_frequency(SYSTICK_FREQ, CPU_FREQ);
    systick_counter_enable();
    systick_interrupt_enable();
}

// sys_tick_handler will be registered to NVIC
// It has to be external and not static to be recognized by the linker
void __attribute__((interrupt)) sys_tick_handler(void);
void sys_tick_handler(void) { ticks++; }

static uint64_t get_ticks(void) { return ticks; }

int main(void) {
    rcc_setup();
    gpio_setup();
    systick_setup();

    uint64_t start_ticks = get_ticks();

    while (1) {
        if (get_ticks() - start_ticks >= 1000) {
            gpio_toggle(LED_PORT, LED_PIN);
            start_ticks = get_ticks();
        }
    }

    // Never return
    return 0;
}
