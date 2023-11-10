
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "PImage.h"

#include "MainFrm.h"
#include "LeftView.h"
#include "PImageView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, &CMainFrame::OnUpdateViewStyles)
	ON_COMMAND_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, &CMainFrame::OnViewStyle)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	return 0;
}
int CMainFrame::getWindowsCentral()
{
	CRect  rect;     
	GetClientRect(rect);//��ô���Ĵ�С 
	m_currentWindowWidth = rect.Width();//��ȡ��ǰ����Ŀ��
	GetWindowRect(rect);//��ô�������Ļ�ϵ�λ��
	//m_currentWindowTLx = rect.TopLeft().x;//��ȡ��ǰ��������Ļ�ϵ����ϵ��x����
	//m_currentWindowCx = m_currentWindowTLx + m_currentWindowWidth/2;//��ȡ��ǰ���ڵ���������
	return m_currentWindowWidth;
}
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	 //������ִ���
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;
	int csize_x = getWindowsCentral();	
	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CLeftView), CSize(csize_x/2, 100), pContext) ||
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CPImageView), CSize(100, 100), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}

	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	//int currentWindowCx = cs.cx;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	return TRUE;
}
 
// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������

CPImageView* CMainFrame::GetRightPane()
{
	CWnd* pWnd = m_wndSplitter.GetPane(0, 1);
	CPImageView* pView = DYNAMIC_DOWNCAST(CPImageView, pWnd);
	return pView;
}
CLeftView* CMainFrame::GetLeftPane()
{
	CWnd* pWnd = m_wndSplitter.GetPane(0, 0);
	CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
	return pView;
}

void CMainFrame::OnUpdateViewStyles(CCmdUI* pCmdUI)
{
	if (!pCmdUI)
		return;

	// TODO: �Զ������չ�˴����Դ�����ͼ���˵��е�ѡ��

	CPImageView* pView = GetRightPane();

	// ����Ҵ�����δ�������߲�����ͼ��
	// ���ڷ�Χ�ڽ�������

	if (pView == NULL)
		pCmdUI->Enable(FALSE);
	else
	{
		DWORD dwStyle = pView->GetStyle() & LVS_TYPEMASK;

		// ��������� ID_VIEW_LINEUP����ֻ���ڴ���
		// LVS_ICON �� LVS_SMALLICON ģʽʱ����������

		if (pCmdUI->m_nID == ID_VIEW_LINEUP)
		{
			if (dwStyle == LVS_ICON || dwStyle == LVS_SMALLICON)
				pCmdUI->Enable();
			else
				pCmdUI->Enable(FALSE);
		}
		else
		{
			// ����ʹ�õ�������ӳ��ͼ����ʽ
			pCmdUI->Enable();
			BOOL bChecked = FALSE;

			switch (pCmdUI->m_nID)
			{
			case ID_VIEW_DETAILS:
				bChecked = (dwStyle == LVS_REPORT);
				break;

			case ID_VIEW_SMALLICON:
				bChecked = (dwStyle == LVS_SMALLICON);
				break;

			case ID_VIEW_LARGEICON:
				bChecked = (dwStyle == LVS_ICON);
				break;

			case ID_VIEW_LIST:
				bChecked = (dwStyle == LVS_LIST);
				break;

			default:
				bChecked = FALSE;
				break;
			}

			pCmdUI->SetRadio(bChecked ? 1 : 0);
		}
	}
}

void CMainFrame::OnViewStyle(UINT nCommandID)
{
	// TODO: �Զ������չ�˴����Դ�����ͼ���˵��е�ѡ��
	//CPImageView* pView = GetRightPane();

	//// ����Ҵ����Ѵ��������� CPImageView��
	//// ����˵�����...
	//if (pView != NULL)
	//{
	//	DWORD dwStyle = -1;

	//	switch (nCommandID)
	//	{
	//	case ID_VIEW_LINEUP:
	//		{
	//			// Ҫ���б�ؼ����������
	//			CListCtrl& refListCtrl = pView->GetListCtrl();
	//			refListCtrl.Arrange(LVA_SNAPTOGRID);
	//		}
	//		break;

	//	// ������������б�ؼ��ϵ���ʽ
	//	case ID_VIEW_DETAILS:
	//		dwStyle = LVS_REPORT;
	//		break;

	//	case ID_VIEW_SMALLICON:
	//		dwStyle = LVS_SMALLICON;
	//		break;

	//	case ID_VIEW_LARGEICON:
	//		dwStyle = LVS_ICON;
	//		break;

	//	case ID_VIEW_LIST:
	//		dwStyle = LVS_LIST;
	//		break;
	//	}

	//	// ������ʽ�����ڽ��Զ����»���
	//	if (dwStyle != -1)
	//		pView->ModifyStyle(LVS_TYPEMASK, dwStyle);
	//}
}

