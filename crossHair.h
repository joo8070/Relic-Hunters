#pragma once
#include "gameNode.h"
class crossHair : public gameNode
{
private:
	image*     _img;  // 크로스헤어 이미지
	MYPOINT    _pos;  // 크로스헤어 이미지
	bool       _isReload;
	int        _frameCount;

	POINT _ptPos;            // 마우스 포인트 상대 좌표
public:
	crossHair() {}
	~crossHair() {}

public:
	HRESULT init();
	void render();
	void update();
	void release();

	void   setIsReload(bool isReload) { _isReload = isReload; }
	bool   getIsReload() { return _isReload; }
};

