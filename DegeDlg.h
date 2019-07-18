#pragma once
#define EDIT_ID 50000

// CDegeDlg 对话框

class CDegeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDegeDlg)
private:
	CString m_staticCaption[16*16];
	CString m_title; //对话框标题
	
public:
	CDegeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDegeDlg();

// 对话框数据
	enum { IDD = IDD_DEGEDLG };

	void setDlgTitle(CString);//设置对话框标题
	void setHFilter(float a[16][16]);
	float b[16][16];
	CPtrArray m_MyEdits;//

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDeok();
};
