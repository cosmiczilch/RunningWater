#include "ExampleGame2/Simulation/Cell.h"
#include "ExampleGame2/Simulation/Grid.h"
#include "ExampleGame2/Simulation/MarkerParticle.h"
#include "ExampleGame2/Simulation/Simulation.h"
#include "Vajra/Engine/Core/Engine.h"
#include "Vajra/Engine/DebugDrawer/DebugDrawer.h"
#include "Vajra/Engine/Timer/Timer.h"
#include "Vajra/Framework/Core/Framework.h"
#include "Vajra/Framework/Logging/Logger.h"
#include "Vajra/Utilities/Utilities.h"

glm::vec3 g = glm::vec3(0.0f, -9.8f, 0.0f);

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
	{
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
	}

	// Create a buffer zone of air around the fluid cells:
	const int numBufferZoneLayers = 3;
	for (int layerNumber = 1; layerNumber <= numBufferZoneLayers; ++layerNumber) {
		this->hashTable->iterator_BeginCells();
		Cell* cell = nullptr;
		while ((cell = this->hashTable->iterator_NextCell()) != nullptr) {
			if ((cell->cellType == CELL_TYPE_AIR || cell->cellType == CELL_TYPE_FLUID) &&
				cell->layer == (layerNumber - 1)) {
				for (int n = 0; n < NEIGHBOR_NUM_NEIGHBORS; ++n) {
					Cell* neighbor = this->getNeighborForCell(cell, (NEIGHBOR_type)n, false);
					if (neighbor != nullptr) {
						// Neighbor already exists:
						if (neighbor->layer == -1 && !this->isCellSolid(neighbor->position.x, neighbor->position.y, neighbor->position.z)) {
							neighbor->cellType = CELL_TYPE_AIR;
							neighbor->layer = layerNumber;
						}
					} else {
						// Create the neighbor:
						neighbor = this->getNeighborForCell(cell, (NEIGHBOR_type)n, true);
						neighbor->layer = layerNumber;
						if (!this->isCellSolid(neighbor->position.x, neighbor->position.y, neighbor->position.z)) {
							neighbor->cellType = CELL_TYPE_AIR;
						} else {
							neighbor->cellType = CELL_TYPE_SOLID;
						}
					}
				}
			}
		}
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

	// Update simulation properties:
	this->updateConvection();
	this->updateExternalForces();
	this->updateSolidNormalForces();
	this->extrapolateFluidVelocitiesToAirCells();
	this->updateSolidCellVelocities();



	this->applyVelocities();

	FRAMEWORK->GetLogger()->dbglog("\nNumber of cells: %u", this->hashTable->Size());
	this->drawCells();
}

void Grid::updateConvection() {
	return;
}


void Grid::updateExternalForces() {
	float deltaTime = ENGINE->GetTimer()->GetDeltaFrameTime();

	// Add gravity:
	{
		this->hashTable->iterator_BeginCells();
		Cell* cell = nullptr;
		while ((cell = this->hashTable->iterator_NextCell()) != nullptr) {
			if (cell->cellType == CELL_TYPE_FLUID) {
				cell->u += g * deltaTime;
			}
		}
	}
}

void Grid::updateSolidNormalForces() {
}

void Grid::updateSolidCellVelocities() {
	/*
	 * Prevent fluid from entering solid cells
	 */
	{
		this->hashTable->iterator_BeginCells();
		Cell* cell = nullptr;
		while ((cell = this->hashTable->iterator_NextCell()) != nullptr) {
			if (cell->cellType == CELL_TYPE_SOLID) {
				for (unsigned int neighbor_type = NEIGHBOR_BELOW; neighbor_type < NEIGHBOR_NUM_NEIGHBORS; ++neighbor_type) {
					Cell* neighbor = this->getNeighborForCell(cell, (NEIGHBOR_type)neighbor_type, false);
					if (neighbor != nullptr) {
						switch (neighbor_type) {

						case NEIGHBOR_BELOW: {
							if (neighbor->u.y > 0.0f) {
								neighbor->u.y = 0.0f;
							}
						} break;

						case NEIGHBOR_ABOVE: {
							if (neighbor->u.y < 0.0f) {
								neighbor->u.y = 0.0f;
							}
						} break;

						case NEIGHBOR_LEFT: {
							if (neighbor->u.x < 0.0f) {
								neighbor->u.x = 0.0f;
							}
						} break;

						case NEIGHBOR_RIGHT: {
							if (neighbor->u.x > 0.0f) {
								neighbor->u.x = 0.0f;
							}
						} break;

						case NEIGHBOR_BEHIND: {
							if (neighbor->u.z < 0.0f) {
								neighbor->u.z = 0.0f;
							}
						} break;

						case NEIGHBOR_FRONT: {
							if (neighbor->u.z > 0.0f) {
								neighbor->u.z = 0.0f;
							}
						} break;

						default: {
							ASSERT(0, "Shouldn't be here.");
						} break;
						}
					}
				}
			}
		}
	}
}


