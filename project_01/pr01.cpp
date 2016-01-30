// =============================================================================
// VIZA654/CSCE646 at Texas A&M University
// Homework 0
// Created by Anton Agana based from Ariel Chisholm's template
// 05.23.2011
//
// This file is supplied with an associated makefile. Put both files in the same
// directory, navigate to that directory from the Linux shell, and type 'make'.
// This will create a program called 'pr01' that you can run by entering
// 'homework0' as a command in the shell.
//
// If you are new to programming in Linux, there is an
// excellent introduction to makefile structure and the gcc compiler here:
//
// http://www.cs.txstate.edu/labs/tutorials/tut_docs/Linux_Prog_Environment.pdf
//
// =============================================================================

#include <cstdlib>
#include <iostream>
#include <GL/glut.h>

#include <fstream>
#include <cassert>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;

// =============================================================================
// These variables will store the input ppm image's width, height, and color
// =============================================================================
string type;
int width, height;
unsigned char *pixmap;
/*Finally, the parameter(for "glDrawPixels()"), pixmap is a pointer to an array of characters
(unsigned char *pixmap) that is used to store the image’s pixmap.*/


// =============================================================================
// setPixels()
//
// This function stores the RGB values of each pixel to "pixmap."
// Then, "glutDisplayFunc" below will use pixmap to display the pixel colors.
// =============================================================================
void setPixels(int argc, char *argv[])
{
   
   for(int y = 0; y < height ; y++) /*Scanline number.*/{
     for(int x = 0; x < width; x++) /*Pixel number on scanline.*/{
       int i = (y * width + x) * 3; /*"i" signifies the value of the pixel value fetched from scanline.*/
       /*At this point within the function,we are assigning color values to our RGB pixmap array.*/

            
        /*This block of code corresponds to command line arguments dictating color of pixmap.*/
	/*Red option.*/	
	if(type=="red"){
	   pixmap[i++] = 0xFF;
	   pixmap[i++] = 0x00; 
	   pixmap[i] = 0x00; 
	}
	/*Green option.*/	
	else if(type=="green"){
	   pixmap[i++] = 0x00;
	   pixmap[i++] = 0xFF; 
	   pixmap[i] = 0x00; 
	}
	/*Blue option.*/	
	else if(type=="blue"){
	   pixmap[i++] = 0x00;
	   pixmap[i++] = 0x00; 
	   pixmap[i] = 0xFF; 
	}
        /*This block of code corresponds to command line argument for "all" option.*/
	else if(type=="all"){
		//Green quadrant.
		if((x>(width/2))&&(y>=(height/2))){
		   pixmap[i++] = 0x00;
		   pixmap[i++] = 0xFF; 
		   pixmap[i] = 0x00; 
		}	
		//Red quadrant.
		if((x<=(width/2))&&(y>=(height/2))){
		   pixmap[i++] = 0xFF;
		   pixmap[i++] = 0x00; 
		   pixmap[i] = 0x00; 
		}	
		//Blue quadrant.
		if((x<=(width/2))&&(y<=(height/2))){
		   pixmap[i++] = 0x00;
		   pixmap[i++] = 0x00; 
		   pixmap[i] = 0xFF; 
		}
		//Yellow quadrant.
		if((x>=(width/2))&&(y<(height/2))){
		   pixmap[i++] = 0xFF;
		   pixmap[i++] = 0xFF; 
		   pixmap[i] = 0x00; 
		}
	}
	/*This block of code corresponds to command line argument for "circle" option.*/
	else if(type=="circle"){
			float diameter = 10000;
			float y_portion= pow((y-width/2),2);
			float x_portion= pow((x-width/2),2);
			float areaCircle= x_portion+y_portion;
			
			
			if(areaCircle<=diameter)
			{		//inside circle yellow. Calls distance function and radius int
				pixmap [i++] = 255;
				pixmap [i++] = 255;
				pixmap [i++] = 0;
			}
			else
			{			//outside circle blue
			pixmap [i++] = 0;
			pixmap [i++] = 0;
			pixmap [i++] = 255; 
			}
        }
	/*This block of code corresponds to command line argument for "other" option.*/
	else if(type=="other"){
			float diameter = 50000;
			float y_portion= pow((y-width/2),2);
			float x_portion= pow((x-width/2),2);
			float areaCircle= x_portion+y_portion;
			
			


			if(areaCircle<=diameter/4)
			{		//inside circle yellow. Calls distance function and radius int
				pixmap [i++] = x*y;
				pixmap [i++] = sin(y)*i;
				pixmap [i++] = y;
			}
			else if(areaCircle<=diameter/2)
			{		//inside circle yellow. Calls distance function and radius int
				pixmap [i++] = x*x;
				pixmap [i++] = y;
				pixmap [i++] = y;
			}
			else if(areaCircle<=diameter)
			{			//outside circle blue
			/*pixmap [i++] = 0;
			pixmap [i++] = i*x*x;
			pixmap [i++] = i*x; */
			pixmap [i++] = x*y;
				pixmap [i++] = x*y;
				pixmap [i++] = y;
			}
        }
	/*This block of code corresponds to command line argument for "other" option.*/
	else{
		cout << "Incorrect input. Now closing." << endl;
		exit(0);
        }
     }
   }
}



