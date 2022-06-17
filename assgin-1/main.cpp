#include <GL/glut.h>
#include <math.h>
#include<stdio.h>
#define PI 3.1416
#define window_height 1000 //Window Height and Width has been taken as a macro so that we can customize easily.
#define window_width 1000
#include<bits/stdc++.h>
using namespace std;
float minus_x=-500.0;
float plus_x=500.0; //
float minus_y= -500.0;
float plus_y= 500.0; //
float xmin,xmax,ymin,ymax;
string seq[4], s1, s2, s3, s4;

float TIME = 1;
// coordinate
float coordinate[100][2];
//initial data store
float coordinate1[100][2];
int node;


int drawaxes;

void left_clipping()
{
    float temp[100][2];
    float x1,y1,x2,y2;
    int j = 0,i;
    for(i=0; i<node; i++)
    {
        x1=coordinate[i][0];
        y1=coordinate[i][1];
        x2=coordinate[i+1][0];
        y2=coordinate[i+1][1];
        if(x1>=xmin&&x2>=xmin)
        {
            //in-in
            temp[j][0] = x2;
            temp[j][1] = y2;
            j++;
        }
        else if(x1<xmin&&x2<xmin)
        {
            //out out do nothing
        }
        else if(x1>xmin&&x2<=xmin)
        {
            //in-out
            float a1 = y1 - y2;
            float b1 = x2-x1;
            float c1 = y1*(x1-x2) - x1*(y1-y2);
            float a2 = 1;
            float b2 = 0;
            float c2 = -xmin;
            temp[j][0] = (b1*c2-b2*c1)/(a1*b2-a2*b1);
            temp[j][1] = (c1*a2 - c2*a1)/(a1*b2 - a2*b1);
            j++;

        }
        else if(x1<xmin&&x2>=xmin)
        {
            //out-in
            int flag = 0;
            float a1 = y1 - y2;
            float b1 = x2-x1;
            float c1 = y1*(x1-x2) - x1*(y1-y2);
            float a2 = 1;
            float b2 = 0;
            float c2 = -xmin;
            temp[j][0] = (b1*c2-b2*c1)/(a1*b2-a2*b1);
            temp[j][1] = (c1*a2 - c2*a1)/(a1*b2 - a2*b1);
            if(temp[j][0] == x2 && temp[j][1]==y2)
            {
                flag = -1;
            }
            j++;
            if(flag==0)
            {
                temp[j][0] = x2;
                temp[j][1] = y2;
                j++;
            }

        }
    }
    for(i=0; i<j; i++)
    {
        coordinate[i][0]=temp[i][0];
        coordinate[i][1]=temp[i][1];
    }
    coordinate[i][0]= coordinate[0][0];
    coordinate[i][1]= coordinate[0][1];
    node = j;

}
void right_clipping()
{
    float temp[100][2];
    float x1,y1,x2,y2;
    int j = 0,i;
    for(i=0; i<node; i++)
    {
        x1=coordinate[i][0];
        y1=coordinate[i][1];
        x2=coordinate[i+1][0];
        y2=coordinate[i+1][1];
        if(x1<=xmax&&x2<=xmax)
        {
            //in-in
            temp[j][0] = x2;
            temp[j][1] = y2;
            j++;
        }
        else if(x1>xmax&&x2>xmax)
        {
            //out out do nothing
        }
        else if(x1<xmax&&x2>=xmax)
        {
            //in-out
            float a1 = y1 - y2;
            float b1 = x2-x1;
            float c1 = y1*(x1-x2) - x1*(y1-y2);
            float a2 = 1;
            float b2 = 0;
            float c2 = -xmax;
            temp[j][0] = (b1*c2-b2*c1)/(a1*b2-a2*b1);
            temp[j][1] = (c1*a2 - c2*a1)/(a1*b2 - a2*b1);
            j++;

        }
        else if(x1>xmax&&x2<=xmax)
        {
            //out-in
            int flag = 0;
            float a1 = y1 - y2;
            float b1 = x2-x1;
            float c1 = y1*(x1-x2) - x1*(y1-y2);
            float a2 = 1;
            float b2 = 0;
            float c2 = -xmax;
            temp[j][0] = (b1*c2-b2*c1)/(a1*b2-a2*b1);
            temp[j][1] = (c1*a2 - c2*a1)/(a1*b2 - a2*b1);
            if(temp[j][0] == x2 && temp[j][1]==y2)
            {
                flag = -1;
            }
            j++;
            if(flag==0)
            {
                temp[j][0] = x2;
                temp[j][1] = y2;
                j++;
            }

        }
    }
    for(i=0; i<j; i++)
    {
        coordinate[i][0]=temp[i][0];
        coordinate[i][1]=temp[i][1];
    }
    coordinate[i][0]= coordinate[0][0];
    coordinate[i][1]= coordinate[0][1];
    node = j;

}
void top_clipping()
{
    float temp[100][2];
    float x1,y1,x2,y2;
    int j = 0,i;
    for(i=0; i<node; i++)
    {
        x1=coordinate[i][0];
        y1=coordinate[i][1];
        x2=coordinate[i+1][0];
        y2=coordinate[i+1][1];
        if(y1<=ymax&&y2<=ymax)
        {
            //in-in
            temp[j][0] = x2;
            temp[j][1] = y2;
            j++;
        }
        else if(y1>ymax&&y2>ymax)
        {
            //out out do nothing
        }
        else if(y1<ymax&&y2>=ymax)
        {
            //in-out
            float a1 = y1 - y2;
            float b1 = x2-x1;
            float c1 = y1*(x1-x2) - x1*(y1-y2);
            float a2 = 0;
            float b2 = 1;
            float c2 = -ymax;
            temp[j][0] = (b1*c2-b2*c1)/(a1*b2-a2*b1);
            temp[j][1] = (c1*a2 - c2*a1)/(a1*b2 - a2*b1);
            j++;

        }
        else if(y1>ymax&&y2<=ymax)
        {
            //out-in
            int flag = 0;
            float a1 = y1 - y2;
            float b1 = x2-x1;
            float c1 = y1*(x1-x2) - x1*(y1-y2);
            float a2 = 0;
            float b2 = 1;
            float c2 = -ymax;
            temp[j][0] = (b1*c2-b2*c1)/(a1*b2-a2*b1);
            temp[j][1] = (c1*a2 - c2*a1)/(a1*b2 - a2*b1);
            if(temp[j][0] == x2 && temp[j][1]==y2)
            {
                flag = -1;
            }
            j++;
            if(flag==0)
            {
                temp[j][0] = x2;
                temp[j][1] = y2;
                j++;
            }

        }
    }
    for(i=0; i<j; i++)
    {
        coordinate[i][0]=temp[i][0];
        coordinate[i][1]=temp[i][1];
    }
    coordinate[i][0]= coordinate[0][0];
    coordinate[i][1]= coordinate[0][1];
    node = j;

}
void bottom_clipping()
{
    float temp[100][2];
    float x1,y1,x2,y2;
    int j = 0,i;
    for(i=0; i<node; i++)
    {
        x1=coordinate[i][0];
        y1=coordinate[i][1];
        x2=coordinate[i+1][0];
        y2=coordinate[i+1][1];
        if(y1>=ymin&&y2>=ymin)
        {
            //in-in
            temp[j][0] = x2;
            temp[j][1] = y2;
            j++;
        }
        else if(y1<ymin&&y2<ymin)
        {
            //out out do nothing
        }
        else if(y1>ymin&&y2<=ymin)
        {
            //in-out
            float a1 = y1 - y2;
            float b1 = x2-x1;
            float c1 = y1*(x1-x2) - x1*(y1-y2);
            float a2 = 0;
            float b2 = 1;
            float c2 = -ymin;
            temp[j][0] = (b1*c2-b2*c1)/(a1*b2-a2*b1);
            temp[j][1] = (c1*a2 - c2*a1)/(a1*b2 - a2*b1);
            j++;

        }
        else if(y1<ymin&&y2>=ymin)
        {
            //out-in
            int flag = 0;
            float a1 = y1 - y2;
            float b1 = x2-x1;
            float c1 = y1*(x1-x2) - x1*(y1-y2);
            float a2 = 0;
            float b2 = 1;
            float c2 = -ymin;
            temp[j][0] = (b1*c2-b2*c1)/(a1*b2-a2*b1);
            temp[j][1] = (c1*a2 - c2*a1)/(a1*b2 - a2*b1);
            if(temp[j][0] == x2 && temp[j][1]==y2)
            {
                flag = -1;
            }
            j++;
            if(flag==0)
            {
                temp[j][0] = x2;
                temp[j][1] = y2;
                j++;
            }

        }
    }
    for(i=0; i<j; i++)
    {
        coordinate[i][0]=temp[i][0];
        coordinate[i][1]=temp[i][1];
    }
    coordinate[i][0]= coordinate[0][0];
    coordinate[i][1]= coordinate[0][1];
    node = j;

}
// final clipped region print
void print(){
    int x,y;
    bool b1 , b2 = false;
    cout<<endl<<"New sequence :";
    for(int i = 0; i<node; i++){
        cout<<" (";
        // Here full design
        for(int j = 0; j<2; j++){
            if(j==1){
                y = coordinate[i][j];
                b1 = true;
            }
            else{
                x =coordinate[i][j];
                b2 = true;
            }
            if(b1==true && b2==true){
             cout<<x;
             cout<<",";
             cout<<y;
             b1  = false;
             b2 = false;
            }
        }
        cout<<")";
        //  cout<<endl;
    }
}

