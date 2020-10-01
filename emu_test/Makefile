CXX_OBJS = \
	test.o

CXX=g++
LD=g++

CXXFLAGS += -std=c++14 -Wall -Wextra -Wold-style-cast
CXXFLAGS += -O0 -g3 -DUSE_SIM

LDFLAGS += -L../chipsim/build
LDFLAGS += -L../drv/gl/build
LDFLAGS += -l:libgl.a
LDFLAGS += -l:libsim.a

DEP = $(CXX_OBJS:%.o=%.d)

PROGRAM=test

PROGRAM : $(CXX_OBJS)
	@cd ../drv/gl && make -f Makefile.linux clean
	@cd ../drv/gl && make -f Makefile.linux
	@cd ../chipsim && make
	@echo "LD $@"; $(LD) $(CXX_OBJS) -o test $(LDFLAGS) -lSDL2

.cpp.o:
	@echo "CXX $@"; $(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -f $(PROGRAM)
	rm -f $(CXX_OBJS)
