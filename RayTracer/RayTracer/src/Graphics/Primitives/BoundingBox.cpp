#include "pch.h"
#include "BoundingBox.h"



BoundingBox::BoundingBox(glm::vec3 min, glm::vec3 max)

{
	m_Params[0] = min;
	m_Params[1] = max;
	m_Centre = (min + max) * 0.5f;

	//Split(0);

}

BoundingBox::~BoundingBox()
{
}

void BoundingBox::Split(int level)
{
	//if (level == MAX_DEPTH) return;

	glm::vec3 min;
	glm::vec3 max;
	//if (m_Triangles.size() > MAX_TRIANGLES_PER_BOX)
	//{
	float epsilon = 1e-1;

		BoundingBox* temp[NUMBER_OF_CHILDREN];
		//Make children
		temp[0]= new BoundingBox(this->m_Params[0] - epsilon, this->m_Centre + epsilon);

		min = glm::vec3(this->m_Centre.x - epsilon, this->m_Params[0].y - epsilon, this->m_Params[0].z - epsilon);
		max = glm::vec3(this->m_Params[1].x + epsilon, this->m_Centre.y + epsilon, this->m_Centre.z + epsilon);
		temp[1] = new BoundingBox(min, max);

		min = glm::vec3(this->m_Params[0].x - epsilon, this->m_Centre.y - epsilon, this->m_Params[0].z - epsilon);
		max = glm::vec3(this->m_Centre.x + epsilon, this->m_Params[1].y + epsilon, this->m_Centre.z + epsilon);
		temp[2] = new BoundingBox(min, max);

		min = glm::vec3(this->m_Centre.x - epsilon, this->m_Centre.y - epsilon, this->m_Params[0].z - epsilon);
		max = glm::vec3(this->m_Params[1].x + epsilon, this->m_Params[1].y + epsilon, this->m_Centre.z + epsilon);
		temp[3] = new BoundingBox(min, max);


		min = glm::vec3(this->m_Params[0].x - epsilon, this->m_Params[0].y - epsilon, this->m_Centre.z- epsilon);
		max = glm::vec3(this->m_Centre.x + epsilon, this->m_Centre.y + epsilon, this->m_Params[1].z + epsilon);
		temp[4] = new BoundingBox(min, max);

		min = glm::vec3(this->m_Centre.x - epsilon, this->m_Params[0].y - epsilon, this->m_Centre.z - epsilon);
		max = glm::vec3(this->m_Params[1].x + epsilon, this->m_Centre.y + epsilon, this->m_Params[1].z + epsilon);
		temp[5] = new BoundingBox(min, max);

		min = glm::vec3(this->m_Params[0].x - epsilon, this->m_Centre.y - epsilon, this->m_Centre.z - epsilon);
		max = glm::vec3(this->m_Centre.x + epsilon, this->m_Params[1].y + epsilon, this->m_Params[1].z + epsilon);
		temp[6] = new BoundingBox(min, max);


		temp[7] = new BoundingBox(this->m_Centre - epsilon, this->m_Params[1] + epsilon);


		//if (level < MAX_DEPTH) {
		for (int i = 0; i < NUMBER_OF_CHILDREN; i++) {
			for (int j = 0; j < m_Triangles.size(); j++) {

					temp[i]->Add(m_Triangles[j]); //Try and add this triangle -> push_back(t)

					if (j == m_Triangles.size() - 1) {
						if (temp[i]->m_Triangles.size() <= 0) {
							delete temp[i];
							break;
						}

						if (temp[i]->m_Triangles.size() > MAX_TRIANGLES_PER_BOX) 
						{
							temp[i]->Split(0);
							temp[i]->m_Triangles.clear();
							children.push_back(temp[i]);
							break;
						}
						
						children.push_back(temp[i]);
					}

				}
			
			}

			//m_Triangles.clear();

			/*for (int i = 0; i < NUMBER_OF_CHILDREN; i++) {
				if()
			}*/

		/*	for (int i = 0; i < children.size(); i++) {
				
				if (this->children[i]->m_Triangles.size() > 0)
				{
					this->children[i]->Split(level + 1);
				}
			}*/
		//}

	//}
	//else
	//{
	////	if (m_Triangles.size() == 0) delete this;
	//	WARN("Triangles On leaf: {0}", m_Triangles.size());
	//	isLeaf = true;
	//}
}

bool BoundingBox::Intersect(Ray & ray)
{
	float txmin, txmax, tymin, tymax, tzmin, tzmax;

	txmin = (m_Params[ray.sign[0]].x - ray.Origin.x) * ray.Inv_Direction.x;
	txmax = (m_Params[1 - ray.sign[0]].x - ray.Origin.x) * ray.Inv_Direction.x;
	tymin = (m_Params[ray.sign[1]].y - ray.Origin.y) * ray.Inv_Direction.y;
	tymax = (m_Params[1 - ray.sign[1]].y - ray.Origin.y) * ray.Inv_Direction.y;

	if (txmin > txmax) swap(txmin, txmax);
	if (tymin > tymax) swap(tymin, tymax);

	if ((txmin > tymax) || (tymin > txmax))
		return false;

	if (tymin > txmin)
		txmin = tymin;
	if (tymax < txmax)
		txmax = tymax;

	tzmin = (m_Params[ray.sign[2]].z - ray.Origin.z) * ray.Inv_Direction.z;
	tzmax = (m_Params[1 - ray.sign[2]].z - ray.Origin.z) * ray.Inv_Direction.z;

	if (tzmin > tzmax) swap(tzmin, tzmax);

	if ((txmin > tzmax) || (tzmin > txmax))
		return false;

	if (tzmin > txmin)
		txmin = tzmin;
	if (tzmax < txmax)
		txmax = tzmax;

	bool intersect = false;
	
	if (children.size() > 0) {
		for (int i = 0; i < children.size(); i++) {
			this->children[i]->Intersect(ray);
		}
	}
	else
	{
		for (int i = 0; i < m_Triangles.size(); i++) {

			if (m_Triangles[i]->Intersect(ray))
			{
				intersect = true;
			}
		}
	}

	return intersect;
}

void BoundingBox::swap(float& first, float& second)
{
	float temp;
	temp = first;
	first = second;
	second = temp;
}

void BoundingBox::Add(Triangle * t)
{
	if (IsVertexInside(t->A()) ||  IsVertexInside(t->B()) || IsVertexInside(t->C())) 
	{
		m_Triangles.push_back(t);
	}
}

bool BoundingBox::IsVertexInside(const glm::vec3& vert)
{
	if (vert.x >= m_Params[0].x &&
		vert.y >= m_Params[0].y &&
		vert.z >= m_Params[0].z &&
		vert.x <= m_Params[1].x &&
		vert.y <= m_Params[1].y &&
		vert.z <= m_Params[1].z ) 
	{
		return true;
	}

	return false;
}


