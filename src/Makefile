CC=g++
CXXFLAGS = -Wall -g 

PRG=jet
SOUCE_FILES = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, %.o,$(SOUCE_FILES))

$(PRG): $(OBJS)
	$(CC) $(CXXFLAGS) -o $(PRG) $(OBJS)

%.o:%.c
	$(CC) $(CXXFLAGS) $< -o $@

.PRONY:clean  
clean:  
	@echo "Removing linked and compiled files......"  
	rm -f $(OBJS) $(PRG)  
