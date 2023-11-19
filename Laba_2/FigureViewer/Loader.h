#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Vector2D.h"

class Loader
{
private:
	bool isLoad();

	std::vector<Vector2D> m_vertices;
	std::vector<int> m_indices;

	std::string m_path;

public:
	Loader(const std::string& path);
	~Loader();

	std::vector<Vector2D> vertices() const;
	std::vector<int> indices() const;

	void load();
};
