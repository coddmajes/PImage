
// PImage.h : PImage 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif
#include "resource.h"       // 主符号
#include "PImageDoc.h"
#include <afxctl.h>
#include "cv.h"
#include "highgui.h"
#include "afxdialogex.h"
#include "FFilterDlg.h"
#define TEXT_SIZE 49
#define SINGLE_LEFT 0
#define SINGLE_RIGHT 1
#define DOUBLE_PATREN 2
//#include "opencv.hpp"
#include <math.h>

using namespace cv;
typedef struct stacknode
{
	Point point;
	int data;
	int length;
	int tag;
	struct stacknode *next;
}stacknode,*LinkStack;
 
// CPImageApp:
// 有关此类的实现，请参阅 PImage.cpp
//

class CPImageApp : public CWinApp
{
private:
	CString m_guidinghuaPath;
	CString m_openFilePath;
	CString m_histFilePath;
	CImage m_image;
	CImage m_img[5];//装一堆图片
	Mat m_mat[5];//装一堆 mat
	int m_choice;//用于选择进行哪个菜单
	int m_modelMatrix;//模板矩阵
	//int m_text[TEXT_SIZE];//模板内容矩阵
	float* m_text;
	int* m_leftText;
	int* m_rightText;
	bool m_default;//用于默认计算最大值最小值灰度值的对比度拉伸
	int m_defalt_singlepatern;//默认只有一个锐化模板
	bool m_drawon;//判断是否继续绘图
	bool m_recover;//是否是图像复原处理
	int m_recoverNum;//设置个数
	int m_last_recoverNum;//设置个数

	int m_hsum;//直方图灰度总数
	int *m_intensity;//直方图的灰度值

	//bool m_facecut;//判断是否进行人脸识别
	int m_last_filter;//用于人脸分割中识别上一个所采用的滤波
	Mat m_filterMat;//用于保存滤波过后的图片用于进行人脸分割

	

public:
	//CPImageDoc * CId;
	CPImageApp();
	~CPImageApp();
	void MatToCImage(Mat& mat, CImage& cimage);
	// CImage结构到Mat结构的转化
	void CImageToMat(CImage& cImage, Mat& mat);
	Mat ReadImage();
	void ShowImage(Mat& mat);
	void RGBtoGRAY(Mat& mat,Mat& );

	void OnMenu();

	void OnFourierTransform(/*Mat,*/int choice/*, int pos_x, int pos_y*/);//傅里叶变换
	void OnDCTTransform(int choice);//DCT变换
	void OnAnticolorChange();//反色变换
	void OnPiecewiseLinearTransform();//分段线性变换
	void OnLogTransform();//对数变换
	//void OnPowerShow();//幂次变换
	void OnHistogramGrayShow();//直方图
	void OnHistogramEqualizationShow();//直方图均衡化
	void OnHistogramRegularizationShow();//直方图规定化
	//void OnFilterSmoothShow();//
	void OnAverageFilterShow();//均值滤波
	void OnMedianFilterShow();//中值滤波
	void OnMaxFilterShow();//最大值滤波
	void OnLaFilterShow();//空域锐化拉普拉斯算子
	void OnRobertsShow(); //空域锐化 Roberts算子
	void OnPrewittShow(); //空域锐化 prewitt算子
	//void OnSobelShow(); //空域锐化 sobel算子
	void OnIlpfShow();//频域理想滤波器
	void OnBlpfShow();//频域巴特沃斯低通滤波器
	void OnBhpfShow();//频域巴特沃斯高通滤波器
	void OnGlpfShow();//高斯低通滤波 //高斯高通滤波 
	void OnLightShow();//加亮点
	

	Mat OnFFT(Mat);//傅里叶变换

	void GrayMin();
	void GrayMax();
	void GrayMean();

	void saltAndPeper(Mat &, int);
	void getMatrix(int);//获取矩阵维数
	void getText(float* text);//获取矩阵内容
	void getSharpenText(int* ,int,int);//获取矩阵内容
	
	void getDefault(bool);
	void getGuiDingHuaPath();
	void setDrawonStatu(bool);

	Mat freqfilt(Mat &scr,Mat &blur);//进行傅里叶变换

	int foundThreshold(int, int, float, Mat,float );
	void getHis(int, int *);

	

	

	float m_hfilter[16][16];

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




	enum 
	{ 
		MIN = 0,
		MAX = 1,
		MEAN = 2
	};

// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual void OnFileOpen();
	//virtual void OnSize(UNIT nType, int cx, int cy);

// 实现
	afx_msg void OnAppAbout();
	afx_msg void OnTransformChoiceF();
	afx_msg void OnTransformChoiceFR();
	afx_msg void OnTransformChoiceDCT();
	afx_msg void OnTransformChoiceDCTR();
	//afx_msg void OnFourierTransform();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnGltInverse();//灰度反色变换
	afx_msg void OnScretch();//对比度拉伸
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClicked2();
	afx_msg void OnLayer();
	afx_msg void OnBitLayer();
	afx_msg void OnGltLogarithm();
	afx_msg void OnHistogramGray();//直方图显示
	afx_msg void OnHistogramEqualization();
	afx_msg void OnHistogramRegularization();
	//afx_msg void OnFilterSmooth();
	afx_msg void OnAverageFilter();
	afx_msg void OnMedianFilter();
	afx_msg void OnMaxFilter();
	afx_msg void OnMin();
	afx_msg void OnLaFilter();//空域锐化 拉普拉斯算子
	afx_msg void OnRoberts();//空域锐化 Roberts 算子
	afx_msg void OnPrewitt(); //空域锐化 prewitt 算子
	afx_msg void OnSobel();
	afx_msg void OnHoriVert();

	//afx_msg void OnPower();

	afx_msg void OnTest();
	
	afx_msg void OnLaGray();
	afx_msg void OnIlpf();
	
	afx_msg void OnBlpf();
	afx_msg void OnBhpf();
	afx_msg void OnGlpf();
	afx_msg void OnGhpf();
	afx_msg void OnIhpf();
	afx_msg void OnLight();//加亮点
	
};

extern CPImageApp theApp;

class CSTRETCHDlg :
	public CDialogEx
{
public:
	CSTRETCHDlg(void);
	~CSTRETCHDlg(void);
};

