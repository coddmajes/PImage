#pragma once
#include "afxwin.h"
#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
#define FIVE 5
#define SEVEN 7
#define EDIT_ID 10000

// CSmoothDlg �Ի���

class CSmoothDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSmoothDlg)

public:
	CSmoothDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSmoothDlg();

	void InitMode();//��ʼ��3*3ģ��
	void chooseMode();//ѡ��ģ��3*3
	void OnClose();//��������������ָ��
	void setDlgTitle(CString, int);//���öԻ������
	void OnClose(CPtrArray &);//��������������ָ��
	void creatEdit(int );
	//void setDlgType();//�ڶԻ��������˲�������
	

	enum { 
		MODE_ZERO = ZERO,
		MODE_ONE = ONE,
		MODE_TWO = TWO,
		MATRIX_THREE = THREE,
		MATRIX_FIVE = FIVE,
		MATRIX_SEVEN = SEVEN};

// �Ի�������
	enum { IDD = IDD_SMOOTH,
		IDM_AVERAGE_FILTER = ID_AVERAGE_FILTER,
		IDM_MEDIAN_FILTER = ID_MEDIAN_FILTER,
		IDM_MAX_FILTER = ID_MAX_FILTER,
		IDM_MIN = ID_MIN,
		IDM_LA_FILTER = ID_LA_FILTER,//������˹����
		IDM_LA_GRAY = ID_LA_GRAY,//������˹����
		IDM_ROBERTS = ID_ROBERTS,
		IDM_PREWITT = ID_PREWITT,//prewitt����
		IDM_SOBEL = ID_SOBEL,
		IDM_HORI_VERT = ID_HORI_VERT, //ˮƽ��ֱ����
		IDM_EDGE_LOG =ID_EDGE_LOG,//���ڸ�˹��������˹����
	};
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	int m_modelMartrix;//ģ������С
	CString m_staticCaption[SEVEN*SEVEN];
	float m_text[SEVEN*SEVEN];
	int m_filterType;//�˲�������
	CString m_title; //�Ի������
	bool m_drawon;//�ж��Ƿ������ͼ

public:
	int m_radioGroup;
	afx_msg void OnBnClickedRadio3();
	
	//CEdit m_edit2;
	//CEdit m_edit1;
	CPtrArray m_MyStatics;//���������ڱ��涯̬�����Ŀؼ���ַ
	CPtrArray m_MyEdits;//

	afx_msg void OnBnClickedSmoothOk();
	afx_msg void OnBnClickedCancel();
	//CString m_modelType;//ģ������
};
