
// LeftView.cpp : CLeftView ���ʵ��
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


// CLeftView ����/����

CLeftView::CLeftView()
{
	// TODO: �ڴ˴���ӹ������
}

CLeftView::~CLeftView()
{
}
CLeftView cLf;
BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	return CView::PreCreateWindow(cs);
}

void CLeftView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: ���� GetTreeCtrl() ֱ�ӷ��� TreeView �����ؼ���
	//  �Ӷ������������ TreeView��
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
	//�豸������DC��
	//cdc���豸������Ļ��࣬clientDCָ���ͻ������豸������PaintDCֻ����OnPaint()������
	//CDC��MFC��DC��һ���� ������װ�˼������еĹ��� HDC�Ĳ�����HDC��DC�ľ��
	//cdc��hdc    hdc = cdc.GetSafeHdc();
	//hdc��cdc    cdc.Attach(hdc);
	//Ӧ�ó�����ֱ�ӷ����豸������(DC)��ֻ���ɸ������API����ͨ���豸������ľ��(HDC)��ӷ��ʸýṹ
	HDC hDC = pDC->GetSafeHdc();
	CRect rc(0, 0, m_image.GetWidth(), m_image.GetHeight());
	m_image.Draw(hDC, 0,0);
	DeleteDC(hDC);
	//m_image.Destroy();
	
}


// CLeftView ���

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPImageDoc* CLeftView::GetDocument() // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPImageDoc)));
	return (CPImageDoc*)m_pDocument;
}
#endif //_DEBUG


// CLeftView ��Ϣ�������\

