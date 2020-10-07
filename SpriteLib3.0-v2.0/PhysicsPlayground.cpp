#include "PhysicsPlayground.h"
#include "Utilities.h"

PhysicsPlayground::PhysicsPlayground(std::string name)
	: Scene(name)
{
	//No gravity this is a top down scene
	m_gravity = b2Vec2(0.f, -800.f);
	m_physicsWorld->SetGravity(m_gravity);
}

void PhysicsPlayground::InitScene(float windowWidth, float windowHeight)
{
	//Dynamically allocates the register
	m_sceneReg = new entt::registry;

	//Attach the register
	ECS::AttachRegister(m_sceneReg);

	//Sets up aspect ratio for the camera
	float aspectRatio = windowWidth / windowHeight;

	// Setup main camera
	{
		//Scene::MainCamera(m_sceneReg, vec4(-75.f, 75.f, -75.f, 75.f), -100.f, windowWidth, windowHeight, true, true);)
		//Creates Camera Entity
		auto entity = ECS::CreateEntity();
		ECS::SetIsMainCamera(entity, true);

		ECS::AttachComponent<Camera>(entity);
		ECS::AttachComponent<HorizontalScroll>(entity);
		ECS::AttachComponent<VerticalScroll>(entity);

		vec4 temp = vec4(-75.f, 75.f, -75.f, 75.f);
		ECS::GetComponent<Camera>(entity).SetOrthoSize(temp);
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);

		ECS::GetComponent<HorizontalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
		ECS::GetComponent<VerticalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
	}
		//Setup Nina
		{
		//Scene::CreatePhysicsSprite(m_sceneReg,"Ninja.png",80,60,1.f,vec3(0.f,30.f,2.f),b2_dynamicBody,0.f,0.f,true,true)
			//Creates Ninja entity
			auto entity = ECS::CreateEntity();
			ECS::SetIsMainPlayer(entity, true);

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);
			ECS::AttachComponent<PhysicsBody>(entity);

			//Setup components
			std::string fileName = "Ninja.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 60, 40);
			ECS::GetComponent<Sprite>(entity).SetTransparency(1.0f);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 30.f, 0.f));

			auto& tempSpr = ECS::GetComponent<Sprite>(entity);
			auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

			float shrinkX = 0.f;
			float shrinkY = 0.f;

			b2Body* tempBody;
			b2BodyDef tempDef;

			tempDef.type = b2_dynamicBody;
			tempDef.position.Set(float32(0.f), float32(30.f));

			tempBody = m_physicsWorld->CreateBody(&tempDef);

			tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()), vec2(0.f, 0.f), false);

			ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetBody()->SetFixedRotation(true);

		}

		//Create Level
		{
			int yPosition = -70.f;
			for (float amount = 0.f; amount < 1000.f; amount=amount+50.f) {
				switch((int)amount)
				{
					case 500:
					{
						yPosition += 50.f;
						Scene::CreateStaticObject("LevelSprites/Grass.png", 50, 50, 50.f, 10.f, vec3(amount, yPosition, 2.f));
						/*Scene::CreateStaticObject("LevelSprites/GrassHillLeft2.png", 50, 50, 50.f,50.f, vec3(amount, yPosition, 2.f));
						Scene::CreateStaticObject("LevelSprites/GrassHillLeft.png", 50, 50, 50.f, 50.f, vec3(amount, yPosition += 50.f, 2.f));
						Scene::CreateStaticObject("LevelSprites/GrassHillLeft2.png", 50, 50, 50.f, 50.f, vec3((amount+50.f), yPosition, 2.f));*/
					break;
					}
					case 700:
					{
						yPosition += 50.f;
						Scene::CreateStaticObject("LevelSprites/Grass.png", 50, 50, 50.f, 10.f, vec3(amount, yPosition, 2.f));
						/*Scene::CreateStaticObject("LevelSprites/GrassHillLeft2.png", 50, 50, 50.f, 50.f, vec3(amount, yPosition, 2.f));
						Scene::CreateStaticObject("LevelSprites/GrassHillLeft.png", 50, 50, 50.f, 50.f, vec3(amount, yPosition += 50.f, 2.f));
						Scene::CreateStaticObject("LevelSprites/GrassHillLeft2.png", 50, 50, 50.f, 50.f, vec3((amount + 50.f), yPosition, 2.f));*/
					break;
					}
					case 900:
					{
						yPosition += 50.f;
						Scene::CreateStaticObject("LevelSprites/Grass.png", 50, 50, 50.f, 10.f, vec3(amount, yPosition, 2.f));
						/*Scene::CreateStaticObject("LevelSprites/GrassHillLeft.png", 50, 50, 0.f, 0.f, vec3(amount, yPosition += 50.f, 2.f));
						Scene::CreateStaticObject("LevelSprites/GrassHillLeft2.png", 50, 50, 0.f, 0.f, vec3((amount + 50.f), yPosition, 2.f));*/
					break;
					}		
					default:
						Scene::CreateStaticObject("LevelSprites/Grass.png", 50, 50, 50.f, 10.f, vec3(amount, yPosition, 2.f));
					break;
				}
			}
		}
		//Create Items
		{
			Scene::CreateObject("Ninja Files/Ninja PNG/Items & FireBall/item1.png",20,20,vec3(50.f,50.f, 2.f));
		}

		//adding hello world for fun
		{
			Scene::CreateObject("Helloworld.png", 100, 100, vec3(100.f, 100.f, 0.f));
			/*auto helloworld = ECS::CreateEntity();

			ECS::AttachComponent<Sprite>(helloworld);
			ECS::AttachComponent<Transform>(helloworld);
			std::string fileName = "HelloWorld.png";
			ECS::GetComponent<Sprite>(helloworld).LoadSprite(fileName, 100, 100);
			ECS::GetComponent<Transform>(helloworld).SetPosition(vec3(100.f, 100.f, 0.f));*/
		}

		ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
		ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
}

void PhysicsPlayground::Update()
{
	Scene::AdjustScrollOffset();
}

void PhysicsPlayground::KeyboardHold()
{
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	float speed = 50.f;
	b2Vec2 vel = b2Vec2(0.f, 0.f);

	if (Input::GetKey(Key::Shift)) {
		speed *= 3.f;
	}

	if (Input::GetKey(Key::W)) {
		vel += b2Vec2(0.f, 1.f);
	}
	if (Input::GetKey(Key::S)) {
		vel += b2Vec2(0.f, -1.f);
	}
	if (Input::GetKey(Key::A)) {
		vel += b2Vec2(-1.f, 0.f);
	}
	if (Input::GetKey(Key::D)) {
		vel += b2Vec2(1.f, 0.f);
	}
	if (Input::GetKey(Key::Space)) {
		//if (player.GetVelocity().y == 0.f) {
			//player.ApplyForce(vec3(0.f,speed,0.f));
			vel += b2Vec2(0.f, 3.f);
		//}		
	}

	player.GetBody()->SetLinearVelocity(speed * vel);
}

void PhysicsPlayground::KeyboardDown()
{
}

void PhysicsPlayground::KeyboardUp()
{
}
