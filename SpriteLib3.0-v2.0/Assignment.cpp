#include "Assignment.h"
#include "Utilities.h"

Assignment::Assignment(std::string name)
	: Scene(name)
{
	m_gravity = b2Vec2(0.f, -800.f);
	m_physicsWorld->SetGravity(m_gravity);
}

void Assignment::InitScene(float windowWidth, float windowHeight)
{
	//Dynamically allocates the register
	m_sceneReg = new entt::registry;

	//Attach the register
	ECS::AttachRegister(m_sceneReg);

	// Create main camera
	Scene::CreateCamera(vec4(-75.f, 75.f, -75.f, 75.f), windowWidth, windowHeight);
	
	//Create Player
	Scene::CreateMainPhysicObject(m_physicsWorld, "Ninja.png", 80, 60, 1.f, vec3(0.f, 30.f, 2.f), 0.f, 0.f);
	
	//Create world here
	{

	}

	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
}

void Assignment::Update()
{
	Scene::AdjustScrollOffset();
}

void Assignment::KeyboardHold()
{
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	float speed = 50.f;
	b2Vec2 vel = b2Vec2(0.f, 0.f);

	if (Input::GetKey(Key::Shift)) {
		speed *= 3.f;
	}

	/*if (Input::GetKey(Key::W)) {
		vel += b2Vec2(0.f, 1.f);
	}*/
	/*if (Input::GetKey(Key::S)) {
		vel += b2Vec2(0.f, -1.f);
	}*/
	if (Input::GetKey(Key::A)) {
		vel += b2Vec2(-1.f, 0.f);
	}
	if (Input::GetKey(Key::D)) {
		vel += b2Vec2(1.f, 0.f);
	}
	if (Input::GetKey(Key::Space)) {
		vel += b2Vec2(0.f, 3.f);
	}

	player.GetBody()->SetLinearVelocity(speed * vel);
}

void Assignment::KeyboardDown()
{
}

void Assignment::KeyboardUp()
{
}
