#include "pch.h"
#include "Camera.h"
#include "RenderWindow.h"

Camera::Camera(RenderWindow* renderWindow, float3 camPos, float3 camRotation, bool responded)
{
	this->renderWindow = renderWindow;
	this->responded = responded;
	this->position = camPos;
	this->rotation = camRotation;
	viewMatrix = DirectX::XMMatrixIdentity();
	projectionMatrix = DirectX::XMMatrixIdentity();

	RECT clientRect{};
	GetClientRect(renderWindow->window->hwnd, &clientRect);
	aspect = (float)clientRect.bottom / float(clientRect.right);

}

Camera::Camera(RenderWindow* renderWindow, bool responded)
{
	this->renderWindow = renderWindow;
	this->responded = responded;
	position = {};
	rotation = {};
	viewMatrix = DirectX::XMMatrixIdentity();
	projectionMatrix = DirectX::XMMatrixIdentity();

	RECT clientRect{};
	GetClientRect(renderWindow->window->hwnd, &clientRect);
	aspect = (float)clientRect.bottom / float(clientRect.right);
}

void Camera::update()
{
	RECT clientRect{};
	GetClientRect(renderWindow->graphics->hwnd, &clientRect);
	aspect = (float)clientRect.bottom / float(clientRect.right);

	viewMatrix = DirectX::XMMatrixTranslation(-position.x, -position.y, -position.z) * DirectX::XMMatrixRotationY(-rotation.y) * DirectX::XMMatrixRotationX(-rotation.x) * DirectX::XMMatrixRotationZ(-rotation.z);
	//projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(0.4 * 3.14, (float)clientRect.right / clientRect.bottom, 0.1f, 100000);



	// Perspective matrix:

	//projectionMatrix = DirectX::XMMatrixSet(aspect * angle,   0,     0,                               0,
	//										  0,			    angle, 0,                               0,
	//										  0,				0,     zfar / (zfar - znear),           1,
	//										  0,			    0,     (zfar * znear) / (znear - zfar), 0);


	// Orthographic matrix:

	//projectionMatrix = DirectX::XMMatrixSet(aspect * angle, 0,			   0,								0,
	//										0,				angle,			   0,								0,
	//										0,				0,				   1 / (zfar - znear),				0,
	//										0,				0,				   znear / (zfar - znear),		    1);



	// Interpolation:

	float v33 = mymath::interpolate(zfar / (zfar - znear), 1 / (zfar - znear), perspectiveCoof);
	float v43 = mymath::interpolate((zfar * znear) / (znear - zfar), znear / (zfar - znear), perspectiveCoof);
	float v44 = mymath::interpolate(0, 1, perspectiveCoof);
	float v34 = mymath::interpolate(1, 0, perspectiveCoof);

	projectionMatrix = DirectX::XMMatrixSet(aspect * angle, 0,				   0,								0,
											0,				angle,			   0,								0,
											0,				0,				   v33,								v34,
											0,				0,				   v43,								v44);
}

