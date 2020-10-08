#include "Player.h"

Player::Player()
{
}

Player::Player(std::string& fileName, std::string& animationJSON, int width, int height, Sprite* sprite, AnimationController* controller, Transform* transform, bool hasPhys, PhysicsBody* body)
{
	InitPlayer(fileName, animationJSON, width, height, sprite, controller, transform, hasPhys, body);
}

void Player::InitPlayer(std::string& fileName, std::string& animationJSON, int width, int height, Sprite* sprite, AnimationController* controller, Transform* transform, bool hasPhys, PhysicsBody* body)
{
	m_sprite = sprite;
	m_animController = controller;
	m_transform = transform;
	m_hasPhysics = hasPhys;
	if (hasPhys)
	{
		m_physBody = body;
	}

	m_animController->InitUVs(fileName);

	m_sprite->LoadSprite(fileName, width, height, true, m_animController);
	m_animController -> SetVAO(m_sprite->GetVAO());
	m_animController->SetTextureSize(m_sprite->GetTextureSize());

	nlohmann::json animations = File::LoadJSON(animationJSON);

	m_animController->AddAnimation(animations["IdleLeft"].get<Animation>());

	m_animController->AddAnimation(animations["IdleRight"].get<Animation>());

	m_animController->AddAnimation(animations["IdleUp"].get<Animation>());

	m_animController->AddAnimation(animations["IdleDown"].get<Animation>());
	
	m_animController->AddAnimation(animations["WalkLeft"].get<Animation>());

	m_animController->AddAnimation(animations["WalkRight"].get<Animation>());

	m_animController->AddAnimation(animations["WalkUp"].get<Animation>());

	m_animController->AddAnimation(animations["WalkDown"].get<Animation>());

	m_animController->AddAnimation(animations["AttackLeft"].get<Animation>());

	m_animController->AddAnimation(animations["AttackRight"].get<Animation>());

	m_animController->AddAnimation(animations["AttackUp"].get<Animation>());

	m_animController->AddAnimation(animations["AttackDown"].get<Animation>());

	m_animController->SetActiveAnim(IDLELEFT);
}

void Player::Update()
{
	if (!m_locked)
	{
		MovementUpdate();
	}

	AnimationUpdate();
}

void Player::MovementUpdate()
{
	m_moving = false;
	if (m_hasPhysics)
	{
		float speed = 50.f;
		vec3 vel = vec3(0.f,0.f, 0.f);

		if (Input::GetKey(Key::Shift)) {
			speed *= 3.f;
		}

		if (Input::GetKey(Key::W)) {
			vel = vec3(0.f, 1.f, 0.f);
			m_facing = UP;
			m_moving = true;
		}
		if (Input::GetKey(Key::S)) {
			vel = vec3(0.f, -1.f, 0.f);
			m_facing = DOWN;
			m_moving = true;
		}
		if (Input::GetKey(Key::A)) {
			vel = vec3(-1.f, 0.f, 0.f);
			m_facing = LEFT;
			m_moving = true;
		}
		if (Input::GetKey(Key::D)) {
			vel = vec3(1.f, 0.f, 0.f);
			m_facing = RIGHT;
			m_moving = true;
		}
		if (Input::GetKey(Key::Space)) {
			//if (player.GetVelocity().y == 0.f) {
				//player.ApplyForce(vec3(0.f,speed,0.f));
			vel = vec3(0.f, 0.f, 3.f);
			m_moving = true;
			//}		
		}

		m_physBody->SetVelocity(vel * speed);
	}
	else
	{
		float speed = 15.f;

		if (Input::GetKey(Key::W))
		{
			m_transform->SetPositionY(m_transform->GetPositionY() + (speed * Timer::deltaTime));
			m_facing = UP;
			m_moving = true;
		}
		if (Input::GetKey(Key::S))
		{
			m_transform->SetPositionY(m_transform->GetPositionY() - (speed * Timer::deltaTime));
			m_facing = DOWN;
			m_moving = true;
		}
		if (Input::GetKey(Key::A))
		{
			m_transform->SetPositionX(m_transform->GetPositionX() - (speed * Timer::deltaTime));
			m_facing = LEFT;
			m_moving = true;
		}
		if (Input::GetKey(Key::D))
		{
			m_transform->SetPositionX(m_transform->GetPositionX() + (speed * Timer::deltaTime));
			m_facing = RIGHT;
			m_moving = true;
		}
	}

	if (Input::GetKeyDown(Key::Space))
	{
		m_moving = false;

		if (m_hasPhysics)
		{
			m_physBody->SetVelocity(vec3());
		}

		m_attacking = true;
		m_locked = true;
	}
}

void Player::AnimationUpdate()
{
	int activeAnimation = 0;

	if (m_moving)
	{
		activeAnimation = WALK;
	}
	else if (m_attacking)
	{
		activeAnimation = ATTACK;

		if (m_animController->GetAnimation(m_animController->GetActiveAnim()).GetAnimationDone())
		{
			m_locked = false;
			m_attacking = false;
			m_animController->GetAnimation(m_animController->GetActiveAnim()).Reset();

			activeAnimation = IDLE;
		}
	}
	else
	{
		activeAnimation = IDLE;
	}

	SetActiveAnimation(activeAnimation * (int)m_facing);
}

void Player::SetActiveAnimation(int anim)
{
}
