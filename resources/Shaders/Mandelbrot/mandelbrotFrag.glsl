#version 460 core

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;
uniform int u_iterations;
uniform vec2 u_fractalCenter;
uniform float u_fractalScale;
uniform vec2 u_juliaC;
uniform vec3 u_color1;
uniform vec3 u_color2;

out vec4 fragColor;

void main()
{
    // Normalize coordinates to the range [-1, 1]
    vec2 normalizedCoord = (2.0 * gl_FragCoord.xy - u_resolution) / min(u_resolution.x, u_resolution.y);

    // Apply scaling and centering to the fractal
    vec2 c = u_fractalCenter + normalizedCoord * u_fractalScale;

    // Julia set iteration
    vec2 z = c;
    int iterations = 0;
    for (int i = 0; i < u_iterations; ++i) {
        z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + u_juliaC;
        if (dot(z, z) > 4.0) {
            break;
        }
        iterations++;
    }

    // Color the fractal based on iterations
    float t = float(iterations) / float(u_iterations - 1);
    vec3 color = mix(u_color1, u_color2, t);

    // Output final color
    fragColor = vec4(color, 1.0);
}
