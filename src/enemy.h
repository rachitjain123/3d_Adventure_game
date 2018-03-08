#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H


class Enemy {
public:
    Enemy() {}
    Enemy(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    bounding_box_t bounding_box();
    int alive;
private:
    VAO *object;
};

#endif // BALENEMY