#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "main.h"


bool   cannon_keyboard_input = true;
bool   drag_pan = false, old_cki;
double drag_oldx = -1, drag_oldy = -1;

using namespace std;

/* Executed when a regular key is pressed/released/held-down */
/* Prefered for Keyboard events */
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Function is called first on GLFW_PRESS.

    if(action == GLFW_RELEASE) 
    {

        // switch (key) {
        // case GLFW_KEY_C:
        // rectangle_rot_status = !rectangle_rot_status;
        // break;
        // case GLFW_KEY_P:
        // triangle_rot_status = !triangle_rot_status;
        // break;
        // case GLFW_KEY_X:
        // do something ..
        // break;
        // default:
        // break;
        // }
    } 

    else if(action == GLFW_PRESS)
    {

        switch (key) 
        {
            case GLFW_KEY_ESCAPE:
            quit(window);
            break;
            default:
            break;
        }
    }

}

/* Executed for character input (like in text boxes) */
void keyboardChar(GLFWwindow *window, unsigned int key) {
    switch (key) {
        case 'Q':
        case 'q':
        quit(window);
        break;
        case 'v':
        case 'V':
        view_change();
        break;
        // case 'f':
        case 'f':
        case 'F':
        fire_ball();
        default:
        break;
    }
}

/* Executed when a mouse button is pressed/released */
void mouseButton(GLFWwindow *window, int button, int action, int mods) {
    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
        if (action == GLFW_PRESS) {

            old_cki = cannon_keyboard_input;
            drag_pan = true;
            cannon_keyboard_input = true;
            if(drag_pan==true && cannon_keyboard_input==true)
            {
                glfwGetCursorPos(window,&x,&y);
                hx=600-x;
                hy=600-y;
            }
        } else if (action == GLFW_RELEASE) {
            cannon_keyboard_input = old_cki;
            drag_pan = false;
            drag_oldx = drag_oldy = -1;
        }
        break;
        default:
        break;
    }
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    // Do something
    double valadd=0.1;
    if(yoffset==-1)
    {
        zoom=zoom+1;
        double val1=cos((M_PI/180)*camera_rotation_angle);
        double val2=sin((M_PI/180)*camera_rotation_angle);
        helx=helx-zoom*val1;
        helz=helz-zoom*val2;
        hely=hely+valadd;
    } 
    else if(yoffset==1)
    {
        zoom=zoom-1;
        double val1=cos((M_PI/180)*camera_rotation_angle);
        double val2=sin((M_PI/180)*camera_rotation_angle);
        
        helx=helx+zoom*val1;
        helz=helz+zoom*val2;
        hely=hely-valadd;
    }
}
