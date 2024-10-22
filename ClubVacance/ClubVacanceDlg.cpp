
// ClubVacanceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClubVacance.h"
#include "ClubVacanceDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <afxdao.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;

CDaoDatabase db;
CDaoRecordset recset(&db);

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CClubVacanceDlg dialog




CClubVacanceDlg::CClubVacanceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClubVacanceDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_exit = AfxGetApp()->LoadIcon(IDI_ICON1);
	m_home = AfxGetApp()->LoadIcon(IDI_ICON2);
	m_db = AfxGetApp()->LoadIcon(IDI_ICON3);
	m_info = AfxGetApp()->LoadIcon(IDI_ICON13);

}

void CClubVacanceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
		DDX_Control(pDX, IDC_Quitter, Exit); 
	DDX_Control(pDX, IDC_ACCUEIL, accueil);
	DDX_Control(pDX, IDC_BD, dbS);
	DDX_Control(pDX, IDC_ABOUT, about);
	DDX_Control(pDX, IDC_MFCBUTTON1, payB); 
	DDX_Control(pDX, IDC_MFCBUTTON2, langueB);
	DDX_Control(pDX, IDC_MFCBUTTON3, activitieB);
	DDX_Control(pDX, IDC_MFCBUTTON4, villageB);

}

BEGIN_MESSAGE_MAP(CClubVacanceDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MFCBUTTON1, &CClubVacanceDlg::OnBnClickedMfcbutton1)
	ON_BN_CLICKED(IDC_MFCBUTTON4, &CClubVacanceDlg::OnBnClickedMfcbutton4)
	ON_BN_CLICKED(IDC_MFCBUTTON3, &CClubVacanceDlg::OnBnClickedMfcbutton3)
	ON_BN_CLICKED(IDC_MFCBUTTON2, &CClubVacanceDlg::OnBnClickedMfcbutton2)
	ON_BN_CLICKED(IDC_ACCUEIL, &CClubVacanceDlg::OnBnClickedAccueil)
	ON_BN_CLICKED(IDC_Quitter, &CClubVacanceDlg::OnBnClickedQuitter)
	ON_BN_CLICKED(IDC_BD, &CClubVacanceDlg::OnBnClickedBd)
	ON_BN_CLICKED(IDC_ABOUT, &CClubVacanceDlg::OnBnClickedAbout)
END_MESSAGE_MAP()


// CClubVacanceDlg message handlers

BOOL CClubVacanceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
		GetDlgItem(IDC_STATIC)->GetWindowRect(rc);
	ScreenToClient(&rc);
	home = new CHome(this);
	home->MoveWindow(rc);

	m_font.CreatePointFont(100, L"Work Sans SemiBold");
	m_font2.CreatePointFont(90, L"Work Sans SemiBold");

	Exit.SetFont(&m_font);
	accueil.SetFont(&m_font);
	dbS.SetFont(&m_font);
	about.SetFont(&m_font);
	payB.SetFont(&m_font2);
	villageB.SetFont(&m_font2);
	activitieB.SetFont(&m_font2);
	langueB.SetFont(&m_font2);
    Exit.SetIcon(m_exit);
	Exit.ModifyStyle( BS_ICON | BS_BITMAP ,0);
    Exit.ModifyStyle( 0 , BS_LEFT);
	accueil.SetIcon(m_home);
	accueil.ModifyStyle( BS_ICON | BS_BITMAP ,0);
    accueil.ModifyStyle( 0 , BS_TOP);
	dbS.SetIcon(m_db);
	dbS.ModifyStyle( BS_ICON | BS_BITMAP ,0);
    dbS.ModifyStyle( 0 , BS_TOP);
	about.SetIcon(m_info);
	about.ModifyStyle( BS_ICON | BS_BITMAP ,0);
    about.ModifyStyle( 0 , BS_TOP);
	/*
	about.SetIcon(m_info);*/

	pay		= NULL;
	village		= NULL;
	activitie		= NULL;
	langue	= NULL;
	//home		= NULL;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClubVacanceDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClubVacanceDlg::OnPaint()
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
HCURSOR CClubVacanceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CClubVacanceDlg::OnBnClickedMfcbutton1()
{
	// TODO: Add your control notification handler code here
	if(home != NULL){
		delete(home);
		home = NULL;
	}
	if(village != NULL){
		delete(village);
		village = NULL;
	}
	if(activitie != NULL){
		delete(activitie);
		activitie = NULL;
	}
	if(langue != NULL){
		delete(langue);
		langue = NULL;
	}
	if(pay == NULL){
		GetDlgItem(IDC_STATIC)->GetWindowRect(rc);
		ScreenToClient(&rc);
		pay = new CPays(this);
		pay->MoveWindow(rc);
	}
}


void CClubVacanceDlg::OnBnClickedMfcbutton4()
{
	// TODO: Add your control notification handler code here
		// TODO: Add your control notification handler code here
	if(home != NULL){
		delete(home);
		home = NULL;
	}
	if(pay != NULL){
		delete(pay);
		pay = NULL;
	}
	if(activitie != NULL){
		delete(activitie);
		activitie = NULL;
	}
	if(langue != NULL){
		delete(langue);
		langue = NULL;
	}
	if(village == NULL){
		GetDlgItem(IDC_STATIC)->GetWindowRect(rc);
		ScreenToClient(&rc);
		village = new CVillage(this);
		village->MoveWindow(rc);
	}
}


