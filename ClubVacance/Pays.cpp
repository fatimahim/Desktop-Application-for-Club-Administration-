// Pays.cpp : implementation file
//

#include "stdafx.h"
#include "ClubVacance.h"
#include "Pays.h"
#include "afxdialogex.h"
#include <afxdao.h>


CDaoDatabase db1;
CDaoRecordset recset1(&db1);

// CPays dialog

IMPLEMENT_DYNAMIC(CPays, CDialogEx)

CPays::CPays(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPays::IDD, pParent)
{
	m_add = AfxGetApp()->LoadIcon(IDI_ICON12);
	m_del= AfxGetApp()->LoadIcon(IDI_ICON12);
	m_up= AfxGetApp()->LoadIcon(IDI_ICON15);
	m_delA= AfxGetApp()->LoadIcon(IDI_ICON16);
	Create(IDD_PaysView, pParent);
	 
}

CPays::~CPays()
{
}

void CPays::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PAYS_LIST, PaysList);
	DDX_Control(pDX, IDC_PAYS_NOM, PaysNom);
	DDX_Control(pDX, IDC_CON, Continent);
	DDX_Control(pDX, IDC_RECHERCHER, Prechercher);
	DDX_Control(pDX, IDC_PAYS_AJOUT, CAdd); 
	DDX_Control(pDX, IDC_PAYS_AJOUT2, CAdd2); 
	DDX_Control(pDX, IDC_Continents_UPDA, up2); 
	DDX_Control(pDX, IDC_PAYS_UPDA, up);
	DDX_Control(pDX, IDC_PAY_SUPP, del);
	DDX_Control(pDX, IDC_Continent_SUPP, del2);
	DDX_Control(pDX, IDC_PAYS_SUPP, delA);
	DDX_Control(pDX, IDC_Continents_SUPP, delA2);
	
}


BEGIN_MESSAGE_MAP(CPays, CDialogEx)
	ON_BN_CLICKED(IDC_PAYS_AJOUT, &CPays::OnBnClickedPaysAjout)
	ON_EN_CHANGE(IDC_VILLAGE_NOM, &CPays::OnEnChangeVillageNom)
	ON_EN_CHANGE(IDC_RECHERCHER, &CPays::OnEnChangeRechercher)
	ON_BN_CLICKED(IDC_PAY_SUPP, &CPays::OnBnClickedPaySupp)
	ON_EN_CHANGE(IDC_PAYS_NOM, &CPays::OnEnChangePaysNom)
	ON_CBN_SELCHANGE(IDC_CON, &CPays::OnCbnSelchangeCon)
	ON_BN_CLICKED(IDC_APP, &CPays::OnBnClickedApp)
	ON_BN_CLICKED(IDC_PAYS_UPDA, &CPays::OnBnClickedPaysUpda)
	ON_BN_CLICKED(IDC_PAYS_AJOUT2, &CPays::OnBnClickedPaysAjout2)
	ON_EN_CHANGE(IDC_RECHERCHER2, &CPays::OnEnChangeRechercher2)
	ON_BN_CLICKED(IDC_Continent_SUPP, &CPays::OnBnClickedContinentSupp)
	ON_BN_CLICKED(IDC_APP2, &CPays::OnBnClickedApp2)
	ON_BN_CLICKED(IDC_Continents_UPDA, &CPays::OnBnClickedContinentsUpda)
	ON_BN_CLICKED(IDC_PAYS_SUPP, &CPays::OnBnClickedPaysSupp)
	ON_EN_CHANGE(IDC_Continent_Nom, &CPays::OnEnChangeContinentNom)
END_MESSAGE_MAP()


