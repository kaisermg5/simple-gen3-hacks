#-------------------------------------------------------------------------------

ifeq ($(strip $(DEVKITARM)),)
$(error Please set DEVKITARM in your environment. export DEVKITARM=/path/to/devkitARM)
endif

include $(DEVKITARM)/base_tools

#-------------------------------------------------------------------------------

SRC := src

export ARMIPS ?= armips
LD := $(PREFIX)ld
CPP := $(PREFIX)cpp
COMMON := ../common


ASFLAGS := -mthumb
WARNINGFLAGS :=	-Wall -Wno-discarded-array-qualifiers \
	-Wno-int-conversion
CFLAGS := -mthumb -mno-thumb-interwork -mcpu=arm7tdmi -mtune=arm7tdmi \
	-march=armv4t -mlong-calls -fno-builtin $(WARNINGFLAGS)  \
	-O -finline 
CPPFLAGS = -I $(COMMON)/pokeemerald_include -I $(COMMON)/agbcc_include -I $(COMMON)/include -I include
#-MMD
LDFLAGS := -r -T $(COMMON)/linker.ld 

#-------------------------------------------------------------------------------
	
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

# Sources
C_SRC := $(call rwildcard,$(SRC),*.c)
S_SRC := $(call rwildcard,$(SRC),*.s)

#-------------------------------------------------------------------------------


.PHONY: all clean clean_objs
all: bpee bpre
	
clean:
	rm -rf build

clean_objs:
	rm -f build/*/*/*.o build/*/*.o

bpee: BPEE
bpre: BPRE

.SECONDEXPANSION:
define RULES
$1_BASEROM := $1.gba
$1_BUILD_DIR := build/$1
$1_BINARY := $$($1_BUILD_DIR)/linked.o
$1_OUTPUT := $$($1_BUILD_DIR)/rom.gba

# Binaries
$1_C_OBJ := $$(C_SRC:%=$$($1_BUILD_DIR)/%.o)
$1_S_OBJ := $$(S_SRC:%=$$($1_BUILD_DIR)/%.o)

$1_ALL_OBJ := $$($1_C_OBJ) $$($1_S_OBJ)

$1_LINKERS := $(COMMON)/$1.ld $(COMMON)/$1_wram.ld $(COMMON)/$1_local.ld
$1_EXTRA_LDFLAGS := $$(foreach f,$$($1_LINKERS),-T $$f)

$1: $$($1_OUTPUT)

.PHONY: $$($1_OUTPUT)

$$($1_OUTPUT): main.s $$($1_BINARY)
	$(ARMIPS) main.s -sym $$($1_BUILD_DIR)/offsets.txt -strequ output_game $$@ -strequ input_game $$($1_BASEROM) -strequ relocatable_obj $$($1_BINARY)

$$($1_BINARY): $$($1_ALL_OBJ) $$($1_LINKERS)
	$(LD) $(LDFLAGS) $$($1_EXTRA_LDFLAGS) -o $$@ $$^

$$($1_BUILD_DIR)/%.c.o: %.c
	mkdir -p $$(@D)
	$(CPP) $(CPPFLAGS) $$< -D $1 | $(CC) $(CFLAGS) -o $$@ -c -xc -

$$($1_BUILD_DIR)/%.s.o: %.s
	mkdir -p $$(@D)
	$(CPP) $(CPPFLAGS) $$< -D $1 | $(AS) $(ASFLAGS) -o $$@


#$1_ALL_DEPS := $$($1_ALL_OBJ:%.o=%.d)
#-include $$($1_ALL_DEPS)
endef

$(eval $(call RULES,BPEE))
$(eval $(call RULES,BPRE))






