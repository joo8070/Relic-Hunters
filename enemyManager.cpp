#include "stdafx.h"
#include "enemyManager.h"
HRESULT enemyManager::init()
{
	return S_OK;
}

void enemyManager::render()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->render();
	}
}

void enemyManager::update(string nowStageName, MYPOINT playerPosion)
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->update(nowStageName, playerPosion);
		if (_vEnemy[i]->getIsDead())
		{
			removeEnemy(i);
		}
	}

}


void enemyManager::release()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		delete _vEnemy[i];
	}
	_vEnemy.clear();

}

void enemyManager::setEnemy(MYPOINT pos)
{
	enemy* tempEnemy = new gruntEnemy;
	tempEnemy->init(_enemyName[RND->getInt(6)], pos);
	_vEnemy.push_back(tempEnemy);
}



void enemyManager::removeEnemy(int arrNum)
{
	_vEnemy.erase(_vEnemy.begin() + arrNum);
}
