#pragma once
#include "afxwin.h"


// CLogDlg 对话框

class CLogDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLogDlg)
private:
	CString m_title; //对话框标题
	float m_text[1];
	bool m_drawon;//判断是否继续绘图
	int m_filterType;//滤波器类型

public:
	void setDlgTitle(CString,int);//设置对话框标题
public:
	CLogDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLogDlg();
	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_LOG,
			IDM_GLT_LOGARITHM = ID_GLT_LOGARITHM,//对数变换

	};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//CEdit m_editLog;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
