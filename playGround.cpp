#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화 함수
HRESULT playGround::init()
{
	gameNode::init(true);
	imageLoad();
	soundLoad();

	ShowCursor(false);// 마우스 숨김
	clipCursor();     // 마우스 렉트안에 가두기

	_player = new player;
	_player->init();

	_stageManager = new stageManager;
	_stageManager->init();

	_uiManager = new UIManager;
	_uiManager->init();
	//상호 참조
	_player->setStageManagerMemoryAddressLink(_stageManager);
	_stageManager->setPlayerMemoryAddressLink(_player);
	_uiManager->setPlayerMemoryAddressLink(_player);
	_uiManager->setStageManagerMemoryAddressLink(_stageManager);

	_nowState = PLAYSTATE::GAME_READY;   // 게임 상태

	_intro = IMAGEMANAGER->findImage("intro");
	_loading = IMAGEMANAGER->findImage("loading");
	_isStart = true;
	return S_OK;
}

//메모리 해제
void playGround::release()
{

}
//연산
void playGround::update()
{
	gameNode::update();

	switch (_nowState)
	{
	case PLAYSTATE::GAME_READY:
		gameReady();
		break;
	case PLAYSTATE::GAME_START:
		gameStart();
		break;
	case PLAYSTATE::GAME_OVER:
		gameOver();
		break;
	}

}

//그리기 전용
void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================

	switch (_nowState)
	{
	case PLAYSTATE::GAME_READY:
		CAMERAMANAGER->frameRender(getMemDC(), _intro, 0, 0, _intro->getFrameX(), _intro->getFrameY());
		CAMERAMANAGER->frameRender(getMemDC(), _loading, WINSIZEX / 2, WINSIZEY - 100, _loading->getFrameX(), _loading->getFrameY());
		break;
	case PLAYSTATE::GAME_START:
		_stageManager->render();
		EFFECTMANAGER->render();
		_player->render();
		_uiManager->render();

		// --------------------- 텍스트 출력 --------------------- //
//sprintf_s(_buffer, ("_player.x : %f, _player.y : %f"), _player->getPlayerPos().x, _player->getPlayerPos().y);
//TextOut(getMemDC(), 10, 70, _buffer, strlen(_buffer));

//sprintf_s(_buffer, ("지금 스테이지 : %s"), _stageManager->getNowStage().c_str());
//TextOut(getMemDC(), 10, 90, _buffer, strlen(_buffer));



// --------------------- 텍스트 출력 --------------------- //

		SetTextColor(getMemDC(), RGB(255, 255, 255));
		SetBkMode(getMemDC(), TRANSPARENT);
		_font = CreateFont(48, 0, 0, 0, FW_BOLD, false, false, false, HANGUL_CHARSET,
			0, 0, 0, 0, TEXT("CookieRunOTF Bold"));
		_oldFont = (HFONT)SelectObject(getMemDC(), _font);

		sprintf_s(_buffer, ("%d"), _player->getCoin());
		TextOut(getMemDC(), WINSIZEX * 0.5f - 10, 54, _buffer, strlen(_buffer));


		sprintf_s(_buffer, ("%d  |  %d"), _player->getNowWeapon()->getCarryBullet(), _player->getNowWeapon()->getCurrentBullet());
		TextOut(getMemDC(), 170, 720, _buffer, strlen(_buffer));

		if (_player->getHP() > 50 && _player->getHP() < 100)
			SetTextColor(getMemDC(), RGB(255, 125, 13));
		else if (_player->getHP() < 50)
			SetTextColor(getMemDC(), RGB(255, 0, 0));

		sprintf_s(_buffer, ("HP : %d"), _player->getHP());
		TextOut(getMemDC(), 170, 820, _buffer, strlen(_buffer));

		SelectObject(getMemDC(), _oldFont);
		DeleteObject(_font);
		TIMEMANAGER->render(getMemDC());
		SetTextColor(getMemDC(), RGB(0, 0, 0));


		break;
	case PLAYSTATE::GAME_OVER:
		break;
	}
	//=============================================
	_backBuffer->render(getHDC(), 0, 0);
}

