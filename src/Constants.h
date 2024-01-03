#pragma once

#include <string>
#include <unordered_map>
#include <vector>
namespace Constants
{
	namespace Window
	{
		constexpr const char * Name = "Nebula - A Fractal Renderer";
		constexpr const int Width = 1280;
		constexpr const int Height = 720;
		// Window
		constexpr const char * Icon = "resources/Icons/tsinghua_icon.png";
	};

	namespace GUI
	{
		constexpr const char * GLSL_VERSION = "#version 460";
	}

	namespace Shaders
	{
		
		// Shaders

		const std::vector<std::string> ShaderNames =  {
			"Mandelbrot",
			"Julia",
		};

		const std::unordered_map<std::string, std::pair<std::string, std::string> > ShaderFiles = {
        	{
        		"Mandelbrot", {"resources/Shaders/Mandelbrot/mandelbrotVert.glsl", "resources/Shaders/Mandelbrot/mandelbrotFrag.glsl"}

        	},

        	{
        		"Julia", {"resources/Shaders/Julia/juliaVert.glsl", "resources/Shaders/Julia/juliaFrag.glsl"}
        		
        	},

        	// Add more shaders here
    	};
		
		// Fonts
		constexpr const char * arialFont = "resources/Fonts/arial.ttf";
		constexpr const char * starFont  = "resources/Fonts/star.ttf";
		constexpr const char * notesFont = "resources/Fonts/notes.ttf";
	}

}