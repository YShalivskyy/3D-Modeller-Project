// mainTable.h : Declaration of the CmainTable

#pragma once

// code generated on Monday, April 25, 2016, 12:08 AM

class CmainTable : public CRecordset
{
public:
	CmainTable(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CmainTable)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	float	m_topRadius;
	float	m_botRadius;
	float	m_height;
	long	m_dotNumber;
	float	m_side;
	float	m_ColorR;
	float	m_ColorG;
	float	m_ColorB;
	long	m_ID;
	float	m_CenterX;
	float	m_CenterY;
	float	m_CenterZ;
	float	m_angleX;
	float	m_angleY;
	float	m_angleZ;
	long	m_typeShape;

// Overrides
	// Wizard generated virtual function overrides
	public:
	virtual CString GetDefaultConnect();	// Default connection string

	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


