#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "afxbutton.h"
#include <vector>
// CPays dialog

class CPays : public CDialogEx
{
	DECLARE_DYNAMIC(CPays)

public:
	CPays(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPays();

// Dialog Data
	enum { IDD = IDD_PaysView };
	bool contains(CString mystring,CString arg);
	void SetOptions();
	void RefreshList();
	bool pasvide();
	HICON m_add;
	HICON m_del;
	HICON m_up;
	HICON m_app;
	HICON m_delA;
	CRect rc;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
	public:
	virtual BOOL OnInitDialog();
	CListCtrl PaysList;
	std::vector<CString> ConsList;
	CString PaysId;
	CString ConId;
	CEdit PaysNom;
	CEdit Prechercher;
	CComboBox Continent;
	CButton up;
	CButton up2;
	CButton del;
	CButton del2;
	CButton delA;
	CButton delA2;
	CButton Modifier;
	CButton CAdd;
	CButton CAdd2;
	afx_msg void OnBnClickedPaysAjout();
	afx_msg void OnEnChangeVillageNom();
	afx_msg void OnEnChangeRechercher();
	afx_msg void OnBnClickedPaySupp();
	afx_msg void OnEnChangePaysNom();
	afx_msg void OnCbnSelchangeCon();
	afx_msg void OnBnClickedApp();
	afx_msg void OnBnClickedPaysUpda();
	afx_msg void OnBnClickedPaysAjout2();
	afx_msg void OnEnChangeRechercher2();
	afx_msg void OnBnClickedContinentSupp();
	afx_msg void OnBnClickedApp2();
	afx_msg void OnBnClickedContinentsUpda();
	afx_msg void OnBnClickedPaysSupp();
	afx_msg void OnEnChangeContinentNom();
};
