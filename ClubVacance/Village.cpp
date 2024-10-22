// Village.cpp : implementation file
//

#include "stdafx.h"
#include "ClubVacance.h"
#include "Village.h"
#include "afxdialogex.h"
#include <afxdao.h>



// CVillage dialog

IMPLEMENT_DYNAMIC(CVillage, CDialogEx)

CVillage::CVillage(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVillage::IDD, pParent)
{
	m_add = AfxGetApp()->LoadIcon(IDI_ICON5);
	m_del= AfxGetApp()->LoadIcon(IDI_ICON5);
	m_up= AfxGetApp()->LoadIcon(IDI_ICON14);
	m_delA= AfxGetApp()->LoadIcon(IDI_ICON16);
	Create(IDD_VillageView, pParent);
}

CVillage::~CVillage()
{
}

void CVillage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VILLAGES_LIST, VillagesList);
	DDX_Control(pDX, IDC_VILLAGE_NOM, VillageNom);
	DDX_Control(pDX, IDC_LANGUE_NOM, LangueNom);
	DDX_Control(pDX, IDC_P, PAYS);
	DDX_Control(pDX, IDC_RECHERCHER, Vrechercher);
	DDX_Control(pDX, IDC_VILLAGES_UPDA, up);
	DDX_Control(pDX, IDC_VILLAGE_SUPP, del);
	DDX_Control(pDX, IDC_VILLAGES_AJOUT, CAdd);
	DDX_Control(pDX, IDC_VILLAGES_SUPP, delA);
}


BEGIN_MESSAGE_MAP(CVillage, CDialogEx)
	ON_BN_CLICKED(IDC_VILLAGES_AJOUT, &CVillage::OnBnClickedVillagesAjout)
	ON_EN_CHANGE(IDC_RECHERCHER, &CVillage::OnEnChangeRechercher)
	ON_EN_CHANGE(IDC_VILLAGE_NOM, &CVillage::OnEnChangeVillageNom)
	ON_EN_CHANGE(IDC_LANGUE_NOM, &CVillage::OnEnChangeLangueNom)
	ON_BN_CLICKED(IDC_VILLAGE_SUPP, &CVillage::OnBnClickedVillageSupp)
	ON_BN_CLICKED(IDC_APP, &CVillage::OnBnClickedApp)
	ON_BN_CLICKED(IDC_VILLAGES_UPDA, &CVillage::OnBnClickedVillagesUpda)
END_MESSAGE_MAP()


