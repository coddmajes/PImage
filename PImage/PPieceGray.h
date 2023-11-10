#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// PPieceGray �Ի���

class PPieceGray : public CDialogEx
{
	DECLARE_DYNAMIC(PPieceGray)

private:
	CString m_title; //�Ի������
	float m_text[4];
	bool default;
	bool m_drawon;//�ж��Ƿ������ͼ
	int m_filterType;//�˲�������
public:
	void setDlgTitle(CString title,int type);//���öԻ������

public:
	PPieceGray(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PPieceGray();
	virtual BOOL OnInitDialog();

// �Ի�������
	enum { IDD = IDD_PIECE_GRAY,
	IDM_LAYER = ID_LAYER,
	IDM_DSCRETCH = ID_DSCRETCH,};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