// CPays message handlers
BOOL CPays::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	PaysList.InsertColumn(0,L"N°",LVCFMT_LEFT,30,-1);
	PaysList.InsertColumn(1,L"Code",LVCFMT_LEFT,50,-1);
	PaysList.InsertColumn(2,L"Nom de Pays",LVCFMT_LEFT,140,-1);
	PaysList.InsertColumn(3,L"Code ",LVCFMT_LEFT,50,-1);
	PaysList.InsertColumn(4,L"Continent",LVCFMT_LEFT,140,-1);
	ListView_SetExtendedListViewStyle( PaysList,LVS_EX_GRIDLINES);

	PaysNom.SetCueBanner(L"Nom de Pays");
	Prechercher.SetCueBanner(L"Rechercher");
	Continent.SetCueBanner(L"Continents");
	RefreshList();
	PaysId = L"-1";

	GetDlgItem(IDC_CODEPAYS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_NOMPAYS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CODECONTINENT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CON2)->ShowWindow(SW_HIDE);

    GetDlgItem(IDC_nomConval)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_APP)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_APP2)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_PAY_SUPP)->EnableWindow(FALSE);			
	GetDlgItem(IDC_PAYS_UPDA)->EnableWindow(FALSE);
	GetDlgItem(IDC_PAYS_AJOUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_PAYS_AJOUT2)->EnableWindow(FALSE);


	GetDlgItem(IDC_CODEPAYS)->EnableWindow(FALSE);
	GetDlgItem(IDC_NOMPAYS)->EnableWindow(FALSE);
	GetDlgItem(IDC_CODECONTINENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_CON2)->EnableWindow(FALSE);
	CAdd.SetIcon(m_add);
	CAdd2.SetIcon(m_add);
	del.SetIcon(m_del);
	del2.SetIcon(m_del);
	delA.SetIcon(m_delA);
	delA2.SetIcon(m_delA);
	//app.SetIcon(m_app);
	up.SetIcon(m_up);
	up2.SetIcon(m_up);
	/*GetDlgItem(8888)->GetWindowRect(rc);
	ScreenToClient(&rc);*/
	return TRUE;
}
void CPays::SetOptions(){
	CComboBox *ComboCon=(CComboBox*)GetDlgItem(IDC_CON);
	ComboCon->ResetContent();
	COleVariant	var;
	var.ChangeType(VT_BSTR, NULL);
	CString lpszFile=L"GestionVillageVacance.mdb";
	db1.Open(lpszFile); 
	CString SqlCmd=L"SELECT no_Con,nomCon FROM CONTINENTS";
	recset1.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCmd,NULL);
	CString V_no, V_nom;	
	while(!recset1.IsEOF())
	{
		recset1.GetFieldValue(0, var);
		V_no.Format(L"%d",(LPCWSTR)var.pbstrVal);
		recset1.GetFieldValue(1, var);
		V_nom = (LPCWSTR)var.pbstrVal;

		ComboCon->AddString(V_no+L" : "+V_nom);
		recset1.MoveNext();
	}
	recset1.Close();

	CComboBox *ComboCon2=(CComboBox*)GetDlgItem(IDC_CON2);
	ComboCon2->ResetContent();
	COleVariant	var1;
	var1.ChangeType(VT_BSTR, NULL);
	CString SqlCmco=L"SELECT no_Con,nomCon FROM CONTINENTS";
	recset1.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCmco,NULL);
	CString V_no1, V_nom1;	
	while(!recset1.IsEOF())
	{
		recset1.GetFieldValue(0, var1);
		V_no1.Format(L"%d",(LPCWSTR)var1.pbstrVal);
		recset1.GetFieldValue(1, var1);
		V_nom1 = (LPCWSTR)var1.pbstrVal;

		ComboCon2->AddString(V_no1+L" : "+V_nom1);
		recset1.MoveNext();
	}
	recset1.Close();
	db1.Close();
}
void CPays::OnBnClickedPaysAjout()
{CDaoDatabase db;
CDaoRecordset recset(&db);
CString lpszFile = L"GestionVillageVacance.mdb";

try {
    db.Open(lpszFile);

    CString P_nom, C_nom;

    GetDlgItemText(IDC_PAYS_NOM, P_nom);
    CComboBox* ComboCon = (CComboBox*)GetDlgItem(IDC_CON);
    int indexContinent = ComboCon->GetCurSel();
    ComboCon->GetLBText(indexContinent, C_nom);

    int nTokenPos = 0;
    CString Con = C_nom.Tokenize(_T(" : "), nTokenPos);
	CString NomCon = C_nom.Tokenize(_T(" : "), nTokenPos);
	// Récupérer l'ID du continent nouvellement ajouté
    CString Sqlcmdco = L"SELECT no_Con FROM CONTINENTS WHERE nomCon = '" + NomCon + "'";
    recset.Open(AFX_DAO_USE_DEFAULT_TYPE, Sqlcmdco, NULL);
   int c_no_co = -1;  // Assuming it's an integer, initialize to a default value
COleVariant var;
var.ChangeType(VT_I4, NULL);  // Use VT_I4 for a 4-byte integer
recset.GetFieldValue(L"no_Con", var);
c_no_co = var.lVal;
recset.Close();
    // Ajouter un nouveau pays
recset.Open(AFX_DAO_USE_DEFAULT_TYPE, L"SELECT * FROM PAYS", NULL);
    recset.AddNew();
    recset.SetFieldValue(L"nomP", (LPCWSTR)P_nom);
	CString codeP = P_nom.Left(3);
    recset.SetFieldValue(L"codeP", (LPCWSTR)codeP);
    recset.SetFieldValue(L"no_Con", (short)(c_no_co)); // Assurez-vous du type correct
    recset.Update();
    recset.Close();

    // Clear text fields
    GetDlgItem(IDC_PAYS_NOM)->SetWindowText(L"");
    GetDlgItem(IDC_CON)->SetWindowText(L"");

    AfxMessageBox(L"Le Pays " + P_nom + L" a été ajouté avec succès !", MB_ICONINFORMATION | MB_OK);

    RefreshList(); // Si RefreshList() est une fonction définie ailleurs dans votre code
}
catch (CDaoException* e) {
    // Gérer les exceptions DAO ici (par exemple, afficher un message d'erreur)
    e->ReportError();
    e->Delete();
}
db.Close();

}


