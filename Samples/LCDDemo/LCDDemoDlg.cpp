
// LCDDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LCDDemo.h"
#include "LCDDemoDlg.h"
#include "afxdialogex.h"

TCHAR colorImageFileName[] = _T("G710Device.tiff");
TCHAR monoImageFileName[] = _T("LogiLogoMonoInverted.bmp");

#define USE_LOGITECH_DLL_ONLY

#ifndef USE_LOGITECH_DLL_ONLY
#pragma comment(lib, "LogitechLcd.lib")
#include "LogitechLcd.h"

#else
#define LOGI_LCD_TYPE_MONO    (0x00000001)
#define LOGI_LCD_TYPE_COLOR   (0x00000002)

#define LOGI_LCD_MONO_BUTTON_0 (0x00000001)
#define LOGI_LCD_MONO_BUTTON_1 (0x00000002)
#define LOGI_LCD_MONO_BUTTON_2 (0x00000004)
#define LOGI_LCD_MONO_BUTTON_3 (0x00000008)

#define LOGI_LCD_COLOR_BUTTON_LEFT   (0x00000100)
#define LOGI_LCD_COLOR_BUTTON_RIGHT  (0x00000200)
#define LOGI_LCD_COLOR_BUTTON_OK     (0x00000400)
#define LOGI_LCD_COLOR_BUTTON_CANCEL (0x00000800)
#define LOGI_LCD_COLOR_BUTTON_UP     (0x00001000)
#define LOGI_LCD_COLOR_BUTTON_DOWN   (0x00002000)
#define LOGI_LCD_COLOR_BUTTON_MENU   (0x00004000)

const int LOGI_LCD_MONO_WIDTH = 160;
const int LOGI_LCD_MONO_HEIGHT = 43;

const int LOGI_LCD_COLOR_WIDTH = 320;
const int LOGI_LCD_COLOR_HEIGHT = 240;

typedef bool (* LPFNDLLINIT)(wchar_t*, int );
typedef bool (* LPFNDLLISCONNECTED)(int);
typedef bool (* LPFNDLLISBUTTONPRESSED)(int);
typedef void (* LPFNDLLUPDATE)();
typedef void (* LPFNDLLSHUTDOWN)();
typedef bool (* LPFNDLLMONOSETBACKGROUND)(byte*);
typedef bool (* LPFNDLLMONOSETTEXT)(int, wchar_t*);
typedef bool (* LPFNDLLCCOLORSETBACKGROUND)(byte*);
typedef bool (* LPFNDLLCOLORSETTITLE)(wchar_t*, int, int, int);
typedef bool (* LPFNDLLCOLORSETTEXT)(int, wchar_t*, int, int, int);


LPFNDLLINIT LogiLcdInit = NULL;
LPFNDLLISCONNECTED LogiLcdIsConnected = NULL;
LPFNDLLISBUTTONPRESSED LogiLcdIsButtonPressed = NULL;
LPFNDLLUPDATE LogiLcdUpdate = NULL;
LPFNDLLSHUTDOWN LogiLcdShutdown = NULL;
LPFNDLLMONOSETBACKGROUND LogiLcdMonoSetBackground = NULL;
LPFNDLLMONOSETTEXT LogiLcdMonoSetText = NULL;
LPFNDLLCCOLORSETBACKGROUND LogiLcdColorSetBackground = NULL;
LPFNDLLCOLORSETTITLE LogiLcdColorSetTitle = NULL;
LPFNDLLCOLORSETTEXT LogiLcdColorSetText = NULL;

#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

ULONG_PTR g_gdiplusToken; 

// CLCDDemoDlg dialog




