/*
Author: Ruben Quiros
Class: ECE 4122
Last Date Modified: 11/28/20

Description:
    This file used OpenGL and GLUT to draw a Gorgia Tech themed "Monopoly board".
    In this version, everything is stationary. However, the user can rotate the scene
    5 degrees by pressing "r" on their keyboard.

SPECIAL NOTE:
    Credit goes to Dr. Hurley for the following functions: init(), reshape(), keyboard(), and
    main(). These functions were inspired by his in-class examples. There are other snippets
    of code for coloring, lighting, buffering, and depth perception that were also taken from
    his examples from lectures. Thank you!
*/

#include <GL/glut.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "ECE_Bitmap.h" // for bitmaps/textures
#include <string>

using namespace std;

// Some Global Params
float angle = 0.0;              // angle of the camera (0.0 == south of maze)
float PI = 3.141592653589793;   // PI for angle calculations
int screenWidth = 500;
int screenHeight = 500;

GLuint texture[1];  // for eyes of ghost and Pac Man
BMP inBitmap;       // for eyes of ghost and Pac Man

// color and material properties
float colorWhite[4] = { 0.60, 0.60, 0.60, 1.0f };
float colorRed[4] = { 1.0, 0.0, 0.0, 1.0f };
float colorCyan[4] = { 0.0, 1.0, 1.0, 1.0f };
float colorPink[4] = { 1.0, 0.7529, 0.7861, 1.0f };
float colorOrange[4] = { 1.0, 0.4921, 0.0, 1.0f };
float colorBlue[4] = { 0.0, 0.0, 1.0, 1.0f };
float colorYellow[4] = { 1.0, 0.0, 0.0, 1.0f };
float colorGreen[4] = { 0.0, 1.0, 0.0, 1.0f };

GLfloat shininess[] = { 5 };

string screenMsg = "You have $1,500\0";

/////////////////////////////////////////////////////////////////////////////////////////////////
// Used to initialize the background and overall scene
/////////////////////////////////////////////////////////////////////////////////////////////////
void init(void){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // glColor3f(0.0,1.0,0.0);
    // glutSolidSphere(0.5,20,20);

    // THIS SECTION IS FOR THE LIGHTING AND MATERIAL PROPERTIES
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);

    GLfloat lightPosition[] = {0.65, 0.65, 0.3, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    GLfloat light_ambient[] = { 0.6, 0.6, 0.6, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    // GLfloat light_position[] = { 0.65, 0.65, 0.65, 0.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    // glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, colorWhite);

    // THIS SECTION IS FOR THE BOARD TEXTURE
    inBitmap.read("boardTexture.bmp");          // read in bmp/texture files
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);      // byte alignment
    glGenTextures(1, texture);                  // initialize the texture
    glBindTexture(GL_TEXTURE_2D, texture[0]);   // bind the texture

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //scale linearly when image smalled than texture

    // determine properties, size, and format of the texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, inBitmap.bmp_info_header.width, inBitmap.bmp_info_header.height, 0,
        GL_BGR_EXT, GL_UNSIGNED_BYTE, &inBitmap.data[0]);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glBindTexture(GL_TEXTURE_2D, 0);   // unbind the texture

    // glEnable(GL_TEXTURE_2D);
    //     glBindTexture(GL_TEXTURE_2D, texture[0]);

    //     glBegin(GL_QUADS);
    //         glTexCoord2f(1, 0);
    //         glVertex3f(0.0f, 0.0f, 0.0f);
    //         glTexCoord2f(0, 0);
    //         glVertex3f(1.3f, 0.0f, 0.0f);
    //         glTexCoord2f(0, 1);
    //         glVertex3f(1.3f, 0.0f, 1.3f);
    //         glTexCoord2f(1, 1);
    //         glVertex3f(0.0f, 0.0f, 1.3f);
    //     glEnd();

    // glDisable(GL_TEXTURE_2D);

    // // SET UP PROPERTIES FOR 3D OBJECTS
    // GLUquadricObj *quadObj;
    // quadObj = gluNewQuadric();
    // gluQuadricDrawStyle(quadObj, GLU_FILL);
    // gluQuadricTexture(quadObj, GL_TRUE);
    // gluQuadricNormals(quadObj, GLU_SMOOTH);

}   // end of init()

