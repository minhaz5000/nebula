// https://www.shadertoy.com/view/4dy3RR
// Orbit trapped julia by maeln
#version 460 core

uniform vec2 u_resolution;
uniform float u_time;
uniform int u_iterations;
uniform vec2 u_fractalCenter;
uniform vec2 u_fractalConstant;
uniform float u_fractalScale;
uniform vec3 u_color1;
uniform vec3 u_color2;
uniform vec3 u_color3;
uniform float u_escapeRadius;


out vec4 fragColor;

vec2 cmul(vec2 i1, vec2 i2) 
{
    return vec2(i1.x*i2.x - i1.y*i2.y, i1.y*i2.x + i1.x*i2.y);
}


vec3 julia(vec2 z, vec2 c)
{
    int i = 0;
    vec2 zi = z;
    
    float trap1 = 10e5;
    float trap2 = 10e5;
    
    for(int n = 0; n < u_iterations; ++n)
    {
        if (dot(zi,zi) > u_escapeRadius)
            break;
        i++;
        zi = cmul(zi,zi) + c;
		
        // Orbit trap
        trap1 = min(trap1, sqrt(zi.x*zi.y));
        trap2 = min(trap2, sqrt(zi.y*zi.y));
    }
    
    return vec3(i,trap1,trap2);
}

vec4 gen_color(vec3 iter)
{
    float t1 = 1.0+log(iter.y)/8.0;
    float t2 = 1.0+log(iter.z)/16.0;
    float t3 = t1/t2;
    
    // vec3 comp = vec3(t1,t1,t1);
    vec3 red = u_color1;
    vec3 black = u_color2;
    vec3 blue = u_color3;
    vec3 comp = mix(blue,black,vec3(t2));
    comp = mix(red,comp,vec3(t1));
    
    return vec4(comp, 1.0);
}

void main()
{
    vec2 z = 2.*(2.*gl_FragCoord.xy - u_resolution.xy) / u_resolution.x;
    // Display the julia fractal for C = (-0.8, [0.0;0.3]).
    vec3 iter = julia((z + u_fractalCenter) * (1 / u_fractalScale), vec2(cos(u_time*u_fractalConstant.x), mix(0.0, 0.3, sin(u_time*u_fractalConstant.y))));
	fragColor = gen_color(iter);
}