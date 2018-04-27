
// UARTDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UART.h"
#include "UARTDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CUARTDlg 对话框



CUARTDlg::CUARTDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUARTDlg::IDD, pParent)
	, m_EditReceive(_T(""))
	, m_EditSend(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUARTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Rec, m_EditReceive);
	DDX_Text(pDX, IDC_EDIT_Sen, m_EditSend);
	DDX_Control(pDX, IDC_COMBO1, m_comport);
	DDX_Control(pDX, IDC_COMBO2, m_Baud);
	DDX_Control(pDX, IDC_MSCOMM1, m_mscom);
}

BEGIN_MESSAGE_MAP(CUARTDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CUARTDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CUARTDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_CLEAN, &CUARTDlg::OnBnClickedButtonClean)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CUARTDlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_CLEANSEND, &CUARTDlg::OnBnClickedButtonCleansend)
END_MESSAGE_MAP()


// CUARTDlg 消息处理程序

BOOL CUARTDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	CString str;
	int i;
	for (i = 0; i < 15; i++)
	{

		str.Format(_T("com %d"), i + 1);
		m_comport.InsertString(i,str);
	}
	m_comport.SetCurSel(0);
	CString str1[] = { _T("300"), _T("600"), _T("1200"), _T("2400"), _T("4800"), _T("9600"), _T("19200"), _T("38400"), _T("43000"), _T("56000"), _T("57600"), _T("115200") };
	for (i = 0; i < 12; i++)
	{
		int judge_tf = m_Baud.AddString(str1[i]);
		if ((judge_tf == CB_ERR) || (judge_tf == CB_ERRSPACE))
			MessageBox(_T("build baud error!"));
	}
	m_Baud.SetCurSel(5);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CUARTDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUARTDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CUARTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUARTDlg::OnBnClickedButtonOpen()		//打开串口按钮程序
{
	// TODO:  在此添加控件通知处理程序代码
	CString str, str1, n;
	GetDlgItemText(IDC_BUTTON_OPEN,str);
	CWnd *h1;
	h1 = GetDlgItem(IDC_BUTTON_OPEN);
	if (!m_mscom.get_PortOpen())
	{
		m_Baud.GetLBText(m_Baud.GetCurSel(),str1);
		str1 = str1 + ',' + 'n' + ',' + '8' + ',' + '1';
		m_mscom.put_CommPort((m_comport.GetCurSel()+1));
		m_mscom.put_InputMode(1);
		m_mscom.put_Settings(str1);
		m_mscom.put_InputLen(1024);
		m_mscom.put_RThreshold(1);
		m_mscom.put_RTSEnable(1);
		m_mscom.put_PortOpen(true);
		if (m_mscom.get_PortOpen())
		{
			str = _T("关闭串口");
			UpdateData(true);
			h1->SetWindowTextW(str);
		}
		else
		{
			m_mscom.put_PortOpen(false);
			if (str != _T("打卡串口"))
			{
				str = _T("打卡串口");
				UpdateData(true);
				h1->SetWindowTextW(str);

			}
			
		}


	}
}


void CUARTDlg::OnBnClickedButtonSend()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	m_mscom.put_Output(COleVariant(m_EditSend));
}


void CUARTDlg::OnBnClickedButtonClean()
{
	// TODO:  在此添加控件通知处理程序代码
	//m_EditReceive = _T("");
	//UpdateData(false);
	GetDlgItem(IDC_EDIT_Rec)->SetWindowTextW(_T(""));
}


void CUARTDlg::OnBnClickedButtonClose()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_mscom.get_PortOpen())
	{
		m_mscom.put_PortOpen(false);
	}
	CDialogEx::OnCancel();
}
BEGIN_EVENTSINK_MAP(CUARTDlg, CDialogEx)
	ON_EVENT(CUARTDlg, IDC_MSCOMM1, 1, CUARTDlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


void CUARTDlg::OnCommMscomm1()
{
	// TODO:  在此处添加消息处理程序代码
	if (m_mscom.get_CommEvent() == 2)
	{
		char str[1024] = {0};
		long k;
		VARIANT InputData = m_mscom.get_Input();
		COleSafeArray fs;
		fs = InputData;
		for (k = 0; k < fs.GetOneDimSize(); k++)
			fs.GetElement(&k, str + k);
		m_EditReceive += str;
		UpdateData(true);
	}
}


void CUARTDlg::OnBnClickedButtonCleansend()
{
	// TODO:  在此添加控件通知处理程序代码
	// TODO:  在此添加控件通知处理程序代码
	//m_EditSend = _T("");
	//UpdateData(false);
	GetDlgItem(IDC_EDIT_Sen)->SetWindowTextW(_T(""));
}
