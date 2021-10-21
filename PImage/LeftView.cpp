
// LeftView.cpp : CLeftView 类的实现
//

#include "stdafx.h"
#include "PImage.h"

#include "PImageDoc.h"
#include "LeftView.h"
#include "afxctl.h"
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CView)

BEGIN_MESSAGE_MAP(CLeftView, CView)
END_MESSAGE_MAP()


// CLeftView 构造/析构

CLeftView::CLeftView()
{
	// TODO: 在此处添加构造代码
}

CLeftView::~CLeftView()
{
}
CLeftView cLf;
BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式
	return CView::PreCreateWindow(cs);
}

void CLeftView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 调用 GetTreeCtrl() 直接访问 TreeView 的树控件，
	//  从而可以用项填充 TreeView。
}
void CLeftView::setImage(CImage& image)
{
	m_image = image;
}
void CLeftView::OnOpenLeftImage(CString openFilePath)
{
	
	if(!m_image.IsNull())
	{
			m_image.Destroy();
	}
	m_openFilePath = openFilePath;
	m_image.Load(openFilePath);

}
void CLeftView::OnDraw(CDC* pDC){
	if (m_image.IsNull()) {
		return;
	}
	//设备描述表（DC）
	//cdc是设备描述表的基类，clientDC指代客户区的设备描述表，PaintDC只用于OnPaint()函数中
	//CDC是MFC的DC的一个类 ，它封装了几乎所有的关于 HDC的操作。HDC是DC的句柄
	//cdc到hdc    hdc = cdc.GetSafeHdc();
	//hdc到cdc    cdc.Attach(hdc);
	//应用程序不能直接访问设备描述表(DC)，只能由各种相关API函数通过设备描述表的句柄(HDC)间接访问该结构
	HDC hDC = pDC->GetSafeHdc();
	CRect rc(0, 0, m_image.GetWidth(), m_image.GetHeight());
	m_image.Draw(hDC, 0,0);
	DeleteDC(hDC);
	m_image.Destroy();
	//DeleteObject(image);
	
}


// CLeftView 诊断

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPImageDoc* CLeftView::GetDocument() // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPImageDoc)));
	return (CPImageDoc*)m_pDocument;
}
#endif //_DEBUG


// CLeftView 消息处理程序\

