#include "GLGeometry.h"

#include <algorithm>
#include <cmath>

namespace GLGeometry
{
	void PushVertex3(std::vector<float> &geometry, float x, float y, float z = 0.0f)
	{
		geometry.push_back(x);
		geometry.push_back(y);
		geometry.push_back(z);
	}

	void PushVertex2(std::vector<float> &geometry, float x, float y)
	{
		geometry.push_back(x);
		geometry.push_back(y);
	}
	
	GLModel GenBillBoard()
	{
		GLModel model;

		std::vector<float> &posdata = model.position;
		std::vector<float> &texdata = model.texcoord;

		PushVertex3(posdata, 1.0, 0.0, 0.0);
		PushVertex3(posdata, 0.0, 0.0, 1.0);
		PushVertex3(posdata, 0.0, 0.0, -1.0);
		PushVertex3(posdata, 0.0, 0.0, 1.0);
		PushVertex3(posdata, 0.0, 0.0, -1.0);
		PushVertex3(posdata, -1.0, 0.0, 0.0);

		PushVertex2(texdata, 0.0, 0.0);
		PushVertex2(texdata, 0.0, 1.0);
		PushVertex2(texdata, 1.0, 0.0);
		PushVertex2(texdata, 0.0, 1.0);
		PushVertex2(texdata, 1.0, 0.0);
		PushVertex2(texdata, 1.0, 1.0);

		return model;
	}

	GLModel Gen2DMesh(int subdiv)
	{
		GLModel model;

		//Calculate positions of triangles
		std::vector<float> &posdata		= model.position;
		std::vector<float> &colordata	= model.color;
		std::vector<float> &texdata		= model.texcoord;
		std::vector<float> &normdata	= model.normal;
		
		//Generate Position data
		float x_offset = -1.0f, y_offset = -1.0f;
		float delta = 2.0f / subdiv;
		for (int x = 0; x < subdiv; x++)
		{
			for (int y = 0; y < subdiv; y++)
			{
				PushVertex3(posdata, x_offset, y_offset);
				PushVertex3(posdata, x_offset + delta, y_offset);
				PushVertex3(posdata, x_offset, y_offset + delta);

				PushVertex3(posdata, x_offset, y_offset + delta);
				PushVertex3(posdata, x_offset + delta, y_offset);
				PushVertex3(posdata, x_offset + delta, y_offset + delta);
				y_offset += delta;
			}
			x_offset += delta;
			y_offset = -1.0f;
		}

		//Normal vectors for each vertex are same
		for (unsigned int n = 0; n < posdata.size(); n++)
		{
			PushVertex3(normdata, 0.0, 0.0, 1.0);
		}

		//Generate texture coordinates (0.0 to 1.0)
		x_offset = 0.0f;
		y_offset = 0.0f;
		delta = 1.0f / subdiv;
		for (int x = 0; x < subdiv; x++)
		{
			for (int y = 0; y < subdiv; y++)
			{
				PushVertex2(texdata, x_offset, y_offset);
				PushVertex2(texdata, x_offset + delta, y_offset);
				PushVertex2(texdata, x_offset, y_offset + delta);

				PushVertex2(texdata, x_offset, y_offset + delta);
				PushVertex2(texdata, x_offset + delta, y_offset);
				PushVertex2(texdata, x_offset + delta, y_offset + delta);

				y_offset += delta;
			}
			x_offset += delta;
			y_offset = 0.0f;
		}
		
		//Generate some smoothly varying color values for each vertex
		int count = subdiv*subdiv*6;
		int b_offset = count * 2 / 3;
		float reciprocal = 1.0f / count;

		for (int i = 0; i < count; i++)
		{
			colordata.push_back(i * reciprocal);
			colordata.push_back((count - i) * reciprocal);
			colordata.push_back(std::min(i, count - i) * reciprocal);
		}

		return model;
	}

