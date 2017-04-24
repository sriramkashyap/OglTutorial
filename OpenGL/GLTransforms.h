#ifndef GLTRANSFORMS_H
#define GLTRANSFORMS_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

class GLCamera
{
protected:
	bool dirty;
	glm::vec3 eye, lookat, up;
	float fov, aspect_ratio, near_z, far_z;
	glm::mat4 view, proj, camera;
	void ComputeFinalMatrix();
	void ComputeProjMatrix();
	void ComputeViewMatrix();

public:
	GLCamera();
	void SetupView(const glm::vec3 &eye, const glm::vec3 &lookat, const glm::vec3 &up);
	void SetupProjection(float fov, float aspect_ratio, float near_z, float far_z);
	void PlaceAt(const glm::vec3 &eye);
	void LookAt(const glm::vec3 &lookat);
	glm::mat4 GetTransform();
};

class GLTransform
{
protected:
	bool dirty;
	glm::mat4 translate, rotate, scale;
	glm::mat4 transform;
	void ComputeTransform();

public:
	GLTransform();
	void Translate(const glm::vec3 &delta);
	void Rotate(const glm::vec3 &axis, float angle);
	void Scale(const glm::vec3 &factor);
	glm::mat4 GetTransform();
	void Billboard(const glm::vec3 &facing, const glm::vec3 &up);

};

#endif
