### Pre-Settings
CC			= gcc
CXX			= g++
CFLAGS		= -g -O2 -pipe
CXXFLAGS	= $(CFLAGS)
INCS		= -I.
LIBS		= -L.
LDFLAGS		= -s -Wl,--as-needed
EXEC		= main

CMD_RM		= rm -rf

### Auto-Generate
SRCS		= $(wildcard *.c) $(wildcard *.cc) $(wildcard *.cpp)
OBJS		= $(patsubst %.cpp, %.o, $(patsubst %.cc, %.o, $(patsubst %.c, %.o, $(SRCS))))

### Targets
default: all

all: all_start all_main

clean: clean_start clean_main

all_start:
	@echo "==== Start Building Project ====="

all_main: $(OBJS)
	@echo ">>>> Create Executable File : $(EXEC)"
	@$(CXX) $(OBJS) $(LIBS) $(LDFLAGS) -o $(EXEC)

clean_start:
	@echo "Start Cleaning Workspace"

clean_main:
	@$(CMD_RM) $(OBJS) $(EXEC)

### Build Rules

%.o: %.c
	@echo "---> Compiling $< ...\n"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

%.o: %.cc
	@echo "---> Compiling $< ...\n"
	@$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

%.o: %.cpp
	@echo "---> Compiling $< ...\n"
	@$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)