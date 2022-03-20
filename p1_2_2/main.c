#include <board.h>
#include <periph/gpio.h>
#include "xtimer.h"
#include "periph_conf.h"

xtimer_t t1;

void callback(void *arg) {	
	(void)(arg);
	gpio_irq_enable(UNWD_GPIO_1);
}

void btn_handler(void *arg) {
	(void)(arg);
	gpio_irq_disable(UNWD_GPIO_1);
	gpio_toggle(LED0_PIN);
	xtimer_set(&t1, 100*1000);
}

int main(void) {
    t1.callback = callback;
    gpio_init(LED0_PIN, GPIO_OUT);
    gpio_init_int(UNWD_GPIO_1, GPIO_IN_PU, GPIO_FALLING, btn_handler, NULL);
    while(1) {
    }
    return 0;
}
