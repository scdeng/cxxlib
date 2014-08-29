#CC=/opt/gcc/gcc-4.9/bin/g++ -std=c++1y
CC=g++
CXXFLAGS = -Wall -g 
#INCLUDE=/opt/gcc/gcc-4.9/include

PRG=jet
SOUCE_FILES = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, %.o,$(SOUCE_FILES))

$(PRG): $(OBJS)
	$(CC) $(CXXFLAGS) -o $(PRG) $(OBJS)

%.o:%.cpp
	$(CC) -c $(CXXFLAGS) $< -o $@

.PRONY:clean  
clean:  
	@echo "Removing linked and compiled files......"  
	rm -f $(OBJS) $(PRG)  
