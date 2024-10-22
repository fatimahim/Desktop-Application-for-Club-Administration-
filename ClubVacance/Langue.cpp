// Langue.cpp : implementation file
//

#include "stdafx.h"
#include "ClubVacance.h"
#include "Langue.h"
#include "afxdialogex.h"
#include <afxdao.h>

// CLangue dialog

IMPLEMENT_DYNAMIC(CLangue, CDialogEx)

CLangue::CLangue(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLangue::IDD, pParent)
{
	m_add = AfxGetApp()->LoadIcon(IDI_ICON7);
	m_del= AfxGetApp()->LoadIcon(IDI_ICON7);
	m_up= AfxGetApp()->LoadIcon(IDI_ICON18);
	m_delA= AfxGetApp()->LoadIcon(IDI_ICON16);
	Create(IDD_Langue, pParent);

}

CLangue::~CLangue()
{
}

void CLangue::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LANGUE_LIST, LanguesList);
	DDX_Control(pDX, IDC_V, Villages);
	DDX_Control(pDX, IDC_LANGUE_NOM, LangueNom);
	DDX_Control(pDX, IDC_RECHERCHER, Lrechercher);
	DDX_Control(pDX, IDC_LANGUE_AJOUT, CAdd);
	DDX_Control(pDX, IDC_LANGUE_AJOUT2, CAdd2);
	DDX_Control(pDX, IDC_LANGUES_UPDA, up);
	DDX_Control(pDX, IDC_LANGUE_SUPP, del);
	DDX_Control(pDX, IDC_LANGUE_SUPP2, del2);
	DDX_Control(pDX, IDC_LANGUES_SUPP, delA);
}


BEGIN_MESSAGE_MAP(CLangue, CDialogEx)
	ON_BN_CLICKED(IDC_LANGUE_AJOUT, &CLangue::OnBnClickedLangueAjout)
	ON_EN_CHANGE(IDC_RECHERCHER, &CLangue::OnEnChangeRechercher)
	ON_EN_CHANGE(IDC_LANGUE_NOM, &CLangue::OnEnChangeLangueNom)
	ON_CBN_SELCHANGE(IDC_V, &CLangue::OnCbnSelchangeV)
	ON_BN_CLICKED(IDC_LANGUE_SUPP, &CLangue::OnBnClickedLangueSupp)
	ON_BN_CLICKED(IDC_APP, &CLangue::OnBnClickedApp)
	ON_BN_CLICKED(IDC_LANGUES_UPDA, &CLangue::OnBnClickedLanguesUpda)
	ON_BN_CLICKED(IDC_LANGUE_AJOUT2, &CLangue::OnBnClickedLangueAjout2)
	ON_BN_CLICKED(IDC_LANGUE_SUPP2, &CLangue::OnBnClickedLangueSupp2)
END_MESSAGE_MAP()


// CLangue message handlers
BOOL CLangue::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	LanguesList.InsertColumn(0,L"N°",LVCFMT_LEFT,30,-1);
	LanguesList.InsertColumn(1,L"Nom De Langue",LVCFMT_LEFT,140,-1);
	LanguesList.InsertColumn(2,L"Nom de Village",LVCFMT_LEFT,140,-1);
	ListView_SetExtendedListViewStyle( LanguesList,LVS_EX_GRIDLINES);

	Lrechercher.SetCueBanner(L"Rechercher");
	LangueNom.SetCueBanner(L"Nom De Langue");
	Villages.SetCueBanner(L"Villages");
	RefreshList();
	LangueId = L"-1";

	//GetDlgItem(IDC_NOMV)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_NOML)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_APP)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LANGUE_SUPP)->EnableWindow(FALSE);			
	GetDlgItem(IDC_LANGUES_UPDA)->EnableWindow(FALSE);
	GetDlgItem(IDC_LANGUE_AJOUT)->EnableWindow(FALSE);
		CAdd.SetIcon(m_add);
	CAdd2.SetIcon(m_add);
	del.SetIcon(m_del);
	del2.SetIcon(m_del);
	//del2.SetIcon(m_del);
	delA.SetIcon(m_delA);
	//delA2.SetIcon(m_delA);
	//app.SetIcon(m_app);
	up.SetIcon(m_up);
