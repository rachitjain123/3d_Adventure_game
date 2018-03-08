#include "main.h"
#include "timer.h"
#include "ball.h"
#include "sea.h"
#include "block.h"
#include "fireball.h"
#include "enemy.h"
#include "gift.h"
#include "barrel_gift.h"
#include "barrel.h"
#include <math.h>
#define nl "\n"
using namespace std;


GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

class timer {
private:
    unsigned long begTime;
public:
    void start() {
        begTime = clock();
    }

    unsigned long elapsedTime() {
        return ((unsigned long) clock() - begTime) / CLOCKS_PER_SEC;
    }

    bool isTimeout(unsigned long seconds) {
        return seconds >= elapsedTime();
    }
};
timer tt;
timer tt2;

int view =0;
float zoom=10;
Ball boat;
Sea  sea;
Fireball fireball;
Block  blocks[123];
Enemy enemy[15];
Gift gift[15];
Barrel_gift barrel_gift[4];
Barrel barrel[4];

float eye_x,eye_y,eye_z,target_x,target_y,target_z,helx,hely,helz,hx,hy,hz;
double x,y;

int score;
int flag_color;
int lives;
int numballs;
int enemies_killed;
int healthpoints;
int boostflag=0;
int level;
int time_boostflag=0;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
extern bool cannon_keyboard_input, drag_pan;
extern double drag_oldx, drag_oldy;

