#pragma once
#include <GL/gl.h>

class Fractal {
private:
    GLuint textureID; // OpenGL texture ID
    int width, height;
    int depth, maxDepth;
    int intensity;
    double minReal, maxReal;
    double minImag, maxImag;
    double realFactor, imagFactor;
    char type;

public:
    Fractal(int width, int height, char type);
    void initializeTexture();
    void generateFractal();
    void render();
    void updateTexture();
    void zoom(int x, int y, float factor);
    // Add other necessary methods and members
};

