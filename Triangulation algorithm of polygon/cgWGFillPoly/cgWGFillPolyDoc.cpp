
// cgWGFillPolyDoc.cpp : CcgWGFillPolyDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "cgWGFillPoly.h"
#endif

#include "cgWGFillPolyDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CcgWGFillPolyDoc

IMPLEMENT_DYNCREATE(CcgWGFillPolyDoc, CDocument)

BEGIN_MESSAGE_MAP(CcgWGFillPolyDoc, CDocument)
END_MESSAGE_MAP()


// CcgWGFillPolyDoc 构造/析构

CcgWGFillPolyDoc::CcgWGFillPolyDoc()
{
	// TODO: 在此添加一次性构造代码
	MHeight = 0;
	MWidth = 0;

	MDisplayMode = -1;

	sortedEdgeTableInformation = "Here is the SortedEdgeTable information:\r\n";
	pointwiseInformation = "Here is the Pointwise information:\r\n";
	seedInformation = "Here is The Seed information:\r\n";
	comparisonInforamtion = "Here is The Comparison information:\r\n";
	polygonalTriangulationInformation = "Here is The PolygonTriangulation information:\r\n";
	sortedEdgeTableTime = 0;
	pointwiseRunTime = 0;
	seedRunTime = 0;
	polygonalTriangualtionRuntime = 0;
}

CcgWGFillPolyDoc::~CcgWGFillPolyDoc()
{
}

BOOL CcgWGFillPolyDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CcgWGFillPolyDoc 序列化

void CcgWGFillPolyDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CcgWGFillPolyDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CcgWGFillPolyDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CcgWGFillPolyDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CcgWGFillPolyDoc 诊断

#ifdef _DEBUG
void CcgWGFillPolyDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CcgWGFillPolyDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CcgWGFillPolyDoc 命令
