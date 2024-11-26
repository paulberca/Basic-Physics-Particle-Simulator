#include "raylib.h"
#include "verletObject/VerletObject.h"
#include "solver/Solver.h"
#include "colorGradient/gradient.h"
#include <vector>

int main() {
    const int screenWidth = 1400;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "Verlet Integration");

    SetTargetFPS(60);

    std::vector<VerletObject> objects;
    Solver solver;
    std::vector<Color> gradient = createRainbowGradient(1000);
    int colorIndex = gradient.size() / 2;

    int objectCount = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GRAY);
        solver.drawConstraint();

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && objectCount < 400) {    // limitation of 400 objects
            Vector2 mousePosition = GetMousePosition();
            Vector2 constraintPosition = solver.constraint_position;
            float constraintRadius = solver.constraint_radius;
            Vector2 distance = Vector2Subtract(mousePosition, constraintPosition);
            float length = Vector2Length(distance);
            VerletObject object(mousePosition, gradient[colorIndex], rand() % 35 + 5);

            if (length < constraintRadius - object.radius) {
                if (!solver.checkCollisions(object, objects)) {
                    objects.push_back(object);
                    colorIndex = (colorIndex + 1) % gradient.size();
                    objectCount++;
                }
            }
        }

//        solver.update(GetFrameTime(), objects);
        solver.allFunctions(GetFrameTime(), objects);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}