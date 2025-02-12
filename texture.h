#pragma once

#include "vec3.h"

class texture {
public:
    virtual vec3 value(const vec3& p) const = 0;
};

class constant_texture : public texture {
public:
    constant_texture() {}
    constant_texture(vec3 c) : color(c) {}
    virtual vec3 value(const vec3& p) const {
        return color;
    }
    vec3 color;
};