void CPays::OnEnChangeVillageNom()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
void CPays::RefreshList(){
CDaoDatabase db;
	CDaoRecordset recset(&db);
	COleVariant var;  // Start Variables
	var.ChangeType(VT_BSTR, NULL);
	CString p_no_Pay,P_nom,C_nom,Pcode,Ccode; // End Variables
	PaysList.DeleteAllItems(); // Clear List
	CString lpszFile=L"GestionVillageVacance.mdb";
	db.Open(lpszFile); // Open Clients.MDB
	CString SqlCmd=L"SELECT no_P,nomP,nomCon,codeP,codeCon FROM PAYS INNER JOIN CONTINENTS ON PAYS.no_Con=CONTINENTS.no_Con order by 1 desc";
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCmd,NULL);
	while(!recset.IsEOF()) // Do until EOF
	{
		int i = 0;	
		recset.GetFieldValue(L"no_P",var);
		p_no_Pay.Format(L"%d",(LPCWSTR)var.pbstrVal);
		PaysList.InsertItem(i,p_no_Pay,0);
		recset.GetFieldValue(L"codeP",var);
		Pcode = (LPCWSTR)var.pbstrVal;
		PaysList.SetItemText(i,1,Pcode);
		recset.GetFieldValue(L"nomP",var);
		P_nom = (LPCWSTR)var.pbstrVal;
		PaysList.SetItemText(i,2,P_nom);	
		recset.GetFieldValue(L"codeCon",var);		
		Ccode = (LPCWSTR)var.pbstrVal;
		PaysList.SetItemText(i,3,Ccode);
		recset.GetFieldValue(L"nomCon",var);		
		C_nom = (LPCWSTR)var.pbstrVal;
		PaysList.SetItemText(i,4,C_nom);		
		i++;		
		recset.MoveNext();
	}	
	recset.Close();

        CString SqlCmc = L"SELECT nomCon FROM CONTINENTS";
        recset.Open(AFX_DAO_USE_DEFAULT_TYPE, SqlCmc, NULL);

        // Clear the existing list before populating it
        ConsList.clear();

        while (!recset.IsEOF()) {
            COleVariant var;
            recset.GetFieldValue(L"nomCon", var);
            ConsList.push_back(var.bstrVal);

            recset.MoveNext(); }
		 recset.Close();
	db.Close();
	SetOptions();
}

