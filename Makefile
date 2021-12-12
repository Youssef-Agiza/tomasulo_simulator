HEADERS= common.hpp mem.hpp regs.hpp rs.hpp types.hpp instruction.hpp defs.hpp cdb.hpp globals.hpp
<<<<<<< HEAD
SRCS= main.cpp rs.cpp exec.cpp issue.cpp wb.cpp globals.cpp utils.cpp decode.cpp
=======
SRCS= main.cpp rs.cpp exec.cpp issue.cpp wb.cpp globals.cpp
>>>>>>> 36bc7d1f224494750c3028f84d6935611f593660
GCC= g++
FLAGS= -g 

# ifeq($(OS))


tomasulo: $(HEADERS) $(SRCS)
		$(GCC) $(SRCS) $(FLAGS) -o tomasulo
