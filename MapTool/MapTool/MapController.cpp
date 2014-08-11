#include "StdAfx.h"
#include "MapController.h"


cMapController::cMapController(void) :
	m_editMode(EDIT_MODE::MODE_HEIGHTMAP)
{
}


cMapController::~cMapController(void)
{
}


// ���̸� ������ �о ������ �����Ѵ�.
bool cMapController::LoadHeightMap(const string &fileName)
{
	m_heightMapFileName = fileName;
	const bool result = m_terrain.CreateFromHeightMap(fileName, "empty" );

	NotifyObserver();
	return result;
}


// ���� ��ü�� ���� ���� �ؽ��ĸ� �ε��Ѵ�.
bool cMapController::LoadHeightMapTexture(const string &fileName)
{
	m_textFileName = fileName;
	const bool result = m_terrain.CreateTerrainTexture(fileName);

	NotifyObserver();
	return result;
}


// ���� ����.
bool cMapController::CreateDefaultTerrain()
{
	m_terrain.CreateTerrain(64, 64, 50.f, 8.f);
	m_terrain.CreateTerrainTexture( "../../media/terrain/grass014.jpg");

	NotifyObserver();
	return true;
}


// �� ���� ��� ����.
void cMapController::ChangeEditMode(EDIT_MODE::TYPE mode)
{
	m_editMode = mode;
}
