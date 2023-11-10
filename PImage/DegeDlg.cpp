// DegeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PImage.h"
#include "DegeDlg.h"
#include "afxdialogex.h"


// CDegeDlg �Ի���

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
	GetClientRect(&rect);//��ȡ�ͻ������
	GetDlgItem(IDDEOK)->GetWindowRect(&rectOK);//��ȡȷ��btn������
	GetDlgItem(IDC_MODEL_CONTENT)->GetWindowRect(&rectMODEL);//��ȡ ģ�徲̬�ı�������
	
	ScreenToClient(&rectOK);
	ScreenToClient(&rectMODEL);

	CStatic *p_MyStatic;
	CEdit *p_MyEdit;
	//int modelWidth = rect.Width()- 2 * rectMODEL.left; //���ȡ model ����
	int firstWidthSpace = rectMODEL.left;//�׸���ȿ�϶
	int perWidth = rectMODEL.left - 20;//����ÿ��edit�Ŀ��
	int perHight = rectMODEL.bottom - rectMODEL.top; //����ÿ��edit�ĸ߶�
	int spaceWidth = rectMODEL.left - 50;//����ÿ��edit֮��Ŀ�϶
	int spaceHight = perHight-10; //����ÿ��edit֮��Ŀ�϶
	int top = rectMODEL.bottom;//���õ�һ�� edit�Ķ���λ��

	for(int i =0; i<16; i++)
	{
		for(int j =0; j<16; j++)
		{
			p_MyStatic = new CStatic();
			p_MyEdit = new CEdit();

			int editLeft = j*perWidth + spaceWidth * j + firstWidthSpace;//edit������ + ��ȿ�϶ +�׸���ȿ�϶
			int editTop = top+spaceHight*(i+1)+ perHight * i;//��һ��edit�Ķ���λ�� + �߶ȿ�϶ + edit����߶�
			int editRight = (j+1)*perWidth + spaceWidth * j  + firstWidthSpace;//edit
			int editBottom = top+spaceHight*(i+1)+ perHight * (i+1);//��һ��edit�Ķ���λ�� + �߶ȿ�϶ + edit����߶�

			
			p_MyEdit->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, CRect(editLeft,editTop,
				editRight, editBottom),this,EDIT_ID+(j+1)+(i*16));

			//����ģ������
			
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


// CDegeDlg ��Ϣ�������


void CDegeDlg::OnBnClickedDeok()
{
	CDialogEx::OnOK();
}
