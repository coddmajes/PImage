
// LeftView.h : CLeftView 类的接口
//


#pragma once
#include <afxctl.h>

class CPImageDoc;

class CLeftView : public CView
{
private:
	CImage m_image;
	CString m_openFilePath;
protected: // 仅从序列化创建
	

// 特性
public:
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)
	CPImageDoc* GetDocument();

// 操作
public:
	void OnOpenLeftImage(CString);
	void setImage(CImage& image);

// 重写
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnDraw(CDC* pDC);
	
	protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};




#ifndef _DEBUG  // LeftView.cpp 中的调试版本
inline CPImageDoc* CLeftView::GetDocument()
   { return reinterpret_cast<CPImageDoc*>(m_pDocument); }
#endif

