#include "stdafx.h"
#include "objectManager.h"
#include "player.h"

HRESULT objectManager::init()
{
	return S_OK;
}

void objectManager::render()
{
	for (int i = 0; i < _vStageShipObject.size(); i++)
	{
		_vStageShipObject[i]->render();
	}
	for (int i = 0; i < _vStage1_1Object.size(); i++)
	{
		_vStage1_1Object[i]->render();
	}
	for (int i = 0; i < _vStageShopObject.size(); i++)
	{
		_vStageShopObject[i]->render();
	}

}

void objectManager::update()
{
	for (int i = 0; i < _vStageShipObject.size(); i++)
	{
		_vStageShipObject[i]->update();
	}
	for (int i = 0; i < _vStage1_1Object.size(); i++)
	{
		_vStage1_1Object[i]->update();
	}
	for (int i = 0; i < _vStageShopObject.size(); i++)
	{
		_vStageShopObject[i]->update();
	}

}

void objectManager::release()
{

}


void objectManager::setStageShip()
{
	MYPOINT _longBoxPos[7] = { {1000,760 }      // longBoxPos 오브젝트 위치
					  ,{2165,1700}, {2370,1700}
					  ,{2165,1550}, {2370,1550}
					  ,{2165,1400}, {2370,1400} };
	// --------------------  longBox -------------------- //
	int count = sizeof(_longBoxPos) / sizeof(_longBoxPos[0]);
	MYPOINT tempPos;
	for (int i = 0; i < count; i++)
	{
		object* temp = new object;
		temp->init(_longBoxPos[i], "longBox", true, BOX);
		_vStageShipObject.push_back(temp);
	}
	// --------------------  longBox -------------------- //

	tempPos.x = 1440;
	tempPos.y = 780;
	// --------------------  smallBox -------------------- //
	object* tempSmallBox = new object;
	tempSmallBox->init(tempPos, "smallBox", true, BOX);
	_vStageShipObject.push_back(tempSmallBox);
	// --------------------  smallBox -------------------- //


	// --------------------  튜토리얼 발판 -------------------- //

	tempPos.x = 1257;
	tempPos.y = 1050;

	object* tempSignBox = new object;
	tempSignBox->init(tempPos, "SignBox", true, DISPLAY);
	_vStageShipObject.push_back(tempSignBox);
	// --------------------  튜토리얼 발판 -------------------- //


	// --------------------  캐릭터 발판 -------------------- //
	object* tempCharSignBox0 = new object;
	tempPos.x = 1300;
	tempPos.y = 850;
	tempCharSignBox0->init(tempPos, "playerSignBox", false, DISPLAY);
	_vStageShipObject.push_back(tempCharSignBox0);


	object* tempCharSignBox1 = new object;
	tempPos.x = 1905;
	tempPos.y = 720;
	tempCharSignBox1->init(tempPos, "playerSignBox", false, DISPLAY);
	_vStageShipObject.push_back(tempCharSignBox1);
	// --------------------  캐릭터 발판 -------------------- //

	// --------------------  캐릭터 발판 홀로그램 -------------------- //
	object* tempPinky_HOLO = new object;
	tempPos.x -= 13;
	tempPos.y -= 100;
	tempPinky_HOLO->init(tempPos, "pinky_HOLO", true, HOLO);
	_vStageShipObject.push_back(tempPinky_HOLO);

	// --------------------  캐릭터 발판 홀로그램 -------------------- //

	// ------------------- 텔레포트 --------------------- //
	tempPos.x = 3100;
	tempPos.y = 570;
	for (int i = 0; i < 4; i++)
	{
		object* tempTel = new object;
		tempTel->setTeleportStageNumber(i + 1);
		tempPos.x += 300;
		if (i == 3)
			tempTel->init(tempPos, "teleporter_1", false, TELEPORT);

		else
			tempTel->init(tempPos, "teleporter_0", false, TELEPORT);

		_vStageShipObject.push_back(tempTel);
	}
	tempPos.x = 3090;
	tempPos.y = 620;
	for (int i = 0; i < 3; i++)
	{
		object* tempStageNum = new object;
		tempPos.x += 300;
		string str;
		if (i == 0)
		{
			str = "stageNumber" + to_string(i + 1);
		}
		else if( i == 1)
		{
			str = "bossNumber";
			tempPos.x += 35;
		}
		else
		{
			str = "shopNumber";
		}
		tempStageNum->init(tempPos, str.c_str(), false, DISPLAY);
		_vStageShipObject.push_back(tempStageNum);
	}

	// -------- 이펙트
	tempPos.x = 3100;
	tempPos.y = 470;
	for (int i = 0; i < 3; i++)
	{
		tempPos.x += 300;
		object* telporterTemp = new object;
		telporterTemp->init(tempPos, "teleportEffect", true, DISPLAY);
		_vStageShipObject.push_back(telporterTemp);
	}

	// ------------------- 텔레포트 --------------------- //

	tempPos.x = 3200;
	tempPos.y = 1350;
	// ------------------ 유물 박스 ------------------ //
	for (int i = 0; i < 4; i++)
	{
		string str = "relicBox" + to_string(i);
		tempPos.x += 300;
		object* tempRelicBox = new object;
		tempRelicBox->init(tempPos, str.c_str(), false, BOX);
		_vStageShipObject.push_back(tempRelicBox);
	}
	// ------------------ 유물 박스 ------------------ //

	//  ----------------- npc --------------------- //
	object* tempNpc = new object;
	tempPos.x = 3900;
	tempPos.y = 725;
	tempNpc->init(tempPos, "NPC", true, DISPLAY);
	_vStageShipObject.push_back(tempNpc);
	//  ----------------- npc --------------------- //

}

