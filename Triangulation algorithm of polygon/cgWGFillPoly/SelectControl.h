#pragma once



// SelectControl 窗体视图

class SelectControl : public CFormView
{
	DECLARE_DYNCREATE(SelectControl)

protected:
	SelectControl();           // 动态创建所使用的受保护的构造函数
	virtual ~SelectControl();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SELECTCONTROL };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPointwise();
	CString Information;
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedSortededgetable();
	afx_msg void OnBnClickedSeed();
	afx_msg void OnBnClickedComparison();
	afx_msg void OnBnClickedPolygonaltriangulation();
};


