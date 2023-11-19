#include "Render2D.h"

Render2D::~Render2D()
{
	for (const auto& object : m_objects)
		if (object)
			delete object;
}

Model2D* Render2D::get_model()
{
	return m_objects[selected];
}

void Render2D::draw(const HDC& hdc)
{
	HBRUSH oldBrush = NULL;
	for (int i = 0; i < m_objects.size(); i++)
	{
		if (i == selected)
		{
			oldBrush = (HBRUSH)SelectObject(hdc, CreateSolidBrush(RGB(255, 0, 0)));
		}

		if (m_objects[i])
			m_objects[i]->draw(hdc);

		if (i == selected)
		{
			DeleteObject(SelectObject(hdc, oldBrush));
		}
	}
}

void Render2D::addObject(Model2D* model)
{
	m_objects.push_back(model);
}

void Render2D::applyToObj(Matrix<> transformMat)
{
		m_objects[selected]->affin(transformMat);
}


void Render2D::nextObj()
{
	selected = (selected + 1) % m_objects.size();
}