//	GetDlgItem(IDC_NOMV)->EnableWindow(FALSE);
	GetDlgItem(IDC_NOML)->EnableWindow(FALSE);
	/*GetDlgItem(8888)->GetWindowRect(rc);
	ScreenToClient(&rc);*/
	
	return TRUE;
}
bool CLangue::contains(CString mystring,CString arg){
	bool yes = true;
	int i;
	for(i=0;i<arg.GetLength() && yes;i++){
		if(mystring[i] != arg[i])
			return false;
	}
	return true;
}
void CLangue::RefreshList(){
	CDaoDatabase db;
	CDaoRecordset recset(&db);
	COleVariant var;  // Start Variables
	var.ChangeType(VT_BSTR, NULL);
	CString l_no_Langue,L_nom,V_nom; // End Variables
	LanguesList.DeleteAllItems(); // Clear List
	CString lpszFile=L"GestionVillageVacance.mdb";
	db.Open(lpszFile); // Open Clients.MDB
	CString SqlCmd=L"SELECT VILLAGES_LANGUES.no_V, LANGUES.nomL, VILLAGES.nomV FROM VILLAGES INNER JOIN (LANGUES INNER JOIN VILLAGES_LANGUES ON VILLAGES_LANGUES.no_L = LANGUES.no_L) ON VILLAGES_LANGUES.no_V = VILLAGES.no_V order by VILLAGES_LANGUES.no_L desc";
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCmd,NULL);
	while(!recset.IsEOF()) // Do until EOF
	{
		int i = 0;	
		recset.GetFieldValue(L"no_V",var);
		l_no_Langue.Format(L"%d",(LPCWSTR)var.pbstrVal);
		LanguesList.InsertItem(i,l_no_Langue,0);
		recset.GetFieldValue(L"nomL",var);
		L_nom = (LPCWSTR)var.pbstrVal;
		LanguesList.SetItemText(i,1,L_nom);	
		recset.GetFieldValue(L"nomV",var);		
		V_nom = (LPCWSTR)var.pbstrVal;
		LanguesList.SetItemText(i,2,V_nom);	
		i++;		
		recset.MoveNext();
	}	
	recset.Close();
	db.Close();
	SetOptions();
}
void CLangue::SetOptions(){
	CDaoDatabase db;
CDaoRecordset recset(&db);
	CComboBox *ComboV=(CComboBox*)GetDlgItem(IDC_V);
	ComboV->ResetContent();
/*	CComboBox *ComboV2=(CComboBox*)GetDlgItem(IDC_NOMV);
	ComboV2->ResetContent();*/
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
		//ComboV2->AddString(V_no+L" : "+V_nom);
		recset.MoveNext();
	}
	recset.Close();
	CComboBox *ComboL=(CComboBox*)GetDlgItem(IDC_LANGUE_NOM);
	ComboL->ResetContent();
	CComboBox *ComboL2=(CComboBox*)GetDlgItem(IDC_NOML);
	ComboL2->ResetContent();
	COleVariant	var1;
	var1.ChangeType(VT_BSTR, NULL);
	CString SqlCml=L"SELECT no_L,nomL FROM LANGUES";
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCml,NULL);
	CString L_no, L_nom;	
	while(!recset.IsEOF())
	{
		recset.GetFieldValue(0, var1);
		L_no.Format(L"%d",(LPCWSTR)var1.pbstrVal);
		recset.GetFieldValue(1, var1);
		L_nom = (LPCWSTR)var1.pbstrVal;

		ComboL->AddString(L_no+L" : "+L_nom);
		ComboL2->AddString(L_no+L" : "+L_nom);
		recset.MoveNext();
	}
	recset.Close();
	db.Close();
	
}

void CLangue::OnBnClickedLangueAjout()
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
		// TODO: Add your control notification handler code here
	CDaoDatabase db;
CDaoRecordset recset(&db);
CString lpszFile = L"GestionVillageVacance.mdb";
    db.Open(lpszFile);
   

    CString  V_nom, L_nom;

    CComboBox* ComboVillage = (CComboBox*)GetDlgItem(IDC_V);
    int indexVillages = ComboVillage->GetCurSel();
    ComboVillage->GetLBText(indexVillages,V_nom);

	CComboBox* ComboLangue = (CComboBox*)GetDlgItem(IDC_LANGUE_NOM);
    int indexLangue = ComboLangue->GetCurSel();
    ComboLangue->GetLBText(indexLangue,L_nom);

    int nTokenPos = 0;
    CString Villages = V_nom.Tokenize(_T(" : "), nTokenPos);
	CString NomDuVillages = V_nom.Tokenize(_T(" : "), nTokenPos);
	///////////////////////pour langue
	
    int nTokenPos1 = 0;
    CString Langues = L_nom.Tokenize(_T(" : "), nTokenPos1);
	CString NomDuLangues = L_nom.Tokenize(_T(" : "), nTokenPos1);
