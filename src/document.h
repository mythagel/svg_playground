/* 
 * Copyright (C) 2013  Nicholas Gill
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * document.h
 *
 *  Created on: 2013-12-05
 *      Author: nicholas
 */

#ifndef DOCUMENT_H_
#define DOCUMENT_H_
#include "colour.h"
#include "types.h"

namespace svg
{

namespace bidi
{
enum class direction
{
    ltr,
    rtl
};

enum class unicode_bidi
{
    normal,
    embed,
    bidi_override
};
}

namespace text
{
enum class display_align
{
    auto_,
    before,
    center,
    after
};

enum class line_increment
{
    auto_,
    // number
};
}

namespace gradient
{

}

namespace media
{

}

namespace paint
{
    struct paint{};
    
    enum class fill_rule
    {
        nonzero,
        evenodd
    };
    
    struct stroke_dasharray{};
    
    enum class stroke_linecap
    {
        butt,
        round,
        square
    };
    
    enum class stroke_linejoin
    {
        miter,
        round,
        bevel
    };
    
    enum class color_rendering
    {
        auto_,
        optimizeSpeed,
        optimizeQuality
    };
}

struct document
{
    // TODO wrappers for optional, default values and inherit.
    bidi::direction direction;
    bidi::unicode_bidi unicode_bidi;
    text::display_align display_align;
    text::line_increment line_increment;
    
    // inherit
    types::colour stop_colour;
    float stop_opacity;
    
    float audio_level;
    
    float fill_opacity;
    float stroke_opacity;
    
    paint::paint fill;
    paint::fill_rule fill_rule;
    paint::paint stroke;
    paint::stroke_dasharray stroke_dasharray;
    types::length stroke_dashoffset;
    paint::stroke_linecap stroke_linecap;
    paint::stroke_linejoin stroke_linejoin;
    float stroke_miterlimit;
    float stroke_width;
    types::colour colour;
    paint::color_rendering color_rendering;
    
    
    // types for allowable svg attributes
    
};

}

#endif /* DOCUMENT_H_ */
