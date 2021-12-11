HEADERS= common.hpp mem.hpp regs.hpp rs.hpp types.hpp instruction.hpp defs.hpp
SRCS= main.cpp rs.cpp exec.cpp issue.cpp wb.cpp
GCC= g++
FLAGS= -g 

tomasulo: $(HEADERS) $(SRCS)
		$(GCC) $(SRCS) $(FLAGS) -o tomasulo
