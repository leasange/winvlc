
// mfcvlcplayerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "vlc\vlc.h"

// CmfcvlcplayerDlg �Ի���
class CmfcvlcplayerDlg : public CDialogEx
{
// ����
public:
	CmfcvlcplayerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCVLCPLAYER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
private:
	libvlc_instance_t * instance;
	libvlc_media_player_t *player;
	libvlc_media_player_t *player2;
	libvlc_event_manager_t* manager;
	libvlc_media_t *media;
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
	// ����������
	CStatic m_hVideoPanel;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnStnClickedStaVideopanel();
	CStatic m_playerCtrl2;
	afx_msg void OnBnClickedBtnRecord();
};
