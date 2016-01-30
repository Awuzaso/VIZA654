// =============================================================================
// Template Program for VIZA654/CSCE646 at Texas A&M University
// Created by Ariel Chisholm
// 09.01.2009
//
// This file is supplied with an associated makefile. Put both files in the same
// directory, navigate to that directory from the Linux shell, and type 'make'.
// This will create a program called 'ppmview' that you can run by entering
// 'ppmview' as a command in the shell. The program will display a small white
// pixmap. Clicking on the pixmap display window will close the program.
//
// This template program is designed to help you get jump-started on your first
// ppmview assignment. If you are new to programming in Linux, there is an
// excellent introduction to makefile structure and the gcc compiler here:
//
// http://www.cs.txstate.edu/labs/tutorials/tut_docs/Linux_Prog_Environment.pdf
//
// For viewing and editing code, Gedit is a good all-purpose text editor
// available on the lab's Linux systems. You can find it on the main GNOME
// menu under Debian>Apps>Editors.
// =============================================================================

// =============================================================================
// [ppmview.cpp]
// [Osazuwa Okundaye]
// [9/19/14]
// To view ".ppm".
// [./ppmview input.ppm]
// To view and save ".ppm". 
// [./ppmview input.ppm output.ppm]
//
// Always put a comment block like this at the top of your source files. You can
// see in the prior comment block my own use of this structure to document the
// origin and purpose of this template file.
// =============================================================================

// =============================================================================
// For all your projects, please adopt a consistent, readable programming style.
// Specifically pay attention to your maximum line lengths and indentation
// levels. A variable maximum line length or indentation level will almost
// always make your code unnecessarily difficult to read.
//
// Google (you may have heard of them) wisely mandates in their own C++ style
// guide a maximum line length of 80 characters, and a indentation level of two
// spaces (no tabs, just as in this document). This a very good coding style
// and I recommend you adopt it unless you have already developed a readable and
// consistent style of your own.
// =============================================================================

#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include <stdio.h>

using namespace std;