bool CPays::contains(CString mystring,CString arg){
	bool yes = true;
	int i;
	for(i=0;i<arg.GetLength() && yes;i++){
		if(mystring[i] != arg[i])
			return false;
	}
	return true;
}
void CPays::OnEnChangeRechercher()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString var;	
	int i=0;
	for(i=0;i<PaysList.GetItemCount();i++){
		GetDlgItemText(IDC_RECHERCHER,var);
		if(var != L""){
			if( contains(PaysList.GetItemText(i,0),var) || contains(PaysList.GetItemText(i,1),var) || contains(PaysList.GetItemText(i,2),var) || contains(PaysList.GetItemText(i,3),var)|| contains(PaysList.GetItemText(i,4),var)){
				GetDlgItem(IDC_NO_PAY)->SetWindowText(PaysList.GetItemText(i,0));
				GetDlgItem(IDC_codePval)->SetWindowText(PaysList.GetItemText(i,1));
				GetDlgItem(IDC_nomPval)->SetWindowText(PaysList.GetItemText(i,2));
				GetDlgItem(IDC_codeCval)->SetWindowText(PaysList.GetItemText(i,3));
				GetDlgItem(IDC_nomCval)->SetWindowText(PaysList.GetItemText(i,4));

				GetDlgItem(IDC_CODEPAYS)->EnableWindow();
				GetDlgItem(IDC_NOMPAYS)->EnableWindow();
				GetDlgItem(IDC_CODECONTINENT)->EnableWindow();
				GetDlgItem(IDC_CON2)->EnableWindow();

				GetDlgItem(IDC_CODEPAYS)->SetWindowText(PaysList.GetItemText(i,1));
				GetDlgItem(IDC_NOMPAYS)->SetWindowText(PaysList.GetItemText(i,2));
				GetDlgItem(IDC_CODECONTINENT)->SetWindowText(PaysList.GetItemText(i,3));
				GetDlgItem(IDC_CON2)->SetWindowText(PaysList.GetItemText(i,4));

				GetDlgItem(IDC_PAY_SUPP)->EnableWindow();
				GetDlgItem(IDC_PAYS_UPDA)->EnableWindow();
				PaysId = PaysList.GetItemText(i,0);
				break;
			}else{
				GetDlgItem(IDC_NO_PAY)->SetWindowText(L"Aucun client");
				GetDlgItem(IDC_codePval)->SetWindowText(L"Aucun client");
				GetDlgItem(IDC_nomPval)->SetWindowText(L"Aucun client");
				GetDlgItem(IDC_codeCval)->SetWindowText(L"Aucun client");
				GetDlgItem(IDC_nomCval)->SetWindowText(L"Aucun client");

				GetDlgItem(IDC_CODEPAYS)->SetWindowText(L"");
				GetDlgItem(IDC_NOMPAYS)->SetWindowText(L"");
				GetDlgItem(IDC_CODECONTINENT)->SetWindowText(L"");
				GetDlgItem(IDC_CON2)->SetWindowText(L"");

				GetDlgItem(IDC_CODEPAYS)->EnableWindow(FALSE);
				GetDlgItem(IDC_NOMPAYS)->EnableWindow(FALSE);
				GetDlgItem(IDC_CODECONTINENT)->EnableWindow(FALSE);
				GetDlgItem(IDC_CON2)->EnableWindow(FALSE);

				GetDlgItem(IDC_PAY_SUPP)->EnableWindow(FALSE);			
				GetDlgItem(IDC_PAYS_UPDA)->EnableWindow(FALSE);

				PaysId = L"-1";
			}
		}else{
			
			GetDlgItem(IDC_NO_PAY)->SetWindowText(L"");
			GetDlgItem(IDC_codePval)->SetWindowText(L"");
			GetDlgItem(IDC_nomPval)->SetWindowText(L"");
			GetDlgItem(IDC_codeCval)->SetWindowText(L"");
			GetDlgItem(IDC_nomCval)->SetWindowText(L"");

			GetDlgItem(IDC_CODEPAYS)->SetWindowText(L"");
			GetDlgItem(IDC_NOMPAYS)->SetWindowText(L"");
			GetDlgItem(IDC_CODECONTINENT)->SetWindowText(L"");
			GetDlgItem(IDC_CON2)->SetWindowText(L"");

			GetDlgItem(IDC_CODEPAYS)->EnableWindow(FALSE);
			GetDlgItem(IDC_NOMPAYS)->EnableWindow(FALSE);
			GetDlgItem(IDC_CODECONTINENT)->EnableWindow(FALSE);
			GetDlgItem(IDC_CON2)->EnableWindow(FALSE);

			GetDlgItem(IDC_PAY_SUPP)->EnableWindow(FALSE);
			GetDlgItem(IDC_PAYS_UPDA)->EnableWindow(FALSE);

			PaysId = L"-1";
		}
	}	
}


