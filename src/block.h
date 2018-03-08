#include "main.h"

#ifndef BLOCK_H
#define BLOCK_H


class Block {
public:
    Block() {}
    Block(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void change_speed();
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
