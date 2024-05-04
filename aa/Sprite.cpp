#include "Sprite.h"
#include "vertex.h"
#include <cstddef>
#include <iostream>
#include "ResourceManager.h"
using namespace std;
Sprite::Sprite()
{
	vboID = 0;
}


void Sprite::init(float x, float y, int width, int height, string texturePath)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	if (vboID == 0) {
		glGenBuffers(1, &vboID);
	}
	/*float vertexData[12];
	vertexData[0] = x + width;
	vertexData[1] = y + height;
	vertexData[2] = x;
	vertexData[3] = y + height;
	vertexData[4] = x;
	vertexData[5] = y ;

	vertexData[6] = x;
	vertexData[7] = y;
	vertexData[8] = x + width;
	vertexData[9] = y;
	vertexData[10] = x + width;
	vertexData[11] = y + height;*/
	texture = ResourceManager::getTexture(texturePath);
	Vertex vertexData[6];
	vertexData[0].SetPosition(x + width, y + height);
	vertexData[1].SetPosition(x, y+height);
	vertexData[2].SetPosition(x, y);
	vertexData[3].SetPosition(x, y);
	vertexData[4].SetPosition(x+width, y);
	vertexData[5].SetPosition(x + width, y+height);

	for (int i = 0; i < 6; i++) {
		vertexData[i].SetColor(255, 0, 0, 255);
	}
	vertexData[1].SetColor(0, 0, 255, 255);
	vertexData[4].SetColor(0, 255, 0, 255);
	
	vertexData[0].SetUV(1.0f, 1.0f);
	vertexData[1].SetUV(0.0f, 1.0f);
	vertexData[2].SetUV(0.0f, 0.0f);
	vertexData[3].SetUV(0.0f, 0.0f);
	vertexData[4].SetUV(1.0f, 0.0f);
	vertexData[5].SetUV(1.0f, 1.0f);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Sprite::draw()
{
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,0);
	//posicion
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	//color
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	//UV
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
}

Sprite::~Sprite()
{
	if (vboID != 0) {
		glDeleteBuffers(1, &vboID);
	}
}