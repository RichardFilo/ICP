#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <string>

class Block
{

public:
    Block();
    // ~Block();
    void set_name(std::string name);
    void set_label(std::string label);
    void set_input_by_index(std::vector<int> input, int index);
    std::string get_name();
    std::string get_label();
    std::vector<std::vector<int>> get_inputs();
    std::vector<std::vector<int>> get_outputs();
    std::vector<int> get_input_by_index(int index);
    std::vector<int> get_output_by_index(int index);
    int get_input_count();


protected:
    std::string name;
    std::string label;
    std::vector<std::vector<int>> inputs;   // { { 1 <-isDefined(0-No, 1-by_value, 2-by_wire) , 4 <- value }, ...}
    std::vector<std::vector<int>> outputs;  // { { 1 <-isDefined(0,1) , 4 <- value }, ...}
    virtual void do_operation() = 0;
};


class Block_sum: public Block
{

public:
    Block_sum(std::vector<std::vector<int>> inputs = {{0,0}, {0,0}}, std::string name = "");
    ~Block_sum(){}
    void do_operation();
};

class Block_sub: public Block
{

public:
    Block_sub(std::vector<std::vector<int>> inputs = {{0,0}, {0,0}}, std::string name = "");
    ~Block_sub(){}
    void do_operation();
};

class Block_inc: public Block
{

public:
    Block_inc(std::vector<std::vector<int>> inputs = {{0,0}}, std::string name = "");
    ~Block_inc(){}
    void do_operation();
};

class Block_dec: public Block
{

public:
    Block_dec(std::vector<std::vector<int>> inputs = {{0,0}}, std::string name = "");
    ~Block_dec(){}
    void do_operation();
};

enum Block_type { sum, sub, inc, dec };
#endif // BLOCK_H
