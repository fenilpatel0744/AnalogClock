/* Graphical Analog Clock */

#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<math.h>
#include<dos.h>
#include<time.h>

#define PI 3.147

void clockLayout();
void secHand();
void hrHand();
void minHand();
int maxx,maxy;

void main()
{
	int gdriver=DETECT,gmode,error;
	initgraph(&gdriver,&gmode,"");
	error=graphresult();
	if(error!=grOk)
	{
		printf("Error in graphics, code= %d",grapherrormsg(error));
		exit(0);
	}
	while(!kbhit())
	{
		clockLayout();
		secHand();
		minHand();
		hrHand();
		sleep(1); /* pausing the outputscreen for 1 sec */
		cleardevice(); /* clearing the previous picture of clock */
	}
}

void clockLayout()
{
	int i,x,y,r,a,b,c;
	float j,k;
	maxx=getmaxx();
	maxy=getmaxy();
	/* printing a round ring with outer radius of 5 pixel */
	for(i=1;i<7;i++)
	{          
		setcolor(BLUE);
		circle(maxx/2,maxy/2,120-i);
	}
	pieslice(maxx/2,maxy/2,0,360,5);
	/* displaying a circle in the middle of clock */
	x=maxx/2+100;y=maxy/2;
	r=100;
	setcolor(GREEN);
	/* marking the hours for every 30 degrees */
	for(j=PI/6;j<=(2*PI);j+=(PI/6))
	{    
		pieslice(x,y,0,360,4);
		x=(maxx/2)+r*cos(j);
		y=(maxy/2)+r*sin(j);
	}
	x=maxx/2+100;y=maxy/2;
	r=100;
	setcolor(RED);
	/* marking the minutes for every 6 degrees */
	for(j=PI/30;j<=(2*PI);j+=(PI/30))
	{  
		pieslice(x,y,0,360,1);
		x=(maxx/2)+r*cos(j);
		y=(maxy/2)+r*sin(j);
	}
}

void secHand()
{
	struct time t;
	int r=80,x=maxx/2,y=maxy/2,sec;
	float O;
	maxx=getmaxx();
	maxy=getmaxy();
	gettime(&t); /*getting the seconds in system clock */
	sec=t.ti_sec;
	O=sec*(PI/30)-(PI/2);
	setcolor(YELLOW);
	line(maxx/2,maxy/2,x+r*cos(O),y+r*sin(O));
}

void hrHand()
{
	int r=50,hr,min;
	int x,y;
	struct time t;
	float O;
	maxx=getmaxx();
	maxy=getmaxy();
	x=maxx/2,y=maxy/2;
	gettime(&t); /*getting the hours in system clock */
	hr=t.ti_hour;
	min=t.ti_min;
	if(hr<=12)O=(hr*(PI/6)-(PI/2))+((min/12)*(PI/30));
	if(hr>12) O=((hr-12)*(PI/6)-(PI/2))+((min/12)*(PI/30));
	setcolor(GREEN);
	line(maxx/2,maxy/2,x+r*cos(O),y+r*sin(O));
}

void minHand()
{
	int r=60,min;
	int x,y;
	float O;
	struct time t;
	maxx=getmaxx();
	maxy=getmaxy();
	x=maxx/2;
	y=maxy/2;
	gettime(&t); /*getting the minutes in system clock */
	min=t.ti_min;
	O=(min*(PI/30)-(PI/2)); 
	setcolor(RED);
	line(maxx/2,maxy/2,x+r*cos(O),y+r*sin(O));
}