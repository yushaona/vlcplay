
// MyVlcDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


#include <xstring>
using namespace std;
#include "..\public_include\vlc\vlc.h"

// CMyVlcDlg 对话框
class CMyVlcDlg : public CDialog
{
// 构造
public:
	CMyVlcDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MYVLC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	static  DWORD  WINAPI ThreadFunc(void* params);
	// 生成的消息映射函数
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
	
	//获取视频时长
	__int64 GetVideoLen();
	//播放
	void  Play(string fileName,HANDLE hWnd);
	//暂停
	void Pause();
	//继续
	void Resume();
	//停止
	void Stop();
};