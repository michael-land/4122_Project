/*
Author: Ruben Quiros
Additional Author: Zhou Lu
Class: ECE 4122
Last Date Modified: 12/1/20

Description:
    This file used OpenGL and GLUT to draw a Gorgia Tech themed "Monopoly board".
    In this version, everything is stationary. However, the user can rotate the scene
    5 degrees by pressing "t" on their keyboard.

SPECIAL NOTE:
    Credit goes to Dr. Hurley for the following functions: init(), reshape(), keyboard(), and
    main(). These functions were inspired by his in-class examples. There are other snippets
    of code for coloring, lighting, buffering, and depth perception that were also taken from
    his examples from lectures. Thank you!
    Credit goes to Anton Gerdelan of antongerdelan.net for the code to parse .obj files
*/
#include <gamerules/Board.h>
#include <GL/glut.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Bitmap.h" // for bitmaps/textures
#include <string>
#include <gamerules/Property.h>
#include <multiplayer/MultiplayerObjects.h>

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
float colorYellow[4] = { 1.0, 1.0, 0.0, 1.0f };
float colorGreen[4] = { 0.0, 1.0, 0.0, 1.0f };

GLfloat shininess[] = { 5 };

string screenMsg = "You have $1,500\0";

namespace GLRenderShared
{
    Board* board;  //pointer to the board that is used for rendering
    client* cli;
    std::string username;
}

//Board* boardPointer = GLRenderShared::board;

/////////////////////////////////////////////////////////////////////////////////////////////////
// Used to initialize the background and overall scene
/////////////////////////////////////////////////////////////////////////////////////////////////
void init(void){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glDepthFunc(GL_LESS);

    // THIS SECTION IS FOR THE LIGHTING AND MATERIAL PROPERTIES
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);

    GLfloat lightPosition[] = {0.65, 0.65, 0.3, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    GLfloat light_ambient[] = { 0.6, 0.6, 0.6, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, colorWhite);
    std::cout << "attempting to set board texture" << std::endl;

    // THIS SECTION IS FOR THE BOARD TEXTURE
    inBitmap.read("/home/jstanhope3/Dropbox/school_notes/ece4122/4122_Project/textures/offwhiteboardTexture.bmp");          // read in bmp/texture files
    std::cout << "after board texture" << std::endl;
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
}   // end of init()

