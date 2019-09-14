
// cgWGFillPolyView.cpp : CcgWGFillPolyView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "cgWGFillPoly.h"
#endif

#include "cgWGFillPolyDoc.h"
#include "cgWGFillPolyView.h"
#include <stack>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CcgWGFillPolyView

IMPLEMENT_DYNCREATE(CcgWGFillPolyView, CView)

BEGIN_MESSAGE_MAP(CcgWGFillPolyView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// CcgWGFillPolyView 构造/析构

CcgWGFillPolyView::CcgWGFillPolyView()
{
	// TODO: 在此处添加构造代码
	pNumbers = 0;/// 初始化pNumbers
	/// 初始化dx和dy数组
	dx[0] = 0; dx[1] = 1; dx[2] = 0; dx[3] = -1;
	dy[0] = -1, dy[1] = 0, dy[2] = 1, dy[3] = 0;
}

CcgWGFillPolyView::~CcgWGFillPolyView()
{
}

void CcgWGFillPolyView::Define_OriginalPoint(CDC *pDC) {
	CcgWGFillPolyDoc *pDoc = GetDocument();// 获取文档类CcgWGDrawLineDoc的指针
	CRect rect;
	GetClientRect(&rect);// 获得窗口的当前的客户区
	pDC->SetMapMode(MM_ANISOTROPIC);// 设置指定设备环境的映射方式
									/// 逻辑坐标和逻辑坐标的转换
	pDC->SetViewportOrg(rect.right / 2, rect.bottom / 2);
	pDC->SetViewportExt(rect.right, rect.bottom);
	pDC->SetWindowOrg(0, 0);
	pDC->SetWindowExt(pDoc->MWidth, -pDoc->MHeight);
}

BOOL CcgWGFillPolyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CcgWGFillPolyView 绘制

void CcgWGFillPolyView::OnDraw(CDC* /*pDC*/)
{
	CcgWGFillPolyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

	/*CDC* pDC = GetDC();
	/// 绘制坐标系
	pDC->MoveTo(0, pDoc->MHeight / 2);
	pDC->LineTo(pDoc->MWidth, pDoc->MHeight / 2);
	pDC->MoveTo(pDoc->MWidth / 2, 0);
	pDC->LineTo(pDoc->MWidth / 2, pDoc->MHeight);*/

	///Define_OriginalPoint(pDC);	
}


// CcgWGFillPolyView 打印

BOOL CcgWGFillPolyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CcgWGFillPolyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CcgWGFillPolyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CcgWGFillPolyView 诊断

#ifdef _DEBUG
void CcgWGFillPolyView::AssertValid() const
{
	CView::AssertValid();
}

void CcgWGFillPolyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CcgWGFillPolyDoc* CcgWGFillPolyView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CcgWGFillPolyDoc)));
	return (CcgWGFillPolyDoc*)m_pDocument;
}
#endif //_DEBUG


// CcgWGFillPolyView 消息处理程序

