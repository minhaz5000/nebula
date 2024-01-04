#version 460 core

uniform vec2 u_resolution;
uniform float u_time;
uniform vec2 u_fractalCenter;
uniform vec2 u_fractalConstant;
uniform float u_fractalScale;
uniform int u_iterations;


out vec4 fragColor;

// check by minDistance

float infinity = 1.0/0.0; // IEEE 754 trickery

// z1 * z2
vec2 c_mul(vec2 z1, vec2 z2) {
    // z1 = a + bi
    // z2 = c + di
    float a = z1[0];
    float b = z1[1];
    float c = z2[0];
    float d = z2[1];

    return vec2(a * c - b * d, a * d + b * c);
}

// z * x
vec2 c_mul(vec2 z, float x) {
    // Simplifies to vector-scalar multiplication
    return z * x;
}

// z1 / z2
vec2 c_div(vec2 z1, vec2 z2) {
    // z1 = a + bi
    // z2 = c + di
    float a = z1[0];
    float b = z1[1];
    float c = z2[0];
    float d = z2[1];

    float denom = c * c + d * d;

    float real = (a * c + b * d) / denom;
    float imag = (b * c - a * d) / denom;

    return vec2(real, imag);
}

// z^p
vec2 c_pow(vec2 z, int p) {
    vec2 result = z;

    for (int i = 1; i < p; i++) {
        result = c_mul(result, z);
    }

    return result;
}

// end

// DEFINITIONS - Please experiment
// rootLen = len(roots) = len(colors)

// Number of roots of the function
int rootLen = 5;
// vec2 as a + bi
vec2[] roots = vec2[](
    vec2(0.66235898, 0.56227951),
    vec2(0.66235898, -0.56227951),
    vec2(0, 1),
    vec2(0, -1),
    vec2(-1.32471796, 0)
);
vec3[] colors = vec3[](
    vec3(0.247, 0.624, 0.745), // #3F9FBE
    vec3(0.788, 0.329, 0.239), // #C9543D
    vec3(0.373, 0.537, 0.294), // #5F894B
    vec3(1., 0.961, 0.208),     // #FFF535
    vec3(0.694, 0.451, 0.49)    // #B1737D
);

vec2 function(vec2 z) {
    // z^5 + z^2 - z + 1
    return c_pow(z, 5) + c_pow(z, 2) - z + vec2(1, 0);
}

vec2 derivative(vec2 z) {
    // 5z^4 + 2z - 1
    return c_mul(c_pow(z, 4), 5.) + c_mul(z, 2.) - vec2(1, 0);
}

// DONT CHANGE ANYTHING PAST THIS LINE

vec2 newtonStep(vec2 z) {
    // Newton's algorithm step
    return z - c_div(function(z), derivative(z));
}

vec3 closestColor(vec2 z, int iterations) {
    // Newton's algorithm
    for (int i = 0; i < iterations; i++) {
        z = newtonStep(z);
    }

    // Determine closest
    int closest = -1;
    float minDistance = infinity;
    for (int i = 0; i < rootLen; i++) {
        float dist = distance(roots[i], z);
        if (dist < minDistance) {
            closest = i;
            minDistance = dist;
        }
    }

    // Return color of closest
    return colors[closest];
}

void main()
{
    // x-Normalized pixel coordinates
    // Can be interpreted as complex plane
    vec2 z = (gl_FragCoord.xy / u_resolution.xy) * 2.0 - vec2(1.0, 1.0);

    // Shift (0, 0) to center and u_fractalScale
    z += u_fractalCenter * vec2(cos(u_time), sin(u_time)) * 0.5;
    z *= (1./u_fractalScale);

    // Output to screen
    fragColor = vec4(closestColor(z, u_iterations), 1);
}
