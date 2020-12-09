
/**********************************************************************************************************************************************************

Aim : Program using glut opengl to implement water simulation graphically using C++
Topic : Water Simulation

Names : Jyoti Dixit and Chandana M.
USNs : 1SG15CS035 and 1SG15CS021

Guides : Mrs. Chaithra - Associate Professor
		 Mrs. Anuradha - Assistant Professor

College : Sapthagiri College of Engineering

**********************************************************************************************************************************************************/

//Including the required header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Including the glut header file
#include <GL/glut.h>

//Declaring constants
#define BOUNDS 1
#define WATERSIZE 200
#define DAMP 20
#define TEXTID 3

//Declaring variables

float water[2][WATERSIZE][WATERSIZE];

//x-y rotation
int spin_x, spin_y;

//zoom
int spin_z;

//Height of window
int h;

//Width of window
int w;

//Declaring other necessary variables
int old_x;
int old_y;
int move_z;

//Declaring and initializing more variables
int depth = 3;
int i = 0;
int t = 0;
int f = 1;

//Function to calculate pixels to display water
void calcwater()
{
	//Declaring local variables
	int x, y;
	float n;
	for(y = 1; y < WATERSIZE-1; y++)
	{
		for(x = 1; x < WATERSIZE-1; x++)
		{
			n = ( water[t][x-1][y] + water[t][x+1][y] + water[t][x][y-1] + water[t][x][y+1] ) /2;
			n -= water[f][x][y];
	      	n = n - (n / DAMP);
			water[f][x][y] = n;
		}
	}
	y = 0;
	for(x = 1; x < WATERSIZE-1; x++)
	{
		n = ( water[t][x-1][y] + water[t][x+1][y] + water[t][x][y+1] ) /2;
		n -= water[f][x][y];
	    n = n - (n / DAMP);
		water[f][x][y] = n;
	}
	x = 0;
	for(y = 1; y < WATERSIZE-1; y++)
	{
		n = ( water[t][x+1][y] + water[t][x][y-1] + water[t][x][y+1] ) /2;
		n -= water[f][x][y];
 		n = n - (n / DAMP);
		water[f][x][y] = n;
	}
	x = WATERSIZE-1;
	for(y = 1; y < WATERSIZE-1; y++)
	{
		n = ( water[t][x-1][y] + water[t][x][y-1] + water[t][x][y+1] ) /2;
		n -= water[f][x][y];
		n = n - (n / DAMP);
		water[f][x][y] = n;
	}
	y = WATERSIZE-1;
	for(x = 1; x < WATERSIZE-1; x++)
	{
		n = ( water[t][x-1][y] + water[t][x+1][y] + water[t][x][y-1] ) /2;
		n -= water[f][x][y];
	    n = n - (n / DAMP);
		water[f][x][y] = n;
	}
}
// End of calcwater() function

//Function for reshaping
void reshape(int width, int height)
{
	//Declaring local variables
	w = width;
	h = height;
	
	//Transformation of x and y from normalized device coordinates to window coordinates
	glViewport(0, 0, width, height);
	
	//Setting the current matrix mode
	glMatrixMode(GL_PROJECTION);
	
	//Replacing the current matrix with the identity matrix
	glLoadIdentity();
	
	//Specifying a viewing frustum into the world coordinate system
	gluPerspective(40.0, (GLfloat) w/(GLfloat) h, 1.0, 2000.0);
	
	//Applying subsequent matrix operations to the modelview matrix stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity ();
}
//End of reshape() function

//Displaying function
void display(void)
{
	//Declaring local variables
    int i, j, tmp;

	//To clear the previous color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(0, 0, spin_z-220);
	glRotatef(spin_x, 0, 1, 0);
	glRotatef(spin_y-60, 1, 0, 0);
	
	//Background color
	glClearColor(0,0,0.1,0.0);
	
	//Calculating calcwater function to calculate and display water in a graphical manner
	calcwater();
	
	//Displaying water graphically in the form of points
	glBegin(GL_POINTS);

	for(i = 0; i < WATERSIZE; i++)
	{
		for(j = 0; j < WATERSIZE; j++)
		{
			glColor3f(0,0.1,1);
			glVertex3f(j-WATERSIZE/2, i-WATERSIZE/2, water[t][j][i]);
		}
	}
	glEnd();
	tmp = t; t = f; f = tmp;
	glPopMatrix();
	glutSwapBuffers();
}
//End of display() function
	
