#include <board.h>
#include <periph/gpio.h>
#include "periph_conf.h"
#include <stdio.h>
#include <xtimer.h>

#define UNUSED(x) (void)(x)

void delay_ms(const uint16_t ms) {
    uint32_t i = ms * 4000; /* approx. value */
    while (i-- > 0) {
      __asm("nop");
    }
}

int password[] = {UNWD_GPIO_6,UNWD_GPIO_5,UNWD_GPIO_4,UNWD_GPIO_7};
int len = sizeof(password)/sizeof(password[0]);
int idx = 0;

void btn_handler(void *arg) {
    int btn_pin = (int)arg;
    gpio_irq_disable(btn_pin);
    if (password[idx] == btn_pin) {
    	printf("Match\n\r");
	idx++;
    } else {
	printf("Mismatch. Start over\n\r");
	idx = 0;
    }
    if (len == idx) {
    	printf("Correct password!\n\r");
	idx = 0;
	gpio_toggle(LED0_PIN);
    }
    delay_ms(100);
    gpio_irq_enable(btn_pin);
}

int main(void) {
    gpio_init(LED0_PIN, GPIO_OUT);
    gpio_init_int(UNWD_GPIO_4, GPIO_IN_PU, GPIO_FALLING, btn_handler, (void*) UNWD_GPIO_4);
    gpio_init_int(UNWD_GPIO_5, GPIO_IN_PU, GPIO_FALLING, btn_handler, (void*) UNWD_GPIO_5);
    gpio_init_int(UNWD_GPIO_6, GPIO_IN_PU, GPIO_FALLING, btn_handler, (void*) UNWD_GPIO_6);
    gpio_init_int(UNWD_GPIO_7, GPIO_IN_PU, GPIO_FALLING, btn_handler, (void*) UNWD_GPIO_7);
    while (1) {
	/**for (int i = 0; i < len; i++) {
		if (irqs[i] >= 500) {
		    gpio_irq_enable(password[i]);
		    irqs[i] = -1;
		} else if (irqs[i] >= 0) {
		    irqs[i]++;
		}
	}*/
	//xtimer_now();
	//
	//printf("%d - %d - %d - %d\n\r", irqs[0], irqs[1], irqs[2], irqs[3]);
    }
    return 0;
}
