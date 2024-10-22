// Activities.cpp : implementation file
//

#include "stdafx.h"
#include "ClubVacance.h"
#include "Activities.h"
#include "afxdialogex.h"
#include <afxdao.h>


// CActivities dialog

IMPLEMENT_DYNAMIC(CActivities, CDialogEx)

CActivities::CActivities(CWnd* pParent /*=NULL*/)
	: CDialogEx(CActivities::IDD, pParent)
{
	
	m_add = AfxGetApp()->LoadIcon(IDI_ICON6);
	m_del= AfxGetApp()->LoadIcon(IDI_ICON6);
	m_up= AfxGetApp()->LoadIcon(IDI_ICON17);
	m_delA= AfxGetApp()->LoadIcon(IDI_ICON16);
	Create(IDD_Activities, pParent);
}

CActivities::~CActivities()
{
}

void CActivities::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ACTIVITIES_LIST, ActivitiesList);
	DDX_Control(pDX, IDC_ACTIVITIE_NOM, ActivitieNom);
	DDX_Control(pDX, IDC_V, Villages);
	DDX_Control(pDX, IDC_GRATUIT, Gratuit);
	DDX_Control(pDX, IDC_NOMG, Gratuit2);
	DDX_Control(pDX, IDC_RECHERCHER, Arechercher);
	DDX_Control(pDX, IDC_ACTIVITIES_UPDA, up);
	DDX_Control(pDX, IDC_ACTIVITIE_AJOUT, CAdd);
	DDX_Control(pDX, IDC_ACTIVITIE_AJOUT2, CAdd2);
	DDX_Control(pDX, IDC_ACTIVITIE_SUPP, del);
	DDX_Control(pDX, IDC_ACTIVITIES_SUPP, delA);
}


BEGIN_MESSAGE_MAP(CActivities, CDialogEx)
	ON_BN_CLICKED(IDC_ACTIVITIE_AJOUT, &CActivities::OnBnClickedActivitieAjout)
	ON_EN_CHANGE(IDC_RECHERCHER, &CActivities::OnEnChangeRechercher)
	ON_EN_CHANGE(IDC_ACTIVITIE_NOM, &CActivities::OnEnChangeActivitieNom)
	ON_CBN_SELCHANGE(IDC_GRATUIT, &CActivities::OnCbnSelchangeGratuit)
	ON_BN_CLICKED(IDC_ACTIVITIE_SUPP, &CActivities::OnBnClickedActivitieSupp)
	ON_BN_CLICKED(IDC_ACTIVITIES_UPDA, &CActivities::OnBnClickedActivitiesUpda)
	ON_BN_CLICKED(IDC_APP1, &CActivities::OnBnClickedApp1)
	ON_BN_CLICKED(IDC_ACTIVITIE_AJOUT2, &CActivities::OnBnClickedActivitieAjout2)
END_MESSAGE_MAP()


