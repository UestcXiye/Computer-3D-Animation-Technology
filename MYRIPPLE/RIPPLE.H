// Ripple.h: interface for the CRipple class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RIPPLE_H__751E3190_8C46_4FE3_87B5_F48131AB711A__INCLUDED_)
#define AFX_RIPPLE_H__751E3190_8C46_4FE3_87B5_F48131AB711A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define GRID_SIZE_X  32
#define GRID_SIZE_Y  32
#define CLIP_NEAR  0.0
#define CLIP_FAR   1000.0
#define RIPPLE_LENGTH     2048
#define RIPPLE_CYCLES     18
#define RIPPLE_AMPLITUDE  0.125
#define RIPPLE_STEP	  7
#define RIPPLE_COUNT	  7

typedef struct {	// 预处理位移矢量表
  double dx[2];
  int r;			// 从原点到该点的距离
} RIPPLE_VECTOR;

typedef struct {	// 预处理涟漪幅度表
  double amplitude;
} RIPPLE_AMP;

typedef struct {
  float x[2];		// 顶点坐标
  float t[2];		// 纹理坐标
  float dt[2];		// 缺省纹理坐标
} RIPPLE_VERTEX;

class CRipple  
{
public:
	CRipple();
	virtual ~CRipple();

	void ripple_init();
	void ripple_dynamics(int mousex, int mousey);
	void ripple_redraw();
	void ripple_click(int mousex, int mousey);
	int ripple_max_distance(int gx, int gy);
	float ripple_distance(int gx, int gy, int cx, int cy);

	RIPPLE_VERTEX ripple_vertex[GRID_SIZE_X][GRID_SIZE_Y];
	int cx[RIPPLE_COUNT];
	int cy[RIPPLE_COUNT];
	int t[RIPPLE_COUNT];
	int max[RIPPLE_COUNT];
	int ripple_max;

};

#endif // !defined(AFX_RIPPLE_H__751E3190_8C46_4FE3_87B5_F48131AB711A__INCLUDED_)
