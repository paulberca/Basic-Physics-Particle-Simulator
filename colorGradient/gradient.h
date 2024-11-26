#pragma once

#include "raylib.h"
#include <vector>

Color interpolate(Color color1, Color color2, double ratio) {
    Color result;

    result.r = color1.r + (color2.r - color1.r) * ratio;
    result.g = color1.g + (color2.g - color1.g) * ratio;
    result.b = color1.b + (color2.b - color1.b) * ratio;
    result.a = 255;

    return result;
}

std::vector<Color> createRainbowGradient(int steps) {
    std::vector<Color> colors = {
            {255, 0, 0, 255},   // Red
            {255, 127, 0, 255}, // Orange
            {255, 255, 0, 255}, // Yellow
            {0, 255, 0, 255},   // Green
            {0, 0, 255, 255},   // Blue
            {75, 0, 130, 255},  // Indigo
            {148, 0, 211, 255}  // Violet
    };

    std::vector<Color> gradient;
    int numColors = colors.size();
    int stepsPerColor = steps / (numColors - 1);

    for (int i = 0; i < numColors - 1; ++i) {
        for (int j = 0; j < stepsPerColor; ++j) {
            double ratio = (double)j / (double)stepsPerColor;
            Color interpolatedColor = interpolate(colors[i], colors[i + 1], ratio);
            gradient.push_back(interpolatedColor);
        }
    }

    return gradient;
}
