#pragma once
#include "First.h"

// CHome dialog

class CHome : public CDialogEx
{
	DECLARE_DYNAMIC(CHome)

public:
	CHome(CWnd* pParent = NULL);   // standard constructor
	virtual ~CHome();

// Dialog Data
	enum { IDD = IDD_HOME };
	HICON m_left;
	HICON m_right;	
	CRect rc;
	CFirst* first;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CButton left;
	CButton right;
	virtual BOOL OnInitDialog();
	afx_msg void OnStnClickedSlides();
};
