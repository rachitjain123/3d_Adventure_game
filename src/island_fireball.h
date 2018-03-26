#include "main.h"

#ifndef ISLAND_FIREBALL_H
#define ISLAND_FIREBALL_H


class Island_Fireball {
public:
    Island_Fireball() {}
    Island_Fireball(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(float camera_rotation_angle,float val);
    double speed;
    bounding_box_t bounding_box();
    int alive;
private:
    VAO *object;
};

#endif 