void CcgWGFillPolyView::PointwiseFillPolygon(int pNumbers, CPoint MPolygon[], CDC* pDC)
{
	DWORD dwStart = GetTickCount();/// 获取开始时间

	const int INF = 0x3f3f3f3f;/// 定义最大值常量
	int maxX = -INF, minX = INF, maxY = -INF, minY = INF;/// 变量赋值
	/// tempx和tempy是MPolygon的上移半格存储数组
	double tempx[N];/// 定义tempx
	double tempy[N];/// 定义tempy
	for (int i = 0; i < pNumbers; i++) {/// 更新tempx和tempy数组
		tempx[i] = MPolygon[i].x;
		tempy[i] = MPolygon[i].y;
		if (tempx[i] > maxX) {
			maxX = (int)tempx[i];
		}
		if (tempx[i] < minX) {
			minX = (int)tempx[i];
		}
		if (tempy[i] > maxY) {
			maxY = (int)tempy[i];
		}
		if (tempy[i] < minY) {
			minY = (int)tempy[i];
		}
		tempy[i] += 0.5;/// 上移半格
	}
	for (int i = minX; i <= maxX; i++) {/// 循环遍历矩形区域
		for (int j = minY; j <= maxY; j++) {
			if (JudgeIn(i, j, tempx, tempy, pNumbers)) {/// 判定该点是不是在多边形内
				pDC->SetPixel(i, j, RGB(255, 0, 0));
			}
		}
	}

	DWORD dwStop = GetTickCount();/// 获得结束时间
	DWORD dwInterval = dwStop - dwStart;/// 获得运行时间
	CcgWGFillPolyDoc* pDoc = (CcgWGFillPolyDoc*)GetDocument();/// 获得Doc指针
	pDoc->pointwiseRunTime = (double)dwInterval;/// 将数据写入pointwiseRunTime
	CString str;/// 将数据写入pointwiseInformation，并将其格式化
	str.Format(_T("%.2lf"), pDoc->pointwiseRunTime);
	pDoc->pointwiseInformation += _T("Runtime Consuming : ") + str + _T("ms\r\n");

	pDoc->UpdateAllViews(this);/// 更新视图
}

bool CcgWGFillPolyView::JudgeIn(int x, int y, double tempx[], double tempy[], int pNumbers)
{/// 判定一个点(x, y)是不是在多边形(tempx和tempy表示)内，pNumbers是多边形点的个数
	int i, j;/// 定义循环变量
	int ans = 0;/// ans表示当前点向右做射线和多边形的交点个数
	for (i = 1, j = 0; i < pNumbers; j = i++) {/// 遍历
		bool cond1 = (y < tempy[i] && y > tempy[j]);/// 条件一
		bool cond2 = (y < tempy[j] && y > tempy[i]);/// 条件二
		bool cond3;/// 条件三
		if (tempy[i] - tempy[j] > 0)
			cond3 = ((y*(tempx[i] - tempx[j]) - tempy[j] * (tempx[i] - tempx[j]) + (tempy[i] - tempy[j])*tempx[j]) 
				>= x * (tempy[i] - tempy[j]));
		else
			cond3 = ((y*(tempx[i] - tempx[j]) - tempy[j] * (tempx[i] - tempx[j]) + (tempy[i] - tempy[j])*tempx[j]) 
				<= x * (tempy[i] - tempy[j]));
		if ((cond1 || cond2) && cond3) {
			ans++;/// 更新ans
		} 
	}
	return (ans % 2 != 0);/// ans为偶数返回FALSE，奇数返回TRUE
}

void CcgWGFillPolyView::SortedEdgeTableFillPolygon(int pNumbers, CPoint MPolygon[], CDC* pDC)
{
	DWORD dwStart = GetTickCount();/// 获取开始时间
	const int runCount = 100;/// 定义运行次数
	int time = runCount;

	while (time--) {/// 循环画图
		edgeNumbers = 0;/// 定义边个数
		LoadPolygon(pNumbers, MPolygon);/// 读入MPolygon数组
		edgeBegin = edgeEnd = 0;/// 定义边开始和边结束变量
		yScan = (int)yMax[0];/// 初始化y扫描线
		Include();/// 判定是否有交点
		UpdataXvalue();/// 更新开始边和结束边，亦即当前操作的边的集合
		while (edgeBegin < edgeEnd) {/// 当开始边和结束边不重合时
			FillScan(pDC);/// 画直线
			yScan--;/// y扫描线迭代更新
			Include();/// 判定是否交点，亦即是否有新的边加入
			UpdataXvalue();/// 更新当前操作的边的集合
		}
	}

	DWORD dwStop = GetTickCount();/// 获取结束时间
	DWORD dwInterval = dwStop - dwStart;/// 获取运行时间
	CcgWGFillPolyDoc* pDoc = (CcgWGFillPolyDoc*)GetDocument();/// 获取Doc指针
	pDoc->sortedEdgeTableTime = (double)dwInterval / runCount;/// 将运行时间写入sortedEdgeTableTime
	CString str;/// 将数据写入sortedEdgeTableInformation中
	str.Format(_T("%.2lf"), pDoc->sortedEdgeTableTime);
	pDoc->sortedEdgeTableInformation += _T("Runtime Consuming : ") + str + _T("ms\r\n");

	pDoc->UpdateAllViews(this);/// 更新视图
}


