#include "GLTransforms.h"
#include "GLIncludes.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

void GLCamera::ComputeFinalMatrix()
{
	camera = proj * view;
	dirty = false;
}

void GLCamera::ComputeProjMatrix()
{
	proj = glm::perspective(fov, aspect_ratio, near_z, far_z);
	dirty = true;
}

void GLCamera::ComputeViewMatrix()
{
	view = glm::lookAt(eye, lookat, up);
	dirty = true;
}

GLCamera::GLCamera() :
	eye(1.0f, 1.0f, 1.0f),
	lookat(0.0f, 0.0f, 0.0f),
	up(0.0f, 1.0f, 0.0f)
{
	fov = 75.0f;
	aspect_ratio = static_cast<float>(glutGet(GLUT_WINDOW_WIDTH)) / glutGet(GLUT_WINDOW_HEIGHT);
	near_z = 0.001f;
	far_z = 1000.0f;

	ComputeViewMatrix();
	ComputeProjMatrix();
}

void GLCamera::SetupView(const glm::vec3 &eye, const glm::vec3 &lookat, const glm::vec3 &up)
{
	this->eye = eye;
	this->lookat = lookat;
	this->up = up;
	ComputeViewMatrix();
}

void GLCamera::SetupProjection(float fov, float aspect_ratio, float near_z, float far_z)
{
	this->fov = fov;
	this->aspect_ratio = aspect_ratio;
	this->near_z = near_z;
	this->far_z = far_z;
	ComputeProjMatrix();
}

void GLCamera::PlaceAt(const glm::vec3 &eye)
{
	this->eye = eye;
	ComputeViewMatrix();
}

void GLCamera::LookAt(const glm::vec3 &lookat)
{
	this->lookat = lookat;
	ComputeViewMatrix();
}

glm::mat4 GLCamera::GetTransform()
{
	if (dirty) { ComputeFinalMatrix(); }
	return camera;
}



void GLTransform::ComputeTransform()
{
	transform = translate * rotate * scale;
	dirty = false;
}

GLTransform::GLTransform()
{
	dirty = true;
}

void GLTransform::Translate(const glm::vec3 &delta)
{
	translate = glm::translate(delta);
	dirty = true;
}

void GLTransform::Rotate(const glm::vec3 &axis, float angle)
{
	rotate = glm::rotate(angle, axis);
	dirty = true;
}

void GLTransform::Scale(const glm::vec3 &factor)
{
	scale = glm::scale(factor);
	dirty = true;
}

glm::mat4 GLTransform::GetTransform()
{
	if (dirty) { ComputeTransform(); }
	return transform;
}

void GLTransform::Billboard(const glm::vec3 &facing, const glm::vec3 &up)
{
	//Replaces rotation matrix
	glm::vec3 face_vector = glm::normalize(facing);
	glm::vec3 side_vector = glm::normalize(glm::cross(face_vector, up));
	glm::vec3 up_vector = glm::normalize(glm::cross(side_vector, face_vector));
	glm::mat3 rot3(side_vector, face_vector, up_vector);
	rotate = glm::mat4(rot3);
}
