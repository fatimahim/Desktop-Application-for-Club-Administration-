#pragma once
#include "afxwin.h"
#include "afxbutton.h"
#include "afxcmn.h"
// CActivities dialog

class CActivities : public CDialogEx
{
	DECLARE_DYNAMIC(CActivities)

public:
	CActivities(CWnd* pParent = NULL);   // standard constructor
	virtual ~CActivities();

// Dialog Data
	enum { IDD = IDD_Activities };
	bool contains(CString mystring,CString arg);
	void SetOptions();
	void RefreshList();
	CRect rc;
	HICON m_add;
	HICON m_del;
	HICON m_up;
	HICON m_app;
	HICON m_delA;
	bool pasvide();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl ActivitiesList;
	CString ActivitieId;
	CEdit ActivitieNom;
	CEdit Arechercher;
	CComboBox Villages;
	CComboBox Gratuit;
	CComboBox Gratuit2;
	CButton up;
	CButton del;
	CButton delA;
	CButton Modifier;
	CButton CAdd;
	CButton CAdd2;
	afx_msg void OnBnClickedActivitieAjout();
	afx_msg void OnEnChangeRechercher();
	afx_msg void OnEnChangeActivitieNom();
	afx_msg void OnCbnSelchangeGratuit();
	afx_msg void OnBnClickedActivitieSupp();
	afx_msg void OnBnClickedActivitiesUpda();
	afx_msg void OnBnClickedApp1();
	afx_msg void OnBnClickedActivitieAjout2();
};
