
// cgWGFillPolyDoc.h : CcgWGFillPolyDoc 类的接口
//


#pragma once


class CcgWGFillPolyDoc : public CDocument
{
protected: // 仅从序列化创建
	CcgWGFillPolyDoc();
	DECLARE_DYNCREATE(CcgWGFillPolyDoc)

// 特性
public:
	int MHeight;/// 视窗高度
	int MWidth;/// 视窗宽度
	int MDisplayMode;/// 函数模式

	double pointwiseRunTime;/// 逐点法运行时间
	CString pointwiseInformation;/// 逐点法显示信息
	double sortedEdgeTableTime;/// 有序边表法运行时间
	CString sortedEdgeTableInformation;/// 有序边表法显示信息
	double seedRunTime;/// 种子法运行时间
	CString seedInformation;/// 种子法显示信息
	CString comparisonInforamtion;/// 比较显示信息
	double polygonalTriangualtionRuntime;/// 多边形的三角剖分时间
	CString polygonalTriangulationInformation;/// 多边形的三角剖分信息

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CcgWGFillPolyDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