// CActivities message handlers
BOOL CActivities::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ActivitiesList.InsertColumn(0,L"N°",LVCFMT_LEFT,30,-1);
	ActivitiesList.InsertColumn(1,L"Nom De Village",LVCFMT_LEFT,140,-1);
	ActivitiesList.InsertColumn(2,L"Nom d'activitie",LVCFMT_LEFT,140,-1);
	ActivitiesList.InsertColumn(3,L"Activité gratuite",LVCFMT_LEFT,140,-1);
	ListView_SetExtendedListViewStyle( ActivitiesList,LVS_EX_GRIDLINES);

	Arechercher.SetCueBanner(L"Rechercher");
	ActivitieNom.SetCueBanner(L"Nom D'activité");
	Villages.SetCueBanner(L"Villages");
	Gratuit.SetCueBanner(L"...");
	Gratuit2.SetCueBanner(L"...");
	RefreshList();
	ActivitieId = L"-1";

	//GetDlgItem(IDC_NOMV)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_NOMA)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_NOMG)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_APP1)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_ACTIVITIE_SUPP)->EnableWindow(FALSE);			
	GetDlgItem(IDC_ACTIVITIES_UPDA)->EnableWindow(FALSE);
	GetDlgItem(IDC_ACTIVITIE_AJOUT)->EnableWindow(FALSE);

	//GetDlgItem(IDC_NOMV)->EnableWindow(FALSE);
	GetDlgItem(IDC_NOMA)->EnableWindow(FALSE);
	GetDlgItem(IDC_NOMG)->EnableWindow(FALSE);
	/*GetDlgItem(8888)->GetWindowRect(rc);
	ScreenToClient(&rc);*/

	CAdd.SetIcon(m_add);
	CAdd2.SetIcon(m_add);
	del.SetIcon(m_del);
	//del2.SetIcon(m_del);
	delA.SetIcon(m_delA);
	//delA2.SetIcon(m_delA);
	//app.SetIcon(m_app);
	up.SetIcon(m_up);
	//up2.SetIcon(m_up);
	return TRUE;
}
void CActivities::RefreshList(){
	CDaoDatabase db;
	CDaoRecordset recset(&db);
	COleVariant var;  // Start Variables
	var.ChangeType(VT_BSTR, NULL);
	CString a_no_Activitie,A_nom,V_nom,agratuit; // End Variables
	ActivitiesList.DeleteAllItems(); // Clear List
	CString lpszFile=L"GestionVillageVacance.mdb";
	db.Open(lpszFile); // Open Clients.MDB

CString SqlCmd=L"SELECT VILLAGES_ACTIVITIES.no_V, VILLAGES_ACTIVITIES.activitie_gratuit, ACTIVITIES.nomA, VILLAGES.nomV FROM VILLAGES INNER JOIN (ACTIVITIES INNER JOIN VILLAGES_ACTIVITIES ON VILLAGES_ACTIVITIES.no_A = ACTIVITIES.no_A) ON VILLAGES_ACTIVITIES.no_V = VILLAGES.no_V order by VILLAGES_ACTIVITIES.no_A desc";
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCmd,NULL);
	
	while(!recset.IsEOF()) // Do until EOF
	{
		int i = 0;	
		recset.GetFieldValue(L"no_V",var);
		a_no_Activitie.Format(L"%d",(LPCWSTR)var.pbstrVal);
		ActivitiesList.InsertItem(i,a_no_Activitie,0);
		recset.GetFieldValue(L"nomV",var);
		V_nom = (LPCWSTR)var.pbstrVal;
		ActivitiesList.SetItemText(i,1,V_nom);	
		recset.GetFieldValue(L"nomA",var);		
		A_nom = (LPCWSTR)var.pbstrVal;
		ActivitiesList.SetItemText(i,2,A_nom);	
		recset.GetFieldValue(L"activitie_gratuit",var);		
		agratuit = (LPCWSTR)var.pbstrVal;
		ActivitiesList.SetItemText(i,3,agratuit);
		i++;		
		recset.MoveNext();
	}	
	recset.Close();
	db.Close();
	SetOptions();
}
void CActivities::SetOptions(){
	CDaoDatabase db;
CDaoRecordset recset(&db);
	CComboBox *ComboV=(CComboBox*)GetDlgItem(IDC_V);
	ComboV->ResetContent();

	COleVariant	var;
	var.ChangeType(VT_BSTR, NULL);
	CString lpszFile=L"GestionVillageVacance.mdb";
	db.Open(lpszFile); 
	CString SqlCmd=L"SELECT no_V,nomV FROM VILLAGES";
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCmd,NULL);
	CString V_no, V_nom;	
	while(!recset.IsEOF())
	{
		recset.GetFieldValue(0, var);
		V_no.Format(L"%d",(LPCWSTR)var.pbstrVal);
		recset.GetFieldValue(1, var);
		V_nom = (LPCWSTR)var.pbstrVal;

		ComboV->AddString(V_no+L" : "+V_nom);
		recset.MoveNext();
	}
	recset.Close();
		CComboBox *ComboA=(CComboBox*)GetDlgItem(IDC_ACTIVITIE_NOM);
	ComboA->ResetContent();
	CComboBox *ComboA2=(CComboBox*)GetDlgItem(IDC_NOMA);
	ComboA2->ResetContent();
	COleVariant	var1;
	var1.ChangeType(VT_BSTR, NULL);
	CString SqlCml=L"SELECT no_A,nomA FROM ACTIVITIES";
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCml,NULL);
	CString A_no, A_nom;	
	while(!recset.IsEOF())
	{
		recset.GetFieldValue(0, var1);
		A_no.Format(L"%d",(LPCWSTR)var1.pbstrVal);
		recset.GetFieldValue(1, var1);
		A_nom = (LPCWSTR)var1.pbstrVal;

		ComboA->AddString(A_no+L" : "+A_nom);
		ComboA2->AddString(A_no+L" : "+A_nom);
		recset.MoveNext();
	}
	recset.Close();
	db.Close();
	 CComboBox *ComboGratuit = (CComboBox*)GetDlgItem(IDC_GRATUIT);
    ComboGratuit->ResetContent();
	CComboBox *ComboGratuit2 = (CComboBox*)GetDlgItem(IDC_NOMG);
    ComboGratuit2->ResetContent();
	 ComboGratuit2->AddString(L"Oui");
    ComboGratuit2->AddString(L"Non");
    ComboGratuit->AddString(L"Oui");
    ComboGratuit->AddString(L"Non");
}
bool CActivities::contains(CString mystring,CString arg){
	bool yes = true;
	int i;
	for(i=0;i<arg.GetLength() && yes;i++){
		if(mystring[i] != arg[i])
			return false;
	}
	return true;
}
void CActivities::OnBnClickedActivitieAjout()
{
	// TODO: Add your control notification handler code here
		// TODO: Add your control notification handler code here
	CDaoDatabase db;
CDaoRecordset recset(&db);
CString lpszFile = L"GestionVillageVacance.mdb";
    db.Open(lpszFile);
   

    CString  V_nom, A_nom, Gratuit;

    CComboBox* ComboVillage = (CComboBox*)GetDlgItem(IDC_V);
    int indexVillages = ComboVillage->GetCurSel();
    ComboVillage->GetLBText(indexVillages,V_nom);

	CComboBox* ComboAct = (CComboBox*)GetDlgItem(IDC_ACTIVITIE_NOM);
    int indexAct = ComboAct->GetCurSel();
    ComboAct->GetLBText(indexAct,A_nom);

    CComboBox* ComboEGrat = (CComboBox*)GetDlgItem(IDC_GRATUIT);
    int indexGratuit = ComboEGrat->GetCurSel();
    ComboEGrat->GetLBText(indexGratuit, Gratuit);
	   int nTokenPos1 = 0;
    CString Grat = Gratuit.Tokenize(_T(" : "), nTokenPos1);

    int nTokenPos = 0;
    CString Villages = V_nom.Tokenize(_T(" : "), nTokenPos);
	CString NomDuVillages = V_nom.Tokenize(_T(" : "), nTokenPos);
 
	int nTokenPos2 = 0;
    CString Activities = A_nom.Tokenize(_T(" : "), nTokenPos2);
	CString NomDuActivities = A_nom.Tokenize(_T(" : "), nTokenPos2);

	/*// Récupérer l'ID du Village nouvellement ajouté
    CString Sqlcmdv = L"SELECT no_V FROM VILLAGES WHERE nomV = '" + NomDuVillages + "'";
    recset.Open(AFX_DAO_USE_DEFAULT_TYPE, Sqlcmdv, NULL);
   int v_no_village = -1;  // Assuming it's an integer, initialize to a default value
COleVariant var1;
var1.ChangeType(VT_I4, NULL);  // Use VT_I4 for a 4-byte integer
recset.GetFieldValue(L"no_V", var1);
v_no_village = var1.lVal;
recset.Close();*/
	/*// Récupérer l'ID du langue nouvellement ajouté
    CString Sqlcmda = L"SELECT no_A FROM ACTIVITIES WHERE nomA = '" + NomDuActivities + "'";
    recset.Open(AFX_DAO_USE_DEFAULT_TYPE, Sqlcmda, NULL);
   int a_no_activitie = -1;  // Assuming it's an integer, initialize to a default value
COleVariant var2;
var2.ChangeType(VT_I4, NULL);  // Use VT_I4 for a 4-byte integer
recset.GetFieldValue(L"no_A", var2);
a_no_activitie = var2.lVal;
recset.Close();*/
	// Ajouter une nouvelle langue/village
    recset.Open(AFX_DAO_USE_DEFAULT_TYPE, L"SELECT * FROM VILLAGES_ACTIVITIES", NULL);
    recset.AddNew();
    recset.SetFieldValue(L"no_V", (LPCWSTR)Villages);
	recset.SetFieldValue(L"no_A", (LPCWSTR)Activities);
	recset.SetFieldValue(L"activitie_gratuit",(LPCWSTR)Grat);
    recset.Update();
    recset.Close();
	db.Close();
    // Clear text fields
    GetDlgItem(IDC_ACTIVITIE_NOM)->SetWindowText(L"");
    GetDlgItem(IDC_GRATUIT)->SetWindowText(L"");
    GetDlgItem(IDC_V)->SetWindowText(L"");

    AfxMessageBox(L"L'activité " + NomDuActivities + L" a été ajouté au village " + NomDuVillages + L"  avec succès  !", MB_ICONINFORMATION | MB_OK);

    RefreshList(); // Si RefreshList() est une fonction définie ailleurs dans votre code


}

