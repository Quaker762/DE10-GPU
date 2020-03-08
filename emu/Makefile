CXX_OBJS = \
	rush3d/card.o \
	rush3d/pcu.o \
	main.o

CXX=g++

CXXFLAGS += -std=c++14 -Wall -Wextra -Wold-style-cast
CXXFLAGS += -O0 -g3

DEP = $(CXX_OBJS:%.o=%.d)

PROGRAM=emulator

PROGRAM : $(CXX_OBJS)
	@echo "LINK $@"; $(CXX) $(CXX_OBJS) -o $(PROGRAM) -lSDL2

.cpp.o:
	@echo "CXX $@"; $(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -f $(PROGRAM)
	rm -f $(CXX_OBJS)