// axes draw
void drawAxes(){
    if(drawaxes==1){
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
    }
}
// original polygon
void input(){
    int x,y;
    glColor3f(1.0, 1.0, 1.0);
    bool b1 , b2 = false;
    glBegin(GL_POLYGON);
    for(int i = 0; i<node; i++){
            //cout<<"P"<<i+1<<": (";
            for(int j = 0; j<2; j++){
                if(j==1){
                    y = coordinate1[i][j];
                    b1 = true;
                    if(b1==true && b2==true){
                        glVertex2f(x,y);
                        //cout<<endl;
                        //cout<<j<<endl;
                        //cout<<" - under the main object draw ";
                        //cout<<x;
                        //cout<<" , ";
                        //cout<<y;
                        b1  = false;
                        b2 = false;
                    }
                }
                else{
                    x =coordinate1[i][j];
                    b2 = true;
                }

            }
    }

    glEnd();
}
// after each clip it will call this function
void clip(){
    int x,y;
    glColor3f(0.0, 1.0, 0.0);
    bool b1 , b2 = false;
    glBegin(GL_POLYGON);
    for(int i = 0; i<node; i++){
            //cout<<"P"<<i+1<<": (";
            for(int j = 0; j<2; j++){
                if(j==1){
                    y = coordinate[i][j];
                    b1 = true;
                    if(b1==true && b2==true){
                        glVertex2f(x,y);
                        //cout<<endl;
                        //cout<<j<<endl;
                        //cout<<" - under the main object draw ";
                        //cout<<x;
                        //cout<<" , ";
                        //cout<<y;
                        b1  = false;
                        b2 = false;
                    }
                }
                else{
                    x =coordinate[i][j];
                    b2 = true;
                }
            }
    }

    glEnd();
}
// timer function
void timer(int){
    glutPostRedisplay();
    glutTimerFunc(2000, timer, 0);
    TIME++;
}


