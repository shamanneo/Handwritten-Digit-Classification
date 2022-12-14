#include "pch.h"
#include "Resource.h"
#include "MainApp.h"

static CMainApp *g_pMainApp = nullptr ; 

CMainApp::CMainApp()
{
    // Initialize GDI+.
    Gdiplus::GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartUpInput, NULL) ;
}

CMainApp::~CMainApp()
{
    Gdiplus::GdiplusShutdown(m_gdiplusToken) ;
}

int CMainApp::Run(HINSTANCE hInstance, int nCmdShow)
{
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MNIST)) ;
    MSG msg ;

    m_MainWnd.Create(NULL, NULL, _T("MNIST"), WS_OVERLAPPEDWINDOW, 0) ; 
    m_MainWnd.ShowWindow(nCmdShow) ; 
    m_MainWnd.UpdateWindow() ; 

    while(::GetMessage(&msg, nullptr, 0, 0)) // main message loop.
    {
        if(PreTranslateMessage(msg))
        {
            continue ; 
        }
        if(!::TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            ::TranslateMessage(&msg) ;
            ::DispatchMessage(&msg) ;
        }
    }
    return (int) msg.wParam ; 
}

//      static 

CMainApp &CMainApp::GetInstance() 
{
    if(g_pMainApp == nullptr)
    {
        g_pMainApp = new CMainApp ; 
    }
    return *g_pMainApp ; 
}

void CMainApp::Release()
{
    if(g_pMainApp != nullptr)
    {
        delete g_pMainApp ; 
        g_pMainApp = nullptr ; 
    }
}

bool CMainApp::PreTranslateMessage(MSG &msg) 
{
    if(m_MainWnd.IsDialogMessage(&msg)) 
    {
        return true ;
    }
    return false ;
}
