
// PImage.h : PImage Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif
#include "resource.h"       // ������
#include "PImageDoc.h"
#include <afxctl.h>
#include "cv.h"
#include "highgui.h"
#include "afxdialogex.h"
#include "FFilterDlg.h"
#include "DegeDlg.h"
#include<algorithm>
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
// �йش����ʵ�֣������ PImage.cpp
//

class CPImageApp : public CWinApp
{
private:
	CString m_guidinghuaPath;
	CString m_openFilePath;
	CString m_histFilePath;
	CImage m_image;
	CImage m_leftImage;
	CImage m_img[6];//װһ��ͼƬ
	Mat m_mat[6];//װһ�� mat
	int m_choice;//����ѡ������ĸ��˵�
	int m_modelMatrix;//ģ�����
	//int m_text[TEXT_SIZE];//ģ�����ݾ���
	float* m_text;
	int* m_leftText;
	int* m_rightText;
	bool m_default;//����Ĭ�ϼ������ֵ��Сֵ�Ҷ�ֵ�ĶԱȶ�����
	int m_defalt_singlepatern;//Ĭ��ֻ��һ����ģ��
	bool m_drawon;//�ж��Ƿ������ͼ
	bool m_recover;//�Ƿ���ͼ��ԭ����
	int m_recoverNum;//���ø���
	int m_last_recoverNum;//���ø���

	int m_hsum;//ֱ��ͼ�Ҷ�����
	int *m_intensity;//ֱ��ͼ�ĻҶ�ֵ
	bool m_odk;

	//bool m_facecut;//�ж��Ƿ��������ʶ��
	int m_last_filter;//���������ָ���ʶ����һ�������õ��˲�
	Mat m_filterMat;//���ڱ����˲������ͼƬ���ڽ��������ָ�
	Mat m_filterMatf;//���ڱ���ԭͼ
	Mat m_filterMatl;
	Mat m_filterMatr;
	Mat m_filterMath;
	Mat m_filterMatv;
	Mat m_filterMatar;//Roberts�ܵ�����
	Mat m_filterMathv;//Roberts�ܵ�����

	Mat m_saveFace;//���������ͼ
	Mat m_saveFaceThre;//���������ͼ
	Mat m_savePic[5];//�����ͼƬ
	Mat m_savePics;//�����ͼƬ

	Mat m_reverseFMat;

	

public:
	//CPImageDoc * CId;
	CPImageApp();
	~CPImageApp();
	void MatToCImage(Mat& mat, CImage& cimage);
	// CImage�ṹ��Mat�ṹ��ת��
	void CImageToMat(CImage& cImage, Mat& mat);
	Mat ReadImage();
	void ShowImage(Mat& mat);
	void RGBtoGRAY(Mat& mat,Mat& );

	void OnMenu();

	void OnFourierTransform(/*Mat,*/int choice/*, int pos_x, int pos_y*/);//����Ҷ�任
	void OnDCTTransform(int choice);//DCT�任
	void OnAnticolorChange();//��ɫ�任
	void OnPiecewiseLinearTransform();//�ֶ����Ա任
	void OnLogTransform();//�����任
	//void OnPowerShow();//�ݴα任
	void OnHistogramGrayShow();//ֱ��ͼ
	void OnHistogramEqualizationShow();//ֱ��ͼ���⻯
	void OnHistogramRegularizationShow();//ֱ��ͼ�涨��
	//void OnFilterSmoothShow();//
	void OnAverageFilterShow();//��ֵ�˲�
	void OnMedianFilterShow();//��ֵ�˲�
	void OnMaxFilterShow();//���ֵ�˲�
	void OnLaFilterShow();//������������˹����
	void OnRobertsShow(); //������ Roberts����
	void OnPrewittShow(); //������ prewitt����
	//void OnSobelShow(); //������ sobel����
	void OnIlpfShow();//Ƶ�������˲���
	void OnBlpfShow();//Ƶ�������˹��ͨ�˲���
	void OnBhpfShow();//Ƶ�������˹��ͨ�˲���
	void OnGlpfShow();//��˹��ͨ�˲� //��˹��ͨ�˲� 
	void OnLightShow();//������
	void OnThresholdShow(); //��ֵ����
	void OnEdgeDetectShow();//���ڱ�Ե���
	void OnEdgeCannyShow();//canny����
	void OnFieldGrowShow();//��������
	void OnFieldSpoShow();//���������ۺ�
	
	void onFaceCutShow();//���������ָ�
	//void OnFaceThreShow();//�����ָ�--��ֵ����
	//void OnFaceEdgeShow();//�����ָ�--��Ե���
	//void OnFaceFcutShow();//�����ָ�--�ָ�ͼ��
	void OnCutTagShow();//���Էָ���
	void OnFaceEdgeShow(int);//���Էָ���
	void OnFaceExtraShow();//�����ָ�

	Mat OnFFT(Mat);//����Ҷ�任

	int countWhite(Mat,int,int);//����������Χ�İ׵����
	Mat screenShoot(Mat,Point,Point);//������ȡͼ��

	void GrayMin();
	void GrayMax();
	void GrayMean();

	void saltAndPeper(Mat &, int);
	void getMatrix(int);//��ȡ����ά��
	void getText(float* text);//��ȡ��������
	void getSharpenText(int* ,int,int);//��ȡ��������
	
