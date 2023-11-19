#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>
#include <array>

#include "FractalSet.h"

#define WIDTH 800 // window width
#define HEIGHT 800 // window height

#define MAXDEPTH 4096 // maximum visual fidelity
#define MINDEPTH 32 // minimum

using namespace std;

FractalSet s = FractalSet(WIDTH, HEIGHT, ' '); // the set/fractal being visualized
bool newScene = true; // whether to draw a new scene

/**
 * Save Image function
 */
// void saveImage() {
//     GLubyte* rgb = new GLubyte[3 * WIDTH*HEIGHT];
//     glReadPixels(0, 0, WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, rgb);
//     FIBITMAP* img = FreeImage_ConvertFromRawBits(rgb, WIDTH, HEIGHT, 3 * WIDTH, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);
//     FreeImage_Save(FIF_PNG, img, "output.png", 0);
//     FreeImage_Unload(img);
// }

/**
 * Keyboard Controls function
 */
void keyControls(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_1: s.setType('m'); s.resetDefaults(); break; // Mandelbrot
            case GLFW_KEY_2: s.setType('b'); s.resetDefaults(); break; // Burning Ship
            case GLFW_KEY_3: s.setType('j'); s.resetDefaults(); break; // Julia
            case GLFW_KEY_4: s.setType('t'); s.resetDefaults(); break; // Tri-Wing Mandelbrot
            case GLFW_KEY_5: s.setType('s'); s.resetDefaults(); break; // Two Squares
            case GLFW_KEY_6: s.setType('v'); s.resetDefaults(); break; // Tri-Wing Vein
            case GLFW_KEY_7: s.setType('f'); s.resetDefaults(); break; // Two Fists
            case GLFW_KEY_8: s.setType('r'); s.resetDefaults(); break; // Ring-Pops
            case GLFW_KEY_9: s.setType('x'); s.resetDefaults(); break; // Shurikens
            case GLFW_KEY_0: s.setType('c'); s.resetDefaults(); break; // Clover
            case GLFW_KEY_R: s.resetDefaults(); break; // reset to defaults
           // case GLFW_KEY_S: saveImage(); break; // save image
        }
        newScene = true; // new frame
        glfwPostEmptyEvent(); // trigger redraw
    }
}

/**
 * Mouse Controls function
 */
void mouseControls(GLFWwindow* window, int button, int action, int mods) {
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    int x = static_cast<int>(xPos);
    int y = static_cast<int>(yPos);

    if (s.getType() != ' ') {
        // LMB is zoom-in
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
            s.zoom('i', x, y);
            s.recalculateSet();
            newScene = true;
            glfwPostEmptyEvent(); // trigger redraw
        }
        // RMB is zoom-out
        else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
            s.zoom('o', x, y);
            s.recalculateSet();
            newScene = true;
            glfwPostEmptyEvent(); // trigger redraw
        }
    }
}

/**
 * Display driver
 */
void display() {
    if (newScene) { // if new frame
        list<Pixel> lp = s.getPixels(); // get the list of pixels
        glClear(GL_COLOR_BUFFER_BIT); // clear the color bit
        glBegin(GL_POINTS); // begin drawing pixels
        // for each pixel
        for (list<Pixel>::iterator p = lp.begin(); p != lp.end(); ++p) {
            array<double, 3> rgb = p->getCol(); // grab rgb values
            array<int, 2> pos = p->getPos(); // grab position
            glColor3d(rgb[0], rgb[1], rgb[2]); // color accordingly
            glVertex2i(pos[0], pos[1]); // place in correct spot
        }
        glEnd(); // finish drawing pixels
        glFlush(); // flush buffer
        newScene = false; // don't continually redraw since static image
    }
}

/**
 * my attempt at not allowing resize, may not work with all window managers
 */
void windowResize(GLFWwindow* window, int width, int height) {
    // on resize, force resize to default
    glfwSetWindowSize(window, WIDTH, HEIGHT);
}

/**
 * initialize GLFW related stuff
 */
GLFWwindow* initGLFW() {
    if (!glfwInit()) {
        cerr << "Failed to initialize GLFW" << endl;
        return nullptr;
    }

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Fractal Display", nullptr, nullptr);
    if (!window) {
        cerr << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyControls);
    glfwSetMouseButtonCallback(window, mouseControls);
    glfwSetFramebufferSizeCallback(window, windowResize);

    return window;
}

/**
 * CLI Menu function
 */
void cliMenu() {
    cout << endl;
    cout << "+---------------------+" << endl;
    cout << "|  Fractal Generator  |" << endl;
    cout << "+---------------------+" << endl;
    cout << endl;
    cout << "Use keyboard controls to change fractal visual:" << endl;
    cout << endl;
    cout << "--- Traditional ---" << endl;
    cout << "1. Mandelbrot Set, 2. Burning Ship Set" << endl;
    cout << "3. Julia Set (k = -0.835 - 0.232i)" << endl;
    cout << endl;
    cout << "--- \"Custom\" ---" << endl;
    cout << "4. Tri-Winged Mandelbrot Set, 5. Two Boxes Set" << endl;
    cout << "6. Tri-Winged Vein Set, 7. Two Fists Set" << endl;
    cout << "8. Two Ring Pops Set, 9. Shuriken Set, 0. Clover Set" << endl;
    cout << "r. Reset to Defaults, s. Save Image" << endl;
    cout << endl;
    cout << "Use mouse controls to zoom:" << endl;
    cout << "LMB = Zoom In, RMB = Zoom Out" << endl;
    cout << endl;
}

/**
 * Main Driver
 */
int main(int argc, char** argv) {
    int depth = 128; // if Windows
    if (argc != 1) { // if Linux execution
         istringstream input(argv[1]);
        if (!(input >> depth)) { // if wrong type
            cout << "Invalid depth. Please use an integer value between 32 and 4096 as an argument." << endl;
            return 0;
        } 
        if (depth < MINDEPTH || depth > MAXDEPTH) { // if bad range
            cout << "Invalid depth. Please use an integer value between 32 and 4096 as an argument." << endl;
            return 0;
        }
    }
    s.setDepth(depth);
    cliMenu();

    GLFWwindow* window = initGLFW();
    if (!window)
        return -1;

    while (!glfwWindowShouldClose(window)) {
        display();
        glfwSwapBuffers(window);
        glfwWaitEvents();
    }

    glfwTerminate();
    return 0; 
}
