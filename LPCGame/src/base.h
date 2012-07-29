#ifndef BASE_H
#define BASE_H

#include "rect.h"
#include "vectors.h"

/*
*  A file for forward declarations of classes or
*  various widely used types
*/
///A collision map of solid tiles/objects
typedef std::vector<Recti> CollisionMap;
class GameObject;
class Camera;
class Map;

#endif