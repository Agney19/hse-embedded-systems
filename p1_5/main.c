#include <board.h>
#include <periph/gpio.h>
#include "periph_conf.h"
#include "xtimer.h"

#define UNUSED(x) (void)(x)

void delay_ms(const uint16_t ms) {
    uint32_t i = ms * 4000; /* approx. value */
    while (i-- > 0) {
      __asm("nop");
    }
}

const uint32_t threshold = 2000000;
const int red_light_pin = UNWD_GPIO_28;
const int yellow_light_pin = UNWD_GPIO_27;
const int green_light_pin = UNWD_GPIO_26;
int lights[] = {green_light_pin, yellow_light_pin, red_light_pin, yellow_light_pin};
int light_times[] = {3000000, 500000, 6000000, 500000};
char* light_labels[] = {"GREEN", "YELLOW", "RED", "YELLOW"};
int light_number = sizeof(lights)/sizeof(lights[0]);
int active_light_idx = 0;
bool is_hastened = false;
uint32_t toggle_time;

void btn_handler(void *arg) {
	UNUSED(arg);
	uint32_t cur_time = xtimer_now_usec();
	printf("Press time: %ld, Planned toggle time: %ld\n\r", cur_time, toggle_time);
	if (is_hastened) {
		printf("Lights are already hastened. Ignoring...\n\r");
		return;
	}
        if (lights[active_light_idx] != red_light_pin) {
		printf("Lights can be hastened only when it's red light. Ignoring...\n\r");
		return;
	}
	if (cur_time >= toggle_time - threshold) {
		printf("Green light will come soon without hastening. Ignoring...\n\r");
		return;
	}
	toggle_time = cur_time + threshold;
	is_hastened = true;
	printf("Successfully hastened. Next toggle will occur in %ld\n\r", toggle_time);
	gpio_irq_disable(UNWD_GPIO_1);
	delay_ms(200);
	gpio_irq_enable(UNWD_GPIO_1);
}

int main(void) {
    gpio_init(red_light_pin, GPIO_OUT);
    gpio_init(yellow_light_pin, GPIO_OUT);
    gpio_init(green_light_pin, GPIO_OUT);
    gpio_init_int(UNWD_GPIO_1, GPIO_IN_PU, GPIO_FALLING, btn_handler, NULL);
    
    gpio_set(lights[active_light_idx]);
    toggle_time = xtimer_now_usec() + light_times[active_light_idx];
    uint32_t cur_time;
    while(1) {
	    cur_time = xtimer_now_usec();
	    if (toggle_time <= cur_time) {
	    	gpio_clear(lights[active_light_idx]);
		is_hastened = false;
		if (active_light_idx == light_number - 1) {
		    active_light_idx = 0;
		} else {
		    active_light_idx++;
		}
	    	gpio_set(lights[active_light_idx]);
		toggle_time = cur_time + light_times[active_light_idx];
		printf("%s light is ON (from %ld - to %ld)\n\r", light_labels[active_light_idx], cur_time, toggle_time);
	    }
    }
    return 0;
}
