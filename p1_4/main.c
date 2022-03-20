#include <board.h>
#include <periph/gpio.h>
#include "periph_conf.h"
#include <stdio.h>
#include "xtimer.h"

int password[] = {UNWD_GPIO_6,UNWD_GPIO_5,UNWD_GPIO_4,UNWD_GPIO_7};
int len = 4;
int idx = 0;
xtimer_t t0;

void callback0(void *arg) {
    (void)(arg);
    for (int i=0; i<len; i++) {
        gpio_irq_enable(password[i]);
    }
}

void logic(int btn_pin) {
    if (password[idx] == btn_pin) {
    	printf("Match: %d\n\r", idx);
	idx++;
    } else {
	printf("Mismatch\n\r");
	idx = 0;
	if (password[idx] == btn_pin) {
	    logic(btn_pin);
	}
    }
    if (len == idx) {
    	printf("Correct password!\n\r");
	idx = 0;
	gpio_toggle(LED0_PIN);
    }
}
void btn_handler0(void *arg) {
    for (int i=0; i<len; i++) {
        gpio_irq_disable(password[i]);
    }
    logic((int)arg);
    xtimer_set(&t0, 300*1000);
}

int main(void) {
    t0.callback = callback0;
    gpio_init(LED0_PIN, GPIO_OUT);
    gpio_init_int(UNWD_GPIO_4, GPIO_IN_PU, GPIO_FALLING, btn_handler0, (void*)UNWD_GPIO_4);
    gpio_init_int(UNWD_GPIO_5, GPIO_IN_PU, GPIO_FALLING, btn_handler0, (void*)UNWD_GPIO_5);
    gpio_init_int(UNWD_GPIO_6, GPIO_IN_PU, GPIO_FALLING, btn_handler0, (void*)UNWD_GPIO_6);
    gpio_init_int(UNWD_GPIO_7, GPIO_IN_PU, GPIO_FALLING, btn_handler0, (void*)UNWD_GPIO_7);
    while (1) {
    }
    return 0;
}
