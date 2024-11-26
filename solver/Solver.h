#pragma once

#include "raylib.h"
#include "raymath.h"
#include "../verletObject/VerletObject.h"
#include <vector>

class Solver {
public:
    Vector2 gravity;
    const Vector2 constraint_position;
    const float constraint_radius;

    Solver(Vector2 gravity = {0.0f, 1000.0f}):
        gravity(gravity),
        constraint_position({(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2}),
        constraint_radius(400.0f) {}

    void update(float deltaTime, std::vector<VerletObject>& objects);
    void updatePositions(float deltaTime, std::vector<VerletObject>& objects);
    void applyGravity(std::vector<VerletObject>& objects);

    void drawObjects(std::vector<VerletObject>& objects);

    void applyConstraint(std::vector<VerletObject>& objects);
    void drawConstraint();

    void solveCollision(std::vector<VerletObject>& objects);

    bool checkCollisions(VerletObject obj, std::vector<VerletObject>& objects);

    void allFunctions(float deltaTime, std::vector<VerletObject>& objects);
};
