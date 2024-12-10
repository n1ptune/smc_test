CROSS_COMPILE := aarch64-linux-gnu-
CC := $(CROSS_COMPILE)gcc
CFLAGS := -Wall -Wextra -O2
TARGET := smc_test

all: $(TARGET)

$(TARGET): smc_test.c
	$(CC) $(CFLAGS) -o $(TARGET) smc_test.c

clean:
	rm -f $(TARGET)

.PHONY: all clean