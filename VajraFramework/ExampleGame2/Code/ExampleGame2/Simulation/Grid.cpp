#include "ExampleGame2/Simulation/Cell.h"
#include "ExampleGame2/Simulation/Grid.h"
#include "ExampleGame2/Simulation/MarkerParticle.h"
#include "ExampleGame2/Simulation/Simulation.h"
#include "Vajra/Engine/DebugDrawer/DebugDrawer.h"
#include "Vajra/Framework/Core/Framework.h"
#include "Vajra/Framework/Logging/Logger.h"

Grid::Grid() {
	this->init();
}

Grid::~Grid() {
	this->destroy();
}

void Grid::Update() {
	this->updateCells();
}

void Grid::updateCells() {
	// Mark all cells as layer = -1:
	{
		this->hashTable->iterator_BeginCells();
		Cell* cell = nullptr;
		while ((cell = this->hashTable->iterator_NextCell()) != nullptr) {
			cell->layer = -1;
		}
	}

	// Update the cells that currently have fluid in them:
	for (MarkerParticle* markerParticle : SIMULATION->markerParticles) {
		int x, y, z;
		this->positionToGridCellCoords(markerParticle->position, x, y, z);

		if (!this->hashTable->HasCell(x, y, z)) {
			Cell* cell = this->hashTable->AddCell(x, y, z);
			cell->cellType = CELL_TYPE_FLUID;
			cell->layer = 0;

		} else {
			Cell* cell = this->hashTable->GetCell(x, y, z);
			if (cell->cellType != CELL_TYPE_SOLID) {
				cell->cellType = CELL_TYPE_FLUID;
				cell->layer = 0;
			}
		}
	}

	// Create a buffer zone of air around the fluid cells:
	const int numBufferZoneLayers = 4;
	for (int layerNumber = 1; layerNumber < numBufferZoneLayers; ++layerNumber) {
	}

	// Delete any cells with layer == -1:
	{
		std::vector<glm::ivec3> cellPositionsForDeletion;

		this->hashTable->iterator_BeginCells();
		Cell* cell = nullptr;
		while ((cell = this->hashTable->iterator_NextCell()) != nullptr) {
			if (cell->layer == -1) {
				cellPositionsForDeletion.push_back(glm::ivec3(cell->position.x, cell->position.y, cell->position.z));
			}
		}

		for (glm::ivec3 cellPositionForDeletion : cellPositionsForDeletion) {
			this->hashTable->RemoveCell(cellPositionForDeletion.x, cellPositionForDeletion.y, cellPositionForDeletion.z);
		}
	}

	FRAMEWORK->GetLogger()->dbglog("\nNumber of cells: %u", this->hashTable->Size());
	this->drawCells();
}

void Grid::markSolidCells() {
	// Mark the floor:
	for (int i = 0; i < WATER_ARENA_SIZE; i += CELL_SIZE) {
		for (int j = 0; j < WATER_ARENA_SIZE; j += CELL_SIZE) {
			Cell* cell = this->hashTable->AddCell(i, 0, j);
			cell->cellType = CELL_TYPE_SOLID;
		}
	}
}

void Grid::init() {
	this->hashTable = new GridHashTable();
	this->markSolidCells();
}

void Grid::destroy() {
}

void Grid::positionToGridCellCoords(glm::vec3 position, int& out_x, int& out_y, int& out_z) {
	out_x = (int)position.x / (int)CELL_SIZE;
	out_y = (int)position.y / (int)CELL_SIZE;
	out_z = (int)position.z / (int)CELL_SIZE;
}

void Grid::drawCells() {
#ifdef DEBUG
#endif

	{
		this->hashTable->iterator_BeginCells();
		Cell* cell = nullptr;
		while ((cell = this->hashTable->iterator_NextCell()) != nullptr) {
			DebugDraw::DrawCube(glm::vec3(cell->position.x + CELL_SIZE/2.0f, cell->position.y + CELL_SIZE/2.0f, cell->position.z + CELL_SIZE/2.0f), CELL_SIZE);
		}
	}
}

