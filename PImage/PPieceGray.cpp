// PPieceGray.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PImage.h"
#include "PPieceGray.h"
#include "afxdialogex.h"


// PPieceGray �Ի���

IMPLEMENT_DYNAMIC(PPieceGray, CDialogEx)

PPieceGray::PPieceGray(CWnd* pParent /*=NULL*/)
	: CDialogEx(PPieceGray::IDD, pParent)
{

}

PPieceGray::~PPieceGray()
{
}

BOOL PPieceGray::OnInitDialog()
{
	SetWindowText(m_title);
	default = false;
	m_drawon = true;
	
	return true;
}

void PPieceGray::setDlgTitle(CString title,int type)
{
	m_title = title;
}

void PPieceGray::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	/*
	DDX_Control(pDX, IDC_EDIT2, m_editAx);
	DDX_Control(pDX, IDC_EDIT4, m_editAy);
	DDX_Control(pDX, IDC_EDIT3, m_editBx);
	DDX_Control(pDX, IDC_EDIT5, m_editBy);*/
	
}


BEGIN_MESSAGE_MAP(PPieceGray, CDialogEx)
	ON_BN_CLICKED(IDOK, &PPieceGray::OnBnClickedOk)
	ON_BN_CLICKED(IDOK3, &PPieceGray::OnBnClickedOk3)
END_MESSAGE_MAP()


// PPieceGray ��Ϣ�������


void PPieceGray::OnBnClickedOk()
{
	UpdateData(true);
	CString textAx,textAy,textBx,textBy;
	GetDlgItem(IDC_EDIT2)->GetWindowText(textAx);
	//m_editAx.GetWindowText(textAx);
	m_text[0] = _ttoi(textAx);//cstringת����int
	GetDlgItem(IDC_EDIT4)->GetWindowText(textAy);
	m_text[1] = _ttoi(textAy);//cstringת����int
	GetDlgItem(IDC_EDIT3)->GetWindowText(textBx);
	m_text[2] = _ttoi(textBx);//cstringת����int
	GetDlgItem(IDC_EDIT5)->GetWindowText(textBy);
	m_text[3] = _ttoi(textBy);//cstringת����int
	if(m_text[0] == NULL || m_text[1] == NULL ||m_text[2] == NULL ||m_text[3] == NULL)
	{
		MessageBox("�������������꣡");
		m_drawon = false;
	}
	
	//default = false;
	theApp.getDefault(default);
	theApp.setDrawonStatu(m_drawon);//���û�ͼ״̬
	theApp.getText(m_text);
	CDialogEx::OnOK();
}


void PPieceGray::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void PPieceGray::OnBnClickedOk3()//Ĭ�ϰ�ť
{
	
	default = true;
	theApp.getDefault(default);
	CDialogEx::OnOK();
}
