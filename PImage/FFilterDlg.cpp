// FFilterDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PImage.h"
#include "FFilterDlg.h"
#include "afxdialogex.h"


// CFFilterDlg �Ի���

IMPLEMENT_DYNAMIC(CFFilterDlg, CDialogEx)

CFFilterDlg::CFFilterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFFilterDlg::IDD, pParent)
{

}

CFFilterDlg::~CFFilterDlg()
{
}

void CFFilterDlg::setDlgTitle(CString title,int type)
{
	m_title = title;
	m_filterType = type;
}

BOOL CFFilterDlg::OnInitDialog()
{
	SetWindowText(m_title);
	if(m_filterType != IDM_BHPF && m_filterType != IDM_BLPF && m_filterType != IDM_LAYER) //���ǰ�����˹��ͨ�͸�ͨ�˲� �Ҷȼ��ֲ�ʱ
	{
		CEdit *edit = (CEdit*)GetDlgItem(IDC_EDIT_LEVEL);
		edit->ShowWindow(FALSE); //���ظÿؼ�
		GetDlgItem(IDC_STATIC_N)->ShowWindow(FALSE); //���ظÿؼ�;
		GetDlgItem(IDC_STATIC_TITLE)->SetWindowText("�������˲����İ뾶:");
		GetDlgItem(IDC_STATIC_R)->SetWindowText("�뾶D0:");

	}
	else if (m_filterType == IDM_LAYER)
	{
		CEdit *edit = (CEdit*)GetDlgItem(IDC_EDIT_LEVEL);
		edit->ShowWindow(TRUE); //���ظÿؼ�
		GetDlgItem(IDC_STATIC_N)->ShowWindow(TRUE); //���ظÿؼ�;
		GetDlgItem(IDC_STATIC_TITLE)->SetWindowText("�������ض��Ҷȼ���Χ:");
		GetDlgItem(IDC_STATIC_R)->SetWindowText("A:");
		GetDlgItem(IDC_STATIC_N)->SetWindowText("B:");
	}
	else
	{
		CEdit *edit = (CEdit*)GetDlgItem(IDC_EDIT_LEVEL);
		edit->ShowWindow(TRUE); //���ظÿؼ�
		GetDlgItem(IDC_STATIC_N)->ShowWindow(TRUE); //���ظÿؼ�;
		GetDlgItem(IDC_STATIC_TITLE)->SetWindowText("�������˲����İ뾶�ͽ���:");
		GetDlgItem(IDC_STATIC_R)->SetWindowText("�뾶D0:");
		GetDlgItem(IDC_STATIC_N)->SetWindowText("����n:");
	}
	
	m_drawon = true;
	return true;
}


void CFFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFFilterDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CFFilterDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CFFilterDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CFFilterDlg ��Ϣ�������


void CFFilterDlg::OnBnClickedOk()
{
	CString textLevel,textSigma;
	GetDlgItem(IDC_EDIT_LEVEL)->GetWindowText(textLevel);//����
	m_text[0] = _ttof(textLevel);//cstringת����int
	GetDlgItem(IDC_EDIT_SIGMA)->GetWindowText(textSigma);
	if(textSigma == "0")
	{
		textSigma = "1";
	}
	m_text[1] = _ttof(textSigma);//cstringת����int
	
	if(m_filterType != IDM_BHPF && m_filterType != IDM_BLPF && m_filterType != IDM_LAYER) //������˹��ͨ�͸�ͨ�˲�ʱ
	{
		if(m_text[1] == NULL )
		{
			MessageBox("������ϵ����");
			m_drawon = false;
		}
	}
	else
	{
		if(m_text[0] == NULL ||  m_text[1] == NULL)
		{
			MessageBox("������ϵ����");
			m_drawon = false;
		}
	}
	
	theApp.getText(m_text);
	theApp.setDrawonStatu(m_drawon);//���û�ͼ״̬
	CDialogEx::OnOK();
}


void CFFilterDlg::OnBnClickedCancel()
{
	m_drawon = false;
	theApp.setDrawonStatu(m_drawon);//���û�ͼ״̬
	CDialogEx::OnCancel();
}
