
// CrosshairsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Crosshairs.h"
#include "CrosshairsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCrosshairsDlg �Ի���




CCrosshairsDlg::CCrosshairsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCrosshairsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCrosshairsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_crosstype);
	DDX_Control(pDX, IDC_SLIDERR, m_csliderR);
	DDX_Control(pDX, IDC_SLIDERG, m_csliderG);
	DDX_Control(pDX, IDC_SLIDERB, m_csliderB);
	DDX_Control(pDX, IDC_SLIDER_SIZE, m_csliderSIZE);
	DDX_Control(pDX, IDC_SLIDER_SIZE2, m_csliderWEIGHT);
}

BEGIN_MESSAGE_MAP(CCrosshairsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CCrosshairsDlg::OnBnClickedButtonStart)
ON_CBN_SELENDOK(IDC_COMBO_TYPE, &CCrosshairsDlg::OnCbnSelendokComboType)
ON_BN_CLICKED(IDC_BUTTON_EXIT, &CCrosshairsDlg::OnBnClickedButtonExit)
ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERR, &CCrosshairsDlg::OnNMReleasedcaptureSlider2)
ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERG, &CCrosshairsDlg::OnNMReleasedcaptureSliderg)
ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERB, &CCrosshairsDlg::OnNMReleasedcaptureSliderb)
ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_SIZE, &CCrosshairsDlg::OnNMReleasedcaptureSliderSize)
ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_WEIGHT, &CCrosshairsDlg::OnNMReleasedcaptureSliderWeight)
END_MESSAGE_MAP()


// CCrosshairsDlg ��Ϣ�������

int red =255, green = 0, blue = 0;
int crosstype = 0;
int crosssize = 23;
int crossweight = 1.1;
BOOL CCrosshairsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_crosstype.SetCurSel(0);
	m_csliderR.SetPos(100);
	m_csliderSIZE.SetPos(30);
	m_csliderWEIGHT.SetPos(15);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCrosshairsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCrosshairsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCrosshairsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HWND hwnd, hdlgwnd;
