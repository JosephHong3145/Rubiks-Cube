#include "Rubiks_Cube.h"
#include <dos.h>

Rubiks_Cube::Rubiks_Cube() {

}

Rubiks_Cube::Rubiks_Cube(vec3 pos, vector<GLuint> texture) {
	texturePack = texture;
	position = pos;
}

void Rubiks_Cube::generateCube(Shader S) {
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            for (int z = 0; z < 3; z++) {
                Cube newCube = Cube(vec3(1.0f), S);
                newCube.setDefaultPosition(vec3(x - 1, y - 1, z - 1) + position);
                cubeArray[x][y][z] = newCube;
                newCube.drawModel();
            }
        }
    }
}

void Rubiks_Cube::setShader(Shader S) {
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            for (int z = 0; z < 3; z++) {
                cubeArray[x][y][z].setCurrentShader(S);

            }
        }
    }
}

void Rubiks_Cube::drawModel() {
    glBindTexture(GL_TEXTURE_2D, 0);

    //draw bottom face 
    glBindTexture(GL_TEXTURE_2D, texturePack[0]);
    for (int x = 0; x < 3; x++) {
        for (int z = 0; z < 3; z++) {
            cubeArray[x][0][z].drawBotFace();
        }
    }

    //draw top face
    glBindTexture(GL_TEXTURE_2D, texturePack[1]);
    for (int x = 0; x < 3; x++) {
        for (int z = 0; z < 3; z++) {
            cubeArray[x][2][z].drawTopFace();
        }
    }

    //draw left face
    glBindTexture(GL_TEXTURE_2D, texturePack[2]);
    for (int y = 0; y < 3; y++) {
        for (int z = 0; z < 3; z++) {
            cubeArray[0][y][z].drawLeftFace();
        }
    }

    //draw right face
    glBindTexture(GL_TEXTURE_2D, texturePack[3]);
    for (int y = 0; y < 3; y++) {
        for (int z = 0; z < 3; z++) {
            cubeArray[2][y][z].drawRightFace();
        }
    }

    //draw Front face
    glBindTexture(GL_TEXTURE_2D, texturePack[4]);
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            cubeArray[x][y][2].drawFrontFace();
        }
    }

    //draw back face
    glBindTexture(GL_TEXTURE_2D, texturePack[5]);
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            cubeArray[x][y][0].drawBackFace();
        }
    }
}

void Rubiks_Cube::rotate_y0(string direction) {

    for (int i = 0; i < 90; i++) {
        if (direction == "left") {
            rotateFactory1--;
            //insert delay here
        }

        else if (direction == "right") {
            rotateFactory1++;
            //insert delay here
        }

        mat4 rotateMatrix = rotate(mat4(1.0f), radians(rotateFactory1), vec3(0.0f, 1.0f, 0.0f));

        for (int x = 0; x < 3; x++) {
            for (int z = 0; z < 3; z++) {
                cubeArray[x][0][z].setCustomRotation(rotateMatrix);
            }
        }
    }
}