/////////////////////////////////////////////////////////////////////////////////////////////////
// Used to draw a green house on a property
/////////////////////////////////////////////////////////////////////////////////////////////////
void drawHouse(int boardSpace, int numHouses){
    unsigned int rotations = boardSpace / 10;   // int will truncate
    unsigned int sideSpace = boardSpace % 10;   // offset for the space on the side

    glColor3f(0.0, 1.0, 0.0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorGreen);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorGreen);

    glPushMatrix();

        // this section rotates the required amount of times
        if(rotations > 0){
            for(int ii = 0; ii < rotations; ++ii){
                glTranslatef(1.04, 0.0, 0.0);
                glRotatef(-90, 0.0, 1.0, 0.0);
            }
        }

        for(int offset = 0; offset < numHouses; ++offset){
            glPushMatrix();
            glTranslatef(((float)(sideSpace - 1))*0.083 + 0.144 + (((float)offset)*0.022), 0.0, 0.144 - 0.03);

            // front and back face
            glBegin(GL_POLYGON);
                glVertex3f(0.0, 0.0, 0.0);
                glVertex3f(0.0, 0.02, 0.0);
                glVertex3f(-0.0025, 0.02, 0.0);
                glVertex3f(0.0075, 0.03, 0.0);
                glVertex3f(0.0175, 0.02, 0.0);
                glVertex3f(0.015, 0.02, 0.0);
                glVertex3f(0.015, 0.0, 0.0);
            glEnd();
            glBegin(GL_POLYGON);
                glVertex3f(0.0, 0.0, 0.03);
                glVertex3f(0.0, 0.02, 0.03);
                glVertex3f(-0.0025, 0.02, 0.03);
                glVertex3f(0.0075, 0.03, 0.03);
                glVertex3f(0.0175, 0.02, 0.03);
                glVertex3f(0.015, 0.02, 0.03);
                glVertex3f(0.015, 0.0, 0.03);
            glEnd();

            // floor
            glBegin(GL_QUADS);
                glVertex3f(0.0, 0.0, 0.0);
                glVertex3f(0.015, 0.0, 0.0);
                glVertex3f(0.015, 0.0, 0.03);
                glVertex3f(0.0, 0.0, 0.03);
            glEnd();

            // walls
            glBegin(GL_QUADS);
                glVertex3f(0.0, 0.0, 0.0);
                glVertex3f(0.0, 0.02, 0.0);
                glVertex3f(0.0, 0.02, 0.03);
                glVertex3f(0.0, 0.0, 0.03);
            glEnd();
            glBegin(GL_QUADS);
                glVertex3f(0.015, 0.0, 0.0);
                glVertex3f(0.015, 0.02, 0.0);
                glVertex3f(0.015, 0.02, 0.03);
                glVertex3f(0.015, 0.0, 0.03);
            glEnd();

            // roof
            glBegin(GL_QUADS);
                glVertex3f(-0.0025, 0.02, 0.0);
                glVertex3f(-0.0025, 0.02, 0.03);
                glVertex3f(0.0075, 0.03, 0.03);
                glVertex3f(0.0075, 0.03, 0.0);
            glEnd();
            glBegin(GL_QUADS);
                glVertex3f(0.0175, 0.02, 0.0);
                glVertex3f(0.0175, 0.02, 0.03);
                glVertex3f(0.0075, 0.03, 0.03);
                glVertex3f(0.0075, 0.03, 0.0);
            glEnd();

            glPopMatrix();
        }   // end of for loop

    glPopMatrix();
}   // end of drawHouse()

/////////////////////////////////////////////////////////////////////////////////////////////////
// Used to draw a red hotel on a property
/////////////////////////////////////////////////////////////////////////////////////////////////
void drawHotel(int boardSpace){
    unsigned int rotations = boardSpace / 10;   // int will truncate
    unsigned int sideSpace = boardSpace % 10;   // offset for the space on the side

    glColor3f(1.0, 0.0, 0.0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorRed);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorRed);

    glPushMatrix();

        // this section rotates the required amount of times
        if(rotations > 0){
            for(int ii = 0; ii < rotations; ++ii){
                glTranslatef(1.04, 0.0, 0.0);
                glRotatef(-90, 0.0, 1.0, 0.0);
            }
        }

        // this larger section draws the hotel
        glPushMatrix();

        glTranslatef(((float)(sideSpace - 1))*0.083 + 0.144 + 0.0115, 0.0, 0.144);
        glRotatef(90, 0.0, 1.0, 0.0);

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
    glPopMatrix();
}   // end of drawHotel()

/////////////////////////////////////////////////////////////////////////////////////////////////
// Used to display the current message on the screen
/////////////////////////////////////////////////////////////////////////////////////////////////
void displayMsg(int playerMoney, int spacePrice, std::string& spaceName){
    std::string playerMsg = "You have $" + std::to_string(playerMoney);
    std::string spaceNameMsg = "You are visiting \"" + spaceName + "\"";
    std::string spacePriceMsg = "Cost of this space: $";

    if(spacePrice > 0){
        spacePriceMsg += std::to_string(spacePrice);
    }
    else{
        spacePriceMsg += "N/A - cannot own this space";
    }

    std::string fullMsg[] = {playerMsg, spaceNameMsg, spacePriceMsg};

    glMatrixMode(GL_PROJECTION);

    glPushMatrix();
        glLoadIdentity();
        glOrtho(0, screenWidth, 0, screenHeight, 0, 10);    // display in ortho/flat 2D space
        glMatrixMode(GL_MODELVIEW);

        glPushMatrix();
            glLoadIdentity();
            glColor3f(1.0, 1.0, 1.0);   // white text
            float offset = 0.0;
            for(const std::string line : fullMsg){
                glRasterPos2i(0.45*screenWidth, 0.80*screenHeight - offset*screenHeight); // this is approximately top/center of the screen
                offset += 0.03;

                for(const char character : line){
                    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, character);   // loop through all chars in message
                }
            }
        glPopMatrix();

        glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
}   // end of displayMsg()

