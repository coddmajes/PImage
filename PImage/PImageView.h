
// PImageView.h : CPImageView ��Ľӿ�
//

#pragma once
#include "resource.h"       // ������
#include "PImageDoc.h"
#include "afxwin.h"
#include <afxctl.h>
#include "cv.h"
#include "highgui.h"


class CPImageView : public CView
{
private:
	CImage m_image;
	CImage *m_img;
	int m_type;
	//CString m_openFilePath;
	//cv::Mat m_magI;
protected: // �������л�����
	CPImageView();
	DECLARE_DYNCREATE(CPImageView)

// ����
public:
	CPImageDoc* GetDocument() const;
	
// ����
public:
	//void OnOpenRightImage(CImage);
	void OnOpenRightImage(CString);
	void DisplayImage(CWnd* m_pMyWnd,const CImage& image);
	void setImage(CImage& image,int);
	void setImg(CImage* image,int);
	//void ShowImage(CImage& image);

	enum 
	{ 
		IDM_F = ID_FOURIER_TRANSFORM,
		IDM_FR = ID_FOURIER_REVERSER,
		IDM_DCT = ID_DCT_TRANSFORM,
		IDM_DCTR = ID_DCT_REVERSE,
		IDM_GLT_INVERSE = ID_GLT_INVERSE,
		IDM_DSCRETCH = ID_DSCRETCH,
		IDM_LAYER = ID_LAYER,
		IDM_BIT_LAYER = ID_BIT_LAYER,
		IDM_GLT_LOGARITHM = ID_GLT_LOGARITHM,//�����任
		//IDM_POWER = ID_POWER,//�ݴα任
		IDM_HISTOGRAM_GRAY = ID_HISTOGRAM_GRAY,//ֱ��ͼ
		IDM_HISTOGRAM_EQUALIZATION = ID_HISTOGRAM_EQUALIZATION,//ֱ��ͼ���⻯
		IDM_HISTOGRAM_REGULARIZATION = ID_HISTOGRAM_REGULARIZATION,//ֱ��ͼ�涨��
		IDM_FILTER_SMOOTH = ID_FILTER_SMOOTH,
		IDM_AVERAGE_FILTER = ID_AVERAGE_FILTER,
		IDM_MEDIAN_FILTER = ID_MEDIAN_FILTER,
		IDM_MAX_FILTER = ID_MAX_FILTER,
		IDM_MIN = ID_MIN,
		IDM_LA_FILTER = ID_LA_FILTER,//������˹����
		IDM_LA_GRAY = ID_LA_GRAY,//������˹���� + ԭͼ
		IDM_ROBERTS = ID_ROBERTS,
		IDM_PREWITT = ID_PREWITT,//prewitt����
		IDM_SOBEL = ID_SOBEL,
		IDM_HORI_VERT = ID_HORI_VERT, //ˮƽ��ֱ����
		IDM_ILPF = ID_ILPF,//�����ͨ�˲���
		IDM_IHPF = ID_IHPF,//����͸��˲���
		IDM_BLPF = ID_BLPF,//���������˹��ͨ�˲���
		IDM_BHPF = ID_BHPF,//���������˹��ͨ�˲���
		IDM_GLPF = ID_GLPF,//��˹��ͨ�˲�
		IDM_GHPF = ID_GHPF,////��˹��ͨ�˲�
		IDM_LIGHT = ID_LIGHT,//������
		IDM_WHITE = ID_WHITE,//����
		IDM_SCRESHOT = ID_SCRESHOT,//��ȡ����
		IDM_FRESTORE = ID_FRESTORE,//����ԭ
		IDM_RESTOREFUC = ID_RESTOREFUC,//�˻�����
		IDM_REVERFILTER = ID_REVERFILTER,//���˲���ԭ
		IDM_GLOBAL_THRESHOLD = ID_GLOBAL_THRESHOLD,//����ȫ����ֵ����
		IDM_OTSU_THRESHOLD = ID_OTSU_THRESHOLD,//OTSU�������ֵ����
		IDM_EDGE_CANNY = ID_EDGE_CANNY,//CANNY����
		IDM_EDGE_HOUGH = ID_EDGE_HOUGH, //����任
		IDM_FACE_CUT = ID_FACE_CUT,//�����ָ�
		IDM_CUT_TAG = ID_CUT_TAG,//�ָ���
		IDM_FACE_THRE = ID_FACE_THRE,//�����ָ�--��ֵ����
		IDM_FACE_EDGE = ID_FACE_EDGE,//�����ָ�--��Ե���
		IDM_FACE_FCUT = ID_FACE_FCUT,//�����ָ�--ͼƬ�ָ�
		IDM_FACE_TAG = ID_FACE_TAG,//�����ָ�--�ָ���
		IDM_FACE_TOP = ID_FACE_TOP,//��ȡ��ͷ
		IDM_FACE_LEFT = ID_FACE_LEFT,//��ȡ������
		IDM_FACE_RIGHTC = ID_FACE_RIGHTC,//��ȡ������
		IDM_FACE_NOSE = ID_FACE_NOSE,//��ȡ����
		IDM_FACE_BOTTOM = ID_FACE_BOTTOM,//��ȡ�°�
		
	};
	
// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnDraw(CDC* pDC);
	//virtual void OnSize(UNIT nType, int cx, int cy);
	
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CPImageView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // PImageView.cpp �еĵ��԰汾
inline CPImageDoc* CPImageView::GetDocument() const
   { return reinterpret_cast<CPImageDoc*>(m_pDocument); }
#endif

