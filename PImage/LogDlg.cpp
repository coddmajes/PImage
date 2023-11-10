// LogDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PImage.h"
#include "LogDlg.h"
#include "afxdialogex.h"


// CLogDlg �Ի���

IMPLEMENT_DYNAMIC(CLogDlg, CDialogEx)

CLogDlg::CLogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLogDlg::IDD, pParent)
{
	m_drawon = true;
}

CLogDlg::~CLogDlg()
{
}

BOOL CLogDlg::OnInitDialog()
{
	SetWindowText(m_title);
	if(m_filterType == IDM_THRESHOLD ) //��ֵ����ʱ
	{
		GetDlgItem(IDC_STATIC_LOG)->SetWindowText("������T0:");
	}
	else if(m_filterType == IDM_GLT_LOGARITHM )//�����任
	{
		GetDlgItem(IDC_STATIC_LOG)->SetWindowText("������ϵ��:");
	}
	else if(m_filterType == IDM_FIELD_GROW )//��������
	{
		GetDlgItem(IDC_STATIC_LOG)->SetWindowText("��������ֵϵ��:");
		GetDlgItem(IDC_LOGEDIT)->SetWindowText("0.02");
	}
	return true;
}

void CLogDlg::setDlgTitle(CString title,int type)
{
	m_title = title;
	m_filterType = type;
}
void CLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_EDIT1, m_editLog);
}


BEGIN_MESSAGE_MAP(CLogDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLogDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CLogDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CLogDlg ��Ϣ�������


void CLogDlg::OnBnClickedOk()
{
	CString text;
	GetDlgItem(IDC_LOGEDIT)->GetWindowText(text);
	m_text[0] = _ttof(text);//cstringת����int
	if(m_text[0] == NULL )
	{
		MessageBox("������ϵ����");
		m_drawon = false;
	}
	theApp.getText(m_text);
	theApp.setDrawonStatu(m_drawon);//���û�ͼ״̬
	CDialogEx::OnOK();
}


void CLogDlg::OnBnClickedCancel()
{
	m_drawon = false;
	theApp.setDrawonStatu(m_drawon);//���û�ͼ״̬
	CDialogEx::OnCancel();
}