/////////////////////////////////////////////////////////////////////////////////////////////////
// Used to draw a green house on a property
/////////////////////////////////////////////////////////////////////////////////////////////////
void drawHouse(float xx, float zz){ // instead it will pass the board position (0-39)
    glColor3f(0.0, 1.0, 0.0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorGreen);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorGreen);

    GLUquadricObj *quadObj;
    quadObj = gluNewQuadric();

    glPushMatrix();
    // glLoadIdentity(); /////////////////////////////// THIS IS THE PROBLEM
    // glTranslatef(0.65,0.0,0.65);
    // glutSolidSphere(0.5, 20, 20);
    // gluCylinder(quadObj, 0.5, 0.5, 0.5, 20, 20);
    glTranslatef(xx,0.0,zz);

    // glScalef(1.0, 1.0, 3000.0);
    // glTranslatef(xx,0.0,zz);

    // front and back face
    glBegin(GL_POLYGON);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.03, 0.0);
        glVertex3f(-0.005, 0.03, 0.0);
        glVertex3f(0.015, 0.045, 0.0);
        glVertex3f(0.035, 0.03, 0.0);
        glVertex3f(0.03, 0.03, 0.0);
        glVertex3f(0.03, 0.0, 0.0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3f(0.0, 0.0, 0.03);
        glVertex3f(0.0, 0.03, 0.03);
        glVertex3f(-0.005, 0.03, 0.03);
        glVertex3f(0.015, 0.045, 0.03);
        glVertex3f(0.035, 0.03, 0.03);
        glVertex3f(0.03, 0.03, 0.03);
        glVertex3f(0.03, 0.0, 0.03);
    glEnd();

    // floor
    glBegin(GL_QUADS);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.03, 0.0, 0.0);
        glVertex3f(0.03, 0.0, 0.03);
        glVertex3f(0.0, 0.0, 0.03);
    glEnd();

    // walls
    glBegin(GL_QUADS);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.03, 0.0);
        glVertex3f(0.0, 0.03, 0.03);
        glVertex3f(0.0, 0.0, 0.03);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(0.03, 0.0, 0.0);
        glVertex3f(0.03, 0.03, 0.0);
        glVertex3f(0.03, 0.03, 0.03);
        glVertex3f(0.03, 0.0, 0.03);
    glEnd();

    // roof
    glBegin(GL_QUADS);
        glVertex3f(-0.005, 0.03, 0.0);
        glVertex3f(-0.005, 0.03, 0.03);
        glVertex3f(0.015, 0.045, 0.03);
        glVertex3f(0.015, 0.045, 0.0);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(0.035, 0.03, 0.0);
        glVertex3f(0.035, 0.03, 0.03);
        glVertex3f(0.015, 0.045, 0.03);
        glVertex3f(0.015, 0.045, 0.0);
    glEnd();

    glPopMatrix();
}   // end of drawHouse()

