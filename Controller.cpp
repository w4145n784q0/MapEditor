#include "Controller.h"
#include"Input.h"
#include"Camera.h"

Controller::Controller()
{
	transform.position_ = { 0,0,0 };
	tar = { 0,0,0 };
}

Controller::~Controller()
{
}

void Controller::Initialize()
{
	transform.position_ = { 0,3,-8 };
	tar = { 0,0,0 };
}

void Controller::Update()
{
	if (Input::IsKey(DIK_A))//ç∂Ç…ìÆÇ≠
	{
		transform.position_.x -= 0.02f;
		tar.x -= 0.02f;
	}
	if (Input::IsKey(DIK_D))//âEÇ…ìÆÇ≠
	{
		transform.position_.x += 0.02f;
		tar.x += 0.02f;
	}
	if (Input::IsKey(DIK_W))//è„Ç…ìÆÇ≠
	{
		transform.position_.z += 0.02f;
		tar.z += 0.02f;
	}
	if (Input::IsKey(DIK_S))//â∫Ç…ìÆÇ≠
	{
		transform.position_.z -= 0.02f;
		tar.z -= 0.02f;
	}

	XMVECTOR posvec = { transform.position_.x , transform.position_.y,transform.position_.z };
	Camera::SetPosition(posvec);
	XMVECTOR tarvec = { tar.x,tar.y,tar.z };
	Camera::SetTarget(tarvec);
}

void Controller::Release()
{
}
