#include <iostream>
#include <ove/math/vec.hpp>

int main()
{
    math::vec2f v1(2, 2);
    math::vec2f v2(4, 4);
    auto v3 = v1 + v2;
    std::cout << v3.x << ", " << v3.y << std::endl;

	return 0;
}
