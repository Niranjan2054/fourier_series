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
    gluOrtho2D(-400,1000,-300,300);
}
float mod_sine(int n,float x, float L)//subtract fomr 200/pi
{
    float result =  400/((4*n*n-1)*pi)*cos(n*pi*x/L);
    return result;
}
float mod_sine1(int n,float x, float L)//subtract fomr 200/pi
{
    float result =  400/((4*n*n-1)*pi)*sin(n*pi*x/L);
    return result;
}
float triangle(int n, float x, float L)//subtract from 1/2
{
    float result =  400/(n*pi)*sin(n*pi*x/L);
    return result;
}
float triangle1(int n, float x, float L)//subtract from 1/2
{
    float result =  400/(n*pi)*cos(n*pi*x/L);
    return result;
}

float square(int n, float x, float L)
{
    float result =  400/((2*n-1)*pi)*sin((2*n-1)*pi*x/L);
    return result;
}
float square1(int n, float x, float L)
{
    float result =  400/((2*n-1)*pi)*cos((2*n-1)*pi*x/L);
    return result;
}

float fourier_series(float (*f)(int,float,float),float x,float L,int no_of_iteration){
    float result=0;
    for(int i=1;i<=no_of_iteration;i++){
        result += f(i,x,L);
    }
    return 1/2- result;
}
void drawCircle(float (*f)(int,float,float),float L,int n,int xc, int yc)
{
    int x,y;
    glBegin(GL_POINTS);
    for(float i = 0;i<2*L;i+=0.075){
        y = f(n,i,L);
        x = square1(n,i,L);
//            printf("%f %f\n",x,y);
        glVertex2f(x+xc,y+yc);
    }
    glEnd();
}

float drawFourierCircle(float (*f)(int,float,float),float L,int no_of_iteration,float x)
{
    int x_init=0,y_init=0;
    int xc, yc;
    for(int n=1;n<=no_of_iteration+1;n++){
        yc = fourier_series(f,x,L,n-1);
        xc = fourier_series(square1,x,L,n-1);
        if(n<=no_of_iteration){
            drawCircle(f,L,n,xc,yc);
        }
        if(n!=1){
            glBegin(GL_LINES);
                glVertex2f(x_init,y_init);
                glVertex2f(xc,yc);
            glEnd();
        }
        x_init = xc;
        y_init = yc;
    }
    glBegin(GL_LINES);
        glVertex2f(x_init,y_init);
        glVertex2f(x+300,y_init);
    glEnd();

}
void display()
{
    float x;
    float tempi=0,tempx=0;
    int iteration = 5;
    int offset= 300;
    int time_period=120;
    for(float i = 0;i<600;i+=0.1){
        glClear(GL_COLOR_BUFFER_BIT); // Clear display window


        glBegin(GL_LINES);
            glVertex2f(0+offset,0);
            glVertex2f(600+offset,0);
        glEnd();
        for(float j = 0;j<i;j+=0.02)
        {

            x= fourier_series(square,j,time_period,iteration);

            if(j!=0){
                glColor3f(i/600,j/i,x/200);
                glBegin(GL_LINES);
                    glVertex2f(tempi+offset,tempx);
                    glVertex2f(j+offset,x);
                glEnd();
            }
            tempi= j;tempx=x;
        }
        drawFourierCircle(square,time_period,iteration,i);
        printf("i = %f, x = %f\n",i,x);
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
    glutInitWindowSize(1400, 600);
    // Create display window with the given title
    glutCreateWindow("Fourier Series");
    // Execute initialization procedure
    init();
    // Send graphics to display window
    glutDisplayFunc(display);
    // Display everything and wait.
    glutMainLoop();
}

