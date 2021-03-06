#include "scene.h"

#include <displaylib/surface_3d.h>
#include <util/keyboard.h>
#include <util/mouse.h>
#include <cmath>

Scene::Scene(Keyboard& keyboard, Mouse& mouse, Surface3D& surface)
:	mKeyboard{keyboard},
	mMouse{mouse},
	mSurface{surface},
	mTestCube1{{0.0f, 0.0f, 2.5f}, 0.5f,Display::YELLOW, Display::BLACK},
	mTestCube2{{1.25f, 0.25f, 2.5f}, 0.5f, Display::GREEN, Display::BLACK},
	mTestCube3{{-1.25f, -0.25f, 2.5f}, 0.3f, Display::RED, Display::BLACK},
	mTestCube4{{0.0f, 0.75f, 2.5f}, 0.25f, Display::YELLOW, Display::BLACK},
	mTestCube5{{0.0f, 1.125f, 2.5f}, 0.125f, Display::YELLOW, Display::BLACK}
{}

void Scene::Update(double totalElapsedSeconds)
{
	using Math::Vector3D;

	const float camMovementSpeed = 0.01f;
	const float camRotationSpeed = 0.8f;

	Vector3D cameraMove;

	if(mKeyboard.IsDown(SDL_SCANCODE_LEFT))
		cameraMove[0] = -camMovementSpeed;
	if(mKeyboard.IsDown(SDL_SCANCODE_RIGHT))
		cameraMove[0] = +camMovementSpeed;
	if(mKeyboard.IsDown(SDL_SCANCODE_PAGEUP))
		cameraMove[1] = +camMovementSpeed;
	if(mKeyboard.IsDown(SDL_SCANCODE_PAGEDOWN))
		cameraMove[1] = -camMovementSpeed;
	if(mKeyboard.IsDown(SDL_SCANCODE_DOWN))
		cameraMove[2] = -camMovementSpeed;
	if(mKeyboard.IsDown(SDL_SCANCODE_UP))
		cameraMove[2] = +camMovementSpeed;

	auto camRotation = mMouse.GetPositionDelta();
	mSurface.camera.transform.Move(cameraMove);
	mSurface.camera.transform.Rotate({camRotation[0] * camRotationSpeed, 0.0f, 0.0f});

	float test1 = std::sin(totalElapsedSeconds);
	float test2 = std::cos(totalElapsedSeconds * 0.5f);

	mTestCube2.transform.SetScale(0.1f + std::fabs(test1) * 0.25f);
	mTestCube2.transform.Rotate({0.0f, 0.003f, 0.0f});
	mTestCube3.transform.SetOrientation({0.0f, test1, test2});
}

void Scene::Draw()
{
	auto view = mSurface.camera.transform.CreateInverseMatrix();

	mTestCube1.Draw(mSurface, view);
	mTestCube2.Draw(mSurface, view);
	mTestCube3.Draw(mSurface, view);
	mTestCube4.Draw(mSurface, view);
	mTestCube5.Draw(mSurface, view);
}