//Other required variables
int num  = 0;
int delay = 70;

//Idle function to continue executing statements		<<<<<<<<<<<<--------------------
void idle(void)
{
	if(!(++num %delay))
	{
		water[f][rand()%WATERSIZE][rand()%WATERSIZE] = -rand()%200;
		delay = rand()%100 + 50;
	}
	
	//To call the display() function continuously
	glutPostRedisplay();
}
//End of idle() function

//Function for mouse movement
void motion(int x, int y)
{
	if(!move_z)
	{
		spin_x = x - old_x;
		spin_y = y - old_y;
	}
	else
		spin_z = y - old_y;
	
	//To call the display() function continuously
	glutPostRedisplay();
}
//End of motion() function

//Function to display text on the window
void DrawTextXY(double x,double y,double z,double scale,char *s)
{
   int i;
   glPushMatrix();
   
   //Translation
   glTranslatef(x,y,z);
   glScalef(scale,scale,scale);

   //Scaling
   for (i=0;i < strlen(s);i++)
   {
      glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,s[i]);
   }
   glPopMatrix();
}
//End of DrawTextXY() function

//Help window
void help()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Replacing the current matrix with the identity matrix
	glLoadIdentity();

	//Clearing the background color
	glClearColor(0.1,0,0.1,1.0);

	//Translation
	glTranslatef(0.0,0.0,-6.0);
	glTranslatef(0.0,-1.3,0.0);

	//Displaying HELP
	glColor3f(0.6,0.8,0.7);
	DrawTextXY(-1.5,2.9,0.0,0.0025,"HELP WINDOW");

	//Displaying the window title
	glColor3f(1.0,0.8,0.4);
	DrawTextXY(-1.75,2.1,0.0,0.0014,"  Keyboard Controls : ");
	
	//Displaying how to maximize the window
	glColor3f(0.1,0.9,0.1);
	DrawTextXY(-1.25,1.3,0.0,0.001,"  Maximize  ->  f ");

	//Displaying how to minimize the window
	glColor3f(0.1,0.1,0.9);
	DrawTextXY(-1.25,0.7,0.0,0.001,"  Minimize ->  m ");
	
	//Displaying how to exit from the current window
	glColor3f(0.9,0.1,0.1);
	DrawTextXY(-1.25,0.1,0.0,0.001,"  Exit  ->  x ");
	glColor3f(0.9,0.9,0.8);
	
	//Finish rendering
	glFlush();
	glutSwapBuffers();
}
//End of help() function

//About window
void cover()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Replacing the current matrix with the identity matrix
	glLoadIdentity();

	//Clearing the background color
	glClearColor(0.1,0,0,0.0);

	//Translation
	glTranslatef(0.0,0.0,-6.0);
	glTranslatef(0.0,-1.3,0.0);
	
	glLoadName(TEXTID);

	//Displaying details
	glColor3f(0.8,0.8,0.8);
	DrawTextXY(-2.0,2.8,0.0,0.0014,"Computer Graphics Mini Project");
	
	//Displaying the project title
	glColor3f(0.7,0.6,0.1);
	DrawTextXY(-1.5,2.0,0.0,0.0014,"WATER RIPPLING EFFECT");

	glColor3f(0.0,0.5,0.9);
	DrawTextXY(-3.0,1.5,0.0,0.0007,"Submitted by :- ");
	
	//Displaying the name of student 1
	glColor3f(1.0,0.0,0.9);
	DrawTextXY(-2.5,1.2,0.0,0.001,"Jyoti Dixit ");

	//Displaying the USN of student 1
	glColor3f(0.7,0.6,0.6);
	DrawTextXY(-2.5,0.95,0.0,0.001,"1SG15CS035 ");

	//Displaying the name of student 2
	glColor3f(1.0,0.0,0.9);
	DrawTextXY(1,1.2,0.0,0.001,"Chandana M.");
	
	//Displaying the USN of student 2
	glColor3f(0.7,0.6,0.6);
	DrawTextXY(1,0.95,0.0,0.001,"1SG15CS021");
	
	glColor3f(0.5,0.6,0.7);
	DrawTextXY(-1.9,0.2,0.0,0.0007,"Under the guidance of : ");
	
	//Displaying the details of project guide 1
	glColor3f(0.9,1.0,0.2);
	DrawTextXY(-1.4,0.0,0.0,0.001,"Mrs. Chaithra");
	
	glColor3f(0.7,1.0,0.0);
	DrawTextXY(-1.4,-0.2,0.0,0.0007,"Associate Professor");
	
	//Displaying the details of project guide 2
	glColor3f(0.9,1.0,0.2);
	DrawTextXY(1.1,0.0,0.0,0.001,"Mrs. Anuradha Badage");
	
	glColor3f(0.7,1.0,0.0);
	DrawTextXY(1.1,-0.2,0.0,0.0007,"Assistant Professor");

	//Displaying the name of college on output window
	glColor3f(0.6,1.0,0.9);
	DrawTextXY(-1.6,-.5,0.0,0.001,"Sapthagiri College of Engineering");
	
	//Finish rendering
	glFlush();

	glutSwapBuffers();
}
//End of cover() function

