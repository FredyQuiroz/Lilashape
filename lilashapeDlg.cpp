// lilashapeDlg.cpp: archivo de implementación
//

#include "stdafx.h"
#include "lilashape.h"
#include "lilashapeDlg.h"
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Cuadro de diálogo CAboutDlg utilizado para el comando Acerca de

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Datos del cuadro de diálogo
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

// Implementación
protected:
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EPuerto;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EPUERTO, m_EPuerto);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()

void CAboutDlg::OnBnClickedOk()
{
	CString temp;
	m_EPuerto.GetWindowText(temp);
	if(temp.IsEmpty()) {

		MessageBox("Por favor ingrese un nombre del puerto por ejemplo 'COM1'");
		return; 
	}
	AfxGetApp()->WriteProfileString("configuracion", "puerto", temp);
	OnOK();
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_EPuerto.SetWindowText(AfxGetApp()->GetProfileString("configuracion", "puerto", "COM1"));
	return TRUE;
}

// Cuadro de diálogo de ClilashapeDlg


CString GetExeDir()
{
	char szPath[1024];
	GetModuleFileName(AfxGetApp()->m_hInstance, szPath, sizeof(szPath));

	char *ptr = strrchr(szPath, '\\');

	if (ptr)
	{
		ptr[1] = '\0';
	}

	ASSERT(strlen(szPath) < sizeof(szPath));

	return szPath;
}

ClilashapeDlg::ClilashapeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ClilashapeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_cDispositivo= 0;
	m_cIR= 0;
	m_cRF=0;
	m_cVacio=0;
	m_cEstado=0;
}

void ClilashapeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOCKWAVEFLASH1, m_SFPelicula);
}

BEGIN_MESSAGE_MAP(ClilashapeDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &ClilashapeDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ClilashapeDlg::OnBnClickedCancel)
	ON_WM_SIZE()
	ON_WM_SERIAL(OnSerialMsg)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// Controladores de mensaje de ClilashapeDlg

BOOL ClilashapeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Agregar el elemento de menú "Acerca de..." al menú del sistema.

	// IDM_ABOUTBOX debe estar en el intervalo de comandos del sistema.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Establecer el icono para este cuadro de diálogo. El marco de trabajo realiza esta operación
	//  automáticamente cuando la ventana principal de la aplicación no es un cuadro de diálogo
	SetIcon(m_hIcon, TRUE);			// Establecer icono grande
	SetIcon(m_hIcon, FALSE);		// Establecer icono pequeño

	CWnd *desktop=CWnd::GetDesktopWindow();
	CRect rect;
	desktop->GetWindowRect(rect);
	// aqui lo lanzamos a pantalla completa

#ifndef _DEBUG
	MoveWindow(rect);
#endif

	if (m_serial.Open(AfxGetApp()->GetProfileString("configuracion", "puerto", "COM1"),this) != ERROR_SUCCESS)
	{
		CAboutDlg dlgAbout;
		if(dlgAbout.DoModal()==IDOK && m_serial.Open(AfxGetApp()->GetProfileString("configuracion", "puerto", "COM1"),this) == ERROR_SUCCESS) {
			
		} else {
			AfxMessageBox(_T("No se puede abrir el puerto '"+AfxGetApp()->GetProfileString("configuracion", "puerto", "COM1") + "'"),MB_ICONSTOP|MB_OK);
			/*PostMessage(WM_CLOSE);
			return FALSE;*/
		}
	}

	m_SFPelicula.put_Movie(GetExeDir() + "lilashape.swf");

	return TRUE;  // Devuelve TRUE  a menos que establezca el foco en un control
}

void ClilashapeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// Si agrega un botón Minimizar al cuadro de diálogo, necesitará el siguiente código
//  para dibujar el icono. Para aplicaciones MFC que utilicen el modelo de documentos y vistas,
//  esta operación la realiza automáticamente el marco de trabajo.

void ClilashapeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Contexto de dispositivo para dibujo

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrar icono en el rectángulo de cliente
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dibujar el icono
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// El sistema llama a esta función para obtener el cursor que se muestra mientras el usuario arrastra
//  la ventana minimizada.
HCURSOR ClilashapeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void ClilashapeDlg::OnBnClickedOk()
{
	// OnOK();
}

void ClilashapeDlg::OnBnClickedCancel()
{
	OnCancel();
}

void ClilashapeDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	if(::IsWindow(m_SFPelicula)) 
		m_SFPelicula.MoveWindow(0,0,cx,cy);
}

BEGIN_EVENTSINK_MAP(ClilashapeDlg, CDialog)
	ON_EVENT(ClilashapeDlg, IDC_SHOCKWAVEFLASH1, 150, ClilashapeDlg::FSCommandShockwaveflash1, VTS_BSTR VTS_BSTR)
END_EVENTSINK_MAP()

