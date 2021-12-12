HEADERS= common.hpp mem.hpp regs.hpp rs.hpp types.hpp instruction.hpp defs.hpp cdb.hpp globals.hpp
SRCS= main.cpp rs.cpp exec.cpp issue.cpp wb.cpp globals.cpp
GCC= g++
FLAGS= -g 

tomasulo: $(HEADERS) $(SRCS)
		$(GCC) $(SRCS) $(FLAGS) -o tomasulo.exe
