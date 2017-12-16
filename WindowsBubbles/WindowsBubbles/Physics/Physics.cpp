#include "Physics.h"

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>

#include <iostream>

/***********************************************************************************/
Physics::Physics() :	m_timestep(1.0f / 60.0f),
						m_velocityIterations(8),
						m_positionIterations(3),
						m_world(b2Vec2(0.0f, -9.81f)) {
}

/***********************************************************************************/
void Physics::init(const std::size_t numBubbles) {
	// Create bubbles
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = { 0.0f / 60.0f, 70.0f / 60.0f };
	//bodyDef.angle = f;

	m_body = m_world.CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = 1.0f;
	circle.m_p = bodyDef.position;

	// Physical properties
	b2FixtureDef fixture;
	fixture.shape = &circle;
	fixture.density = 1.0f;
	fixture.friction = 0.3f;

	m_body->CreateFixture(&fixture);

	b2BodyDef ground;
	ground.position.Set(0.0f / 60.0f, -50.0f / 60.0f);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f / 60.0f, 10.0f / 60.0f); // half-width and half-height
	
	auto groundBody = m_world.CreateBody(&ground);
	groundBody->CreateFixture(&groundBox, 0.0f);
}

/***********************************************************************************/
void Physics::update() {
	m_world.Step(m_timestep, m_velocityIterations, m_positionIterations);

	const auto pos = m_body->GetPosition();
	const auto rot = m_body->GetAngle();

	std::printf("%4.2f %4.2f %4.2f\n", pos.x, pos.y, rot);
}