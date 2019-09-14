// SelectControl.cpp : 实现文件
//

#include "stdafx.h"
#include "cgWGFillPoly.h"
#include "SelectControl.h"
#include "cgWGFillPolyDoc.h"


// SelectControl

IMPLEMENT_DYNCREATE(SelectControl, CFormView)

SelectControl::SelectControl()
	: CFormView(IDD_SELECTCONTROL)
	, Information(_T("Hello, Here is the Second Experiment of\r\nthe Computer Graphics Class!\r\n\r\nThe Application belongs to 16020031075王刚\r\n"))
{

}

SelectControl::~SelectControl()
{
}

void SelectControl::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SI, Information);
}

BEGIN_MESSAGE_MAP(SelectControl, CFormView)
	ON_BN_CLICKED(IDC_POINTWISE, &SelectControl::OnBnClickedPointwise)
	ON_BN_CLICKED(IDC_SORTEDEDGETABLE, &SelectControl::OnBnClickedSortededgetable)
	ON_BN_CLICKED(IDC_SEED, &SelectControl::OnBnClickedSeed)
	ON_BN_CLICKED(IDC_COMPARISON, &SelectControl::OnBnClickedComparison)
	ON_BN_CLICKED(IDC_POLYGONALTRIANGULATION, &SelectControl::OnBnClickedPolygonaltriangulation)
END_MESSAGE_MAP()


// SelectControl 诊断

#ifdef _DEBUG
void SelectControl::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void SelectControl::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// SelectControl 消息处理程序


void SelectControl::OnBnClickedPointwise()
{
	// TODO: 在此添加控件通知处理程序代码
	CcgWGFillPolyDoc* pDoc = (CcgWGFillPolyDoc*)GetDocument();
	pDoc->MDisplayMode = 0;
	pDoc->UpdateAllViews(this);
}

void SelectControl::OnBnClickedSortededgetable()
{
	// TODO: 在此添加控件通知处理程序代码
	CcgWGFillPolyDoc* pDoc = (CcgWGFillPolyDoc*)GetDocument();
	pDoc->MDisplayMode = 1;
	pDoc->UpdateAllViews(this);
}

void SelectControl::OnBnClickedSeed()
{
	// TODO: 在此添加控件通知处理程序代码
	CcgWGFillPolyDoc* pDoc = (CcgWGFillPolyDoc*)GetDocument();
	pDoc->MDisplayMode = 2;
	pDoc->UpdateAllViews(this);
}

void SelectControl::OnBnClickedComparison()
{
	// TODO: 在此添加控件通知处理程序代码
	CcgWGFillPolyDoc* pDoc = (CcgWGFillPolyDoc*)GetDocument();
	pDoc->MDisplayMode = 3;
	pDoc->UpdateAllViews(this);
}


void SelectControl::OnBnClickedPolygonaltriangulation()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("请逆时针画点，否则会出错！"));
	CcgWGFillPolyDoc* pDoc = (CcgWGFillPolyDoc*)GetDocument();
	pDoc->MDisplayMode = 4;
	pDoc->UpdateAllViews(this);
}

void SelectControl::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: 在此添加专用代码和/或调用基类
	CcgWGFillPolyDoc* pDoc = (CcgWGFillPolyDoc*)GetDocument();
	if (pDoc->MDisplayMode == 0) {/// 逐点法
		GetDlgItem(IDC_SI)->SetWindowText(pDoc->pointwiseInformation);
	}
	if (pDoc->MDisplayMode == 1) {/// 有序边表法
		GetDlgItem(IDC_SI)->SetWindowText(pDoc->sortedEdgeTableInformation);
	}
	if (pDoc->MDisplayMode == 2){/// 种子法
		GetDlgItem(IDC_SI)->SetWindowText(pDoc->seedInformation);
	}
	if (pDoc->MDisplayMode == 3) {/// 上述三种方法的比较
		GetDlgItem(IDC_SI)->SetWindowText(pDoc->comparisonInforamtion);
	}
	if (pDoc->MDisplayMode == 4) {/// 多边形的三角剖分算法
		GetDlgItem(IDC_SI)->SetWindowText(pDoc->polygonalTriangulationInformation);
	}
}


void SelectControl::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
}



