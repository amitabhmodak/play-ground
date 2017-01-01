#include "stdafx.h"
#include "FloodFill.h"
#include <iostream>
#include <algorithm>

#define visited -1
#define zero 0
#define one 1
#define RIGHT(a)(a + 1)
#define LEFT(a)(a - 1)
#define TOP(a)(RIGHT(a))
#define BOTTOM(a)(LEFT(a))

void FloodFill::getMatrix() {

	std::cout << "Rows: ";
	std::cin >> m_rows;
	std::cout << "\nColumns: ";
	std::cin >> m_columns;

	for (int i = 0; i < m_rows; i++)  
		for (int j = 0; j < m_columns; j++) {
			std::cin >> m_matrix[i][j];
			}
}

void FloodFill::showMatrix() {
	for (int i = 0; i < m_rows; i++) {
		std::cout << "\n";
		for (int j = 0; j < m_columns; j++) {
			std::cout << m_matrix[i][j] << " ";
		}
	}
		
}

void FloodFill::testFloodFill() {
	int max = 0;
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_columns; j++) {
			if (m_matrix[i][j] == one) {
				max = std::max(max, floodfill(i, j));
			}
		}
	}

	std::cout << "\nMax " << max << "\n";
}

int FloodFill::floodfill(int i, int j) {
	if (i < 0 || i >= m_rows || j < 0 || j >= m_columns || m_matrix[i][j] == zero || m_matrix[i][j] == visited)
		return 0;
	m_matrix[i][j] = visited;
	return 1 + floodfill(RIGHT(i), j) + floodfill(LEFT(i), j) +
		floodfill(i, BOTTOM(j)) + floodfill(i, TOP(j)) +
		floodfill(RIGHT(i), TOP(j)) + floodfill(LEFT(i), TOP(j)) +
		floodfill(RIGHT(i), BOTTOM(j)) + floodfill(LEFT(i), BOTTOM(j));

}

 