// CVillage message handlers
BOOL CVillage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	VillagesList.InsertColumn(0,L"N°",LVCFMT_LEFT,30,-1);
	VillagesList.InsertColumn(1,L"Code",LVCFMT_LEFT,50,-1);
	VillagesList.InsertColumn(2,L"Nom de Villages",LVCFMT_LEFT,140,-1);
	VillagesList.InsertColumn(3,L"Nom De Pays",LVCFMT_LEFT,140,-1);
	ListView_SetExtendedListViewStyle( VillagesList,LVS_EX_GRIDLINES);

	Vrechercher.SetCueBanner(L"Rechercher");
	VillageNom.SetCueBanner(L"Nom de Village");
	PAYS.SetCueBanner(L"Pays");
	LangueNom.SetCueBanner(L"Langue ");
	RefreshList();
	VillageId = L"-1";

	GetDlgItem(IDC_CODEVILLAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_NOMVILLAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_NOMP)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_APP)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_VILLAGE_SUPP)->EnableWindow(FALSE);			
	GetDlgItem(IDC_VILLAGES_UPDA)->EnableWindow(FALSE);
	GetDlgItem(IDC_VILLAGES_AJOUT)->EnableWindow(FALSE);

	GetDlgItem(IDC_CODEVILLAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_NOMVILLAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_NOMP)->EnableWindow(FALSE);
	/*GetDlgItem(8888)->GetWindowRect(rc);
	ScreenToClient(&rc);*/
	CAdd.SetIcon(m_add);
	//CAdd2.SetIcon(m_add);
	del.SetIcon(m_del);
	//del2.SetIcon(m_del);
	delA.SetIcon(m_delA);
	//delA2.SetIcon(m_delA);
	//app.SetIcon(m_app);
	up.SetIcon(m_up);
	//up2.SetIcon(m_up);
	
	return TRUE;
	
}
bool CVillage::contains(CString mystring,CString arg){
	bool yes = true;
	int i;
	for(i=0;i<arg.GetLength() && yes;i++){
		if(mystring[i] != arg[i])
			return false;
	}
	return true;
}
void CVillage::OnBnClickedVillagesAjout()
{
	// TODO: Add your control notification handler code here
	CDaoDatabase db;
CDaoRecordset recset(&db);
CString lpszFile = L"GestionVillageVacance.mdb";
    db.Open(lpszFile);
   

    CString P_nom, V_nom, L_nom;

    GetDlgItemText(IDC_VILLAGE_NOM, V_nom);
	GetDlgItemText(IDC_LANGUE_NOM, L_nom);
    CComboBox* ComboPay = (CComboBox*)GetDlgItem(IDC_P);
    int indexPays = ComboPay->GetCurSel();
    ComboPay->GetLBText(indexPays, P_nom);


    int nTokenPos = 0;
    CString Pays = P_nom.Tokenize(_T(" : "), nTokenPos);
	CString NomDuPays = P_nom.Tokenize(_T(" : "), nTokenPos);
    // Récupérer l'ID du pays nouvellement ajouté
    CString Sqlcmdp = L"SELECT no_P FROM PAYS WHERE nomP = '" + NomDuPays + "'";
    recset.Open(AFX_DAO_USE_DEFAULT_TYPE, Sqlcmdp, NULL);
   int p_no_pay = -1;  // Assuming it's an integer, initialize to a default value
COleVariant var;
var.ChangeType(VT_I4, NULL);  // Use VT_I4 for a 4-byte integer
recset.GetFieldValue(L"no_P", var);
p_no_pay = var.lVal;
recset.Close();

    // Ajouter un nouveau village
 recset.Open(AFX_DAO_USE_DEFAULT_TYPE, L"SELECT * FROM VILLAGES", NULL);
    recset.AddNew();
    recset.SetFieldValue(L"nomV", (LPCWSTR)V_nom);
	CString codeV = V_nom.Left(3);
    recset.SetFieldValue(L"codeV", (LPCWSTR)codeV);
    recset.SetFieldValue(L"no_P", (short)p_no_pay);
    recset.Update();
    recset.Close();
	// Récupérer l'ID du Village nouvellement ajouté
    CString Sqlcmdv = L"SELECT no_V FROM VILLAGES WHERE nomV = '" + V_nom + "'";
    recset.Open(AFX_DAO_USE_DEFAULT_TYPE, Sqlcmdv, NULL);
   int v_no_village = -1;  // Assuming it's an integer, initialize to a default value
COleVariant var1;
var1.ChangeType(VT_I4, NULL);  // Use VT_I4 for a 4-byte integer
recset.GetFieldValue(L"no_V", var1);
v_no_village = var1.lVal;
recset.Close();

	// Ajouter une nouvelle langue
    recset.Open(AFX_DAO_USE_DEFAULT_TYPE, L"SELECT * FROM LANGUES", NULL);
    recset.AddNew();
    recset.SetFieldValue(L"nomL", (LPCWSTR)L_nom);
    recset.Update();
    recset.Close();
	// Récupérer l'ID du langue nouvellement ajouté
    CString Sqlcmdl = L"SELECT no_L FROM LANGUES WHERE nomL = '" + L_nom + "'";
    recset.Open(AFX_DAO_USE_DEFAULT_TYPE, Sqlcmdl, NULL);
   int l_no_langue = -1;  // Assuming it's an integer, initialize to a default value
COleVariant var2;
var2.ChangeType(VT_I4, NULL);  // Use VT_I4 for a 4-byte integer
recset.GetFieldValue(L"no_L", var2);
l_no_langue = var2.lVal;
recset.Close();
	// Ajouter une nouvelle langue/village
    recset.Open(AFX_DAO_USE_DEFAULT_TYPE, L"SELECT * FROM VILLAGES_LANGUES", NULL);
    recset.AddNew();
    recset.SetFieldValue(L"no_V", (short)v_no_village);
	recset.SetFieldValue(L"no_L", (short)l_no_langue);
    recset.Update();
    recset.Close();
	db.Close();
    // Clear text fields
    GetDlgItem(IDC_VILLAGE_NOM)->SetWindowText(L"");
    GetDlgItem(IDC_LANGUE_NOM)->SetWindowText(L"");
    GetDlgItem(IDC_P)->SetWindowText(L"");


    AfxMessageBox(L"Le Village " + V_nom + L" a été ajouté avec succès !", MB_ICONINFORMATION | MB_OK);

    RefreshList(); // Si RefreshList() est une fonction définie ailleurs dans votre code

db.Close();

}
void CVillage::RefreshList(){
	CDaoDatabase db;
	CDaoRecordset recset(&db);
	COleVariant var;  // Start Variables
	var.ChangeType(VT_BSTR, NULL);
	CString v_no_Village,V_nom,P_nom,Vcode; // End Variables
	VillagesList.DeleteAllItems(); // Clear List
	CString lpszFile=L"GestionVillageVacance.mdb";
	db.Open(lpszFile); // Open Clients.MDB
	CString SqlCmd=L"SELECT no_V,nomV,nomP,codeV FROM VILLAGES INNER JOIN PAYS ON PAYS.no_P=VILLAGES.no_P order by 1 desc";
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCmd,NULL);
	while(!recset.IsEOF()) // Do until EOF
	{
		int i = 0;	
		recset.GetFieldValue(L"no_V",var);
		v_no_Village.Format(L"%d",(LPCWSTR)var.pbstrVal);
		VillagesList.InsertItem(i,v_no_Village,0);
		recset.GetFieldValue(L"codeV",var);
		Vcode = (LPCWSTR)var.pbstrVal;
		VillagesList.SetItemText(i,1,Vcode);	
		recset.GetFieldValue(L"nomV",var);
		V_nom = (LPCWSTR)var.pbstrVal;
		VillagesList.SetItemText(i,2,V_nom);	
		recset.GetFieldValue(L"nomP",var);		
		P_nom = (LPCWSTR)var.pbstrVal;
		VillagesList.SetItemText(i,3,P_nom);		
		i++;		
		recset.MoveNext();
	}	
	recset.Close();
	db.Close();
	SetOptions();
}
void CVillage::SetOptions(){
	CDaoDatabase db;
CDaoRecordset recset(&db);
	CComboBox *ComboP=(CComboBox*)GetDlgItem(IDC_P);
	ComboP->ResetContent();
	COleVariant	var;
	var.ChangeType(VT_BSTR, NULL);
	CString lpszFile=L"GestionVillageVacance.mdb";
	db.Open(lpszFile); 
	CString SqlCmd=L"SELECT no_P,nomP FROM PAYS";
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCmd,NULL);
	CString V_no, V_nom;	
	while(!recset.IsEOF())
	{
		recset.GetFieldValue(0, var);
		V_no.Format(L"%d",(LPCWSTR)var.pbstrVal);
		recset.GetFieldValue(1, var);
		V_nom = (LPCWSTR)var.pbstrVal;

		ComboP->AddString(V_no+L" : "+V_nom);
		recset.MoveNext();
	}
	recset.Close();
	CComboBox *ComboP2=(CComboBox*)GetDlgItem(IDC_NOMP);
	ComboP2->ResetContent();
	COleVariant	var1;
	var1.ChangeType(VT_BSTR, NULL);
	CString SqlCmd1=L"SELECT no_P,nomP FROM PAYS";
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCmd1,NULL);
	CString V_no1, V_nom1;	
	while(!recset.IsEOF())
	{
		recset.GetFieldValue(0, var1);
		V_no1.Format(L"%d",(LPCWSTR)var1.pbstrVal);
		recset.GetFieldValue(1, var1);
		V_nom1 = (LPCWSTR)var1.pbstrVal;

		ComboP2->AddString(V_no1+L" : "+V_nom1);
		recset.MoveNext();
	}
	recset.Close();
	db.Close();

}

