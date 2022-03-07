#include <board.h>
#include <periph/gpio.h>
#include "periph_conf.h"

static char my_stack[THREAD_STACKSIZE_DEFAULT];

int g = 1;
const int gc = 2;
static int gs = 3;
static const int gsc = 4;

void* my_thread(void* arg) {
	(void)(arg);
	int p = 1;
	const int pc = 2;
	static int ps = 3;
	static const int psc = 4;
	printf("Process variables:\n\r %p - const %p - static %p - static const %p\n\r", &p, &pc, &ps, &psc);
	return arg;
}

void btn_handler(void *arg) {
	(void)(arg);
	int i = 1;
	const int ic = 2;
	static int is = 3;
	static const int isc = 4;
	printf("Interruption variables:\n\r %p - const %p - static %p - static const %p\n\r", &i, &ic, &is, &isc);
}

void print_from_function(void) {
    int f = 1;
    const int fc = 2;
    static int fs = 3;
    static const int fsc = 4;
    printf("Function local variables:\n\r %p - const %p - static %p - static const %p\n\r", &f, &fc, &fs, &fsc);
}

int main(void) {
    gpio_init_int(UNWD_GPIO_1, GPIO_IN_PU, GPIO_FALLING, btn_handler, NULL);
    int l = 1;
    const int lc = 2;
    static int ls = 3;
    static const int lsc = 4;

    printf("\n\rMain local variables:\n\r %p - const %p - static %p - static const %p\n\r", &l, &lc, &ls, &lsc);
    print_from_function();
    printf("Global variables:\n\r %p - const %p - static %p - static const %p\n\r", &g, &gc, &gs, &gsc);
    thread_create(my_stack, sizeof(my_stack), THREAD_PRIORITY_MAIN-1, THREAD_CREATE_STACKTEST, my_thread, (void*)NULL, "My thread");
    while(1) {
    }
    return 0;
}