	void getDefault(bool);
	void getGuiDingHuaPath();
	void setDrawonStatu(bool);

	Mat freqfilt(Mat &scr,Mat &blur);//���и���Ҷ�任

	int foundThreshold(int, int, float, Mat,float );
	void getHis(int, int *);

	void splitFiled(Mat,int,LinkStack&,Point,Point);
	void mergeField();

	

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
		IDM_THRESHOLD = ID_THRESHOLD, //��ֵ����
		IDM_GLOBAL_THRESHOLD = ID_GLOBAL_THRESHOLD,//����ȫ����ֵ����
		IDM_OTSU_THRESHOLD = ID_OTSU_THRESHOLD,//OTSU�������ֵ����
		IDM_EDGE_DETECT = ID_EDGE_DETECT,//���ڱ�Ե���
		IDM_EDGE_SOBEL = ID_EDGE_SOBEL,//���ڱ�ԵSOBEL����
		IDM_EDGE_LAPLA = ID_EDGE_LAPLA,//���ڱ�ԵLAPLA
		IDM_EDGE_LOG = ID_EDGE_LOG,//���ڸ�˹��������˹����
		IDM_EDGE_CANNY = ID_EDGE_CANNY,//CANNY����
		IDM_EDGE_HOUGH = ID_EDGE_HOUGH, //����任
		IDM_FIELD_GROW = ID_FIELD_GROW,//��������
		IDM_FIELD_SPO = ID_FIELD_SPO,//���������ۺ�
		IDM_FACE_CUT = ID_FACE_CUT,//�����ָ�
		IDM_FACE_THRE = ID_FACE_THRE,//�����ָ�--��ֵ����
		IDM_FACE_EDGE = ID_FACE_EDGE,//�����ָ�--��Ե���
		IDM_FACE_FCUT = ID_FACE_FCUT,//�����ָ�--ͼƬ�ָ�
		IDM_FACE_TAG = ID_FACE_TAG,//�����ָ�--�ָ���
		IDM_CUT_TAG = ID_CUT_TAG,//�ָ���
		IDM_FACE_TOP = ID_FACE_TOP,//��ȡ��ͷ
		IDM_FACE_LEFT = ID_FACE_LEFT,//��ȡ������
		IDM_FACE_RIGHTC = ID_FACE_RIGHTC,//��ȡ������
		IDM_FACE_NOSE = ID_FACE_NOSE,//��ȡ����
		IDM_FACE_BOTTOM = ID_FACE_BOTTOM,//��ȡ�°�
		
		
	};

	enum 
	{ 
		MIN = 0,
		MAX = 1,
		MEAN = 2
	};

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual void OnFileOpen();
	//virtual void OnSize(UNIT nType, int cx, int cy);

// ʵ��
	afx_msg void OnAppAbout();
	afx_msg void OnTransformChoiceF();
	afx_msg void OnTransformChoiceFR();
	afx_msg void OnTransformChoiceDCT();
	afx_msg void OnTransformChoiceDCTR();
	//afx_msg void OnFourierTransform();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnGltInverse();//�Ҷȷ�ɫ�任
	afx_msg void OnScretch();//�Աȶ�����
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClicked2();
	afx_msg void OnLayer();
	afx_msg void OnBitLayer();
	afx_msg void OnGltLogarithm();
	afx_msg void OnHistogramGray();//ֱ��ͼ��ʾ
	afx_msg void OnHistogramEqualization();
	afx_msg void OnHistogramRegularization();
	//afx_msg void OnFilterSmooth();
	afx_msg void OnAverageFilter();
	afx_msg void OnMedianFilter();
	afx_msg void OnMaxFilter();
	afx_msg void OnMin();
	afx_msg void OnLaFilter();//������ ������˹����
	afx_msg void OnRoberts();//������ Roberts ����
	afx_msg void OnPrewitt(); //������ prewitt ����
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
	afx_msg void OnLight();//������
	afx_msg void OnWhite();//����
	afx_msg void OnScreshot();//��ȡ����
	afx_msg void OnFrestore();//����ԭ
	afx_msg void OnRestorefuc();//�˻�����
	afx_msg void OnReverfilter();//���˲�
	afx_msg void OnThreshold(); //��ֵ����
	afx_msg void OnGlobalThreshold();
	afx_msg void OnOtsuThreshold();
	afx_msg void OnEdgeDetect();//���ڱ�Ե���
	afx_msg void OnEdgeSobel();
	afx_msg void OnEdgeLapla();
	afx_msg void OnEdgeLog();
	afx_msg void OnEdgeHough();
	afx_msg void OnEdgeCanny();
	afx_msg void OnFieldGrow();
	afx_msg void OnFieldSpo();
	afx_msg void OnFaceCut();
	afx_msg void OnCutTag();
	afx_msg void OnFaceThre();
	afx_msg void OnFaceEdge();
	afx_msg void OnFaceFcut();
	afx_msg void OnFaceTag();
	afx_msg void OnFaceTop();
	afx_msg void OnFaceLeft();
	afx_msg void OnFaceRight();
	afx_msg void OnFaceNose();
	afx_msg void OnFaceBottom();
	afx_msg void OnFileSave();
};

extern CPImageApp theApp;

class CSTRETCHDlg :
	public CDialogEx
{
public:
	CSTRETCHDlg(void);
	~CSTRETCHDlg(void);
};

