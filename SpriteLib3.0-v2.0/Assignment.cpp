#include "Assignment.h"
#include "Utilities.h"

Assignment::Assignment(std::string name)
	: Scene(name)
{
	m_gravity = b2Vec2(0.f, -3000.f);
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
	Scene::CreateMainPhysicObject(m_physicsWorld, "Ninja.png", 80, 60, 1.f, vec3(0.f, 100.f, 2.f), 0.f, 0.f);
	
	//Create world here
	{
		for (float positionForX = 0.f; positionForX < 900.f; positionForX+=100.f)
		{
			if (positionForX == 300.f) {
				Scene::CreateStaticObject("LevelSprites/Grass.png", 100, 100, 70.f, 20.f, vec3(positionForX, 100.f, 2.f));
			}
			else if (positionForX == 400.f)
			{

			}
			else if (positionForX == 500.f)
			{
				Scene::CreateMoveableObject(m_physicsWorld,"LevelSprites/Grass.png",50, 50, vec3(positionForX, 1000.f, 5.f),40.f,0.f);
				Scene::CreateStaticObject("LevelSprites/Grass.png", 100, 100, 70.f, 20.f, vec3(positionForX, 0.f, 2.f));
			}
			else if (positionForX == 800.f)
			{
				Scene::CreateStaticObject("LevelSprites/Grass.png", 100, 100, 70.f, 20.f, vec3(positionForX, 0.f, 2.f));
				Scene::CreateStaticObject("LevelSprites/Grass.png", 100, 100, 70.f, 20.f, vec3(positionForX, 100.f, 2.f));
				//item for finish
				Scene::CreateObject("Ninja Files/Ninja PNG/Items & FireBall/item2.png", 10, 10, vec3(positionForX, 170.f, 2.f));

			}
			else {
				Scene::CreateStaticObject("LevelSprites/Grass.png", 100, 100, 70.f, 20.f, vec3(positionForX, 0.f, 2.f));
			}
		}
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
		std::cout << "Your speed: " << speed << "\n";
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
		if (isJumping == false)
		{
			vel += b2Vec2(0.f, 3.f);
			if (player.GetPosition().y > 180.f) {
				isJumping = true;
			}
		}
		else if(player.GetPosition().y < 80.f) {
			isJumping = false;
		}
	} 
	if (Input::GetKey(Key::F)) {

	}

	player.GetBody()->SetLinearVelocity(speed * vel);
	if (player.GetPosition().x >= 800.f && player.GetPosition().y >= 170.f) {
		//end game
		std::cout << "Congratz you completed the game.\n";
	}
}

void Assignment::KeyboardDown()
{
}

void Assignment::KeyboardUp()
{
}
