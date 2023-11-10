
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
	
	if(m_type == IDM_LIGHT || m_type == IDM_WHITE|| m_type == IDM_SCRESHOT || m_type == IDM_FRESTORE || m_type == IDM_RESTOREFUC 
		|| m_type == IDM_REVERFILTER //ͼ��ָ�
		||m_type == IDM_GLOBAL_THRESHOLD ||m_type == IDM_OTSU_THRESHOLD//ͼ��ָ�--��ֵ����
		||m_type ==IDM_EDGE_CANNY ||m_type ==IDM_EDGE_HOUGH //ͼ��ָ�--��Ե����
		||m_type == IDM_FACE_THRE || m_type ==IDM_FACE_EDGE ||m_type == IDM_FACE_FCUT || m_type == IDM_FACE_TAG//ͼ��ָ�--�����ָ�
		||m_type == IDM_FACE_TOP ||m_type == IDM_FACE_LEFT || m_type == IDM_FACE_RIGHTC || m_type == IDM_FACE_NOSE 
		||m_type == IDM_FACE_BOTTOM //ͼ��ָ�--�����ָ�
		||m_type == IDM_HISTOGRAM_GRAY || m_type == IDM_HISTOGRAM_EQUALIZATION || m_type ==IDM_HISTOGRAM_REGULARIZATION//ֱ��ͼ
		||m_type == IDM_MEDIAN_FILTER ||m_type == IDM_MAX_FILTER ||m_type == IDM_MIN//����ƽ���˲�
		||m_type == IDM_ILPF ||m_type ==IDM_IHPF||m_type == IDM_BLPF ||m_type == IDM_BHPF ||m_type == IDM_GLPF ||m_type == IDM_GHPF //Ƶ���˲�
		//||m_type == IDM_FRESTORE
		)
	{
		int j =0;
		for(int i = 0; i< 6&&!m_img[i].IsNull();i++)
		{
			CRect rc(0, 0, m_img[i].GetWidth(), m_img[i].GetHeight());
			

	switch(m_type)
	{
		
		case IDM_HISTOGRAM_GRAY://ֱ��ͼ
			m_img[i].Draw(hDC, 0,0);
			break;
		case IDM_LIGHT://ͼ��ָ�
			m_img[i].Draw(hDC, 0,0);
			break;
		case IDM_GLOBAL_THRESHOLD://ͼ��ָ�--��ֵ����
			m_img[i].Draw(hDC, 0,0);
			break;
		case IDM_EDGE_CANNY://ͼ��ָ�--��Ե����
			m_img[i].Draw(hDC, 0,0);
			break;
		case IDM_FACE_THRE://ͼ��ָ�--�����ָ�
			m_img[i].Draw(hDC, 0,0);
			break;	
		
		case IDM_ILPF://�����ͨ�˲���
			m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			break;
		case IDM_IHPF://����͸��˲���
			m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			break;
		case IDM_BLPF://���������˹��ͨ�˲���
			m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			break;
		case IDM_BHPF://���������˹��ͨ�˲���
			m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			break;
		case IDM_GLPF://��˹��ͨ�˲�
			m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			break;
		case IDM_GHPF://��˹��ͨ�˲�
			m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			break;

		case IDM_MEDIAN_FILTER://��ֵ�˲�
			m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			break;
		case IDM_MAX_FILTER://���ֵ�˲�
			m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			break;
		case IDM_MIN://��Сֵ�˲�
			m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			break;

		case IDM_HISTOGRAM_EQUALIZATION://ֱ��ͼ���⻯
			m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			break;
		case IDM_WHITE://ͼ��ָ�
			m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			break;
		case IDM_OTSU_THRESHOLD://ͼ��ָ�--��ֵ����
			m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			break;
		case IDM_EDGE_HOUGH://ͼ��ָ�--��Ե����
			m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			break;
		case IDM_FACE_EDGE://ͼ��ָ�--�����ָ�
			m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			break;
		case IDM_HISTOGRAM_REGULARIZATION://ֱ��ͼ�涨��
			if(i>=3)
			{
				m_img[i].Draw(hDC, m_img[i-1].GetWidth()*j + 10*j,m_img[3].GetHeight()+10);
				j++;
			}
			else
				m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			break;
			
		case IDM_FACE_TOP://ͼ��ָ�--�����ָ�--��ͷ
			if(i>=1)
			{
				m_img[i].Draw(hDC, m_img[i-1].GetWidth()*i + 10*i,0);
			}
			else
				m_img[i].Draw(hDC, 0,0);
			break;
		case IDM_FACE_LEFT://ͼ��ָ�--�����ָ�--����
			if(i>=1)
			{
				m_img[i].Draw(hDC, m_img[i-1].GetWidth()*i + 10*i,0);
			}
			else
				m_img[i].Draw(hDC, 0,0);
			break;
		case IDM_FACE_RIGHTC://ͼ��ָ�--�����ָ�--����
			if(i>=1)
			{
				m_img[i].Draw(hDC, m_img[i-1].GetWidth()*i + 10*i,0);
			}
			else
				m_img[i].Draw(hDC, 0,0);
			break;
		case IDM_FACE_NOSE://ͼ��ָ�--�����ָ�--����
			if(i>=1)
			{
				m_img[i].Draw(hDC, m_img[i-1].GetWidth()*i + 10*i,0);
			}
			else
				m_img[i].Draw(hDC, 0,0);
			break;
		case IDM_FACE_BOTTOM://ͼ��ָ�--�����ָ�--�°�
			if(i>=1)
			{
				m_img[i].Draw(hDC, m_img[i-1].GetWidth()*i + 10*i,0);
			}
			else
				m_img[i].Draw(hDC, 0,0);
			break;
			
		case IDM_FACE_FCUT://ͼ��ָ�--�����ָ�
			/*
			if(i == 1)
			{
				m_img[i].Draw(hDC, 0, m_img[i].GetHeight()*i+10*i);
			}
			else
			{
				m_img[i].Draw(hDC, 0,0);
			}*/
			m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			break;
		
		case IDM_SCRESHOT://ͼ��ָ�
			if(i >= 2)
			{
				m_img[i].Draw(hDC, m_img[i].GetWidth()*j + 10*j, m_img[i].GetHeight()+10);
				j++;
			}
			else
			{
				m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			}
			break;
		case IDM_FACE_TAG://ͼ��ָ�--�����ָ�
			if(i == 3)
			{
				m_img[i].Draw(hDC, 0, m_img[i].GetHeight()+10);
			}
			else
			{
				m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			}
			break;
		/*
		case IDM_FACE_EDGE://ͼ��ָ�--�����ָ�
			if(i == 1 || i == 2)
			{
				j = 1;
				m_img[i].Draw(hDC, m_img[i].GetWidth()*(i-1) + 10*(i-1), m_img[i].GetHeight()*j+10*j);
				
			}
			else
			{
				m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			}
			break;
			*/
		case IDM_FRESTORE://ͼ��ָ�
			if(i >=2)
			{
				m_img[i].Draw(hDC, m_img[i].GetWidth()*j+10*j, m_img[i].GetHeight()+10);
				j++;
			}
			else
			{
				m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			}
			break;
		case IDM_RESTOREFUC://�˻�����
			if(i == 2 || i == 3)
			{
				m_img[i].Draw(hDC, m_img[i].GetWidth()*j+10*j, m_img[i].GetHeight()*(i-j-1)+10*(i-j-1));
				j++;
			}
			/*
			else if(i == 4)
			{
				m_img[i].Draw(hDC, m_img[i].GetWidth()*j, m_img[i].GetHeight()*(j+1)+10*(j+1));
				CString strLabel;
				strLabel.Format("�˻�����Ϊ:"
					"H(u,v) = G(u,v)/(G(u,v)*n - ��G(u,v+i) )"
					"���У�u = 0,��s-1,v = t-1,��0; i = 1,��n;"
					"��ʵ��n = 6;"
					"�� t-v < n ʱ��n = t-v;");
				j++;
				pDC->TextOut(m_img[i].GetWidth()*j+10*j,m_img[i].GetHeight()*j+10*j, strLabel);
				//pDC->TextOut();
			}*/
			else
			{
				m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			}
			
			break;
		case IDM_REVERFILTER://ͼ��ָ�
			if(i >=3)
			{
				m_img[i].Draw(hDC, m_img[i].GetWidth()*j+10*j, m_img[i].GetHeight()+10);
				j++;
			}
			else
			{
				m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			}
			break;
		//default:
		//	CRect rc(0, 0, m_image.GetWidth(), m_image.GetHeight());
		//	m_image.Draw(hDC, 0,0);
		//	break;
		}
		}
		}
	else
	{
		CRect rc(0, 0, m_image.GetWidth(), m_image.GetHeight());
		m_image.Draw(hDC, 0,0);
	}
	DeleteDC(hDC);
	//m_image.Destroy();
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
