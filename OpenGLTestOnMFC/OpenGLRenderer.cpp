#pragma once
#include "stdafx.h"
#include "OpenGLRenderer.h"
#include <iostream>
#include <gl\GLU.h>
#include <stdlib.h> 
#include <stdio.h> 
#define BUFSIZE 512 

void COpenGLRenderer::init(void)
{
	glClearColor(0.8, 0.8, 0.8, 0.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);


		/****************************************/
		/*       Set up OpenGL lights           */
		/****************************************/
		GLfloat light1_ambient[] = { 0.1f, 0.1f, 0.3f, 1.0f };
		GLfloat light1_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat light1_position[] = { 1.0, 0.5, 0.8, 0.0 }; 
	
		glEnable(GL_LIGHTING);
		glEnable(GL_NORMALIZE);
	
		glEnable(GL_LIGHT1);
		glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
		glLightfv(GL_LIGHT1, GL_POSITION, light1_position);


	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_FLAT);
	glDepthRange(0.0, 1.0); /* The default z mapping */
	isAxes = true;

	defaultAngle = vec3(0, 0, 0);
	defaultScale = vec3(1, 1, 1);
	m_pick = false;
	m_mouseX = 0;
	m_mouseY = 0;

	pickMode = false;
	viewMode = true;
}

string COpenGLRenderer::processHits(GLint hits, GLuint buffer[], bool lbotton)
{
	string res;
	unsigned int i, j;
	GLuint names, *ptr;

	res += "   hits = " + to_string(hits);
	ptr = (GLuint *)buffer;
	if (!hits) {
		for (auto i : shapes)
			i->marked = false;
	}
	for (i = 0; i < hits; i++) { /* for each hit */
		names = *ptr;
		ptr+=3;
		res += " name: ";
		for (j = 0; j < names; j++) { /* for each name */
			for (auto i : shapes)
			{
				if (i->ID == *ptr) {
					if (lbotton) i->marked = true;
					else i->marked = false;
				}
			}
			res += to_string(*ptr);
			ptr++;
		}
	}
	return res;
}

string COpenGLRenderer::pickRects(int x, int y, bool lbotton)
{
	GLuint selectBuf[BUFSIZE];
	GLint hits;
	GLint viewport[4];

	glSelectBuffer(BUFSIZE, selectBuf);
	(void)glRenderMode(GL_SELECT);

	glInitNames();
	glPushName(0);

	for (auto i : shapes)
		i->draw(defaultAngle,i->currentScale);

	hits = glRenderMode(GL_RENDER);
	return processHits(hits, selectBuf, lbotton);
}

void COpenGLRenderer::render()
{
	currRotX = currRotX + incrementRotX;
	currRotY = currRotY + incrementRotY;
	currRotZ = currRotZ + incrementRotZ;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	if (isAxes)
		axes.draw();
	if (shapes.size() == 0)
		std::cout << "No objects";

	countMarked = 0;
	vec3 angle(currRotX, currRotY, currRotZ);
	for (int i = 0; i < shapes.size(); i++)
	{
		if (shapes[i]->marked) {
			vec3 lastCenter = shapes[i]->getCenter();
			lastCenter.z += m_translationZ - m_lastTranslation;
			shapes[i]->changeCenter(lastCenter);
			countMarked++;
		}

		if (m_pick) 
		{
			glDisable(GL_LIGHTING);
			glColor3ub(shapes[i]->ID, 0, 0);
			shapes[i]->draw(angle,shapes[i]->currentScale);
		}
		else {
			glColor3f(shapes[i]->colour.x, shapes[i]->colour.y, shapes[i]->colour.z);
			shapes[i]->draw(angle,shapes[i]->currentScale);
		}
	}

	m_lastTranslation = m_translationZ;


	if (viewMode) {
			for (auto i : shapes) 
				i->marked = false;
	}

	if (m_pick) {
		unsigned char pixel[4];
		glReadPixels(m_mouseX, windowHeight - m_mouseY - 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
		for (auto i : shapes)
		{
			if (i->ID == (int)pixel[0])
			{
				i->marked = true;
			}
		}
		m_pick = false;
	}

	glFlush();

}

void COpenGLRenderer::saveData()
{
	dataTable.Open();
	dataTable.CanAppend();
	for (auto i : shapes) {
		dataTable.AddNew();
		if (i->isConus()) {
			dataTable.m_botRadius = i->getBotRadius();
			dataTable.m_topRadius = i->getTopRadius();
			dataTable.m_dotNumber = i->getDotNumber();
			dataTable.m_typeShape = 1;
			
		}
		else if (i->isPyramid()) {
			dataTable.m_side = i->getSideLength();
			dataTable.m_typeShape = 2;
		}
		dataTable.m_height = i->getHeight();
	    dataTable.m_CenterX = i->getCenter().x;
		dataTable.m_CenterY = i->getCenter().y;
		dataTable.m_CenterZ = i->getCenter().z;
		dataTable.m_ColorB = i->getColor().b;
		dataTable.m_ColorR = i->getColor().r;
		dataTable.m_ColorG = i->getColor().g;
		dataTable.m_angleX = i->getAngleRotation().x;
		dataTable.m_angleY = i->getAngleRotation().y;
		dataTable.m_angleZ = i->getAngleRotation().z;
		dataTable.m_ID++;
		dataTable.Update();
	}
	dataTable.Close();
}

void COpenGLRenderer::loadData()
{
	dataTable.Open();
	while (!dataTable.IsEOF()) {
		if (dataTable.m_typeShape == 1) {
			Shape* conus = new Conus(dataTable.m_height,
									dataTable.m_topRadius,
									dataTable.m_botRadius,
									dataTable.m_dotNumber,
									vec3(dataTable.m_ColorR, dataTable.m_ColorG, dataTable.m_ColorB),
									vec3(dataTable.m_angleX, dataTable.m_angleY, dataTable.m_angleZ),
									vec3(dataTable.m_CenterX, dataTable.m_CenterY, dataTable.m_CenterZ));
			shapes.push_back(conus);
		}
		else if (dataTable.m_typeShape == 2) {
			Shape* pyr = new Pyramid(dataTable.m_side,
									dataTable.m_height,
									vec3(dataTable.m_ColorR, dataTable.m_ColorG, dataTable.m_ColorB),
									vec3(dataTable.m_angleX, dataTable.m_angleY, dataTable.m_angleZ),
									vec3(dataTable.m_CenterX, dataTable.m_CenterY, dataTable.m_CenterZ));
			shapes.push_back(pyr);
		}
		dataTable.MoveNext();
	}
	dataTable.Close();
}

void COpenGLRenderer::deleteData()
{
	dataTable.Open();
	while (!dataTable.IsEOF()) {
		dataTable.Delete();
		dataTable.MoveNext();
	}
	dataTable.Close();
}

