#pragma once

#include <string>
#include <unordered_map>
#include <vector>
namespace Constants
{
	namespace Window
	{
		constexpr const char * windowName = "Nebula - A Fractal Renderer";
		constexpr const int Width = 1280;
		constexpr const int Height = 720;
		constexpr const char * windowIcon = "resources/Icons/nebula_icon.png";
	};

	namespace GUI
	{
		constexpr const char * GLSL_VERSION = "#version 460";

		// Fonts
		constexpr const char * arialFont = "resources/Fonts/arial.ttf";
	}

	namespace Shaders
	{
		
		// Shaders

		const std::vector<std::string> ShaderNames =  {
			"Mandelbrot",
			"Julia",
			"Julia Complex Dynamics"
			"Newton",
		};

		const std::unordered_map<std::string, std::pair<std::string, std::string> > ShaderFiles = {
        	{
        		"Mandelbrot", {"resources/Shaders/Mandelbrot/mandelbrotVert.glsl", "resources/Shaders/Mandelbrot/mandelbrotFrag.glsl"}

        	},

        	{
        		"Julia", {"resources/Shaders/Julia/juliaVert.glsl", "resources/Shaders/Julia/juliaFrag.glsl"}
        		
        	},

        	{
        		"Julia Complex Dynamics", {"resources/Shaders/Julia Complex Dynamics/juliaComplexDynamicsVert.glsl", "resources/Shaders/Julia Complex Dynamics/juliaComplexDynamicsFrag.glsl"}
        		
        	},

        	{
        		"Newton", {"resources/Shaders/Newton/newtonVert.glsl", "resources/Shaders/Newton/newtonFrag.glsl"}
        		
        	},

        	// Add more shaders here
    	};
	}

}