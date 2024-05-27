
// HistogramEqualizationDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "HistogramEqualization.h"
#include "HistogramEqualizationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHistogramEqualizationDlg 대화 상자



CHistogramEqualizationDlg::CHistogramEqualizationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HISTOGRAMEQUALIZATION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHistogramEqualizationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_RGB, sliderRGB);
}

BEGIN_MESSAGE_MAP(CHistogramEqualizationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CHistogramEqualizationDlg::OnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_HIST, &CHistogramEqualizationDlg::OnClickedButtonHist)
	ON_BN_CLICKED(IDC_BUTTON_DRAW, &CHistogramEqualizationDlg::OnBnClickedButtonDraw)
END_MESSAGE_MAP()


// CHistogramEqualizationDlg 메시지 처리기

BOOL CHistogramEqualizationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	// 슬라이더 범위 설정
	sliderRGB.SetRangeMin(0);
	sliderRGB.SetRangeMax(2);
	sliderRGB.SetPos(0);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CHistogramEqualizationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CHistogramEqualizationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CHistogramEqualizationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHistogramEqualizationDlg::OnClickedButtonOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_image.IsNull()) {
		HRESULT hr = m_image.Load(_T("test image.bmp"));
		if (SUCCEEDED(hr)) {
			((CStatic*)GetDlgItem(IDC_STATIC_BEFORE))->SetBitmap(m_image);
		}
	}
	GetDlgItem(IDC_BUTTON_HIST)->ShowWindow(TRUE);
	
}


void CHistogramEqualizationDlg::OnClickedButtonHist()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	createHistogram();
	((CStatic*)GetDlgItem(IDC_STATIC_AFTER))->SetBitmap(m_imageAfter);
	GetDlgItem(IDC_BUTTON_DRAW)->ShowWindow(TRUE);
	GetDlgItem(IDC_SLIDER_RGB)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_TEXT_R)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_TEXT_G)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_TEXT_B)->ShowWindow(TRUE);
	
}


void CHistogramEqualizationDlg::createHistogram()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_imageAfter.IsNull()) {
		m_imageAfter.Create(256, 256, 24);
	}
	//int bp =  m_image.GetBPP(); // 24비트 영상
	// 초기화
	for (int i = 0; i < 256; i++) {
		beforeYCnt[i] = 0; 

		beforeSumYCnt[i] = 0;

		beforeRCnt[i] = 0, beforeGCnt[i] = 0, beforeBCnt[i] = 0;
		afterRCnt[i] = 0, afterGCnt[i] = 0, afterBCnt[i] = 0;
	}

	// Y에 대한 히스토그램 평활화 개시
	COLORREF pixColor;
	int r, g, b;
	int k, sum = 0, totalPixels = 256 * 256;
	for (int i = 0; i < m_image.GetHeight(); i++) {
		for (int j = 0; j < m_image.GetWidth(); j++) {
			pixColor = m_image.GetPixel(j, i);
			r = GetRValue(pixColor);
			g = GetGValue(pixColor);
			b = GetBValue(pixColor);

			// 원본 영상의 R, G, B 각 개수 카운팅
			beforeRCnt[r]++;
			beforeGCnt[g]++;
			beforeBCnt[b]++;

			// RGB를 YUV(Y Cb Cr)로 바꾸기
			RGB_TO_YUV(r, g, b, beforeYUVColor[i][j].Y, beforeYUVColor[i][j].U, beforeYUVColor[i][j].V);

			// Y의 히스토그램 평활화를 위한 Y의 개수 카운팅
			beforeYCnt[beforeYUVColor[i][j].Y]++;
		}
	}
	// Y의 누적합 구하기
	beforeSumYCnt[0] = beforeYCnt[0];
	for (int i = 1; i < 256; i++)
		beforeSumYCnt[i] = beforeSumYCnt[i - 1] + beforeYCnt[i];
	
	// Y에 대한 히스토그램 평활화 실시
	for (int i = 0; i < m_image.GetHeight(); i++) {
		for (int j = 0; j < m_image.GetWidth(); j++) {
			// 우선 결과 영상의 YUV에 원본 영상 YUV 대입
			afterYUVColor[i][j] = beforeYUVColor[i][j];

			// 이전 Y에 대하여 히스토그램 평활화
			k = beforeYUVColor[i][j].Y;
			afterYUVColor[i][j].Y = beforeSumYCnt[k] * (255.0 / totalPixels);

			// 평활화 된 Y`에 대해 Y`UV로 RGB 변환
			YUV_TO_RGB(afterYUVColor[i][j].Y, afterYUVColor[i][j].U, afterYUVColor[i][j].V, r, g, b);

			// 결과 영상의 R, G, B 각 개수 카운팅
			afterRCnt[r]++;
			afterGCnt[g]++;
			afterBCnt[b]++;

			// 결과 영상의 현재 픽셀에 RGB값 설정
			m_imageAfter.SetPixel(j, i, RGB(r, g, b));
		}
	}

}