CLCDDemoDlg::CLCDDemoDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CLCDDemoDlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLCDDemoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_INIT_NAME, m_initName);
    DDX_Control(pDX, IDC_EDIT_INIT_RESULT, m_initResult);
    DDX_Control(pDX, IDC_EDIT_ISCONNECTED_RESULT, m_isConnectedResult);
    DDX_Control(pDX, IDC_CHECK_INIT_BW, m_checkboxInitBW);
    DDX_Control(pDX, IDC_CHECK_INIT_QVGA, m_checkboxInitQVGA);
    DDX_Control(pDX, IDC_CHECK_IS_CONNECTED_BW, m_checkIsConnectedBW);
    DDX_Control(pDX, IDC_CHECK_ISCONNECTED_QVGA, m_checkIsConnectedQVGA);
    DDX_Control(pDX, IDC_CHECK_IS_PRESSED_0, m_checkButton0);
    DDX_Control(pDX, IDC_CHECK_IS_PRESSED_1, m_checkButton1);
    DDX_Control(pDX, IDC_CHECK_IS_PRESSED_2, m_checkButton2);
    DDX_Control(pDX, IDC_CHECK_IS_PRESSED_3, m_checkButton3);
    DDX_Control(pDX, IDC_CHECK_IS_PRESSED_UP, m_checkButtonUp);
    DDX_Control(pDX, IDC_CHECK_IS_PRESSED_LEFT, m_checkButtonLeft);
    DDX_Control(pDX, IDC_CHECK_IS_PRESSED_OK, m_checkButtonOK);
    DDX_Control(pDX, IDC_CHECK_IS_PRESSED_RIGHT, m_checkButtonRight);
    DDX_Control(pDX, IDC_CHECK_IS_PRESSED_DOWN, m_checkButtonDown);
    DDX_Control(pDX, IDC_CHECK_IS_PRESSED_MENU, m_checkButtonMenu);
    DDX_Control(pDX, IDC_CHECK_IS_PRESSED_CANCEL, m_checkButtonCancel);
    DDX_Control(pDX, IDC_EDIT_MONO_LINE_0, m_monoText0);
    DDX_Control(pDX, IDC_EDIT_MONO_LINE_1, m_monoText1);
    DDX_Control(pDX, IDC_EDIT_MONO_LINE_2, m_monoText2);
    DDX_Control(pDX, IDC_EDIT_MONO_LINE_3, m_monoText3);
    DDX_Control(pDX, IDC_EDIT_COLOR_TITLE, m_colorTextTitle);
    DDX_Control(pDX, IDC_EDIT_COLOR_LINE_0, m_colorText0);
    DDX_Control(pDX, IDC_EDIT_COLOR_LINE_1, m_colorText1);
    DDX_Control(pDX, IDC_EDIT_COLOR_LINE_2, m_colorText2);
    DDX_Control(pDX, IDC_EDIT_COLOR_LINE_3, m_colorText3);
    DDX_Control(pDX, IDC_EDIT_COLOR_LINE_4, m_colorText4);
    DDX_Control(pDX, IDC_EDIT_COLOR_LINE_5, m_colorText5);
    DDX_Control(pDX, IDC_EDIT_COLOR_LINE_6, m_colorText6);
    DDX_Control(pDX, IDC_EDIT_COLOR_LINE_7, m_colorText7);
    DDX_Control(pDX, IDC_EDIT1, m_red);
    DDX_Control(pDX, IDC_EDIT13, m_green);
    DDX_Control(pDX, IDC_EDIT14, m_blue);
}

