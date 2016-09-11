#include "stdafx.h"
#include "OpenGLControl.h"
#include ".\openglcontrol.h"

vec3 COpenGLControl::defineColor(CString current)
{
	if (current == "Red")
		return vec3(1, 0, 0);
	else if (current == "Green")
		return vec3(0, 1, 0);
	else if (current == "Blue")
		return vec3(0, 0, 1);
	else if (current == "Yellow")
		return vec3(1, 1, 0);
	else if (current == "Cyan")
		return vec3(0, 0, 0.5);
}

COpenGLControl::COpenGLControl(void)
{
	m_fPosX = 0.0f;		// X position of model in camera view
	m_fPosY = 0.0f;		// Y position of model in camera view
	m_fZoom = 45.0f;	// Zoom on model in camera view
	m_fRotX = 45.05f;		// Rotation on model in camera view
	m_fRotY	= -10.05f;		// Rotation on model in camera view
	m_bIsMaximized = false;
	
}

COpenGLControl::~COpenGLControl(void)
{
}

BEGIN_MESSAGE_MAP(COpenGLControl, CWnd)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

void COpenGLControl::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	ValidateRect(NULL);
}

void COpenGLControl::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	if (0 >= cx || 0 >= cy || nType == SIZE_MINIMIZED) return;

	float Width = cx;
    float Height = cy;
	m_openGLRenderer.windowHeight = Height;
	m_openGLRenderer.windowWidth = Width;


	// Map the OpenGL coordinates.
	glViewport(0, 0, cx, cy);

	// Projection view
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	// Set our current view perspective
	gluPerspective(45.0f, (float)cx / (float)cy, 0.01f, 2000.0f);
	//gluPerspective(60.0f, (GLfloat)Width / (GLfloat)Height, 1.0f, 100.0f);
	//glOrtho(-100.0, 100.0, -100.0, 100.0, -2000, 2000);

	// Model view
	
	glScalef(0.01, 0.01, 0.01);

	glMatrixMode(GL_MODELVIEW);

	
	//pretty point of view
	//glRotatef(-30, 0, 0, 1);
	//glRotatef(-29, 0, 1, 0);
	//glRotatef(-40, 1, 0, 0);
	//glScalef(0.7, 0.7, 0.7);

	switch (nType)
	{
		// If window resize token is "maximize"
		case SIZE_MAXIMIZED:
		{
			// Get the current window rect
			GetWindowRect(m_rect);

			// Move the window accordingly
			MoveWindow(6, 6, cx - 14, cy - 14);

			// Get the new window rect
			GetWindowRect(m_rect);

			// Store our old window as the new rect
			m_oldWindow = m_rect;

			break;
		}

		// If window resize token is "restore"
		case SIZE_RESTORED:
		{
			// If the window is currently maximized
			if (m_bIsMaximized)
			{
				// Get the current window rect
				GetWindowRect(m_rect);

				// Move the window accordingly (to our stored old window)
				MoveWindow(m_oldWindow.left, m_oldWindow.top - 18, m_originalRect.Width() - 4, m_originalRect.Height() - 4);

				// Get the new window rect
				GetWindowRect(m_rect);

				// Store our old window as the new rect
				m_oldWindow = m_rect;
			}
		
			break;
		}
	}
}

int COpenGLControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1) return -1;

	oglInitialize();

	return 0;
}

void COpenGLControl::OnDraw(CDC *pDC)
{
	// If the current view is perspective...

}

void COpenGLControl::OnTimer(UINT nIDEvent)
{
	switch (nIDEvent)
	{
		case 1:
		{
			// Clear color and depth buffer bits
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Draw OpenGL scene
			oglDrawScene();

			// Swap buffers
			SwapBuffers(hdc);

			break;
		}

		default:
			break;
	}

	CWnd::OnTimer(nIDEvent);
}

