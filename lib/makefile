include ../toolchain.mk

SRC_PATH = ./src
INC_PATH = ./inc
OBJ_PATH = ./o
DEP_PATH = ./d

A_FLAGS = -f elf64
C_FLAGS = -std=c99 -ffreestanding -fno-builtin -fno-stack-protector -nostdlib \
			-mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2
D_FLAGS = -MM -MT $@ -MP -MF

OBJS  = $(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.c.o,$(shell find $(SRC_PATH) -name "*.c"))
OBJS += $(patsubst $(SRC_PATH)/%.s,$(OBJ_PATH)/%.s.o,$(shell find $(SRC_PATH) -name "*.s"))

DEPS  = $(patsubst $(SRC_PATH)/%.c,$(DEP_PATH)/%.d,$(shell find $(SRC_PATH) -name "*.c"))

all: lib.a

lib.a: $(OBJS)
	@$(AR) -r $@ $^

$(OBJ_PATH)/%.s.o: $(SRC_PATH)/%.s
	@echo "  Assembling $@"
	@$(AS) $< $(A_FLAGS) -o $@

$(OBJ_PATH)/%.c.o: $(SRC_PATH)/%.c
	@echo "  Compiling  $@"
	@$(CC) $(C_FLAGS) -c -I$(INC_PATH) $< -o $@
	@$(CC) $(C_FLAGS) $(D_FLAGS) $(DEP_PATH)/$*.d -I$(INC_PATH) $<

clean:
	@rm -fr *.a o/*.o d/*.d

-include $(DEPS)
