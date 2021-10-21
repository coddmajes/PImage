
// LeftView.h : CLeftView ��Ľӿ�
//


#pragma once
#include <afxctl.h>

class CPImageDoc;

class CLeftView : public CView
{
private:
	CImage m_image;
	CString m_openFilePath;
protected: // �������л�����
	

// ����
public:
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)
	CPImageDoc* GetDocument();

// ����
public:
	void OnOpenLeftImage(CString);
	void setImage(CImage& image);

// ��д
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnDraw(CDC* pDC);
	
	protected:
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};




#ifndef _DEBUG  // LeftView.cpp �еĵ��԰汾
inline CPImageDoc* CLeftView::GetDocument()
   { return reinterpret_cast<CPImageDoc*>(m_pDocument); }
#endif