bool CActivities::pasvide(){
	CString var0,var1,var2,var3;
	//GetDlgItemText(IDC_NUM,var0);
	GetDlgItemText(IDC_ACTIVITIE_NOM,var1);
	GetDlgItemText(IDC_V,var2);
	GetDlgItemText(IDC_GRATUIT,var3);
    if(var1 == "" || var2 == "" || var3 == "")
		return false;
	else if(var1 != "" && var2 != "" && var3 != "")
		return true;
	return true;
}
void CActivities::OnEnChangeRechercher()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString var;	
	int i=0;
	for(i=0;i<ActivitiesList.GetItemCount();i++){
		GetDlgItemText(IDC_RECHERCHER,var);
		if(var != L""){
			if(contains(ActivitiesList.GetItemText(i,0),var) || contains(ActivitiesList.GetItemText(i,1),var) || contains(ActivitiesList.GetItemText(i,2),var) || contains(ActivitiesList.GetItemText(i,3),var)){
				GetDlgItem(IDC_NO_VILLAGE)->SetWindowText(ActivitiesList.GetItemText(i,0));
				GetDlgItem(IDC_nomVval)->SetWindowText(ActivitiesList.GetItemText(i,1));
				GetDlgItem(IDC_nomAval)->SetWindowText(ActivitiesList.GetItemText(i,2));
				GetDlgItem(IDC_nomGval)->SetWindowText(ActivitiesList.GetItemText(i,3));

				//GetDlgItem(IDC_NOMV)->EnableWindow();
				GetDlgItem(IDC_NOMA)->EnableWindow();
				GetDlgItem(IDC_NOMG)->EnableWindow();

				//GetDlgItem(IDC_NOMV)->SetWindowText(ActivitiesList.GetItemText(i,1));
				GetDlgItem(IDC_NOMA)->SetWindowText(ActivitiesList.GetItemText(i,2));
				GetDlgItem(IDC_NOMG)->SetWindowText(ActivitiesList.GetItemText(i,3));

				GetDlgItem(IDC_ACTIVITIE_SUPP)->EnableWindow();
				GetDlgItem(IDC_ACTIVITIES_UPDA)->EnableWindow();
				ActivitieId = ActivitiesList.GetItemText(i,0);
				break;
			}else{
				GetDlgItem(IDC_NO_VILLAGE)->SetWindowText(L"Aucun Village");
				GetDlgItem(IDC_nomVval)->SetWindowText(L"Aucun Village");
				GetDlgItem(IDC_nomAval)->SetWindowText(L"Aucun Village");
				GetDlgItem(IDC_nomGval)->SetWindowText(L"Aucun Village");

				//GetDlgItem(IDC_NOMV)->SetWindowText(L"");
				GetDlgItem(IDC_NOMA)->SetWindowText(L"");
				GetDlgItem(IDC_NOMG)->SetWindowText(L"");

				//GetDlgItem(IDC_NOMV)->EnableWindow(FALSE);
				GetDlgItem(IDC_NOMA)->EnableWindow(FALSE);
				GetDlgItem(IDC_NOMG)->EnableWindow(FALSE);

				GetDlgItem(IDC_ACTIVITIE_SUPP)->EnableWindow(FALSE);			
				GetDlgItem(IDC_ACTIVITIES_UPDA)->EnableWindow(FALSE);

				ActivitieId = L"-1";
			}
		}else{
			
			GetDlgItem(IDC_NO_VILLAGE)->SetWindowText(L"");
			GetDlgItem(IDC_nomVval)->SetWindowText(L"");
			GetDlgItem(IDC_nomAval)->SetWindowText(L"");
			GetDlgItem(IDC_nomGval)->SetWindowText(L"");

			//GetDlgItem(IDC_NOMV)->SetWindowText(L"");
			GetDlgItem(IDC_NOMA)->SetWindowText(L"");
			GetDlgItem(IDC_NOMG)->SetWindowText(L"");

			//GetDlgItem(IDC_NOMV)->EnableWindow(FALSE);
			GetDlgItem(IDC_NOMA)->EnableWindow(FALSE);
			GetDlgItem(IDC_NOMG)->EnableWindow(FALSE);

			GetDlgItem(IDC_ACTIVITIE_SUPP)->EnableWindow(FALSE);
			GetDlgItem(IDC_ACTIVITIES_UPDA)->EnableWindow(FALSE);

			ActivitieId = L"-1";
		}
	}	
}


