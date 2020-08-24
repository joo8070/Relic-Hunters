#pragma once
#include "gameNode.h"
#include "object.h"
#include <vector>

class objectManager : public gameNode
{
private:
	typedef vector<object*>           vObject;
	typedef vector<object*>::iterator viObject;

private:
	vObject  _vStageShipObject;	 // stageShip ø¿∫Í¡ß∆Æ ∫§≈Õ
	vObject  _vStage1_1Object;   // stage1_1  ø¿∫Í¡ß∆Æ ∫§≈Õ
	vObject  _vStageShopObject;  // stageShop ø¿∫Í¡ß∆Æ ∫§≈Õ

public:
	objectManager() {}
	~objectManager() {}
public:
	HRESULT init();
	void render();
	void update();
	void release();
public:

public:
	void setStageShip(); // ship Ω∫≈◊¿Ã¡ˆ ºº∆√
	void setStage1_1();
	void setStageShop();
	void setStage1_1Teleport(MYPOINT pos);
	void setSelectCharacter(bool isJimmy);

public:
	void removeShipObject(int arrNum) { _vStageShipObject.erase(_vStageShipObject.begin() + arrNum); }
	void removeStage1_1Object(int arrNum) { _vStage1_1Object.erase(_vStage1_1Object.begin() + arrNum); }
	void removeShopObject(int arrNum) { _vStageShopObject.erase(_vStageShopObject.begin() + arrNum); }

public:
	vObject getVStageShipObject() { return _vStageShipObject; } //ShipObject ∫§≈Õ getter
	vObject getVStage1_1Object()  { return _vStage1_1Object; }  //1_1Object  ∫§≈Õ getter
	vObject getVStageShopObject() { return _vStageShopObject; }  //ShopObject ∫§≈Õ getter
};