void objectManager::setStage1_1()
{
	MYPOINT _longBoxPos[] = { {2200,900},{2550,900},{2900,900},
							  {2200,1250},{2550, 1250},{2900,1250}, };
	// --------------------  longBox -------------------- //
	int count = sizeof(_longBoxPos) / sizeof(_longBoxPos[0]);
	MYPOINT tempPos;
	for (int i = 0; i < count; i++)
	{
		object* temp = new object;
		temp->init(_longBoxPos[i], "longBox", true, BOX);
		_vStage1_1Object.push_back(temp);
	}
	// --------------------  longBox -------------------- //


	// --------------------  smallBox -------------------- //
	for (int i = 0; i < 12; i++)
	{
		MYPOINT tempPos1;
		tempPos1.x = 4217 + (i % 4) * 400;
		tempPos1.y = 780 + (i / 4) * 300;
		object* tempSmallBox = new object;
		tempSmallBox->init(tempPos1, "smallBox", true, BOX);
		_vStage1_1Object.push_back(tempSmallBox);
	}
	// --------------------  smallBox -------------------- //

}

void objectManager::setStageShop()
{
	MYPOINT tempPos;

	// ----------------- npc --------------------- //
	object* tempNpc = new object;
	tempPos.x = 1030;
	tempPos.y = 300;
	tempNpc->init(tempPos, "NPC", true, DISPLAY);
	IMAGEMANAGER->findImage("NPC")->setFrameY(1);
	_vStageShopObject.push_back(tempNpc);
	// ----------------- npc --------------------- //

	// ----------- shop Item Desk ----------- //
	tempPos.x = 900;
	tempPos.y = 400;
	object* tempShopDesk = new object;
	tempShopDesk->init(tempPos, "shopDesk", false, BOX);
	_vStageShopObject.push_back(tempShopDesk);
	// ----------- shop Item Desk ----------- //

	// ----------- teleport to ship ----------- //
	tempPos.x = 1850;
	tempPos.y = 800;
	object* tempTeleport = new object;
	tempTeleport->setTeleportStageNumber(1);
	tempTeleport->init(tempPos, "teleporter_0", false, TELEPORT);
	_vStageShopObject.push_back(tempTeleport);
	// ----------- teleport to ship  ----------- //

	tempPos.x = 1850;
	tempPos.y = 690;
	object* telporterEffectTemp = new object;
	telporterEffectTemp->init(tempPos, "teleportEffect", true, DISPLAY);
	_vStageShopObject.push_back(telporterEffectTemp);


}

void objectManager::setStage1_1Teleport(MYPOINT pos)
{
	object* tempTeleport = new object;
	tempTeleport->setTeleportStageNumber(999);
	tempTeleport->init(pos, "teleporter_0", false, TELEPORT);
	_vStage1_1Object.push_back(tempTeleport);

	pos.y -= 110;
	object* telporterEffectTemp = new object;
	telporterEffectTemp->init(pos, "teleportEffect", true, DISPLAY);
	_vStage1_1Object.push_back(telporterEffectTemp);
}

void objectManager::setSelectCharacter(bool isJimmy)
{
	if (isJimmy)
	{
		object* tempJimmy_HOLO = new object;
		MYPOINT tempPos;
		tempPos.x -= 13;
		tempPos.y -= 100;
		tempJimmy_HOLO->init(tempPos, "jimmy_HOLO", true, HOLO);
		_vStageShipObject.push_back(tempJimmy_HOLO);
	}
	else
	{
		object* tempPinky_HOLO = new object;
		MYPOINT tempPos;
		tempPos.x -= 13;
		tempPos.y -= 100;
		tempPinky_HOLO->init(tempPos, "pinky_HOLO", true, HOLO);
		_vStageShipObject.push_back(tempPinky_HOLO);
	}
	
}

