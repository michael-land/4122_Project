/*
Author: Ruben Quiros
Class: ECE 4122
Last Date Modified: 11/21/20

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
#include <render/Bitmap.h> // for bitmaps/textures

// Some Global Params
GLuint texture[1];  // for eyes of ghost and Pac Man
BMP inBitmap;       // for eyes of ghost and Pac Man
// color and material properties
float colorWhite[4] = { 0.60, 0.60, 0.60, 1.0f };
float angle = 0.0;              // angle of the camera (0.0 == south of maze)
float colorRed[4] = { 1.0, 0.0, 0.0, 1.0f };
float colorCyan[4] = { 0.0, 1.0, 1.0, 1.0f };
float colorPink[4] = { 1.0, 0.7529, 0.7861, 1.0f };
float colorOrange[4] = { 1.0, 0.4921, 0.0, 1.0f };
float colorBlue[4] = { 0.0, 0.0, 1.0, 1.0f };
float colorYellow[4] = { 1.0, 0.0, 0.0, 1.0f };

GLfloat shininess[1] = { 5 };

float PI = 3.141592653589793;   // PI for angle calculations


/////////////////////////////////////////////////////////////////////////////////////////////////
// Used to initialize the background and overall scene
/////////////////////////////////////////////////////////////////////////////////////////////////
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glDepthFunc(GL_LESS);

    // THIS SECTION IS FOR THE LIGHTING AND MATERIAL PROPERTIES
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);

    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, colorWhite);

    // THIS SECTION IS FOR THE BOARD TEXTURE
    inBitmap.read("/home/jstanhope3/Dropbox/school_notes/ece4122/4122_Project/src/boardTexture.bmp");          // read in bmp/texture files
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);      // byte alignment
    glGenTextures(1, texture);                  // initialize the texture
    glBindTexture(GL_TEXTURE_2D, texture[0]);   // bind the texture

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //scale linearly when image smalled than texture

    // determine properties, size, and format of the texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, inBitmap.bmp_info_header.width, inBitmap.bmp_info_header.height, 0,
        GL_BGR_EXT, GL_UNSIGNED_BYTE, &inBitmap.data[0]);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glEnable(GL_TEXTURE_2D);    // enable the texture

    // SET UP PROPERTIES FOR 3D OBJECTS
    GLUquadricObj *quadObj;
    quadObj = gluNewQuadric();
    gluQuadricDrawStyle(quadObj, GLU_FILL);
    gluQuadricTexture(quadObj, GL_TRUE);
    gluQuadricNormals(quadObj, GLU_SMOOTH);

}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Used to draw the entire scene; this will get recalled when the scene or window changes
/////////////////////////////////////////////////////////////////////////////////////////////////
void display() {
    // enable coloring and depth
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); // ???

    glPushMatrix(); // just double check that we start at the origin

        // for consistency of the view type
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        // set the camera position, where it is looking, and its up vector
        // Note: the angle is incremented by 5 degrees to rotate the camera
        // around the center of the maze
        gluLookAt(1.25*sin(angle*PI / 180.0) + 0.65, 1.25, 1.25*cos(angle*PI / 180.0) + 0.65,
                0.65, 0.0, 0.65,      // where the camera is looking (center of maze)
                0.0, 1.0, 0.0);     // up vector

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

    glPopMatrix();

    glutSwapBuffers();
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Used when the window is reshaped
/////////////////////////////////////////////////////////////////////////////////////////////////
void reshape(int w, int h){
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);   // adjust width and height
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // used to set the position, where the camera is looking, and its up vector
    gluLookAt(4.0*sin(angle*PI / 180.0) + 0.65, 2.5, 4.0*cos(angle*PI / 180.0) + 0.65,
            0.65, 0.0, 0.65,      // where the camera is looking (center of maze)
            0.0, 1.0, 0.0);     // up vector
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Used to detect keyboard inputs; used here to rotate the camera around the maze
/////////////////////////////////////////////////////////////////////////////////////////////////
void keyboard(unsigned char key, int x, int y){
    switch (key) {
    case 'r':
        // change camera angle
        angle += 5;
        if(angle == 360){
            angle = 0;          // reset to zero after complete circle
        }
        glutPostRedisplay();    // redraw scene after angle change and/or window resize
        break;
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
int setup(int argc, char** argv){
    glutInit(&argc, argv);

    // enable depth, doubles, and RGBA mode
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0, 0);   // top left
    glutInitWindowSize(500, 500);   // initial window dimensions
    glutCreateWindow("Buzzopoly - ECE 4122 Final Project"); // name of window

    init();                     // initialize scene properties
    glutDisplayFunc(display);   // display the scene
    glutReshapeFunc(reshape);   // reshape the window
    glutKeyboardFunc(keyboard); // read keyboard input
    glutMainLoop();             // loop through main again
    return 0;
}
