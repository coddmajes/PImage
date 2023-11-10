#pragma once


// CFFilterDlg 对话框

class CFFilterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFFilterDlg)

private:
	CString m_title; //对话框标题
	bool m_drawon;//判断是否继续绘图
	int m_filterType;//滤波器类型
	float m_text[2];

public:
	void setDlgTitle(CString,int);//设置对话框标题

public:
	CFFilterDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFFilterDlg();
	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_F_FILTERDLG,
		IDM_BLPF = ID_BLPF,//理想巴特沃斯低通滤波器
		IDM_BHPF = ID_BHPF,//理想巴特沃斯高通滤波器
		IDM_LAYER = ID_LAYER,
	};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