# define LIMITE			5
# define PROGRESO_IR	16
# define PROGRESO_RF	32
# define PROGRESO_VACIO	48
# define ESTADO			80
# define DISPOSITIVO	64

void ClilashapeDlg::FSCommandShockwaveflash1(LPCTSTR command, LPCTSTR args)
{
	CString szCommand= command;
	CString szArgumentos= args;
	CByteArray mensaje;
	CString temp;

	if(szCommand=="up") {

		if(szArgumentos=="ir") {
			m_cIR++;
			if(m_cIR>LIMITE)
				m_cIR=0;
			mensaje.Add(PROGRESO_IR | m_cIR);
			temp.Format("%d", m_cIR);
			m_SFPelicula.SetVariable("_root.ir", temp);
			AfxGetApp()->WriteProfileInt(m_cDispositivo==2 ? "cuerpo" : "cara","ir", m_cIR);
		} else if(szArgumentos=="rf") {
			m_cRF++;
			if(m_cRF>LIMITE)
				m_cRF=0;
			mensaje.Add(PROGRESO_RF | m_cRF);
			temp.Format("%d", m_cRF);
			m_SFPelicula.SetVariable("_root.rf", temp);
			AfxGetApp()->WriteProfileInt(m_cDispositivo==2 ? "cuerpo" : "cara","rf", m_cRF);
		} else if(szArgumentos=="vacio") {
			m_cVacio++;
			if(m_cVacio>LIMITE)
				m_cVacio=0;
			mensaje.Add(PROGRESO_VACIO | m_cVacio);
			temp.Format("%d", m_cVacio);
			m_SFPelicula.SetVariable("_root.vacio", temp);
			AfxGetApp()->WriteProfileInt(m_cDispositivo==2 ? "cuerpo" : "cara","vacio", m_cVacio);
		}
	} else if(szCommand=="down") {
		if(szArgumentos=="ir") {
			m_cIR--;
			if(m_cIR<0)
				m_cIR=LIMITE;
			mensaje.Add(PROGRESO_IR | m_cIR);
			temp.Format("%d", m_cIR);
			m_SFPelicula.SetVariable("_root.ir", temp);
			AfxGetApp()->WriteProfileInt(m_cDispositivo==2 ? "cuerpo" : "cara","ir", m_cIR);
		} else if(szArgumentos=="rf") {
			m_cRF--;
			if(m_cRF<0)
				m_cRF=LIMITE;
			mensaje.Add(PROGRESO_RF | m_cIR);
			temp.Format("%d", m_cRF);
			m_SFPelicula.SetVariable("_root.rf", temp);
			AfxGetApp()->WriteProfileInt(m_cDispositivo==2 ? "cuerpo" : "cara","rf", m_cRF);
		} else if(szArgumentos=="vacio") {
			m_cVacio--;
			if(m_cVacio<0)
				m_cVacio=LIMITE;
			mensaje.Add(PROGRESO_VACIO | m_cVacio);
			temp.Format("%d", m_cVacio);
			m_SFPelicula.SetVariable("_root.vacio", temp);
			AfxGetApp()->WriteProfileInt(m_cDispositivo==2 ? "cuerpo" : "cara","vacio", m_cVacio);
		}
	} else if(szCommand=="start") {
		m_cEstado=1;
		mensaje.Add(ESTADO | m_cEstado);
		temp.Format("%d", m_cEstado);
		m_SFPelicula.SetVariable("_root.estado", temp);
	} else if(szCommand=="stop") {
		m_cEstado=2;
		mensaje.Add(ESTADO | m_cEstado);
		temp.Format("%d", m_cEstado);
		m_SFPelicula.SetVariable("_root.estado", temp);
	} else if(szCommand=="cuerpo") {
		m_cDispositivo=2;
		mensaje.Add(DISPOSITIVO | m_cDispositivo);

		m_cIR= AfxGetApp()->GetProfileInt(m_cDispositivo==2 ? "cuerpo" : "cara","ir", 0);
		m_cRF= AfxGetApp()->GetProfileInt(m_cDispositivo==2 ? "cuerpo" : "cara","rf", 0);
		m_cVacio= AfxGetApp()->GetProfileInt(m_cDispositivo==2 ? "cuerpo" : "cara","vacio", 0);

		temp.Format("%d", m_cIR);
		m_SFPelicula.SetVariable("_root.ir", temp);
		mensaje.Add(PROGRESO_IR | m_cIR);
		temp.Format("%d", m_cRF);
		m_SFPelicula.SetVariable("_root.rf", temp);
		mensaje.Add(PROGRESO_RF | m_cIR);
		temp.Format("%d", m_cVacio);
		m_SFPelicula.SetVariable("_root.vacio", temp);
		mensaje.Add(PROGRESO_VACIO | m_cVacio);
	} else if(szCommand=="cara") {
		m_cDispositivo= 1;
		mensaje.Add(DISPOSITIVO | m_cDispositivo);

		m_cIR= AfxGetApp()->GetProfileInt(m_cDispositivo==2 ? "cuerpo" : "cara","ir", 0);
		m_cRF= AfxGetApp()->GetProfileInt(m_cDispositivo==2 ? "cuerpo" : "cara","rf", 0);
		m_cVacio= AfxGetApp()->GetProfileInt(m_cDispositivo==2 ? "cuerpo" : "cara","vacio", 0);

		temp.Format("%d", m_cIR);
		m_SFPelicula.SetVariable("_root.ir", temp);
		mensaje.Add(PROGRESO_IR | m_cIR);
		temp.Format("%d", m_cRF);
		m_SFPelicula.SetVariable("_root.rf", temp);
		mensaje.Add(PROGRESO_RF | m_cIR);
		temp.Format("%d", m_cVacio);
		m_SFPelicula.SetVariable("_root.vacio", temp);
		mensaje.Add(PROGRESO_VACIO | m_cVacio);
	}
	if(!mensaje.IsEmpty())
		m_serial.Write(mensaje.GetData(),mensaje.GetSize());
}

