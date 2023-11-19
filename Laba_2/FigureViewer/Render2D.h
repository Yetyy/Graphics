#pragma once
#include "Model2D.h"
#include <wtypes.h>

class Render2D
{
private:
	std::vector<Model2D*> m_objects;
	int selected = 0;

public:
	Render2D() = default;
	~Render2D();
	Model2D* get_model();
	void draw(const HDC& hdc);
	void addObject(Model2D* model);
	void applyToObj(Matrix<> transformMat);

	void nextObj();
};
