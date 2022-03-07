#include <board.h>
#include <periph/gpio.h>
#include "periph_conf.h"
#include "xtimer.h"

#define UNUSED(x) (void)(x)

const uint32_t short_delay = 80000;
const uint32_t long_delay = 800000;
uint32_t current_delay = long_delay;
int led_state = 1;
uint32_t led_start = 0;
uint32_t press_threshold = 800000;
uint32_t press_start = 0;
uint32_t zero = 0;

int main(void) {
    gpio_init(LED0_PIN, GPIO_OUT);
    gpio_init(UNWD_GPIO_1, GPIO_IN_PU);
    while (1) {
	printf("%ld - %d - %ld - %d\n\r", current_delay, led_state, press_start, gpio_read(UNWD_GPIO_1) );
	if (gpio_read(UNWD_GPIO_1) == 0) {
		if (press_start == 0) {
			press_start = xtimer_now_usec();
		}
	} else if (press_start != 0) {
		if (xtimer_now_usec() >= press_threshold + press_start) {
			 current_delay = (current_delay == long_delay) ? short_delay : long_delay;
		} else {
			if (led_state == 1) {
				led_state = 0;
				led_start = xtimer_now_usec();
			} else {
				led_state = 1;
				gpio_clear(LED0_PIN);
			}
		}
		press_start = 0;
	}	
	if (led_state == 0 && xtimer_now_usec() >= led_start + current_delay) {
		gpio_toggle(LED0_PIN);
		led_start = xtimer_now_usec();
	}
    }
    return 0;
}
