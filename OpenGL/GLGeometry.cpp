#include "GLGeometry.h"

#include <algorithm>

namespace GLGeometry
{
	void PushVertex(std::vector<float> &geometry, float x, float y, float z = 0.0f)
	{
		geometry.push_back(x);
		geometry.push_back(y);
		geometry.push_back(z);
	}

	std::vector<float> GenMesh(int subdiv)
	{
		float delta = 2.0f / subdiv;
		std::vector<float> data;

		float x_offset = -1.0f, y_offset = -1.0f;
		for (int x = 0; x < subdiv; x++)
		{
			for (int y = 0; y < subdiv; y++)
			{
				PushVertex(data, x_offset, y_offset);
				PushVertex(data, x_offset + delta, y_offset);
				PushVertex(data, x_offset, y_offset + delta);
				
				PushVertex(data, x_offset, y_offset + delta);
				PushVertex(data, x_offset + delta, y_offset);
				PushVertex(data, x_offset + delta, y_offset + delta);

				y_offset += delta;
			}
			x_offset += delta;
			y_offset = -1.0f;
		}

		return data;
	}

	std::vector<float> GenColor(int count)
	{
		std::vector<float> data;
		int b_offset = count * 2 / 3;
		float reciprocal = 1.0f / count;

		for (int i = 0; i < count; i++)
		{
			data.push_back(i * reciprocal);
			data.push_back((count-i) * reciprocal);
			data.push_back(std::min(i,count-i) * reciprocal);
		}
		return data;
	}
}
