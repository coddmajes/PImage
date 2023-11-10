// SmoothDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PImage.h"
#include "SmoothDlg.h"
#include "afxdialogex.h"

using namespace std;

// CSmoothDlg �Ի���

IMPLEMENT_DYNAMIC(CSmoothDlg, CDialogEx)

CSmoothDlg::CSmoothDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSmoothDlg::IDD, pParent)
	, m_radioGroup(0)
{
	
}

void CSmoothDlg::OnClose(CPtrArray & myEdits)
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

CSmoothDlg::~CSmoothDlg()
{
	if(m_MyEdits.GetData() == NULL )
	{
		return;
	}
	OnClose(m_MyEdits);
	//OnClose(m_MyRightEdits);
	//OnClose();
}

void CSmoothDlg::creatEdit(int choice)
{
	chooseMode();
}

BOOL CSmoothDlg::OnInitDialog()
{
	SetWindowText(m_title);
	m_drawon = true;//�ж��Ƿ������ͼ
	CButton* radio=(CButton*)GetDlgItem(IDC_RADIO3);
	radio->SetCheck(1);
	if(m_filterType ==IDM_EDGE_LOG)
	{
		GetDlgItem(IDC_RADIO7)->ShowWindow(FALSE); //���ظÿؼ�;
	}
	creatEdit(m_radioGroup);//��ʼ����ֻ����һ��ģ��
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


// CSmoothDlg ��Ϣ�������


void CSmoothDlg::OnBnClickedRadio3()
{
	UpdateData(true);
	UpdateData(true);
	switch (m_radioGroup)
	{
	case MODE_ZERO:
		OnClose(m_MyEdits);
		creatEdit(MODE_ZERO);//��ʼ����ֻ����һ��ģ��
		break;
	case MODE_ONE:
		OnClose(m_MyEdits);
		creatEdit(MODE_ONE);//��ʼ����ֻ����һ��ģ��
		break;
	case MODE_TWO:
		OnClose(m_MyEdits);
		creatEdit(MODE_TWO);//��ʼ����ֻ����һ��ģ��

		break;

	}
	
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
	GetClientRect(&rect);//��ȡ�ͻ������
	GetDlgItem(ID_SMOOTH_OK)->GetWindowRect(&rectOK);//��ȡȷ��btn������
	GetDlgItem(IDC_MODEL_CONTENT)->GetWindowRect(&rectMODEL);//��ȡ ģ�徲̬�ı�������
	
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
	
	//GetDlgItem(IDC_STATIC_TITLE)->SetWindowText("�������˲����İ뾶:");

	//int modelWidth = rect.Width()- 2 * rectMODEL.left; //���ȡ model ����
	int firstWidthSpace = rectMODEL.left;//�׸���ȿ�϶
	int perWidth = rectMODEL.left - 20;//����ÿ��edit�Ŀ��
	int perHight = rectMODEL.bottom - rectMODEL.top; //����ÿ��edit�ĸ߶�
	int spaceWidth = rectMODEL.left - 30;//����ÿ��edit֮��Ŀ�϶
	int spaceHight = perHight-4; //����ÿ��edit֮��Ŀ�϶
	int top = rectMODEL.bottom;//���õ�һ�� edit�Ķ���λ��

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

			int editLeft = j*perWidth + spaceWidth * j + firstWidthSpace;//edit������ + ��ȿ�϶ +�׸���ȿ�϶
			int editTop = top+spaceHight*(i+1)+ perHight * i;//��һ��edit�Ķ���λ�� + �߶ȿ�϶ + edit����߶�
			int editRight = (j+1)*perWidth + spaceWidth * j  + firstWidthSpace;//edit
			int editBottom = top+spaceHight*(i+1)+ perHight * (i+1);//��һ��edit�Ķ���λ�� + �߶ȿ�϶ + edit����߶�

			
			p_MyEdit->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, CRect(editLeft,editTop,
				editRight, editBottom),this,EDIT_ID+(j+1)+(i*m_modelMartrix));

			//����ģ������
			if(m_filterType == IDM_AVERAGE_FILTER || m_filterType ==IDM_MEDIAN_FILTER || m_filterType ==IDM_MAX_FILTER ||m_filterType == IDM_MIN)
			{
				m_staticCaption[j+(i*m_modelMartrix)].Format("%d",1);
			}
			else if (m_filterType == IDM_LA_FILTER || m_filterType == IDM_LA_GRAY )
			{
				int value = j+(i*m_modelMartrix); //�õ� ����
				if(value%2 != 0 )
				{
					m_staticCaption[value].Format("%d",1);
				}
				else if(value == m_modelMartrix*m_modelMartrix/2) //������м���Ǹ�ֵ 
				{
					m_staticCaption[value].Format("%d",-(m_modelMartrix*m_modelMartrix/2));
				}
				else
				{
					m_staticCaption[value].Format("%d",0);
				}
				
			}
			else if(m_filterType ==IDM_EDGE_LOG)
			{
				int value =0;
				if(m_modelMartrix == 3)
				{
					value = j+(i*m_modelMartrix); //�õ� ����
					if(value%2 != 0 )
					{
						m_staticCaption[value].Format("%d",1);
					}
					else if(value == m_modelMartrix*m_modelMartrix/2) //������м���Ǹ�ֵ 
					{
						m_staticCaption[value].Format("%d",-(m_modelMartrix*m_modelMartrix/2));
					}
					else
					{
						m_staticCaption[value].Format("%d",0);
					}
				}
				else if(m_modelMartrix == 5)
				{
					value = j+(i*m_modelMartrix); //�õ� ����
					m_staticCaption[value].Format("%d",logModeF[value]);
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

//#1015

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}*/


void CSmoothDlg::OnBnClickedSmoothOk()
{
	//���ڻ�ȡģ������
	int n =0;
	n = m_MyEdits.GetSize();
	if(n ==0 )
	{
		MessageBox("��ѡ��ģ���С��");
		m_drawon = false;
	}
	CString text;
	for(int i = 0; i<n; i++)
	{
		CEdit *pEdit = (CEdit*)m_MyEdits.GetAt(i);
		if(pEdit != NULL)
		{
			pEdit->GetWindowText(text);
			m_text[i] = _ttoi(text);//cstringת����int 
		}
	}
	theApp.getMatrix(m_modelMartrix);
	theApp.setDrawonStatu(m_drawon);//���û�ͼ״̬
	theApp.getText(m_text);
	CDialogEx::OnOK();
	//AfxGetMainWnd()->SendMessage(WM_CLOSE);
}




void CSmoothDlg::OnBnClickedCancel()
{
	m_drawon = false;
	theApp.setDrawonStatu(m_drawon);//���û�ͼ״̬
	CDialogEx::OnCancel();
}
