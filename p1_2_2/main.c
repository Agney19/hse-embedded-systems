#include <board.h>
#include <periph/gpio.h>
#include "periph_conf.h"

#define UNUSED(x) (void)(x)

void delay_ms(const uint16_t ms) {
    uint32_t i = ms * 4000; /* approx. value */
    while (i-- > 0) {
      __asm("nop");
    }
}

void btn_handler(void *arg) {
	UNUSED(arg);
	gpio_toggle(LED0_PIN);
	gpio_irq_disable(UNWD_GPIO_1);
	delay_ms(100);
	gpio_irq_enable(UNWD_GPIO_1);
}

int main(void) {
    gpio_init(LED0_PIN, GPIO_OUT);
    gpio_init_int(UNWD_GPIO_1, GPIO_IN_PU, GPIO_FALLING, btn_handler, NULL);
    while(1) {
    }
    return 0;
}