void CcgWGFillPolyView::LoadPolygon(int pNumbers, CPoint MPolygon[])
{
	double x1, y1, x2, y2;/// 定义变量

	x1 = MPolygon[0].x; 
	y1 = MPolygon[0].y + 0.5;/// 上移半格
	for (int i = 1; i < pNumbers; i++) {
		x2 = MPolygon[i].x;
		y2 = MPolygon[i].y + 0.5;
		if (y1 != y2) {/// 把斜率不为0的直线才执行写入
			InsertPolygon(x1, y1, x2, y2);
		}
		x1 = x2;/// 更新x1
		y1 = y2;/// 更新x2
	}
}

void CcgWGFillPolyView::InsertPolygon(double x1, double y1, double x2, double y2)
{
	int i;/// 定义循环变量
	double Ymax, Ymin;/// 定义纵坐标的最大值Ymax和最小值Ymin
	Ymax = (y2 > y1) ? y2 : y1;/// 更新Ymax
	Ymin = (y2 > y1) ? y1 : y2;/// 更新Ymin
	i = edgeNumbers;/// 更新i值为边个数
	/// 冒泡排序，按照纵坐标从小到大排序
	while (i > 0 && Ymax > yMax[i - 1]) {///当边不空，且当前Ymax大于上一条边的纵坐标
		yMax[i] = yMax[i - 1];/// 更新数值
		yMin[i] = yMin[i - 1];
		Xa[i] = Xa[i - 1];
		Dx[i] = Dx[i - 1];
		i--;/// 迭代i，i同时又代表Ymax和Ymin需要填入的位置
	}
	yMax[i] = Ymax;/// 赋值
	yMin[i] = Ymin;/// 赋值
	if (y2 > y1) /// 更新Xa[i]的数值为Ymax对应的横坐标值;
		Xa[i] = x2;
	else         
		Xa[i] = x1;
	Dx[i] = (x1 - x2) / (y1 - y2);/// 跟新Dx[i]为当前直线的斜率的倒数
	edgeNumbers++;/// 边的个数加一
}

void CcgWGFillPolyView::Include()
{
	while (edgeEnd < edgeNumbers && yScan < yMax[edgeEnd]) {
		/// 当边结束小于边条数且扫描线小于边结束边的y坐标时
		Xa[edgeEnd] = Xa[edgeEnd] - 0.5 * Dx[edgeEnd];///获得真正的x坐标
		Dx[edgeEnd] = -Dx[edgeEnd];/// 去Dx的倒数，方便后续计算
		edgeEnd++;/// 这证明加入了一条新边
	}
}

void CcgWGFillPolyView::UpdataXvalue()
{
	int start = edgeBegin;/// 定义start边变量

	for (int i = start; i < edgeEnd; i++) {///从start边到结束边遍历
		if (yScan > yMin[i]) {/// 当前i边的yMin小于y扫描线
			Xa[i] = Xa[i] + Dx[i];/// 更新Xa[i]的数值，从上一次的Xa[i]获得
			SortX(edgeBegin, i);/// Xa数组从开始变到当前边i从小到大排序
		}
		else {/// 当前边需要被去掉
			for (int j = i; j > edgeBegin; j--) {
				/// 从当前边i到开始边从后往前更新
				yMin[j] = yMin[j - 1];/// 后一条边的数据更新为前一条边的数据
				Xa[j] = Xa[j - 1];
				Dx[j] = Dx[j - 1];
				///yMax[j] = yMax[j - 1];可以加上，但是用不到
			}
			edgeBegin++;/// 更新开始边
		}
	}
}

