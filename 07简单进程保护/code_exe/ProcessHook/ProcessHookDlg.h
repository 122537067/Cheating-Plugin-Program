
// ProcessHookDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CProcessHookDlg �Ի���
class CProcessHookDlg : public CDialogEx
{
// ����
public:
	CProcessHookDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PROCESSHOOK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSelect();
	CString cs_processname;
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonClose();
	bool LoadDriver(void);
	bool UnloadDriver(void);
	CString m_drivername;
	CString m_driverpath;
	CButton btn_start;
	CButton btn_close;
};
