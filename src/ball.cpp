#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, 0, y);
    this->rotation = 90;
    speedy = 0.0;
    static const GLfloat vertex_buffer_data_hexagon[] = {


        1.0f, 0.1f, -1.0f,
        1.0f, 0.1f, 1.0f,
        -1.0f, 0.1f, -1.0f,//
        -1.0f, 0.1f, -1.0f,
        1.0f, 0.1f, 1.0f,
        -1.0f, 0.1f, 1.0f,//
        -1.0f, 0.1f, 1.0f,
        1.0f, 0.1f, 1.0f,
        0.0f, 0.1f, 2.0f,//
        0.0f, 0.1f, -2.0f,
        1.0f, 0.1f, -1.0f,
        -1.0f, 0.1f, -1.0f,//
    };

    static const GLfloat vertex_buffer_data_base[] = {
        0.0f,1.0f, -2.0f,
        1.0f,1.0f,-1.0f,
        1.0f, 0.0f, -1.0f,
        0.0f,1.0f, -2.0f,
        0.0f,0.0f,-2.0f,
        1.0f, 0.0f, -1.0f,//
        
        0.0f,1.0f,2.0f,
        1.0f,1.0f, 1.0f,
        0.0f, 0.0f, 2.0f,
        1.0f,0.0f,1.0f,
        1.0f,1.0f, 1.0f,
        0.0f, 0.0f, 2.0f,//

        1.0f,1.0f,-1.0f,
        1.0f,1.0f, 1.0f,
        1.0f, 0.0f, -1.0f,
        1.0f,0.0f,1.0f,
        1.0f,1.0f, 1.0f,
        1.0f, 0.0f, -1.0f,//

        
        -1.0f,1.0f,-1.0f,
        -1.0f,1.0f, 1.0f,
        -1.0f, 0.0f, -1.0f,
        -1.0f,0.0f,1.0f,
        -1.0f,1.0f, 1.0f,
        -1.0f, 0.0f, -1.0f,//

        -1.0f,1.0f,-1.0f,
        0.0f,1.0f, -2.0f,
        -1.0f, 0.0f, -1.0f,
        0.0f,0.0f,-2.0f,
        0.0f,1.0f, -2.0f,
        -1.0f, 0.0f, -1.0f,//

        0.0f,1.0f,2.0f,
        -1.0f,1.0f, 1.0f,
        0.0f, 0.0f, 2.0f,
        -1.0f,0.0f,1.0f,
        0.0f, 0.0f, 2.0f,//
        -1.0f,1.0f, 1.0f,


    };


    static const GLfloat vertex_buffer_data_head[] = {
        -0.2f, 0.0f, -0.2f,
        0.0f, 3.0f, 0.0f,
        0.2f, 0.0f, -0.2f,//

        0.0f, 3.0f, 0.0f,
        0.2f, 0.0f, 0.2f,
        -0.2f, 0.0f, 0.2f,//

        0.0f, 3.0f, 0.0f,
        0.2f, 0.0f, -0.2f,
        0.2f, 0.0f, 0.2f,//

        0.0f, 3.0f, 0.0f,
        -0.2f, 0.0f, 0.2f,
        -0.2f, 0.0f, -0.2f,//
    };

    static const GLfloat vertex_buffer_data4[] = {
        //Flag 
        0.0f, 3.0f, 0.0f,
        1.5f, 2.0f, 0.0f,
        0.5f, 2.0f, 0.0f,//
        1.5f, 2.0f, 0.0f,
        0.5f, 2.0f, 0.0f,
        0.2f, 0.0f, 0.0f,//
    };
    // for(int i=0;i<3;i++)
    // {
        this->object[0] = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data_hexagon, COLOR_BLACK, GL_FILL);
        this->object[1] = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data_base, COLOR_GREEN, GL_FILL);
        this->object[2] = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data_head, COLOR_RED, GL_FILL);
        this->object[3] = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data4, COLOR_purple, GL_FILL);
        this->object[4] = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data4+9, COLOR_maroon, GL_FILL);
        // break;
    // }
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(int i=0;i<5;i++)
        draw3DObject(this->object[i]);
}

void Ball::set_position(float x, float y) 
{
    this->position = glm::vec3(x, 0, y);
}

void Ball::change_speed()
{
    if(this->position.y>=0 && this->position.y<=0.1)
        accy=-0.001;
    speedy  += accy ;
    this->position.y += speedy;
    // std::cout<<this->position.y<<"\n";
}


void Ball::tick() 
{
    change_speed();
}

