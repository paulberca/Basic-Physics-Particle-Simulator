#pragma once

#include "raylib.h"
#include "raymath.h"

class VerletObject {
public:
    Vector2 position_current;
    Vector2 position_previous;
    Vector2 acceleration;
    float radius;
    Color color;

    VerletObject(Vector2 position, Color color, float radius = 15, Vector2 acceleration = {0, 0}):
        position_current(position),
        position_previous(position),
        acceleration(acceleration),
        radius(radius),
        color(color) {}

    void updatePosition(float deltaTime);

    void accelerate(Vector2 acc);
};

