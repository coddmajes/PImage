// SharpenDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PImage.h"
#include "SharpenDlg.h"
#include "afxdialogex.h"


// CSharpenDlg 对话框

IMPLEMENT_DYNAMIC(CSharpenDlg, CDialogEx)

CSharpenDlg::CSharpenDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSharpenDlg::IDD, pParent)
	, m_radiobtngroup(0)
{

}

CSharpenDlg::~CSharpenDlg()
{
	if(m_MyLeftEdits.GetData() == NULL && m_MyRightEdits.GetData() == NULL)
	{
		return;
	}
	OnClose(m_MyLeftEdits);
	OnClose(m_MyRightEdits);
	
}
void CSharpenDlg::setDlgTitle(CString title, int type)
{
	m_title = title;
	m_filterType = type;
}
void CSharpenDlg::OnClose(CPtrArray & myEdits)
{
	int n = myEdits.GetSize();
	for(int i = 0; i<n; i++)
	{
		CEdit *pEdit = (CEdit*)myEdits.GetAt(i);
		if(pEdit != NULL)
		{
			delete pEdit;
		}
		myEdits[i] = NULL;
	}
	myEdits.RemoveAll();
	CDialogEx::OnClose();
}

void CSharpenDlg::creatEdit(int choice)
{
	CRect rectOK,rectMODEL,rect;
	GetClientRect(&rect);//获取客户区宽度
	GetDlgItem(ID_SHARPEN_OK)->GetWindowRect(&rectOK);//获取确定btn的坐标
	GetDlgItem(IDC_RADIO2)->GetWindowRect(&rectMODEL);//获取 模板静态文本的坐标
	
	ScreenToClient(&rectOK);
	ScreenToClient(&rectMODEL);

	CStatic *p_MyStatic;
	CEdit *p_MyEdit;

	//int modelWidth = rect.Width()- 2 * rectMODEL.left; //宽度取 model 对齐
	int firstWidthSpace = rectMODEL.left;//首个宽度空隙
	int perWidth = rectMODEL.left - 20;//设置每个edit的宽度
	int perHight = rectMODEL.bottom - rectMODEL.top; //设置每个edit的高度
	int spaceWidth = rectMODEL.left - 30;//设置每个edit之间的空隙
	int spaceHight = perHight-4; //设置每个edit之间的空隙
	int top = rectMODEL.bottom;//设置第一排 edit的顶部位置
	int matrix = 3;
	if( m_filterType == IDM_ROBERTS || m_filterType == IDM_HORI_VERT)
	{
		matrix = 2;
	}
	
	if(choice == RIGHT)
	{
		firstWidthSpace = firstWidthSpace + 3*perWidth + 3*spaceWidth;//首个宽度空隙
		
	}
	//int firstWidthSpace = rectMODEL.left;//首个宽度空隙
	

	for(int i =0; i<matrix; i++)
	{
		for(int j =0; j<matrix; j++)
		{
			p_MyStatic = new CStatic();
			p_MyEdit = new CEdit();

			int editLeft = j*perWidth + spaceWidth * j + firstWidthSpace;//edit本身宽度 + 宽度空隙 +首个宽度空隙
			int editTop = top+spaceHight*(i+1)+ perHight * i;//第一排edit的顶部位置 + 高度空隙 + edit本身高度
			int editRight = (j+1)*perWidth + spaceWidth * j  + firstWidthSpace;//edit
			int editBottom = top+spaceHight*(i+1)+ perHight * (i+1);//第一排edit的顶部位置 + 高度空隙 + edit本身高度

			if(choice == LEFT)
			{
				p_MyEdit->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, CRect(editLeft,editTop,
				editRight, editBottom),this,EDIT_LEFTID+(j+1)+(i*matrix));
			}
			else if(choice == RIGHT)
			{
				p_MyEdit->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, CRect(editLeft,editTop,
				editRight, editBottom),this,EDIT_RIGHTID+(j+1)+(i*matrix));
			}
			int value = j+(i*matrix); //得到 坐标

			//设置模板内容
			if(m_filterType == IDM_ROBERTS)
			{
				if(choice == LEFT)
				{
					if(value != 0 && value != 3)
					{
						m_staticLeftCaption[value].Format("%d",0);
					}
					else if(value == 0)
					{
						m_staticLeftCaption[value].Format("%d",-1);
					}
					else if (value == 3)
					{
						m_staticLeftCaption[value].Format("%d",1);
					}
					//p_MyEdit->SetWindowText(m_staticLeftCaption[value]);
				}
				else
				{
					if(value != 1 && value != 2)
					{
						m_staticRightCaption[value].Format("%d",0);
					}
					else if(value == 1)
					{
						m_staticRightCaption[value].Format("%d",-1);
					}
					else if (value == 2)
					{
						m_staticRightCaption[value].Format("%d",1);
					}
					//p_MyEdit->SetWindowText(m_staticRightCaption[value]);
				}
			}
			else if(m_filterType == IDM_HORI_VERT)
			{
				if(choice == LEFT)
				{
					if(value != 0 && value != 1)
					{
						m_staticLeftCaption[value].Format("%d",0);
					}
					else if(value == 0)
					{
						m_staticLeftCaption[value].Format("%d",-1);
					}
					else if (value == 1)
					{
						m_staticLeftCaption[value].Format("%d",1);
					}
					//p_MyEdit->SetWindowText(m_staticLeftCaption[value]);
				}
				else
				{
					if(value != 0 && value != 2)
					{
						m_staticRightCaption[value].Format("%d",0);
					}
					else if(value == 0)
					{
						m_staticRightCaption[value].Format("%d",-1);
					}
					else if (value == 2)
					{
						m_staticRightCaption[value].Format("%d",1);
					}
					//p_MyEdit->SetWindowText(m_staticRightCaption[value]);
				}
			}
			else if(m_filterType == IDM_PREWITT)
			{
				if(choice == LEFT)
				{
					if(value == 0 || value == 1 || value == 2)
					{
						m_staticLeftCaption[value].Format("%d",-1);
					}
					else if (value == 6 || value == 7 || value == 8)
					{
						m_staticLeftCaption[value].Format("%d",1);
					}
					else
					{
						m_staticLeftCaption[value].Format("%d",0);
					}
					//p_MyEdit->SetWindowText(m_staticLeftCaption[value]);
				}
				else
				{
					if(value == 0 || value == 3 || value == 6)
					{
						m_staticRightCaption[value].Format("%d",-1);
					}
					else if (value == 2 || value == 5 || value == 8)
					{
						m_staticRightCaption[value].Format("%d",1);
					}
					else
					{
						m_staticRightCaption[value].Format("%d",0);
					}
					//p_MyEdit->SetWindowText(m_staticRightCaption[value]);
				}
			}
			else if(m_filterType ==IDM_SOBEL )
			{
				if(choice == LEFT)
				{
					if(value == 0 || value == 2)
					{
						m_staticLeftCaption[value].Format("%d",-1);
					}
					else if(value == 1)
					{
						m_staticLeftCaption[value].Format("%d",-2);
					}
					else if (value == 6 || value == 8)
					{
						m_staticLeftCaption[value].Format("%d",1);
					}
					else if(value == 7)
					{
						m_staticLeftCaption[value].Format("%d",2);
					}
					else
					{
						m_staticLeftCaption[value].Format("%d",0);
					}
					//p_MyEdit->SetWindowText(m_staticLeftCaption[value]);
				}
				else
				{
					if(value == 0 || value == 6)
					{
						m_staticRightCaption[value].Format("%d",-1);
					}
					else if(value == 3)
					{
						m_staticRightCaption[value].Format("%d",-2);
					}
					else if (value == 2 || value == 8)
					{
						m_staticRightCaption[value].Format("%d",1);
					}
					else if(value == 5)
					{
						m_staticRightCaption[value].Format("%d",2);
					}
					else
					{
						m_staticRightCaption[value].Format("%d",0);
					}
					//p_MyEdit->SetWindowText(m_staticRightCaption[value]);
				}
			}
			/*
			else if (m_filterType == ID_PREWITT)
			{
				int value = j+(i*3); //得到 坐标
				if(value%2 != 0 )
				{
					m_staticCaption[value].Format("%d",1);
				}
				else if(value == 3*3/2) //如果是中间的那个值 
				{
					m_staticCaption[value].Format("%d",-(3*3/2));
				}
				else
				{
					m_staticCaption[value].Format("%d",0);
				}
				
			}*/
			if(choice == LEFT)
			{
				p_MyEdit->SetWindowText(m_staticLeftCaption[value]);
				if(p_MyEdit != NULL)
				{
					m_MyLeftEdits.Add((void*)p_MyEdit);
				}
			}
			else
			{
				p_MyEdit->SetWindowText(m_staticRightCaption[value]);
				if(p_MyEdit != NULL)
				{
					m_MyRightEdits.Add((void*)p_MyEdit);
				}
			}

		}
	}
}

