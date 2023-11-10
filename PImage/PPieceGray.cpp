// PPieceGray.cpp : 实现文件
//

#include "stdafx.h"
#include "PImage.h"
#include "PPieceGray.h"
#include "afxdialogex.h"


// PPieceGray 对话框

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


// PPieceGray 消息处理程序


void PPieceGray::OnBnClickedOk()
{
	UpdateData(true);
	CString textAx,textAy,textBx,textBy;
	GetDlgItem(IDC_EDIT2)->GetWindowText(textAx);
	//m_editAx.GetWindowText(textAx);
	m_text[0] = _ttoi(textAx);//cstring转换成int
	GetDlgItem(IDC_EDIT4)->GetWindowText(textAy);
	m_text[1] = _ttoi(textAy);//cstring转换成int
	GetDlgItem(IDC_EDIT3)->GetWindowText(textBx);
	m_text[2] = _ttoi(textBx);//cstring转换成int
	GetDlgItem(IDC_EDIT5)->GetWindowText(textBy);
	m_text[3] = _ttoi(textBy);//cstring转换成int
	if(m_text[0] == NULL || m_text[1] == NULL ||m_text[2] == NULL ||m_text[3] == NULL)
	{
		MessageBox("请输入两点坐标！");
		m_drawon = false;
	}
	
	//default = false;
	theApp.getDefault(default);
	theApp.setDrawonStatu(m_drawon);//设置绘图状态
	theApp.getText(m_text);
	CDialogEx::OnOK();
}


void PPieceGray::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void PPieceGray::OnBnClickedOk3()//默认按钮
{
	
	default = true;
	theApp.getDefault(default);
	CDialogEx::OnOK();
}
