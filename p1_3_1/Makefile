# name of your application
APPLICATION = p1_3_1

# If no BOARD is found in the environment, use this default:
BOARD ?= unwd-range-l1-r3

CFLAGS += -DITERATIONS=10000 -DPERFORMANCE_RUN=1

LINKFLAGS += -u _printf_float

USEMODULE += periph_gpio_irq

USEMODULE += xtimer

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(HOME)/RIOT/

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

WERROR = 0

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include