BEGIN_MESSAGE_MAP(CLCDDemoDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_TIMER()
    ON_BN_CLICKED(IDC_BUTTON_INIT, &CLCDDemoDlg::OnClickedButtonInit)
    ON_BN_CLICKED(IDC_BUTTON_ISCONNECTED, &CLCDDemoDlg::OnClickedButtonIsconnected)
    ON_BN_CLICKED(IDC_BUTTON_SHUTDOWN, &CLCDDemoDlg::OnBnClickedButtonShutdown)
    ON_BN_CLICKED(IDC_BUTTON_SET_TEXT, &CLCDDemoDlg::OnBnClickedButtonSetText)
    ON_BN_CLICKED(IDCANCEL, &CLCDDemoDlg::OnBnClickedCancel)
    ON_BN_CLICKED(IDC_BUTTON_RANDOM_BACKGROUND, &CLCDDemoDlg::OnBnClickedButtonRandomBackground)
    ON_BN_CLICKED(IDC_BUTTON_BACKGROUND_FROM_IMAGE2, &CLCDDemoDlg::OnBnClickedButtonBackgroundFromImage2)
END_MESSAGE_MAP()


// CLCDDemoDlg message handlers

BOOL CLCDDemoDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);			// Set big icon
    SetIcon(m_hIcon, FALSE);		// Set small icon

    // TODO: Add extra initialization here
    m_initName.SetWindowTextW(L"LCDDemo");
    m_checkboxInitBW.SetCheck(BST_CHECKED);
    m_checkboxInitQVGA.SetCheck(BST_CHECKED);
    m_checkIsConnectedBW.SetCheck(BST_CHECKED);
    m_checkIsConnectedQVGA.SetCheck(BST_CHECKED);
    m_red.SetWindowTextW(L"255");
    m_green.SetWindowTextW(L"255");
    m_blue.SetWindowTextW(L"255");

    // Start Gdiplus 
    Gdiplus::GdiplusStartupInput gdiplusStartupInput; 
    Gdiplus::GdiplusStartup(&g_gdiplusToken, &gdiplusStartupInput, NULL); 

	HINSTANCE logiDllHandle = LoadLibrary(L"LogitechLcd.dll");
    if (logiDllHandle != NULL)
    {
        LogiLcdInit = (LPFNDLLINIT)GetProcAddress(logiDllHandle, "LogiLcdInit");
        LogiLcdIsConnected = (LPFNDLLISCONNECTED)GetProcAddress(logiDllHandle, "LogiLcdIsConnected");
        LogiLcdIsButtonPressed = (LPFNDLLISBUTTONPRESSED)GetProcAddress(logiDllHandle, "LogiLcdIsButtonPressed");
        LogiLcdUpdate = (LPFNDLLUPDATE)GetProcAddress(logiDllHandle, "LogiLcdUpdate");
        LogiLcdShutdown = (LPFNDLLSHUTDOWN)GetProcAddress(logiDllHandle, "LogiLcdShutdown");
        LogiLcdMonoSetBackground = (LPFNDLLMONOSETBACKGROUND)GetProcAddress(logiDllHandle, "LogiLcdMonoSetBackground");
        LogiLcdMonoSetText = (LPFNDLLMONOSETTEXT)GetProcAddress(logiDllHandle, "LogiLcdMonoSetText");
        LogiLcdColorSetBackground = (LPFNDLLCCOLORSETBACKGROUND)GetProcAddress(logiDllHandle, "LogiLcdColorSetBackground");
        LogiLcdColorSetTitle = (LPFNDLLCOLORSETTITLE)GetProcAddress(logiDllHandle, "LogiLcdColorSetTitle");
        LogiLcdColorSetText = (LPFNDLLCOLORSETTEXT)GetProcAddress(logiDllHandle, "LogiLcdColorSetText");

    }

    return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLCDDemoDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLCDDemoDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}



