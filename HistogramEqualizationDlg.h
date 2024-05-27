
// HistogramEqualizationDlg.h: 헤더 파일
//

#pragma once

// 스택 영역이 기본 1MB라 생성이 안 됨
// 이에 [프로젝트 설정]->[링커]->[시스템]에 스택 예약 크기를 256MB(268435456)로 변경하였음
typedef struct YUV {
	int Y;
	int U;
	int V;
} YUV;

// CHistogramEqualizationDlg 대화 상자
class CHistogramEqualizationDlg : public CDialogEx
{
// 생성입니다.
public:
	CHistogramEqualizationDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HISTOGRAMEQUALIZATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButtonOpen();
	afx_msg void OnClickedButtonHist();
	afx_msg void OnBnClickedButtonDraw();
	CImage m_image;
	CImage m_imageAfter;
	
	// 영상의 픽셀별 YUV(Y, Cb, Cr) 값
	YUV beforeYUVColor[256][256];
	YUV afterYUVColor[256][256];

	// Y 개수 배열
	int beforeYCnt[256];

	// Y 누적합 배열
	int beforeSumYCnt[256];

	// 전후 RGB 개수 세기
	int beforeRCnt[256], beforeGCnt[256], beforeBCnt[256];
	int afterRCnt[256], afterGCnt[256], afterBCnt[256];
	
	void createHistogram();

	template <typename T>
	inline T limit(const T& value)
	{
		return ((value > 255) ? 255 : ((value < 0) ? 0 : value));
	}
	void RGB_TO_YUV(int R, int G, int B, int& Y, int& U, int& V);
	void YUV_TO_RGB(int Y, int U, int V, int& R, int& G, int& B);
	CSliderCtrl sliderRGB;
};
