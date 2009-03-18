// lilashapeDlg.h: archivo de encabezado
//

#pragma once
#include "shockwaveflash1.h"
# include "Serial/SerialMFC.h"

// Cuadro de diálogo de ClilashapeDlg
class ClilashapeDlg : public CDialog
{
// Construcción
public:
	ClilashapeDlg(CWnd* pParent = NULL);	// Constructor estándar

// Datos del cuadro de diálogo
	enum { IDD = IDD_LILASHAPE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Compatibilidad con DDX/DDV

	CSerialMFC		m_serial;
// Implementación
protected:
	HICON m_hIcon;

	// Funciones de asignación de mensajes generadas
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CShockwaveflash1 m_SFPelicula;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_EVENTSINK_MAP()
	void FSCommandShockwaveflash1(LPCTSTR command, LPCTSTR args);
	afx_msg LRESULT OnSerialMsg (WPARAM wParam, LPARAM lParam);
	void DisplayEvent (LPCTSTR lpszMsg);
	void DisplayEventSetting (LPCTSTR lpszMsg, LPCTSTR lpszSetting, bool fOn);
	void ParseData(char data);
	afx_msg void OnDestroy();
	char m_cDispositivo;
	char m_cIR;
	char m_cRF;
	char m_cVacio;
	char m_cEstado;
};