/////////////////////////////////////////////////////////////////////////////////////////////////
// Used to draw a red hotel on a property
/////////////////////////////////////////////////////////////////////////////////////////////////
void drawHotel(float xx, float zz){ // instead it will pass the board position (0-39)
    glColor3f(1.0, 0.0, 0.0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorRed);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorRed);

    GLUquadricObj *quadObj;
    quadObj = gluNewQuadric();

    glPushMatrix();
    // glLoadIdentity(); /////////////////////////////// THIS IS THE PROBLEM
    // glTranslatef(0.65,0.0,0.65);
    // glutSolidSphere(0.5, 20, 20);
    // gluCylinder(quadObj, 0.5, 0.5, 0.5, 20, 20);
    glTranslatef(xx,0.0,zz);

    // glScalef(1.0, 1.0, 3000.0);
    // glTranslatef(xx,0.0,zz);

    // front and back face
    glBegin(GL_POLYGON);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.03, 0.0);
        glVertex3f(-0.005, 0.03, 0.0);
        glVertex3f(0.015, 0.045, 0.0);
        glVertex3f(0.035, 0.03, 0.0);
        glVertex3f(0.03, 0.03, 0.0);
        glVertex3f(0.03, 0.0, 0.0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3f(0.0, 0.0, 0.06);
        glVertex3f(0.0, 0.03, 0.06);
        glVertex3f(-0.005, 0.03, 0.06);
        glVertex3f(0.015, 0.045, 0.06);
        glVertex3f(0.035, 0.03, 0.06);
        glVertex3f(0.03, 0.03, 0.06);
        glVertex3f(0.03, 0.0, 0.06);
    glEnd();

    // floor
    glBegin(GL_QUADS);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.03, 0.0, 0.0);
        glVertex3f(0.03, 0.0, 0.06);
        glVertex3f(0.0, 0.0, 0.06);
    glEnd();

    // walls
    glBegin(GL_QUADS);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.03, 0.0);
        glVertex3f(0.0, 0.03, 0.06);
        glVertex3f(0.0, 0.0, 0.06);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(0.03, 0.0, 0.0);
        glVertex3f(0.03, 0.03, 0.0);
        glVertex3f(0.03, 0.03, 0.06);
        glVertex3f(0.03, 0.0, 0.06);
    glEnd();

    // roof
    glBegin(GL_QUADS);
        glVertex3f(-0.005, 0.03, 0.0);
        glVertex3f(-0.005, 0.03, 0.06);
        glVertex3f(0.015, 0.045, 0.06);
        glVertex3f(0.015, 0.045, 0.0);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(0.035, 0.03, 0.0);
        glVertex3f(0.035, 0.03, 0.06);
        glVertex3f(0.015, 0.045, 0.06);
        glVertex3f(0.015, 0.045, 0.0);
    glEnd();

    glPopMatrix();
}   // end of drawHouse()

/////////////////////////////////////////////////////////////////////////////////////////////////
// Used to display the current message on the screen
/////////////////////////////////////////////////////////////////////////////////////////////////
void displayMsg(string& message){
    screenMsg = message;    // update the global message
    glMatrixMode(GL_PROJECTION);

    glPushMatrix();
        glLoadIdentity();
        glOrtho(0, screenWidth, 0, screenHeight, 0, 10);    // display in ortho/flat 2D space
        glMatrixMode(GL_MODELVIEW);

        glPushMatrix();
            glLoadIdentity();
            glColor3f(1.0, 1.0, 1.0);   // white text
            glRasterPos2i(0.45*screenWidth, 0.85*screenHeight); // this is approximately top/center of the screen

            for(const char character : message){
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, character);   // loop through all chars in message
            }
        glPopMatrix();

        glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
}   // end of displayMsg()