HANDLE hSetCross = NULL;
DWORD WINAPI SetCross(LPVOID lpParam) {
	while (true) {
		hwnd = ::FindWindow(NULL, L"Counter-Strike");
		//hwnd = ::FindWindow(L"Notepad", NULL);
		hdlgwnd = ::FindWindow(NULL, L"����׼��");

		if (::IsWindow(hwnd)) {
				HDC hdc = ::GetDC(hwnd);	//��Ϸ����
				HDC hdlgdc = ::GetDC(hdlgwnd);	//������
				CDC cdc;
				CDC dlgcdc;
				cdc.Attach(hdc);
				dlgcdc.Attach(hdlgdc);

				HPEN hpen = ::CreatePen(PS_SOLID, crossweight, RGB(red,green,blue));
				HPEN hpenold = (HPEN)cdc.SelectObject(hpen);
				HPEN hdlgpenold = (HPEN)dlgcdc.SelectObject(hpen);
				RECT rect;
				int width, height;

				::GetClientRect(hwnd, &rect);
				width = rect.right - rect.left;
				height = rect.bottom - rect.top;

				if (crosstype == 0) {		//���׼��
					cdc.MoveTo(width/2 - crosssize, height/2);
					cdc.LineTo(width/2 - 6, height/2);
					cdc.MoveTo(width/2 + 6, height/2);
					cdc.LineTo(width/2 + crosssize, height/2);
					cdc.MoveTo(width/2, height/2-crosssize);
					cdc.LineTo(width/2, height/2-6);
					cdc.MoveTo(width/2, height/2+6);
					cdc.LineTo(width/2, height/2+crosssize);
					CBrush brush,*oldbrush;
					oldbrush=cdc.SelectObject(&brush);
					cdc.Ellipse(width/2 -1, height/2-1, width/2+1, height/2+1);
					cdc.SelectObject(oldbrush);


					width = 55;
					height = 75;
					dlgcdc.MoveTo(width/2 - crosssize, height/2);
					dlgcdc.LineTo(width/2 - 6, height/2);
					dlgcdc.MoveTo(width/2 + 6, height/2);
					dlgcdc.LineTo(width/2 + crosssize, height/2);
					dlgcdc.MoveTo(width/2, height/2-crosssize);
					dlgcdc.LineTo(width/2, height/2-6);
					dlgcdc.MoveTo(width/2, height/2+6);
					dlgcdc.LineTo(width/2, height/2+crosssize);

					CBrush dlgbrush,*olddlgbrush;
					olddlgbrush=dlgcdc.SelectObject(&dlgbrush);
					dlgcdc.Ellipse(width/2 -1, height/2-1, width/2+1, height/2+1);
					dlgcdc.SelectObject(olddlgbrush);

				} else if (crosstype == 1) {		//ʮ��׼��
					cdc.MoveTo(width/2 - crosssize, height/2);
					cdc.LineTo(width/2 + crosssize, height/2);
					cdc.MoveTo(width/2, height/2-crosssize);
					cdc.LineTo(width/2, height/2+crosssize);

					width = 55;
					height = 75;
					dlgcdc.MoveTo(width/2 - crosssize, height/2);
					dlgcdc.LineTo(width/2 + crosssize, height/2);
					dlgcdc.MoveTo(width/2, height/2-crosssize);
					dlgcdc.LineTo(width/2, height/2+crosssize);
				} else if (crosstype == 2)  {			//����׼��
					CBrush brush,*oldbrush;
					oldbrush=cdc.SelectObject(&brush);
					cdc.Ellipse(width/2 -1, height/2-1, width/2+1, height/2+1);
					cdc.SelectObject(oldbrush);

					width = 55;
					height = 75;
					CBrush dlgbrush,*olddlgbrush;
					olddlgbrush=dlgcdc.SelectObject(&dlgbrush);
					dlgcdc.Ellipse(width/2 -1, height/2-1, width/2+1, height/2+1);
					dlgcdc.SelectObject(olddlgbrush);
				} else if (crosstype == 3)  {		//Բ��׼��
					CRgn r,r1,r2,rgn;
					r.CreateEllipticRgn(width/2-crossweight,height/2-crossweight,width/2+crossweight,height/2+crossweight);
					r1.CreateEllipticRgn(width/2-crosssize-crossweight,height/2-crosssize-crossweight,width/2+crosssize+crossweight,height/2+crosssize+crossweight);
					r2.CreateEllipticRgn(width/2-crosssize,height/2-crosssize,width/2+crosssize,height/2+crosssize);
					rgn.CreateRectRgn(width/2-crosssize-crossweight-5,height/2-crosssize-crossweight-5,width/2+crosssize+crossweight+5,height/2+crosssize+crossweight+5);
					//�ϲ�
					rgn.CombineRgn(&r1,&r2,RGN_DIFF);
					CBrush bsh(RGB(red,green,blue));
					cdc.FillRgn(&r,&bsh);
					cdc.FillRgn(&rgn,&bsh);
					rgn.DeleteObject();
					r.DeleteObject();
					r1.DeleteObject();
					r2.DeleteObject();

					width = 55;
					height = 75;
					CRgn dlgr,dlgr1,dlgr2,dlgrgn;
					dlgr.CreateEllipticRgn(width/2-crossweight,height/2-crossweight,width/2+crossweight,height/2+crossweight);
					dlgr1.CreateEllipticRgn(width/2-crosssize-crossweight,height/2-crosssize-crossweight,width/2+crosssize+crossweight,height/2+crosssize+crossweight);
					dlgr2.CreateEllipticRgn(width/2-crosssize,height/2-crosssize,width/2+crosssize,height/2+crosssize);
					dlgrgn.CreateRectRgn(width/2-crosssize-crossweight-5,height/2-crosssize-crossweight-5,width/2+crosssize+crossweight+5,height/2+crosssize+crossweight+5);
					//�ϲ�
					dlgrgn.CombineRgn(&dlgr1,&dlgr2,RGN_DIFF);
					CBrush dlgbsh(RGB(red,green,blue));
					dlgcdc.FillRgn(&dlgr,&dlgbsh);
					dlgcdc.FillRgn(&dlgrgn,&dlgbsh);
					dlgr.DeleteObject();
					dlgrgn.DeleteObject();
					dlgr1.DeleteObject();
					dlgr2.DeleteObject();
				}
				dlgcdc.SelectObject(hdlgpenold);
				cdc.SelectObject(hpenold);
				::DeleteObject(hpen);
				::ReleaseDC(hwnd, hdc);
				::ReleaseDC(hdlgwnd, hdlgdc);
				cdc.DeleteDC();
				dlgcdc.DeleteDC();
		} 

	}
	return 0;
}

