CPPFLAGS = -g -Wall
TARGETS = test_block

all: $(TARGETS)

test_block: ../examples/test_block.cpp block.o
	$(CXX) $(CPPFLAGS) -o $@ $^

block.o: API/block.cpp
	$(CXX) $(CPPFLAGS) -o $@ -c $^

clean:
	$(RM) *.o $(TARGETS)
