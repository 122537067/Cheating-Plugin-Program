
// ProcessHookDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProcessHook.h"
#include "ProcessHookDlg.h"
#include "afxdialogex.h"
#include "DLG_PROCESS.h"
#include "ctl_code.h"
#include <winsvc.h>
#include <shlwapi.h>
#pragma comment(lib,"Shlwapi.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////////////////////////
DLG_PROCESS dlg_process;
CProcessHookDlg *g_dlg;
DWORD g_processid;
HANDLE hDevice;
///////////////////////////////////////////////////////////////////////////
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


// CProcessHookDlg �Ի���




CProcessHookDlg::CProcessHookDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProcessHookDlg::IDD, pParent)
	, cs_processname(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProcessHookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PROCESS, cs_processname);
	DDX_Control(pDX, IDC_BUTTON_START, btn_start);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, btn_close);
}

BEGIN_MESSAGE_MAP(CProcessHookDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SELECT, &CProcessHookDlg::OnBnClickedButtonSelect)
	ON_BN_CLICKED(IDC_BUTTON_START, &CProcessHookDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CProcessHookDlg::OnBnClickedButtonClose)
END_MESSAGE_MAP()


// CProcessHookDlg ��Ϣ�������

BOOL CProcessHookDlg::OnInitDialog()
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
	g_dlg = this;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CProcessHookDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CProcessHookDlg::OnPaint()
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
HCURSOR CProcessHookDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CProcessHookDlg::OnBnClickedButtonSelect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (dlg_process.m_hWnd==0)
	{
		dlg_process.Create(IDD_CHOOSEPROCESS,this);
	}
	dlg_process.ShowWindow(SW_SHOW);
}


void CProcessHookDlg::OnBnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (cs_processname.IsEmpty() || g_processid == 0) {
		::MessageBox(NULL, _T("δѡ��Ŀ��"), _T("����"), MB_ICONERROR);
		return;
	}
	WCHAR syspath[255];
	GetCurrentDirectory(sizeof(syspath),syspath);
	TRACE("·��Ϊ:");
	TRACE(syspath);
	TRACE("\n");
	wcscat(syspath, L"\\hook.sys");
    if (PathFileExists(syspath)) {
		m_driverpath = syspath;
		m_drivername = L"hook.sys";
		LoadDriver();		//��������
		hDevice = ::CreateFile(L"\\\\.\\MySysLinkName_20170411", GENERIC_READ | GENERIC_WRITE, 0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL );	//��ʼ����
		TRACE("��ʼ\n");
		if (hDevice == INVALID_HANDLE_VALUE) {
			TRACE("��ȡ�������ʧ��: %s with Win32 error code: %d\n","MyDriver", GetLastError() );
			::MessageBox(NULL, _T("��ȡ�������ʧ��"), _T("����"), MB_ICONERROR);
			getchar();
			return;
		}
		int port[2];
		int buffret;
		ULONG dwWrite;
		port[0] = g_processid;
		::DeviceIoControl(hDevice, hook_code , &port, 8, &buffret, 4, &dwWrite, NULL);
    } else  {
		::MessageBox(NULL, _T("��ǰĿ¼������hook.sys"), _T("����"), MB_ICONERROR);
	}
}


void CProcessHookDlg::OnBnClickedButtonClose()
{
	if (!m_drivername.IsEmpty() && !m_driverpath.IsEmpty() && hDevice) {
			TRACE("��������\n");
			if (hDevice == INVALID_HANDLE_VALUE) {
				TRACE("��ȡ�������ʧ��: %s with Win32 error code: %d\n","MyDriver", GetLastError() );
				::MessageBox(NULL, _T("��ȡ�������ʧ��"), _T("����"), MB_ICONERROR);
				getchar();
				return;
			}
			int port[2];
			int buffret;
			ULONG dwWrite;
			port[0] = g_processid;
			::DeviceIoControl(hDevice, unhook_code , &port, 8, &buffret, 4, &dwWrite, NULL);
			TRACE("unhook�ɹ�\n");
			UnloadDriver();
	} else {
		::MessageBox(NULL, _T("δ��������"), _T("����"), MB_ICONERROR);
	}
}


