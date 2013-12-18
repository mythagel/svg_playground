#include "types/colour.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace svg::types;

void check_colour(const std::string& clr, const std::string& expected)
{
    std::istringstream ss(clr);
    colour c;
    ss >> c;

    std::stringstream s;
    s << c;

    if(s.str() != expected)
        throw std::logic_error(clr + " Not parsed to '" + expected + "' actual: '" + s.str() + "'");
    std::cout << "'" << clr << "' -> '" << s.str() << "'\n";
}

int main()
{
    check_colour("#000", "rgb(0, 0, 0)");
    check_colour("#fff", "rgb(255, 255, 255)");
    check_colour("#6CF", "rgb(102, 204, 255)");
    check_colour("#9400D3", "rgb(148, 0, 211)");
    check_colour("#FFD700", "rgb(255, 215, 0)");
    check_colour("rgb(233, 150, 122)", "rgb(233, 150, 122)");
    check_colour("rgb(255, 165, 0)", "rgb(255, 165, 0)");
    check_colour("rgb(12.375%, 34.286%, 28.97%)", "rgb(31, 87, 73)");
    check_colour("black", "rgb(0, 0, 0)");
    check_colour("green", "rgb(0, 128, 0)");
    check_colour("silver", "rgb(192, 192, 192)");
    check_colour("lime", "rgb(0, 255, 0)");
    check_colour("gray", "rgb(128, 128, 128)");
    check_colour("olive", "rgb(128, 128, 0)");
    check_colour("white", "rgb(255, 255, 255)");
    check_colour("yellow", "rgb(255, 255, 0)");
    check_colour("maroon", "rgb(128, 0, 0)");
    check_colour("navy", "rgb(0, 0, 128)");
    check_colour("red", "rgb(255, 0, 0)");
    check_colour("blue", "rgb(0, 0, 255)");
    check_colour("purple", "rgb(128, 0, 128)");
    check_colour("teal", "rgb(0, 128, 128)");
    check_colour("fuchsia", "rgb(255, 0, 255)");
    check_colour("aqua", "rgb(0, 255, 255)");
    return 0;
}