BOOL bstatus = -1;
void CCrosshairsDlg::OnBnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (bstatus == -1) {		//δ��ʼ���¿��߳�
		hSetCross = ::CreateThread(NULL, 0, SetCross, NULL, 0, NULL);
		bstatus = true;
	} else if (bstatus == true) {		//�ѿ�ʼ����ͣ�߳�
		::SuspendThread(hSetCross);
		::RedrawWindow(hwnd, NULL, NULL, RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW);
		Invalidate(true);
		bstatus = false;
	} else if (bstatus == false) {		//����ͣ��ָ��߳�
		::ResumeThread(hSetCross);
		bstatus = true;
	}
}



void CCrosshairsDlg::OnCbnSelendokComboType()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TRACE("type change!type = %d\n", m_crosstype.GetCurSel());
	crosstype = m_crosstype.GetCurSel();
	::Sleep(20);
	::RedrawWindow(hwnd, NULL, NULL, RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW);
	Invalidate(true);
}


void CCrosshairsDlg::OnBnClickedButtonExit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::TerminateThread(hSetCross, 0);
	::RedrawWindow(hwnd, NULL, NULL, RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW);
	::Sleep(20);
	::RedrawWindow(hwnd, NULL, NULL, RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW);
	Invalidate(true);
	exit(0);
}


void CCrosshairsDlg::OnNMReleasedcaptureSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TRACE("r = %d\n", m_csliderR.GetPos());
	red = (m_csliderR.GetPos()/100.0)*255;
	::Sleep(20);
	::RedrawWindow(hwnd, NULL, NULL, RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW);
	Invalidate(true);
	*pResult = 0;
}


void CCrosshairsDlg::OnNMReleasedcaptureSliderg(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TRACE("g = %d\n", m_csliderG.GetPos());
	green = (m_csliderG.GetPos()/100.0)*255;
	::Sleep(20);
	::RedrawWindow(hwnd, NULL, NULL, RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW);
	Invalidate(true);
	*pResult = 0;
}


void CCrosshairsDlg::OnNMReleasedcaptureSliderb(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TRACE("b = %d\n", m_csliderB.GetPos());
	blue = (m_csliderB.GetPos()/100.0)*255;
	::Sleep(20);
	::RedrawWindow(hwnd, NULL, NULL, RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW);
	Invalidate(true);
	*pResult = 0;
}


void CCrosshairsDlg::OnNMReleasedcaptureSliderSize(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TRACE("size change!%d\n", m_csliderSIZE.GetPos());
	crosssize = (m_csliderSIZE.GetPos()/100.0)*50+10;
	::Sleep(20);
	::RedrawWindow(hwnd, NULL, NULL, RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW);
	Invalidate(true);
	*pResult = 0;
}


void CCrosshairsDlg::OnNMReleasedcaptureSliderWeight(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TRACE("weight change!%d\n", m_csliderWEIGHT.GetPos());
	crossweight = (m_csliderWEIGHT.GetPos()/100.0)*5;
	::Sleep(20);
	::RedrawWindow(hwnd, NULL, NULL, RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW);
	Invalidate(true);
	*pResult = 0;
}