bool CVillage::pasvide(){
	CString var0,var1,var2,var3;
	//GetDlgItemText(IDC_NUM,var0);
	GetDlgItemText(IDC_VILLAGE_NOM,var1);
	GetDlgItemText(IDC_P,var2);
	GetDlgItemText(IDC_LANGUE_NOM,var3);
    if(var1 == "" || var2 == "" || var3 == "")
		return false;
	else if(var1 != "" && var2 != "" && var3 != "")
		return true;
	return true;
}
void CVillage::OnEnChangeRechercher()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString var;	
	int i=0;
	for(i=0;i<VillagesList.GetItemCount();i++){
		GetDlgItemText(IDC_RECHERCHER,var);
		if(var != L""){
			if(contains(VillagesList.GetItemText(i,0),var) || contains(VillagesList.GetItemText(i,1),var) || contains(VillagesList.GetItemText(i,2),var) || contains(VillagesList.GetItemText(i,3),var)){

	            GetDlgItem(IDC_NO_VILLAGE)->SetWindowText(VillagesList.GetItemText(i,0));
				GetDlgItem(IDC_codeVval)->SetWindowText(VillagesList.GetItemText(i,1));
				GetDlgItem(IDC_nomVval)->SetWindowText(VillagesList.GetItemText(i,2));
				GetDlgItem(IDC_nomPval)->SetWindowText(VillagesList.GetItemText(i,3));

				GetDlgItem(IDC_CODEVILLAGE)->EnableWindow();
				GetDlgItem(IDC_NOMVILLAGE)->EnableWindow();
				GetDlgItem(IDC_NOMP)->EnableWindow();

				GetDlgItem(IDC_CODEVILLAGE)->SetWindowText(VillagesList.GetItemText(i,1));
				GetDlgItem(IDC_NOMVILLAGE)->SetWindowText(VillagesList.GetItemText(i,2));
				GetDlgItem(IDC_NOMP)->SetWindowText(VillagesList.GetItemText(i,3));

				GetDlgItem(IDC_VILLAGE_SUPP)->EnableWindow();
				GetDlgItem(IDC_VILLAGES_UPDA)->EnableWindow();
				VillageId = VillagesList.GetItemText(i,0);
				break;
			}else{
				GetDlgItem(IDC_NO_VILLAGE)->SetWindowText(L"Aucun client");
				GetDlgItem(IDC_codeVval)->SetWindowText(L"Aucun client");
				GetDlgItem(IDC_nomVval)->SetWindowText(L"Aucun client");
				GetDlgItem(IDC_nomPval)->SetWindowText(L"Aucun client");

				GetDlgItem(IDC_CODEVILLAGE)->SetWindowText(L"");
				GetDlgItem(IDC_NOMVILLAGE)->SetWindowText(L"");
				GetDlgItem(IDC_NOMP)->SetWindowText(L"");

				GetDlgItem(IDC_CODEVILLAGE)->EnableWindow(FALSE);
				GetDlgItem(IDC_NOMVILLAGE)->EnableWindow(FALSE);
				GetDlgItem(IDC_NOMP)->EnableWindow(FALSE);

				GetDlgItem(IDC_VILLAGE_SUPP)->EnableWindow(FALSE);			
				GetDlgItem(IDC_VILLAGES_UPDA)->EnableWindow(FALSE);

				VillageId = L"-1";
			}
		}else{
			
			GetDlgItem(IDC_NO_VILLAGE)->SetWindowText(L"");
			GetDlgItem(IDC_codeVval)->SetWindowText(L"");
			GetDlgItem(IDC_nomVval)->SetWindowText(L"");
			GetDlgItem(IDC_nomPval)->SetWindowText(L"");

			GetDlgItem(IDC_CODEVILLAGE)->SetWindowText(L"");
			GetDlgItem(IDC_NOMVILLAGE)->SetWindowText(L"");
			GetDlgItem(IDC_NOMP)->SetWindowText(L"");

			GetDlgItem(IDC_CODEVILLAGE)->EnableWindow(FALSE);
			GetDlgItem(IDC_NOMVILLAGE)->EnableWindow(FALSE);
			GetDlgItem(IDC_NOMP)->EnableWindow(FALSE);

			GetDlgItem(IDC_VILLAGE_SUPP)->EnableWindow(FALSE);
			GetDlgItem(IDC_VILLAGES_UPDA)->EnableWindow(FALSE);

			VillageId = L"-1";
		}
	}	
}


