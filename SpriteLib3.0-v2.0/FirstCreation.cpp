#include "FirstCreation.h"
#include "Utilities.h"

FirstCreation::FirstCreation(std::string name)
	: Scene(name)
{
	//no gravity this is a topdown scene
	m_gravity = b2Vec2(0.f, 0.f);
	m_physicsWorld->SetGravity(m_gravity);
}

void FirstCreation::Unload()
{
	Scene::Unload();
}

void FirstCreation::InitScene(float windowWidth, float windowHeight)
{
	//Allocates register
	m_sceneReg = new entt::registry;

	//Attach the reg
	ECS::AttachRegister(m_sceneReg);

	float aspectRatio = windowWidth / windowHeight;

	//Setup main camera
	{
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



	//Setup new Entity
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		ECS::SetIsMainPlayer(entity, true);

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Setup components
		std::string fileName = "Ninja.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 80, 60);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.0f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 0.f));
	}

	//TODO: Create a new entity
	{
		auto test = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(test);
		ECS::AttachComponent<Transform>(test);

		std::string fileName = "Ninja Files/Ninja PNG/Items & FireBall/item4.png";
		ECS::GetComponent<Sprite>(test).LoadSprite(fileName, 10, 10);
		ECS::GetComponent<Transform>(test).SetPosition(vec3(-50.f, 0.f, 0.f));
	}

	//adding hello world for fun
	{
		auto helloworld = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(helloworld);
		ECS::AttachComponent<Transform>(helloworld);
		std::string fileName = "HelloWorld.png";
		ECS::GetComponent<Sprite>(helloworld).LoadSprite(fileName, 100, 100);
		ECS::GetComponent<Transform>(helloworld).SetPosition(vec3(100.f, 100.f, 0.f));
	}

	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
}

void FirstCreation::Update() {
	Scene::AdjustScrollOffset();
}

void FirstCreation::KeyboardHold() {
	auto& player = ECS::GetComponent<Transform>(MainEntities::MainPlayer());
	float speed = 20.f;

	/*switch (Input::inputString())
	{
		case 'W':
		{

		}
		default:
		{
			OutputDebugString("Testing");
		}
	}*/
	if (Input::GetKey(Key::W))
	{
		player.SetPositionY(player.GetPositionY() + (speed * Timer::deltaTime));
	}
	if (Input::GetKey(Key::S))
	{
		player.SetPositionY(player.GetPositionY() - (speed * Timer::deltaTime));
	}
	if (Input::GetKey(Key::A))
	{
		player.SetPositionX(player.GetPositionX() - (speed * Timer::deltaTime));
	}
	if (Input::GetKey(Key::D))
	{
		player.SetPositionX(player.GetPositionX() + (speed * Timer::deltaTime));
	}
}
void FirstCreation::KeyboardDown() {
	if (Input::GetKeyDown(Key::W)) {
		printf("Key down\n");
	}
	/*if (Input::GetKeyDown(Key::S)) {
		
	}
	if (Input::GetKeyDown(Key::A)) {

	}
	if (Input::GetKeyDown(Key::D)) {

	}*/
}
void FirstCreation::KeyboardUp() {
	if (Input::GetKeyUp(Key::W))
	{
		printf("Key Up\n");
	}
	/*if (Input::GetKeyUp(Key::S))
	{

	}
	if (Input::GetKeyUp(Key::A))
	{

	}
	if (Input::GetKeyUp(Key::D))
	{

	}*/
}
