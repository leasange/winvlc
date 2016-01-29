
// mfcvlcplayerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mfcvlcplayer.h"
#include "mfcvlcplayerDlg.h"
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


// CmfcvlcplayerDlg 对话框



CmfcvlcplayerDlg::CmfcvlcplayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CmfcvlcplayerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmfcvlcplayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STA_VIDEOPANEL, m_hVideoPanel);
	DDX_Control(pDX, IDC_STA_VIDEOPANEL2, m_playerCtrl2);
}

BEGIN_MESSAGE_MAP(CmfcvlcplayerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_STN_CLICKED(IDC_STA_VIDEOPANEL, &CmfcvlcplayerDlg::OnStnClickedStaVideopanel)
	ON_BN_CLICKED(IDC_BTN_RECORD, &CmfcvlcplayerDlg::OnBnClickedBtnRecord)
END_MESSAGE_MAP()


// CmfcvlcplayerDlg 消息处理程序

BOOL CmfcvlcplayerDlg::OnInitDialog()
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

	ShowWindow(SW_MAXIMIZE);

	// TODO:  在此添加额外的初始化代码
	static const char* vlc_args[] =
	{
		"-I",
		"dummy",
		"--ignore-config",
		"--rtsp-caching=100",
		"--realrtsp-caching=100",
		//"--extraintf=logger",
		"--verbose=2",
		"--rtsp-tcp",
		"--rtsp-timeout=60000"
		//str.c_str()
	};
	// 创建一个VLC实例
	instance = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);
	media = libvlc_media_new_location(instance, "rtsp://218.204.223.237:554/live/1/66251FC11353191F/e7ooqwcfbqjoo80j.sdp");
	player = libvlc_media_player_new_from_media(media);
	player2 = libvlc_media_player_new_from_media(media);
	libvlc_media_player_set_hwnd(player, m_hVideoPanel.GetSafeHwnd());
	libvlc_media_player_set_hwnd(player2, m_playerCtrl2.GetSafeHwnd());
	//log_trace_format("开始播放：%s", tempUrl.c_str());
	//manager = libvlc_media_player_event_manager(player);
	//libvlc_event_attach(man, libvlc_event_e::libvlc_MediaPlayerEndReached, player_callback_t, this);
	//libvlc_event_attach(man, libvlc_event_e::libvlc_MediaPlayerEncounteredError, player_callback_t, this);

	// 播放文件
	if (libvlc_media_player_play(player) != 0)      /* play the media_player */
	{
		//log_debug_format("播放失败：%s", tempUrl.c_str());
		libvlc_media_player_release(player);   /* Free the media_player */
		player = 0;
		return -1;
	}
	// 播放文件
	if (libvlc_media_player_play(player2) != 0)      /* play the media_player */
	{
		//log_debug_format("播放失败：%s", tempUrl.c_str());
		libvlc_media_player_release(player2);   /* Free the media_player */
		player = 0;
		return -1;
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CmfcvlcplayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CmfcvlcplayerDlg::OnPaint()
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
HCURSOR CmfcvlcplayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmfcvlcplayerDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	if (m_hVideoPanel.GetSafeHwnd())
	{
		RECT rect;
		GetClientRect(&rect);
		m_hVideoPanel.MoveWindow(0, 0, (rect.right - rect.left)/2-2, (rect.bottom - rect.top)/2);
		m_playerCtrl2.MoveWindow((rect.right - rect.left) / 2 + 2, 0, (rect.right - rect.left) / 2 - 4, (rect.bottom - rect.top) / 2);
	}
	if (GetDlgItem(IDC_BTN_RECORD))
	{
		RECT rect;
		GetClientRect(&rect);
		GetDlgItem(IDC_BTN_RECORD)->MoveWindow(0, (rect.bottom - rect.top) - 100, 200, 30);
	}
}


void CmfcvlcplayerDlg::OnStnClickedStaVideopanel()
{
	// TODO:  在此添加控件通知处理程序代码
	MessageBox(_T("单击可以啦！"));
}


void CmfcvlcplayerDlg::OnBnClickedBtnRecord()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!libvlc_video_is_recording(player))
	{
		libvlc_video_toggle_record(player, "E:\\xxx");
		GetDlgItem(IDC_BTN_RECORD)->SetWindowTextW(_T("停止录像"));
	}
	else
	{
		libvlc_video_toggle_record(player, NULL);
		GetDlgItem(IDC_BTN_RECORD)->SetWindowTextW(_T("开始录像"));
	}
}
