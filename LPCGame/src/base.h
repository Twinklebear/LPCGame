#ifndef BASE_H
#define BASE_H

#include "rect.h"
#include "vectors.h"

//This file exists to provide forward declaration of classes because VS decided
//to flip it's fucking shit because it sucks ass and suddenly decided none of my
//classes existed because fuck me right?

///A collision map of solid tiles/objects
typedef std::vector<Recti> CollisionMap;
class GameObject;
class Camera;
class Map;

#endif