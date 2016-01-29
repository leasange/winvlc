
// mfcvlcplayerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mfcvlcplayer.h"
#include "mfcvlcplayerDlg.h"
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


// CmfcvlcplayerDlg �Ի���



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


// CmfcvlcplayerDlg ��Ϣ�������

BOOL CmfcvlcplayerDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MAXIMIZE);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
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
	// ����һ��VLCʵ��
	instance = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);
	media = libvlc_media_new_location(instance, "rtsp://218.204.223.237:554/live/1/66251FC11353191F/e7ooqwcfbqjoo80j.sdp");
	player = libvlc_media_player_new_from_media(media);
	player2 = libvlc_media_player_new_from_media(media);
	libvlc_media_player_set_hwnd(player, m_hVideoPanel.GetSafeHwnd());
	libvlc_media_player_set_hwnd(player2, m_playerCtrl2.GetSafeHwnd());
	//log_trace_format("��ʼ���ţ�%s", tempUrl.c_str());
	//manager = libvlc_media_player_event_manager(player);
	//libvlc_event_attach(man, libvlc_event_e::libvlc_MediaPlayerEndReached, player_callback_t, this);
	//libvlc_event_attach(man, libvlc_event_e::libvlc_MediaPlayerEncounteredError, player_callback_t, this);

	// �����ļ�
	if (libvlc_media_player_play(player) != 0)      /* play the media_player */
	{
		//log_debug_format("����ʧ�ܣ�%s", tempUrl.c_str());
		libvlc_media_player_release(player);   /* Free the media_player */
		player = 0;
		return -1;
	}
	// �����ļ�
	if (libvlc_media_player_play(player2) != 0)      /* play the media_player */
	{
		//log_debug_format("����ʧ�ܣ�%s", tempUrl.c_str());
		libvlc_media_player_release(player2);   /* Free the media_player */
		player = 0;
		return -1;
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CmfcvlcplayerDlg::OnPaint()
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
HCURSOR CmfcvlcplayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmfcvlcplayerDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	MessageBox(_T("������������"));
}


void CmfcvlcplayerDlg::OnBnClickedBtnRecord()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!libvlc_video_is_recording(player))
	{
		libvlc_video_toggle_record(player, "E:\\xxx");
		GetDlgItem(IDC_BTN_RECORD)->SetWindowTextW(_T("ֹͣ¼��"));
	}
	else
	{
		libvlc_video_toggle_record(player, NULL);
		GetDlgItem(IDC_BTN_RECORD)->SetWindowTextW(_T("��ʼ¼��"));
	}
}
