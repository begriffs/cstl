P_NAME          :=  tstclib
P_C_SRCS        :=  $(wildcard *.c)
P_C_OBJS        :=  ${P_C_SRCS:.c=.o}
P_INCLUDE_DIRS  :=  ../inc
P_LIBRARY_DIRS  :=  ../src
P_LIBRARIES     :=  clib
CPPFLAGS        +=  $(foreach includedir,$(P_INCLUDE_DIRS),-I$(includedir))
LDFLAGS         +=  $(foreach librarydir,$(P_LIBRARY_DIRS),-L$(librarydir))
LDFLAGS         +=  $(foreach library,$(P_LIBRARIES),-l$(library))
CC              :=  gcc
CFLAGS          :=  -std=c89 -pedantic -Wall -g

.PHONY:         all clean
all:            $(P_NAME)
$(P_NAME):      $(P_C_OBJS)
		$(CC) $(CCFLAGS) $(P_C_OBJS) -o $(P_NAME) $(LDFLAGS)
clean:
		@- $(RM) $(P_NAME)
		@- $(RM) $(P_C_OBJS)
		@- $(RM) core*
		@- $(RM) tags

