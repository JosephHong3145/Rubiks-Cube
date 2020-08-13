#pragma once
#include "Cube.h"
#include <array>
#include <vector>

using namespace glm;
using namespace std;

class Rubiks_Cube {
private:
	array<array<array<Cube, 3>, 3>, 3> cubeArray;
	vec3 position;
	vector<GLuint> texturePack;

	float rotateFactory1 = 0.0f,
		rotateFactory2 = 0.0f,
		rotateFactory3 = 0.0f,
		rotateFactorx0 = 0.0f,
		rotateFactorx1 = 0.0f,
		rotateFactorx2 = 0.0f,
		rotateFactorz1 = 0.0f,
		rotateFactorz2 = 0.0f,
		rotateFactorz3 = 0.0f;

public:
	Rubiks_Cube();
	Rubiks_Cube(vec3 pos, vector<GLuint> texture);

	void generateCube(Shader S);
	void setShader(Shader S);
	void drawModel();

	void rotate_y0(string direction);
};