
// MyVlcDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MyVlc.h"
#include "MyVlcDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



#define WM_UPDATE (WM_USER+10)

// CMyVlcDlg 对话框




CMyVlcDlg::CMyVlcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyVlcDlg::IDD, pParent)
	, m_path(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_path = _T("D:\\video\\2.mp4");
}

void CMyVlcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_path);
	
}

BEGIN_MESSAGE_MAP(CMyVlcDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CMyVlcDlg::OnBnClickedButton1)
	ON_MESSAGE(WM_UPDATE,&CMyVlcDlg::OnUpdateStatic)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyVlcDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyVlcDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMyVlcDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CMyVlcDlg 消息处理程序

BOOL CMyVlcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyVlcDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMyVlcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CMyVlcDlg::OnBnClickedButton1()
{
	VLCPlayer::NewVLC();
	UpdateData(TRUE);
	DWORD threadId;
	HANDLE hThread = CreateThread(NULL,0,CMyVlcDlg::ThreadFunc,this,CREATE_SUSPENDED,&threadId);
	ResumeThread(hThread);

	UpdateData(FALSE);
}

DWORD CMyVlcDlg::ThreadFunc( void* params )
{



	CMyVlcDlg *Cwnd = (CMyVlcDlg*)params;
	HWND Hwnd = ::GetDlgItem(Cwnd->m_hWnd,IDC_STATIC);

	VLCPlayer *inst = VLCPlayer::NewVLC();
	USES_CONVERSION;
	string s(W2A(Cwnd->m_path));
	inst->Play(s,Hwnd);

	return 0;
	//-----------------------------------------------------------

	
	CMyVlcDlg *obj = (CMyVlcDlg*)params;
	//::SetWindowText(::GetDlgItem(obj->m_hWnd,IDC_EDIT2),_T("ssssssss"));

	HWND vHwnd = ::GetDlgItem(obj->m_hWnd,IDC_STATIC);

	libvlc_instance_t *     vlc_ins    = NULL;
	libvlc_media_player_t * vlc_player = NULL;
	libvlc_media_t *        vlc_media  = NULL;

	const char * vlc_args[] = 
	{
		"-I",
		"dummy",
		"--ignore-config",
		"--extraintf=logger",
		"--verbose=2", 
	};  

	// 创建一个VLC实例
	vlc_ins = libvlc_new(sizeof(vlc_args)/sizeof(vlc_args[0]), vlc_args);
	if(vlc_ins != NULL)
	{
		// 创建一个VLC播放器
		vlc_player = libvlc_media_player_new(vlc_ins);
		if(vlc_player != NULL)
		{
			USES_CONVERSION;
			string s(W2A(obj->m_path));
			const char* cstr = s.c_str(); 

			// 通过文件路径创建一个媒体实例,这里是我的测试文件
			vlc_media = libvlc_media_new_path(vlc_ins,cstr);
			if(vlc_media != NULL)
			{
				// 解析媒体实例
				libvlc_media_parse(vlc_media);
				// 获取媒体文件的播放长度,  返回 ms
				libvlc_time_t duration = libvlc_media_get_duration(vlc_media);

				// 此处是获取媒体包含多个的视频和音频轨以及其他类型的轨道信息
				libvlc_media_track_info_t *media_tracks = NULL;
				int trackCount = libvlc_media_get_tracks_info(vlc_media, &media_tracks);
				// 这里是释放内存，但我测试的时候会有问题，还没仔细研究是为何
				// free(media_tracks);  // crash?

				// 把打开的媒体文件设置给播放器
				libvlc_media_player_set_media(vlc_player, vlc_media);

				// 因为是windows系统，所以需要设置一个HWND给播放器作为窗口,这里就直接使用桌面窗口,这里仅是测试
				//libvlc_media_player_set_hwnd(vlc_player, ::GetDesktopWindow());
				libvlc_media_player_set_hwnd(vlc_player, vHwnd);
				// 开始播放视频
				libvlc_media_player_play(vlc_player);

				// 这里仅是为了打印一些信息出来,20秒后退出
				time_t last_time = time(NULL);
				while((time(NULL) < (last_time + 20)))
				{
					Sleep(10);
					// 获取当前播放位置
					libvlc_time_t play_time = libvlc_media_player_get_time(vlc_player);
					printf("playing time : %lld ms\r", (__int64)(play_time));

					// 获取媒体的状态
					// libvlc_state_t media_state = libvlc_media_get_state(vlc_media);
					// printf("\nmedia state : %d\n", (int)(media_state));
				}
				// 停止
				libvlc_media_player_stop(vlc_player);
				// 释放
				libvlc_media_release(vlc_media);
			}
			// 释放
			libvlc_media_player_release(vlc_player);
		}
		// 释放
		libvlc_release(vlc_ins);
	}
	return 0;
}

