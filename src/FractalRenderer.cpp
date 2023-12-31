#include "FractalRenderer.h"

FractalRenderer::FractalRenderer(Window * w) : window{w}
{
	fractal = new Renderer();
	fractal->loadShaders(Constants::Shaders::shaderFiles);
}