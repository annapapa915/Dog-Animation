#include <stdlib.h>
#include <glut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <array>
#define PI 3.1415

using namespace std;

// Anna Papadopoulou 3136

// A quadric object used in glCylinder
GLUquadric* qobj;

// Variable signifying the camera angle
float camera_angle = 0;
// Changes according to the menu choices picked
int mode = 0;
// Used in the timer func
int FPS = 200;

// Contains the amount we rotate each body part. From left to right the values represent torso, neck, head, ul1, ul2, ul3, ul4, ll1, ll2, ll3, ll4, foot1, foot2, foot3, foot4
array<float, 15> theta = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
// The final angles we want each part to reach during the animation
array<float, 15> end_angles;

// Width and height of window
int W = 500, H = 500;


// Struct that represents a node of a tree
typedef struct treenode
{
    // stores a 4 x 4 homogenous coordinate matrix
    GLfloat m[16];
    // contains the graphics primitives
    void (*f)();
    struct treenode* sibling;
    struct treenode* child;
} treenode;

// Nodes representing every body part
treenode torso_node, head_node, neck_node, ul_node_1, ul_node_2, ul_node_3, ul_node_4, ll_node_1, ll_node_2, ll_node_3, ll_node_4, feet_node_1, feet_node_2, feet_node_3, feet_node_4;


// Function that sets the camera when we change the view from the menu
void setCamera()
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float angle_x, angle_z;

    // If camera is on the front, then the angle is 0
    if (mode == 0)
    {
        camera_angle = 0;

    }
    // If camera is on the side, the angle is 90 degrees
    else if (mode == 1)
    {
        camera_angle = 90;
    }
    angle_x = 70 * sin(camera_angle * PI / 180);
    angle_z = -70 * cos(camera_angle * PI / 180);

    // Change point of looking accordingly
    gluLookAt(0, 0, 0, angle_x, 0, angle_z, 0, 1, 0);
    glMatrixMode(GL_MODELVIEW);

}

// Function that draws a cylinder closed with a disk
void Cylinder(float a, float b, float c, float d, float e) {

    qobj = gluNewQuadric();
    gluQuadricNormals(qobj, GLU_SMOOTH);

    gluCylinder(qobj, a, b, c, d, e);
    gluDisk(qobj, 0, a, d, e);

}

// Function that traverses a tree structure
// We first look for children and then siblings
void traverse(treenode* root)
{
    if (root == NULL) return;
    glPushMatrix();
    glMultMatrixf(root->m);
    root->f();
    if (root->child != NULL) traverse(root->child);
    glPopMatrix();
    if (root->sibling != NULL) traverse(root->sibling);
}

// Function that draws the torso
void torso()
{
    glColor3ub(155, 115, 165);
    // Rotates both the torso and its children
    glRotatef(theta[0], 0.0, 0.0, 1.0);
    glPushMatrix();

    glRotated(90, 0.0, 1.0, 0.0);
    glTranslatef(0, 0, -0.5);

    
    Cylinder(0.2, 0.2, 0.9, 20, 8);
    glPopMatrix();
 
}

// Function that draws the neck
void neck()
{
    glColor3ub(155, 135, 165);
    glPushMatrix();

    glTranslatef(0.35, 0.13, 0);

    glRotatef(theta[1], 0.0, 0.0, -10.0);
    glRotated(90, -1.0, 1.0, 0.0);

    Cylinder(0.06, 0.06, 0.3, 10, 8);
    glPopMatrix();
 
}

// Function that draws the head
void head()
{
  
    qobj = gluNewQuadric();
    gluQuadricNormals(qobj, GLU_SMOOTH);
    glPushMatrix();
    glColor3ub(175, 165, 165);

    glRotatef(theta[2], 0.0, 0.0, -1.0);
    glTranslatef(0.58, 0.37, 0); 
   
    
    gluSphere(qobj, 0.13, 20, 8);
    glPopMatrix();
 

}

// Function that draws the front right upper leg
void upper_leg1()
{

    glColor3ub(155, 115, 165);
    glPushMatrix();
    glTranslatef(0.34, -0.14, -0.1);

    glRotatef(theta[3], 0.0, 0.0, 1.0);
    glRotated(90, 1.0, 0.0, 0.0);


    Cylinder(0.06, 0.06, 0.2, 10, 8);
    glPopMatrix();

}

