#include<windows.h>
#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#define pi 3.1415926535897932384626433

void init()
{
    // For displaying the window color
    glClearColor(0, 0, 0, 0);
    // Choosing the type of projection
    glColor3f(1,0,0);
    glMatrixMode(GL_PROJECTION);
    glPointSize(3);
    // for setting the transformation which here is 2D
    gluOrtho2D(0,600,-300,300);
}
float mod_sine(int n,float x, float L)//subtract fomr 200/pi
{
    float result =  400/((4*n*n-1)*pi)*cos(n*pi*x/L);
    return result;
}
float triangle(int n, float x, float L)//subtract from 1/2
{
    float result =  400/(n*pi)*sin(n*pi*x/L);
    return result;
}

float square(int n, float x, float L)
{
    float result =  400/((2*n-1)*pi)*sin((2*n-1)*pi*x/L);
    return result;
}
float fourier_series(float (*f)(int,float,float),float x,float L,int no_of_iteration){
    float result=0;
    for(int i=1;i<=no_of_iteration;i++){
        result += f(i,x,L);
    }
    return 1/2- result;
}



void display()
{
    float x;
    float tempi=0,tempx=0;
    for(float i = 0;i<600;i+=1){
        glClear(GL_COLOR_BUFFER_BIT); // Clear display window
        glBegin(GL_LINES);
            glVertex2f(0,0);
            glVertex2f(600,0);
        glEnd();
        for(float j = 0;j<i;j+=1)
        {
            x= fourier_series(triangle,j,120,4);
            if(j!=0){
                glBegin(GL_LINES);
                    glVertex2f(tempi,tempx);
                    glVertex2f(j,x);
                glEnd();
            }
            tempi= j;tempx=x;
            printf("i = %f, x = %f\n",j,x);
        }
        glFlush();
    }

}

int main(int agrc, char ** argv)
{
    // Initialize GLUT
    glutInit(&agrc, argv);
    // Set display mode
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    // Set top - left display window position.
    glutInitWindowPosition(100, 100);
    // Set display window width and height
    glutInitWindowSize(600, 600);
    // Create display window with the given title
    glutCreateWindow("Fourier Series");
    // Execute initialization procedure
    init();
    // Send graphics to display window
    glutDisplayFunc(display);
    // Display everything and wait.
    glutMainLoop();
}

