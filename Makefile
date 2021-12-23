HEADERS= common.hpp mem.hpp regs.hpp rs.hpp types.hpp instruction.hpp defs.hpp cdb.hpp globals.hpp params.h
SRCS= main.cpp rs.cpp  issue.cpp can_exec.cpp exec.cpp wb.cpp globals.cpp utils.cpp files.cpp update.cpp
GCC= g++
FLAGS= -g --std=c++11
TARGET_NAME=tomasulo
TARGET_DIR=.
TARGET= $(TARGET_DIR)/$(TARGET_NAME)

TEST_DIR= tests
TESTS= beq.txt
OUTPUT_DIR= results
RESULTS= $(OUTPUT_DIR)/beq.txt\
			$(OUTPUT_DIR)/jal_jalr.txt\
			$(OUTPUT_DIR)/loop.txt\
			$(OUTPUT_DIR)/diffPc.txt\
			$(OUTPUT_DIR)/deps.txt

tomasulo: $(HEADERS) $(SRCS)
		$(GCC) $(SRCS) $(FLAGS) -o  $(TARGET)

.PHONY: tests
tests: $(RESULTS)

$(RESULTS): $(OUTPUT_DIR)/%.txt: $(TEST_DIR)/%.txt
		$(TARGET) $< $@