//Function to perform actions as per the key pressed on the keyboard
void keyboard(unsigned char key, int x, int y)
{
	static int old_x = 50;
	static int old_y = 50;
	static int old_width = 512;
	static int old_height = 512;
    switch (key)
	{
		case 'x':	//Exit from the current window using keyboard
					exit(0);
					break;

		case 'm':	//Minimizing the current window to a fixed size
					glutPositionWindow(old_x, old_y);
				    glutReshapeWindow(old_width, old_height);
					break;

		case 'f':	//Maximizing the current window to the full window size
					if (glutGet(GLUT_WINDOW_WIDTH) < glutGet(GLUT_SCREEN_WIDTH))
					{
						old_x = glutGet(GLUT_WINDOW_X);
						old_y = glutGet(GLUT_WINDOW_Y);
						old_width = glutGet(GLUT_WINDOW_WIDTH);
						old_height = glutGet(GLUT_WINDOW_HEIGHT);
						glutFullScreen();
					}
					break;

		case ' ':	water[f][WATERSIZE/2][WATERSIZE/2] = -1000;
					break;
	}
}
//End of keyboard() function

//Funnction to be called initially to set the desired height and width of window
void init(void)
{
	int i, j;

	//Initializing the width and height of window
	w = glutGet(GLUT_WINDOW_WIDTH);
	h = glutGet(GLUT_WINDOW_HEIGHT);

	glEnable(GL_DEPTH_TEST);
	for( i = 0; i < WATERSIZE; i++)
	{
		for( j = 0; j < WATERSIZE; j++)
		{
			water[0][j][i] = 0;
			water[1][j][i] = 0;
		}
	}
}
//End of init() function

//Menu function
void menu(int id)
{
	switch(id)
	{
		case 1:	//Displaying water ripples continuously
				calcwater();
				glutIdleFunc(idle);
				break;

		case 2:	//Displaying still water
				glutIdleFunc(NULL);
				break;

		case 3:	//Displaying about window
				cover();
				glutIdleFunc(cover);
				break;

		case 4:	//Displaying help window
				help();
				glutIdleFunc(help);
				break;

		case 5:	//Exit from the display
				exit(0);
	}
}				
//End of menu() function

//Main function
void main(int argc, char** argv)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(748,700);
	glutInit(&argc, argv);
	glColor3f(0.2,0.1,0.3);
	glutCreateWindow("Simulating Water");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	//Creating menu
	glutCreateMenu(menu);
	
	//Adding menu entries
	glutAddMenuEntry("Continue rippling",1);
	glutAddMenuEntry("Stop rippling",2);
	glutAddMenuEntry("About",3);
	glutAddMenuEntry("Help",4);
	glutAddMenuEntry("Exit",5);

	//Ataching a mouse button for the current window to the identifier of the current menu
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	//Calling the keyboard function
	glutKeyboardFunc(keyboard);

	//glutMotionFunc(motion);

	glEnable (GL_DEPTH_TEST);
	glColor3f(0.2,0.1,0.3);
	printf("Water Simulation\n");
	init();
	glutMainLoop();
}
//End of main function
