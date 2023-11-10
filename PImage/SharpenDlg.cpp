// SharpenDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PImage.h"
#include "SharpenDlg.h"
#include "afxdialogex.h"


// CSharpenDlg �Ի���

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
	GetClientRect(&rect);//��ȡ�ͻ������
	GetDlgItem(ID_SHARPEN_OK)->GetWindowRect(&rectOK);//��ȡȷ��btn������
	GetDlgItem(IDC_RADIO2)->GetWindowRect(&rectMODEL);//��ȡ ģ�徲̬�ı�������
	
	ScreenToClient(&rectOK);
	ScreenToClient(&rectMODEL);

	CStatic *p_MyStatic;
	CEdit *p_MyEdit;

	//int modelWidth = rect.Width()- 2 * rectMODEL.left; //���ȡ model ����
	int firstWidthSpace = rectMODEL.left;//�׸���ȿ�϶
	int perWidth = rectMODEL.left - 20;//����ÿ��edit�Ŀ��
	int perHight = rectMODEL.bottom - rectMODEL.top; //����ÿ��edit�ĸ߶�
	int spaceWidth = rectMODEL.left - 30;//����ÿ��edit֮��Ŀ�϶
	int spaceHight = perHight-4; //����ÿ��edit֮��Ŀ�϶
	int top = rectMODEL.bottom;//���õ�һ�� edit�Ķ���λ��
	int matrix = 3;
	if( m_filterType == IDM_ROBERTS || m_filterType == IDM_HORI_VERT)
	{
		matrix = 2;
	}
	
	if(choice == RIGHT)
	{
		firstWidthSpace = firstWidthSpace + 3*perWidth + 3*spaceWidth;//�׸���ȿ�϶
		
	}
	//int firstWidthSpace = rectMODEL.left;//�׸���ȿ�϶
	

	for(int i =0; i<matrix; i++)
	{
		for(int j =0; j<matrix; j++)
		{
			p_MyStatic = new CStatic();
			p_MyEdit = new CEdit();

			int editLeft = j*perWidth + spaceWidth * j + firstWidthSpace;//edit������ + ��ȿ�϶ +�׸���ȿ�϶
			int editTop = top+spaceHight*(i+1)+ perHight * i;//��һ��edit�Ķ���λ�� + �߶ȿ�϶ + edit����߶�
			int editRight = (j+1)*perWidth + spaceWidth * j  + firstWidthSpace;//edit
			int editBottom = top+spaceHight*(i+1)+ perHight * (i+1);//��һ��edit�Ķ���λ�� + �߶ȿ�϶ + edit����߶�

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
			int value = j+(i*matrix); //�õ� ����

			//����ģ������
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
			else if(m_filterType ==IDM_SOBEL || m_filterType ==IDM_FACE_CUT)
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
				int value = j+(i*3); //�õ� ����
				if(value%2 != 0 )
				{
					m_staticCaption[value].Format("%d",1);
				}
				else if(value == 3*3/2) //������м���Ǹ�ֵ 
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
	m_patern_default = SINGLE_LEFT;//Ĭ��һ��ģ��
	creatEdit(LEFT);//��ʼ����ֻ����һ��ģ��
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


// CSharpenDlg ��Ϣ�������

void CSharpenDlg::getData(int choice)
{
	//���ڻ�ȡģ������
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
			m_lefttext[i] = _ttoi(text);//cstringת����int
		}
		else
		{
			pEdit = (CEdit*)m_MyRightEdits.GetAt(i);
			pEdit->GetWindowText(text);
			m_righttext[i] = _ttoi(text);//cstringת����int
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
		creatEdit(LEFT);//��ʼ����ֻ����һ��ģ��
		break;
	case ONE:
		m_patern_default = SINGLE_RIGHT;
		OnClose(m_MyLeftEdits);
		creatEdit(RIGHT);//��ʼ����ֻ����һ��ģ��
		break;
	case TWO:
		m_patern_default = DOUBLE_PATREN;
		OnClose(m_MyLeftEdits);
		OnClose(m_MyRightEdits);
		creatEdit(LEFT);//��ʼ����ֻ����һ��ģ��
		creatEdit(RIGHT);//��ʼ����ֻ����һ��ģ��
		break;

	}
}


void CSharpenDlg::OnBnClickedCancel()
{
	m_drawon = false;
	theApp.setDrawonStatu(m_drawon);//���û�ͼ״̬
	CDialogEx::OnCancel();
}
