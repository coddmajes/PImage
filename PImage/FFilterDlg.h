#pragma once


// CFFilterDlg �Ի���

class CFFilterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFFilterDlg)

private:
	CString m_title; //�Ի������
	bool m_drawon;//�ж��Ƿ������ͼ
	int m_filterType;//�˲�������
	float m_text[2];

public:
	void setDlgTitle(CString,int);//���öԻ������

public:
	CFFilterDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFFilterDlg();
	virtual BOOL OnInitDialog();

// �Ի�������
	enum { IDD = IDD_F_FILTERDLG,
		IDM_BLPF = ID_BLPF,//���������˹��ͨ�˲���
		IDM_BHPF = ID_BHPF,//���������˹��ͨ�˲���
		IDM_LAYER = ID_LAYER,
	};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
