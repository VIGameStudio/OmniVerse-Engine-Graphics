#include <ove/core/container/vector.hpp>

#include <ctime>
#include <iostream>
#include <vector>

using namespace core;

const char* test_str = "Lorem ipsum dolor sit amet, scelerisque amet lacus dolor arcu, sed sagittis sed lobortis ac pharetra, habitasse eros ipsum sagittis wisi amet, eu eu debitis ligula, nulla lectus sed tincidunt risus quisque ut. Vestibulum dolor ut viverra ornare, metus accumsan bibendum laoreet, sapien amet sed proin habitasse morbi netus. Ut suspendisse et non, pellentesque elit dui egestas quam pellentesque nulla, ligula vitae interdum eleifend imperdiet sit quis, vel pulvinar, non elit at aenean porta et. Dolore blandit. Egestas sem hac tempus. Ut sed praesent scelerisque sed maecenas eu. Metus eget pellentesque leo fusce ligula, id non, magnis neque quam sapien amet, dui aliquam morbi. Platea nec malesuada sit nullam ipsum. In aliquam rutrum tincidunt lectus nec, quam amet purus rhoncus suspendisse, eget consectetuer quam pharetra libero, ornare neque arcu nam interdum porta."
                       "Suscipit ligula eu nunc donec, ipsum ultricies in sed erat nunc. Porttitor pellentesque. Consequat a dui wisi pellentesque augue arcu, quam at nec integer phasellus amet, ligula morbi amet eveniet sunt platea, ligula quis eget. Phasellus vitae sed pretium a nec quisque, feugiat tincidunt vestibulum viverra, vivamus sit dolor duis est. Scelerisque et nulla varius. Porttitor erat eget ut morbi. Facilisis nam lacus, risus fames ut ipsum curabitur accusamus, possimus vivamus est suspendisse morbi. Ullamcorper adipiscing sed, dolor sit vitae dolor feugiat, proin nulla maecenas vivamus amet."
                       "Velit nulla tempus orci pretium, placeat condimentum vitae sapien eget, a adipiscing justo aliquam dapibus in orci, egestas arcu, leo mi ac velit turpis at sed. Quisque etiam id erat, erat dolor facilisi nec pretium consequat, vehicula bibendum lobortis pede vestibulum sed, inceptos amet maecenas ut, a hac. Et tellus, placerat molestie faucibus fringilla justo, sagittis vel enim vel. Nullam nunc, eu risus duis morbi nulla libero, eleifend ornare lorem justo eros, hendrerit nonummy eu gravida nunc in, sed recusandae. Nec ligula, ante nulla, maecenas faucibus ipsum lobortis. Asperiores pellentesque aenean, mauris vel tincidunt mi, consequat ducimus urna ante, condimentum bibendum sit nam nascetur. Nulla libero erat auctor, mauris sapiente non, sollicitudin vestibulum, ullamcorper in tortor nec ipsum ultrices. Eu eros in eu adipiscing duis. Eros dolor in a magna ultrices vehicula, velit eget molestie pharetra massa commodo, ornare eu, maecenas nunc, ut vestibulum. Felis cum a, mattis pede gravida sed, velit velit amet convallis ultrices venenatis."
                       "Nec id erat hendrerit lacus quis, ut pulvinar diam, sem laoreet sit, wisi velit morbi nec erat, ut viverra eget diam felis magna vitae. In feugiat a urna, quisque commodo maecenas at, ligula vitae sunt, elementum facilisi et ullamcorper diam, etiam felis at sollicitudin neque eu. Taciti ipsum ornare rutrum eget ipsum luctus, ligula nullam a dui ut curabitur ac, imperdiet vestibulum neque ac, libero cum aliquet, pellentesque massa dolor accumsan condimentum suscipit viverra. Ac accumsan quam nec, et aenean fusce malesuada imperdiet duis erat, hendrerit vel at, massa lacus id ridiculus, ut a ad sodales imperdiet etiam. Ipsum autem ipsum, mauris felis eu. Bibendum ad vivamus neque ullamcorper eros, augue justo rutrum nam. Urna amet mauris potenti morbi nibh ultrices, sollicitudin ut non duis ultrices litora, est volutpat morbi justo consectetur. Porta nec libero vestibulum ut aliquam, nulla ac sagittis justo, eu sem ornare tellus, sem felis mi morbi. Tristique pede gravida commodo, pretium non donec. Est aliquet, nisl curabitur sociis nibh pulvinar wisi, a malesuada eleifend. Erat ipsum quam vel morbi integer."
                       "Lorem ipsum dolor sit amet, scelerisque amet lacus dolor arcu, sed sagittis sed lobortis ac pharetra, habitasse eros ipsum sagittis wisi amet, eu eu debitis ligula, nulla lectus sed tincidunt risus quisque ut. Vestibulum dolor ut viverra ornare, metus accumsan bibendum laoreet, sapien amet sed proin habitasse morbi netus. Ut suspendisse et non, pellentesque elit dui egestas quam pellentesque nulla, ligula vitae interdum eleifend imperdiet sit quis, vel pulvinar, non elit at aenean porta et. Dolore blandit. Egestas sem hac tempus. Ut sed praesent scelerisque sed maecenas eu. Metus eget pellentesque leo fusce ligula, id non, magnis neque quam sapien amet, dui aliquam morbi. Platea nec malesuada sit nullam ipsum. In aliquam rutrum tincidunt lectus nec, quam amet purus rhoncus suspendisse, eget consectetuer quam pharetra libero, ornare neque arcu nam interdum porta."
                       "Suscipit ligula eu nunc donec, ipsum ultricies in sed erat nunc. Porttitor pellentesque. Consequat a dui wisi pellentesque augue arcu, quam at nec integer phasellus amet, ligula morbi amet eveniet sunt platea, ligula quis eget. Phasellus vitae sed pretium a nec quisque, feugiat tincidunt vestibulum viverra, vivamus sit dolor duis est. Scelerisque et nulla varius. Porttitor erat eget ut morbi. Facilisis nam lacus, risus fames ut ipsum curabitur accusamus, possimus vivamus est suspendisse morbi. Ullamcorper adipiscing sed, dolor sit vitae dolor feugiat, proin nulla maecenas vivamus amet."
                       "Velit nulla tempus orci pretium, placeat condimentum vitae sapien eget, a adipiscing justo aliquam dapibus in orci, egestas arcu, leo mi ac velit turpis at sed. Quisque etiam id erat, erat dolor facilisi nec pretium consequat, vehicula bibendum lobortis pede vestibulum sed, inceptos amet maecenas ut, a hac. Et tellus, placerat molestie faucibus fringilla justo, sagittis vel enim vel. Nullam nunc, eu risus duis morbi nulla libero, eleifend ornare lorem justo eros, hendrerit nonummy eu gravida nunc in, sed recusandae. Nec ligula, ante nulla, maecenas faucibus ipsum lobortis. Asperiores pellentesque aenean, mauris vel tincidunt mi, consequat ducimus urna ante, condimentum bibendum sit nam nascetur. Nulla libero erat auctor, mauris sapiente non, sollicitudin vestibulum, ullamcorper in tortor nec ipsum ultrices. Eu eros in eu adipiscing duis. Eros dolor in a magna ultrices vehicula, velit eget molestie pharetra massa commodo, ornare eu, maecenas nunc, ut vestibulum. Felis cum a, mattis pede gravida sed, velit velit amet convallis ultrices venenatis."
                       "Nec id erat hendrerit lacus quis, ut pulvinar diam, sem laoreet sit, wisi velit morbi nec erat, ut viverra eget diam felis magna vitae. In feugiat a urna, quisque commodo maecenas at, ligula vitae sunt, elementum facilisi et ullamcorper diam, etiam felis at sollicitudin neque eu. Taciti ipsum ornare rutrum eget ipsum luctus, ligula nullam a dui ut curabitur ac, imperdiet vestibulum neque ac, libero cum aliquet, pellentesque massa dolor accumsan condimentum suscipit viverra. Ac accumsan quam nec, et aenean fusce malesuada imperdiet duis erat, hendrerit vel at, massa lacus id ridiculus, ut a ad sodales imperdiet etiam. Ipsum autem ipsum, mauris felis eu. Bibendum ad vivamus neque ullamcorper eros, augue justo rutrum nam. Urna amet mauris potenti morbi nibh ultrices, sollicitudin ut non duis ultrices litora, est volutpat morbi justo consectetur. Porta nec libero vestibulum ut aliquam, nulla ac sagittis justo, eu sem ornare tellus, sem felis mi morbi. Tristique pede gravida commodo, pretium non donec. Est aliquet, nisl curabitur sociis nibh pulvinar wisi, a malesuada eleifend. Erat ipsum quam vel morbi integer.";
#define TEST_STR_LEN 7300

void test_vector_t()
{
    vector_t<char> vec(5);
    for (size_t i = 0; i < TEST_STR_LEN; ++i) {
        vec.push_back(test_str[i]);
    }

    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it;
    }

    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
    }

    std::cout << std::endl;
}

void test_std_vector()
{
    std::vector<char> vec(5);
    for (size_t i = 0; i < TEST_STR_LEN; ++i) {
        vec.push_back(test_str[i]);
    }

    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it;
    }

    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
    }

    std::cout << std::endl;
}

int main()
{
    std::clock_t start;

    start = std::clock();
    test_vector_t();
    auto time1 = (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000);

    start = std::clock();
    test_std_vector();
    auto time2 = (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000);

    std::cout << "Time1: " << time1 << " ms" << std::endl;
    std::cout << "Time2: " << time2 << " ms" << std::endl;

    return 0;
}