// =============================================================================
// OpenGL Display and Mouse Processing Functions.
//
// You can read up on OpenGL and modify these functions, as well as the commands
// in main(), to perform more sophisticated display or GUI behavior. This code
// will service the bare minimum display needs for most assignments.
// =============================================================================
static void windowResize(int w, int h)
{   
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0,(w/2),0,(h/2),0,1); 
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity() ;
}
//Function responsible for graphics display.
static void windowDisplay(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glRasterPos2i(0,0);
   /*Call to "glRasterPos2i(0,0)" assures that the image will be
  drawn in the window starting at the lower left corner (pixel 0 on scanline 0).*/
  glPixelStorei(GL_UNPACK_ALIGNMENT,1);
  glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, pixmap);
  /*Procedure, "glDrawPixels()" that takes an image pixmap and
  displays it in the graphics window.*/

   /*The width and height parameters to "glDrawPixels()" specify the width, in pixels,
   of a scanline, and the height of the image, in the number of scanlines.*/

   /*The GL_RGB parameter indicates that the pixels are stored as RGB
   quadruples, with color primaries stored in the order red, green and blue.*/

   /*GL_UNSIGNED_BYTE parameter indicates that each color primary is
  stored in a single byte and treated as an unsigned number between zero
  and 255.*/
  glFlush();
}
static void processMouse(int button, int state, int x, int y)
{
  if(state == GLUT_UP)
  exit(0);               // Exit on mouse click.
}
static void init(void)
{
  glClearColor(1,1,1,1); // Set background color.
}

// =============================================================================
// main() Program Entry
// =============================================================================
int main(int argc, char *argv[])
{

  //initialize the global variables
  width = 300;
  height = 300;
  pixmap = new unsigned char[width * height * 3];  //Do you know why "3" is used?

  //Our function for setting our "1D" array of pixel values for our pixmap.
  type = argv[1];
  setPixels(argc, argv);

  // OpenGL Commands:
  // Once "glutMainLoop" is executed, the program loops indefinitely to all
  // glut functions.  
  glutInit(&argc, argv);
  glutInitWindowPosition(100, 100); // Where the window will display on-screen.
  glutInitWindowSize(width, height);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutCreateWindow("Project 01");
  init();
  glutReshapeFunc(windowResize);
   //This is the function where display takes place.
  glutDisplayFunc(windowDisplay);
  glutMouseFunc(processMouse);
  glutMainLoop();

  return 0; //This line never gets reached. We use it because "main" is type int.
}