// =============================================================================
// These variables will store the input ppm image's width, height, and color
// depth values read in from the ppm header.
// =============================================================================
int width, height, maxcolor;
FILE *input_fileRead, *input_fileWrite;
string format;
int x, y;
int pixel;
unsigned char red;
unsigned char green;
unsigned char blue;
char rgb[3];
// =============================================================================
// You need 1 byte to store the information in an 8-bit color channel, and an
// unsigned char provides 1 byte. Use an unsigned char array to store the rgb
// pixmap data. glDrawPixels() requires an array of bytes in the order red,
// green, blue, red, green, blue, etc... , but you can also use the order red,
// green, blue, alpha, red, green, blue, alpha, etc... , if you want to give
// each pixel an alpha channel. Just make sure to change GL_RGB to GL_RGBA in
// glDrawPixels(); and GLUT_RGB to GLUT_RGBA in glutInitDisplayMode();
// =============================================================================
unsigned char *pixmap;
// =============================================================================
// You'll need to modify these functions to read and write pixmaps from ppm
// files. Here writePPM() does nothing and readPPM() just creates an empty
// white pixmap. Remember when you modify these function that OpenGL needs a
// pixmap with row positions reversed (going from bottom to top instead of
// from top to bottom). You may want to modify these functions' interfaces to
// to take arguments like char or FILE pointers so you can pass in input_fileReads
// or open file streams.
// =============================================================================
///////////////////////////////////
/*Function for writing new file.*/
//////////////////////////////////
void readPPM(FILE *input_fileRead){
	//Variables
	char magicNumber[2];
	char ch;		
	char comment;

	/*With function "fscanf" we read the input file and store its
	contents within the 2 character array of magic number.*/
	fscanf(input_fileRead, "%s", magicNumber);
	
	/*If the contents of character array, "magic number" prove
	to fall under the designation of "P6", we proceed with reading
	the file.*/
	if((magicNumber[0] == 'P') && (magicNumber[1] == '6')){
		/*Parse through the first two characters of the file.*/
		ch=fgetc(input_fileRead);		
		ch =fgetc(input_fileRead);
		/*We do this to read over comments.We read comments if there
		are "#" characters present.*/
		while(ch == '#'){
			/*If a "\n" character is read, we are at the end of comment line.
			A line break is introduced.*/
			/*if(comment == '#'){
				cout << endl;
				ch = comment;
				comment=fgetc(input_fileRead);
				
			}		
			else{
			comment = fgetc(input_fileRead);
			cout << comment;
			}*/

			
			if(comment == '\n'){
				
				ch = fgetc(input_fileRead);
				cout << endl;
			}		
			else{
			comment = fgetc(input_fileRead);
			cout << comment;
			}

		}
	/*Put back the last character so we can start at proper position.*/
	ungetc(ch, input_fileRead);//Put back last character.
	/*we are reading the values for width,height and maxcolor and placing
	them within their variables.*/
	fscanf(input_fileRead, "%d %d %d", &width, &height, &maxcolor);
	/*Our output.*/
	cout << "width = " << width << "" << " height = " << height << "" << " maxcolor = " << maxcolor << "" << endl;
	}
	/*Scenario where the inputfile is an invalid format.*/
	else{
		cout << "Incorrect file format. Please try again." << endl;
		exit(0);
	}
  	
}
///////////////////////////////////////////
/*Function for displaying file contents.*/
//////////////////////////////////////////
void displayPPM(FILE * input_fileRead){ 
  
	fgetc(input_fileRead);
    
  pixmap = new unsigned char[width * height * 3];


  for(y = height-1; y >= 0; y--){
    for(x = 0; x < width; x++){
      

      pixel = (y * width + x) * 3; 
        /*We grab the values from the stream
	and place them within the character stream*/
	/*red = fgetc(input_fileRead);
	green = fgetc(input_fileRead);
	blue = fgetc(input_fileRead);*/

	/*Pixel value is placed within pixmap and incremented subsequently.*/
      pixmap[pixel++] = fgetc(input_fileRead);
	/*Pixel value is placed within pixmap and incremented subsequently.*/    
      pixmap[pixel++] = fgetc(input_fileRead);
	/*Pixel value is placed within pixmap.*/
      pixmap[pixel] = fgetc(input_fileRead);


	

    }
  }
}
///////////////////////////////////
/*Function for writing new file.*/
///////////////////////////////////
void writePPM(FILE *input_fileWrite){
    
       string input;
       
       char choice;
       fprintf(input_fileWrite, "P6\n");
	/*Write to new file the "magic number" 
	designation and introduce linebreak.*/ 
       /*cout << "Insert a message?Type 'y' to do so or 'n' to continue." << endl;
       cin >> choice;
       if(choice == 'y'){
		cout << "Please type message." << endl;
		cin.get(input,256);
		cout << input << endl;
		//fprintf(input_fileWrite,"#%s\n",input);
	}*/

       fprintf(input_fileWrite, "%d %d\n", width, height);
	/*Write to new file the the width and 
	height and introduce linebreak.*/ 
       fprintf(input_fileWrite, "%d", maxcolor);

	

  

   cout << "Want to see something interesting?Type 'y' for it."<< endl;
   cin>>choice;
  /*Note that we reverse how y values are placed in file given
  the differences between how images are displayed in OpenGL vs
  how values of images are arranged.*/ 
  for(y = height-1; y >= 0; y--) {
    for(x = 0; x < width; x++) {
      
      /*Specifying pixel.*/ 
      pixel = (y * width + x) * 3; 
       
      red = pixmap[pixel++];	 
      green = pixmap[pixel++];   	
      blue = pixmap[pixel];
      
      
      if(choice == 'y'){
	      fputc(blue,input_fileWrite);
	      fputc(blue,input_fileWrite);
	      fputc(blue,input_fileWrite);
      }
      else{
	      fputc(blue,input_fileWrite);
	      fputc(red,input_fileWrite);
	      fputc(green,input_fileWrite);
      }
	
      


    }
  }
}

