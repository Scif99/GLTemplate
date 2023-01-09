#version 430 core

// Initial velocity and start time
layout (location = 0) in vec3 InitialVelocity;
layout (location = 1) in float StartTime;


out float Transp; // Transparency of the particle

uniform float Time; // Animation time
uniform float ParticleLifetime; // Max particle lifetime
uniform vec3 Gravity = vec3(0.0,-0.5,0.0); // world coords

uniform mat4 MVP;

void main()
{
	 // Initial position
	 vec3 pos = vec3(0.0);
	 Transp = 0.0;

	 // Particle doesn't exist until the start time
	if(Time > StartTime)
	{
		float t = Time - StartTime;
		if(t<ParticleLifetime)
		{
			pos += (InitialVelocity * t) + (Gravity * t * t); //Apply physics
			Transp = 1.0 - t / ParticleLifetime;
		}
		gl_Position =  MVP*vec4(pos, 1.f);

	}

}