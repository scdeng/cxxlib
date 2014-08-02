CC=g++
CXXFLAGS = -Wall -g 

PRG=splay
SOUCE_FILES = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, %.o,$(SOUCE_FILES))

$(PRG): $(OBJS)
	$(CC) $(CXXFLAGS) -o $(PRG) $(OBJS)

#%.o:%.c
#	$(CC) $(CXXFLAGS) $< -o $@

.SUFFIXES: .c .o .cpp  
.cpp.o:  
	$(CC) $(CXXFLAGS) -c $*.cpp -o $*.o 

.PRONY:clean  
clean:  
	@echo "Removing linked and compiled files......"  
	rm -f $(OBJS) $(PRG) 

