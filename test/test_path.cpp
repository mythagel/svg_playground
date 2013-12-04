#include "pathparser.h"
#include <iostream>
#include <string>

struct pathwriter : svg::path::parser
{
    float startx;
    float starty;
    float cpx;
    float cpy;
    
	void move_to(bool abs, float x, float y) override
	{
	    if(abs)
    	    std::cerr << "move_to(" << x << ", " << y << ")\n";
	    else
	        std::cerr << "rel_move_to(" << x << ", " << y << ")\n";
        startx = cpx = x;
        starty = cpy = y;
	}

	void line_to(bool abs, float x, float y) override
	{
	    if(abs)
    	    std::cerr << "line_to(" << x << ", " << y << ")\n";
	    else
	        std::cerr << "rel_line_to(" << x << ", " << y << ")\n";
        cpx = x;
        cpy = y;
	}
	void horizontal_line_to(bool abs, float x) override
	{
	    if(abs)
    	    std::cerr << "horizontal_line_to(" << x << ")\n";
	    else
	        std::cerr << "rel_horizontal_line_to(" << x << ")\n";
        cpx = x;
	}
	void vertical_line_to(bool abs, float y) override
	{
	    if(abs)
    	    std::cerr << "vertical_line_to(" << y << ")\n";
	    else
	        std::cerr << "rel_vertical_line_to(" << y << ")\n";
        cpy = y;
	}

	void curve_to(bool abs, float x1, float y1, float x2, float y2, float x, float y) override
	{
	    if(abs)
    	    std::cerr << "curve_to(" << x1 << ", " << y1 << ", " << x2 << ", " << y2 << ", " << x << ", " << y << ")\n";
	    else
	        std::cerr << "rel_curve_to(" << x1 << ", " << y1 << ", " << x2 << ", " << y2 << ", " << x << ", " << y << ")\n";
        cpx = x;
        cpy = y;
	}
	void smooth_curve_to(bool abs, float x2, float y2, float x, float y) override
	{
	    if(abs)
    	    std::cerr << "smooth_curve_to(" << x2 << ", " << y2 << ", " << x << ", " << y << ")\n";
	    else
	        std::cerr << "rel_smooth_curve_to(" << x2 << ", " << y2 << ", " << x << ", " << y << ")\n";
        cpx = x;
        cpy = y;
	}

	void bezier_curve_to(bool abs, float x1, float y1, float x, float y) override
	{
	    if(abs)
    	    std::cerr << "bezier_curve_to(" << x1 << ", " << y1 << ", " << x << ", " << y << ")\n";
	    else
	        std::cerr << "rel_bezier_curve_to(" << x1 << ", " << y1 << ", " << x << ", " << y << ")\n";
        cpx = x;
        cpy = y;
	}
	void smooth_bezier_curve_to(bool abs, float x, float y) override
	{
	    if(abs)
    	    std::cerr << "smooth_bezier_curve_to(" << x << ", " << y << ")\n";
	    else
	        std::cerr << "rel_smooth_bezier_curve_to(" << x << ", " << y << ")\n";
        cpx = x;
        cpy = y;
	}

	void close_path() override
	{
	    std::cerr << "close_path(" << startx << ", " << starty << ")\n";
        cpx = startx;
        cpy = starty;
	}
	void eof() override
	{
	}
};

void do_path(const std::string& path)
{
    pathwriter parser;
    auto c = path.c_str();
    auto end = c + path.size();
    
    parser.parse(c, end);
}

int main()
{
    do_path("M 100 100 L 200 200");
    do_path("M100 100L200 200");
    do_path("M100 100 200 200");
    
    do_path("M 100 200 L 200 100 L -100 -200");
    do_path("M 100 200 L 200 100 -100 -200");
    do_path("M 100-200");
    do_path("M 0.6.5");

    do_path("M100,100L200,200");
    do_path("M100,100L200,200");
    do_path("M100,100,200,200");
    
    do_path("M100,200L200,100L-100,-200");
    do_path("M100,200L200,100,-100,-200");
    do_path("M100,-200");
    do_path("M0.6,.5");

    return 0;
}