//////////////////////////////////////////////////
/*Function for handling command line arguments.*/
/////////////////////////////////////////////////
void commandLine(int argc, char *argv[]){
	

	//Scenario where less than two arguments are supplied by the user.

	//NOTE: Arguments: input_input_fileRead output_input_fileRead 
	if( argc < 2){
		cout << "Incorrect number of arguments supplied to program." << endl;
		cout << "Now closing." << endl;
		exit(0);
	}
	//Scenario for reading and displaying from file.
	else if(argc == 2){
		input_fileRead = fopen(argv[1],"r");
		cout << "These are the contents of file, " << argv[1] << endl;
		readPPM(input_fileRead);
		displayPPM(input_fileRead);
	}
	//Scenario for reading, displaying and copying from file.
	else if(argc == 3){
		input_fileRead = fopen(argv[1],"r");
		input_fileWrite = fopen(argv[2],"w");		
		cout << "These are the contents of file, " << argv[1] << endl;
		readPPM(input_fileRead);
		displayPPM(input_fileRead);
		cout << "Now saving file, " << argv[1] << " to " << argv[2] << " ." << endl;
		writePPM(input_fileWrite);
		
	}
}
// =============================================================================
// OpenGL Display and Mouse Processing Functions.
//
// You can read up on OpenGL and modify these functions, as well as the commands
// in main(), to perform more sophisticated display or GUI behavior. This code
// will service the bare minimum display needs for most assignments.
// =============================================================================
static void resize(int w, int h)
{   
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0,(w/2),0,(h/2),0,1); 
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity() ;
}
static void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glRasterPos2i(0,0);
  glPixelStorei(GL_UNPACK_ALIGNMENT,1);
  glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, pixmap);
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
  // Check command line arguments and read in the input_fileRead, then call readPPM().
  commandLine(argc, argv);
  






  // OpenGL commands
  glutInit(&argc, argv);
  glutInitWindowPosition(100, 100); // Where the window will display on-screen.
  glutInitWindowSize(width, height);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutCreateWindow(argv[1]);
  init();
  glutReshapeFunc(resize);
  glutDisplayFunc(display);
  glutMouseFunc(processMouse);
  glutMainLoop();

  // Check command line arguments and read in the output input_fileRead if present.
  // Then call writePPM() if necessary.

  return 0;
}

// =============================================================================
// GENERAL RECOMMENDATIONS AND SOLUTIONS TO COMMON PROBLEMS
//
// Use FILE, fopen, fclose, fscanf, fprintf, fgetc, and fputc to construct
// the readPPM and writePPM functions. The isspace() function from ctype.h
// is also very useful. You can learn about basic C file I/O issues in the
// excellent Wikipedia entry here:
//
// http://en.wikipedia.org/wiki/C_file_input/output
//
// Pay special attention to the section on the "The EOF Pitfall". Values
// returned from fgetc should be stored in an int, not a char.
//
// You can make more sophisticated versions of these functions using the C++
// <fstream> library and cin/cout. This is probably overkill for the ppm
// utilities you're creating in this class, unless you are already comfortable
// with the C++ way of doing things.
//
// If you stick with a more C-style approach, I strongly recommend you use
// fgetc and fputc to test for the P6 'magic number' bytes and to skip over
// any comment lines. When you've finished skipping over comments, scan-in
// the image width, height and color depth using this line:
//
//      fscanf(imagefile, "%d %d %d", &width, &height, &maxcolor);
//
// Then use this line to grab the last newline character after the maxcolor byte:
//
//      fgetc(imagefile);
//
// after which I recommend using fgetc to read in color channel byte values.
//
// This method is proven and works well. You should adhere to it in your own
// program unless you thoroughly test your own alternate methods.
//
//
// *** IMPORTANT ***
//
// DON'T DO THIS:
//
//      fscanf(imagefile, "%d %d\n %d\n", &width, &height, &maxcolor);
//
// OR THIS:
//
//      fscanf(imagefile, "%d %d %d\n", &width, &height, &maxcolor);
//
// OR THIS:
//
//      fscanf(imagefile, "\n", &ch);
//
// to scan in the last newline after the maxcolor byte.
//
// fscanf is not required to only read in one char byte for each explicit
// newline scan. This is because C binary I/O allows a newline character to
// sometimes be output as two characters, depending on the target output file
// type and other system conventions, and likewise be identified during scan in
// from two char bytes of an input file. fscanf may scan the newline and also
// the following first red color channel byte, if the hex value for that red
// color channel byte corresponds to a character that fscanf interprets as part
// of the newline. This definitely happens if the first red color channel has
// the hex value 0B (which is the hex value for a vertical tab character), but
// fscanf may be vulnerable to other newline-trailing hex values as well.
// If you must use fscanf to read in the last newline, you need to instead
// explicitely instruct fscanf to read in a single char:
//
// fscanf(imagefile, "%c", &ch);
//
// But fgetc(imagefile) will work fine too.
//
// Don't attempt to search for and skip over white space or comments lines after
// the newline that follows the maxcolor byte - there should never be any such
// chunks of data in a valid ppm file. At best you will add useless code to
// your project; at worst you will generate the same problem as the fscanf issue
// above - you may accidentally scan the first red color channel byte, and
// possibly following bytes as well, if the hex values for these bytes
// correspond to whitespace or comment line characters that you're skipping.
//
//
// For image output I recommend you use fprintf to write out the ppm header
// data:
//
//     fprintf(outfile, "P6\n");
//     fprintf(outfile, "%d %d\n", width, height);
//     fprintf(outfile, "255\n");
//
// and then fputc to output color channel byte values.
// =============================================================================