
// PImageView.h : CPImageView 类的接口
//

#pragma once
#include "resource.h"       // 主符号
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
protected: // 仅从序列化创建
	CPImageView();
	DECLARE_DYNCREATE(CPImageView)

// 特性
public:
	CPImageDoc* GetDocument() const;
	
// 操作
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
		IDM_GLT_LOGARITHM = ID_GLT_LOGARITHM,//对数变换
		//IDM_POWER = ID_POWER,//幂次变换
		IDM_HISTOGRAM_GRAY = ID_HISTOGRAM_GRAY,//直方图
		IDM_HISTOGRAM_EQUALIZATION = ID_HISTOGRAM_EQUALIZATION,//直方图均衡化
		IDM_HISTOGRAM_REGULARIZATION = ID_HISTOGRAM_REGULARIZATION,//直方图规定化
		IDM_FILTER_SMOOTH = ID_FILTER_SMOOTH,
		IDM_AVERAGE_FILTER = ID_AVERAGE_FILTER,
		IDM_MEDIAN_FILTER = ID_MEDIAN_FILTER,
		IDM_MAX_FILTER = ID_MAX_FILTER,
		IDM_MIN = ID_MIN,
		IDM_LA_FILTER = ID_LA_FILTER,//拉普拉斯算子
		IDM_LA_GRAY = ID_LA_GRAY,//拉普拉斯算子 + 原图
		IDM_ROBERTS = ID_ROBERTS,
		IDM_PREWITT = ID_PREWITT,//prewitt算子
		IDM_SOBEL = ID_SOBEL,
		IDM_HORI_VERT = ID_HORI_VERT, //水平垂直算子
		IDM_ILPF = ID_ILPF,//理想低通滤波器
		IDM_IHPF = ID_IHPF,//理想低高滤波器
		IDM_BLPF = ID_BLPF,//理想巴特沃斯低通滤波器
		IDM_BHPF = ID_BHPF,//理想巴特沃斯高通滤波器
		IDM_GLPF = ID_GLPF,//高斯低通滤波
		IDM_GHPF = ID_GHPF,////高斯高通滤波
		IDM_LIGHT = ID_LIGHT,//加亮点
		
	};
	
// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnDraw(CDC* pDC);
	//virtual void OnSize(UNIT nType, int cx, int cy);
	
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CPImageView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // PImageView.cpp 中的调试版本
inline CPImageDoc* CPImageView::GetDocument() const
   { return reinterpret_cast<CPImageDoc*>(m_pDocument); }
#endif

