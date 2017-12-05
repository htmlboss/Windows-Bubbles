#pragma once

#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2Body.h>

class Physics {

public:
	Physics();

	void init(const std::size_t numBubbles);
	void update();

	auto getPosition() const { return m_body->GetPosition(); }

private:
	// Simulation parameters
	const float32 m_timestep;
	const int32 m_velocityIterations;
	const int32 m_positionIterations;
	
	b2World m_world;

	b2Body* m_body = nullptr;
};

