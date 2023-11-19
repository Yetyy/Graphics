#include "Model2D.h"


Model2D::Model2D(const std::vector<Vector2D> &vertices, const std::vector<int> &indices) :
	m_vertices(vertices),
	m_indices(indices)
{
}

Model2D::Model2D(const std::string path, double dX, double dY)
{
	Loader loader(path);
	loader.load();
	m_vertices = loader.vertices();
	m_indices = loader.indices();
	fillMatrix(dX, dY);
}

void Model2D::draw(const HDC& hdc)
{
	POINT* vertcs = getPoints();

	Polygon(hdc, vertcs, m_vertices.size());
	delete[] vertcs;
}

void Model2D::apply(Matrix<> transformMat)
{
	m_modelMatrix = transformMat * m_modelMatrix;
}

pair<double, double> Model2D::getFirstCoord()
{
	return pair<double, double>(m_modelMatrix(0, 0), m_modelMatrix(1, 0));
}

void Model2D::fillMatrix(double dX, double dY)
{
	Matrix<> matrix(3, m_vertices.size());
	for (int i = 0; i < m_indices.size() - 1; i++)
	{
		matrix.setVaue(0, i, m_vertices[m_indices[i]].x() + dX);
		matrix.setVaue(1, i, m_vertices[m_indices[i]].y() + dY);
		matrix.setVaue(2, i, 1);
	}
	m_modelMatrix = matrix;
}

POINT* Model2D::getPoints()
{
	POINT* result = new POINT[m_vertices.size()];
	for (int i = 0; i < m_vertices.size(); i++)
	{
		result[i].x = round(m_modelMatrix(0, i) / m_modelMatrix(2, i));
		result[i].y = round(m_modelMatrix(1, i) / m_modelMatrix(2, i));
	}
	return result;
}
void Model2D::affin(Matrix<> transformMat) 
{ int tempX = getFirstCoord().first; 
int tempY = getFirstCoord().second; 
apply(Translation(-tempX, -tempY)); 
apply(transformMat); 
apply(Translation(tempX, tempY)); }

void Model2D::Rotation_M(double O)
{
	O = (O * M_PI)/ 180;
	affin(Rotation(O));

}
void Model2D::Translation_M(double x, double y)
{
	affin(Translation(x, y));
}