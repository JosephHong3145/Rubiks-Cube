#include "Rubiks_Cube.h"
#include <ctime>


void delay(int ms) {
    clock_t goal = ms + clock();
    while (goal > clock());
    return;
}

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
                newCube.setPositionTag(vec3(x, y, z));
                newCube.setInitialPositionTag(vec3(x, y, z));
                cubeArray.push_back(newCube);
                newCube.drawModel();
            }
        }
    }
}

void Rubiks_Cube::setShader(Shader S) {
    for (int i = 0; i < 27; i++) {
        cubeArray[i].setCurrentShader(S);
    }
}

void Rubiks_Cube::drawModel() {
    glBindTexture(GL_TEXTURE_2D, 0);

    for (int i = 0; i < 27; i++) {
        glBindTexture(GL_TEXTURE_2D, texturePack[0]);
        if (cubeArray[i].getInitialPositionTag().y == 0) cubeArray[i].drawBotFace();

        glBindTexture(GL_TEXTURE_2D, texturePack[1]);
        if (cubeArray[i].getInitialPositionTag().y == 2) cubeArray[i].drawTopFace();

        glBindTexture(GL_TEXTURE_2D, texturePack[2]);
        if (cubeArray[i].getInitialPositionTag().x == 0) cubeArray[i].drawLeftFace();

        glBindTexture(GL_TEXTURE_2D, texturePack[3]);
        if (cubeArray[i].getInitialPositionTag().x == 2) cubeArray[i].drawRightFace();

        glBindTexture(GL_TEXTURE_2D, texturePack[4]);
        if (cubeArray[i].getInitialPositionTag().z == 0) cubeArray[i].drawBackFace();

        glBindTexture(GL_TEXTURE_2D, texturePack[5]);
        if (cubeArray[i].getInitialPositionTag().z == 2) cubeArray[i].drawFrontFace();

    }
}

void Rubiks_Cube::rotate_y(string direction, int y) {
    if (direction == "CCW") {
        rotateFactor.y = -90;
    }

    else if (direction == "CW") {
        rotateFactor.y = 90;
    }

    mat4 rotateMatrix = rotate(mat4(1.0f), radians(rotateFactor.y), vec3(0.0f, 1.0f, 0.0f));

    for (int i = 0; i < cubeArray.size(); i++) {
        if (cubeArray[i].getPositionTag().y == y) {
            cubeArray[i].rotateCube(rotateMatrix);
        }
    }
    
    //re-set position tag to fit the newly rotated cube
    for (int i = 0; i < cubeArray.size(); i++) {
        cubeArray[i].rotatePositionTagY(direction, y);
    }
}

void Rubiks_Cube::rotate_x(string direction, int x) {
    if (direction == "CCW") {
        rotateFactor.x = 90;
    }

    else if (direction == "CW") {
        rotateFactor.x = -90;
    }

    //set rotation matrix
    mat4 rotateMatrix = rotate(mat4(1.0f), radians(rotateFactor.x), vec3(1.0f, 0.0f, 0.0f));

    //perform rotation (using said matrix)
    for (int i = 0; i < cubeArray.size(); i++) {
        if (cubeArray[i].getPositionTag().x == x) cubeArray[i].rotateCube(rotateMatrix);
            
    }

    //re-set position tag to fit the newly rotated cube
    for (int i = 0; i < cubeArray.size(); i++) {
        cubeArray[i].rotatePositionTagX(direction, x);

    }
}

void Rubiks_Cube::rotate_z(string direction, int z) {
    if (direction == "CCW") {
        rotateFactor.z = 90;
    }

    else if (direction == "CW") {
        rotateFactor.z = -90;
    }

    mat4 rotateMatrix = rotate(mat4(1.0f), radians(rotateFactor.z), vec3(0.0f, 0.0f, 1.0f));

    for (int i = 0; i < cubeArray.size(); i++) {
        if (cubeArray[i].getPositionTag().z == z) cubeArray[i].rotateCube(rotateMatrix);
    }

    //re-set position tag to fit the newly rotated cube
    for (int i = 0; i < cubeArray.size(); i++) {
        cubeArray[i].rotatePositionTagZ(direction, z);
    }
}

void Rubiks_Cube::resetPosition() {

    for (int i = 0; i < cubeArray.size(); i++) {
        cubeArray[i].setDefaultRotation(rotate(mat4(1.0f), radians(0.0f), vec3(0.0f, 1.0f, 0.0f)));
        cubeArray[i].setPositionTag(cubeArray[i].getInitialPositionTag());
    }

}

void Rubiks_Cube::debug() {
    /*for (int i = 0; i < cubeArray.size(); i++) {
        if (cubeArray[i].getPositionTag().y == 0) {
            cubeArray[i].printPositionTag();
        }

        if (cubeArray[i].getPositionTag().y == 1) {
            cubeArray[i].printPositionTag();
        }

        if (cubeArray[i].getPositionTag().y == 2) {
            cubeArray[i].printPositionTag();
        }
    }*/

    for (int i = 0; i < cubeArray.size(); i++) {
        if (cubeArray[i].getInitialPositionTag() == vec3(0.0f)) {
            cubeArray[i].printPositionTag();
        }
    }
}