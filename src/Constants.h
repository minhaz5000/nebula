#pragma once

#include <string>
#include <unordered_map>
namespace Constants
{
	namespace Window
	{
		constexpr const char * windowName = "Nebula - A Fractal Renderer";
		constexpr const int windowHeight = 1280;
		constexpr const int windowWidth = 720;
		// Window
		constexpr const char * windowIcon            = "resources/Icons/tsinghua_icon.png";
	};

	namespace GUI
	{
		constexpr const char * GLSL_VERSION = "#version 330";
	}

	namespace Shaders
	{
		
		// Shaders

		enum class ShaderID: unsigned int {
			Mandelbrot, Julia
		};

		const std::unordered_map<Constants::Shaders::ShaderID, std::pair<std::string, std::string>> shaderFiles = {
        	{
        		ShaderID::Mandelbrot, {"resources/Shaders/Mandelbrot/mandelbrotVert.glsl", "resources/Shaders/Mandelbrot/mandelbrotFrag.glsl"}
        	},

        	// Add more shaders here
    	};

		

		
		// Fonts
		constexpr const char * arialFont = "resources/Fonts/arial.ttf";
		constexpr const char * starFont  = "resources/Fonts/star.ttf";
		constexpr const char * notesFont = "resources/Fonts/notes.ttf";
	}

}