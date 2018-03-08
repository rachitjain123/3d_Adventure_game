#include "gift.h"
#include "main.h"
Gift::Gift(float x, float y, color_t color) {
    this->position = glm::vec3(x, 2, y);
    this->rotation = 1;
   float r = 1.5;

    float n = 10000;
    // float r = 0.5;

    float theta = 2*3.14159/n;

    GLfloat vertex_buffer_data[90000];

    int i,j;
    for(i=0; i<n; i++)
    {
        float ab=theta*i;
        float angle=ab+theta;

        float x=r*cos(angle);
        float y=r*sin(angle);
        float z=0.0f;

        float x1=r*cos(ab);
        float y1=r*sin(ab);
        float z1=0.0f;

        float x2=0.0f;
        for(j=0;j<3;j++)
            vertex_buffer_data[i*9+j]=x2;
        vertex_buffer_data[i*9+3]=x1;
        vertex_buffer_data[i*9+4]=y1;
        vertex_buffer_data[i*9+5]=z1;
        vertex_buffer_data[i*9+6]=x;
        vertex_buffer_data[i*9+7]=y;
        vertex_buffer_data[i*9+8]=z;

    }

    this->object = create3DObject(GL_TRIANGLES, 30000, vertex_buffer_data, COLOR_pila, GL_FILL);
}

void Gift::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Gift::set_position(float x, float y) {
    this->position = glm::vec3(x, 0, y);
}

void Gift::change_speed()
{
    int accx=0;
    int accy=0;

    int speedx  = accx ;
    int speedy  = accy ;
}
void Gift::tick() 
{
    this->rotation++;
}
bounding_box_t Gift::bounding_box() {
    float x = this->position.x;
    float z = this->position.z;
    bounding_box_t bbox = { x, 0, z, 0.4,0.4,0.4};
    return bbox;
}