bool CProcessHookDlg::LoadDriver(void)
{
	bool bRet = false;
	SC_HANDLE hServiceMgr=NULL;		//SCM�������ľ��
	SC_HANDLE hServiceDDK=NULL;	//NT��������ķ�����
	hServiceMgr =  ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);	//�򿪷�����ƹ�����
	if (hServiceMgr == NULL) {
		TRACE( "OpenSCManager()ʧ�ܣ�ԭ��=%d\n", GetLastError() );
		goto BExit;
	} else {
		TRACE( "OpenSCManager()�ɹ�\n");
	}
	hServiceDDK = ::CreateService(hServiceMgr, m_drivername,  m_drivername, SERVICE_ALL_ACCESS, SERVICE_KERNEL_DRIVER, SERVICE_DEMAND_START, SERVICE_ERROR_IGNORE, m_driverpath, NULL, NULL, NULL, NULL, NULL);	//������������Ӧ�ķ���
	if (hServiceDDK == NULL) {
		DWORD dwRtn = GetLastError();
		if( dwRtn != ERROR_IO_PENDING && dwRtn != ERROR_SERVICE_EXISTS )  {  
			TRACE( "��������ԭ�򴴽�����ʧ�ܣ�ԭ��=%d\n", GetLastError() );
			goto BExit;
		}  else  {
			TRACE( "CrateService() ���񴴽�ʧ�ܣ������ڷ����Ѿ���������ԭ��=%d\n", GetLastError() );  
		}
		hServiceDDK = ::OpenService(hServiceMgr, m_drivername, SERVICE_ALL_ACCESS);		// ���������Ѿ����أ�ֻ��Ҫ��  
		if (hServiceDDK == NULL) {
			TRACE( "OpenService()ʧ�ܣ�ԭ��=%d\n", GetLastError() );
			goto BExit;
		} else {
			TRACE( "OpenService()�ɹ�\n");
		}
	} else {
		TRACE( "CreateService()�ɹ�\n");
	}
	bool ret = ::StartService(hServiceDDK, NULL, NULL);	//�����������
	if (ret == false) {
		TRACE( "StartService()ʧ�ܣ���������Ѿ�������ԭ��=%d\n", GetLastError() );
	}
	bRet = true;
BExit:	//�뿪ǰ��Ӧ����
	if(hServiceDDK) {
		CloseServiceHandle(hServiceDDK);
	}
	if(hServiceMgr) {
		CloseServiceHandle(hServiceMgr);
	}
	return bRet;
}


bool CProcessHookDlg::UnloadDriver(void)
{
	bool bRet = false;
	SC_HANDLE hSCM=NULL;		//SCM�������ľ��,�������OpenSCManager�ķ���ֵ
	SC_HANDLE hService=NULL;	//NT��������ķ��������������OpenService�ķ���ֵ
	SERVICE_STATUS SvrSta;
	hSCM = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS );  //��SCM������
	if( hSCM == NULL ) {
		TRACE( "OpenSCManager() ʧ�� %d ! \n", GetLastError());  
		goto BeforeLeave;
	} else {
		TRACE( "OpenSCManager() �ɹ� ! \n" );  
	}
	hService = OpenService( hSCM, m_drivername, SERVICE_ALL_ACCESS);  //����������Ӧ�ķ���
	if( hService == NULL )  {
		TRACE( "OpenService() ʧ�� %d ! \n", GetLastError() );  
		goto BeforeLeave;
	} else {  
		TRACE( "OpenService() �ɹ� ! \n" );
	} 
	if( !ControlService( hService, SERVICE_CONTROL_STOP , &SvrSta ) ) {		//ֹͣ�����������ֹͣʧ�ܣ�ֻ�������������ܣ��ٶ�̬����
		TRACE( "��ControlService() ֹͣ��������ʧ�� :%d !\n", GetLastError() );  
	}  else  {
		TRACE( "��ControlService() ֹͣ��������ɹ� !\n" );  
	}  
	if( !DeleteService( hService ) ) {		//��̬ж����������
		TRACE( "ж��ʧ��:DeleteSrevice()�����:%d !\n", GetLastError() );  
	}  else  {  
		TRACE ( "ж�سɹ� !\n" );  
	}  
	bRet = true;
BeforeLeave:		//�뿪ǰ�رմ򿪵ľ��
	if(hService>0) {
		CloseServiceHandle(hService);
	}
	if(hSCM>0) {
		CloseServiceHandle(hSCM);
	}
	return bRet;
}