/*
	// Récupérer l'ID du Village nouvellement ajouté
    CString Sqlcmdv = L"SELECT no_V FROM VILLAGES WHERE nomV = '" + NomDuVillages + "'";
    recset.Open(AFX_DAO_USE_DEFAULT_TYPE, Sqlcmdv, NULL);
   int v_no_village = -1;  // Assuming it's an integer, initialize to a default value
COleVariant var1;
var1.ChangeType(VT_I4, NULL);  // Use VT_I4 for a 4-byte integer
recset.GetFieldValue(L"no_V", var1);
v_no_village = var1.lVal;
recset.Close();

	// Récupérer l'ID du langue nouvellement ajouté
    CString Sqlcmdl = L"SELECT no_L FROM LANGUES WHERE nomL = '" + NomDuLangues + "'";
    recset.Open(AFX_DAO_USE_DEFAULT_TYPE, Sqlcmdl, NULL);
   int l_no_langue = -1;  // Assuming it's an integer, initialize to a default value
COleVariant var2;
var2.ChangeType(VT_I4, NULL);  // Use VT_I4 for a 4-byte integer
recset.GetFieldValue(L"no_L", var2);
l_no_langue = var2.lVal;
recset.Close();*/
	// Ajouter une nouvelle langue/village
    recset.Open(AFX_DAO_USE_DEFAULT_TYPE, L"SELECT * FROM VILLAGES_LANGUES", NULL);
    recset.AddNew();
    recset.SetFieldValue(L"no_V", (LPCWSTR)Villages);
	recset.SetFieldValue(L"no_L", (LPCWSTR)Langues);
    recset.Update();
    recset.Close();
	
db.Close();
    // Clear text fields
    GetDlgItem(IDC_LANGUE_NOM)->SetWindowText(L"");
    GetDlgItem(IDC_V)->SetWindowText(L"");

    AfxMessageBox(L"La Langue " + NomDuLangues +  L" a été ajouté au village " + NomDuVillages + L"  avec succès  !", MB_ICONINFORMATION | MB_OK);

    RefreshList(); // Si RefreshList() est une fonction définie ailleurs dans votre code


}

bool CLangue::pasvide(){
	CString var0,var1,var2,var3;
	//GetDlgItemText(IDC_NUM,var0);
	GetDlgItemText(IDC_LANGUE_NOM,var1);
	GetDlgItemText(IDC_V,var2);
    if(var1 == "" || var2 == "" )
		return false;
	else if(var1 != "" && var2 != "" )
		return true;
	return true;
}
void CLangue::OnEnChangeRechercher()
{
		// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString var;	
	int i=0;
	for(i=0;i<LanguesList.GetItemCount();i++){
		GetDlgItemText(IDC_RECHERCHER,var);
		if(var != L""){
			if(contains(LanguesList.GetItemText(i,0),var) || contains(LanguesList.GetItemText(i,1),var) || contains(LanguesList.GetItemText(i,2),var) || contains(LanguesList.GetItemText(i,3),var)){
				GetDlgItem(IDC_NO_VILLAGE)->SetWindowText(LanguesList.GetItemText(i,0));
				GetDlgItem(IDC_nomVval)->SetWindowText(LanguesList.GetItemText(i,2));
				GetDlgItem(IDC_nomLval)->SetWindowText(LanguesList.GetItemText(i,1));

				//GetDlgItem(IDC_NOMV)->EnableWindow();
				GetDlgItem(IDC_NOML)->EnableWindow();

				//GetDlgItem(IDC_NOMV)->SetWindowText(LanguesList.GetItemText(i,2));
				GetDlgItem(IDC_NOML)->SetWindowText(LanguesList.GetItemText(i,1));

				GetDlgItem(IDC_LANGUE_SUPP)->EnableWindow();
				GetDlgItem(IDC_LANGUES_UPDA)->EnableWindow();
				LangueId = LanguesList.GetItemText(i,0);
				break;
			}else{
				GetDlgItem(IDC_NO_VILLAGE)->SetWindowText(L"Aucun Langue");
				GetDlgItem(IDC_nomVval)->SetWindowText(L"Aucun Langue");
				GetDlgItem(IDC_nomLval)->SetWindowText(L"Aucun Langue");

				//GetDlgItem(IDC_NOMV)->SetWindowText(L"");
				GetDlgItem(IDC_NOML)->SetWindowText(L"");

				//GetDlgItem(IDC_NOMV)->EnableWindow(FALSE);
				GetDlgItem(IDC_NOML)->EnableWindow(FALSE);

				GetDlgItem(IDC_LANGUE_SUPP)->EnableWindow(FALSE);			
				GetDlgItem(IDC_LANGUES_UPDA)->EnableWindow(FALSE);

				LangueId = L"-1";
			}
		}else{
			
			GetDlgItem(IDC_NO_VILLAGE)->SetWindowText(L"");
			GetDlgItem(IDC_nomVval)->SetWindowText(L"");
			GetDlgItem(IDC_nomLval)->SetWindowText(L"");

			//GetDlgItem(IDC_NOMV)->SetWindowText(L"");
			GetDlgItem(IDC_NOML)->SetWindowText(L"");

			//GetDlgItem(IDC_NOMV)->EnableWindow(FALSE);
			GetDlgItem(IDC_NOML)->EnableWindow(FALSE);

			GetDlgItem(IDC_LANGUE_SUPP)->EnableWindow(FALSE);
			GetDlgItem(IDC_LANGUES_UPDA)->EnableWindow(FALSE);

			LangueId = L"-1";
		}
	}	
}