void CActivities::OnEnChangeActivitieNom()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	
}


void CActivities::OnCbnSelchangeGratuit()
{
	// TODO: Add your control notification handler code here
	if(pasvide())
		GetDlgItem(IDC_ACTIVITIE_AJOUT)->EnableWindow(TRUE);
	else
		GetDlgItem(IDC_ACTIVITIE_AJOUT)->EnableWindow(FALSE);
}


void CActivities::OnBnClickedActivitieSupp()
{
	// TODO: Add your control notification handler code here
			try {

	// TODO: Add your control notification handler code here
	CDaoDatabase db1;
	CDaoRecordset recset1(&db1);
	CString lpszFile=L"GestionVillageVacance.mdb";
	db1.Open(lpszFile);
	CString V_nom;
	GetDlgItemText(IDC_nomVval, V_nom);

    // Récupérer l'ID du langue nouvellement ajouté
    CString Sqlcmda = L"SELECT no_V FROM VILLAGES WHERE nomV = '" + V_nom  + "'";
    recset1.Open(AFX_DAO_USE_DEFAULT_TYPE, Sqlcmda, NULL);
   int villageID = -1;  // Assuming it's an integer, initialize to a default value
   COleVariant var;
    recset1.GetFieldValue(L"no_V", var);
        villageID = var.lVal;
recset1.Close();
     // Step 1: Delete associated records in VILLAGES_ACTIVITIES
    CString sqlDeleteActivities;  
    sqlDeleteActivities.Format(L"DELETE FROM VILLAGES_ACTIVITIES WHERE no_A = %s AND no_V = %d;", ActivitieId, villageID);
    db1.Execute(sqlDeleteActivities);


	db1.Close();
	recset1.Close();
	GetDlgItem(IDC_RECHERCHER)->SetWindowText(L"");
	 RefreshList();
	 AfxMessageBox(L"L'activité a été supprimé \navec succès !",MB_ICONINFORMATION|MB_OK);}
	catch (CDaoException* e) {
    // Handle exceptions, e.g., display an error message
    e->ReportError();
    e->Delete();
}
}