void Camera::responseInput(MainWindow* mainWindow)
{
	if (responded)
	{
		rotation.x += (double)mainWindow->rawMouseDelta.y * rotationSpeed * renderWindow->graphics->deltaTime;
		rotation.y += (double)mainWindow->rawMouseDelta.x * rotationSpeed * renderWindow->graphics->deltaTime;

		DirectX::XMVECTOR tangent = DirectX::XMVector3Transform(DirectX::XMVectorSet(0, 0, 1, 0), DirectX::XMMatrixRotationX(rotation.x) * DirectX::XMMatrixRotationY(rotation.y));
		DirectX::XMVECTOR binormal = DirectX::XMVector3Transform(DirectX::XMVectorSet(1, 0, 0, 0), DirectX::XMMatrixRotationX(rotation.x) * DirectX::XMMatrixRotationY(rotation.y));
		DirectX::XMVECTOR normal = DirectX::XMVector3Transform(DirectX::XMVectorSet(0, 1, 0, 0), DirectX::XMMatrixRotationX(rotation.x) * DirectX::XMMatrixRotationY(rotation.y));

		this->tangent = { DirectX::XMVectorGetX(tangent), DirectX::XMVectorGetY(tangent) , DirectX::XMVectorGetZ(tangent) };
		this->bitangent = { DirectX::XMVectorGetX(binormal), DirectX::XMVectorGetY(binormal) , DirectX::XMVectorGetZ(binormal) };
		this->normal = { DirectX::XMVectorGetX(normal), DirectX::XMVectorGetY(normal) , DirectX::XMVectorGetZ(normal) };


		float tickIncreaseSpeed = (renderWindow->graphics->deltaTime / maxSpeedTime) * moveSpeed;
		bool moved = false;
		if (GetAsyncKeyState('W'))
		{
			velocity.x += DirectX::XMVectorGetX(tangent) * tickIncreaseSpeed;
			velocity.y += DirectX::XMVectorGetY(tangent) * tickIncreaseSpeed;
			velocity.z += DirectX::XMVectorGetZ(tangent) * tickIncreaseSpeed;
			moved = true;
		}
		if (GetAsyncKeyState('D'))
		{
			velocity.x += DirectX::XMVectorGetX(binormal) * tickIncreaseSpeed;
			velocity.y += DirectX::XMVectorGetY(binormal) * tickIncreaseSpeed;
			velocity.z += DirectX::XMVectorGetZ(binormal) * tickIncreaseSpeed;
			moved = true;
		}
		if (GetAsyncKeyState('S'))
		{
			velocity.x -= DirectX::XMVectorGetX(tangent) * tickIncreaseSpeed;
			velocity.y -= DirectX::XMVectorGetY(tangent) * tickIncreaseSpeed;
			velocity.z -= DirectX::XMVectorGetZ(tangent) * tickIncreaseSpeed;
			moved = true;
		}
		if (GetAsyncKeyState('A'))
		{
			velocity.x -= DirectX::XMVectorGetX(binormal) * tickIncreaseSpeed;
			velocity.y -= DirectX::XMVectorGetY(binormal) * tickIncreaseSpeed;
			velocity.z -= DirectX::XMVectorGetZ(binormal) * tickIncreaseSpeed;
			moved = true;
		}

		if (GetAsyncKeyState(VK_SPACE))
		{
			position.y += moveSpeed * renderWindow->graphics->deltaTime;
		}

		if (GetAsyncKeyState(VK_SHIFT))
		{
			position.y -= moveSpeed * renderWindow->graphics->deltaTime;
		}

		float tickDecreasSpeed = (renderWindow->graphics->deltaTime / minSpeedTime) * moveSpeed;
		if (!moved)
		{
			float length = mymath::getLength(velocity);
			if (length - tickDecreasSpeed < 0)
				velocity = { 0, 0, 0 };
			else
				velocity -= mymath::normalize(velocity) * tickDecreasSpeed;
		}

		if (mymath::getLength(velocity) > moveSpeed)
			mymath::setLength(&velocity, moveSpeed);

		position += velocity * renderWindow->graphics->deltaTime;
	}
}

void Camera::setPerspectiveCoof(float value)
{
	perspectiveCoof = value;
	update();
}

Ray Camera::castRay(float pX, float pY)
{
	RECT clientRect;
	GetClientRect(renderWindow->window->hwnd, &clientRect);

	float width = clientRect.right;
	float height = clientRect.bottom;
	float angle = this->angle;
	float nearPlane = this->angle;
	float aspect = this->aspect;

	float3 normalizedMousePosition = float3
	{
	((renderWindow->window->mousePos.x / width) * 2 - 1) / aspect,
	-((renderWindow->window->mousePos.y / height) * 2 - 1),
	nearPlane
	};

	float3 spacedNormalizedMousePosition = position + bitangent * normalizedMousePosition.x + normal * normalizedMousePosition.y + tangent * normalizedMousePosition.z;
	float3 direction = mymath::normalize(spacedNormalizedMousePosition - position);

	Ray ray;
	ray.position = spacedNormalizedMousePosition;
	ray.direction = direction;
	
	return ray;
}

Ray Camera::castRayFromMouse()
{
	Camera* camera = renderWindow->boundCamera;
	float2 mousePos = renderWindow->window->mousePos;
	Ray ray = camera->castRay(mousePos.x, mousePos.y);
	return ray;
}
