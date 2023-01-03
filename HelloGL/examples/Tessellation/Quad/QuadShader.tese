#version 430

layout(quads, equal_spacing, ccw) in;

void main()
{
	float u = gl_TessCoord.x;
	float v = gl_TessCoord.y;


	vec4 p0 = gl_in[0].gl_Position; //bottom left
	vec4 p1 = gl_in[1].gl_Position; //bottom right
	vec4 p2 = gl_in[2].gl_Position; //top right
	vec4 p3 = gl_in[3].gl_Position; //top left

	vec4 A = (1-u)*p0 + u*p1;
	vec4 B = (1-u)*p3 + u*p2;

	gl_Position =  (1-v)*A + v*B;

}