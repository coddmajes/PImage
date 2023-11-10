
// MainFrm.cpp : CMainFrame 类的实现
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
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
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
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	return 0;
}
int CMainFrame::getWindowsCentral()
{
	CRect  rect;     
	GetClientRect(rect);//获得窗体的大小 
	m_currentWindowWidth = rect.Width();//获取当前窗体的宽度
	GetWindowRect(rect);//获得窗体在屏幕上的位置
	//m_currentWindowTLx = rect.TopLeft().x;//获取当前窗体在屏幕上的左上点的x坐标
	//m_currentWindowCx = m_currentWindowTLx + m_currentWindowWidth/2;//获取当前窗口的中心坐标
	return m_currentWindowWidth;
}
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	 //创建拆分窗口
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
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	return TRUE;
}
 
// CMainFrame 诊断

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


// CMainFrame 消息处理程序

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

	// TODO: 自定义或扩展此代码以处理“视图”菜单中的选项

	CPImageView* pView = GetRightPane();

	// 如果右窗格尚未创建或者不是视图，
	// 则在范围内禁用命令

	if (pView == NULL)
		pCmdUI->Enable(FALSE);
	else
	{
		DWORD dwStyle = pView->GetStyle() & LVS_TYPEMASK;

		// 如果命令是 ID_VIEW_LINEUP，则只有在处于
		// LVS_ICON 或 LVS_SMALLICON 模式时才启用命令

		if (pCmdUI->m_nID == ID_VIEW_LINEUP)
		{
			if (dwStyle == LVS_ICON || dwStyle == LVS_SMALLICON)
				pCmdUI->Enable();
			else
				pCmdUI->Enable(FALSE);
		}
		else
		{
			// 否则，使用点线来反映视图的样式
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
	// TODO: 自定义或扩展此代码以处理“视图”菜单中的选项
	//CPImageView* pView = GetRightPane();

	//// 如果右窗格已创建而且是 CPImageView，
	//// 则处理菜单命令...
	//if (pView != NULL)
	//{
	//	DWORD dwStyle = -1;

	//	switch (nCommandID)
	//	{
	//	case ID_VIEW_LINEUP:
	//		{
	//			// 要求列表控件与网格对齐
	//			CListCtrl& refListCtrl = pView->GetListCtrl();
	//			refListCtrl.Arrange(LVA_SNAPTOGRID);
	//		}
	//		break;

	//	// 其他命令更改列表控件上的样式
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

	//	// 更改样式；窗口将自动重新绘制
	//	if (dwStyle != -1)
	//		pView->ModifyStyle(LVS_TYPEMASK, dwStyle);
	//}
}

