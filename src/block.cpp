#include "block.h"
#include "main.h"

Block::Block(float x, float y, color_t color) {
    this->position = glm::vec3(x, 0, y);
    this->rotation = 0;
    static const GLfloat vertex_buffer_data[] = {
        
        0.0f, 1.5f, 0.0f,
        -0.5f, 0.0f, -0.5f,
        0.5f, 0.0f, -0.5f,//
        0.0f, 1.5f, 0.0f,
        0.5f, 0.0f, -0.5f,
        0.5f, 0.0f, 0.5f,//
        0.0f, 1.5f, 0.0f,
        0.5f, 0.0f, 0.5f,
        -0.5f, 0.0f, 0.5f,//
        0.0f, 1.5f, 0.0f,
        -0.5f, 0.0f, 0.5f,
        -0.5f, 0.0f, -0.5f,//
    };

   

    this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, color, GL_FILL);
}

void Block::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Block::set_position(float x, float y) {
    this->position = glm::vec3(x, 0, y);
}

void Block::change_speed()
{
    int accx=0;
    int accy=0;

    int speedx  = accx ;
    int speedy  = accy ;
}
void Block::tick() 
{
}
bounding_box_t Block::bounding_box() {
    float x = this->position.x;
    float z = this->position.z;
    bounding_box_t bbox = { x, 0, z, 0.4,0.4,0.4};
    return bbox;
}

