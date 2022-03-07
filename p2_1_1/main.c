#include <board.h>
#include <periph/gpio.h>
#include "periph_conf.h"
#include "mutex.h"

static char my_stack_1[THREAD_STACKSIZE_DEFAULT];
static char my_stack_2[THREAD_STACKSIZE_DEFAULT];
static char my_stack_3[THREAD_STACKSIZE_DEFAULT];

mutex_t m;

void delay_ms(const uint16_t ms) {
	uint32_t i = ms * 4000;
	while (i-- > 0) {
		__asm("nop");
	}
}

void* high_priority_thread(void* arg) {
    (void)arg;
    printf("\n\rhigh priority thread started");
    thread_yield();
    mutex_lock(&m);
    printf("\n\rhigh priority thread acquired mutex");
    mutex_unlock(&m);
    printf("\n\rhigh priority thread finished");
    return NULL;
}
void* medium_priority_thread(void* arg) {
    (void)arg;
    printf("\n\rmedium priority thread started");
    printf("\n\rmedium priority thread working.....");
    printf("\n\rmedium priority thread finished");
    return NULL;
}
void* low_priority_thread(void* arg) {
    (void)arg;
    printf("\n\rlow priority thread started");
    mutex_init(&m);
    mutex_lock(&m);
    printf("\n\rlow priority thread acquired mutex");
    thread_create(my_stack_3, sizeof(my_stack_3), 2, THREAD_CREATE_WOUT_YIELD, high_priority_thread, NULL, "HP");
    thread_yield();
    printf("\n\rlow priority thread resumed");
    thread_create(my_stack_2, sizeof(my_stack_2), 3, THREAD_CREATE_WOUT_YIELD, medium_priority_thread, NULL, "MP");
    thread_yield();
    printf("\n\rlow priority thread released mutex");
    mutex_unlock(&m);
    printf("\n\rlow priority thread finished");
    return NULL;
}

int main(void) {
    printf("\n\r");
    thread_create(my_stack_1, sizeof(my_stack_1), 4, THREAD_CREATE_WOUT_YIELD, low_priority_thread, NULL, "LP");
    thread_yield();
    printf("\n\r");
    printf("0");

    return 0;
}
