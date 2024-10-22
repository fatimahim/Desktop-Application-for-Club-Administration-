#pragma once


// CFirst dialog

class CFirst : public CDialogEx
{
	DECLARE_DYNAMIC(CFirst)

public:
	CFirst(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFirst();

// Dialog Data
	enum { IDD = IDD_First };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
