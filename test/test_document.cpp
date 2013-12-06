#include "document.h"
#include <iostream>

int main()
{
    svg::line_element line;
    line.x1.value = 5;
    auto l2 = line;
    
    std::cout << *l2.x1 << "\n";
    std::cout << *l2.x2 << "\n";
    std::cout << l2.get("x1").get() << "\n";
    std::cout << l2.get("x2").get() << "\n";
//    std::cout << l2.get("x3").get() << "\n";
    return 0;
}

