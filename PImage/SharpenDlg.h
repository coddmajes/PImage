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
// CSharpenDlg �Ի���

class CSharpenDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSharpenDlg)

public:
	void creatEdit(int );
	void setDlgTitle(CString, int);//���öԻ������
	void getData(int);
	void OnClose(CPtrArray &);//��������������ָ��

public:
	CSharpenDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSharpenDlg();

// �Ի�������
	enum { IDD = IDD_SHARPEN,
		IDM_ROBERTS = ID_ROBERTS,
		IDM_PREWITT = ID_PREWITT,//prewitt����
		IDM_SOBEL = ID_SOBEL,
		IDM_HORI_VERT = ID_HORI_VERT, //ˮƽ��ֱ����
		IDM_FACE_CUT = ID_FACE_CUT,//�����ָ�
	};

private:
	CString m_title; //�Ի������
	int m_filterType;//�˲�������
	CString m_staticLeftCaption[9];
	CString m_staticRightCaption[9];
	//CPtrArray m_MyEdits;
	CPtrArray m_MyLeftEdits;//
	CPtrArray m_MyRightEdits;//
	int m_lefttext[9];
	int m_righttext[9];
	int m_patern_default;//�б��Ƿ�Ĭ��һ��ģ��
	bool m_drawon;//�ж��Ƿ������ͼ

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSharpenOk();
	int m_radiobtngroup;
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedCancel();
};
