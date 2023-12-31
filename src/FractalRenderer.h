#include "Renderer/Renderer.h"
#include "Window/GUI.h"
#include "Window/Window.h"
#include "Window/Input.h"

class FractalRenderer {
private:
	Renderer * fractal;
	GUI * fractalController;
	Window * window;
public:
	FractalRenderer(Window * w);
	~FractalRenderer();
};