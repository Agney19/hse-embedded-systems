#include <board.h>
#include <periph/gpio.h>
#include "periph_conf.h"

void delay_ms(const uint16_t ms) {
    uint32_t i = ms * 4000; /* approx. value */
    while (i-- > 0) {
      __asm("nop");
    }
}

int main(void) {
    gpio_init(LED0_PIN, GPIO_OUT);
    gpio_init(UNWD_GPIO_1, GPIO_IN_PU);
    while(1) {
        if (gpio_read(UNWD_GPIO_1) == 0) {
		gpio_toggle(LED0_PIN);
	}
    }
    return 0;
}
