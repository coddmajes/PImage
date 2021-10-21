
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
class CPImageView;

class CMainFrame : public CFrameWnd
{
private:
	int m_currentWindowCx;//��ǰ���ڵ��м�λ��
	int m_currentWindowWidth;//��ǰ���ڵĿ��
	int m_currentWindowTLx;//��ǰ���ڵ����ϵ��x����
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
protected:
	CSplitterWnd m_wndSplitter;
public:
	int getWindowsCentral();
// ����
public:

// ��д
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
	CPImageView* GetRightPane();
	CLeftView* GetLeftPane();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CStatusBar        m_wndStatusBar;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateViewStyles(CCmdUI* pCmdUI);
	afx_msg void OnViewStyle(UINT nCommandID);
	DECLARE_MESSAGE_MAP()

};


