#include "enemy.h"
#include "main.h"
Enemy::Enemy(float x, float z, color_t color) 
{
    int y_pos=0;
    this->rotation = 90+rand()%360;
    this->position = glm::vec3(x, y_pos, z);
    this->speed = 0.07;
    if(level>1)
        this->speed=0.08;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        // Side 1 => Back
        -3.0f, -2.0f, -2.0f,
        -3.0f, -2.0f, 2.0f,
        -3.0f, 2.0f, 2.0f,

        -3.0f, 2.0f, 2.0f,
        -2.0f, -2.0f, -2.0f,
        -3.0f, 2.0f, -2.0f,

        -3.0f, -2.0f, -2.0f,
        -3.0f, -2.0f, 2.0f,
        4.0f, 0.0f, 0.0f,

        // Side 3 => Top


        // Side 4 => Left
        -3.0f, -2.0f, -2.0f,
        -3.0f, 2.0f, -2.0f,
        4.0f, 0.0f, 0.0f,

        -3.0f, 2.0f, -2.0f,
        -3.0f, 2.0f, 2.0f,
        4.0f, 0.0f, 0.0f,

        // Side 5 => Right
        -3.0f, -2.0f, 2.0f,
        -3.0f, 2.0f, 2.0f,
        4.0f, 0.0f, 0.0f
    };

    this->object = create3DObject(GL_TRIANGLES, 18, vertex_buffer_data, color, GL_FILL);
}

void Enemy::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Enemy::set_position(float x, float z) 
{
    this->position = glm::vec3(x, 0, z);
}

void Enemy::tick() {
    float theta = (this->rotation - 90) * M_PI / 180;
    float new_x = this->position.x - this->speed * sin(theta);
    float new_z = this->position.z - this->speed * cos(theta);
    this->set_position(new_x,new_z);
}
