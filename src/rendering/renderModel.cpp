#include "renderModel.h"
#include <iostream>

const int RenderModel::GetVertexCount() {
	return vertexCount;
}

const int RenderModel::GetIndexCount() {
	return indexCount;
}

const GLfloat* RenderModel::GetVertexData() {
	return vertexData;
}

const GLuint* RenderModel::GetIndexData() {
	return indexData;
}

glm::vec3* RenderModel::GetNormalData() {
	return normalData;
}

void RenderModel::init() {
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &VertexBufferID);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, GetVertexDataSize(), vertexData, GL_STATIC_DRAW);

	glGenBuffers(1, &IndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetIndexDataSize(), indexData, GL_STATIC_DRAW);

	glGenBuffers(1, &NormalBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, NormalBufferID);
	glBufferData(GL_ARRAY_BUFFER, GetNormalDataSize(), normalData, GL_STATIC_DRAW);
}

void RenderModel::calculateNormals() {
	for (int triangleOffset = 0; triangleOffset < vertexCount*3; triangleOffset += 9) {
		glm::vec3 a = glm::vec3(
			vertexData[triangleOffset + 3] - vertexData[triangleOffset],
			vertexData[triangleOffset + 4] - vertexData[triangleOffset + 1],
			vertexData[triangleOffset + 5] - vertexData[triangleOffset + 2]
		);

		glm::vec3 b = glm::vec3(
			vertexData[triangleOffset + 6] - vertexData[triangleOffset],
			vertexData[triangleOffset + 7] - vertexData[triangleOffset + 1],
			vertexData[triangleOffset + 8] - vertexData[triangleOffset + 2]
		);

		glm::vec3 triangleNormal = glm::vec3(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		);

		normalData[triangleOffset / 3 + 0] = triangleNormal;
		normalData[triangleOffset / 3 + 1] = triangleNormal;
		normalData[triangleOffset / 3 + 2] = triangleNormal;
	}
}

void RenderModel::dispose() {
	glDeleteBuffers(1, &VertexBufferID);
	glDeleteBuffers(1, &IndexBufferID);
	glDeleteBuffers(1, &NormalBufferID);
	glDeleteVertexArrays(1, &VertexArrayID);
}

const int RenderModel::GetVertexDataSize() {
	return vertexCount * 3 * sizeof(vertexData[0]);
}

const int RenderModel::GetIndexDataSize() {
	return indexCount * sizeof(indexData[0]);
}

const int RenderModel::GetNormalDataSize() {
	return vertexCount * sizeof(normalData[0]);
}