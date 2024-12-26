#version 460 core

uniform vec2 u_resolution;
uniform float u_time;
uniform int u_iterations;
uniform vec2 u_fractalCenter;
uniform vec2 u_fractalConstant;
uniform float u_fractalScale;
uniform vec3 u_color1;
uniform vec3 u_color2;
uniform float u_escapeRadius;

out vec4 fragColor;

void main()
{
    // Normalize coordinates to the range [-1, 1]
    vec2 normalizedCoord = (2.0 * gl_FragCoord.xy - u_resolution) / min(u_resolution.x, u_resolution.y);

    // Apply scaling and centering to the fractal
    vec2 c = u_fractalCenter + normalizedCoord * (1 / u_fractalScale);

    // Add time to create animation
    vec2 juliaC = vec2(cos(u_time), sin(u_time));

    vec2 z = c;
    int iterations = 0;
    float minDistance = 100.0;
    vec2 minZ = vec2(0.0);

    for (int i = 0; i < u_iterations; ++i) {
        vec2 zSquared = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y);
        z = zSquared + juliaC + u_fractalConstant;

        float distance = length(z);

        if (distance < minDistance) {
            minDistance = distance;
            minZ = z;
        }

        if (dot(z, z) > 4.0) {
            break;
        }
        iterations++;
    }

    // Orbit color trapping
    float trapColor = atan(minZ.y, minZ.x) / (u_escapeRadius * 3.14159265359);

    // Color the fractal based on iterations and orbit color trapping
    float t = float(iterations) / float(u_iterations - 1);
    vec3 color = mix(u_color1, u_color2, t) * trapColor;

    // Output final color
    fragColor = vec4(color, 1.0);
}
