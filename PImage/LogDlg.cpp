// LogDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PImage.h"
#include "LogDlg.h"
#include "afxdialogex.h"


// CLogDlg 对话框

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
	if(m_filterType == IDM_GLT_LOGARITHM )//对数变换
	{
		GetDlgItem(IDC_STATIC_LOG)->SetWindowText("请输入系数:");
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


// CLogDlg 消息处理程序


void CLogDlg::OnBnClickedOk()
{
	CString text;
	GetDlgItem(IDC_LOGEDIT)->GetWindowText(text);
	m_text[0] = _ttof(text);//cstring转换成int
	if(m_text[0] == NULL )
	{
		MessageBox("请输入系数！");
		m_drawon = false;
	}
	theApp.getText(m_text);
	theApp.setDrawonStatu(m_drawon);//设置绘图状态
	CDialogEx::OnOK();
}


void CLogDlg::OnBnClickedCancel()
{
	m_drawon = false;
	theApp.setDrawonStatu(m_drawon);//设置绘图状态
	CDialogEx::OnCancel();
}