	GLModel GenCylinder(int segments, int slices)
	{
		GLModel model;

		std::vector<float> &position = model.position;
		std::vector<float> &texcoord = model.texcoord;
		std::vector<float> &normal = model.normal;
		std::vector<float> &color = model.color;

		const float two_pi = 2.0f * 3.14159f;
		std::vector<float> data;

		float radius1 = 1.0f;
		float radius2 = 1.0f;

		for (int i = 0; i < segments; i++) //Vertical subdivisions
		{
			float z1 = (2.0f * i / segments) - 1.0f;
			float z2 = (2.0f * (i + 1) / segments) - 1.0f;

			for (int j = 0; j < slices; j++) //Radial subdivisions
			{
				float theta1 = two_pi * j / slices;
				float theta2 = two_pi * (j + 1) / slices;

				float x11 = radius1 * std::cos(theta1);
				float x12 = radius1 * std::cos(theta2);
				float x21 = radius2 * std::cos(theta1);
				float x22 = radius2 * std::cos(theta2);

				float y11 = radius1 * std::sin(theta1);
				float y12 = radius1 * std::sin(theta2);
				float y21 = radius2 * std::sin(theta1);
				float y22 = radius2 * std::sin(theta2);

				//Position data for sphere
				PushVertex3(position, x11, y11, z1);
				PushVertex3(position, x21, y21, z2);
				PushVertex3(position, x22, y22, z2);

				PushVertex3(position, x11, y11, z1);
				PushVertex3(position, x22, y22, z2);
				PushVertex3(position, x12, y12, z1);

				//Some color data. just use |position| here...
				PushVertex3(color, std::abs(x11), std::abs(y11), std::abs(z1));
				PushVertex3(color, std::abs(x21), std::abs(y21), std::abs(z2));
				PushVertex3(color, std::abs(x22), std::abs(y22), std::abs(z2));

				PushVertex3(color, std::abs(x11), std::abs(y11), std::abs(z1));
				PushVertex3(color, std::abs(x22), std::abs(y22), std::abs(z2));
				PushVertex3(color, std::abs(x12), std::abs(y12), std::abs(z1));

				//Normal vectors, again same as position (x,y) because this is a unit circle.
				PushVertex3(normal, x11, y11, 0.0f);
				PushVertex3(normal, x21, y21, 0.0f);
				PushVertex3(normal, x22, y22, 0.0f);

				PushVertex3(normal, x11, y11, 0.0f);
				PushVertex3(normal, x22, y22, 0.0f);
				PushVertex3(normal, x12, y12, 0.0f);

				//Texture coordinates
				PushVertex2(texcoord, static_cast<float>(j) / slices, static_cast<float>(i) / segments);
				PushVertex2(texcoord, static_cast<float>(j) / slices, static_cast<float>(i + 1) / segments);
				PushVertex2(texcoord, static_cast<float>(j + 1) / slices, static_cast<float>(i + 1) / segments);

				PushVertex2(texcoord, static_cast<float>(j) / slices, static_cast<float>(i) / segments);
				PushVertex2(texcoord, static_cast<float>(j + 1) / slices, static_cast<float>(i + 1) / segments);
				PushVertex2(texcoord, static_cast<float>(j + 1) / slices, static_cast<float>(i) / segments);
			}
		}

		return model;
	}

	GLModel GenSphere(int segments, int slices)
	{
		GLModel model;

		std::vector<float> &position = model.position;
		std::vector<float> &texcoord = model.texcoord;
		std::vector<float> &normal = model.normal;
		std::vector<float> &color = model.color;

		//Unit sphere centered at zero
		const float two_pi = 2.0f * 3.14159f;
		std::vector<float> data;
		for (int i = 0; i < segments; i++) //Vertical subdivisions
		{
			float z1 = (2.0f * i / segments) - 1.0f;
			float z2 = (2.0f * (i+1) / segments) - 1.0f;

			float radius1 = std::sqrt(1.0f - z1*z1);
			float radius2 = std::sqrt(1.0f - z2*z2);

			for (int j = 0; j < slices; j++) //Radial subdivisions
			{
				float theta1 = two_pi * j / slices;
				float theta2 = two_pi * (j + 1) / slices;

				float x11 = radius1 * std::cos(theta1);
				float x12 = radius1 * std::cos(theta2);
				float x21 = radius2 * std::cos(theta1);
				float x22 = radius2 * std::cos(theta2);

				float y11 = radius1 * std::sin(theta1);
				float y12 = radius1 * std::sin(theta2);
				float y21 = radius2 * std::sin(theta1);
				float y22 = radius2 * std::sin(theta2);

				//Position data for sphere
				PushVertex3(position,x11, y11, z1);
				PushVertex3(position, x21, y21, z2);
				PushVertex3(position, x22, y22, z2);

				PushVertex3(position, x11, y11, z1);
				PushVertex3(position, x22, y22, z2);
				PushVertex3(position, x12, y12, z1);

				//Color data. just use |position| here...
				PushVertex3(color, fabs(x11), fabs(y11), fabs(z1));
				PushVertex3(color, fabs(x21), fabs(y21), fabs(z2));
				PushVertex3(color, fabs(x22), fabs(y22), fabs(z2));

				PushVertex3(color, fabs(x11), fabs(y11), fabs(z1));
				PushVertex3(color, fabs(x22), fabs(y22), fabs(z2));
				PushVertex3(color, fabs(x12), fabs(y12), fabs(z1));

				//Normal vectors, again same as position because this is a unit sphere.
				PushVertex3(normal, x11, y11, z1);
				PushVertex3(normal, x21, y21, z2);
				PushVertex3(normal, x22, y22, z2);

				PushVertex3(normal, x11, y11, z1);
				PushVertex3(normal, x22, y22, z2);
				PushVertex3(normal, x12, y12, z1);

				//Texture coordinates
				PushVertex2(texcoord, static_cast<float>(j) / slices, static_cast<float>(i) / segments);
				PushVertex2(texcoord, static_cast<float>(j) / slices, static_cast<float>(i+1) / segments);
				PushVertex2(texcoord, static_cast<float>(j+1) / slices, static_cast<float>(i+1) / segments);

				PushVertex2(texcoord, static_cast<float>(j) / slices, static_cast<float>(i) / segments);
				PushVertex2(texcoord, static_cast<float>(j+1) / slices, static_cast<float>(i+1) / segments);
				PushVertex2(texcoord, static_cast<float>(j+1) / slices, static_cast<float>(i) / segments);

			}
		}

		return model;
	}
}
