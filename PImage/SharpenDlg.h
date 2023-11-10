#pragma once

#define EDIT_LEFTID 80000
#define EDIT_RIGHTID 90000
#define LEFT 1
#define RIGHT 0
#define SINGLE_LEFT 0
#define SINGLE_RIGHT 1
#define DOUBLE_PATREN 2

#define ZERO 0
#define ONE 1
#define TWO 2
// CSharpenDlg 对话框

class CSharpenDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSharpenDlg)

public:
	void creatEdit(int );
	void setDlgTitle(CString, int);//设置对话框标题
	void getData(int);
	void OnClose(CPtrArray &);//用来消除创建的指针

public:
	CSharpenDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSharpenDlg();

// 对话框数据
	enum { IDD = IDD_SHARPEN,
		IDM_ROBERTS = ID_ROBERTS,
		IDM_PREWITT = ID_PREWITT,//prewitt算子
		IDM_SOBEL = ID_SOBEL,
		IDM_HORI_VERT = ID_HORI_VERT, //水平垂直算子
		IDM_FACE_CUT = ID_FACE_CUT,//人脸分割
	};

private:
	CString m_title; //对话框标题
	int m_filterType;//滤波器类型
	CString m_staticLeftCaption[9];
	CString m_staticRightCaption[9];
	//CPtrArray m_MyEdits;
	CPtrArray m_MyLeftEdits;//
	CPtrArray m_MyRightEdits;//
	int m_lefttext[9];
	int m_righttext[9];
	int m_patern_default;//判别是否默认一个模板
	bool m_drawon;//判断是否继续绘图

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSharpenOk();
	int m_radiobtngroup;
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedCancel();
};
