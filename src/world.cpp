#ifndef __WORLD_CPP
#define __WORLD_CPP

#include "../include/world.h"

#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

void world::draw_moving_map(double xpos, double ypos, double xsize, double ysize) const
{
    double world_x_size = x_dim_max - x_dim_min;
    double world_y_size = y_dim_max - y_dim_min;

    vector<ground_object*> o = objects;
    for (unsigned int i = 0; i < o.size(); i++)
    {
        ground_object* object = objects[i];
        double object_x_normalized_location = xpos + xsize * ((object->get_x_position() - x_dim_min) / world_x_size);
        double object_y_normalized_location = ypos + ysize + -1.0 * ysize * ((object->get_y_position() - y_dim_min) / world_y_size);
        object->draw_moving_map_symbol(object_x_normalized_location, object_y_normalized_location, xsize, ysize);
    }
}

void world::set_dimensions(double xds, double xdb, double yds, double ydb)
{
    if (dimensions_finalized)
    {
        throw 1;
    }
    x_dim_min = xds;
    x_dim_max = xdb;
    y_dim_min = yds;
    y_dim_max = ydb;
    dimensions_finalized = true;
}

void world::add_object(ground_object* obj)
{
    if (!dimensions_finalized)
    {
        throw 2;
    }
    if (objects_finalized)
    {
        throw 3;
    }

    objects.push_back(obj);
}

void world::finalize_objects()
{
    if (!dimensions_finalized)
    {
        throw 2;
    }
    if (objects_finalized)
    {
        throw 3;
    }
    for (unsigned int i = 0; i < objects.size(); i++)
    {
        objects_by_x_dim.push_back(objects[i]);
        objects_by_y_dim.push_back(objects[i]);
    }
    std::sort(objects_by_x_dim.begin(), objects_by_x_dim.end(), ground_object::compare_by_x_dimension);
    std::sort(objects_by_y_dim.begin(), objects_by_y_dim.end(), ground_object::compare_by_y_dimension);

    objects_finalized = true;
}


#endif