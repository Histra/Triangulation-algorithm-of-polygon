
// DrawHeartView.cpp : CDrawHeartView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DrawHeart.h"
#endif

#include "DrawHeartDoc.h"
#include "DrawHeartView.h"
#include <ctime>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDrawHeartView

IMPLEMENT_DYNCREATE(CDrawHeartView, CView)

BEGIN_MESSAGE_MAP(CDrawHeartView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CDrawHeartView 构造/析构

CDrawHeartView::CDrawHeartView()
{
	// TODO: 在此处添加构造代码

}

CDrawHeartView::~CDrawHeartView()
{
}

BOOL CDrawHeartView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

void CDrawHeartView::Define_OriginalPoint(CDC *pDC) {
	CDrawHeartDoc *pDoc = GetDocument();// 获取文档类CcgWGDrawLineDoc的指针
	CRect rect;
	GetClientRect(&rect);// 获得窗口的当前的客户区
	pDC->SetMapMode(MM_ANISOTROPIC);// 设置指定设备环境的映射方式
									/// 逻辑坐标和逻辑坐标的转换
	pDC->SetViewportOrg(rect.right / 2, rect.bottom / 2);
	pDC->SetViewportExt(rect.right, rect.bottom);
	pDC->SetWindowOrg(0, 0);
	pDC->SetWindowExt(pDoc->MWidth, -pDoc->MHeight);
}


// CDrawHeartView 绘制

void CDrawHeartView::OnDraw(CDC* /*pDC*/)
{
	CDrawHeartDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CDC* pDC = GetDC();
	Define_OriginalPoint(pDC);
	
	/*const double pi = 3.141592654;
	double b = 300;
	const int time = 100000;
	int lim = 1.82*time;
	for (int i = -lim; i < lim; i++) {
		double x = i / double(time);
		//double y = pow(x*x, 1 / 3.0) + 0.9*sqrt(3.3 - x*x)*sin(b*x*pi);
		double y = pow(x*x, 1 / 3.0) + 0.7*sqrt(3.3 - x*x)*sin(b*x*pi);
		pDC->SetPixel(x * 50, y * 50, RGB(255, 0, 0));
		//pDC->SetPixel((x+0.01)*50, (y+0.01)*50, RGB(0, 255, 0));
	}*/
	const double pi = 3.141592654;
	double b = 320;
	const int tim = 10000;
	int lim = 1.82*tim;
	int coun = 99;
	srand(unsigned(time(NULL)));
	for (int i = -lim; i < lim; i++) {
		double x = i / double(tim);
		double y = pow(x*x, 1 / 3.0) + 0.7*sqrt(3.3 - x*x)*sin(b*x*pi);
		pDC->SetPixel(x * 50, y * 50, RGB(255, 0, 0));
	}
	while (coun--) {
		int xt = rand() % 150;
		int yt = rand() % 150;
		int r = rand() % 256;
		int g = rand() % 256;
		int b = rand() % 256;
		int xsign = rand() % 2;
		int ysign = rand() % 2;
		int size = rand() % 35 + 16;
		for (int i = -lim; i < lim; i++) {
			double x = i / double(tim);
			double y = pow(x*x, 1 / 3.0) + 0.7*sqrt(3.3 - x*x)*sin(b*x*pi);
			x += xt / 10.0;
			y += yt / 10.0;
			if (xsign == 0)
				x = -x;
			if (ysign == 0)
				y = -y;
			pDC->SetPixel(x * size, y * size, RGB(r, g, b));
		}
	}
	MessageBox(_T("这里是我给你的99颗心，我喜欢你！"));

	
	

	// TODO: 在此处为本机数据添加绘制代码
}


// CDrawHeartView 打印

BOOL CDrawHeartView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDrawHeartView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CDrawHeartView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CDrawHeartView 诊断

#ifdef _DEBUG
void CDrawHeartView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawHeartView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawHeartDoc* CDrawHeartView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawHeartDoc)));
	return (CDrawHeartDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawHeartView 消息处理程序


void CDrawHeartView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	CDrawHeartDoc *pDoc = GetDocument();
	pDoc->MWidth = cx;
	pDoc->MHeight = cy;
	// TODO: 在此处添加消息处理程序代码
}