void CActivities::OnBnClickedActivitiesUpda()
{
	// TODO: Add your control notification handler code here
//	GetDlgItem(IDC_NO_VILLAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ACTIVITIES_UPDA)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_nomAval)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_nomGval)->ShowWindow(SW_HIDE);
	//
	//GetDlgItem(IDC_NOMV)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_NOMA)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_NOMG)->ShowWindow(SW_SHOW);


	GetDlgItem(IDC_APP1)->ShowWindow(SW_SHOW);
}


void CActivities::OnBnClickedApp1()
{
	// TODO: Add your control notification handler code here
	CDaoDatabase db2;
CDaoRecordset recset2(&db2);

	CString v_no_village, V_nom, A_nom,A_nomo,Gratuit;
	GetDlgItemText(IDC_NO_VILLAGE,v_no_village);
	GetDlgItemText(IDC_nomAval,A_nomo);
	GetDlgItemText(IDC_nomVval,V_nom);
/*
int nTokenPos = 0;
CString village = V_nom.Tokenize(_T(" : "), nTokenPos);
CString Nomvillage = V_nom.Tokenize(_T(" : "), nTokenPos);*/

CComboBox* ComboActivitie = (CComboBox*)GetDlgItem(IDC_NOMA);
int indexActivitie = ComboActivitie->GetCurSel();
ComboActivitie->GetLBText(indexActivitie, A_nom);
CComboBox* ComboEGrat = (CComboBox*)GetDlgItem(IDC_NOMG);
int indexGratuit = ComboEGrat->GetCurSel();
ComboEGrat->GetLBText(indexGratuit, Gratuit);

int nTokenPos1 = 0;
CString Grat = Gratuit.Tokenize(_T(" : "), nTokenPos1);
int nTokenPos2 = 0;
CString Activitie = A_nom.Tokenize(_T(" : "), nTokenPos2);
CString NomDactiviti = A_nom.Tokenize(_T(" : "), nTokenPos2);

CString lpszFile = L"GestionVillageVacance.mdb";
db2.Open(lpszFile);

/*// Récupérer l'ID du village nouvellement ajouté
CString Sqlcmdv = L"SELECT no_V FROM VILLAGES WHERE nomV = '" + V_nom + "'";
recset2.Open(AFX_DAO_USE_DEFAULT_TYPE, Sqlcmdv, NULL);
int v_no_village = -1;

var.ChangeType(VT_I4, NULL);
recset2.GetFieldValue(L"no_V", var);
v_no_village = var.lVal;
recset2.Close();
CString strVillageID;
strVillageID.Format(L"%d", v_no_village);*/
// Récupérer l'ID de la langue nouvellement ajoutée
CString Sqlcmdl = L"SELECT no_A FROM ACTIVITIES WHERE nomA = '" + A_nomo + "'";
recset2.Open(AFX_DAO_USE_DEFAULT_TYPE, Sqlcmdl, NULL);
int l_no_langue1 = -1;
COleVariant var;
var.ChangeType(VT_I4, NULL);  // Assurez-vous de réinitialiser la variable var pour éviter des problèmes
recset2.GetFieldValue(L"no_A", var);
l_no_langue1 = var.lVal;
recset2.Close();
CString strActivitiID;
strActivitiID.Format(L"%d", l_no_langue1);

CString strSqlUpdate = L"UPDATE VILLAGES_ACTIVITIES SET no_A = " + Activitie + " WHERE no_V = " + v_no_village + " AND no_A = " + strActivitiID + ";";
db2.Execute(strSqlUpdate);

CString strSqlUpdate2 = L"UPDATE VILLAGES_ACTIVITIES SET activitie_gratuit = '" + Grat + "' WHERE no_V = " + v_no_village + " AND no_A = " + strActivitiID + ";";
db2.Execute(strSqlUpdate2);
db2.Close();
recset2.Close();
	GetDlgItem(IDC_RECHERCHER)->SetWindowText(L"");
	GetDlgItem(IDC_NO_VILLAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_nomVval)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_nomAval)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_nomGval)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ACTIVITIES_UPDA)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_NOMA)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_NOMG)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_APP1)->ShowWindow(SW_HIDE);
	RefreshList();
	AfxMessageBox(L"Les informations du Village "+V_nom+" \n a été mis à jour avec succès !",MB_ICONINFORMATION|MB_OK);

}


void CActivities::OnBnClickedActivitieAjout2()
{
	// TODO: Add your control notification handler code here
	CDaoDatabase db;
CDaoRecordset recset(&db);
CString lpszFile = L"GestionVillageVacance.mdb";

try {
    db.Open(lpszFile);
   

    CString  A_nom;
    GetDlgItemText(IDC_ACTIVITIE_NOM2, A_nom);

 // Ajouter un nouveau Activitie
    recset.Open(AFX_DAO_USE_DEFAULT_TYPE, L"SELECT * FROM ACTIVITIES", NULL);
    recset.AddNew();
    recset.SetFieldValue(L"nomA", (LPCWSTR)A_nom);
    
    recset.Update();
    recset.Close();
    // Clear text fields
    GetDlgItem(IDC_ACTIVITIE_NOM2)->SetWindowText(L"");

    AfxMessageBox(L"L'activité " + A_nom + L" a été ajouté avec succès !", MB_ICONINFORMATION | MB_OK);

    RefreshList(); // Si RefreshList() est une fonction définie ailleurs dans votre code
}
catch (CDaoException* e) {
    // Gérer les exceptions DAO ici (par exemple, afficher un message d'erreur)
    e->ReportError();
    e->Delete();
}
db.Close();

}
