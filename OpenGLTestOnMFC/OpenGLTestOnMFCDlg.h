
// OpenGLTestOnMFCDlg.h : header file
//

#pragma once

#include "OpenGLControl.h"
//#include "DialogControl.h"
#include "afxwin.h"
#include "afxcmn.h"

// COpenGLTestOnMFCDlg dialog
class COpenGLTestOnMFCDlg : public CDialog
{
// Construction
public:
	COpenGLTestOnMFCDlg(CWnd* pParent = NULL);	// standard constructor



// Dialog Data
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPENGLTESTONMFC_DIALOG };
//#endif // AFX_DESIGN_TIME
//
//	

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	COpenGLControl m_oglWindow;
	//DialogControl* m_dlgControl;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CButton m_drawButton;
	afx_msg void OnBnClickedDrawButton();
	CListBox m_colorList;
	afx_msg void OnLbnSelchangeColorList();
	CSliderCtrl m_scaleSlider;
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);

	CSliderCtrl m_angleXSlider;
	CSliderCtrl m_angleYSlider;
	CSliderCtrl m_angleZSlider;
	afx_msg void OnNMCustomdrawAngleSliderX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawAngleSliderY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawAngleSliderZ(NMHDR *pNMHDR, LRESULT *pResult);
	bool m_pickModeActivated;
	bool m_viewModeActivated;
	afx_msg void OnBnClickedPickRadio();
	afx_msg void OnBnClickedViewRadio();

	afx_msg void OnMarkRadio();
	afx_msg void OnNMCustomdrawTranslatezSlider(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_translateZSlider;
	afx_msg void OnBnClickedDrawPyramidButton();
	afx_msg void OnNMCustomdrawScaleXSlider(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_scaleXSlider;
	CSliderCtrl m_scaleYSlider;
	CSliderCtrl m_scaleZSlider;
	afx_msg void OnNMCustomdrawScaleYSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawScaleZSlider(NMHDR *pNMHDR, LRESULT *pResult);
	CButton m_saveButton;
	afx_msg void OnBnClickedSaveButton();
	CButton m_loadButton;
	afx_msg void OnBnClickedLoadButton();
};
