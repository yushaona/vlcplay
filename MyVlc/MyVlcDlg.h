
// MyVlcDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


#include <xstring>
using namespace std;
#include "..\public_include\vlc\vlc.h"

// CMyVlcDlg �Ի���
class CMyVlcDlg : public CDialog
{
// ����
public:
	CMyVlcDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MYVLC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	static  DWORD  WINAPI ThreadFunc(void* params);
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg LRESULT OnUpdateStatic(WPARAM wParam, LPARAM lParam);
	CString m_path;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};

/*
typedef DWORD (WINAPI *PTHREAD_START_ROUTINE)(
LPVOID lpThreadParameter
);
*/


class VLCPlayer
{
private:
	libvlc_instance_t *     vlc_ins;
	libvlc_media_player_t * vlc_player;
	libvlc_media_t *        vlc_media ;

private:
	VLCPlayer();
	~VLCPlayer();
	static VLCPlayer *s_Instance;

public:
	static VLCPlayer *NewVLC();
	
	//��ȡ��Ƶʱ��
	__int64 GetVideoLen();
	//����
	void  Play(string fileName,HANDLE hWnd);
	//��ͣ
	void Pause();
	//����
	void Resume();
	//ֹͣ
	void Stop();
};