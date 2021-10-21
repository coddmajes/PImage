#pragma once
#include "afxwin.h"
#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
#define FIVE 5
#define SEVEN 7
#define EDIT_ID 10000

// CSmoothDlg 对话框

class CSmoothDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSmoothDlg)

public:
	CSmoothDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSmoothDlg();

	void InitMode();//初始化3*3模板
	void chooseMode();//选择模板3*3
	void OnClose();//用来消除创建的指针
	void setDlgTitle(CString, int);//设置对话框标题
	//void setDlgType();//在对话框设置滤波器类型
	

	enum { 
		MODE_ZERO = ZERO,
		MODE_ONE = ONE,
		MODE_TWO = TWO,
		MATRIX_THREE = THREE,
		MATRIX_FIVE = FIVE,
		MATRIX_SEVEN = SEVEN};

// 对话框数据
	enum { IDD = IDD_SMOOTH,
		IDM_AVERAGE_FILTER = ID_AVERAGE_FILTER,
		IDM_MEDIAN_FILTER = ID_MEDIAN_FILTER,
		IDM_MAX_FILTER = ID_MAX_FILTER,
		IDM_MIN = ID_MIN,
		IDM_LA_FILTER = ID_LA_FILTER,//拉普拉斯算子
		IDM_LA_GRAY = ID_LA_GRAY,//拉普拉斯算子
		IDM_ROBERTS = ID_ROBERTS,
		IDM_PREWITT = ID_PREWITT,//prewitt算子
		IDM_SOBEL = ID_SOBEL,
		IDM_HORI_VERT = ID_HORI_VERT, //水平垂直算子

	};
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	int m_modelMartrix;//模板矩阵大小
	CString m_staticCaption[SEVEN*SEVEN];
	float m_text[SEVEN*SEVEN];
	int m_filterType;//滤波器类型
	CString m_title; //对话框标题
	bool m_drawon;//判断是否继续绘图

public:
	int m_radioGroup;
	afx_msg void OnBnClickedRadio3();
	
	//CEdit m_edit2;
	//CEdit m_edit1;
	CPtrArray m_MyStatics;//链表类用于保存动态创建的控件地址
	CPtrArray m_MyEdits;//

	afx_msg void OnBnClickedSmoothOk();
	afx_msg void OnBnClickedCancel();
	//CString m_modelType;//模板类型
};
