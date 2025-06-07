#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>

#include <stdint.h>

#define CPU_FREQ (84000000) // 84 MHz
#define SYSTICK_FREQ (1000) // 1 kHz

// freq := CPU_FREQ / ((PRESCALAR + 1) * (ARR_VALUE + 1))
// freq will be 1000 Hz
#define PRESCALAR (84)
#define ARR_VALUE (1000)

#define LED_PORT (GPIOA)
#define LED_PIN (GPIO5)

volatile uint64_t ticks = 0;

static void rcc_setup(void) {
    rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_3V3_84MHZ]);
}

static void gpio_setup(void) {
    rcc_periph_clock_enable(RCC_GPIOA);
    gpio_mode_setup(LED_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, LED_PIN);
    gpio_set_af(LED_PORT, GPIO_AF1, LED_PIN);
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

static void timer_setup(void) {
    rcc_periph_clock_enable(RCC_TIM2);

    timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

    // Setup PWM mode
    // output compare mode
    timer_set_oc_mode(TIM2, TIM_OC1, TIM_OCM_PWM1);

    // Enable PWM output on channel 1
    timer_enable_counter(TIM2);
    timer_enable_oc_output(TIM2, TIM_OC1);

    // Setup frequency and resolution
    timer_set_prescaler(TIM2, PRESCALAR);
    timer_set_period(TIM2, ARR_VALUE);
}

static void timer_set_duty_cycle(float duty_cycle) {
    // duty cycle = (ccr / arr) * 100
    // ccr = (duty_cycle / 100) * arr
    uint32_t ccr_value = (uint32_t)((duty_cycle / 100.0f) * ARR_VALUE);
    timer_set_oc_value(TIM2, TIM_OC1, ccr_value);
}

int main(void) {
    rcc_setup();
    gpio_setup();
    systick_setup();
    timer_setup();

    uint64_t start_ticks = get_ticks();
    float duty_cycle = 0.0f;

    while (1) {
        if (get_ticks() - start_ticks >= 10) {
            duty_cycle += 1.0f;
            if (duty_cycle > 100.0f) {
                duty_cycle = 0.0f; // Reset duty cycle after reaching 100%
            }
            timer_set_duty_cycle(duty_cycle);
            start_ticks = get_ticks();
        }
    }

    // Never return
    return 0;
}