void CHistogramEqualizationDlg::RGB_TO_YUV(int R, int G, int B, int& Y, int& U, int& V)
{
	// TODO: 여기에 구현 코드 추가.
	Y = (int)limit(0.299 * R + 0.587 * G + 0.114 * B + 0.5);
	U = (int)limit(-0.169 * R - 0.331 * G + 0.500 * B + 128 + 0.5);
	V = (int)limit(0.500 * R - 0.419 * G - 0.081 * B + 128 + 0.5);
}


void CHistogramEqualizationDlg::YUV_TO_RGB(int Y, int U, int V, int& R, int& G, int& B)
{
	// TODO: 여기에 구현 코드 추가.
	R = (int)limit(Y + 1.4075 * (V - 128) + 0.5);
	G = (int)limit(Y - 0.3455 * (U - 128) - 0.7169 * (V - 128) + 0.5);
	B = (int)limit(Y + 1.7790 * (U - 128) + 0.5);
}


void CHistogramEqualizationDlg::OnBnClickedButtonDraw()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// flag
	//	0: R, 1: G, 2: B
	int flag = sliderRGB.GetPos(), sum = 0;
	CClientDC dc(this);
	// 히스토그램 그리기
	
	// 흰 배경으로 채우기
	dc.FillSolidRect(340, 268, 256, -256, RGB(255, 255, 255));
	dc.FillSolidRect(340, 540, 256, -256, RGB(255, 255, 255));
	for (int i = 0; i < 256; i++) {
		if (flag == 0) {		// R
			// 1픽셀씩 빨간색으로 사각형 그리기.
			// 카운트가 너무 커서 50으로 나누고 소수점 올림으로 사용
			dc.FillSolidRect(340 + i, 268, 1, -ceil(beforeRCnt[i] / 50.), RGB(255, 0, 0));
			dc.FillSolidRect(340 + i, 540, 1, -ceil(afterRCnt[i] / 50.), RGB(255, 0, 0));
		}
		else if (flag == 1) {	// G
			dc.FillSolidRect(340 + i, 268, 1, -ceil(beforeGCnt[i] / 50.), RGB(0, 255, 0));
			dc.FillSolidRect(340 + i, 540, 1, -ceil(afterGCnt[i] / 50.), RGB(0, 255, 0));
		}
		else{					// B
			dc.FillSolidRect(340 + i, 268, 1, -ceil(beforeBCnt[i] / 50.), RGB(0, 0, 255));
			dc.FillSolidRect(340 + i, 540, 1, -ceil(afterBCnt[i] / 50.), RGB(0, 0, 255));
		}
	}
	// 누적분포함수 그리기

	// 원본 영상에 대한 누적 분포함수
	dc.FillSolidRect(670, 268, 256, -256, RGB(255, 255, 255));
	dc.MoveTo(670, 268);
	for (int i = 0; i < 256; i++) {
		if (flag == 0) {		// R
			dc.SelectObject(new CPen(0,0, RGB(255, 0, 0)));
			sum += beforeRCnt[i];
		}
		else if (flag == 1) {	// G
			dc.SelectObject(new CPen(0, 0, RGB(0, 255, 0)));
			sum += beforeGCnt[i];
		}
		else {					// B
			dc.SelectObject(new CPen(0, 0, RGB(0, 0, 255)));
			sum += beforeBCnt[i];
		}
		dc.LineTo(670 + i, 268 - floor(sum / 256.));
	}

	// 히스토그램 평활화 영상에 대한 누적분포 함수
	dc.FillSolidRect(670, 540, 256, -256, RGB(255, 255, 255));
	dc.MoveTo(670, 540);	// 펜 이동
	sum = 0;				// 합 초기화
	for (int i = 0; i < 256; i++) {
		if (flag == 0) {		// R
			// 붉은 색의 펜 오브젝트 생성 및 선택
			dc.SelectObject(new CPen(0, 0, RGB(255, 0, 0)));
			sum += afterRCnt[i];
		}
		else if (flag == 1) {	// G
			dc.SelectObject(new CPen(0, 0, RGB(0, 255, 0)));
			sum += afterGCnt[i];
		}
		else {					// B
			dc.SelectObject(new CPen(0, 0, RGB(0, 0, 255)));
			sum += afterBCnt[i];
		}
		dc.LineTo(670 + i, 540 - floor(sum / 256.));
	}
}
