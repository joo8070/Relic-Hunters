#include "stdafx.h"
#include "itemManager.h"

HRESULT itemManager::init()
{

	return S_OK;
}

void itemManager::render()
{
	for (int i = 0; i < _vItem.size(); i++)
	{
		if (_vItem[i]->getStageName() == _nowStage)
			_vItem[i]->render();
	}

}

void itemManager::update()
{
	for (int i = 0; i < _vItem.size(); i++)
	{
		if (_vItem[i]->getStageName() == _nowStage)
		_vItem[i]->update();

		if (_vItem[i]->getIsDisappear())
		{
			removeItemIndex(i);
		}
	}


}

void itemManager::release()
{

}

void itemManager::initCoinItem(string imgName, MYPOINT pos, string nowStageName)
{
	item* temp;
	temp = new item;
	temp->init(imgName, pos, ITEM_COIN, nowStageName);
	_vItem.push_back(temp);
}

void itemManager::initGunItem(string imgName, MYPOINT pos, string nowStageName)
{
	item* temp;
	temp = new item;
	temp->init(imgName, pos, ITEM_GUN, nowStageName);
	_vItem.push_back(temp);
}

void itemManager::initHPItem(string imgName, MYPOINT pos, string nowStageName)
{
	item* temp;
	temp = new item;
	temp->init(imgName, pos, ITEM_HP, nowStageName);
	_vItem.push_back(temp);
}

void itemManager::initBulletItem(string imgName, MYPOINT pos, string nowStageName)
{
	item* temp;
	temp = new item;
	temp->init(imgName, pos, ITEM_BULLET, nowStageName);
	_vItem.push_back(temp);
}



