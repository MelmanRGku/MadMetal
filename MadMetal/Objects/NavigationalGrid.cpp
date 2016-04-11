#include "NavigationalGrid.h"



NavigationalGrid::NavigationalGrid(std::vector<glm::vec3> vertices, std::vector<std::vector<unsigned int>> faces, int numOfQuads) : m_vertices(vertices), m_faces(faces), m_numOfQuads(numOfQuads)
{
}
NavigationalGrid::~NavigationalGrid()
{

}

std::vector<glm::vec3>* NavigationalGrid::getVertices() { return &m_vertices; }
std::vector<std::vector<unsigned int>>* NavigationalGrid::getFaces() { return &m_faces; }
int NavigationalGrid::getNumOfQuads() { return m_numOfQuads; }