/////////////////////////////////////////////////////////////////////////////////////////////////
// Used to Get the board coordinates from the space ID.
/////////////////////////////////////////////////////////////////////////////////////////////////
// corners are .17 by .17
// others are .11 by .17
// X by Z
void spaceIDtoCoord(const int spaceID, float* x, float* z)
{
    const float corner = 0.144;
    const float space = 0.083;
    const float hc = corner/2;
    const float hs = space/2;
    if (spaceID == 0)
    {
        *x = hc;
        *z = hc;
    }
    else if (1 <= spaceID && spaceID <= 9)
    {
        *x = corner + hs + space * (spaceID - 1);
        *z = hc;
    }
    else if (spaceID == 10)
    {
        *x = corner + 9 * space + hc;
        *z = hc;
    }
    else if (11 <= spaceID && spaceID <= 19)
    {
        *x = corner + 9 * space + hc;
        *z = corner + hs + space * (spaceID % 10 - 1);
    }
    else if (spaceID == 20)
    {
        *x = corner + 9 * space + hc;
        *z = corner + 9 * space + hc;
    }
    else if (21 <= spaceID && spaceID <= 29)
    {
        *x = corner + hs + (9 - spaceID % 10) * space;
        *z = corner + 9 * space + hc;
    }
    else if (spaceID == 30)
    {
        *x = hc;
        *z = corner + 9 * space + hc;
    }
    else if (31 <= spaceID && spaceID <= 39)
    {
        *x = hc;
        *z = corner + hs + (9 - spaceID % 10) * space;
    }
}

////////////////////////////////////////////////////////////////////////////////
// draws a player as a cylinder
////////////////////////////////////////////////////////////////////////////////
void drawPlayerCylinder(float x, float z)
{
    GLUquadricObj *quadObj;
    quadObj = gluNewQuadric();

    glColor3f(colorCyan[0], colorCyan[1], colorCyan[2]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorCyan);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorCyan);

    //glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, colorPink);
    //glMaterialfv(GL_FRONT, GL_AMBIENT, colorPink);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, colorPink);
    // Draw the pacman (a sphere of radius 0.5 at height 0.5)

    glPushMatrix();
    glTranslatef(x, 0.030, z); // position
    glRotatef(90, 1.0, 0.0, 0.0);
    //gluCylinder(GLUquadric* qobj, GLdouble baseRadius, GLdouble topRadius, GLdouble height, GLint slices, GLint stacks);
    //base at z = 0; top at z = height
    gluCylinder(quadObj, 0.015, 0.015, 0.030, 100, 100);
    glPopMatrix(); //every push needs a pop

    glPushMatrix();
    glTranslatef(x, 0.030, z); // position coin/powerup
    glRotatef(90, 1.0, 0.0, 0.0);
    //gluDisk(GLUquadric *qobj, GLdouble innerRadius, GLdouble outerRadius, GLint slices, GLint loops);
    gluDisk(quadObj, 0.0, 0.015, 100, 100);
    glPopMatrix(); //every push needs a pop

}


