#pragma once
#ifndef DATATYPES
#define DATATYPES

#include <glm/glm.hpp>

#include <string>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct Texture
{
    unsigned int id;
    std::string type;
};

#endif