BOOL CSharpenDlg::OnInitDialog()
{
	SetWindowText(m_title);
	m_drawon = true;
	CButton* radio=(CButton*)GetDlgItem(IDC_RADIO2);
	radio->SetCheck(1);
	m_patern_default = SINGLE_LEFT;//默认一个模板
	creatEdit(LEFT);//初始化都只设置一个模板
	return true;
}

void CSharpenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO2, m_radiobtngroup);
}


BEGIN_MESSAGE_MAP(CSharpenDlg, CDialogEx)
	ON_BN_CLICKED(ID_SHARPEN_OK, &CSharpenDlg::OnBnClickedSharpenOk)
	ON_BN_CLICKED(IDC_RADIO2, &CSharpenDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CSharpenDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO4, &CSharpenDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDCANCEL, &CSharpenDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CSharpenDlg 消息处理程序

void CSharpenDlg::getData(int choice)
{
	//用于获取模板数据
	//CPtrArray m_MyEdits;
	int n = 0;
	if(choice == LEFT)
	{
		n = m_MyLeftEdits.GetSize();
	}
	else
	{
		n = m_MyRightEdits.GetSize();
	}
	
	CString text;
	for(int i = 0; i<n; i++)
	{
		CEdit *pEdit;
		if(choice == LEFT)
		{
			pEdit = (CEdit*)m_MyLeftEdits.GetAt(i);
			pEdit->GetWindowText(text);
			m_lefttext[i] = _ttoi(text);//cstring转换成int
		}
		else
		{
			pEdit = (CEdit*)m_MyRightEdits.GetAt(i);
			pEdit->GetWindowText(text);
			m_righttext[i] = _ttoi(text);//cstring转换成int
		}
	}
	//theApp.getMatrix(m_modelMartrix);
	if(choice == LEFT)
	{
		theApp.getSharpenText(m_lefttext,LEFT,m_patern_default);
	}
	else if(choice == RIGHT)
	{
		theApp.getSharpenText(m_righttext,RIGHT,m_patern_default);
	}
	
}

void CSharpenDlg::OnBnClickedSharpenOk()
{
	if(m_patern_default == SINGLE_LEFT )
	{
		getData(LEFT);
	}
	else if(m_patern_default == SINGLE_RIGHT)
	{
		getData(RIGHT);
	}
	else if(m_patern_default == DOUBLE_PATREN)
	{
		getData(LEFT);
		getData(RIGHT);
	}
	
	CDialogEx::OnOK();
}


void CSharpenDlg::OnBnClickedRadio2()
{
	UpdateData(true);
	switch (m_radiobtngroup)
	{
	case ZERO:
		m_patern_default = SINGLE_LEFT;
		OnClose(m_MyRightEdits);
		creatEdit(LEFT);//初始化都只设置一个模板
		break;
	case ONE:
		m_patern_default = SINGLE_RIGHT;
		OnClose(m_MyLeftEdits);
		creatEdit(RIGHT);//初始化都只设置一个模板
		break;
	case TWO:
		m_patern_default = DOUBLE_PATREN;
		OnClose(m_MyLeftEdits);
		OnClose(m_MyRightEdits);
		creatEdit(LEFT);//初始化都只设置一个模板
		creatEdit(RIGHT);//初始化都只设置一个模板
		break;

	}
}


void CSharpenDlg::OnBnClickedCancel()
{
	m_drawon = false;
	theApp.setDrawonStatu(m_drawon);//设置绘图状态
	CDialogEx::OnCancel();
}
