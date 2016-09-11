#pragma once
#include "Shape.h"
#include "Pyramid.h"
#include "Grid.h"
#include "Conus.h"
#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <gl\GLU.h>
#include <stdlib.h> 
#include <stdio.h> 
#include "mainTable.h"
using std::string;
using std::vector;

class COpenGLRenderer
{
protected:
	int Width, Height;
	CmainTable dataTable;

public:

	vector<Shape*> shapes;
	Grid axes;
	bool isAxes;
	bool newAdded = false;
	bool setNewScale = false;

	vec3 defaultAngle;
	vec3 defaultScale;
	float angleRotation = 0.1;
	float incrementRotation = 0;

	float incrementRotX = 0;
	float incrementRotY = 0;
	float incrementRotZ = 0;

	float currRotX = 0;
	float currRotY = 0;
	float currRotZ = 0;

	bool m_pick;
	bool viewMode;
	bool pickMode;

	float m_mouseX;
	float m_mouseY;
	float windowHeight;
	float windowWidth;

	float m_translationZ = 0;
	float m_lastTranslation = 0;

	int countMarked = 0;

	void init();
	string processHits(GLint hits, GLuint buffer[], bool lbotton = true);
	string pickRects(int x, int y, bool lbotton = true);
	void render();
	void saveData();
	void loadData();
	void deleteData();
};
