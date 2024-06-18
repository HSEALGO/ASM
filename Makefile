.PHONY: default
default: all

# -------------------- Config --------------------
BUILD_TYPE ?= Release
BUILD_DIR ?= build

SRC_DIRS := src
INC_DIRS := .
EXEC_SRCS := src/main.c src/test.c

CC := gcc
NASM := nasm

CFLAGS += -no-pie -m32
NASMFLAGS += -f elf
LDFLAGS += -no-pie -m32

ifeq ($(BUILD_TYPE),Debug)
	CFLAGS += -Wall -Wextra -g3 -O0 -fsanitize=undefined,address
	LDFLAGS += -fsanitize=undefined,address
	NASMFLAGS += -g
endif

.PHONY: test
test: $(BUILD_DIR)/src/test
	@echo Running tests...
	@$(BUILD_DIR)/src/test

.PHONY: run
run: $(BUILD_DIR)/src/main
	@echo Running with args: $(ARGS)
	@$(BUILD_DIR)/src/main $(ARGS)

# -------------------- Internal Variables --------------------
SRCS := $(shell find $(SRC_DIRS) -name *.c -or -name *.nasm)
OBJS := $(patsubst %,$(BUILD_DIR)/%.o,$(basename $(SRCS)))
DEPS := $(patsubst %,$(BUILD_DIR)/%.d,$(basename $(SRCS)))

EXEC_OBJS := $(patsubst %,$(BUILD_DIR)/%.o,$(basename $(EXEC_SRCS)))
NO_EXEC_OBJS := $(filter-out $(EXEC_OBJS),$(OBJS))
EXECS := $(addprefix $(BUILD_DIR)/,$(basename $(EXEC_SRCS)))

# INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CFLAGS += $(INC_FLAGS) -MMD -MP

# -------------------- Targets --------------------
.PHONY: all
all: $(EXECS) integral

integral: $(BUILD_DIR)/src/main
	@echo Creating symbolic link...
	@ln -sf $(BUILD_DIR)/src/main ./integral

.PHONY: clean
clean:
	@echo Cleaning...
	@rm -rf $(BUILD_DIR)
	@rm -rf ./integral

# Recompile when flags change
.PHONY: flags

FLAG_TYPES := C NASM LD
FLAG_TARGETS := $(FLAG_TYPES:%=$(BUILD_DIR)/%FLAGS.txt)

$(foreach FLAG_TYPE,$(FLAG_TYPES),$(eval $(FLAG_TYPE)FLAGS_FILE := $(BUILD_DIR)/$(FLAG_TYPE)FLAGS.txt))

$(FLAG_TARGETS): $(BUILD_DIR)/%FLAGS.txt: flags
	@{ \
		mkdir -p $(BUILD_DIR); \
		TMP=$$(mktemp); \
		echo $($*FLAGS) >> $$TMP; \
		cmp -s $$TMP $@ || mv -f $$TMP $@; \
	}

# Compile binaries
$(EXECS): %: %.o $(NO_EXEC_OBJS) $(LDFLAGS_FILE)
	@echo Compiling $@...
	@$(CC) $(NO_EXEC_OBJS) $(LDFLAGS) $< -o $@ -lm

# .c to .o
$(BUILD_DIR)/%.o: %.c $(CFLAGS_FILE)
	@echo Compiling $@...
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# .nasm to .o
$(BUILD_DIR)/%.o: %.nasm $(NASMFLAGS_FILE)
	@echo Compiling $@...
	@mkdir -p $(dir $@)
	@$(NASM) $(NASMFLAGS) $< -o $@

# Add header dependencies
-include $(DEPS)
