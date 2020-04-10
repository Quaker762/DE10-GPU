CXX_OBJS = \
	rush3d/card.o \
	rush3d/pcu.o \

CXX=g++

CXXFLAGS += -std=c++14 -Wall -Wextra -Wold-style-cast
CXXFLAGS += -O0 -g3
CXXFLAGS += -I.
CXXFLAGS += -I../

DEP = $(CXX_OBJS:%.o=%.d)

PROGRAM=build/libsim.a
OUTPUT += build/libsim.a

PROGRAM : $(CXX_OBJS)
	@mkdir -p ./build
	@echo "AR $@"; $(AR) -rcs $(OUTPUT) $(CXX_OBJS)

.cpp.o:
	@echo "CXX $@"; $(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -f $(PROGRAM)
	rm -f $(CXX_OBJS)
