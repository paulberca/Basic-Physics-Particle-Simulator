#include "Solver.h"

void Solver::update(float deltaTime, std::vector<VerletObject> &objects) {
    const int substeps = 8;
    const float sub_dt = deltaTime / (float)substeps;

    for (int i = 0; i < substeps; i++) {
        applyGravity(objects);
        applyConstraint(objects);
        solveCollision(objects);
        updatePositions(sub_dt, objects);

        drawObjects(objects);
    }
}

void Solver::updatePositions(float deltaTime, std::vector<VerletObject> &objects) {
    for (auto &object : objects) {
        object.updatePosition(deltaTime);
    }
}

void Solver::applyGravity(std::vector<VerletObject> &objects) {
    for (auto &object : objects) {
        object.accelerate(gravity);
    }
}

void Solver::drawObjects(std::vector<VerletObject> &objects) {
    for (auto &object : objects) {
        DrawCircleV(object.position_current, object.radius, object.color);
    }
}

void Solver::applyConstraint(std::vector<VerletObject> &objects) {
    for (auto &object : objects) {
        const Vector2 distance = Vector2Subtract(constraint_position, object.position_current);
        const float length = Vector2Length(distance);

        if (length > (constraint_radius - object.radius)) {
            const Vector2 normal = Vector2Scale(distance, 1.0f / length);
            object.position_current = Vector2Add(constraint_position, Vector2Scale(normal, - (constraint_radius - object.radius)));
        }
    }
}

void Solver::drawConstraint() {
    DrawCircleV(constraint_position, constraint_radius, WHITE);
}

void Solver::solveCollision(std::vector<VerletObject> &objects) {
    for (int i = 0; i < objects.size(); i++) {
        for (int j = i + 1; j < objects.size(); j++) {
            const Vector2 collision_axis = Vector2Subtract(objects[i].position_current, objects[j].position_current);
            const float distance = Vector2Length(collision_axis);
            if (distance < (objects[i].radius + objects[j].radius)) {
                const Vector2 normal = Vector2Scale(collision_axis, 1.0f / distance);
                const float delta = (objects[i].radius + objects[j].radius) - distance;
                objects[i].position_current = Vector2Add(objects[i].position_current, Vector2Scale(normal, delta / 2));
                objects[j].position_current = Vector2Add(objects[j].position_current, Vector2Scale(normal, -delta / 2));
            }
        }
    }
}

bool Solver::checkCollisions(VerletObject obj, std::vector<VerletObject> &objects) {
    for (auto &object : objects) {
        const Vector2 collision_axis = Vector2Subtract(obj.position_current, object.position_current);
        const float distance = Vector2Length(collision_axis);
        if (distance < (obj.radius + object.radius)) {
            return true;
        }
    }
    return false;
}

void Solver::allFunctions(float deltaTime, std::vector<VerletObject> &objects) {
    const int substeps = 8;
    const float sub_dt = deltaTime / (float)substeps;

    for (int index = 0; index < substeps; index++) {
        for (int i = 0; i < objects.size(); i++) {
            objects[i].accelerate(gravity);

            const Vector2 dist = Vector2Subtract(constraint_position, objects[i].position_current);
            const float length = Vector2Length(dist);
            if (length > (constraint_radius - objects[i].radius)) {
                const Vector2 normal = Vector2Scale(dist, 1.0f / length);
                objects[i].position_current = Vector2Add(constraint_position, Vector2Scale(normal, - (constraint_radius - objects[i].radius)));
            }

            for (int j = i+1; j < objects.size(); j++) {
                const Vector2 collision_axis = Vector2Subtract(objects[i].position_current, objects[j].position_current);
                const float distance = Vector2Length(collision_axis);
                if (distance < (objects[i].radius + objects[j].radius)) {
                    const Vector2 normal = Vector2Scale(collision_axis, 1.0f / distance);
                    const float delta = (objects[i].radius + objects[j].radius) - distance;
                    objects[i].position_current = Vector2Add(objects[i].position_current, Vector2Scale(normal, delta / 2));
                    objects[j].position_current = Vector2Add(objects[j].position_current, Vector2Scale(normal, -delta / 2));
                }
            }

            objects[i].updatePosition(sub_dt);

//            DrawCircleV(objects[i].position_current, objects[i].radius, objects[i].color);
        }
    }

    for (auto &object : objects) {
        DrawCircleV(object.position_current, object.radius, object.color);
    }
}


