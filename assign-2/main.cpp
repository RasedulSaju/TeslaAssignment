#include<GL/glut.h>
#include<math.h>
#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;

float x = 1;
bool b = false;
int refPoints = -1;
// view port
float xmin , ymin , xmax , ymax ;
// input line
float ax, ay, bx, by;
// length width
float minus_x=-500.0;
float plus_x=500.0; //
float minus_y= -500.0;
float plus_y= 500.0; //

const int TOP = 1;
const int BOTTOM = 2;
const int RIGHT = 4;
const int LEFT = 8;

void tr(){
        //x min OK ?
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINES);
        glVertex3f(xmin,minus_y,0);
        glVertex3f(xmin,plus_y,0);
        //x max OK ?
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINES);
        glVertex3f(xmax,minus_y,0);
        glVertex3f(xmax,plus_y,0);
        //y min OK ?
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINES);
        glVertex3f(minus_x,ymin,0);
        glVertex3f(plus_x,ymin,0);
        // y max OK ?
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINES);
        glVertex3f(minus_x,ymax,0);
        glVertex3f(plus_x,ymax,0);
        glEnd();

    //glVertex2f(6, 4);
    //glEnd();
}

int ComputeOutCode(float x, float y){
    int code = 0;
    if (y > ymax) //above the clip window
        code |= TOP;
    else if (y < ymin) //below the clip window
        code |= BOTTOM;
    if (x > xmax) //to the right of clip window
        code |= RIGHT;
    else if (x < xmin) //to the left of clip window
        code |= LEFT;
    return code;
}
void CSA(float x1, float y1, float x2, float y2)
{
    //Outcodes for P0, P1, and whatever point lies outside the clip rectangle
    int outcode0, outcode1, outcodeOut;
    bool accept = false, done = false;
    //compute outcodes
    outcode0 = ComputeOutCode(x1, y1);
    outcode1 = ComputeOutCode(x2, y2);
    do
    {
        if (!(outcode0 | outcode1)) //
        {
            accept = true;

            done = true;
        }
        else if (outcode0 & outcode1) // Trivially reject
            done = true;
        else
        { //failed both tests, so calculate the line segment to clip from an
            // outside point to an intersection with clip edge
            float x, y;
            //At least one endpoint is outside the clip rectangle; pick it.
            outcodeOut = outcode0 ? outcode0 : outcode1;
            //Now find the intersection point;
            //use formulas y = y1 + slope * (x - x1), x = x1 + (1/slope)* (y - y1)
            if (outcodeOut &BOTTOM ) //point is above the clip rectangle
            {
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;
            }
            else if (outcodeOut &TOP ) //point is below the clip rectangle
            {
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;
            }
            else if (outcodeOut & RIGHT) //point is to the right of clip rectangl
            {
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;
            }
            else //point is to the left of clip rectangle
            {
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);

                x = xmin;
            }
            //Now we move outside point to intersection point to clip
            //and gets ready for next pass.
            if (outcodeOut == outcode0)
            {
                x1 = x;
                y1 = y;
                outcode0 = ComputeOutCode(x1, y1);
            }
            else
            {
                x2 = x;
                y2 = y;
                outcode1 = ComputeOutCode(x2, y2);
            }
        }
    } while (!done);
    if (accept)
    {
        //result
        if(x==6 || x>6){
            glColor3f(0, 1, 0);
            glBegin(GL_LINES);
            glVertex2d(x1, y1);
            glVertex2d(x2, y2);

            glEnd();
        }
        //printf("x1=%f, x2=%f, y1=%f, y2=%f", &x1, &x2, &y1, &y2);
    }
}
void CohenSutherland()
{
    //glClear(GL_COLOR_BUFFER_BIT);
    //glLoadIdentity();
    //drawClippingWindow();
    glPointSize(5);

        //ax = 50;
        //ay = 50;
        //bx = 250;
        //by = 250;

    if (refPoints == -1)
    {
        //reference points

        //reference line
        if(x>3 && x<6){
            glBegin(GL_LINES);
            glColor3f(1, 1, 0);
            glVertex2f(ax, ay);
            glVertex2f(bx, by);
            glEnd();
        }

    }

    CSA(ax, ay, bx, by);

    glutSwapBuffers();
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    if(x<=3){
        tr();
    }
    if(x>3){
        tr();
        CohenSutherland();
    }
    /*if(x>6 && b!=true && x<=10){
        //glPushMatrix();
        tr2();
        //glPopMatrix();
        printf("%.6f\n",x);
        b = true;
    }*/

    glFlush();
}

void reshape(int h, int w)
{
    //view port
    glViewport(0, 0, w, h);
    //projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-500.0,500.0, -500.0,500.0, -50.0,50.0);
    glMatrixMode(GL_MODELVIEW);
}

void init ()
{
    glClearColor(0, 0, 0, 0);
}

void timer(int){
    glutPostRedisplay();
    glutTimerFunc(2000, timer, 0);
    x++;
}

int main (int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(720, 720);
    glutCreateWindow("Cohen Sutherland Line Clipping Algorithm");
    ifstream input;
    input.open("C:/Users/USER/Downloads/Assignment/assign-2/n.txt");// we have to provide full path. otherwise it will not open.
     if(input.fail()){                                                             // fail function checked.
        cout<<"Failed!"<<endl;
     }
     cout<<"File read from =  C:/Users/USER/Downloads/Assignment/assign-2/n.txt"<<endl;
    string value;
    int c = 0,s,i;
        while(input>>value){
                c++;
                if(c<=4){
                    if(c==1){
                        stringstream s(value);
                        s >> xmin;
                        cout<<"Xmin = "<<xmin<<endl;
                    }
                    else if(c==3){
                        stringstream s(value);
                        s >> xmax;
                       cout<<"Xmax = "<<xmax<<endl;
                    }
                    else if(c==2){
                        stringstream s(value);
                        s >> ymin;
                        cout<<"ymin = "<<ymin<<endl;
                    }
                    else{
                        stringstream s(value);
                        s >> ymax;
                        cout<<"ymax = "<<ymin<<endl;
                    }
                }
                if(c==5){
                    stringstream s(value);
                        s >> ax;
                        cout<<"Ax = "<<ax<<endl;
                }
                if(c==6){
                    stringstream s(value);
                        s >> ay;
                        cout<<"Ay = "<<ay<<endl;
                }
                if(c==7){
                    stringstream s(value);
                        s >> bx;
                        cout<<"Bx = "<<bx<<endl;
                }
                if(c==8){
                    stringstream s(value);
                        s >> by;
                        cout<<"By = "<<by<<endl;
                }

        }
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0,timer,0);
    glutMainLoop();
}
