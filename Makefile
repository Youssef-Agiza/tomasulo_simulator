# HEADERS= common.hpp mem.hpp regs.hpp rs.hpp types.hpp instruction.hpp defs.hpp cdb.hpp globals.hpp params.h
# SRCS= main.cpp rs.cpp  issue.cpp can_exec.cpp exec.cpp wb.cpp globals.cpp utils.cpp files.cpp update.cpp
HEADERS= $(wildcard src/*.h) $(wildcard src/*.hpp) 
SRCS = $(wildcard src/*.cpp)


GCC= g++
FLAGS= -g --std=c++11
TARGET_NAME=tomasulo
TARGET_DIR=.
TARGET= $(TARGET_DIR)/$(TARGET_NAME)



tomasulo: $(HEADERS) $(SRCS)
		$(GCC) $(SRCS) $(FLAGS) -o  $(TARGET)


TEST_DIR= tests
OUTPUT_DIR= results
#RESULTS= $(OUTPUT_DIR)/beq.txt\
			$(OUTPUT_DIR)/load_store.txt \
			$(OUTPUT_DIR)/jal_jalr.txt\
			$(OUTPUT_DIR)/loop.txt\
			$(OUTPUT_DIR)/diffPc.txt\
			$(OUTPUT_DIR)/deps.txt\

RESULTS= $(wildcard $(OUTPUT_DIR)/*.txt)

.PHONY: tests
tests: $(RESULTS)

$(RESULTS): $(OUTPUT_DIR)/%.txt: $(TEST_DIR)/%.txt
		$(TARGET) $< $@