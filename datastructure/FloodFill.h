#pragma once
#include<vector>

class FloodFill
{
	int m_matrix[10][10];
	int m_rows = 0;
	int m_columns = 0;
	int floodfill(int i, int j);
public:
	FloodFill() = default;
	~FloodFill() = default;
	void getMatrix();
	void showMatrix();
	void testFloodFill();
	
};

