#include "VerletObject.h"

void VerletObject::updatePosition(float deltaTime) {
    const Vector2 velocity = Vector2Subtract(position_current, position_previous);

    position_previous = position_current;

    // position_current = position_current + velocity + acceleration * deltaTime * deltaTime;
    position_current = Vector2Add(position_current, Vector2Add(velocity, Vector2Scale(acceleration, deltaTime * deltaTime)));

    acceleration = {0, 0};
}

void VerletObject::accelerate(Vector2 acc) {
    acceleration = Vector2Add(acceleration, acc);
}
