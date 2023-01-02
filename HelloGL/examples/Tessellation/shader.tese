#version 410 core

layout(isolines) in;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{ 
	float u = gl_TessCoord.x; //tessellation u coordinate

	 // The patch vertices (control points)
	 vec3 p0 = gl_in[0].gl_Position.xyz;
	 vec3 p1 = gl_in[1].gl_Position.xyz;
	 vec3 p2 = gl_in[2].gl_Position.xyz;
	 vec3 p3 = gl_in[3].gl_Position.xyz;

	float u1 = (1.f - u);
	float u2 = u*u;

	// Blending functions
	 float b3 = u2 * u;
	 float b2 = 3.f * u2 * u1;
	 float b1 = 3.f * u * u1 * u1;
	 float b0 = u1 * u1 * u1;

	 // Cubic Bezier interpolation
	vec3 p = p0 * b0 + p1 * b1 + p2 * b2 + p3 * b3;

	gl_Position = projection* view* model* vec4(p, 1.f);


}