#pragma once
#include "afxwin.h"
#include "afxbutton.h"
#include "afxcmn.h"

// CLangue dialog

class CLangue : public CDialogEx
{
	DECLARE_DYNAMIC(CLangue)

public:
	CLangue(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLangue();

// Dialog Data
	enum { IDD = IDD_Langue };
	void SetOptions();
	void RefreshList();
	bool contains(CString mystring,CString arg);
	HICON m_add;
	HICON m_del;
	HICON m_up;
	HICON m_app;
	HICON m_delA;
	bool pasvide();
	CRect rc;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	public:
	virtual BOOL OnInitDialog();
	CListCtrl LanguesList;
	CString LangueId;
	CEdit LangueNom;
	CEdit Lrechercher;
	CComboBox Villages;
	CButton up;
	CButton del;
	CButton del2;
	CButton delA;
	CButton Modifier;
	CButton CAdd;
	CButton CAdd2;
	afx_msg void OnBnClickedLangueAjout();
	afx_msg void OnEnChangeRechercher();
	afx_msg void OnEnChangeLangueNom();
	afx_msg void OnCbnSelchangeV();
	afx_msg void OnBnClickedLangueSupp();
	afx_msg void OnBnClickedApp();
	afx_msg void OnBnClickedLanguesUpda();
	afx_msg void OnBnClickedLangueAjout2();
	afx_msg void OnBnClickedLangueSupp2();
};