////////////////////////////////////////////////////////////////////////////////
// draws a player as a sphere
////////////////////////////////////////////////////////////////////////////////
void drawPlayerSphere(float x, float z)
{

    glColor3f(colorYellow[0], colorYellow[1], colorYellow[2]);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colorYellow);
    //glMaterialfv(GL_FRONT, GL_AMBIENT, colorYellow);
    glMaterialfv(GL_FRONT, GL_SPECULAR, colorYellow);
    // Draw the pacman (a sphere of radius 0.5 at height 0.5)

    glPushMatrix();
    glTranslatef(x, 0.015, z); // position
    glutSolidSphere(0.015, 100, 100); // pacman sphere; 100 and 100 are slices and stacks
    glPopMatrix(); //every push needs a pop

}

void displayManual();

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
        displayManual(); // display the menu of options

        // set the camera position, where it is looking, and its up vector
        // Note: the angle is incremented by 5 degrees to rotate the camera
        // around the center of the maze
        gluLookAt(1.25*sin(angle*PI / 180.0) + 0.52, 1.25, 1.25*cos(angle*PI / 180.0) + 0.52,
                0.52, 0.0, 0.52,    // where the camera is looking (center of maze)
                0.0, 1.0, 0.0);     // up vector

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture[0]);

        glBegin(GL_QUADS);
            glTexCoord2f(1, 0);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glTexCoord2f(0, 0);
            glVertex3f(1.04f, 0.0f, 0.0f);
            glTexCoord2f(0, 1);
            glVertex3f(1.04f, 0.0f, 1.04f);
            glTexCoord2f(1, 1);
            glVertex3f(0.0f, 0.0f, 1.04f);
        glEnd();
        // glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);

        // drawHouse(0.17,0.17);   // the corner spaces are 0.17 by 0.17 units
        //drawHotel(0.17,0.17);

        //while loop
        Board* bd = GLRenderShared::board;
        if (bd != nullptr) {
            std::cout << "In display loop" << std::endl;
            
            std::cout << "set bd" << std::endl;
            BoardSpace* curr = bd->getHead();
            BoardSpace* tail = bd->getTail();
            std::vector<Player*> players = bd->getPlayers();
            std::cout << "accessing board pointer" << std::endl;

            int p1pos = (players[0])->getSpace()->getSpaceID();
            float p1x, p1z;
            spaceIDtoCoord(p1pos, &p1x, &p1z);
            if (p1pos % 10 % 2 == 0)
            {
                p1z += 0.02;
            }
            else
            {
                p1x -= 0.02;
            }
            drawPlayerCylinder(p1x, p1z);

            int p2pos = (players[1])->getSpace()->getSpaceID();
            float p2x, p2z;
            spaceIDtoCoord(p2pos, &p2x, &p2z);
            if (p2pos % 10 % 2 == 0)
            {
                p2z -= 0.02;
            }
            else
            {
                p2x += 0.02;
            }
            drawPlayerSphere(p2x, p2z);
            // Player 1 is a cylinder, Player 2 is a sphere
            // Board has a vector of player objects called "players"
            // each Player has a pointer to a BoardSpace object that indicates which space they're on (called boardSpace)
            // each boardSpace object has a space ID associated with it, there is a get function for each boardSpace objects called "getSpaceID" that returns an integer
            // so to get the ID of the space that each player is current on, you could use something like:
            // currPlayer->getSpace()->getSpaceID()  where currPlayer is a pointer to a Player object

            //drawHotel(28);
            while (curr->getSpaceID() != tail->getSpaceID())
            {
                int currID = curr->getSpaceID();
                float x, z;  //coordinates for center of this space
                spaceIDtoCoord(currID, &x, &z);
                Property* property = (Property*) curr;
                int houses = property->getUpgrades();  //1-4 is a house, >=5 is hotel
                if (1 <= houses && houses <= 4)
                {
                    drawHouse(currID, houses);
                }
                else if (houses >= 5)
                {
                    drawHotel(currID);
                }

                curr = curr->getNextSpace();
            }
        }

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
    gluLookAt(1.25*sin(angle*PI / 180.0) + 0.52, 1.25, 1.25*cos(angle*PI / 180.0) + 0.52,
            0.52, 0.0, 0.52,    // where the camera is looking (center of maze)
            0.0, 1.0, 0.0);     // up vector
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Used to detect keyboard inputs; used here to rotate the camera around the maze
/////////////////////////////////////////////////////////////////////////////////////////////////
void keyboard(unsigned char key, int x, int y){
    Board* boardPointer = GLRenderShared::board;
	client* cli = GLRenderShared::cli;

    playerMove outMsg;
    outMsg.playerID = GLRenderShared::username;
    outMsg.movePosition = 0;
    std::cout << "username: " << GLRenderShared::username << std::endl;
    switch (key) {
        case 'b':
        case 'B':
            // attempt to buy a property
            // insert function sending 'b' to server
            outMsg.moveType = 'b';
            outMsg.playerRoll = 0;
            cli->sendToServer(outMsg);

			break;
        case 's':
        case 'S':
            // send message that you want to sell a property to the bank
            // print success of sale to the screen
            outMsg.moveType = 's';
            outMsg.playerRoll = 0;
            cli->sendToServer(outMsg);

            // if there are any hotels/houses, they should recieve their worth back
            // also, houses and hotels should disappear

            // board object should be updated here before being redrawn
            // because houses/hotels might disappear
            glutPostRedisplay();
            break;

        case 'h':
        case 'H':
            // send message that you want to upgrade
            // technically a player can buy multiple houses in a row
            outMsg.moveType = 'h';
            outMsg.playerRoll = 0;
            cli->sendToServer(outMsg);


            glutPostRedisplay();
            break;

        case 'j':
        case 'J':
            // send message that you want to buy a hotel
            // server should return success or fail
            outMsg.moveType = 'j';
            outMsg.playerRoll = 0;
            cli->sendToServer(outMsg);

            glutPostRedisplay();
            break;

        case 'r': // roll dice
        case 'R':
            // send message that your turn is over
            // board object should be updated here before being redrawn
            outMsg.moveType = 'r';
            outMsg.playerRoll = 0;
            cli->sendToServer(outMsg);

            glutPostRedisplay();
            break;

        case 'n':
        case 'N':
            // send message that your turn is over
            // board object should be updated here before being redrawn
            outMsg.moveType = 'n';
            outMsg.playerRoll = 0;
            cli->sendToServer(outMsg);

            glutPostRedisplay();
            break;

        case 't':
        case 'T':
            // change camera angle
            angle += 5;
            if(angle == 360){
                angle = 0;          // reset to zero after complete circle
            }
            glutPostRedisplay();    // redraw scene after angle change and/or window resize
            break;
        default:
            break;
    }   // end of switch
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Used to display the button functions on the screen
/////////////////////////////////////////////////////////////////////////////////////////////////
void displayManual(void){
    std::string message[] ={"Keyboard Functions",
                            "B: Buy a property\0",
                            "S: Sell your property\0",
                            "H: Build a house\0",
                            "J: Build a Hotel\0",
                            "R: Roll the dice\0",
                            "N: End your turn\0",
                            "T: Rotate the board\0"};

    glMatrixMode(GL_PROJECTION);

    glPushMatrix();
        glLoadIdentity();
        glOrtho(0, screenWidth, 0, screenHeight, 0, 10);    // display in ortho/flat 2D space
        glMatrixMode(GL_MODELVIEW);

        glPushMatrix();
            glLoadIdentity();
            glColor3f(1.0, 1.0, 1.0);   // white text
            float offset = 0.0;
            for(const std::string line : message){
                glRasterPos2i(0.75 * screenWidth, 0.40 * screenHeight - offset*screenHeight); // bottom right of screen
                offset += 0.03;

                for(const char character : line){
                    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, character);   // loop through all chars in message
                }
            }
        glPopMatrix();

        glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
}   // end of displayManual()

////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
// Main function - this is where everything is inialized/called
/////////////////////////////////////////////////////////////////////////////////////////////////
int setup(int argc, char** argv) {
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
