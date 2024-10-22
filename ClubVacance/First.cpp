// First.cpp : implementation file
//

#include "stdafx.h"
#include "ClubVacance.h"
#include "First.h"
#include "afxdialogex.h"


// CFirst dialog

IMPLEMENT_DYNAMIC(CFirst, CDialogEx)

CFirst::CFirst(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFirst::IDD, pParent)
{
	Create(IDD_First, pParent);
}

CFirst::~CFirst()
{
}

void CFirst::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFirst, CDialogEx)
END_MESSAGE_MAP()


// CFirst message handlers
