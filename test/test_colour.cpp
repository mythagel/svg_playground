#include "colour.h"
#include <iostream>

using namespace svg::types;

int main()
{
    {colour c1("#000"); std::cout << c1 << "\n";}
    {colour c1("#fff"); std::cout << c1 << "\n";}
    {colour c1("#6CF"); std::cout << c1 << "\n";}
    {colour c1("#9400D3"); std::cout << c1 << "\n";}
    {colour c1("#FFD700"); std::cout << c1 << "\n";}
    {colour c1("rgb(233, 150, 122)"); std::cout << c1 << "\n";}
    {colour c1("rgb(255, 165, 0)"); std::cout << c1 << "\n";}
    {colour c1("rgb(12.375%, 34.286%, 28.97%)"); std::cout << c1 << "\n";}
    {colour c1("black"); std::cout << c1 << "\n";}
    {colour c1("green"); std::cout << c1 << "\n";}
    {colour c1("silver"); std::cout << c1 << "\n";}
    {colour c1("lime"); std::cout << c1 << "\n";}
    {colour c1("gray"); std::cout << c1 << "\n";}
    {colour c1("olive"); std::cout << c1 << "\n";}
    {colour c1("white"); std::cout << c1 << "\n";}
    {colour c1("yellow"); std::cout << c1 << "\n";}
    {colour c1("maroon"); std::cout << c1 << "\n";}
    {colour c1("navy"); std::cout << c1 << "\n";}
    {colour c1("red"); std::cout << c1 << "\n";}
    {colour c1("blue"); std::cout << c1 << "\n";}
    {colour c1("purple"); std::cout << c1 << "\n";}
    {colour c1("teal"); std::cout << c1 << "\n";}
    {colour c1("fuchsia"); std::cout << c1 << "\n";}
    {colour c1("aqua"); std::cout << c1 << "\n";}
    return 0;
}

