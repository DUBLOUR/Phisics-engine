#include<iostream>
#include<stdio.h>
#include<cmath>
#include<ctime>
using namespace std;
#define ld long double
#define sqr(x) (x)*(x)

const ld  G = 6.6740831e-11;    //Гравитационная константа, трогать не стоит!
const ld  MIN_MASS = 1e-3;      //Минимальный вес тела (кг)
const ld  MAX_MASS = 1e9;       //Максимальный вес тела (кг)
const int MAX_N = 100;          //Максимальное количество объектов (штук)
const int COUNT_STEP = 1e4;     //Количество шагов просчета
const int STEP_CALC = 1;        //Шаг просчета физики (секунды) ( STEP_CALC >= 1 )
const int STEP_ANIM = 100;      //Шаг анимации (секунды) ( STEP_ANIM >= STEP_CALC )
const int PRECISION = 10;       //Знаков после запятой ( 0 <= PRECISION <= 100 )
                                //Входной и итоговый фаил
const char iFile[] = "Planet001.txt";
const char oFile[] = "Animation001.txt";


struct body {
    ld m,x,y,nx,ny;
};

body a[MAX_N];
int n;



void calc_vect(int num);
void remove_obj(int num);
void next_step();
void add_obj();
void write();



inline void calc_vect(int num) ///=============================
{
    ld new_x=0,
       new_y=0;

    for (int i=0; i<n; ++i)
    {
        if (i==num)
            continue;

        ld dx,dy,r,F,k;

        dx=-a[num].x+a[i].x;
        dy=-a[num].y+a[i].y;
        r =sqr(dx) + sqr(dy);
        F =(G * a[i].m) * (a[num].m / sqr(r)); ///error - sqr() ?
        k =r / F;

        new_x+=dx*k;
        new_y+=dy*k;
    }

    a[num].nx+=STEP_CALC*new_x/a[num].m;
    a[num].ny+=STEP_CALC*new_y/a[num].m;
}

inline void write() ///========================================
{
    for (int i=0; i<n; ++i)
        cout<<a[i].x<<' '<<a[i].y<<'\n';
    cout<<'\n';
}

inline void next_step() ///====================================
{
    for (int i=0; i<n; ++i)
        calc_vect(i);

    for (int i=0; i<n; ++i) {
        a[i].x+=a[i].nx;
        a[i].y+=a[i].ny;
    }
}

inline void add_obj() ///======================================
{

    ld v,vx,vy;
    cin>>a[n].m
       >>a[n].x
       >>a[n].y
       >>vx
       >>vy
       >>v;

    if (a[n].m < MIN_MASS)
        a[n].m = MIN_MASS;

    if (a[n].m > MAX_MASS)
        a[n].m = MAX_MASS;



    ld k=1;
    if (v) {k = sqrt(sqr(vx) + sqr(vy)) / v; }
      else {vx=0; vy=0;}

    a[n].nx = STEP_CALC*vx/k;
    a[n].ny = STEP_CALC*vy/k;

    ++n;
}

inline void remove_obj(int num) ///============================
{
    for (int i=num; i<n; ++i)
        a[i]=a[i+1];
    --n;
}




int main() ///=================================================
{
    freopen(iFile, "r", stdin);
    freopen(oFile, "w", stdout);

    int s;
    cin>>s;
    for (int i=0; i<s; ++i)
        add_obj();


    cout.setf(ios::fixed);
    cout.precision(PRECISION);

    write();
    for (int i=0; i<COUNT_STEP; ++i) {
        next_step();

        if (!( ( (i+1) * STEP_CALC) %STEP_ANIM))
            write();
    }


}
