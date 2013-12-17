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
 * paint.cpp
 *
 *  Created on: 2013-12-17
 *      Author: nicholas
 */

#include "paint.h"

namespace svg
{
namespace types
{
namespace paint
{

std::ostream& operator<<(std::ostream& os, system_paint v)
{
    switch(v)
    {
        case system_paint::ActiveBorder:
            os << "ActiveBorder";
            break;
        case system_paint::ActiveCaption:
            os << "ActiveCaption";
            break;
        case system_paint::AppWorkspace:
            os << "AppWorkspace";
            break;
        case system_paint::Background:
            os << "Background";
            break;
        case system_paint::ButtonFace:
            os << "ButtonFace";
            break;
        case system_paint::ButtonHighlight:
            os << "ButtonHighlight";
            break;
        case system_paint::ButtonShadow:
            os << "ButtonShadow";
            break;
        case system_paint::ButtonText:
            os << "ButtonText";
            break;
        case system_paint::CaptionText:
            os << "CaptionText";
            break;
        case system_paint::GrayText:
            os << "GrayText";
            break;
        case system_paint::Highlight:
            os << "Highlight";
            break;
        case system_paint::HighlightText:
            os << "HighlightText";
            break;
        case system_paint::InactiveBorder:
            os << "InactiveBorder";
            break;
        case system_paint::InactiveCaption:
            os << "InactiveCaption";
            break;
        case system_paint::InactiveCaptionText:
            os << "InactiveCaptionText";
            break;
        case system_paint::InfoBackground:
            os << "InfoBackground";
            break;
        case system_paint::InfoText:
            os << "InfoText";
            break;
        case system_paint::Menu:
            os << "Menu";
            break;
        case system_paint::MenuText:
            os << "MenuText";
            break;
        case system_paint::Scrollbar:
            os << "Scrollbar";
            break;
        case system_paint::ThreeDDarkShadow:
            os << "ThreeDDarkShadow";
            break;
        case system_paint::ThreeDFace:
            os << "ThreeDFace";
            break;
        case system_paint::ThreeDHighlight:
            os << "ThreeDHighlight";
            break;
        case system_paint::ThreeDLightShadow:
            os << "ThreeDLightShadow";
            break;
        case system_paint::ThreeDShadow:
            os << "ThreeDShadow";
            break;
        case system_paint::Window:
            os << "Window";
            break;
        case system_paint::WindowFrame:
            os << "WindowFrame";
            break;
        case system_paint::WindowText:
            os << "WindowText";
            break;
    }
    return os;
}
std::istream& operator>>(std::istream& is, system_paint& v)
{
    std::string tok;
    is >> tok;

    if(tok == "ActiveBorder")
        v = system_paint::ActiveBorder;
    else if(tok == "ActiveCaption")
        v = system_paint::ActiveCaption;
    else if(tok == "AppWorkspace")
        v = system_paint::AppWorkspace;
    else if(tok == "Background")
        v = system_paint::Background;
    else if(tok == "ButtonFace")
        v = system_paint::ButtonFace;
    else if(tok == "ButtonHighlight")
        v = system_paint::ButtonHighlight;
    else if(tok == "ButtonShadow")
        v = system_paint::ButtonShadow;
    else if(tok == "ButtonText")
        v = system_paint::ButtonText;
    else if(tok == "CaptionText")
        v = system_paint::CaptionText;
    else if(tok == "GrayText")
        v = system_paint::GrayText;
    else if(tok == "Highlight")
        v = system_paint::Highlight;
    else if(tok == "HighlightText")
        v = system_paint::HighlightText;
    else if(tok == "InactiveBorder")
        v = system_paint::InactiveBorder;
    else if(tok == "InactiveCaption")
        v = system_paint::InactiveCaption;
    else if(tok == "InactiveCaptionText")
        v = system_paint::InactiveCaptionText;
    else if(tok == "InfoBackground")
        v = system_paint::InfoBackground;
    else if(tok == "InfoText")
        v = system_paint::InfoText;
    else if(tok == "Menu")
        v = system_paint::Menu;
    else if(tok == "MenuText")
        v = system_paint::MenuText;
    else if(tok == "Scrollbar")
        v = system_paint::Scrollbar;
    else if(tok == "ThreeDDarkShadow")
        v = system_paint::ThreeDDarkShadow;
    else if(tok == "ThreeDFace")
        v = system_paint::ThreeDFace;
    else if(tok == "ThreeDHighlight")
        v = system_paint::ThreeDHighlight;
    else if(tok == "ThreeDLightShadow")
        v = system_paint::ThreeDLightShadow;
    else if(tok == "ThreeDShadow")
        v = system_paint::ThreeDShadow;
    else if(tok == "Window")
        v = system_paint::Window;
    else if(tok == "WindowFrame")
        v = system_paint::WindowFrame;
    else if(tok == "WindowText")
        v = system_paint::WindowText;
    else
        throw std::invalid_argument("unrecognised value for system-paint: " + tok);
    return is;
}

std::ostream& operator<<(std::ostream& os, const paint& v)
{
    return os;
}
std::istream& operator>>(std::istream& is, paint& v)
{
    return is;
}

std::ostream& operator<<(std::ostream& os, fill_rule v)
{
    switch(v)
    {
        case fill_rule::inherit:
            os << "inherit";
            break;
        case fill_rule::nonzero:
            os << "nonzero";
            break;
        case fill_rule::evenodd:
            os << "evenodd";
            break;
    }
    return os;
}
std::istream& operator>>(std::istream& is, fill_rule& v)
{
    std::string tok;
    is >> tok;
    if(tok == "inherit")
        v = fill_rule::inherit;
    else if(tok == "nonzero")
        v = fill_rule::nonzero;
    else if(tok == "evenodd")
        v = fill_rule::evenodd;
    else
        throw std::invalid_argument("unrecognised value for fill-rule: " + tok);
    return is;
}

}
}
}
