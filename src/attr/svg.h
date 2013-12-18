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
 * svg.h
 *
 *  Created on: 2013-12-18
 *      Author: nicholas
 */

#ifndef ATTR_SVG_H_
#define ATTR_SVG_H_
#include <boost/optional.hpp>
#include "typed_attribute.h"
#include "../types/svg.h"
#include "properties.h"
#include "../types/focus.h"
#include "../types/boolean.h"
#include "../types/animate.h"
#include "core.h"
#include "../types/length.h"
#include "../types/aspect_ratio.h"

namespace svg
{
namespace attr
{

struct svg
{
    attr::properties properties;
    boost::optional<types::focus::focusHighlight> focusHighlight;
    boost::optional<types::boolean> externalResourcesRequired;
    boost::optional<types::focus::focusable> focusable;

    boost::optional<types::focus::navigation> nav_next;
    boost::optional<types::focus::navigation> nav_prev;
    boost::optional<types::focus::navigation> nav_up;
    boost::optional<types::focus::navigation> nav_up_right;
    boost::optional<types::focus::navigation> nav_right;
    boost::optional<types::focus::navigation> nav_down_right;
    boost::optional<types::focus::navigation> nav_down;
    boost::optional<types::focus::navigation> nav_down_left;
    boost::optional<types::focus::navigation> nav_left;
    boost::optional<types::focus::navigation> nav_up_left;

    boost::optional<types::animate::syncBehaviorDefault> syncBehaviorDefault;
    boost::optional<types::animate::syncToleranceDefault> syncToleranceDefault;

    attr::core core;

    boost::optional<types::length> width;
    boost::optional<types::length> height;

    boost::optional<types::aspect_ratio::preserveAspectRatio> preserveAspectRatio;

    boost::optional<types::svg::viewBox> viewBox;
    boost::optional<types::svg::zoomAndPan> zoomAndPan;
    boost::optional<types::svg::version> version;
    boost::optional<types::svg::baseProfile> baseProfile;
    boost::optional<std::string> contentScriptType;
    boost::optional<types::svg::snapshotTime> snapshotTime;
    boost::optional<types::svg::timelineBegin> timelineBegin;
    boost::optional<types::svg::playbackOrder> playbackOrder;

};

void map_attributes(svg& attr, attribute_map_t& attrs);

}
}

#endif /* ATTR_SVG_H_ */
