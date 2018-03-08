#include "main.h"

#ifndef SEA_H
#define SEA_H


class Sea {
public:
    Sea() {}
    Sea(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
