#pragma once
#include <GL/glew.h>

struct Position {
	float x;
	float y;
};

struct Color {
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct Vertex {
	Position position;
	Color color;
	void SetPosition(float x, float y) {
		position.x = x;
		position.y = y;
	}
	void SetColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
		color.r = r; 
		color.g = g;
		color.b = b;
		color.a = a;
	}
};