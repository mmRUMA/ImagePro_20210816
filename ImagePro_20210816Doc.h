
// ImagePro_20210816Doc.h: CImagePro20210816Doc 클래스의 인터페이스
//


#pragma once


class CImagePro20210816Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CImagePro20210816Doc() noexcept;
	DECLARE_DYNCREATE(CImagePro20210816Doc)

// 특성입니다.
public:
	unsigned char **inputImg; // 입력 영상1에 대한 포인터
	unsigned char **inputImg2; // 입력 영상2에 대한 포인터
	unsigned char **resultImg; // 결과 영상에 대한 포인터
	int imageWidth, imageHeight; // 영상의 크기
	int depth; // 흑백 영상 = 1, 컬러 영상 = 3

	int gImageWidth, gImageHeight; // 크기가 변환 영상의 크기
	unsigned char** gResultImg; // 크기가 변한 결과 영상에 대한 포인터
// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CImagePro20210816Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	void LoadImageFile(CArchive& ar);
	void LoadSecondImageFile(CArchive& ar);
};
