#include <board.h>
#include <periph/gpio.h>
#include "periph_conf.h"
#include "mutex.h"

static char my_stack_1[THREAD_STACKSIZE_DEFAULT];
static char my_stack_2[THREAD_STACKSIZE_DEFAULT];

mutex_t m1;
mutex_t m2;

void delay_ms(const uint16_t ms) {
	uint32_t i = ms * 4000;
	while (i-- > 0) {
		__asm("nop");
	}
}

void* thread_1(void* arg) {
    (void)arg;
    printf("\n\rthread 1 started");
    mutex_init(&m1);
    mutex_lock(&m1);
    printf("\n\rthread 1 acquired m1");
    thread_yield();
    mutex_lock(&m2);
    printf("\n\rthread 1 acquired m2");
    mutex_unlock(&m2);
    mutex_unlock(&m1);
    return NULL;
}
void* thread_2(void* arg) {
    (void)arg;
    printf("\n\rthread 2 started");
    mutex_init(&m2);
    mutex_lock(&m2);
    printf("\n\rthread 2 acquired m2");
    thread_yield();
    mutex_lock(&m1);
    printf("\n\rthread 2 acquired m1");
    mutex_unlock(&m1);
    mutex_unlock(&m2);
    return NULL;
}

int main(void) {
    printf("\n\r");
    thread_create(my_stack_1, sizeof(my_stack_1), 5, THREAD_CREATE_WOUT_YIELD, thread_1, NULL, "thread_1");
    thread_create(my_stack_2, sizeof(my_stack_2), 5, THREAD_CREATE_WOUT_YIELD, thread_2, NULL, "thread_2");
    thread_yield();
    printf("\n\r");
    printf("0");

    return 0;
}
