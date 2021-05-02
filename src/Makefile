CPPFLAGS = -g -Wall
TARGETS = test_block test_block_schema

all: $(TARGETS)

test_block: ../examples/test_block.cpp block.o
	$(CXX) $(CPPFLAGS) -o $@ $^

block.o: API/block.cpp
	$(CXX) $(CPPFLAGS) -o $@ -c $^

test_block_schema: ../examples/test_block_schema.cpp block_schema.o block.o
	$(CXX) $(CPPFLAGS) -o $@ $^

block_schema.o: API/block_schema.cpp
	$(CXX) $(CPPFLAGS) -o $@ -c $^

clean:
	$(RM) *.o $(TARGETS)
