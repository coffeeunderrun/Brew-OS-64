include ../toolchain.mk

SRC_PATH = ./src
INC_PATH = ./inc
OBJ_PATH = ./o
DEP_PATH = ./d

LIB_PATH = ../lib
LIB_INC = $(LIB_PATH)/inc
LIB = $(LIB_PATH)/lib.a

A_FLAGS = -f elf64 -dASM
C_FLAGS = -std=c99 -mcmodel=kernel -nostdlib -lgcc -g \
			-mno-red-zone -mno-mmx -mno-sse -mno-sse2 -mno-3dnow -masm=intel \
			-ffreestanding -fno-builtin -fno-stack-protector -fno-pic
D_FLAGS = -MM -MT $@ -MP -MF
L_FLAGS = -z max-page-size=0x1000 -T link.ld -m elf_x86_64 -Map map.txt
I_FLAGS = -I$(INC_PATH) -I$(LIB_INC)

OBJS  = $(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.c.o,$(shell find $(SRC_PATH) -name "*.c"))
OBJS += $(patsubst $(SRC_PATH)/%.s,$(OBJ_PATH)/%.s.o,$(shell find $(SRC_PATH) -name "*.s"))

DEPS  = $(patsubst $(SRC_PATH)/%.c,$(DEP_PATH)/%.d,$(shell find $(SRC_PATH) -name "*.c"))

BUILD = build.txt
BUILD_FLAGS  = --defsym _build_date=$$(date +'%Y%m%d')
BUILD_FLAGS += --defsym _build_number=$$(cat $(BUILD))

all: kernel.bin

kernel.bin: $(OBJS) $(LIB)
	@echo "  Linking      $@"
	@$(LD) $(L_FLAGS) $(BUILD_FLAGS) -o $@ $^ 
	@if ! test -f $(BUILD); then echo 0 > $(BUILD); fi
	@echo $$(($$(cat $(BUILD)) + 1)) > $(BUILD)

$(OBJ_PATH)/%.s.o: $(SRC_PATH)/%.s
	@echo "  Assembling $@"
	@$(AS) $< $(A_FLAGS) -o $@

$(OBJ_PATH)/%.c.o: $(SRC_PATH)/%.c
	@echo "  Compiling  $@"
	@$(CC) $(C_FLAGS) -c $(I_FLAGS) $< -o $@
	@$(CC) $(C_FLAGS) $(D_FLAGS) $(DEP_PATH)/$*.d $(I_FLAGS) $<

clean:
	@rm -fr *.bin o/*.o d/*.d

-include $(DEPS)