LRESULT ClilashapeDlg::OnSerialMsg (WPARAM wParam, LPARAM /*lParam*/)
{
	CSerial::EEvent eEvent = CSerial::EEvent(LOWORD(wParam));
	CSerial::EError eError = CSerial::EError(HIWORD(wParam));

	if (eError)
		DisplayEvent(_T("An internal error occurred."));

	if (eEvent & CSerial::EEventBreak)
		DisplayEvent(_T("Break detected on input."));

	if (eEvent & CSerial::EEventError)
		DisplayEvent(_T("A line-status error occurred."));

	if (eEvent & CSerial::EEventRcvEv)
		DisplayEvent(_T("Event character has been received."));

	if (eEvent & CSerial::EEventRing)
		DisplayEvent(_T("Ring detected"));

	if (eEvent & CSerial::EEventSend)
		DisplayEvent(_T("All data is send"));

	if (eEvent & CSerial::EEventCTS)
		DisplayEventSetting(_T("CTS signal change"), _T("CTS"), m_serial.GetCTS());

	if (eEvent & CSerial::EEventDSR)
		DisplayEventSetting(_T("DSR signal change"), _T("DSR"), m_serial.GetDSR());

	if (eEvent & CSerial::EEventRLSD)
		DisplayEventSetting(_T("RLSD signal change"), _T("RLSD"), m_serial.GetRLSD());

	if (eEvent & CSerial::EEventRecv)
	{
		// Create a clean buffer
		DWORD dwRead;
		char szData[101];
		const int nBuflen = sizeof(szData)-1;

		// Obtain the data from the serial port
		do
		{
			m_serial.Read(szData,nBuflen,&dwRead);
			szData[dwRead] = '\0';

			// Scan the string for unwanted characters
			for (DWORD dwChar=0; dwChar<dwRead; dwChar++)
			{
				ParseData(szData[dwChar]);
			}
			// Display the fetched string
			// hacer algo con los datos recibidos.
		} while (dwRead == nBuflen);
	}

	return 0;
}

void ClilashapeDlg::ParseData(char data) {

	CString temp;
	if(PROGRESO_IR&data) {
		m_cIR= 15&data;
		temp.Format("%d", m_cIR);
		m_SFPelicula.SetVariable("_root.ir", temp);
		AfxGetApp()->WriteProfileInt(m_cDispositivo==2 ? "cuerpo" : "cara","ir", m_cIR);
	} else if(PROGRESO_RF&data) {
		m_cRF=15&data;
		temp.Format("%d", m_cRF);
		m_SFPelicula.SetVariable("_root.rf", temp);
		AfxGetApp()->WriteProfileInt(m_cDispositivo==2 ? "cuerpo" : "cara","rf", m_cRF);
	} else if(PROGRESO_VACIO&data) {
		m_cVacio= 15&data;
		temp.Format("%d", m_cVacio);
		m_SFPelicula.SetVariable("_root.vacio", temp);
		AfxGetApp()->WriteProfileInt(m_cDispositivo==2 ? "cuerpo" : "cara","vacio", m_cVacio);
	} else if(ESTADO&data) {
		m_cEstado= 15&data;
		temp.Format("%d", m_cEstado);
		m_SFPelicula.SetVariable("_root.estado", temp);
	} else if(DISPOSITIVO&data) {
		// no se reciben señales de dispositivos
	}
}

void ClilashapeDlg::DisplayEvent (LPCTSTR lpszMsg)
{

}

void ClilashapeDlg::DisplayEventSetting (LPCTSTR lpszMsg, LPCTSTR lpszSetting, bool fOn)
{

}

void ClilashapeDlg::OnDestroy()
{
	m_serial.Close();
	CDialog::OnDestroy();
}