void CLangue::OnEnChangeLangueNom()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

}


void CLangue::OnCbnSelchangeV()
{
	// TODO: Add your control notification handler code here
		if(pasvide())
		GetDlgItem(IDC_LANGUE_AJOUT)->EnableWindow(TRUE);
	else
		GetDlgItem(IDC_LANGUE_AJOUT)->EnableWindow(FALSE);
}


void CLangue::OnBnClickedLangueSupp()
{
	// TODO: Add your control notification handler code here
		try { CDaoDatabase db1;
        CDaoRecordset recset1(&db1);
        CString lpszFile = L"GestionVillageVacance.mdb";
        db1.Open(lpszFile);

        CString V_nom;
        GetDlgItemText(IDC_nomVval, V_nom);

        // Récupérer l'ID du village
        CString Sqlcmda = L"SELECT no_V FROM VILLAGES WHERE nomV = '" + V_nom + "'";
        recset1.Open(AFX_DAO_USE_DEFAULT_TYPE, Sqlcmda, NULL);

        int villageID = -1;  // Assuming it's an integer, initialize to a default value
        COleVariant var;
        if (!recset1.IsEOF()) {
            recset1.GetFieldValue(L"no_V", var);
            villageID = var.lVal;
        }
        recset1.Close();

        // Step 2: Delete associated records in VILLAGES_LANGUES
        CString sqlDeleteLanguages;
        sqlDeleteLanguages.Format(L"DELETE FROM VILLAGES_LANGUES WHERE no_L = %s AND no_V = %d;", LangueId, villageID);
        db1.Execute(sqlDeleteLanguages);

        db1.Close();
        recset1.Close();
        GetDlgItem(IDC_RECHERCHER)->SetWindowText(L"");
        RefreshList();
        AfxMessageBox(L"La Langue a été supprimée\navec succès !", MB_ICONINFORMATION | MB_OK);
    }
    catch (CDaoException* e) {
        // Handle exceptions, e.g., display an error message
        e->ReportError();
        e->Delete();
    }
}


