// MyRippleDoc.cpp : implementation of the CMyRippleDoc class
//

#include "stdafx.h"
#include "MyRipple.h"

#include "MyRippleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyRippleDoc

IMPLEMENT_DYNCREATE(CMyRippleDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyRippleDoc, CDocument)
	//{{AFX_MSG_MAP(CMyRippleDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyRippleDoc construction/destruction

CMyRippleDoc::CMyRippleDoc()
{
	// TODO: add one-time construction code here

}

CMyRippleDoc::~CMyRippleDoc()
{
}

BOOL CMyRippleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyRippleDoc serialization

void CMyRippleDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMyRippleDoc diagnostics

#ifdef _DEBUG
void CMyRippleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyRippleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyRippleDoc commands
