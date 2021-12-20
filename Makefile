HEADERS= common.hpp mem.hpp regs.hpp rs.hpp types.hpp instruction.hpp defs.hpp cdb.hpp globals.hpp params.h
SRCS= main.cpp rs.cpp  issue.cpp can_exec.cpp exec.cpp wb.cpp globals.cpp utils.cpp decode.cpp update.cpp
GCC= g++
FLAGS= -g 



tomasulo: $(HEADERS) $(SRCS)
		$(GCC) $(SRCS) $(FLAGS) -o tomasulo
