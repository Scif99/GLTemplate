#version 410 core

layout(vertices = 4) out; //number of vertices in output patch

uniform int NumSegments;
uniform int NumStrips;

void main(void)
{
	//Pass vertex position unmodified
	//The arrays gl_out and gl_in contain the input and output information associated with each vertex in the patch
	//gl_InvocationID defines the output patch vertex for which this invocation of the TCS is responsible
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

	//Define tessellation levels
	gl_TessLevelOuter[0] = float(NumStrips);
	gl_TessLevelOuter[1] = float(NumSegments); //number of line segments produced (note might need to swap values on cards other than nVidia)

}