void CVillage::OnEnChangeVillageNom()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	
}


void CVillage::OnEnChangeLangueNom()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
		if(pasvide())
		GetDlgItem(IDC_VILLAGES_AJOUT)->EnableWindow(TRUE);
	else
		GetDlgItem(IDC_VILLAGES_AJOUT)->EnableWindow(FALSE);
}


void CVillage::OnBnClickedVillageSupp()
{
	// TODO: Add your control notification handler code here
	try {

	// TODO: Add your control notification handler code here
	CDaoDatabase db1;
	CDaoRecordset recset1(&db1);
	CString lpszFile=L"GestionVillageVacance.mdb";
	db1.Open(lpszFile);
 // Step 1: Delete associated records in VILLAGES_ACTIVITIES
    CString sqlDeleteActivities = L"DELETE FROM VILLAGES_ACTIVITIES WHERE no_V = " + VillageId + ";";
    db1.Execute(sqlDeleteActivities);

    // Step 2: Delete associated records in VILLAGES_LANGUES
    CString sqlDeleteLanguages = L"DELETE FROM VILLAGES_LANGUES WHERE no_V  = " +  VillageId + ";";
    db1.Execute(sqlDeleteLanguages);

    // Step 3: Delete associated records in VILLAGES
    CString sqlDeleteVillages = L"DELETE FROM VILLAGES WHERE no_V = " + VillageId + ";";
    db1.Execute(sqlDeleteVillages);


	db1.Close();
	recset1.Close();
	GetDlgItem(IDC_RECHERCHER)->SetWindowText(L"");
	 RefreshList();
	 AfxMessageBox(L"Le Village a été supprimé \navec succès !",MB_ICONINFORMATION|MB_OK);}
	catch (CDaoException* e) {
    // Handle exceptions, e.g., display an error message
    e->ReportError();
    e->Delete();
}
	
}