void CPays::OnBnClickedPaySupp()
{
	try {

	// TODO: Add your control notification handler code here
	CDaoDatabase db1;
	CDaoRecordset recset1(&db1);
	CString lpszFile=L"GestionVillageVacance.mdb";
	db1.Open(lpszFile);
 // Step 1: Delete associated records in VILLAGES_ACTIVITIES
    CString sqlDeleteActivities = L"DELETE FROM VILLAGES_ACTIVITIES WHERE no_V IN (SELECT no_V FROM VILLAGES WHERE no_P = " + PaysId + ");";
    db1.Execute(sqlDeleteActivities);

    // Step 2: Delete associated records in VILLAGES_LANGUES
    CString sqlDeleteLanguages = L"DELETE FROM VILLAGES_LANGUES WHERE no_V IN (SELECT no_V FROM VILLAGES WHERE no_P = " +  PaysId + ");";
    db1.Execute(sqlDeleteLanguages);

    // Step 3: Delete associated records in VILLAGES
    CString sqlDeleteVillages = L"DELETE FROM VILLAGES WHERE no_P = " + PaysId + ";";
    db1.Execute(sqlDeleteVillages);

    // Step 4: Delete the country
    CString sqlDeleteCountry = L"DELETE FROM PAYS WHERE no_P = " +  PaysId + ";";
    db1.Execute(sqlDeleteCountry);



	recset1.Close();
	GetDlgItem(IDC_RECHERCHER)->SetWindowText(L"");
	 RefreshList();
	 AfxMessageBox(L"Le pays a été supprimé \navec succès !",MB_ICONINFORMATION|MB_OK);}
	catch (CDaoException* e) {
    // Handle exceptions, e.g., display an error message
    e->ReportError();
    e->Delete();
}
	db1.Close();
}




void CPays::OnEnChangePaysNom()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
		
}
bool CPays::pasvide(){
	CString var0,var1,var2,var3;
	//GetDlgItemText(IDC_NUM,var0);
	GetDlgItemText(IDC_PAYS_NOM,var1);
	GetDlgItemText(IDC_CON,var2);
	if(var1 == "" || var2 == "" )
		return false;
	else if(var1 != "" && var2 != "" )
		return true;

	return true;
}

void CPays::OnCbnSelchangeCon()
{
	// TODO: Add your control notification handler code here
	if(pasvide())
		GetDlgItem(IDC_PAYS_AJOUT)->EnableWindow(TRUE);
	else
		GetDlgItem(IDC_PAYS_AJOUT)->EnableWindow(FALSE);
}


