CFLAGS  ?=  -W -Wall -Wextra -Werror -Wundef -Wshadow -Wdouble-promotion \
            -Wformat-truncation -fno-common -Wconversion \
            -g3 -Os -ffunction-sections -fdata-sections -Iinclude \
            -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 $(EXTRA_CFLAGS)
LDFLAGS ?= -Tld/link.ld -nostartfiles -nostdlib --specs nano.specs -lc -lgcc -Wl,--gc-sections -Wl,-Map=$(BUILD_DIR)/$@.map

SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
HEADERS = $(wildcard $(INC_DIR)/*.h)

all: $(BUILD_DIR) $(BUILD_DIR)/firmware.bin

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

firmware.elf: $(OBJECTS)
	arm-none-eabi-gcc $(OBJECTS) $(LDFLAGS) -o $(BUILD_DIR)/$@

$(BUILD_DIR)/firmware.bin: firmware.elf
	arm-none-eabi-objcopy -O binary $(BUILD_DIR)/firmware.elf $@

flash: $(BUILD_DIR)/firmware.bin
	sudo /home/linuxbrew/.linuxbrew/bin/st-flash --reset write $< 0x08000000

clean:
	rm -rf $(BUILD_DIR)/*

compile_commands: clean
	bear -- make

.PHONY: clean flash compile_commands
