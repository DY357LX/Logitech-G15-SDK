
// LCDDemoDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CLCDDemoDlg dialog
class CLCDDemoDlg : public CDialogEx
{
// Construction
public:
	CLCDDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_LCDDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    CEdit m_initName;
    afx_msg void OnClickedButtonInit();
    CEdit m_initResult;
    afx_msg void OnClickedButtonIsconnected();
    CEdit m_isConnectedResult;
    afx_msg void OnBnClickedButtonShutdown();
    CButton m_checkboxInitBW;
    CButton m_checkboxInitQVGA;
    CButton m_checkIsConnectedBW;
    CButton m_checkIsConnectedQVGA;
    CButton m_checkButton0;
    CButton m_checkButton1;
    CButton m_checkButton2;
    CButton m_checkButton3;
    CButton m_checkButtonUp;
    CButton m_checkButtonLeft;
    CButton m_checkButtonOK;
    CButton m_checkButtonRight;
    CButton m_checkButtonDown;
    CButton m_checkButtonMenu;
    CButton m_checkButtonCancel;
    afx_msg void OnBnClickedButtonSetText();
    CEdit m_monoText0;
    CEdit m_monoText1;
    CEdit m_monoText2;
    CEdit m_monoText3;
    CEdit m_colorTextTitle;
    CEdit m_colorText0;
    CEdit m_colorText1;
    CEdit m_colorText2;
    CEdit m_colorText3;
    CEdit m_colorText4;
    CEdit m_colorText5;
    CEdit m_colorText6;
    CEdit m_colorText7;
    afx_msg void OnBnClickedCancel();
    CEdit m_red;
    CEdit m_green;
    CEdit m_blue;
    afx_msg void OnBnClickedButtonRandomBackground();
    afx_msg void OnBnClickedButtonBackgroundFromImage2();
};
