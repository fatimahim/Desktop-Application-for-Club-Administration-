
// ClubVacanceDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "Pays.h"
#include "Home.h"
#include "Village.h"
#include "Activities.h"
#include "Langue.h"
#include "afxbutton.h"

// CClubVacanceDlg dialog
class CClubVacanceDlg : public CDialogEx
{
// Construction
public:
	CClubVacanceDlg(CWnd* pParent = NULL);	// standard constructor
	CRect rc;
// Dialog Data
	enum { IDD = IDD_CLUBVACANCE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CFont m_font;
	CFont m_font2;
	HICON m_home;	
	//HICON m_clientsIcon;
	HICON m_exit;
	HICON m_db;
	

	HICON m_info;
	CPays*		pay;
	CVillage* village;
	CActivities*		activitie;
	CLangue*	langue;
	CHome*	home;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

afx_msg void OnBnClickedMfcbutton1();
afx_msg void OnBnClickedMfcbutton4();
afx_msg void OnBnClickedMfcbutton3();
afx_msg void OnBnClickedMfcbutton2();
afx_msg void OnBnClickedAccueil();
afx_msg void OnBnClickedQuitter();
	CButton Exit;
	CButton accueil;
	CButton dbS;
	/*
	afx_msg void OnBnClickedAbout();
	*/
	CButton about;
	CMFCButton payB;
	CMFCButton villageB;
	CMFCButton langueB;
	CMFCButton activitieB;
	afx_msg void OnBnClickedBd();
	afx_msg void OnBnClickedAbout();
};
