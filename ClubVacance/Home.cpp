// Home.cpp : implementation file
//

#include "stdafx.h"
#include "ClubVacance.h"
#include "Home.h"
#include "afxdialogex.h"


// CHome dialog

IMPLEMENT_DYNAMIC(CHome, CDialogEx)

CHome::CHome(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHome::IDD, pParent)
{
	/*m_left = AfxGetApp()->LoadIcon(IDI_ICON23);
	m_right	= AfxGetApp()->LoadIcon(IDI_ICON24);*/
	Create(IDD_HOME, pParent);
}

CHome::~CHome()
{
}

void CHome::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LEFT, left);
	DDX_Control(pDX, IDC_RIGHT, right);
}


BEGIN_MESSAGE_MAP(CHome, CDialogEx)
	ON_STN_CLICKED(IDC_SLIDES, &CHome::OnStnClickedSlides)
END_MESSAGE_MAP()


// CHome message handlers
BOOL CHome::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GetDlgItem(IDC_SLIDES)->GetWindowRect(rc);
	ScreenToClient(&rc);
	first = new CFirst(this);
	first->MoveWindow(rc);

	left.SetIcon(m_left);
	right.SetIcon(m_right);

	return TRUE;
}


void CHome::OnStnClickedSlides()
{
	// TODO: Add your control notification handler code here
}