Timer t60(1.0 / 60);
void draw() 
{
    // reset_screen();
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glUseProgram(programID);
    
    target_x=boat.position.x;
    target_y=boat.position.y;
    target_z=boat.position.z;
    
    double fval;
    if(view%5==1)
    {
        eye_y=boat.position.y+2.1;
        fval=0;

        if(target_x==boat.position.x)
            target_x=boat.position.x-5*cos(camera_rotation_angle*M_PI/180.0f);
        if(target_y==boat.position.y)            
            target_y=1;
        if(target_z==boat.position.z)
            target_z=boat.position.z-5*sin(camera_rotation_angle*M_PI/180.0f);
    }
    else if(view%5==0)
    {
        eye_y=3;
        fval =5;
    }
    else if(view%5==2)
    {
        eye_y=10;
        fval=0.6;
    }
    else if(view%5==3)
    {
        eye_y=5;
        fval=1;
    }
    //helicopter view
    else if(view%5==4)  
    {
        fval=-1;
        eye_x=helx;
        eye_y=hely;
        eye_z=helz;

        if(target_x==0)
        {
            target_y=0;
            target_z=0;
            eye_y=0;
        }
    }

    eye_z=boat.position.z+fval*sin(camera_rotation_angle*M_PI/180.0f);
    eye_x=boat.position.x+fval*cos(camera_rotation_angle*M_PI/180.0f);
    
    if(fval==1)
    {
        eye_x=1;
        eye_z=1;
    }

    if(fval ==-1)
    {
        //helicopter
        target_x=hx-x;
        target_y=hy+2;
        target_z=hz+y;
    }


    glm::vec3 eye (eye_x, eye_y, eye_z);
    glm::vec3 target (target_x, target_y, target_z);
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    boat.draw(VP);
    sea.draw(VP);
    for(int i=0;i<15;i++)
    {
        gift[i].draw(VP);
        enemy[i].draw(VP);
    }
    // blo.draw(VP);
    fireball.draw(VP);
    for(int i=0;i<123;i++)
    {
        blocks[i].draw(VP);
    }
    // for(int i=0;i<4;i++)
    // {
    //     barrel_gift[i].draw(VP);
    // }
    for(int i=0;i<4;i++)
    {
        barrel[i].draw(VP);
        barrel_gift[i].draw(VP);
    }

}
void tick_input(GLFWwindow *window) 
{
    int l1  = glfwGetKey(window, GLFW_KEY_A);
    int r1 = glfwGetKey(window, GLFW_KEY_D);
    if(glfwGetKey(window, GLFW_KEY_LEFT))
    {
        camera_rotation_angle-=2;
        boat.rotation+=2;
    }
    else if(glfwGetKey(window, GLFW_KEY_RIGHT)) 
    {
        camera_rotation_angle+=2;
        boat.rotation-=2;
    }
    else if(glfwGetKey(window, GLFW_KEY_UP)) 
    {
        double speedd=0.1;
        if(boostflag==1 && tt.elapsedTime()<time_boostflag+5)
            speedd=0.8;
        else if(boostflag==1 && tt.elapsedTime()>=time_boostflag+5)
            boostflag=0;
        boat.position.z-=speedd*sin((M_PI/180)*camera_rotation_angle);
        boat.position.x-=speedd*cos((M_PI/180)*camera_rotation_angle);
    }
    else if(glfwGetKey(window, GLFW_KEY_SPACE))
    {
        // cout<<"fa";
        boat.speedy=0.1;
        boat.accy=-0.01;
        double speedd=0.2;  
        boat.position.z-=speedd*sin((M_PI/180)*camera_rotation_angle);
        boat.position.x-=speedd*cos((M_PI/180)*camera_rotation_angle);
    }
    else
    {
        if(glfwGetKey(window, GLFW_KEY_R))
        {
            screen_center_x=0;
            screen_center_y=0;
            screen_zoom=1;
            reset_screen();
        }
        if (l1 && screen_center_x - 4/screen_zoom > -4) 
        {   
            screen_center_x -= 0.05; 
            reset_screen(); 
        }
        if (r1 && screen_center_x + 4/screen_zoom < 4) 
        {
            screen_center_x += 0.05;
            reset_screen();
        }
        if (glfwGetKey(window, GLFW_KEY_W) && screen_center_y + 4/screen_zoom < 4)
        { 
            screen_center_y += 0.05;
            reset_screen();
        }
        if (glfwGetKey(window, GLFW_KEY_S) && screen_center_y - 4/screen_zoom > -4)
        {
            screen_center_y -= 0.05; 
            reset_screen();
        }
    }
}
void tick_elements() 
{
    glfwGetCursorPos(window,&x,&y);
    int cnt=0;
    int cnt2=0;

    if(healthpoints<=0)
    {
        glfwSetWindowTitle(window,"GAME OVER");
        // mainball.position.x=-100;
    }
    boat.tick();
    for(int i=0;i<4;i++)
        barrel[i].tick();

    if(boat.position.y<=-0.1 && boat.position.y>=-0.2 && boat.speedy<0)
        boat.accy=0.001;
    if(boat.position.y<=-0.2)
    {
        // cout<<"Dada";
        boat.position.y=0;
        boat.speedy=0;
        // cout<<boat.position.y<<nl;
    }
    for(int i=0;i<123;i++)
    {
        double r1=sqrt((blocks[i].position.x-boat.position.x)*(blocks[i].position.x-boat.position.x)+(blocks[i].position.z-boat.position.z)*(blocks[i].position.z-boat.position.z));
        // cout<<blocks[i].position.x<<nl;
        // cout<<r1<<nl;
        if(r1<1)
        {
            boat.position.z-=-0.1*sin((M_PI/180)*camera_rotation_angle);
            boat.position.x-=-0.1*cos((M_PI/180)*camera_rotation_angle);
            cnt=1;
            healthpoints-=20;
        }
    }
    for(int i=0;i<4;i++)
    {
        barrel_gift[i].tick();
        // if(t3.elapsedTime()>=1)
        // {
        barrel_gift[i].position.x=barrel[i].position.x;
        barrel_gift[i].position.z=barrel[i].position.z+3;
        // }
        // barrel_gift[i].position.x=barrel[i].position.x;
        double r1=sqrt((barrel[i].position.x-boat.position.x)*(barrel[i].position.x-boat.position.x)+(barrel[i].position.z-boat.position.z)*(barrel[i].position.z-boat.position.z));
        // cout<<blocks[i].position.x<<nl;
        // cout<<r1<<nl;
        if(r1<2)
        {
            // boat.position.z-=-0.1*sin((M_PI/180)*camera_rotation_angle);
            // boat.position.x-=-0.1*cos((M_PI/180)*camera_rotation_angle);
            cnt2=1;
            healthpoints-=20;
        }
    }
    for(int i=0;i<4;i++)
    {
        double r1=sqrt((barrel_gift[i].position.x-boat.position.x)*(barrel_gift[i].position.x-boat.position.x)+(barrel_gift[i].position.z-boat.position.z)*(barrel_gift[i].position.z-boat.position.z));
        if(r1<2)
        {
            healthpoints+=100;
            // timer t3;
            // t3.start();
            // while(t3.elapsedTime()<1)
            // {
            barrel_gift[i].position.x=-11212121;
            float r1 = -100 +((float)rand() / (float)RAND_MAX)*200;
            float r2 = -100 +((float)rand() / (float)RAND_MAX)*200;
            barrel[i]=Barrel(r1,r2,COLOR_white);
            // }
        }
    }
    for(int i=0;i<15;i++)
    {
        double r2=sqrt((enemy[i].position.x-boat.position.x)*(enemy[i].position.x-boat.position.x)+(enemy[i].position.z-boat.position.z)*(enemy[i].position.z-boat.position.z));
        double r3=sqrt((gift[i].position.x-boat.position.x)*(gift[i].position.x-boat.position.x)+(gift[i].position.z-boat.position.z)*(gift[i].position.z-boat.position.z));
        if(r3<3)
        {
            healthpoints+=rand()%103;
            gift[i].position.x=-102121;
        }
        if(r2<3)
        {
            enemies_killed++;
            healthpoints-=100;
            // enemy[i].position.x=-1000;
            float r1 = -100 +((float)rand() / (float)RAND_MAX)*200;
            float r2 = -100 +((float)rand() / (float)RAND_MAX)*200;
            // if(enemy[i].color=="WHITE")
            // cout<<enemy[i].color;
            if(flag_color!=-1 && i==flag_color)
            {
                if(boostflag==0)
                    time_boostflag=tt.elapsedTime();
                boostflag=1;   
            }
            if(enemies_killed%3!=0)
                enemy[i]=Enemy(r1,r2,COLOR_white);
            else
            {
                flag_color=i;
                enemy[i]=Enemy(r1,r2,COLOR_LBROWN);
            }
        }

    }
    for(int i=0;i<15;i++)
    {
        double r2=sqrt((enemy[i].position.x-fireball.position.x)*(enemy[i].position.x-fireball.position.x)+(enemy[i].position.z-fireball.position.z)*(enemy[i].position.z-fireball.position.z));
        if(r2<3)
        {
            enemies_killed++;
            healthpoints+=100;
            // enemy[i].position.x=-1000;
            fireball.position.x=-100000;
            float r1 = -100 +((float)rand() / (float)RAND_MAX)*150;
            float r2 = -100 +((float)rand() / (float)RAND_MAX)*150;
            // enemy[i]=Enemy(r1,r2,COLOR_white);
            if(flag_color!=-1 && i==flag_color)
            {
                if(boostflag==0)
                    time_boostflag=tt.elapsedTime();
                boostflag=1;   
            }
            gift[i]=Gift(enemy[i].position.x,enemy[i].position.z,COLOR_purple);
            if(enemies_killed%3!=0)
                enemy[i]=Enemy(r1,r2,COLOR_white);
            else
            {
                // if(boostflag==0)
                    // time_boostflag=tt.elapsedTime();
                // boostflag=1;
                flag_color=i;
                enemy[i]=Enemy(r1,r2,COLOR_LBROWN);
            }
        }

    }
    char buffer1[1234];
    char buffer2[1234];
    char buffer3[1234];
    char buffer4[1234];
    string strb;
    strb="health Points : ";
    sprintf(buffer1,"%d",healthpoints);
    strb+=buffer1;

    int val=0;
    if(tt.elapsedTime()%15==0 && tt.elapsedTime()!=0)
    {
        boat.position.z-=-0.2*sin((M_PI/180)*camera_rotation_angle);
        boat.position.x-=-0.2*cos((M_PI/180)*camera_rotation_angle);
        val=1;
    }
    sprintf(buffer2,"%d",val);
    strb+=" Wind status: ";
    strb+=buffer2;
    sprintf(buffer3,"%d",enemies_killed);
    strb+=" Enemies killed: ";
    strb+=buffer3;

    sprintf(buffer4,"%d",level);
    strb+=" Level: ";
    strb+=buffer4;
    if(enemies_killed!=0 && enemies_killed%5==0)
        level++;
    char outstring[1234];
    int j=0;
    for(j=0;j<strb.length();j++)
        outstring[j]=strb[j];
    outstring[j]='\0';

    glfwSetWindowTitle(window,outstring);
    // cout<<cnt<<nl;
    // cout<<boat.position.x<<"\n";
    fireball.tick(camera_rotation_angle);
    // if(fireball.position)

    double r3=sqrt((boat.position.x-fireball.position.x)*(boat.position.x-fireball.position.x)+(boat.position.z-fireball.position.z)*(boat.position.z-fireball.position.z));
    if(r3>15)
        fireball.position.x=-1000000;
    for(int i=0;i<15;i++)
    {
        gift[i].tick();
        enemy[i].tick();
    }
}
void initGL(GLFWwindow *window, int width, int height) 
{
    int x1=0,y1=0;
    boat=Ball(x1,y1,COLOR_CRIMSON);
    sea=Sea(x1,y1,COLOR_LBLUE);
    fireball=Fireball(-10000000,0,COLOR_BROWN);
    for(int i=0;i<15;i++)
    {
        float r1 = -100 +((float)rand() / (float)RAND_MAX)*200;
        float r2 = -100 +((float)rand() / (float)RAND_MAX)*200;
        enemy[i]=Enemy(r1,r2,COLOR_white);
        gift[i]=Gift(-100000,r2,COLOR_purple);
    }
    for(int i=0;i<4;i++)
    {
        float r1 = -100 + ((float)rand() / (float)RAND_MAX)*200;
        float r2 = -100 + ((float)rand() / (float)RAND_MAX)*200;
        barrel[i]=Barrel(r1,r2,COLOR_white);
        barrel_gift[i]=Barrel_gift(r1-1,r2,COLOR_pila);
    }
    int no_blocks=0;
    while(no_blocks<123)
    {
        float r1 = -100 +((float)rand() / (float)RAND_MAX)*200;
        float r2 = -100 +((float)rand() / (float)RAND_MAX)*200;
        int rndom=rand()%3;
        if(rndom==0)
            blocks[no_blocks] = Block(r1,r2,COLOR_BLACK);
        if(rndom==1)
            blocks[no_blocks] = Block(r1,r2,COLOR_CRIMSON);
        if(rndom==2)
            blocks[no_blocks] = Block(r1,r2,COLOR_YELLOW);
        no_blocks++;
    }
    
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) 
{
    flag_color=-1;
    tt.start();
    numballs=12;
    level=1;

    healthpoints=40000;
    // tt.start();
    srand(time(0));
    int width  = 1200;
    int height = 1200;
    lives=7;
    score=0;

    window = initGLFW(width, height);

    initGL (window, width, height);
     audio_init();

    /* Draw in loop */ 
    while(!glfwWindowShouldClose(window)) 
    {
         audio_play();
        // Process timers

        if(t60.processTick()) 
        {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }
        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}


void view_change()
{
    if(view!=3)
        view=view+1;
    else
    {
        helx=boat.position.x+zoom*cos((M_PI/180)*camera_rotation_angle);
        hely=4;
        helz=boat.position.x+zoom*sin((M_PI/180)*camera_rotation_angle);
        hx=boat.position.x;
        hy=boat.position.y;
        hz=boat.position.z;
        view=view+1;
    }
}
void fire_ball()
{
    fireball.position.x=boat.position.x;
    fireball.position.z=boat.position.z;
}
void reset_screen() 
{
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