/////////////////////////////////////////////////////////////////////////////////////////////////
// Used to set up the lighting and material properties
/////////////////////////////////////////////////////////////////////////////////////////////////
void lightAndMaterials(void){
    //
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Used to draw the entire scene; this will get recalled when the scene or window changes
/////////////////////////////////////////////////////////////////////////////////////////////////
void display(void){
    // enable coloring and depth
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // enable default lighting and material properties
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);

    // glLoadIdentity();
    glPushMatrix(); // just double check that we start at the origin

        // for consistency of the view type
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        displayMsg(screenMsg);  // display the current message on the screen
 
        // set the camera position, where it is looking, and its up vector
        // Note: the angle is incremented by 5 degrees to rotate the camera
        // around the center of the maze
        gluLookAt(1.25*sin(angle*PI / 180.0) + 0.65, 1.25, 1.25*cos(angle*PI / 180.0) + 0.65,
                0.65, 0.0, 0.65,    // where the camera is looking (center of maze)
                0.0, 1.0, 0.0);     // up vector

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glBegin(GL_QUADS);
            glTexCoord2f(1, 0);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glTexCoord2f(0, 0);
            glVertex3f(1.3f, 0.0f, 0.0f);
            glTexCoord2f(0, 1);
            glVertex3f(1.3f, 0.0f, 1.3f);
            glTexCoord2f(1, 1);
            glVertex3f(0.0f, 0.0f, 1.3f);
        glEnd();
        // glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);

        // drawHouse(0.17,0.17);   // the corner spaces are 0.17 by 0.17 units
        drawHotel(0.17,0.17);

    glPopMatrix();

    glutSwapBuffers();
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Used when the window is reshaped
/////////////////////////////////////////////////////////////////////////////////////////////////
void reshape(int w, int h){
    // first update the screen width and height variables
    screenWidth = w;
    screenHeight = h;

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);   // adjust width and height
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // set the camera position, where it is looking, and its up vector
    // Note: the angle is incremented by 5 degrees to rotate the camera
    // around the center of the maze
    gluLookAt(1.25*sin(angle*PI / 180.0) + 0.65, 1.25, 1.25*cos(angle*PI / 180.0) + 0.65,
            0.65, 0.0, 0.65,    // where the camera is looking (center of maze)
            0.0, 1.0, 0.0);     // up vector
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Used to detect keyboard inputs; used here to rotate the camera around the maze
/////////////////////////////////////////////////////////////////////////////////////////////////
void keyboard(unsigned char key, int x, int y){
    bool success = true;
    switch (key) {
        case 'b':
        case 'B':
            // attempt to buy a property
            // insert function sending 'b' to server
            // server should return success or fail
            if(success){
                // print success of purchase to the screen
            }
            else{
                // print failure of purchase to the screen
            }
            break;
        case 's':
        case 'S':
            // send message that you want to sell a property to the bank
            // insert function sending 's' to server
            // print success of sale to the screen

            // if there are any hotels/houses, they should recieve their worth back
            // also, houses and hotels should disappear

            // board object should be updated here before being redrawn
            // because houses/hotels might disappear
            glutPostRedisplay();
            break;
        case 'h':
        case 'H':
            // send message that you want to buy a house
            // technically a player can buy multiple houses in a row

            // insert function sending 'h' to server
            // server should return success or fail
            if(success){
                // print success of purchase to the screen
            }
            else{
                // print failure of purchase to the screen
            }        // board object should be updated here before being redrawn
            glutPostRedisplay();
            break;
        case 'j':
        case 'J':
            // send message that you want to buy a hotel
            // insert function sending 'j' to server
            // server should return success or fail
            if(success){            // success if they have enough money AND they have 4 houses
                // print success of purchase to the screen
            }
            else{
                // print failure of purchase to the screen
            }        // board object should be updated here before being redrawn
            glutPostRedisplay();
            break;
        case 'n':
        case 'N':
            // send message that your turn is over
            // insert function sending n'' to server
            // board object should be updated here before being redrawn
            glutPostRedisplay();
            break;
        case 'r':
        case 'R':
            // change camera angle
            angle += 5;
            if(angle == 360){
                angle = 0;          // reset to zero after complete circle
            }
            glutPostRedisplay();    // redraw scene after angle change and/or window resize
            break;
        default:
            break;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Main function - this is where everything is inialized/called
/////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv){
    glutInit(&argc, argv);

    // enable depth, doubles, and RGBA mode
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0, 0);   // top left
    glutInitWindowSize(screenWidth, screenHeight);   // initial window dimensions
    glutCreateWindow("Buzzopoly - ECE 4122 Final Project"); // name of window

    init();                     // initialize scene properties
    glutDisplayFunc(display);   // display the scene
    glutReshapeFunc(reshape);   // reshape the window
    glutKeyboardFunc(keyboard); // read keyboard input
    glutMainLoop();             // loop through main again
    return 0;
}