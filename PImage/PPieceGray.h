#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// PPieceGray 对话框

class PPieceGray : public CDialogEx
{
	DECLARE_DYNAMIC(PPieceGray)

private:
	CString m_title; //对话框标题
	float m_text[4];
	bool default;
	bool m_drawon;//判断是否继续绘图
	int m_filterType;//滤波器类型
public:
	void setDlgTitle(CString title,int type);//设置对话框标题

public:
	PPieceGray(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PPieceGray();
	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_PIECE_GRAY,
	IDM_LAYER = ID_LAYER,
	IDM_DSCRETCH = ID_DSCRETCH,};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedOk();
	/*
	CEdit m_editAx;
	CEdit m_editAy;
	CEdit m_editBx;
	CEdit m_editBy;
	*/
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk3();
};