void init(void){
    drawaxes=1;   // if '0' then white , as well as for '10'.
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glOrtho(minus_x, plus_x, minus_y,plus_y, -50.0,50.0);
}
// clipping region first
void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    if(TIME>2 && TIME<4){
        input();//original polygon
    }

    drawAxes(); // clip rectangle

    if(TIME==4 || TIME>4){
       clip(); // clip polygon
    }
    glFlush();
}
// full polygon draw second

// left clip third

// right clip forth

// top clip fifth

// bottom clip sixth

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitWindowPosition (0, 0);
    glutInitWindowSize (window_width, window_height);
    glutCreateWindow ("Sutherland-Hodgman polygon clipping algorithm ");
    init();
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutTimerFunc(0,timer,0);


    ifstream input;
    //input.open("D:/Graphics Lab/assgin-1/n.txt");// we have to provide full path. otherwise it will not open.
    cout << "Select input file\n1. n.txt\n2. in-2.txt\n3. in-3.txt\n4. in-4.txt\n5. in-5.txt\n ";
    int s;
    cin >> s;

    switch(s){
        case 1:
            input.open("C:/Users/USER/Downloads/Assignment/assgin-1/n.txt");
            break;
        case 2:
            input.open("C:/Users/USER/Downloads/Assignment/assgin-1/in-2.txt");
            break;
        case 3:
            input.open("C:/Users/USER/Downloads/Assignment/assgin-1/in-3.txt");
            break;
        case 4:
            input.open("C:/Users/USER/Downloads/Assignment/assgin-1/in-4.txt");
            break;
        case 5:
            input.open("C:/Users/USER/Downloads/Assignment/assgin-1/in-5.txt");
            break;
    }
     if(input.fail()){                                                             // fail function checked.
        cout<<"Failed!"<<endl;
     }
    string value;
    int c = 0,i;
        while(input>>value){
                c++;
                if(c<=4){
                    if(c==1){
                        stringstream s(value);
                        s >> xmin;
                        cout<<"Xmin = "<<xmin<<endl;
                    }
                    else if(c==2){
                        stringstream s(value);
                        s >> xmax;
                       cout<<"Xmax = "<<xmax<<endl;
                    }
                    else if(c==3){
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
                // input the sequence

                else if(c>=5 && c<=8){
                    if(c==5){
                        seq[c-5] = value;
                        s1=seq[c-5];
                    }
                    else if(c==6){
                        seq[c-5]= value;
                        s2=seq[c-5];
                    }
                    else if(c==7){
                        seq[c-5] = value;
                        s3=seq[c-5];
                    }
                    else if(c==8){
                        seq[c-5] = value;
                        s4=seq[c-5];
                    }
                }
                // next work.
                else if(c>=5 && c<=8){
                    if(c==5){
                        seq[c-5] = value;
                        s1=seq[c-5];
                    }
                    else if(c==6){
                        seq[c-5]= value;
                        s2=seq[c-5];
                    }
                    else if(c==7){
                        seq[c-5] = value;
                        s3=seq[c-5];
                    }
                    else if(c==8){
                        seq[c-5] = value;
                        s4=seq[c-5];
                    }
                }
                else if(c==9){
                    stringstream s(value);
                    s >> node;
                    for( i = 0; i<node; i++){
                        for(int j = 0; j<2; j++){
                            float x = 0;
                            input>>value;
                            stringstream s(value);
                            s >> x;
                            coordinate[i][j] = x;
                            coordinate1[i][j] = x;
                        }
                    }
                }
        } // end of while.
        coordinate[i][0]= coordinate[0][0];
        coordinate[i][1]= coordinate[0][1];
        //extra word
        coordinate1[i][0]= coordinate1[0][0];
        coordinate1[i][1]= coordinate1[0][1];
        // clipping sequence print
        cout<<"Clipping edge sequence: "<<s1<<" "<<s2<<" "<<s3<<" "<<s4<<endl;
        // time to print the clipping region
        glutDisplayFunc(display);
        // no. of vertices
        for(int i = 0; i<node; i++){
            cout<<"P"<<i+1<<": (";
            for(int j = 0; j<2; j++){
                if(j==1){
                    cout<<coordinate[i][j];
                }
                else{
                    cout<<coordinate[i][j];
                    cout<<",";
                }
            }
            cout<<")";
            cout<<endl;
        }
        cout<<endl;
        //its time to call clipping functions
        //-----------------------------------------------------------------work start---------------
            for(i=0; i<4; i++){
            //if(!strcmp(seq[i],"L"))
            if(seq[i]=="L"){
                left_clipping();
                // display function call
                cout<<"Clipping with respect to LEFT edge... ";
                cout<<endl;
                print();
                clip();
                cout<<endl;
            }
            else if(seq[i]=="R"){
                right_clipping();
                // display function call
                cout<<endl;
                cout<<"Clipping with respect to Right edge... ";
                print();
                clip();
                cout<<endl;
            }
            else if(seq[i]=="T"){
                top_clipping();
                // display function call

                cout<<endl;
                cout<<"Clipping with respect to TOP edge... ";
                print();
                clip();
                cout<<endl;
            }
            else if(seq[i]=="B"){
                bottom_clipping();
                // display function call

                cout<<endl;
                cout<<"Clipping with respect to BOTTOM edge... ";
                cout<<endl;
                print();
                clip();
                cout<<endl;
            }
        }
        glutMainLoop();

        return 0;
}