LRESULT CMyVlcDlg::OnUpdateStatic( WPARAM wParam, LPARAM lParam )
{
	if (wParam == 0)
		GetDlgItem(IDC_EDIT2)->SetWindowText(_T("sdfsfsdfsdf"));


	return 0;
}


//--------------------------------------------------------------

VLCPlayer *VLCPlayer::s_Instance = NULL;

VLCPlayer * VLCPlayer::NewVLC()
{
	if (s_Instance == NULL)
	{
		CRITICAL_SECTION cs;
		InitializeCriticalSection(&cs);
		EnterCriticalSection(&cs);
		if (s_Instance == NULL)
			s_Instance = new VLCPlayer();
		LeaveCriticalSection(&cs);
		DeleteCriticalSection(&cs);
	}
	return s_Instance;
}

const char * vlc_args[] = 
{
	"-I",
	"dummy",
	"--ignore-config",
	"--extraintf=logger",
	"--verbose=2", 
}; 

VLCPlayer::VLCPlayer()
{
	vlc_ins    = NULL;
	vlc_player = NULL;
	vlc_media  = NULL;
	// 创建一个VLC实例
	vlc_ins = libvlc_new(sizeof(vlc_args)/sizeof(vlc_args[0]), vlc_args);
	if (vlc_ins != NULL)
		vlc_player = libvlc_media_player_new(vlc_ins);


}

VLCPlayer::~VLCPlayer()
{
	if (vlc_ins != NULL)
	{
		libvlc_release(vlc_ins);
		vlc_ins = NULL;
	}
	if (vlc_player != NULL)
	{
		if (libvlc_media_player_is_playing(vlc_player))
			libvlc_media_player_stop(vlc_player);
		libvlc_media_player_release(vlc_player);
		vlc_player = NULL;
	}
	if (vlc_media  != NULL)
	{
		libvlc_media_release(vlc_media);
		vlc_media = NULL;
	}
}


void VLCPlayer::Play(string fileName,HANDLE hWnd)
{
	Stop();
	vlc_media = libvlc_media_new_path(vlc_ins,fileName.c_str());
	if(vlc_media != NULL)
	{
		// 解析媒体实例
		libvlc_media_parse(vlc_media);
		// 把打开的媒体文件设置给播放器
		libvlc_media_player_set_media(vlc_player, vlc_media);
		libvlc_media_player_set_hwnd(vlc_player, hWnd);
		libvlc_media_player_play(vlc_player);
	}
}

void VLCPlayer::Pause()
{
	if (vlc_player !=NULL)
		libvlc_media_player_pause(vlc_player);
}

void VLCPlayer::Resume()
{
	if (vlc_player !=NULL)
		libvlc_media_player_set_pause ( vlc_player,0);
}

void VLCPlayer::Stop()
{
	if (vlc_player != NULL)
	{
		if (libvlc_media_player_is_playing(vlc_player))
			libvlc_media_player_stop(vlc_player);
	}
	if (vlc_media != NULL)
	{
		libvlc_media_release(vlc_media);
		vlc_media = NULL;
	}
}
//ms
__int64 VLCPlayer::GetVideoLen()
{

	__int64 duration = 0;
// 	if (vlc_media != NULL)
// 	{
// 		duration = (__int64)libvlc_media_get_duration(vlc_media);
// 	}
	return duration / 1000;
}

void CMyVlcDlg::OnBnClickedButton2()
{
	VLCPlayer::NewVLC()->Pause();
}

void CMyVlcDlg::OnBnClickedButton3()
{
	VLCPlayer::NewVLC()->Resume();
}

void CMyVlcDlg::OnBnClickedButton4()
{
	VLCPlayer::NewVLC()->Stop();
}
