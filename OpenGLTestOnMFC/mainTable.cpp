// mainTable.h : Implementation of the CmainTable class



// CmainTable implementation

// code generated on Monday, April 25, 2016, 12:08 AM

#include "stdafx.h"
#include "mainTable.h"
IMPLEMENT_DYNAMIC(CmainTable, CRecordset)

CmainTable::CmainTable(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_topRadius = 0.0;
	m_botRadius = 0.0;
	m_height = 0.0;
	m_dotNumber = 0;
	m_side = 0.0;
	m_ColorR = 0.0;
	m_ColorG = 0.0;
	m_ColorB = 0.0;
	m_ID = 0;
	m_CenterX = 0.0;
	m_CenterY = 0.0;
	m_CenterZ = 0.0;
	m_angleX = 0.0;
	m_angleY = 0.0;
	m_angleZ = 0.0;
	m_typeShape = 0;
	m_nFields = 16;
	m_nDefaultType = dynaset;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CmainTable::GetDefaultConnect()
{
	return _T("DSN=DataSource;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2015;WSID=YARIK;DATABASE=model;");
}

CString CmainTable::GetDefaultSQL()
{
	return _T("[dbo].[mainTable]");
}

void CmainTable::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Single(pFX, _T("[topRadius]"), m_topRadius);
	RFX_Single(pFX, _T("[botRadius]"), m_botRadius);
	RFX_Single(pFX, _T("[height]"), m_height);
	RFX_Long(pFX, _T("[dotNumber]"), m_dotNumber);
	RFX_Single(pFX, _T("[side]"), m_side);
	RFX_Single(pFX, _T("[ColorR]"), m_ColorR);
	RFX_Single(pFX, _T("[ColorG]"), m_ColorG);
	RFX_Single(pFX, _T("[ColorB]"), m_ColorB);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Single(pFX, _T("[CenterX]"), m_CenterX);
	RFX_Single(pFX, _T("[CenterY]"), m_CenterY);
	RFX_Single(pFX, _T("[CenterZ]"), m_CenterZ);
	RFX_Single(pFX, _T("[angleX]"), m_angleX);
	RFX_Single(pFX, _T("[angleY]"), m_angleY);
	RFX_Single(pFX, _T("[angleZ]"), m_angleZ);
	RFX_Long(pFX, _T("[typeShape]"), m_typeShape);

}
/////////////////////////////////////////////////////////////////////////////
// CmainTable diagnostics

#ifdef _DEBUG
void CmainTable::AssertValid() const
{
	CRecordset::AssertValid();
}

void CmainTable::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


