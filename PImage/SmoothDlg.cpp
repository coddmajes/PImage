// SmoothDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PImage.h"
#include "SmoothDlg.h"
#include "afxdialogex.h"

using namespace std;

// CSmoothDlg 对话框

IMPLEMENT_DYNAMIC(CSmoothDlg, CDialogEx)

CSmoothDlg::CSmoothDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSmoothDlg::IDD, pParent)
	, m_radioGroup(0)
{
	
}


CSmoothDlg::~CSmoothDlg()
{
	OnClose();
}

BOOL CSmoothDlg::OnInitDialog()
{
	SetWindowText(m_title);
	m_drawon = true;//判断是否继续绘图
	
	return true;
}

void CSmoothDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO3, m_radioGroup);
	
}


BEGIN_MESSAGE_MAP(CSmoothDlg, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO3, &CSmoothDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO5, &CSmoothDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO7, &CSmoothDlg::OnBnClickedRadio3)
	//ON_EN_CHANGE(IDC_EDIT1, &CSmoothDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(ID_SMOOTH_OK, &CSmoothDlg::OnBnClickedSmoothOk)
	ON_BN_CLICKED(IDCANCEL, &CSmoothDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CSmoothDlg 消息处理程序


void CSmoothDlg::OnBnClickedRadio3()
{
	UpdateData(true);
	chooseMode();
	//chooseMode();
	
}

void CSmoothDlg::OnClose()
{
	int n = m_MyEdits.GetSize();
	for(int i = 0; i<n; i++)
	{
		CEdit *pEdit = (CEdit*)m_MyEdits.GetAt(i);
		if(pEdit != NULL)
		{
			delete pEdit;
		}
		m_MyEdits[i] = NULL;
	}
	m_MyEdits.RemoveAll();
	CDialogEx::OnClose();
}

void CSmoothDlg::chooseMode()
{
	//CString m_staticCaption;
	CRect rectOK,rectMODEL,rect;
	GetClientRect(&rect);//获取客户区宽度
	GetDlgItem(ID_SMOOTH_OK)->GetWindowRect(&rectOK);//获取确定btn的坐标
	GetDlgItem(IDC_MODEL_CONTENT)->GetWindowRect(&rectMODEL);//获取 模板静态文本的坐标
	
	ScreenToClient(&rectOK);
	ScreenToClient(&rectMODEL);

	CStatic *p_MyStatic;
	CEdit *p_MyEdit;

	//int modelMartrix;
	switch (m_radioGroup)
	{
		case MODE_ZERO:
			m_modelMartrix = MATRIX_THREE;
			break;
		case MODE_ONE:
			m_modelMartrix = MATRIX_FIVE;
			break;
		case MODE_TWO:
			m_modelMartrix = MATRIX_SEVEN;
			break;
	}
	
	//GetDlgItem(IDC_STATIC_TITLE)->SetWindowText("请输入滤波器的半径:");

	//int modelWidth = rect.Width()- 2 * rectMODEL.left; //宽度取 model 对齐
	int firstWidthSpace = rectMODEL.left;//首个宽度空隙
	int perWidth = rectMODEL.left - 20;//设置每个edit的宽度
	int perHight = rectMODEL.bottom - rectMODEL.top; //设置每个edit的高度
	int spaceWidth = rectMODEL.left - 30;//设置每个edit之间的空隙
	int spaceHight = perHight-4; //设置每个edit之间的空隙
	int top = rectMODEL.bottom;//设置第一排 edit的顶部位置

	int logModeF[25] = {0,0,-1,0,0,
					   0,-1,-2,-1,0,
					   -1,-2,16,-2,-1,
					   0,-1,-2,-1,0,
					   0,0,-1,0,0};
	for(int i =0; i<m_modelMartrix; i++)
	{
		for(int j =0; j<m_modelMartrix; j++)
		{
			p_MyStatic = new CStatic();
			p_MyEdit = new CEdit();

			int editLeft = j*perWidth + spaceWidth * j + firstWidthSpace;//edit本身宽度 + 宽度空隙 +首个宽度空隙
			int editTop = top+spaceHight*(i+1)+ perHight * i;//第一排edit的顶部位置 + 高度空隙 + edit本身高度
			int editRight = (j+1)*perWidth + spaceWidth * j  + firstWidthSpace;//edit
			int editBottom = top+spaceHight*(i+1)+ perHight * (i+1);//第一排edit的顶部位置 + 高度空隙 + edit本身高度

			
			p_MyEdit->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, CRect(editLeft,editTop,
				editRight, editBottom),this,EDIT_ID+(j+1)+(i*m_modelMartrix));

			//设置模板内容
			if(m_filterType == IDM_AVERAGE_FILTER || m_filterType ==IDM_MEDIAN_FILTER || m_filterType ==IDM_MAX_FILTER ||m_filterType == IDM_MIN)
			{
				m_staticCaption[j+(i*m_modelMartrix)].Format("%d",1);
			}
			else if (m_filterType == IDM_LA_FILTER || m_filterType == IDM_LA_GRAY )
			{
				int value = j+(i*m_modelMartrix); //得到 坐标
				if(value%2 != 0 )
				{
					m_staticCaption[value].Format("%d",1);
				}
				else if(value == m_modelMartrix*m_modelMartrix/2) //如果是中间的那个值 
				{
					m_staticCaption[value].Format("%d",-(m_modelMartrix*m_modelMartrix/2));
				}
				else
				{
					m_staticCaption[value].Format("%d",0);
				}
				
			}
			
			p_MyEdit->SetWindowText(m_staticCaption[j+(i*m_modelMartrix)]);
			if(p_MyEdit != NULL)
			{
				m_MyEdits.Add((void*)p_MyEdit);
			}

		}
	}
}

void CSmoothDlg::setDlgTitle(CString title, int type)
{
	m_title = title;
	m_filterType = type;
}


/*
void CSmoothDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

//#1015

	// TODO:  在此添加控件通知处理程序代码
}*/


void CSmoothDlg::OnBnClickedSmoothOk()
{
	//用于获取模板数据
	int n =0;
	n = m_MyEdits.GetSize();
	if(n ==0 )
	{
		MessageBox("请选择模板大小！");
		m_drawon = false;
	}
	CString text;
	for(int i = 0; i<n; i++)
	{
		CEdit *pEdit = (CEdit*)m_MyEdits.GetAt(i);
		if(pEdit != NULL)
		{
			pEdit->GetWindowText(text);
			m_text[i] = _ttoi(text);//cstring转换成int 
		}
	}
	theApp.getMatrix(m_modelMartrix);
	theApp.setDrawonStatu(m_drawon);//设置绘图状态
	theApp.getText(m_text);
	CDialogEx::OnOK();
	//AfxGetMainWnd()->SendMessage(WM_CLOSE);
}




void CSmoothDlg::OnBnClickedCancel()
{
	m_drawon = false;
	theApp.setDrawonStatu(m_drawon);//设置绘图状态
	CDialogEx::OnCancel();
}
