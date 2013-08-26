#include "Timer.h"
#include <GL/freeglut.h>
#include "Texture.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>
#include <avbin.h>
#include "MovieState.h"
#include <sstream>
#include <memory>

#include <AL/alut.h>
using namespace std;


int resWidth = 1024;
int resHeight = 768;

Timer timer;

Texture panel;

//mouse cursor in pixel coordinates on screen
int screenCursorX=0;
int screenCursorY=0;


float translationRate = 100;

float translationX=-625,translationY=-238;

std::shared_ptr<MovieState> gameOver;




///\todo separate out the loading from the playsound
void playSound(const std::string& sound){

	ALuint buffer = alutCreateBufferFromFile(sound.c_str());

	if(!buffer)throw std::runtime_error((std::string("could not find sound file ") + sound));
	ALuint source;
	alGenSources(1, &source);

	alSourcei(source, AL_BUFFER,buffer);

	alSourcePlay(source);

}



void savePng(const char* filename, const unsigned char* pixels, unsigned int width, unsigned int height, unsigned int channels)
{

    std::cerr<<"Wriring image with "<<width<<" "<<height<<" "<<channels<<" to "<<filename<<std::endl;
    stbi_write_png(filename, width, height, channels, pixels, width*channels);

}


void drawFrame()
{

    int threeQuartersScreenX = (resWidth>>1) + (resWidth>>2); //
    //std::cout<<threeQuartersScreenX<<std::endl;
    int quarterScreenX = resWidth>>2;
    //std::cout<<quarterScreenX<<std::endl;
    int threeQuartersScreenY = (resHeight>>1) + (resHeight>>2); //
    int quarterScreenY = resHeight>>2;



    translationX += screenCursorX>threeQuartersScreenX ? -.50
    : (screenCursorX < quarterScreenX? .50 : 0.0);

    //std::cout<<"cursorY quarter 3quarter "<<screenCursorY<<" "<<quarterScreenY<<" "<<threeQuartersScreenY<<std::endl;

    translationY += screenCursorY>threeQuartersScreenY ? .50
    : (screenCursorY < quarterScreenY? -.50 : 0.0);

    translationX = -std::max<float>(-translationX, 0.0);
    translationX = -std::min<float>(-translationX, panel.w-(800));

    translationY = std::min<float>(translationY, 0.0);
    translationY = std::max<float>(translationY, -(panel.h - 700) );

    //std::cout<<"txy "<<translationX<<" "<<translationY<<std::endl;

    glClear(GL_COLOR_BUFFER_BIT);

/*
    //std::cout<<"New frame"<<std::endl;
    gameOver->update();///\todo if no update crash
    //std::cout<<"Done updating"<<std::endl;
    if(gameOver->playing){///\todo crash without
       // std::cout<<"playing"<<std::endl;
        gameOver->texture.bind();
        //std::cout<<"Bound texture"<<std::endl;
        glBegin(GL_QUADS);

            glTexCoord2f(1.0,0.0);
            glVertex3f(1.0,1.0,0.0);

            glTexCoord2f(0.0,0.0);
            glVertex3f(-1.0,1.0,0.0);

            glTexCoord2f(0.0,1.0);
            glVertex3f(-1.0,-1.0,0.0);

            glTexCoord2f(1.0,1.0);
            glVertex3f(1.0,-1.0,0.0);

        glEnd();
     //   std::cout<<"Done with draw"<<std::endl;
}
*/


    panel.bind();

    glPushMatrix();
    glTranslatef(translationX,translationY,0.0);

    glBegin(GL_QUADS);

/*
            glTexCoord2f(1.0,0.0);
            glVertex3f(1.0,1.0,0.0);

            glTexCoord2f(0.0,0.0);
            glVertex3f(-1.0,1.0,0.0);

            glTexCoord2f(0.0,1.0);
            glVertex3f(-1.0,-1.0,0.0);

            glTexCoord2f(1.0,1.0);
            glVertex3f(1.0,-1.0,0.0);
*/



            glTexCoord2f(1.0,0.0);
            glVertex3f(panel.w,panel.h,0.0);

            glTexCoord2f(0.0,0.0);
            glVertex3f(0,panel.h,0.0);

            glTexCoord2f(0.0,1.0);
            glVertex3f(0,0,0.0);

            glTexCoord2f(1.0,1.0);
            glVertex3f(panel.w,0,0.0);



    glEnd();

    glPopMatrix();

    glutSwapBuffers();
   // std::cout<<"Done totally"<<std::endl;
}


//we don't allow the user to reshape the screen, for simplicity's sake here
void reshape(int w, int h)
{



}


void init()
{

    if (avbin_init())
    {
        printf("Fatal: Couldn't initialize AVbin");
        exit(-1);
    }

    panel = Texture("panel.jpg");

    gameOver.reset(new MovieState("WinGame.mp4"));

    gameOver->begin();

    gameOver->update();///\todo if no update crash



    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glClearColor(0.0f,0.0f,0.0f,1.0f);

    glEnable(GL_TEXTURE_2D);  //enable fixed function texturing


    glViewport(0,0,resWidth, resHeight);

    gluOrtho2D(0,resWidth*.75,0,resHeight*.75);

    glutWarpPointer(resWidth / 2, resHeight / 2);


}


void setCursor(int cursorX, int cursorY)
{
   // std::cout<<"Cursor "<<cursorX<<" "<<cursorY<<std::endl;


  screenCursorX = cursorX;
    screenCursorY = cursorY;



}


void mouseMotionButtonDown(int cursorX, int cursorY)
{

    setCursor(cursorX, cursorY);

}

void mouseMotion(int cursorX, int cursorY)
{

    setCursor(cursorX, cursorY);

}



void mouseButtonHandler(int button, int state, int x, int y)
{

    if(state==GLUT_UP)
    {



    }
    else if(state==GLUT_DOWN)
    {


    }

}



void keyFunc(unsigned char key, int x, int y)
{
    switch(key)
    {

    case 27:
    {
        exit(0);
        break;
    }
    default:
        break;
    }

}



int main(int argc,char** argv)
{
    try
    {
        glutInit(&argc, argv);

        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

        glutInitWindowSize(resWidth, resHeight);
        glutInitWindowPosition(0,0);

        glutCreateWindow("Everyone Panic!");

        alutInit(&argc, argv); //init alut

        init();


        glutDisplayFunc(drawFrame);
        glutReshapeFunc(reshape);
        glutMotionFunc(mouseMotionButtonDown);


        glutKeyboardFunc(keyFunc);

        glutMouseFunc(mouseButtonHandler);
        glutPassiveMotionFunc(mouseMotion);

        glutIdleFunc(glutPostRedisplay);

        glutMainLoop();

        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr<<"EXCEPTION: "<<e.what()<<std::endl;
    }

}