void CLangue::OnBnClickedApp()
{
	// TODO: Add your control notification handler code here
CDaoDatabase db2;
CDaoRecordset recset2(&db2);

	CString v_no_village, V_nom, L_nom,L_nomo;
	GetDlgItemText(IDC_NO_VILLAGE,v_no_village);
	GetDlgItemText(IDC_nomLval,L_nomo);
	GetDlgItemText(IDC_nomVval,V_nom);
/*
int nTokenPos = 0;
CString village = V_nom.Tokenize(_T(" : "), nTokenPos);
CString Nomvillage = V_nom.Tokenize(_T(" : "), nTokenPos);*/

CComboBox* ComboLangue = (CComboBox*)GetDlgItem(IDC_NOML);
int indexLangue = ComboLangue->GetCurSel();
ComboLangue->GetLBText(indexLangue, L_nom);

int nTokenPos1 = 0;
CString Langues = L_nom.Tokenize(_T(" : "), nTokenPos1);
CString NomDuLangues = L_nom.Tokenize(_T(" : "), nTokenPos1);

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
CString Sqlcmdl = L"SELECT no_L FROM LANGUES WHERE nomL = '" + L_nomo + "'";
recset2.Open(AFX_DAO_USE_DEFAULT_TYPE, Sqlcmdl, NULL);
int l_no_langue1 = -1;
COleVariant var;
var.ChangeType(VT_I4, NULL);  // Assurez-vous de réinitialiser la variable var pour éviter des problèmes
recset2.GetFieldValue(L"no_L", var);
l_no_langue1 = var.lVal;
recset2.Close();
CString strLangueID;
strLangueID.Format(L"%d", l_no_langue1);

CString strSqlUpdate = L"UPDATE VILLAGES_LANGUES SET no_L = " + Langues + " WHERE no_V = " + v_no_village + " AND no_L = "+strLangueID+";";
db2.Execute(strSqlUpdate);

db2.Close();
recset2.Close();
	GetDlgItem(IDC_RECHERCHER)->SetWindowText(L"");
	GetDlgItem(IDC_NO_VILLAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_nomVval)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_nomLval)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LANGUES_UPDA)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_NOML)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_APP)->ShowWindow(SW_HIDE);
	RefreshList();
	AfxMessageBox(L"Les informations du Village "+V_nom+" \n a été mis à jour avec succès !",MB_ICONINFORMATION|MB_OK);
}


void CLangue::OnBnClickedLanguesUpda()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_NO_VILLAGE)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_nomVval)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_nomLval)->ShowWindow(SW_HIDE);

	//GetDlgItem(IDC_NOMV)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_NOML)->ShowWindow(SW_SHOW);


	GetDlgItem(IDC_APP)->ShowWindow(SW_SHOW);
}


void CLangue::OnBnClickedLangueAjout2()
{
	// TODO: Add your control notification handler code here
	CDaoDatabase db;
CDaoRecordset recset(&db);
CString lpszFile = L"GestionVillageVacance.mdb";

try {
    db.Open(lpszFile);
   

    CString  L_nom;
    GetDlgItemText(IDC_LANGUE_NOM2, L_nom);
 // Ajouter une nouvelle langue
    recset.Open(AFX_DAO_USE_DEFAULT_TYPE, L"SELECT * FROM LANGUES", NULL);
    recset.AddNew();
    recset.SetFieldValue(L"nomL", (LPCWSTR)L_nom);
    recset.Update();
    recset.Close();
    // Clear text fields
    GetDlgItem(IDC_LANGUE_NOM2)->SetWindowText(L"");
    GetDlgItem(IDC_V)->SetWindowText(L"");

    AfxMessageBox(L"La Langue " + L_nom + L" a été ajouté avec succès !", MB_ICONINFORMATION | MB_OK);

    RefreshList(); // Si RefreshList() est une fonction définie ailleurs dans votre code
}
catch (CDaoException* e) {
    // Gérer les exceptions DAO ici (par exemple, afficher un message d'erreur)
    e->ReportError();
    e->Delete();
}
db.Close();

}


void CLangue::OnBnClickedLangueSupp2()
{/*
	// TODO: Add your control notification handler code here
	try { CDaoDatabase db1;
        CDaoRecordset recset1(&db1);
        CString lpszFile = L"GestionVillageVacance.mdb";
        db1.Open(lpszFile);

        CString V_nom;
        GetDlgItemText(IDC_nomVval, V_nom);

        // Récupérer l'ID du village
        CString Sqlcmda = L"SELECT no_V FROM VILLAGES WHERE nomV = '" + V_nom + "'";
        recset1.Open(AFX_DAO_USE_DEFAULT_TYPE, Sqlcmda, NULL);

        int villageID = -1;  // Assuming it's an integer, initialize to a default value
        COleVariant var;
        if (!recset1.IsEOF()) {
            recset1.GetFieldValue(L"no_V", var);
            villageID = var.lVal;
        }
        recset1.Close();

        // Step 2: Delete associated records in VILLAGES_LANGUES
        CString sqlDeleteLanguages;
        sqlDeleteLanguages.Format(L"DELETE FROM LANGUES WHERE no_L = %s ;", LangueId);
        db1.Execute(sqlDeleteLanguages);

        db1.Close();
        recset1.Close();
        GetDlgItem(IDC_RECHERCHER)->SetWindowText(L"");
        RefreshList();
        AfxMessageBox(L"La Langue a été supprimée\navec succès !", MB_ICONINFORMATION | MB_OK);
    }
    catch (CDaoException* e) {
        // Handle exceptions, e.g., display an error message
        e->ReportError();
        e->Delete();
    }*/
}
