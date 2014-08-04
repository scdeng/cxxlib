CC=g++
CXXFLAGS = -Wall -g 

PRG=jet
SOUCE_FILES = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, %.o,$(SOUCE_FILES))
#OBJS = main.o array.o 
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

