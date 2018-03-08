#include "main.h"

#ifndef FIREBALL_H
#define FIREBALL_H


class Fireball {
public:
    Fireball() {}
    Fireball(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(float camera_rotation_angle);
    double speed;
    bounding_box_t bounding_box();
    int alive;
private:
    VAO *object;
};

#endif // BALENEMY