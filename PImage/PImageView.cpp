
// PImageView.cpp : CPImageView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "PImage.h"
#endif

#include "PImageDoc.h"
#include "PImageView.h"
#include "cv.h"
#include "highgui.h"
#include "MainFrm.h"
using namespace std;
using namespace cv;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPImageView

IMPLEMENT_DYNCREATE(CPImageView, CView)

BEGIN_MESSAGE_MAP(CPImageView, CView)
	ON_WM_STYLECHANGED()
END_MESSAGE_MAP()

// CPImageView ����/����

CPImageView::CPImageView()
{
	// TODO: �ڴ˴���ӹ������

}

CPImageView::~CPImageView()
{
}

BOOL CPImageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}
/*
void CPImageView::OnDraw(CDC* pDC)
{
	int i = 0;
}
*/
void CPImageView::OnInitialUpdate()
{
	CView::OnInitialUpdate();


	// TODO: ���� GetListCtrl() ֱ�ӷ��� ListView ���б�ؼ���
	//  �Ӷ������������ ListView��
}
void CPImageView::setImage(CImage& image,int type)
{
	m_image = image;
	m_type = type;
}

void  CPImageView::setImg(CImage* image,int type)
{
	m_img = image;
	m_type = type;
}


// ��ʾͼ��ָ������
void CPImageView::DisplayImage(CWnd* m_pMyWnd,const CImage& image)
{
	m_pMyWnd->Invalidate(TRUE);
	/*
	CDC *m_pDC = m_pMyWnd->GetDC();//��ȡ������ӵ�е��豸�����ģ�������ʾͼ��
	m_pMyWnd->UpdateWindow();

	CRect rc;
	m_pMyWnd->GetWindowRect(&rc);
 
	/*InvalidateRect(m_pMyWnd->m_hWnd,&rc,true);*//*
	int nwidth = rc.Width();
	int nheight = rc.Height();
 
	int fixed_width = min(image.GetWidth(),nwidth);
	int fixed_height = min(image.GetHeight(),nheight);
 
	double ratio_w = fixed_width / (double)image.GetWidth();
	double ratio_h = fixed_height / (double)image.GetHeight();
	double ratio = min(ratio_w,ratio_h);
 
	int show_width = (int)(image.GetWidth() * ratio);
	int show_height = (int)(image.GetHeight() * ratio);
 
	int offsetx = (nwidth - show_width) / 2;
	int offsety = (nheight - show_height) / 2;
 
	::SetStretchBltMode(m_pDC->GetSafeHdc(),COLORONCOLOR);//����λͼ������ģʽ
	image.StretchBlt(m_pDC->GetSafeHdc(),0,0,show_width,show_height,
		0,0,image.GetWidth(),image.GetHeight(),SRCCOPY);
	m_pDC->DeleteDC();*/
}
void CPImageView::OnDraw(CDC* pDC)
{
	if (m_image.IsNull() && m_img->IsNull()) {
		return;
	}

	HDC hDC = pDC->GetSafeHdc();
	
	if(m_type == IDM_LIGHT )
	{
		int j =0;
		for(int i = 0; i< 5&&!m_img[i].IsNull();i++)
		{
			CRect rc(0, 0, m_img[i].GetWidth(), m_img[i].GetHeight());
			

			switch(m_type)
			{
				case IDM_LIGHT:
					m_img[i].Draw(hDC, 0,0);
					break;
		
			
			}
		}
	}
	else
	{
		CRect rc(0, 0, m_image.GetWidth(), m_image.GetHeight());
		m_image.Draw(hDC, 0,0);
	}
	DeleteDC(hDC);
	m_image.Destroy();
}


// CPImageView ���

#ifdef _DEBUG
void CPImageView::AssertValid() const
{
	CView::AssertValid();
}

void CPImageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPImageDoc* CPImageView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPImageDoc)));
	return (CPImageDoc*)m_pDocument;
}
#endif //_DEBUG


// CPImageView ��Ϣ�������
void CPImageView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: ��Ӵ�������Ӧ�û��Դ�����ͼ��ʽ�ĸ���	
	CView::OnStyleChanged(nStyleType,lpStyleStruct);
}