void CLCDDemoDlg::OnTimer(UINT_PTR nIDEvent)
{

    LogiLcdUpdate();

    if (LogiLcdIsButtonPressed(LOGI_LCD_MONO_BUTTON_0))
        m_checkButton0.SetCheck(BST_CHECKED);
    else
        m_checkButton0.SetCheck(BST_UNCHECKED);

    if (LogiLcdIsButtonPressed(LOGI_LCD_MONO_BUTTON_1))
        m_checkButton1.SetCheck(BST_CHECKED);
    else
        m_checkButton1.SetCheck(BST_UNCHECKED);

    if (LogiLcdIsButtonPressed(LOGI_LCD_MONO_BUTTON_2))
        m_checkButton2.SetCheck(BST_CHECKED);
    else
        m_checkButton2.SetCheck(BST_UNCHECKED);

    if (LogiLcdIsButtonPressed(LOGI_LCD_MONO_BUTTON_3))
        m_checkButton3.SetCheck(BST_CHECKED);
    else
        m_checkButton3.SetCheck(BST_UNCHECKED);

    if (LogiLcdIsButtonPressed(LOGI_LCD_COLOR_BUTTON_UP))
        m_checkButtonUp.SetCheck(BST_CHECKED);
    else
        m_checkButtonUp.SetCheck(BST_UNCHECKED);

    if (LogiLcdIsButtonPressed(LOGI_LCD_COLOR_BUTTON_LEFT))
        m_checkButtonLeft.SetCheck(BST_CHECKED);
    else
        m_checkButtonLeft.SetCheck(BST_UNCHECKED);

    if (LogiLcdIsButtonPressed(LOGI_LCD_COLOR_BUTTON_OK))
        m_checkButtonOK.SetCheck(BST_CHECKED);
    else
        m_checkButtonOK.SetCheck(BST_UNCHECKED);

    if (LogiLcdIsButtonPressed(LOGI_LCD_COLOR_BUTTON_RIGHT))
        m_checkButtonRight.SetCheck(BST_CHECKED);
    else
        m_checkButtonRight.SetCheck(BST_UNCHECKED);

    if (LogiLcdIsButtonPressed(LOGI_LCD_COLOR_BUTTON_DOWN))
        m_checkButtonDown.SetCheck(BST_CHECKED);
    else
        m_checkButtonDown.SetCheck(BST_UNCHECKED);

    if (LogiLcdIsButtonPressed(LOGI_LCD_COLOR_BUTTON_MENU))
        m_checkButtonMenu.SetCheck(BST_CHECKED);
    else
        m_checkButtonMenu.SetCheck(BST_UNCHECKED);

    if (LogiLcdIsButtonPressed(LOGI_LCD_COLOR_BUTTON_CANCEL))
        m_checkButtonCancel.SetCheck(BST_CHECKED);
    else
        m_checkButtonCancel.SetCheck(BST_UNCHECKED);


    CDialogEx::OnTimer(nIDEvent);
}


void CLCDDemoDlg::OnClickedButtonInit()
{
    SetTimer(1, 30, NULL);

    wchar_t text[MAX_PATH];
    m_initName.GetWindowText(text, MAX_PATH);

    int type = 0;

    if (BST_CHECKED == m_checkboxInitBW.GetCheck())
    {
        type = LOGI_LCD_TYPE_MONO;
    }
    if (BST_CHECKED == m_checkboxInitQVGA.GetCheck())
    {
        type = type | LOGI_LCD_TYPE_COLOR;
    }

    BOOL ret = FALSE;

    ret = LogiLcdInit(text, type);

    m_initResult.SetWindowText((ret == TRUE) ? L"TRUE" : L"FALSE");
}


void CLCDDemoDlg::OnClickedButtonIsconnected()
{
    int type = 0;

    if (BST_CHECKED == m_checkIsConnectedBW.GetCheck())
    {
        type = LOGI_LCD_TYPE_MONO;
    }
    if (BST_CHECKED == m_checkIsConnectedQVGA.GetCheck())
    {
        type = type | LOGI_LCD_TYPE_COLOR;
    }

    bool ret = LogiLcdIsConnected(type);


    m_isConnectedResult.SetWindowText((ret) ? L"TRUE" : L"FALSE");
}


void CLCDDemoDlg::OnBnClickedButtonShutdown()
{
    LogiLcdShutdown();
    m_initResult.SetWindowTextW(L"");
}