void CPays::OnBnClickedApp()
{
	
	CDaoDatabase db2;
	CDaoRecordset recset2(&db2);
	CString p_no_Pay,P_nom,C_nom,Pcode,Ccode;
	GetDlgItemText(IDC_NO_PAY,p_no_Pay);
//	GetDlgItemText(IDC_CODEPAYS, Pcode);
	GetDlgItemText(IDC_NOMPAYS,P_nom);
//	GetDlgItemText(IDC_CODECONTINENT, Ccode);
	 CComboBox* ComboCon = (CComboBox*)GetDlgItem(IDC_CON2);
    int indexContinent = ComboCon->GetCurSel();
    ComboCon->GetLBText(indexContinent,C_nom);

    int nTokenPos = 0;
    CString Con = C_nom.Tokenize(_T(" : "), nTokenPos);
	CString NomCon = C_nom.Tokenize(_T(" : "), nTokenPos);

	CString autoGeneratedPcode = P_nom.Left(3);

// Automatically generate continent code from the first three characters of the continent name
   CString autoGeneratedCcode = NomCon.Left(3);
	CString lpszFile=L"GestionVillageVacance.mdb";
	db2.Open(lpszFile);
	/*// Récupérer l'ID du continent nouvellement ajouté
    CString Sqlcmdco = L"SELECT no_Con FROM CONTINENTS WHERE nomCon = '" + NomCon + "'";
    recset2.Open(AFX_DAO_USE_DEFAULT_TYPE, Sqlcmdco, NULL);
   int c_no_co = -1;  // Assuming it's an integer, initialize to a default value
COleVariant var;
var.ChangeType(VT_I4, NULL);  // Use VT_I4 for a 4-byte integer
recset2.GetFieldValue(L"no_Con", var);
c_no_co = var.lVal;
recset2.Close();
CString strContinentID;
        strContinentID.Format(L"%d", c_no_co);*/
	CString SqlCmd = L"UPDATE PAYS SET nomP = '" + P_nom + "', codeP = '" + autoGeneratedPcode + "', no_Con = " + Con + " WHERE no_P = " + p_no_Pay + ";";
    db2.Execute(SqlCmd);
	db2.Close();
	recset2.Close();
	GetDlgItem(IDC_RECHERCHER)->SetWindowText(L"");
	GetDlgItem(IDC_codePval)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_nomPval)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_codeCval)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_nomCval)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_PAYS_UPDA)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CODEPAYS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_NOMPAYS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CODECONTINENT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CON2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_APP)->ShowWindow(SW_HIDE);
	RefreshList();
	AfxMessageBox(L"Les informations du Pays "+P_nom+" \n a été mis à jour avec succès !",MB_ICONINFORMATION|MB_OK);
}


void CPays::OnBnClickedPaysUpda()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_NO_PAY)->ShowWindow(SW_HIDE);
//	GetDlgItem(IDC_codePval)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_nomPval)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_codeCval)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_nomCval)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_PAYS_UPDA)->ShowWindow(SW_HIDE);

//	GetDlgItem(IDC_CODEPAYS)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_NOMPAYS)->ShowWindow(SW_SHOW);
//	GetDlgItem(IDC_CODECONTINENT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CON2)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_APP)->ShowWindow(SW_SHOW);
}


void CPays::OnBnClickedPaysAjout2()
{
	// TODO: Add your control notification handler code here
	CDaoDatabase db;
CDaoRecordset recset(&db);
CString lpszFile = L"GestionVillageVacance.mdb";

try {
    db.Open(lpszFile);
    recset.Open(AFX_DAO_USE_DEFAULT_TYPE, L"SELECT * FROM CONTINENTS", NULL);

    CString  C_nom;

    GetDlgItemText(IDC_Continent_Nom, C_nom);
    // Ajouter un nouveau pays
    recset.AddNew();
    recset.SetFieldValue(L"nomCon", (LPCWSTR)C_nom);
	CString codeC = C_nom.Left(3);
    recset.SetFieldValue(L"codeCon", (LPCWSTR)codeC);
    recset.Update();
    recset.Close();

    // Clear text fields
    GetDlgItem(IDC_Continent_Nom)->SetWindowText(L"");

    AfxMessageBox(L"La Continents" + C_nom + L" a été ajouté avec succès !", MB_ICONINFORMATION | MB_OK);

    RefreshList(); // Si RefreshList() est une fonction définie ailleurs dans votre code
	GetDlgItem(IDC_Continent_Nom)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_Continent_Nom)->ShowWindow(SW_SHOW);
}
catch (CDaoException* e) {
    // Gérer les exceptions DAO ici (par exemple, afficher un message d'erreur)
    e->ReportError();
    e->Delete();
}
db.Close();
}