void Grid::extrapolateFluidVelocitiesToAirCells() {

	{
		// Set layer field to 0 for fluid cells and -1 for every other type:
		this->hashTable->iterator_BeginCells();
		Cell* cell = nullptr;
		while ((cell = this->hashTable->iterator_NextCell()) != nullptr) {
			if (cell->cellType == CELL_TYPE_FLUID) {
				cell->layer =  0;
			} else {
				cell->layer = -1;
			}
		}

		const int numBufferZoneLayers = 3;
		for (int layerNumber = 1; layerNumber <= numBufferZoneLayers; ++layerNumber) {
			this->hashTable->iterator_BeginCells();
			Cell* cell = nullptr;
			while ((cell = this->hashTable->iterator_NextCell()) != nullptr) {
				if (cell->layer == -1) {
					Averager uxAverager, uyAverager, uzAverager;
					for (int neighbor_type = NEIGHBOR_BELOW; neighbor_type < NEIGHBOR_NUM_NEIGHBORS; ++neighbor_type) {
						Cell* neighbor = this->getNeighborForCell(cell, (NEIGHBOR_type)neighbor_type, false);
						if (neighbor != nullptr) {
							if (neighbor->layer == (layerNumber - 1)) {
								uxAverager.AddItem(neighbor->u.x);
								uyAverager.AddItem(neighbor->u.y);
								uzAverager.AddItem(neighbor->u.z);
							}
						}
					}
					cell->u = glm::vec3(uxAverager.GetAverage(), uyAverager.GetAverage(), uzAverager.GetAverage());
					cell->layer = layerNumber;
				}
			}
		}


	}
}

void Grid::applyVelocities() {
	float deltaTime = ENGINE->GetTimer()->GetDeltaFrameTime();

	{
		for (MarkerParticle* markerParticle : SIMULATION->markerParticles) {
			int x, y, z;
			this->positionToGridCellCoords(markerParticle->position, x, y, z);

			Cell* cell = this->hashTable->GetCell(x, y, z);
			if (cell != nullptr) {
				if (cell->cellType == CELL_TYPE_FLUID) {
					markerParticle->position += cell->u * deltaTime;
				}
			}
		}
	}
}

bool Grid::isCellSolid(int x, int y, int z) {
	if (y < 0) {
		// Floor
		return true;
	}
	if (x < 0 || x > WATER_ARENA_SIZE) {
		return true;
	}
	if (z < 0 || z > WATER_ARENA_SIZE) {
		return true;
	}
	Cell* cell = this->hashTable->GetCell(x, y, z);
	if (cell != nullptr) {
		return (cell->cellType == CELL_TYPE_SOLID);
	}
	return false;
}

void Grid::init() {
	this->hashTable = new GridHashTable();
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

	// return;

	{
		this->hashTable->iterator_BeginCells();
		Cell* cell = nullptr;
		while ((cell = this->hashTable->iterator_NextCell()) != nullptr) {
			if (cell->cellType == CELL_TYPE_AIR) {
				DebugDraw::SetColor(1.0f, 1.0f, 1.0f, 0.1f);
			} else if (cell->cellType == CELL_TYPE_FLUID) {
				DebugDraw::SetColor(0.0f, 0.0f, 1.0f, 0.4f);
			} else if (cell->cellType == CELL_TYPE_SOLID) {
				DebugDraw::SetColor(0.0f, 0.0f, 0.0f, 0.4f);
			}
			DebugDraw::DrawCube(glm::vec3(cell->position.x + CELL_SIZE/2.0f, cell->position.y + CELL_SIZE/2.0f, cell->position.z + CELL_SIZE/2.0f), CELL_SIZE);
		}
	}
}

Cell* Grid::getNeighborForCell(Cell* cell, NEIGHBOR_type neighborType, bool create) {
	Cell* neighbor = nullptr;
	int nx = cell->position.x;
	int ny = cell->position.y;
	int nz = cell->position.z;
	switch (neighborType) {
	case NEIGHBOR_BELOW:     ny = ny - 1; break;
	case NEIGHBOR_ABOVE:     ny = ny + 1; break;
	case NEIGHBOR_LEFT:      nx = nx + 1; break;
	case NEIGHBOR_RIGHT:     nx = nx - 1; break;
	case NEIGHBOR_BEHIND:    nz = nz - 1; break;
	case NEIGHBOR_FRONT:     nz = nz + 1; break;
	default:                 ASSERT(0, "Valid neighbor type %d", neighborType); break;
	}

	neighbor = this->hashTable->GetCell(nx, ny, nz);
	if (neighbor == nullptr && create) {
		neighbor = this->hashTable->AddCell(nx, ny, nz);
	}

	return neighbor;
}

