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
 * svg.cpp
 *
 *  Created on: 2013-12-18
 *      Author: nicholas
 */

#include "svg.h"

namespace svg
{
namespace attr
{

void map_attributes(svg& attr, attribute_map_t& attrs)
{
    map_attributes(attr.properties, attrs);

    attrs.emplace("focusHighlight", make_attr(attr.focusHighlight));
    attrs.emplace("externalResourcesRequired", make_attr(attr.externalResourcesRequired));
    attrs.emplace("focusable", make_attr(attr.focusable));
    attrs.emplace("nav_next", make_attr(attr.nav_next));
    attrs.emplace("nav_prev", make_attr(attr.nav_prev));
    attrs.emplace("nav_up", make_attr(attr.nav_up));
    attrs.emplace("nav_up_right", make_attr(attr.nav_up_right));
    attrs.emplace("nav_right", make_attr(attr.nav_right));
    attrs.emplace("nav_down_right", make_attr(attr.nav_down_right));
    attrs.emplace("nav_down", make_attr(attr.nav_down));
    attrs.emplace("nav_down_left", make_attr(attr.nav_down_left));
    attrs.emplace("nav_left", make_attr(attr.nav_left));
    attrs.emplace("nav_up_left", make_attr(attr.nav_up_left));
    attrs.emplace("syncBehaviorDefault", make_attr(attr.syncBehaviorDefault));
    attrs.emplace("syncToleranceDefault", make_attr(attr.syncToleranceDefault));

    map_attributes(attr.core, attrs);

    attrs.emplace("width", make_attr(attr.width));
    attrs.emplace("height", make_attr(attr.height));
    attrs.emplace("preserveAspectRatio", make_attr(attr.preserveAspectRatio));
    attrs.emplace("viewBox", make_attr(attr.viewBox));
    attrs.emplace("zoomAndPan", make_attr(attr.zoomAndPan));
    attrs.emplace("version", make_attr(attr.version));
    attrs.emplace("baseProfile", make_attr(attr.baseProfile));
    attrs.emplace("contentScriptType", make_attr(attr.contentScriptType));
    attrs.emplace("snapshotTime", make_attr(attr.snapshotTime));
    attrs.emplace("timelineBegin", make_attr(attr.timelineBegin));
    attrs.emplace("playbackOrder", make_attr(attr.playbackOrder));
}

}
}