// Function that draws the back right upper leg
void upper_leg2()
{
    glColor3ub(155, 115, 165);
    glRotatef(theta[4], 0.0, 0.0, -1.0);
    glPushMatrix();
    glTranslatef(-0.44, -0.14, -0.1);

    glRotated(90, 1.0, 0.0, 0.0);

    Cylinder(0.06, 0.06, 0.2, 10, 8);
    glPopMatrix();
    
}

// Function that draws the front left upper leg
void upper_leg3()
{
    glColor3ub(155, 115, 165);
    glPushMatrix();
    glTranslatef(0.34, -0.14, 0.1);

    glRotatef(theta[5], 0.0, 0.0, 1.0);
    glRotated(90, 1.0, 0.0, 0.0);

    Cylinder(0.06, 0.06, 0.2, 10, 8);
    glPopMatrix();

}

// Function that draws the back left upper leg
void upper_leg4()
{
    glRotatef(theta[6], 0.0, 0.0, -1.0);
    glColor3ub(155, 115, 165);
    glPushMatrix();
    glTranslatef(-0.44, -0.14, 0.1);

    glRotated(90, 1.0, 0.0, 0.0);

    Cylinder(0.06, 0.06, 0.2, 10, 8);
    glPopMatrix();
}

// Function that draws the front right lower leg
void lower_leg1()
{
    glColor3ub(155, 135, 165);
    glRotatef(theta[7], 0.0, 0.0, 1.0);
    glPushMatrix();
    
    glRotated(90, 1.0, 0.0, 0.0);
    glTranslatef(0.34, -0.1, 0.34);

    Cylinder(0.06, 0.06, 0.2, 10, 8);
    glPopMatrix();

}


// Function that draws the back right lower leg
void lower_leg2()
{
    glColor3ub(155, 135, 165);
    glPushMatrix();
    glRotatef(theta[8], 0.0, 0.0, -1.0);
    glTranslatef(-0.44, -0.34, -0.1);

    glRotated(90, 1.0, 0.0, 0.0);

    Cylinder(0.06, 0.06, 0.2, 10, 8);
    glPopMatrix();
 

}

// Function that draws the front left lower leg
void lower_leg3()
{
    glColor3ub(155, 135, 165);
    glRotatef(theta[9], 0.0, 0.0, 1.0);
    glPushMatrix();

    glRotated(90, 1.0, 0.0, 0.0);
    glTranslatef(0.34, 0.1, 0.34);

    Cylinder(0.06, 0.06, 0.2, 10, 8);
    glPopMatrix();

}

// Function that draws the back left lower leg
void lower_leg4()
{
    glColor3ub(155, 135, 165);
    glPushMatrix();
    glRotatef(theta[10], 1.0, 0.0, -1.0);
    glTranslatef(-0.44, -0.34, 0.1);

    glRotated(90, 1.0, 0.0, 0.0);

    Cylinder(0.06, 0.06, 0.2, 10, 8);
    glPopMatrix();

}

// Function that draws the front right foot
void foot_1()
{
    glColor3ub(255, 211, 182);
    glPushMatrix();
    

    glRotatef(theta[11], 0.0, 0.0, 1.0);
    glRotated(90, 0.0, 1.0, 0.0);
    glTranslatef(0.1, -0.54, 0.28);

    Cylinder(0.05, 0.05, 0.25, 10, 8);
    glPopMatrix();


}

// Function that draws the back right foot
void foot_2()
{
    glColor3ub(255, 211, 182);
    glPushMatrix();
    glTranslatef(-0.5, -0.54, -0.1);

    glRotatef(theta[12], 1.0, 0.0, -1.0);
    glRotated(90, 0.0, 1.0, 0.0);

    Cylinder(0.05, 0.05, 0.25, 10, 8);
    glPopMatrix();


}

// Function that draws the front left foot
void foot_3()
{
    glColor3ub(255, 211, 182);
    glPushMatrix();


    glRotatef(theta[13], 0.0, 0.0, 1.0);
    glRotated(90, 0.0, 1.0, 0.0);
    glTranslatef(-0.1, -0.54, 0.28);

    Cylinder(0.05, 0.05, 0.25, 10, 8);
    glPopMatrix();

}

// Function that draws the back left foot
void foot_4()
{
    glColor3ub(255, 211, 182);
    glPushMatrix();
    glTranslatef(-0.5, -0.54, 0.1);

    glRotatef(theta[14], 1.0, 0.0, -10.0);
    glRotated(90, 0.0, 1.0, 0.0);

    Cylinder(0.05, 0.05, 0.25, 10, 8);
    glPopMatrix();

}

