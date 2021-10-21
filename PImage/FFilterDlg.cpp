// FFilterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PImage.h"
#include "FFilterDlg.h"
#include "afxdialogex.h"


// CFFilterDlg 对话框

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
	if(m_filterType != IDM_BHPF && m_filterType != IDM_BLPF) //巴特沃斯低通和高通滤波时
	{
		CEdit *edit = (CEdit*)GetDlgItem(IDC_EDIT_LEVEL);
		edit->ShowWindow(FALSE); //隐藏该控件
		GetDlgItem(IDC_STATIC_N)->ShowWindow(FALSE); //隐藏该控件;
		GetDlgItem(IDC_STATIC_TITLE)->SetWindowText("请输入滤波器的半径:");

	}
	else
	{
		CEdit *edit = (CEdit*)GetDlgItem(IDC_EDIT_LEVEL);
		edit->ShowWindow(TRUE); //隐藏该控件
		GetDlgItem(IDC_STATIC_N)->ShowWindow(TRUE); //隐藏该控件;
		GetDlgItem(IDC_STATIC_TITLE)->SetWindowText("请输入滤波器的半径和阶数:");
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


// CFFilterDlg 消息处理程序


void CFFilterDlg::OnBnClickedOk()
{
	CString textLevel,textSigma;
	GetDlgItem(IDC_EDIT_LEVEL)->GetWindowText(textLevel);//阶数
	m_text[0] = _ttoi(textLevel);//cstring转换成int
	GetDlgItem(IDC_EDIT_SIGMA)->GetWindowText(textSigma);
	m_text[1] = _ttoi(textSigma);//cstring转换成int
	if(m_filterType != IDM_BHPF && m_filterType != IDM_BLPF) //巴特沃斯低通和高通滤波时
	{
		if(m_text[1] == NULL )
		{
			MessageBox("请输入系数！");
			m_drawon = false;
		}
	}
	else
	{
		if(m_text[0] == NULL ||  m_text[1] == NULL)
		{
			MessageBox("请输入系数！");
			m_drawon = false;
		}
	}
	
	theApp.getText(m_text);
	theApp.setDrawonStatu(m_drawon);//设置绘图状态
	CDialogEx::OnOK();
}


void CFFilterDlg::OnBnClickedCancel()
{
	m_drawon = false;
	theApp.setDrawonStatu(m_drawon);//设置绘图状态
	CDialogEx::OnCancel();
}