void CClubVacanceDlg::OnBnClickedMfcbutton3()
{
	// TODO: Add your control notification handler code here
		if(home != NULL){
		delete(home);
		home = NULL;
	}
	if(pay != NULL){
		delete(pay);
		pay = NULL;
	}
	
	if(village != NULL){
		delete(village);
		village = NULL;
	}
	if(langue != NULL){
		delete(langue);
		langue = NULL;
	}
	if(activitie == NULL){
		GetDlgItem(IDC_STATIC)->GetWindowRect(rc);
		ScreenToClient(&rc);
		activitie = new CActivities(this);
		activitie->MoveWindow(rc);
	}
}


void CClubVacanceDlg::OnBnClickedMfcbutton2()
{
	// TODO: Add your control notification handler code here
	if(home != NULL){
		delete(home);
		home = NULL;
	}
	if(pay != NULL){
		delete(pay);
		pay = NULL;
	}
	
	if(village != NULL){
		delete(village);
		village = NULL;
	}
	
	if(activitie != NULL){
		delete(activitie);
		activitie = NULL;
	}
	if(langue == NULL){
		GetDlgItem(IDC_STATIC)->GetWindowRect(rc);
		ScreenToClient(&rc);
		langue = new CLangue(this);
		langue->MoveWindow(rc);
	}
}


void CClubVacanceDlg::OnBnClickedAccueil()
{
	// TODO: Add your control notification handler code here
		if(langue != NULL){
		delete(langue);
		langue = NULL;
	}
	if(pay != NULL){
		delete(pay);
		pay = NULL;
	}
	
	if(village != NULL){
		delete(village);
		village = NULL;
	}
	
	if(activitie != NULL){
		delete(activitie);
		activitie = NULL;
	}
	if(home == NULL){
		GetDlgItem(IDC_STATIC)->GetWindowRect(rc);
		ScreenToClient(&rc);
		home = new CHome(this);
		home->MoveWindow(rc);
	}
}


void CClubVacanceDlg::OnBnClickedQuitter()
{
	// TODO: Add your control notification handler code here<
	OnOK();
}


void CClubVacanceDlg::OnBnClickedBd()
{
	// TODO: Add your control notification handler code here
	CString lpszFile =L"GestionVillageVacance.mdb";
	db.Create(lpszFile);
	//db.Open(lpszFile);	

	CString creation_table_continents=L"CREATE TABLE CONTINENTS(no_Con AUTOINCREMENT PRIMARY KEY,nomCon VARCHAR(100) UNIQUE ,codeCon VARCHAR(3) UNIQUE);";

	CString creation_table_pays=L"CREATE TABLE PAYS(no_P AUTOINCREMENT PRIMARY KEY,nomP VARCHAR(30) UNIQUE, codeP VARCHAR(3) , no_Con INTEGER,FOREIGN KEY (no_Con) REFERENCES CONTINENTS(no_Con) );";
	CString creation_table_villages=L"CREATE TABLE VILLAGES(no_V AUTOINCREMENT PRIMARY KEY,nomV VARCHAR(30) UNIQUE, codeV VARCHAR(3) ,no_P INTEGER,FOREIGN KEY (no_P) REFERENCES PAYS(no_P));";
	CString creation_table_activities=L"CREATE TABLE ACTIVITIES(no_A AUTOINCREMENT PRIMARY KEY,nomA VARCHAR(30) UNIQUE);";
	CString creation_table_langues=L"CREATE TABLE LANGUES(no_L AUTOINCREMENT PRIMARY KEY,nomL VARCHAR(30) UNIQUE);";
	CString creation_table_villages_activities = L"CREATE TABLE VILLAGES_ACTIVITIES(no_V INTEGER, no_A INTEGER, FOREIGN KEY (no_V) REFERENCES VILLAGES(no_V), FOREIGN KEY (no_A) REFERENCES ACTIVITIES(no_A),activitie_gratuit VARCHAR(3),PRIMARY KEY (no_V, no_A));";

// Nouvelle table pour lier VILLAGES et LANGUES
CString creation_table_villages_langues = L"CREATE TABLE VILLAGES_LANGUES(no_V INTEGER, no_L INTEGER, FOREIGN KEY (no_V) REFERENCES VILLAGES(no_V), FOREIGN KEY (no_L) REFERENCES LANGUES(no_L),PRIMARY KEY (no_V, no_L));";
	
	db.Execute(creation_table_continents);
	
	db.Execute(creation_table_pays);
	db.Execute(creation_table_villages);
	db.Execute(creation_table_activities);
	db.Execute(creation_table_langues);
	db.Execute(creation_table_villages_activities);
	db.Execute(creation_table_villages_langues);
	
	db.Close(); 
   
}


void CClubVacanceDlg::OnBnClickedAbout()
{
	// TODO: Add your control notification handler code here

CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}