void CLCDDemoDlg::OnBnClickedButtonSetText()
{
    wchar_t text[MAX_PATH];

    m_monoText0.GetWindowText(text, MAX_PATH);
    LogiLcdMonoSetText(0, text);
    m_monoText1.GetWindowText(text, MAX_PATH);
    LogiLcdMonoSetText(1, text);
    m_monoText2.GetWindowText(text, MAX_PATH);
    LogiLcdMonoSetText(2, text);
    m_monoText3.GetWindowText(text, MAX_PATH);
    LogiLcdMonoSetText(3, text);

    wchar_t redText[MAX_PATH];
    m_red.GetWindowTextW(redText, MAX_PATH);
    wchar_t greenText[MAX_PATH];
    m_green.GetWindowTextW(greenText, MAX_PATH);
    wchar_t blueText[MAX_PATH];
    m_blue.GetWindowTextW(blueText, MAX_PATH);

    int red, green, blue = 0;

    if (wcscmp(L"", redText) == 0 || wcscmp(L"", greenText) == 0 || wcscmp(L"", blueText) == 0)
    {
        red = 255;
        green = 255;
        blue = 255;
    }
    else
    {
        red = _wtoi(redText);
        green = _wtoi(greenText);
        blue = _wtoi(blueText);
    }

    m_colorTextTitle.GetWindowText(text, MAX_PATH);
    LogiLcdColorSetTitle(text, red, green, blue);

    m_colorText0.GetWindowText(text, MAX_PATH);
    LogiLcdColorSetText(0, text, red, green, blue);
    m_colorText1.GetWindowText(text, MAX_PATH);
    LogiLcdColorSetText(1, text, red, green, blue);
    m_colorText2.GetWindowText(text, MAX_PATH);
    LogiLcdColorSetText(2, text, red, green, blue);
    m_colorText3.GetWindowText(text, MAX_PATH);
    LogiLcdColorSetText(3, text, red, green, blue);
    m_colorText4.GetWindowText(text, MAX_PATH);
    LogiLcdColorSetText(4, text, red, green, blue);
    m_colorText5.GetWindowText(text, MAX_PATH);
    LogiLcdColorSetText(5, text, red, green, blue);
    m_colorText6.GetWindowText(text, MAX_PATH);
    LogiLcdColorSetText(6, text, red, green, blue);
    m_colorText7.GetWindowText(text, MAX_PATH);
    LogiLcdColorSetText(7, text, red, green, blue);

}

BYTE pixels[LOGI_LCD_MONO_WIDTH * LOGI_LCD_MONO_HEIGHT];

void CLCDDemoDlg::OnBnClickedButtonRandomBackground()
{

    if (LogiLcdIsConnected(LOGI_LCD_TYPE_MONO))
    {
        for (int i = 0; i < (LOGI_LCD_MONO_WIDTH * LOGI_LCD_MONO_HEIGHT); i++)
        {
            pixels[i] = (BYTE)rand();
        }

		LogiLcdMonoSetBackground(pixels);

    }

    if (LogiLcdIsConnected(LOGI_LCD_TYPE_COLOR))
    {
        BYTE colorBitmap[LOGI_LCD_COLOR_WIDTH * LOGI_LCD_COLOR_HEIGHT * 4];

        for (int i = 0; i < (LOGI_LCD_COLOR_WIDTH * LOGI_LCD_COLOR_HEIGHT * 4); i++)
        {
            colorBitmap[i] = (BYTE)rand();
        }

        LogiLcdColorSetBackground(colorBitmap);

    }
}

bool SetColorBackgroundFromFile(TCHAR* fileName)
{
    HDC hdc = ::GetDC(NULL);

    // Load the image. Any of the following formats are supported: BMP, GIF, JPEG, PNG, TIFF, Exif, WMF, and EMF
    Gdiplus::Bitmap* image = Gdiplus::Bitmap::FromFile( fileName );

    if (NULL == image)
        return false;

    // Get the bitmap handle
    HBITMAP hBitmap = NULL;
    Gdiplus::Status status = image->GetHBITMAP(RGB(0,0,0), &hBitmap);
    if (status != Gdiplus::Ok)
        return false;

    BITMAPINFO bitmapInfo = {0};
    bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

    // Check what we got
    int ret = GetDIBits(hdc, hBitmap, 0,
        0,
        NULL,
        &bitmapInfo, DIB_RGB_COLORS);

    if (LOGI_LCD_COLOR_WIDTH != bitmapInfo.bmiHeader.biWidth || LOGI_LCD_COLOR_HEIGHT != bitmapInfo.bmiHeader.biHeight)
    {
        ::MessageBoxW(NULL, _T("Oooops. Make sure to use a 320 by 240 image for color background."), _T("LCDDemo"), MB_ICONEXCLAMATION);
        return false;
    }

    bitmapInfo.bmiHeader.biCompression = BI_RGB;
    bitmapInfo.bmiHeader.biHeight = -bitmapInfo.bmiHeader.biHeight; // this value needs to be inverted, or else image will show up upside/down

    BYTE byteBitmap[LOGI_LCD_COLOR_WIDTH * LOGI_LCD_COLOR_HEIGHT * 4]; // we have 32 bits per pixel, or 4 bytes

    // Gets the "bits" from the bitmap and copies them into a buffer 
    // which is pointed to by byteBitmap.
    ret = GetDIBits(hdc, hBitmap, 0,
        -bitmapInfo.bmiHeader.biHeight, // height here needs to be positive. Since we made it negative previously, let's reverse it again.
        &byteBitmap,
        (BITMAPINFO *)&bitmapInfo, DIB_RGB_COLORS);

    LogiLcdColorSetBackground(byteBitmap);

    // delete the image when done 
    if (image)
    {
        delete image;
        image = NULL;
    }

    return true;
}

