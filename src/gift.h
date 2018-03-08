#include "main.h"

#ifndef GIFT_H
#define GIFT_H


class Gift {
public:
    Gift() {}
    Gift(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void change_speed();
    double speed;
    bounding_box_t bounding_box();
    int alive;
private:
    VAO *object;
};

#endif 