#include "../src/API/block_schema.h"
#include <iostream>

int main(){
    using namespace std;

    Block_schema schema;
    std::string sum1 = schema.add_block(sum);
    std::string sum2 = schema.add_block(sum);
    std::string sum3 = schema.add_block(sum);
    std::string sub1 = schema.add_block(sub);
    std::string sub2 = schema.add_block(sub);
    std::string inc1 = schema.add_block(inc);

    schema.add_junction(sum1,0,sum2,0);
    schema.add_junction(inc1,0,sum2,1);
    schema.add_junction(sum2,0,sub2,1);

    schema.set_block_input_by_index(3,inc1,0);
    schema.set_block_input_by_index(5,sum1,0);
    schema.set_block_input_by_index(-10,sum1,1);

    schema.simulate();
}