bool SetMonoBackgroundFromFile(TCHAR* fileName)
{
    HDC hdc = ::GetDC(NULL);

    Gdiplus::Bitmap* imageMono = Gdiplus::Bitmap::FromFile( fileName );

    if (NULL == imageMono)
        return false;

    // Get the bitmap handle
    HBITMAP hBitmap = NULL;
    Gdiplus::Status status = imageMono->GetHBITMAP(RGB(0,0,0), &hBitmap);

    if (status != Gdiplus::Ok)
        return false;

    BITMAPINFO bitmapInfoMono = {0};
    bitmapInfoMono.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

    // Check what we got
    int ret = GetDIBits(hdc, hBitmap, 0,
        0,
        NULL,
        &bitmapInfoMono, DIB_RGB_COLORS);

    if (LOGI_LCD_MONO_WIDTH != bitmapInfoMono.bmiHeader.biWidth || LOGI_LCD_MONO_HEIGHT != bitmapInfoMono.bmiHeader.biHeight)
    {
        ::MessageBoxW(NULL, _T("Oooops. Make sure to use a 160 by 43 image for color background."), _T("LCDDemo"), MB_ICONEXCLAMATION);
        return false;;
    }

    bitmapInfoMono.bmiHeader.biCompression = BI_RGB;
    bitmapInfoMono.bmiHeader.biHeight = -bitmapInfoMono.bmiHeader.biHeight; // this value needs to be inverted, or else image will show up upside/down

    BYTE byteBitmapMono[LOGI_LCD_MONO_WIDTH * LOGI_LCD_MONO_HEIGHT * 4];

    // Gets the "bits" from the bitmap and copies them into a buffer 
    // which is pointed to by byteBitmapMono.
    ret = GetDIBits(hdc, hBitmap, 0,
        -bitmapInfoMono.bmiHeader.biHeight, // height here needs to be positive. Since we made it negative previously, let's reverse it again to make it positive.
        &byteBitmapMono,
        (BITMAPINFO *)&bitmapInfoMono, DIB_RGB_COLORS);

    BYTE byteBitmapMono8bpp[LOGI_LCD_MONO_WIDTH * LOGI_LCD_MONO_HEIGHT];

    // Transform 32bpp data into 8bpp. Let's just take the value of first of 4 bytes (Blue)
    for (int ii = 0; ii < (LOGI_LCD_MONO_WIDTH * LOGI_LCD_MONO_HEIGHT * 4); ii = ii + 4)
    {
        byteBitmapMono8bpp[ii / 4] = byteBitmapMono[ii];
    }

    LogiLcdMonoSetBackground(byteBitmapMono8bpp);

    // delete the image when done 
    if (imageMono)
    {
        delete imageMono;
        imageMono = NULL;
    }

    return true;
}

void CLCDDemoDlg::OnBnClickedButtonBackgroundFromImage2()
{
    SetColorBackgroundFromFile(colorImageFileName);

    SetMonoBackgroundFromFile(monoImageFileName);
}

void CLCDDemoDlg::OnBnClickedCancel()
{
	LogiLcdShutdown();

    // Shutdown Gdiplus 
    Gdiplus::GdiplusShutdown(g_gdiplusToken); 

    CDialogEx::OnCancel();
}
