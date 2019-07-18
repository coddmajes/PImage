// DegeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PImage.h"
#include "DegeDlg.h"
#include "afxdialogex.h"


// CDegeDlg 对话框

IMPLEMENT_DYNAMIC(CDegeDlg, CDialogEx)

CDegeDlg::CDegeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDegeDlg::IDD, pParent)
{

}

CDegeDlg::~CDegeDlg()
{
}
void CDegeDlg::setDlgTitle(CString title)
{
	m_title = title;
	//m_filterType = type;
}
void CDegeDlg::setHFilter(float a[16][16])
{
	for(int i =0; i<16; i++)
	{
		for(int j =0; j<16; j++)
		{
			b[i][j] = a[i][j];
		}
	}

}


BOOL CDegeDlg::OnInitDialog()
{
	SetWindowText(m_title);
	/*
	CRect rectOK,rectMODEL,rect;
	GetClientRect(&rect);//获取客户区宽度
	GetDlgItem(IDDEOK)->GetWindowRect(&rectOK);//获取确定btn的坐标
	GetDlgItem(IDC_MODEL_CONTENT)->GetWindowRect(&rectMODEL);//获取 模板静态文本的坐标
	
	ScreenToClient(&rectOK);
	ScreenToClient(&rectMODEL);

	CStatic *p_MyStatic;
	CEdit *p_MyEdit;
	//int modelWidth = rect.Width()- 2 * rectMODEL.left; //宽度取 model 对齐
	int firstWidthSpace = rectMODEL.left;//首个宽度空隙
	int perWidth = rectMODEL.left - 20;//设置每个edit的宽度
	int perHight = rectMODEL.bottom - rectMODEL.top; //设置每个edit的高度
	int spaceWidth = rectMODEL.left - 50;//设置每个edit之间的空隙
	int spaceHight = perHight-10; //设置每个edit之间的空隙
	int top = rectMODEL.bottom;//设置第一排 edit的顶部位置

	for(int i =0; i<16; i++)
	{
		for(int j =0; j<16; j++)
		{
			p_MyStatic = new CStatic();
			p_MyEdit = new CEdit();

			int editLeft = j*perWidth + spaceWidth * j + firstWidthSpace;//edit本身宽度 + 宽度空隙 +首个宽度空隙
			int editTop = top+spaceHight*(i+1)+ perHight * i;//第一排edit的顶部位置 + 高度空隙 + edit本身高度
			int editRight = (j+1)*perWidth + spaceWidth * j  + firstWidthSpace;//edit
			int editBottom = top+spaceHight*(i+1)+ perHight * (i+1);//第一排edit的顶部位置 + 高度空隙 + edit本身高度

			
			p_MyEdit->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, CRect(editLeft,editTop,
				editRight, editBottom),this,EDIT_ID+(j+1)+(i*16));

			//设置模板内容
			
			m_staticCaption[j+(i*16)].Format("%d",b[i][j]);

			p_MyEdit->SetWindowText(m_staticCaption[j+(i*16)]);
			if(p_MyEdit != NULL)
			{
				m_MyEdits.Add((void*)p_MyEdit);
			}

		}
	}*/
	return true;
}
void CDegeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDegeDlg, CDialogEx)
	ON_BN_CLICKED(IDDEOK, &CDegeDlg::OnBnClickedDeok)
END_MESSAGE_MAP()


// CDegeDlg 消息处理程序


void CDegeDlg::OnBnClickedDeok()
{
	CDialogEx::OnOK();
}
