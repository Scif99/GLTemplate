#version 430 core

// Initial velocity and start time
layout (location = 0) in vec3 a_InitialVelocity;
layout (location = 1) in float a_StartTime;


out float Transp; // Transparency of the particle

uniform float u_Time; // Animation time
uniform float u_ParticleLifetime; // Max particle lifetime
uniform vec3 u_Gravity = vec3(0.0,-0.5,0.0); // world coords

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

const float MAX_DISTANCE = 5.f;
const float MIN_DISTANCE  = 1.f;
const float MAX_SIZE = 100.f;
const float MIN_SIZE = 10.f;


void main()
{
	 // Initial position
	 vec3 pos = vec3(0.0);
	 Transp = 0.0;

	 // Particle doesn't exist until the start time
	if(u_Time > a_StartTime)
	{
		float t = u_Time - a_StartTime;
		if(t < u_ParticleLifetime)
		{
			pos += (a_InitialVelocity * t) + (u_Gravity * t * t); //Apply physics
			Transp = 1.0 - t / u_ParticleLifetime;
		}
		gl_Position =  u_Projection * u_View * u_Model*vec4(pos, 1.f);

		//We also scale the size of the particle based off the distance from the camera
		//Otherwise the particlers will be a fixed pixel size....
		
		//**TO_DO REWRITE WITHOUT ALL THE CONDITIONALS
		vec3 origin = vec3(0.0); //Initial position of particle
		vec4 ViewPos =  u_View * u_Model * vec4( origin, 1.0 ); //position of particles in view space
		float zDist = abs(ViewPos.z);
		if(zDist < MIN_DISTANCE)
		{
				gl_PointSize = MAX_SIZE;
		}

		if(zDist > MAX_DISTANCE)
		{
				gl_PointSize = MIN_SIZE;
		}

		//Otherwise we lerp
		else
		{
			float u = (MAX_SIZE - MIN_SIZE) / (MAX_DISTANCE - MIN_DISTANCE);
			gl_PointSize = MAX_SIZE - u*(zDist - MIN_DISTANCE);
		}

	}

}