void CcgWGFillPolyView::SortX(int edgeBegin, int i)
{
	double temp;/// 定义临时变量
	while (i > edgeBegin && Xa[i] < Xa[i - 1]) {/// 冒泡排序
		temp = Xa[i]; Xa[i] = Xa[i - 1]; Xa[i - 1] = temp;
		temp = Dx[i]; Dx[i] = Dx[i - 1]; Dx[i - 1] = temp;
		temp = yMin[i]; yMin[i] = yMin[i - 1]; yMin[i - 1] = temp;
		///temp = yMax[i]; yMax[i] = yMax[i - 1]; yMax[i - 1] = temp;可以加上
		i--;/// 迭代
	}
}

void CcgWGFillPolyView::FillScan(CDC* pDC)
{
	for (int i = edgeBegin; i < edgeEnd; i += 2) {///点点之间画点
		pDC->MoveTo(Xa[i], yScan);
		pDC->LineTo(Xa[i + 1], yScan);
	}
}

void CcgWGFillPolyView::SeedFillPolygon(int pNumbers, CPoint MPolygon[], CDC* pDC)
{
	DWORD dwStart = GetTickCount();/// 获得开始时间
	const int INF = 0x3f3f3f3f;/// 定义最大值常量
	int maxX = -INF, minX = INF, maxY = -INF, minY = INF;/// 赋值
	/// tempx和tempy是MPolygon的上移半格存储数组
	double tempx[N];/// 定义tempx
	double tempy[N];/// 定义tempy
	for (int i = 0; i < pNumbers; i++) {/// 更新tempx和tempy数组
		tempx[i] = MPolygon[i].x;
		tempy[i] = MPolygon[i].y;
		if (tempx[i] > maxX) {
			maxX = (int)tempx[i];
		}
		if (tempx[i] < minX) {
			minX = (int)tempx[i];
		}
		if (tempy[i] > maxY) {
			maxY = (int)tempy[i];
		}
		if (tempy[i] < minY) {
			minY = (int)tempy[i];
		}
		tempy[i] += 0.5;/// 上移半格
	}
	srand(unsigned(time(NULL)));/// 随机种子
	int randX, randY;/// 定义随机变量坐标(randX, randY)
	while (TRUE) {/// 直到找到在多边形内部的一个点为止
		/// 在矩形区域(minX,minY)~(maxX, maxY)内找点
		randX = rand() % (maxX - minX) + minX;
		randY = rand() % (maxY - minY) + minY;
		if (JudgeIn(randX, randY, tempx, tempy, pNumbers))
			break;/// 判断当前点是不是在多边形内
	}

	judgeRgb = pDC->GetPixel(randX, randY);/// 设置judgeRgb
	targetRgb = RGB(0, 255, 0);/// 设置需要填充的颜色
	
	SeedRecursion(randX, randY, pDC);/// 执行递归函数

	DWORD dwStop = GetTickCount();/// 获得结束时间
	DWORD dwInterval = dwStop - dwStart;/// 运行时间
	CcgWGFillPolyDoc* pDoc = (CcgWGFillPolyDoc*)GetDocument();/// 获取Doc指针
	pDoc->seedRunTime = (double)dwInterval;/// 把运行时间写入seedRunTime中
	CString str;/// 把数据写入seedInformation,并格式化
	str.Format(_T("%.2lf"), pDoc->seedRunTime);
	pDoc->seedInformation += _T("Runtime Consuming : ") + str + _T("ms\r\n");

	pDoc->UpdateAllViews(this);/// 更新视图	
}

void CcgWGFillPolyView::SeedRecursion(int x, int y, CDC* pDC)
{/// 图像不能画太大qwq
	pDC->SetPixel(x, y, targetRgb);/// 画当前点
	for (int i = 0; i < 4; i++) {/// 循环遍历dx和dy数组,以实现对区域的四连通
		COLORREF now = pDC->GetPixel(x + dx[i], y + dy[i]);/// 得到新的当前点的像素值
		if (now == judgeRgb)/// 如果新的当前点的像素值是judgeRbg的话
			SeedRecursion(x + dx[i], y + dy[i], pDC);///递归调用SeedRecursion
	}
}

