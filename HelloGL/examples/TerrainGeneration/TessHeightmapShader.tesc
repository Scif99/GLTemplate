#version 430 core

layout(vertices=4) out;

in vec2 TexCoord[];
out vec2 TextureCoord[];

uniform mat4 MV;


void main()
{
	//Pass vertex attributes unmodified
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    TextureCoord[gl_InvocationID] = TexCoord[gl_InvocationID];

    //Note we only need to define tessellation levels once per patch!
    if (gl_InvocationID == 0)
    {

        const int MIN_TESS_LEVEL = 4;
        const int MAX_TESS_LEVEL = 64;

        //For patches within this range, we linearly interpolate to determine tessellation level
        const float MIN_DISTANCE = 20;
        const float MAX_DISTANCE = 800;

        //Get eye-space coordinates of patch vertices
        vec4 eyeSpacePos00 = MV* gl_in[0].gl_Position;
        vec4 eyeSpacePos01 = MV *gl_in[1].gl_Position;
        vec4 eyeSpacePos10 = MV * gl_in[2].gl_Position;
        vec4 eyeSpacePos11 = MV * gl_in[3].gl_Position;

        //Scale to [0,1]
        //This value is used as the parameter in interpolation
        //Note because we are in eye-space, the distance from camera to patch vertex is just eyeSpacePos.z
        float distance00 = clamp((abs(eyeSpacePos00.z)-MIN_DISTANCE) / (MAX_DISTANCE-MIN_DISTANCE), 0.0, 1.0);
        float distance01 = clamp((abs(eyeSpacePos01.z)-MIN_DISTANCE) / (MAX_DISTANCE-MIN_DISTANCE), 0.0, 1.0);
        float distance10 = clamp((abs(eyeSpacePos10.z)-MIN_DISTANCE) / (MAX_DISTANCE-MIN_DISTANCE), 0.0, 1.0);
        float distance11 = clamp((abs(eyeSpacePos11.z)-MIN_DISTANCE) / (MAX_DISTANCE-MIN_DISTANCE), 0.0,1.0);

        //For each edge of the quad patch, we tessellate based on the closest vertex
        //This is an arbitrary choice, we just need to make a decision for each edge
        float tesslevelouter0 = mix( MAX_TESS_LEVEL, MIN_TESS_LEVEL, min(distance10, distance00) );
        float tesslevelouter1 = mix(MAX_TESS_LEVEL, MIN_TESS_LEVEL, min(distance00,distance10));
        float tesslevelouter2 = mix(MAX_TESS_LEVEL, MIN_TESS_LEVEL, min(distance11,distance10));
        float tesslevelouter3 = mix(MAX_TESS_LEVEL, MIN_TESS_LEVEL, min(distance01,distance11));


        gl_TessLevelOuter[0] = tesslevelouter0;
        gl_TessLevelOuter[1] = tesslevelouter1;
        gl_TessLevelOuter[2] = tesslevelouter2;
        gl_TessLevelOuter[3] = tesslevelouter3;

        //For the inner levels, we choose the level of the largest parallel outer edge
        //Again this is arbitrary, there is no definite right way to decide
        gl_TessLevelInner[0] = max(tesslevelouter1, tesslevelouter3);
        gl_TessLevelInner[1] =  max(tesslevelouter0, tesslevelouter2);
    }
}