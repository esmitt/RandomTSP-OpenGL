#include <stdlib.h>

#include <GL/glut.h>

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define WINDOW_WIDTH  600
#define WINDOW_HEIGHT 600

//point data structure
typedef struct{
	int x, y;
}point;

point* arrayCities = NULL;	//to store the cities positions
int nCities;								//number of cities
int* position = NULL;				//order to visit the cities
double** distances;					//a pre-computed array of distances between cities (to speedup)
double initialDistance;			//a value to print at the end of the running

//
// To display onto window using OpenGL commands
//
void display()
{
	//
	// clear window to black
	//
	glClearColor( 0, 0 , 0 , 0 );
	glClear( GL_COLOR_BUFFER_BIT );
	glLoadIdentity();
	//orange color
	glColor3ub(200, 100, 15);
	
	//draw path
	glBegin(GL_LINE_LOOP);
	for (int k = 0; k < nCities; k++)
		glVertex2i(arrayCities[position[k]].x, arrayCities[position[k]].y);
	glEnd();

	//draw points, aka cities
	glPointSize(3);
	//light-gray color
	glColor3ub(200, 200, 200);
	for (int k = 0; k < nCities; k++)
	{
		glBegin(GL_POINTS);
			glVertex2i(arrayCities[k].x, arrayCities[k].y);
		glEnd();
	}
	glutSwapBuffers();
}

//return the total distance from initial city to the last one + last one to the initial one
double computeDistance()
{
	double distancePath = 0.0;
	for (int k = 0; k < nCities - 1; k++)
		distancePath += distances[position[k]][position[k + 1]];
	distancePath += distances[position[nCities - 1]][position[0]];
	return distancePath;
}

//swap 2 different random position in the path
// if distance is less, then swap, otherwise keep it
void Swap2Elements(int* e1, int *e2)
{
	do
	{
		*e1 = rand() % nCities;
		*e2 = rand() % nCities;
	} while (*e1 == *e2);
	int temp = position[*e1];
	position[*e1] = position[*e2];
	position[*e2] = temp;
}

// performs the iterations (are 25.000)
// a limit is added to avoid finish all iterations 9
void getShortestPath()
{
	int k = 0;
	int limit = 10000;
	while (k < 25000 && limit > 0)
	{
		int e1, e2;
		double d1 = computeDistance();
		Swap2Elements(&e1, &e2);
		double d2 = computeDistance();
		if (d2 > d1)
		{
			//revert the swaps
			int temp = position[e1];
			position[e1] = position[e2];
			position[e2] = temp;
			//std::cout << "No swap" << std::endl;
			limit--;
		}
		else
			printf("Distance iteration-%d : %lf\n", k,computeDistance());
		k++;
	}
}


//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y )
{
   // exit when ESC is pressed.
	if (key == 27)
		exit(0);
	 else if (key == 'a')
	 {
		 getShortestPath();
		 printf("Initial distance: %lf; Shortest path: %lf\n", initialDistance, computeDistance());
	 }
	 else if (key == 's')
	 {
			int e1, e2;
			double d1 = computeDistance();
			Swap2Elements(&e1, &e2);
			double d2 = computeDistance();
			if (d2 > d1)
			{
				//revert the swaps
				int temp = position[e1];
				position[e1] = position[e2];
				position[e2] = temp;
			}
			printf("Distance: %lf \n", computeDistance());

	 }
    // to refresh the window it calls display() function
   glutPostRedisplay() ;
}


//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize( int w, int h )
{
	glViewport( 0,0,w,h) ;
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( -w/2, w/2, -h/2, h/2, -1, 1);
	glMatrixMode( GL_MODELVIEW);
	glLoadIdentity();
}

// compute the euclidean distance between two points
double distanceFinder(point a, point b)
{
	return sqrt(pow(a.x - b.x, 2.0) + pow(a.y - b.y, 2.0));
}

//initialize the opengl setup and variables
void Init(int size) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	
	nCities = size;			// set the number of cities given by the user
	srand(time(NULL));	//to start each execution as different

	//dynamically create the arrays
	//arrayCities = new point[size];
	arrayCities = (point*)malloc(size * sizeof(point));
	position = (int*)malloc(size * sizeof(int));
	distances = (double**)malloc(size * sizeof(double*));

	// place the cities on the screen
	for (int k = 0; k < size; k++)
	{
		distances[k] = (double*)malloc(size * sizeof(double));
		int ri = rand() % (WINDOW_WIDTH + 1);
		ri -= WINDOW_WIDTH / 2;
		arrayCities[k].x = ri;
		ri = rand() % (WINDOW_HEIGHT + 1);
		ri -= WINDOW_HEIGHT / 2;
		arrayCities[k].y = ri;
		position[k] = k;
	}

	//computes the distance from all cities to all cities
	for (int y = 0; y < size; y++)
		for (int x = 0; x < size; x++)
			distances[x][y] = distanceFinder(arrayCities[x], arrayCities[y]);	//from city y to each x

	initialDistance = computeDistance();
	printf("Initial distance: %lf\n", initialDistance);
}

int main( int argc, char *argv[] )
{
	int n;
	printf("Please insert the number of cities [0,10000]: ");
	scanf("%d", &n);
	printf("\n");
	glutInit(&argc, argv );
	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow( "TSP Opengl" ) ;

	glutDisplayFunc( (void*)display ) ;
	glutIdleFunc((void*)display);
  glutReshapeFunc( onResize );
	//
	// keyboard registration
	//
	glutKeyboardFunc( onKeyDown ) ;
	Init(n);
	
	glutMainLoop();
	return 0;
}