void playGround::imageLoad()
{
	// ------------------------------------- 크로스헤어 이미지 ------------------------------------- //
	IMAGEMANAGER->addImage("crossHair_Standard", "Image/crossHair/crosshair.bmp", 42, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("crossHair_Reload", "Image/crossHair/reload.bmp", 504, 42, 12, 1, true, RGB(255, 0, 255));
	// ------------------------------------- 크로스헤어 이미지 ------------------------------------- //

	// ------------------------------------- 스테이지 이미지 ------------------------------------- //
	IMAGEMANAGER->addImage("STAGE_1_1", "Image/map/stage1-1.bmp", 6280, 2056, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("STAGE_1_1_COLLISION", "Image/map/stage1-1_collision.bmp", 6280, 2056, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("STAGE_BOSS", "Image/map/stageBoss.bmp", 5000, 2733, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("STAGE_BOSS_COLLISION", "Image/map/stageBoss_collision.bmp", 5000, 2733, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("STAGE_SHIP", "Image/map/ship.bmp", 5500, 2000, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("STAGE_SHIP_COLLISION", "Image/map/ship_collision.bmp", 5500, 2000, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("STAGE_SHOP", "Image/map/shop.bmp", 3000, 1080, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("STAGE_SHOP_COLLISION", "Image/map/shop_collision.bmp", 3000, 1080, false, RGB(255, 0, 255));
	// ------------------------------------- 스테이지 이미지 ------------------------------------- //

	// ------------------------------------- 플레이어 이미지 ------------------------------------- //
	// 지미
	IMAGEMANAGER->addFrameImage("jimmy_IDLE", "Image/player/jimmy/IDLE.bmp", 1188, 252, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("jimmy_WALK", "Image/player/jimmy/WALK.bmp", 666, 252, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("jimmy_RUN", "Image/player/jimmy/RUN.bmp", 666, 264, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("jimmy_HIT", "Image/player/jimmy/HIT.bmp", 216, 270, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("jimmy_DEATH", "Image/player/jimmy/DEATH.bmp", 924, 270, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("jimmy_DASH", "Image/player/jimmy/DASH.bmp", 342, 270, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("jimmy_HOLO", "Image/player/jimmy/HOLO.bmp", 3078, 234, 27, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("jimmy_TELEPORT", "Image/player/jimmy/TELEPORT.bmp", 792, 240, 8, 2, true, RGB(255, 0, 255));
	// 핑키
	IMAGEMANAGER->addFrameImage("pinky_HOLO", "Image/player/pinky/HOLO.bmp", 3483, 240, 27, 2, true, RGB(255, 0, 255));


	// NPC
	IMAGEMANAGER->addFrameImage("NPC", "Image/npc/IDLE.bmp", 900, 222, 10, 2, true, RGB(255, 0, 255));
	// ------------------------------------- 플레이어 이미지 ------------------------------------- //

	// ------------------------------------- 적 이미지 ------------------------------------- //
									// ====== tutle ====== //
	IMAGEMANAGER->addFrameImage("tutle1_WALK", "Image/enemy/tutle/WALK1.bmp", 468, 204, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tutle1_IDLE", "Image/enemy/tutle/IDLE1.bmp", 864, 210, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tutle1_HIT", "Image/enemy/tutle/HIT1.bmp", 144, 234, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tutle1_DEATH", "Image/enemy/tutle/DEATH1.bmp", 1116, 234, 13, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("tutle2_WALK", "Image/enemy/tutle/WALK2.bmp", 468, 204, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tutle2_IDLE", "Image/enemy/tutle/IDLE2.bmp", 864, 210, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tutle2_HIT", "Image/enemy/tutle/HIT2.bmp", 144, 234, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tutle2_DEATH", "Image/enemy/tutle/DEATH2.bmp", 1116, 234, 13, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("tutle3_WALK", "Image/enemy/tutle/WALK3.bmp", 468, 204, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tutle3_IDLE", "Image/enemy/tutle/IDLE3.bmp", 864, 210, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tutle3_HIT", "Image/enemy/tutle/HIT3.bmp", 144, 234, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tutle3_DEATH", "Image/enemy/tutle/DEATH3.bmp", 1116, 234, 13, 2, true, RGB(255, 0, 255));


	// ====== duck ====== //
	IMAGEMANAGER->addFrameImage("duck1_WALK", "Image/enemy/duck/WALK1.bmp", 936, 210, 13, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("duck1_IDLE", "Image/enemy/duck/IDLE1.bmp", 414, 204, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("duck1_HIT", "Image/enemy/duck/HIT1.bmp", 138, 204, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("duck1_DEATH", "Image/enemy/duck/DEATH1.bmp", 828, 204, 12, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("duck2_WALK", "Image/enemy/duck/WALK2.bmp", 936, 210, 13, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("duck2_IDLE", "Image/enemy/duck/IDLE2.bmp", 414, 204, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("duck2_HIT", "Image/enemy/duck/HIT2.bmp", 138, 204, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("duck2_DEATH", "Image/enemy/duck/DEATH2.bmp", 828, 204, 12, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("duck3_WALK", "Image/enemy/duck/WALK3.bmp", 936, 210, 13, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("duck3_IDLE", "Image/enemy/duck/IDLE3.bmp", 414, 204, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("duck3_HIT", "Image/enemy/duck/HIT3.bmp", 138, 204, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("duck3_DEATH", "Image/enemy/duck/DEATH3.bmp", 828, 204, 12, 2, true, RGB(255, 0, 255));

	// ====== boss ====== //
	IMAGEMANAGER->addFrameImage("boss_WALK", "Image/enemy/boss/WALK.bmp", 1458, 540, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_IDLE", "Image/enemy/boss/IDLE.bmp", 3150, 522, 14, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_HIT", "Image/enemy/boss/HIT.bmp", 450, 522, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_DEATH", "Image/enemy/boss/DEATH.bmp", 5148, 540, 13, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_EGG", "Image/enemy/boss/EGG.bmp", 5952, 246, 32, 1, true, RGB(255, 0, 255));


	// ------------------------------------- 적 이미지 ------------------------------------- //

	// ------------------------------------- 오브젝트 이미지 ------------------------------------- //
	IMAGEMANAGER->addFrameImage("smallBox", "Image/object/smallBoxSprite.bmp", 288, 126, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("smallBoxCollapse", "Image/object/smallBoxCollapse.bmp", 5016, 126, 22, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("longBox", "Image/object/longBoxSprite.bmp", 558, 144, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("longBoxCollapse", "Image/object/longBoxCollapse.bmp", 7392, 177, 22, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SignBox", "Image/object/SignBox.bmp", 2310, 129, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("playerSignBox", "Image/object/playerSignBox.bmp", 81, 58, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("teleporter_0", "Image/object/teleporter_0.bmp", 135, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("teleporter_1", "Image/object/teleporter_1.bmp", 135, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("relicBox0", "Image/object/relicBox0.bmp", 110, 61, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("relicBox1", "Image/object/relicBox1.bmp", 110, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("relicBox2", "Image/object/relicBox2.bmp", 110, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("relicBox3", "Image/object/relicBox3.bmp", 110, 77, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("relicBox4", "Image/object/relicBox4.bmp", 110, 77, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stageNumber1", "Image/object/stageNumber1.bmp", 156, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bossNumber", "Image/object/bossNumber.bmp", 93, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("shopNumber", "Image/object/shopNumber.bmp", 93, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("shopDesk", "Image/object/shopDesk.bmp", 352, 170, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("teleportEffect", "Image/object/teleportEffect.bmp", 2193, 117, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("eButton", "Image/object/eButton.bmp", 176, 28, 8, 1, true, RGB(255, 0, 255));

	// ------------------------------------- 오브젝트 이미지 ------------------------------------- //

	// ------------------------------------- Gun 이미지 ------------------------------------- //
	IMAGEMANAGER->addFrameImage("heavyGun", "Image/gun/heavy.bmp", 108, 60, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("pistolGun", "Image/gun/pistol.bmp", 114, 60, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("shotGun", "Image/gun/shotgun.bmp", 192, 66, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossGun", "Image/gun/bossGun.bmp", 436, 100, 2, 1, true, RGB(255, 0, 255));
	// ------------------------------------- Gun 이미지 ------------------------------------- //

	// ------------------------------------- bullet 이미지 ------------------------------------- //
	IMAGEMANAGER->addImage("pistolBullet", "Image/bullet/pistolBullet.bmp", 26, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("shotgunBullet", "Image/bullet/shotgunBullet.bmp", 23, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("heavyBullet", "Image/bullet/heavyBullet.bmp", 348, 25, 12, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("bossBullet1", "Image/bullet/bossBullet1.bmp", 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bossBullet2", "Image/bullet/bossBullet2.bmp", 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossBullet3", "Image/bullet/bossBullet3.bmp", 836, 60, 12, 1, true, RGB(255, 0, 255));
	// ------------------------------------- bullet 이미지 ------------------------------------- //


	// ------------------------------------- UI 이미지 ------------------------------------- //
	IMAGEMANAGER->addImage("jimmy_face_UI", "Image/UI/face/jimmy.bmp", 96, 81, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("star_UI", "Image/UI/star.bmp", 175, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("HPBARIMG", "Image/UI/HPBARIMG.bmp", 100, 87, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BULLETIMG", "Image/UI/BULLET.bmp", 100, 87, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gameover_UI", "Image/UI/gameover.bmp", 600, 309, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("1-1_InterUI", "Image/UI/ShowStage/1-1.bmp", 12116, 122, 13, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_InterUI", "Image/UI/ShowStage/boss.bmp", 12116, 122, 13, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("shop_InterUI", "Image/UI/ShowStage/shop.bmp", 7276, 102, 13, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("intro", "Image/UI/intro.bmp", 19200, 900, 12, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("loading", "Image/UI/loading.bmp", 933, 50, 4, 1, true, RGB(255, 0, 255));

	// ------------------------------------- UI 이미지 ------------------------------------- //

	// -------------------------------------- 이펙트 이미지 --------------------------------- //
	IMAGEMANAGER->addImage("runL_Effect", "Image/effect/runL_Effect.bmp", 156, 14, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("runR_Effect", "Image/effect/runR_Effect.bmp", 156, 14, true, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("runL_Effect", "runL_Effect", 156, 14, 26, 14, 10.0f, 1);
	EFFECTMANAGER->addEffect("runR_Effect", "runR_Effect", 156, 14, 26, 14, 10.0f, 1);


	IMAGEMANAGER->addImage("pistol_effect", "Image/effect/pistol_effect.bmp", 144, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("shotgun_effect", "Image/effect/shotgun_effect.bmp", 144, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("heavygun_effect", "Image/effect/heavygun_effect.bmp", 144, 24, true, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("pistol_effect", "pistol_effect", 144, 24, 24, 24, 10.0f, 10);
	EFFECTMANAGER->addEffect("shotgun_effect", "shotgun_effect", 144, 24, 24, 24, 10.0f, 10);
	EFFECTMANAGER->addEffect("heavygun_effect", "heavygun_effect", 144, 24, 24, 24, 10.0f, 10);


	IMAGEMANAGER->addImage("findPlayer_effect", "Image/effect/findPlayer.bmp", 84, 34, true, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("findPlayer_effect", "findPlayer_effect", 84, 34, 14, 34, 5.0f, 30);

	IMAGEMANAGER->addImage("findPlayerBoss_effect", "Image/effect/findPlayerBoss.bmp", 252, 102, true, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("findPlayerBoss_effect", "findPlayerBoss_effect", 252, 102, 42, 102, 10.0f, 1);

	// -------------------------------------- 이펙트 이미지 -------------------------------- //

	// -------------------------------------- 아이템 이미지 -------------------------------- //
	IMAGEMANAGER->addFrameImage("coin_item", "Image/item/coin.bmp", 109, 25, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("heavy_bullet_item", "Image/item/heavy.bmp", 800, 52, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("pistol_bullet_item", "Image/item/pistol.bmp", 800, 52, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("shotgun_bullet_item", "Image/item/shotgun.bmp", 800, 52, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("health_item", "Image/item/health.bmp", 300, 30, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pistol_gun_item", "Image/item/pistol_gun_item.bmp", 34, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("heavy_gun_item", "Image/item/heavy_gun_item.bmp", 32, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("shotgun_gun_item", "Image/item/shotgun_gun_item.bmp", 60, 18, true, RGB(255, 0, 255));
	//ITEM_GUN
	// -------------------------------------- 아이템 이미지 -------------------------------- //



}

void playGround::soundLoad()
{
	SOUNDMANAGER->addSound("브금", "sound/브금.mp3", true, false);
	SOUNDMANAGER->addSound("동전", "sound/동전.wav", false, false);
	SOUNDMANAGER->addSound("권총", "sound/권총.wav", false, false);
	SOUNDMANAGER->addSound("샷건", "sound/샷건.wav", false, false);
	SOUNDMANAGER->addSound("장전", "sound/장전소리.mp3", false, false);
	SOUNDMANAGER->addSound("총줍는사운드", "sound/총줍는사운드.wav", false, false);


}

void playGround::gameReady()
{
	_nowState = PLAYSTATE::GAME_READY;

	_introCount++;
	if (_introCount % 10 == 0)
	{
		_intro->setFrameX(_intro->getFrameX() + 1);
		if (_intro->getFrameX() >= _intro->getMaxFrameX())
		{
			_intro->setFrameX(0);
		}
		_introCount = 0;
	}
	_loadingCount++;
	if (_loadingCount % 50 == 0)
	{
		_loading->setFrameX(_loading->getFrameX() + 1);
		if (_loading->getFrameX() >= _loading->getMaxFrameX())
		{
			_loading->setFrameX(0);
		}
		_loadingCount = 0;
	}

	if (_isStart)
	{
		_startCount++;

		if (_startCount > 100)
		{
			_nowState = PLAYSTATE::GAME_START;
			SOUNDMANAGER->play("브금", 0.1f);
			CAMERAMANAGER->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, 6280 - WINSIZEX, 2056 - WINSIZEY);
			_startCount = 0;
		}
	}

}

void playGround::gameStart()
{
	_nowState = PLAYSTATE::GAME_START;
	_player->update();
	_stageManager->update();
	EFFECTMANAGER->update();
	CAMERAMANAGER->update();
	_uiManager->update();

}

void playGround::gameOver()
{
	_nowState = PLAYSTATE::GAME_OVER;
}

void playGround::clipCursor()
{
	RECT rc2;
	POINT lt, rb;
	GetClientRect(_hWnd, &rc2);

	lt.x = rc2.left;
	lt.y = rc2.top;
	rb.x = rc2.right;
	rb.y = rc2.bottom;

	ClientToScreen(_hWnd, &lt);
	ClientToScreen(_hWnd, &rb);

	rc2.left = lt.x;
	rc2.top = lt.y;
	rc2.right = rb.x;
	rc2.bottom = rb.y;
	ClipCursor(&rc2);
}
