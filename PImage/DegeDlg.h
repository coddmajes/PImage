#pragma once
#define EDIT_ID 50000

// CDegeDlg �Ի���

class CDegeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDegeDlg)
private:
	CString m_staticCaption[16*16];
	CString m_title; //�Ի������
	
public:
	CDegeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDegeDlg();

// �Ի�������
	enum { IDD = IDD_DEGEDLG };

	void setDlgTitle(CString);//���öԻ������
	void setHFilter(float a[16][16]);
	float b[16][16];
	CPtrArray m_MyEdits;//

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDeok();
};