// Function that moves the front right leg of the dog by changing the angles corresponding to the parts we want to move
void moveLegUp()
{
    if (theta[3] < end_angles[3])
    {
        theta[3] = theta[3] + 0.32;
    }

    if (theta[7] < end_angles[7])
    {
        theta[7] = theta[7] + 0.12;
    }

}

// Function that moves the dog's whole body up by changing the angles corresponding to the parts we want to move 
// The front legs are slightly bent
void moveBodyUp()
{
    if (theta[4] < end_angles[4])
    {
        theta[4] = theta[4] + 0.5;
    }
    if (theta[6] < end_angles[6])
    {
        theta[6] = theta[6] + 0.5;
    }
    if (theta[3] < end_angles[3])
    {
        theta[3] = theta[3] + 0.54;
    }
    if (theta[7] < end_angles[7])
    {
        theta[7] = theta[7] + 0.22;
    }
    if (theta[5] < end_angles[5])
    {
        theta[5] = theta[5] + 0.34;
    }
    if (theta[9] < end_angles[9])
    {
        theta[9] = theta[9] + 0.14;
    }
    if (theta[0] < end_angles[0])
    {
        theta[0] = theta[0] + 0.4;
    }
    if (theta[1] < end_angles[1])
    {
        theta[1] = theta[1] + 0.42;
    }
    if (theta[2] < end_angles[2])
    {
        theta[2] = theta[2] + 0.18;
    }
   
}

// Function that moves the dog's head down by changing the angles corresponding to the parts we want to move 
void moveHeadDown()
{
    if (theta[1] < end_angles[1])
    {
        theta[1] = theta[1] + 0.5;
    }
    if (theta[2] < end_angles[2])
    {
        theta[2] = theta[2] + 0.25;
    }
}

// Function that changes the dog's animation depending the option picked at the menu
void updateAnimation()
{

    switch (mode)
    {
   
    case 2:
    {
        moveLegUp();

        break;
    }
    case 3:
    {
        moveBodyUp();

        break;
    }
    case 4:
    {
        moveHeadDown();

        break;
    }
   
    }

    glutPostRedisplay();
}

// A timer function that updates the animation
void timer(int)
{
    updateAnimation();
    glutTimerFunc(1000.0 / FPS, timer, 0);
}


void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    
    // By traversing the torso, we draw it on the screen
    traverse(&torso_node);

    glFlush();

    glutSwapBuffers();

}


// Initialization
void myinit()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);

    // Tree structure of the dog
    // We have a binary tree that follows the LCRS representation
    // The torso is the root of our tree

    // torso
    glGetFloatv(GL_MODELVIEW_MATRIX, torso_node.m);
    torso_node.f = torso;
    torso_node.sibling = NULL;
    torso_node.child = &ul_node_4;

    // neck
    glGetFloatv(GL_MODELVIEW_MATRIX, neck_node.m);
    neck_node.f = neck;
    neck_node.sibling = NULL;
    neck_node.child = &head_node;


    // head
    glGetFloatv(GL_MODELVIEW_MATRIX, head_node.m);
    head_node.f = head;
    head_node.sibling = NULL;
    head_node.child = NULL;


    // upper front leg
    glGetFloatv(GL_MODELVIEW_MATRIX, ul_node_1.m);
    ul_node_1.f = upper_leg1;
    ul_node_1.sibling = &neck_node;
    ul_node_1.child = &ll_node_1;


    // down front leg
    glGetFloatv(GL_MODELVIEW_MATRIX, ll_node_1.m);
    ll_node_1.f = lower_leg1;
    ll_node_1.sibling = NULL;
    ll_node_1.child = &feet_node_1;


    // upper back leg
    glGetFloatv(GL_MODELVIEW_MATRIX, ul_node_2.m);
    ul_node_2.f = upper_leg2;
    ul_node_2.sibling = &ul_node_3;
    ul_node_2.child = &ll_node_2;


    // down back leg
    glGetFloatv(GL_MODELVIEW_MATRIX, ll_node_2.m);
    ll_node_2.f = lower_leg2;
    ll_node_2.sibling = NULL;
    ll_node_2.child = &feet_node_2;


    // front foot
    glGetFloatv(GL_MODELVIEW_MATRIX, feet_node_1.m);
    feet_node_1.f = foot_1;
    feet_node_1.sibling = NULL;
    feet_node_1.child = NULL;


    // back foot
    glGetFloatv(GL_MODELVIEW_MATRIX, feet_node_2.m);
    feet_node_2.f = foot_2;
    feet_node_2.sibling = NULL;
    feet_node_2.child = NULL;


    // upper front leg
    glGetFloatv(GL_MODELVIEW_MATRIX, ul_node_3.m);
    ul_node_3.f = upper_leg3;
    ul_node_3.sibling = &ul_node_1;
    ul_node_3.child = &ll_node_3;



    // down front leg
    glGetFloatv(GL_MODELVIEW_MATRIX, ll_node_3.m);
    ll_node_3.f = lower_leg3;
    ll_node_3.sibling = NULL;
    ll_node_3.child = &feet_node_3;


    // upper back leg
    glGetFloatv(GL_MODELVIEW_MATRIX, ul_node_4.m);
    ul_node_4.f = upper_leg4;
    ul_node_4.sibling = &ul_node_2;
    ul_node_4.child = &ll_node_4;


    // down back leg
    glGetFloatv(GL_MODELVIEW_MATRIX, ll_node_4.m);
    ll_node_4.f = lower_leg4;
    ll_node_4.sibling = NULL;
    ll_node_4.child = &feet_node_4;


    // front foot
    glGetFloatv(GL_MODELVIEW_MATRIX, feet_node_3.m);
    feet_node_3.f = foot_3;
    feet_node_3.sibling = NULL;
    feet_node_3.child = NULL;


    // back foot
    glGetFloatv(GL_MODELVIEW_MATRIX, feet_node_4.m);
    feet_node_4.f = foot_4;
    feet_node_4.sibling = NULL;
    feet_node_4.child = NULL;


    timer(0);

}

