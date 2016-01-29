
// mfcvlcplayerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "vlc\vlc.h"

// CmfcvlcplayerDlg 对话框
class CmfcvlcplayerDlg : public CDialogEx
{
// 构造
public:
	CmfcvlcplayerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCVLCPLAYER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
private:
	libvlc_instance_t * instance;
	libvlc_media_player_t *player;
	libvlc_media_player_t *player2;
	libvlc_event_manager_t* manager;
	libvlc_media_t *media;
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 播放器窗体
	CStatic m_hVideoPanel;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnStnClickedStaVideopanel();
	CStatic m_playerCtrl2;
	afx_msg void OnBnClickedBtnRecord();
};