bool CcgWGFillPolyView::PT(int pNumbers, CPoint MPOlygon[], CDC* pDC)
{
	if (pNumbers <= 4)/// 如果当前多边形的边数小于3那么判定该多边形非法
		return FALSE;

	DWORD dwStart = GetTickCount();/// 获得开始运行时间
	CPen pNewPen;///定义画笔颜色为红色
	pNewPen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	CPen* poldPen = pDC->SelectObject(&pNewPen);
	/// 定义循环变量i,j,k
	int i = 0;
	int j = 1;
	int k = 2;
	while (pNumbers > 4) {/// 当多边形的边数大于3时进行
		bool cond1;/// 条件一，向量ij的和向量ik的夹角必须小于π
		double a1 = MPOlygon[j].x - MPOlygon[i].x;
		double a2 = MPOlygon[j].y - MPOlygon[i].y;
		double b1 = MPOlygon[k].x - MPOlygon[i].x;
		double b2 = MPOlygon[k].y - MPOlygon[i].y;
		cond1 = (a1*b2 <= a2*b1);
		bool cond2 = TRUE;/// 条件二，当前多边形中不能有其他点
		double tempx[4];/// 当前多边形上移半格
		double tempy[4];
		tempx[0] = MPOlygon[i].x;
		tempy[0] = MPOlygon[i].y+0.5;
		tempx[1] = MPOlygon[j].x;
		tempy[1] = MPOlygon[j].y+0.5;
		tempx[2] = MPOlygon[k].x;
		tempy[2] = MPOlygon[k].y+0.5;
		tempx[3] = tempx[0];
		tempy[3] = tempy[0];
		for (int p = 0; p < pNumbers; p++) {
			if (p != i && p != j && p != k) {/// 判断其他点是否在当前三角形内
				if (JudgeIn(MPOlygon[p].x, MPOlygon[p].y, tempx, tempy, 3 + 1)) {
					cond2 = FALSE;
					break;
				}	
			}
		}
		///cond1 = true;////
		if (cond1 && cond2) {/// 如果同时满足条件一和条件二
			pDC->MoveTo(MPOlygon[i]);/// 从i点到k点画线
			pDC->LineTo(MPOlygon[k]);
			for (int t = j; t < pNumbers - 1; t++) {/// 更新当前多边形
				MPOlygon[t] = MPOlygon[t + 1];
			}
			pNumbers--;/// 更新多边形的边数
			i = 0;/// 重新赋值i，j，k
			j = 1;
			k = 2;
		}
		else {/// 否则
			i ++;/// i下移一点
			j = i + 1;
			k = j + 1;
		}
	}

	pDC->SelectObject(poldPen);/// 跟新pDC

	DWORD dwStop = GetTickCount();/// 获得结束时间
	DWORD dwInterval = dwStop - dwStart;/// 获得运行时间
	CcgWGFillPolyDoc* pDoc = (CcgWGFillPolyDoc*)GetDocument();/// 获得Doc指针
	pDoc->polygonalTriangualtionRuntime = (double)dwInterval;/// 将数据写入Doc类中
	CString str;/// 将数据写入polygonalTriangulationInformation，并将其格式化
	str.Format(_T("%.2lf"), pDoc->polygonalTriangualtionRuntime);
	pDoc->polygonalTriangulationInformation += _T("Runtime Consuming : ") + str + _T("ms\r\n");

	pDoc->UpdateAllViews(this);/// 更新视图
	return TRUE;
}

void CcgWGFillPolyView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	CcgWGFillPolyDoc* pDoc = GetDocument();
	pDoc->MHeight = cy;
	pDoc->MWidth = cx;
	// TODO: 在此处添加消息处理程序代码
}


