#ifndef BLOCK_SCHEMA_H
#define BLOCK_SCHEMA_H

#include "block.h"
#include <unordered_map>
#include <utility>  //pair

typedef struct{
    std::string block_name;
    int port_index;
} Port;

class Block_schema
{

public:
    Block_schema();
    ~Block_schema();
    std::string add_block(Block_type type);
    void remove_block(std::string block_name);
    int change_block_name(std::string block_name, std::string name);
    int set_block_input_by_index(int value, std::string block_name, int index);
    
    std::string get_block_label(std::string block_name);
    std::vector<std::vector<int>> get_block_inputs(std::string block_name);
    std::vector<std::vector<int>> get_block_outputs(std::string block_name);

    int add_junction(std::string block1, int index_output1, std::string block2, int index_input2);
    void remove_junction(std::string block1, int index_output1, std::string block2, int index_input2);
    int simulate();
    std::string generate_sim_code();

private:
    std::unordered_map<std::string, Block*> blocks;
    std::vector<std::pair<Port, Port>> junctions;
    std::vector<std::pair<Port, std::vector<int>>> event_calendar;
    std::string code_modification;
    std::string gen_name(std::string prefix);
    void remove_junc_of_block(std::string block_name);
    void remove_event_of_block(std::string block_name);
    void remove_event_of_port(std::string block, int index_input);
    void change_name_in_junctions(std::string pre_name, std::string new_name);
    void change_name_in_calendar(std::string pre_name, std::string new_name);
};

#endif // BLOCK_SCHEMA_H