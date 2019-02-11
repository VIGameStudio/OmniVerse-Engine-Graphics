#include <ove/core/memory/linear_alloc.hpp>
#include <ove/core/memory/new.hpp>
#include <ove/core/util/types.hpp>

#include <iostream>

using namespace core;

#define DATA_SIZE 1023

struct entity_t {
public:
    entity_t()
    {
        for (u32 i = 0; i < DATA_SIZE; ++i) {
            data[i] = (rand() % 100) > 50 ? 'x' : 'o';
        }
    }

    char data[DATA_SIZE];
};

void print(const entity_t& e)
{
    for (u32 i = 0; i < DATA_SIZE; ++i) {
        std::cout << e.data[i] << ' ';
    }
    std::cout << std::endl;
}

int main()
{
    std::cout << "Hello world!" << std::endl;

    linear_alloc_t alloc(536870912); // 500MB

    entity_t* e = new_<entity_t>(alloc);
    print(*e);

    delete_(alloc, *e);
    alloc.clear();

    return 0;
}
