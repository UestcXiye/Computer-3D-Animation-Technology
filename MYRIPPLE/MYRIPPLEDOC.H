// MyRippleDoc.h : interface of the CMyRippleDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSDOPENGLDOC_H__D8D007EA_6A74_40F5_A776_6C75DFEE163C__INCLUDED_)
#define AFX_MYSDOPENGLDOC_H__D8D007EA_6A74_40F5_A776_6C75DFEE163C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyRippleDoc : public CDocument
{
protected: // create from serialization only
	CMyRippleDoc();
	DECLARE_DYNCREATE(CMyRippleDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyRippleDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyRippleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyRippleDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSDOPENGLDOC_H__D8D007EA_6A74_40F5_A776_6C75DFEE163C__INCLUDED_)
