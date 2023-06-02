// MyRippleView.cpp : implementation of the CMyRippleView class
//

#include "stdafx.h"
#include "MyRipple.h"

#include "MyRippleDoc.h"
#include "MyRippleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int win_size_x , win_size_y ;
/////////////////////////////////////////////////////////////////////////////
// CMyRippleView

IMPLEMENT_DYNCREATE(CMyRippleView, CView)

BEGIN_MESSAGE_MAP(CMyRippleView, CView)
	//{{AFX_MSG_MAP(CMyRippleView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyRippleView construction/destruction

CMyRippleView::CMyRippleView()
{
	// TODO: add construction code here
	m_pRipple=new CRipple;
}

CMyRippleView::~CMyRippleView()
{
}

BOOL CMyRippleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
////////////////////////////////////////////////////////////////
//设置窗口类型
	cs.style |=WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
////////////////////////////////////////////////////////////////
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyRippleView drawing

void CMyRippleView::OnDraw(CDC* pDC)
{
	CMyRippleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
//////////////////////////////////////////////////////////////////
	RenderScene();	//渲染场景
//////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////
// CMyRippleView printing

BOOL CMyRippleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyRippleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyRippleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyRippleView diagnostics

#ifdef _DEBUG
void CMyRippleView::AssertValid() const
{
	CView::AssertValid();
}

void CMyRippleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyRippleDoc* CMyRippleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyRippleDoc)));
	return (CMyRippleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyRippleView message handlers

int CMyRippleView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
//////////////////////////////////////////////////////////////////
//初始化OpenGL和设置定时器
	m_pDC = new CClientDC(this);
	SetTimer(1, 20, NULL);
	InitializeOpenGL(m_pDC);
//////////////////////////////////////////////////////////////////
	image_init("data/distort.rgb");	
	return 0;
}

void CMyRippleView::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//删除调色板和渲染上下文、定时器
	::wglMakeCurrent(0,0);
	::wglDeleteContext( m_hRC);
	if (m_hPalette)
	    DeleteObject(m_hPalette);
	if ( m_pDC )
	{
		delete m_pDC;
	}
	KillTimer(1);		
/////////////////////////////////////////////////////////////////
	
}

void CMyRippleView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//添加窗口缩放时的图形变换函数
	glViewport(0,0,cx,cy);
/////////////////////////////////////////////////////////////////
	win_size_x = cx;
	win_size_y = cy;
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, cx, 0, cy , CLIP_NEAR, CLIP_FAR);
  
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    m_pRipple->ripple_init();	
}

void CMyRippleView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
/////////////////////////////////////////////////////////////////
//添加定时器响应函数和场景更新函数
	Invalidate(FALSE);	
/////////////////////////////////////////////////////////////////
	m_pRipple->ripple_dynamics(mousex, mousey);	
	CView::OnTimer(nIDEvent);
}

/////////////////////////////////////////////////////////////////////
//	                  设置逻辑调色板
//////////////////////////////////////////////////////////////////////
void CMyRippleView::SetLogicalPalette(void)
{
    struct
    {
        WORD Version;
        WORD NumberOfEntries;
        PALETTEENTRY aEntries[256];
    } logicalPalette = { 0x300, 256 };

	BYTE reds[] = {0, 36, 72, 109, 145, 182, 218, 255};
	BYTE greens[] = {0, 36, 72, 109, 145, 182, 218, 255};
	BYTE blues[] = {0, 85, 170, 255};

    for (int colorNum=0; colorNum<256; ++colorNum)
    {
        logicalPalette.aEntries[colorNum].peRed =
            reds[colorNum & 0x07];
        logicalPalette.aEntries[colorNum].peGreen =
            greens[(colorNum >> 0x03) & 0x07];
        logicalPalette.aEntries[colorNum].peBlue =
            blues[(colorNum >> 0x06) & 0x03];
        logicalPalette.aEntries[colorNum].peFlags = 0;
    }

    m_hPalette = CreatePalette ((LOGPALETTE*)&logicalPalette);
}


//////////////////////////////////////////////////////////
//						初始化openGL场景
//////////////////////////////////////////////////////////
BOOL CMyRippleView::InitializeOpenGL(CDC* pDC)
{
	m_pDC = pDC;
	SetupPixelFormat();
	//生成绘制描述表
	m_hRC = ::wglCreateContext(m_pDC->GetSafeHdc());
	//置当前绘制描述表
	::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);

	return TRUE;
}

//////////////////////////////////////////////////////////
//						设置像素格式
//////////////////////////////////////////////////////////
BOOL CMyRippleView::SetupPixelFormat()
{
	PIXELFORMATDESCRIPTOR pfd = { 
	    sizeof(PIXELFORMATDESCRIPTOR),    // pfd结构的大小 
	    1,                                // 版本号 
	    PFD_DRAW_TO_WINDOW |              // 支持在窗口中绘图 
	    PFD_SUPPORT_OPENGL |              // 支持 OpenGL 
	    PFD_DOUBLEBUFFER,                 // 双缓存模式 
	    PFD_TYPE_RGBA,                    // RGBA 颜色模式 
	    24,                               // 24 位颜色深度 
	    0, 0, 0, 0, 0, 0,                 // 忽略颜色位 
	    0,                                // 没有非透明度缓存 
	    0,                                // 忽略移位位 
	    0,                                // 无累加缓存 
	    0, 0, 0, 0,                       // 忽略累加位 
	    32,                               // 32 位深度缓存     
	    0,                                // 无模板缓存 
	    0,                                // 无辅助缓存 
	    PFD_MAIN_PLANE,                   // 主层 
	    0,                                // 保留 
	    0, 0, 0                           // 忽略层,可见性和损毁掩模 
	}; 	
	int pixelformat;
	pixelformat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);//选择像素格式
	::SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd);	//设置像素格式
	if(pfd.dwFlags & PFD_NEED_PALETTE)
		SetLogicalPalette();	//设置逻辑调色板
	return TRUE;
}



//////////////////////////////////////////////////////////
//						场景绘制与渲染
//////////////////////////////////////////////////////////
BOOL CMyRippleView::RenderScene() 
{
	m_pRipple->ripple_redraw();

	::SwapBuffers(m_pDC->GetSafeHdc());		//交互缓冲区
	return TRUE;
}

void CMyRippleView::image_init(char *fn)
{

  unsigned int *buf;
  int width, height, depth;

  buf = m_Texture.read_texture(fn, &width, &height, &depth);
  if (buf == NULL)
  {
    MessageBox("distort: Can't load image file ", "Error",MB_OK);
    exit(-1);
  }

  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexImage2D(GL_TEXTURE_2D, 0, depth, width, height, 
	       0, GL_RGBA, GL_UNSIGNED_BYTE, buf);
  glEnable(GL_TEXTURE_2D);
  
  free(buf);
}

void CMyRippleView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	mousex = point.x;
	mousey = win_size_y-point.y;
    m_pRipple->ripple_click(mousex, mousey);	
	CView::OnLButtonDown(nFlags, point);
}