void COpenGLControl::OnMouseMove(UINT nFlags, CPoint point)
{
	int diffX = (int)(point.x - m_fLastX);
	int diffY = (int)(point.y - m_fLastY);
	m_fLastX  = (float)point.x;
	m_fLastY  = (float)point.y;
	static CPoint prev = point;
	bool picking = false;
	std::string res = m_openGLRenderer.pickRects(point.x, point.y);
	// Left mouse button
	if (nFlags & MK_LBUTTON)
	{
		for (auto &i : m_openGLRenderer.shapes)
		{
			if (i->marked)
			{
				vec3 lastCenter = i->getCenter();
				lastCenter.x += (float)0.05f * diffX;
				lastCenter.y -= (float)0.05f * diffY;
				
				i->changeCenter(lastCenter);
				picking = true;
				
			}
		}
        
		if (!picking) {
			m_fRotX += (float)0.5f * diffY;

			if ((m_fRotX > 360.0f) || (m_fRotX < -360.0f))
			{
				m_fRotX = 0.0f;
			}

			m_fRotY += (float)0.5f * diffX;

			if ((m_fRotY > 360.0f) || (m_fRotY < -360.0f))
			{
				m_fRotY = 0.0f;
			}
		}
		picking = false;
	}

	// Right mouse button
	else if (nFlags & MK_RBUTTON)
	{
		m_fZoom -= (float)0.1f * diffY;
	}

	// Middle mouse button
	else if (nFlags & MK_MBUTTON)
	{
		m_fPosX += (float)0.05f * diffX;
		m_fPosY -= (float)0.05f * diffY;
	}

	OnDraw(NULL);

	CWnd::OnMouseMove(nFlags, point);
	prev = point;
}

void COpenGLControl::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();

	if (m_openGLRenderer.pickMode) {
		m_openGLRenderer.m_pick = true;
		m_openGLRenderer.m_mouseX = point.x;
		m_openGLRenderer.m_mouseY = point.y;
	}
	else
		m_openGLRenderer.m_pick = false;
}

void COpenGLControl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar) {
	/*case LVKF_CONTROL:
		m_openGLRenderer.m_ctrl = true;
		break;*/
	case VK_CONTROL:
		//m_openGLRenderer.m_shiftPressed = true;
		break;
	}
}

void COpenGLControl::oglCreate(CRect rect, CWnd *parent)
{
	CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_OWNDC, NULL, (HBRUSH)GetStockObject(BLACK_BRUSH), NULL);

	CreateEx(0, className, "OpenGL", WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, rect, parent, 0);

	// Set initial variables' values
	m_oldWindow	   = rect;
	m_originalRect = rect;

	hWnd = parent;
}

void COpenGLControl::oglInitialize(void)
{
	// Initial Setup:
	//
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32, // bit depth
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		16, // z-buffer depth
		0, 0, 0, 0, 0, 0, 0,
	};

	// Get device context only once.
	hdc = GetDC()->m_hDC;
	
	// Pixel format.
	m_nPixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, m_nPixelFormat, &pfd);

	// Create the OpenGL Rendering Context.
	hrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hrc);

	// Basic Setup:
	//
	// Set color to use when clearing the background.
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);

	// Turn on backface culling
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	
	// Turn on depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Send draw request
	OnDraw(NULL);

	vec3 color = defineColor("Cyan");
	createConus(1, 3, 5, color, 16, vec3(0,0,0), vec3(0,0,0));

	m_openGLRenderer.init();
	
}

void COpenGLControl::oglDrawScene(void)
{
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -m_fZoom);
	glTranslatef(m_fPosX, m_fPosY, 0.0f);
	glRotatef(m_fRotX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_fRotY, 0.0f, 1.0f, 0.0f);

	
	m_openGLRenderer.render();//(FrameTime);
	
	
}

void COpenGLControl::createConus(float topR, float botR, float height, vec3 color, int dotNumber, vec3 angle, vec3 center)
{
	Shape* conus = new Conus(height, topR, botR, dotNumber, color, angle, center);
	m_openGLRenderer.shapes.push_back(conus);
	m_openGLRenderer.newAdded = true;
}

void COpenGLControl::createPyramid(float side, float height, vec3 color, vec3 angle, vec3 center)
{
	Shape* pyramid = new Pyramid(side, height, color, angle, center);
	m_openGLRenderer.shapes.push_back(pyramid);
	m_openGLRenderer.newAdded = true;
}
