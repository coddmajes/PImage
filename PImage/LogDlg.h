#pragma once
#include "afxwin.h"


// CLogDlg �Ի���

class CLogDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLogDlg)
private:
	CString m_title; //�Ի������
	float m_text[1];
	bool m_drawon;//�ж��Ƿ������ͼ
	int m_filterType;//�˲�������

public:
	void setDlgTitle(CString,int);//���öԻ������
public:
	CLogDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLogDlg();
	virtual BOOL OnInitDialog();

// �Ի�������
	enum { IDD = IDD_LOG,
			IDM_GLT_LOGARITHM = ID_GLT_LOGARITHM,//�����任
			IDM_THRESHOLD = ID_THRESHOLD, //��ֵ����
			IDM_FIELD_GROW = ID_FIELD_GROW,//��������

	};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//CEdit m_editLog;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