void CPays::OnEnChangeRechercher2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// TODO:  Add your control notification handler code here
	CString searchTerm;
    GetDlgItemText(IDC_RECHERCHER2, searchTerm);

    if (!searchTerm.IsEmpty()) {
        bool found = false;
        for (int i = 0; i < ConsList.size(); i++) {
            if (contains(ConsList[i], searchTerm)) {
                // Update UI elements when the search term is found
                GetDlgItem(IDC_nomConval)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_Continent_Nom)->ShowWindow(SW_HIDE);
                GetDlgItem(IDC_nomConval)->SetWindowText(ConsList[i]);

                GetDlgItem(IDC_Continent_Nom)->EnableWindow();
                GetDlgItem(IDC_Continent_Nom)->SetWindowText(ConsList[i]);

                GetDlgItem(IDC_Continent_SUPP)->EnableWindow();
                GetDlgItem(IDC_Continents_UPDA)->EnableWindow();
       //         ConId = ;

                found = true;
                break;
            }
        }

        if (!found) {
            // Update UI elements when the search term is not found
            GetDlgItem(IDC_nomConval)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_Continent_Nom)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_nomConval)->SetWindowText(L"Aucun Continents");

            GetDlgItem(IDC_Continent_Nom)->SetWindowText(L"");
            GetDlgItem(IDC_Continent_Nom)->EnableWindow(FALSE);

            GetDlgItem(IDC_Continent_SUPP)->EnableWindow(FALSE);
            GetDlgItem(IDC_Continents_UPDA)->EnableWindow(FALSE);

            ConId = L"-1";
        }
    } else {
        // Reset UI elements when the search term is empty
        GetDlgItem(IDC_nomConval)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_Continent_Nom)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_nomConval)->SetWindowText(L"");

     //   GetDlgItem(IDC_Continent_Nom)->SetWindowText(L"");
       // GetDlgItem(IDC_Continent_Nom)->EnableWindow(FALSE);

        GetDlgItem(IDC_Continent_SUPP)->EnableWindow(FALSE);
        GetDlgItem(IDC_Continents_UPDA)->EnableWindow(FALSE);

        ConId = L"-1";
    }

}


void CPays::OnBnClickedContinentSupp()
{
	// TODO: Add your control notification handler code here
   try {CDaoDatabase db;
        CDaoRecordset recset(&db);

        CString lpszFile = L"GestionVillageVacance.mdb";
        db.Open(lpszFile);

        // Step 0: Get the continent name from the static control or wherever it is stored
        CString continentName;  // Replace this with the actual way you get the continent name
        GetDlgItemText(IDC_nomConval, continentName);

        // Step 1: Delete associated records in VILLAGES_ACTIVITIES
        CString sqlDeleteActivities = L"DELETE FROM VILLAGES_ACTIVITIES WHERE no_V IN (SELECT no_V FROM VILLAGES WHERE no_P IN (SELECT no_P FROM PAYS WHERE no_Con IN (SELECT no_Con FROM CONTINENTS WHERE nomCon = '" + continentName + "')))";
        db.Execute(sqlDeleteActivities);

        // Step 2: Delete associated records in VILLAGES_LANGUES
        CString sqlDeleteLanguages = L"DELETE FROM VILLAGES_LANGUES WHERE no_V IN (SELECT no_V FROM VILLAGES WHERE no_P IN (SELECT no_P FROM PAYS WHERE no_Con IN (SELECT no_Con FROM CONTINENTS WHERE nomCon = '" + continentName + "')))";
        db.Execute(sqlDeleteLanguages);

        // Step 3: Delete associated records in VILLAGES
        CString sqlDeleteVillages = L"DELETE FROM VILLAGES WHERE no_P IN (SELECT no_P FROM PAYS WHERE no_Con IN (SELECT no_Con FROM CONTINENTS WHERE nomCon = '" + continentName + "'))";
        db.Execute(sqlDeleteVillages);

        // Step 4: Delete associated records in PAYS
        CString sqlDeleteCountries = L"DELETE FROM PAYS WHERE no_Con IN (SELECT no_Con FROM CONTINENTS WHERE nomCon = '" + continentName + "')";
        db.Execute(sqlDeleteCountries);

        // Step 5: Delete the continent
        CString sqlDeleteContinent = L"DELETE FROM CONTINENTS WHERE nomCon = '" + continentName + "'";
        db.Execute(sqlDeleteContinent);

        db.Close();
		RefreshList();
		GetDlgItem(IDC_Continent_Nom)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RECHERCHER2)->SetWindowText(L"");
		GetDlgItem(IDC_Continent_Nom)->SetWindowText(L"");
		GetDlgItem(IDC_nomConval)->ShowWindow(SW_HIDE);
        // Optionally, update your UI or show a message indicating success
        AfxMessageBox(L"Le continent et ses pays associés ont été supprimés avec succès !", MB_ICONINFORMATION | MB_OK);
    }
    catch (CDaoException* e) {
        // Handle exceptions, e.g., display an error message
        e->ReportError();
        e->Delete();
    }

}


