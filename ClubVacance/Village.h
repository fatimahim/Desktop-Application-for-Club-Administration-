#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// CVillage dialog

class CVillage : public CDialogEx
{
	DECLARE_DYNAMIC(CVillage)

public:
	CVillage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVillage();

// Dialog Data
	enum { IDD = IDD_VillageView };
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
	CListCtrl VillagesList;
	CString VillageId;
	CEdit VillageNom;
	CEdit LangueNom;
	CEdit Vrechercher;
	CComboBox PAYS;
	CButton up;
	CButton del;
	CButton delA;
	CButton Modifier;
	CButton CAdd;
	afx_msg void OnBnClickedVillagesAjout();
	afx_msg void OnEnChangeRechercher();
	afx_msg void OnEnChangeVillageNom();
	afx_msg void OnEnChangeLangueNom();
	afx_msg void OnBnClickedVillageSupp();
	afx_msg void OnBnClickedApp();
	afx_msg void OnBnClickedVillagesUpda();
};