// Function that reshapes the screen
void reshape(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, W, H); // adjust the view
    W = w;
    H = h;
}

// Function that resets the angles, effectively returning the dog to its original position
void resetAngles()
{
    array<float, 15> refresh = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    array<float, 15> new_end_angles = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    end_angles = new_end_angles;
    theta = refresh;
}


// Sub menu that dictates where the camera faces
void menuS1(int id)
{

    switch (id)
    {
        // camera faces on the side
        case 0: {
             mode = 0;

             setCamera();
             glutPostRedisplay();
             break;
        }
  
        // camera face on the front
        case 1:
        {
           mode = 1;
           myinit();

           setCamera();
           glutPostRedisplay();
           break;
        }

    }
}


// Sub menu that dictates which animation we want to see
void menuS2(int id)
{
    switch (id)
    {
    // Lifts leg
    case 0:
    {
        mode = 2;
        resetAngles();
        // The end angles we want each dog's part to reach
        array<float, 15> new_end_angles = { 0, 0, 0, 80, 0, 0, 0, 30, 0, 0, 0, 30, 0, 0, 0 };
        end_angles = new_end_angles;
        break;
    }
    // Lifts body
    case 1:
    {
        mode = 3;
        resetAngles();
        array<float, 15> new_end_angles = { 25, 10, 5, 80, 23, 50, 23, 30, 0, 20, 0, 30, 80, 20, 0 };
        end_angles = new_end_angles;
        break;

        break;
    }
    // Head moves down
    case 2: 
    {
        mode = 4;
        resetAngles();
        array<float, 15> new_end_angles = { 0, 80, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        end_angles = new_end_angles;
        break;
    }
    // Revert to original position
    case 3:
        mode = 5;
        resetAngles();

        break;
    }
}

// Menu containing sub menus
void menu(int id)
{
    switch (id)
    {
    case 13:
        exit(0);
    }
}

int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(W, H);
    glutInitWindowPosition(500, 200);
    glutCreateWindow("Model Dog");
    //Register callback function
    glutDisplayFunc(display);

    glutReshapeFunc(reshape);

    myinit();

    int sub1 = glutCreateMenu(menuS1);
    glutAddMenuEntry("Camera on the side", 0);
    glutAddMenuEntry("Camera on the front", 1);
    glutCreateMenu(menuS1);


    int sub2 = glutCreateMenu(menuS2);
    glutAddMenuEntry("Lift front leg up", 0);
    glutAddMenuEntry("Lift front body up", 1);
    glutAddMenuEntry("Head down", 2);
    glutAddMenuEntry("Return to original position", 3);
    glutCreateMenu(menuS2);


    glutCreateMenu(menu);

    glutAddSubMenu("Change View", sub1);
    glutAddSubMenu("Move Dog", sub2);

    glutAddMenuEntry("Termination", 13);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();

    return 0;
}