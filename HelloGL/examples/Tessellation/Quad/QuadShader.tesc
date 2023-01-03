#version 430 core

layout(vertices=4) out;

uniform int Outer[4];
uniform int Inner[2];

void main()
{
	//Pass vertex position unmodified
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position; 

	 gl_TessLevelOuter[0] = float(Outer[0]);
	 gl_TessLevelOuter[1] = float(Outer[1]);
	 gl_TessLevelOuter[2] = float(Outer[2]);
	 gl_TessLevelOuter[3] = float(Outer[3]);

	 gl_TessLevelInner[0] = float(Inner[0]);
	 gl_TessLevelInner[1] = float(Inner[1]);
}
