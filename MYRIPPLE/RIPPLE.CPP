// Ripple.cpp: implementation of the CRipple class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyRipple.h"
#include "Ripple.h"
#include <math.h>
#include "Ripple_table.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern int win_size_x, win_size_y;

CRipple::CRipple()
{

}

CRipple::~CRipple()
{

}

void CRipple::ripple_init()
{
  int i, j;

  glDisable(GL_DEPTH_TEST);

  ripple_max = (int)sqrt(win_size_y*win_size_y+win_size_x*win_size_x);

  for (i = 0; i < RIPPLE_COUNT; i++)
  {
    t[i] = ripple_max + RIPPLE_LENGTH;
    cx[i] = 0;
    cy[i] = 0;
    max[i] = 0;
  }

  for (i = 0; i < GRID_SIZE_X; i++)
    for (j = 0; j < GRID_SIZE_Y; j++)
    {
      ripple_vertex[i][j].x[0] = i/(GRID_SIZE_X - 1.0)*win_size_x;
      ripple_vertex[i][j].x[1] = j/(GRID_SIZE_Y - 1.0)*win_size_y;
      ripple_vertex[i][j].dt[0] = i/(GRID_SIZE_X - 1.0);
      ripple_vertex[i][j].dt[1] = j/(GRID_SIZE_Y - 1.0);
    }
}

////////////////////////////////////////////////////////////////////////////////
//  生成新的纹理坐标
void CRipple::ripple_dynamics(int mousex, int mousey)
{
  int i, j, k;
  int x, y;
  int mi, mj;
  int r;
  float sx, sy;
  float amp;

  for (i = 0; i < RIPPLE_COUNT; i++)
	  t[i] += RIPPLE_STEP;

  for (i = 0; i < GRID_SIZE_X; i++)
	  for (j = 0; j < GRID_SIZE_Y; j++)
	  {
		  ripple_vertex[i][j].t[0] = ripple_vertex[i][j].dt[0];
		  ripple_vertex[i][j].t[1] = ripple_vertex[i][j].dt[1];
		  for (k = 0; k < RIPPLE_COUNT; k++)
		  {
			  x = i - cx[k];
			  y = j - cy[k];
			  if (x < 0)
			  {
				  x *= -1;
				  sx = -1.0;
			  }
			  else
				  sx = 1.0;
			  if (y < 0)
			  {
				  y *= -1;
				  sy = -1.0;
			  }
			  else
				  sy = 1.0;
			  mi = x;
			  mj = y;
			  r = t[k] - ripple_vector[mi][mj].r;
			  if (r < 0)
				  r = 0;
			  if (r > RIPPLE_LENGTH - 1)
				  r = RIPPLE_LENGTH - 1;
			  amp = 1.0 - 1.0*t[k]/RIPPLE_LENGTH;
			  amp *= amp;
			  if (amp < 0.0)
				  amp = 0.0;
			  ripple_vertex[i][j].t[0]
				  += ripple_vector[mi][mj].dx[0]*sx*ripple_amp[r].amplitude*amp;
			  ripple_vertex[i][j].t[1]
				  += ripple_vector[mi][mj].dx[1]*sy*ripple_amp[r].amplitude*amp;
		  }
	  }
}

////////////////////////////////////////////////////////////////////////////////
//  绘制纹理
void CRipple::ripple_redraw()
{
  int i, j;

  glClear(GL_COLOR_BUFFER_BIT);
  for (i = 0; i < GRID_SIZE_X - 1; i++)
  {
	  for (j = 0; j < GRID_SIZE_Y - 1; j++)
	  {
		  glBegin(GL_POLYGON);
			glTexCoord2fv(ripple_vertex[i][j].t);
			glVertex2fv(ripple_vertex[i][j].x);
			glTexCoord2fv(ripple_vertex[i][j + 1].t);
			glVertex2fv(ripple_vertex[i][j + 1].x);
			glTexCoord2fv(ripple_vertex[i + 1][j + 1].t);
			glVertex2fv(ripple_vertex[i + 1][j + 1].x);
			glTexCoord2fv(ripple_vertex[i + 1][j].t);
			glVertex2fv(ripple_vertex[i + 1][j].x);
		  glEnd();
	  }
  }
}

////////////////////////////////////////////////////////////////////////////////
//  计算两点的距离
float CRipple::ripple_distance(int gx, int gy, int cx, int cy)
{
	return sqrt(1.0*(gx - cx)*(gx - cx) + 1.0*(gy - cy)*(gy - cy));
}


int CRipple::ripple_max_distance(int gx, int gy)
{
  float d;
  float temp_d;

  d = ripple_distance(gx, gy, 0, 0);
  temp_d = ripple_distance(gx, gy, GRID_SIZE_X, 0);
  if (temp_d > d)
	  d = temp_d;
  temp_d = ripple_distance(gx, gy, GRID_SIZE_X, GRID_SIZE_Y);
  if (temp_d > d)
	  d = temp_d;
  temp_d = ripple_distance(gx, gy, 0, GRID_SIZE_Y);
  if (temp_d > d)
	  d = temp_d;

  return (d/GRID_SIZE_X)*win_size_x + RIPPLE_LENGTH/6;
}


////////////////////////////////////////////////////////////////////////////////
//  生成新的涟漪纹理
void CRipple::ripple_click(int mousex, int mousey)
{
	int index;
    index = 0;
    while (t[index] < max[index] && index < RIPPLE_COUNT)
		index++;
    
    if (index < RIPPLE_COUNT)
    {
		cx[index] = 1.0*mousex/win_size_x*GRID_SIZE_X;
		cy[index] = 1.0*mousey/win_size_y*GRID_SIZE_Y;
		t[index] = 4*RIPPLE_STEP;
		max[index] = ripple_max_distance(cx[index], cy[index]);
    }
}