void CVillage::OnBnClickedApp()
{
	// TODO: Add your control notification handler code here
	CDaoDatabase db2;
	CDaoRecordset recset2(&db2);
	CString v_no_village,V_nom,P_nom;
	GetDlgItemText(IDC_NO_VILLAGE,v_no_village);
//	GetDlgItemText(IDC_CODEPAYS, Pcode);
	GetDlgItemText(IDC_NOMVILLAGE,V_nom);
//	GetDlgItemText(IDC_CODECONTINENT, Ccode);
	 CComboBox* ComboCon = (CComboBox*)GetDlgItem(IDC_NOMP);
    int indexContinent = ComboCon->GetCurSel();
    ComboCon->GetLBText(indexContinent,P_nom);

    int nTokenPos = 0;
    CString Pay = P_nom.Tokenize(_T(" : "), nTokenPos);
//	CString NomPay = P_nom.Tokenize(_T(" : "), nTokenPos);

	CString autoGeneratedVcode = V_nom.Left(3);

// Automatically generate continent code from the first three characters of the continent name
	CString lpszFile=L"GestionVillageVacance.mdb";
	db2.Open(lpszFile);
	/* // Récupérer l'ID du pays nouvellement ajouté
    CString Sqlcmdp = L"SELECT no_P FROM PAYS WHERE nomP = '" + NomPay + "'";
    recset2.Open(AFX_DAO_USE_DEFAULT_TYPE, Sqlcmdp, NULL);
   int p_no_pay = -1;  // Assuming it's an integer, initialize to a default value
COleVariant var;
var.ChangeType(VT_I4, NULL);  // Use VT_I4 for a 4-byte integer
recset2.GetFieldValue(L"no_P", var);
p_no_pay = var.lVal;
recset2.Close();
CString strPayID;
        strPayID.Format(L"%d", p_no_pay);*/
	CString SqlCmd = L"UPDATE VILLAGES SET nomV = '" + V_nom + "', codeV = '" + autoGeneratedVcode + "', no_P = " + Pay + " WHERE no_V = " + v_no_village + ";";
    db2.Execute(SqlCmd);
	db2.Close();
	recset2.Close();
	GetDlgItem(IDC_RECHERCHER)->SetWindowText(L"");
	GetDlgItem(IDC_codeVval)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_nomVval)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_nomPval)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_VILLAGES_UPDA)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CODEVILLAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_NOMVILLAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_NOMP)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_APP)->ShowWindow(SW_HIDE);
	RefreshList();
	AfxMessageBox(L"Les informations du Village "+V_nom+" \n a été mis à jour avec succès !",MB_ICONINFORMATION|MB_OK);

}


void CVillage::OnBnClickedVillagesUpda()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_NO_VILLAGE)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_codeVval)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_nomVval)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_nomPval)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_VILLAGES_UPDA)->ShowWindow(SW_HIDE);

//	GetDlgItem(IDC_CODEVILLAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_NOMVILLAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_NOMP)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_APP)->ShowWindow(SW_SHOW);
}