void CPays::OnBnClickedApp2()
{
	// TODO: Add your control notification handler code here
	CDaoDatabase db2;
	CDaoRecordset recset2(&db2);
	CString Connom,Cnom;	
	GetDlgItemText(IDC_Continent_Nom,Connom);
	GetDlgItemText(IDC_nomConval,Cnom);
	 CString autoGeneratedCcode = Connom.Left(3);
	CString lpszFile=L"GestionVillageVacance.mdb";
	db2.Open(lpszFile);
	// Récupérer l'ID du continent nouvellement ajouté
        CString Sqlcmdco = L"SELECT no_Con FROM CONTINENTS WHERE nomCon = '" + Cnom + "'";
        recset2.Open(AFX_DAO_USE_DEFAULT_TYPE, Sqlcmdco, NULL);
        int c_no_co = -1;  // Assuming it's an integer, initialize to a default value
        COleVariant var;
        var.ChangeType(VT_I4, NULL);  // Use VT_I4 for a 4-byte integer
        recset2.GetFieldValue(L"no_Con", var);
        c_no_co = var.lVal;
        recset2.Close();
		CString strContinentID;
        strContinentID.Format(L"%d", c_no_co);
	CString SqlCmd=L"UPDATE CONTINENTS SET nomCon = '"+Connom+"', codeCon = '"+autoGeneratedCcode+"' WHERE no_Con = "+strContinentID+";";
	db2.Execute(SqlCmd);
	db2.Close();
	recset2.Close();
	 GetDlgItem(IDC_RECHERCHER2)->SetWindowText(L"");
  //  GetDlgItem(IDC_nomConval)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_Continents_UPDA)->ShowWindow(SW_SHOW);
   // GetDlgItem(IDC_NOMCONTINENT)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_APP2)->ShowWindow(SW_HIDE);

    // Actualiser la liste ou effectuer d'autres actions nécessaires
    RefreshList();
	 AfxMessageBox(L"Les informations du continent " + Connom + L" ont été mises à jour avec succès !", MB_ICONINFORMATION | MB_OK);

}

void CPays::OnBnClickedContinentsUpda()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_nomConval)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_Continents_UPDA)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_Continent_Nom)->ShowWindow(SW_SHOW);


	GetDlgItem(IDC_APP2)->ShowWindow(SW_SHOW);
}


void CPays::OnBnClickedPaysSupp()
{
	// TODO: Add your control notification handler code here
}


void CPays::OnEnChangeContinentNom()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	GetDlgItem(IDC_PAYS_AJOUT2)->EnableWindow(TRUE);
}
