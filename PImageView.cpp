
// PImageView.cpp : CPImageView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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

// CPImageView 构造/析构

CPImageView::CPImageView()
{
	// TODO: 在此处添加构造代码

}

CPImageView::~CPImageView()
{
}

BOOL CPImageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

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


	// TODO: 调用 GetListCtrl() 直接访问 ListView 的列表控件，
	//  从而可以用项填充 ListView。
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


// 显示图像到指定窗口
void CPImageView::DisplayImage(CWnd* m_pMyWnd,const CImage& image)
{
	m_pMyWnd->Invalidate(TRUE);
	/*
	CDC *m_pDC = m_pMyWnd->GetDC();//获取窗口所拥有的设备上下文，用于显示图像
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
 
	::SetStretchBltMode(m_pDC->GetSafeHdc(),COLORONCOLOR);//设置位图的伸缩模式
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
		|| m_type == IDM_REVERFILTER //图像恢复
		||m_type == IDM_GLOBAL_THRESHOLD ||m_type == IDM_OTSU_THRESHOLD//图像分割--阈值处理
		||m_type ==IDM_EDGE_CANNY ||m_type ==IDM_EDGE_HOUGH //图像分割--边缘处理
		||m_type == IDM_FACE_THRE || m_type ==IDM_FACE_EDGE ||m_type == IDM_FACE_FCUT || m_type == IDM_FACE_TAG//图像分割--人脸分割
		||m_type == IDM_FACE_TOP ||m_type == IDM_FACE_LEFT || m_type == IDM_FACE_RIGHTC || m_type == IDM_FACE_NOSE 
		||m_type == IDM_FACE_BOTTOM //图像分割--人脸分割
		||m_type == IDM_HISTOGRAM_GRAY || m_type == IDM_HISTOGRAM_EQUALIZATION || m_type ==IDM_HISTOGRAM_REGULARIZATION//直方图
		||m_type == IDM_MEDIAN_FILTER ||m_type == IDM_MAX_FILTER ||m_type == IDM_MIN//空域平滑滤波
		||m_type == IDM_ILPF ||m_type ==IDM_IHPF||m_type == IDM_BLPF ||m_type == IDM_BHPF ||m_type == IDM_GLPF ||m_type == IDM_GHPF //频域滤波
		//||m_type == IDM_FRESTORE
		)
	{
		int j =0;
		for(int i = 0; i< 6&&!m_img[i].IsNull();i++)
		{
			CRect rc(0, 0, m_img[i].GetWidth(), m_img[i].GetHeight());
			

	switch(m_type)
	{
		
		case IDM_HISTOGRAM_GRAY://直方图
			m_img[i].Draw(hDC, 0,0);
			break;
		case IDM_LIGHT://图像恢复
			m_img[i].Draw(hDC, 0,0);
			break;
		case IDM_GLOBAL_THRESHOLD://图像分割--阈值处理
			m_img[i].Draw(hDC, 0,0);
			break;
		case IDM_EDGE_CANNY://图像分割--边缘处理
			m_img[i].Draw(hDC, 0,0);
			break;
		case IDM_FACE_THRE://图像分割--人脸分割
			m_img[i].Draw(hDC, 0,0);
			break;	
		
		case IDM_ILPF://理想低通滤波器
			m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			break;
		case IDM_IHPF://理想低高滤波器
			m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			break;
		case IDM_BLPF://理想巴特沃斯低通滤波器
			m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			break;
		case IDM_BHPF://理想巴特沃斯高通滤波器
			m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			break;
		case IDM_GLPF://高斯低通滤波
			m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			break;
		case IDM_GHPF://高斯高通滤波
			m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			break;

		case IDM_MEDIAN_FILTER://中值滤波
			m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			break;
		case IDM_MAX_FILTER://最大值滤波
			m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			break;
		case IDM_MIN://最小值滤波
			m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			break;

		case IDM_HISTOGRAM_EQUALIZATION://直方图均衡化
			m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			break;
		case IDM_WHITE://图像恢复
			m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			break;
		case IDM_OTSU_THRESHOLD://图像分割--阈值处理
			m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			break;
		case IDM_EDGE_HOUGH://图像分割--边缘处理
			m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			break;
		case IDM_FACE_EDGE://图像分割--人脸分割
			m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			break;
		case IDM_HISTOGRAM_REGULARIZATION://直方图规定化
			if(i>=3)
			{
				m_img[i].Draw(hDC, m_img[i-1].GetWidth()*j + 10*j,m_img[3].GetHeight()+10);
				j++;
			}
			else
				m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			break;
			
		case IDM_FACE_TOP://图像分割--人脸分割--额头
			if(i>=1)
			{
				m_img[i].Draw(hDC, m_img[i-1].GetWidth()*i + 10*i,0);
			}
			else
				m_img[i].Draw(hDC, 0,0);
			break;
		case IDM_FACE_LEFT://图像分割--人脸分割--左脸
			if(i>=1)
			{
				m_img[i].Draw(hDC, m_img[i-1].GetWidth()*i + 10*i,0);
			}
			else
				m_img[i].Draw(hDC, 0,0);
			break;
		case IDM_FACE_RIGHTC://图像分割--人脸分割--右脸
			if(i>=1)
			{
				m_img[i].Draw(hDC, m_img[i-1].GetWidth()*i + 10*i,0);
			}
			else
				m_img[i].Draw(hDC, 0,0);
			break;
		case IDM_FACE_NOSE://图像分割--人脸分割--鼻子
			if(i>=1)
			{
				m_img[i].Draw(hDC, m_img[i-1].GetWidth()*i + 10*i,0);
			}
			else
				m_img[i].Draw(hDC, 0,0);
			break;
		case IDM_FACE_BOTTOM://图像分割--人脸分割--下巴
			if(i>=1)
			{
				m_img[i].Draw(hDC, m_img[i-1].GetWidth()*i + 10*i,0);
			}
			else
				m_img[i].Draw(hDC, 0,0);
			break;
			
		case IDM_FACE_FCUT://图像分割--人脸分割
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
		
		case IDM_SCRESHOT://图像恢复
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
		case IDM_FACE_TAG://图像分割--人脸分割
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
		case IDM_FACE_EDGE://图像分割--人脸分割
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
		case IDM_FRESTORE://图像恢复
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
		case IDM_RESTOREFUC://退化函数
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
				strLabel.Format("退化函数为:"
					"H(u,v) = G(u,v)/(G(u,v)*n - ∑G(u,v+i) )"
					"其中，u = 0,…s-1,v = t-1,…0; i = 1,…n;"
					"本实验n = 6;"
					"当 t-v < n 时，n = t-v;");
				j++;
				pDC->TextOut(m_img[i].GetWidth()*j+10*j,m_img[i].GetHeight()*j+10*j, strLabel);
				//pDC->TextOut();
			}*/
			else
			{
				m_img[i].Draw(hDC, m_img[i].GetWidth()*i + 10*i,0);
			}
			
			break;
		case IDM_REVERFILTER://图像恢复
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


// CPImageView 诊断

#ifdef _DEBUG
void CPImageView::AssertValid() const
{
	CView::AssertValid();
}

void CPImageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPImageDoc* CPImageView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPImageDoc)));
	return (CPImageDoc*)m_pDocument;
}
#endif //_DEBUG


// CPImageView 消息处理程序
void CPImageView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: 添加代码以响应用户对窗口视图样式的更改	
	CView::OnStyleChanged(nStyleType,lpStyleStruct);
}