void CcgWGFillPolyView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (pNumbers < N) {/// 防止栈溢出
		MPolygon[pNumbers] = point;/// 更新MPolygon数组
		pNumbers++;
		mousePoint = point;
	}
	CView::OnLButtonDown(nFlags, point);
}

void CcgWGFillPolyView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDC* pDC = GetDC();
	if (pNumbers > 0) {
		pDC->SetROP2(2);///取背景色的反，抹除上一条线
		pDC->MoveTo(MPolygon[pNumbers - 1]);
		pDC->LineTo(mousePoint);

		mousePoint = point;
		pDC->MoveTo(MPolygon[pNumbers - 1]);
		pDC->LineTo(mousePoint);
	}

	CView::OnMouseMove(nFlags, point);
}

void CcgWGFillPolyView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CcgWGFillPolyDoc* pDoc = (CcgWGFillPolyDoc*)GetDocument();/// 获取Doc指针
	CDC* pDC = GetDC();/// 获取CDC指针
	pDC->MoveTo(MPolygon[pNumbers-1]);
	pDC->LineTo(MPolygon[0]);/// 话最后一条线
	MPolygon[pNumbers] = MPolygon[0];/// 再次添加一个点为第一个点
	pNumbers++;

	if (pDoc->MDisplayMode == 0) {/// 点击按钮Pointwise后执行
		PointwiseFillPolygon(pNumbers, MPolygon, pDC);
	}
	if (pDoc->MDisplayMode == 1) {/// 点击SortedEdgeTable按钮后执行
		SortedEdgeTableFillPolygon(pNumbers, MPolygon, pDC);
	}
	if (pDoc->MDisplayMode == 2) {/// 点击Seed按钮后执行
		SeedFillPolygon(pNumbers, MPolygon, pDC);
	}
	if (pDoc->MDisplayMode == 3) {/// 点击Comparison按钮后执行
		/// 更新comparisonInformation，并将其格式化
		pDoc->comparisonInforamtion = "Here is The Comparison information:\r\n";
		pDoc->comparisonInforamtion += _T("\tPointWise\t\tSorted\t\tSeed\r\nTime:\t");
		CString str;/// 以下为将再次执行上述三个函数的结果写入comparisonInformation
		PointwiseFillPolygon(pNumbers, MPolygon, pDC);
		str.Format(_T("%.2lf"), pDoc->pointwiseRunTime);
		pDoc->comparisonInforamtion += str + _T("\t\t");
		SortedEdgeTableFillPolygon(pNumbers, MPolygon, pDC);
		str.Format(_T("%.2lf"), pDoc->sortedEdgeTableTime);
		pDoc->comparisonInforamtion += str + _T("\t\t");
		SeedFillPolygon(pNumbers, MPolygon, pDC);
		str.Format(_T("%.2lf"), pDoc->seedRunTime);
		pDoc->comparisonInforamtion += str + _T("\r\n");

		pDoc->UpdateAllViews(this);/// 更新视图
	}
	if (pDoc->MDisplayMode == 4) {/// 点击PolygonTriangulation按钮后执行
		if (!PT(pNumbers, MPolygon, pDC))/// 要求点必须逆时针画qwq
			MessageBox(_T("The Polygon is illegal!"));
	}
	pNumbers = 0;/// 更新多边形的边数
	
	CView::OnLButtonDblClk(nFlags, point);
}

/*double a1 = (MPolygon[1].x - MPolygon[0].x);
		double a2 = (MPolygon[1].y - MPolygon[0].y);
		double b1 = (MPolygon[2].x - MPolygon[0].x);
		double b2 = (MPolygon[2].y - MPolygon[0].y);
		if (a1*b2 > b1*a2) {
			std::stack<CPoint>sta;
			for (int i = 0; i < pNumbers; i++) {
				sta.push(MPolygon[i]);
			}
			int i = 0;
			while (!sta.empty()) {
				MPolygon[i++] = sta.top();
				sta.pop();
			}
		}*/
/// MDisplayMode = 4， 加上后顺时针也可