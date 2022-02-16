#pragma once

class Vector {
public:
    Vector(float x, float y, float z);

    float x;
    float y;
    float z;
};

inline
Vector::Vector(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}
