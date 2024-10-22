#pragma once


// Chome dialog

class Chome : public CDialogEx
{
	DECLARE_DYNAMIC(Chome)

public:
	Chome(CWnd* pParent = NULL);   // standard constructor
	virtual ~Chome();

// Dialog Data
	enum { IDD = IDD_HOME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
