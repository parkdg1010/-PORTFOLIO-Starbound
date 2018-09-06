#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init(void)
{
	//로딩클래스 초기화
	_loading = new loading;
	_loading->init(); //로딩화면 이미지와 로딩 프로그래스바

	//이미지 및 사운드 로딩
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release(void)
{
	//로딩클래스 해제
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingScene::update(void)
{
	//로딩클래스 업데이트
	_loading->update(); //로딩바 업데이트

	//로딩완료후 씬변경
	if (_loading->loadingDone()) //loadingImage와 loadingSound의 인자값으로 addimage, addframeimage하고 다 되면 true
	{
		SCENEMANAGER->loadScene("시작"); //게임씬으로 전환
	}
}

void loadingScene::render(void)
{
	//로딩클래스 렌더
	_loading->render();
}

//로딩이미지 함수(이곳에 이미지를 전부 넣어라)
void loadingScene::loadingImage()
{
	//_loading->loadImage();
	//_loading->loadFrameImage();
	//_loading->loadSound();

	//맵툴ui
	loadingMapToolImage();
	
	//인트로
	loadingIntroImage();

	//타일
	loadingTiles();

	//배경
	_loading->loadImage("배경Top0", "Texture/object/background/top/back0.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("배경Top1", "Texture/object/background/top/back1.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("배경Top2", "Texture/object/background/top/back2.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("배경Top3", "Texture/object/background/top/back3.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("배경Top4", "Texture/object/background/top/back4.bmp", 1280, 720, true, MAGENTA);

	_loading->loadImage("배경Bot0", "Texture/object/background/bot/back0.bmp", 512, 512);
	_loading->loadImage("배경Bot1", "Texture/object/background/bot/back1.bmp", 512, 512);
	_loading->loadImage("배경Bot2", "Texture/object/background/bot/back2.bmp", 512, 512);
	_loading->loadImage("배경Bot3", "Texture/object/background/bot/back3.bmp", 512, 512);

	//오브젝트
	loadingObjects();

	//플레이어
	loadingPlayer();

	//아이템
	loadingItem();

	//ui
	_loading->loadFrameImage("숫자", "Texture/ui/numbers.bmp", 160, 16, 10, 1);
	_loading->loadImage("빈패드", "Texture/ui/empty.bmp", 18, 18, true, MAGENTA);
	
	//IMAGEMANAGER->addImage("mountain", "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	//백그라운드 이미지
	//_loading->loadImage("mountain", "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

}

//로딩사운드 함수(이곳에 사운드를 전부 넣어라)
void loadingScene::loadingSound()
{
}

void loadingScene::loadingEffect()
{
}


void loadingScene::loadingMapToolImage()
{
	//타일
	_loading->loadFrameImage("타일아이콘", "Texture/mapTool/icons/TileIcons_360x216x10x6.bmp", 360, 216, 10, 6);
	_loading->loadFrameImage("오브젝트아이콘", "Texture/mapTool/icons/ObjectIcons_360x216_10x6.bmp", 360, 216, 10, 6);
	_loading->loadFrameImage("아이템아이콘", "Texture/mapTool/icons/itemIcons_360x216_10x6.bmp", 360, 216, 10, 6);

	_loading->loadImage("큰월드", "Texture/maptool/ui/bigWorld_36x36.bmp", 36, 36, true, MAGENTA);
	_loading->loadImage("중간월드", "Texture/maptool/ui/midWorld_36x36.bmp", 36, 36, true, MAGENTA);
	_loading->loadImage("작은월드", "Texture/maptool/ui/smallWorld_36x36.bmp", 36, 36, true, MAGENTA);
	_loading->loadImage("월드삭제", "Texture/maptool/ui/eraseWorld_36x36.bmp", 36, 36, true, MAGENTA);

	//UI
	_loading->loadImage("맵툴UI", "Texture/maptool/ui/CtrlInterface_503x486.bmp", 503, 486, true, MAGENTA);
	_loading->loadFrameImage("맵툴표시줄", "Texture/maptool/ui/mapTool_134x70_1x2.bmp", 134, 70, 1, 2);
	_loading->loadFrameImage("맵툴최소화", "Texture/maptool/ui/underbar_44x70_1x2.bmp", 44, 70, 1, 2);
	_loading->loadFrameImage("맵세이브UI", "Texture/maptool/ui/save_134x70_1x2.bmp", 134, 70, 1, 2);
	_loading->loadFrameImage("맵로드UI", "Texture/maptool/ui/load_134x70_1x2.bmp", 134, 70, 1, 2);
	_loading->loadFrameImage("크기태그", "Texture/maptool/ui/worldTag2_260x38_4x1.bmp", 260, 38, 4, 1);
	_loading->loadFrameImage("지형태그", "Texture/maptool/ui/terrainTag_260x38_4x1.bmp", 260, 38, 4, 1);
	_loading->loadFrameImage("아이템태그", "Texture/maptool/ui/itemTag_260x38_4x1.bmp", 260, 38, 4, 1);
	_loading->loadFrameImage("오브젝트태그", "Texture/maptool/ui/furnitureTag_260x38_4x1.bmp", 260, 38, 4, 1);
	_loading->loadFrameImage("에너미태그", "Texture/maptool/ui/enemyTag_260x38_4x1.bmp", 260, 38, 4, 1);
	_loading->loadImage("드래그", "Texture/maptool/ui/dragRc.bmp", 1280, 720);
}

void loadingScene::loadingIntroImage()
{
	_loading->loadImage("우주", "Texture/intro/space.bmp", 1280, 720);
	_loading->loadImage("별", "Texture/intro/introStar.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("지구", "Texture/intro/planet2.bmp", 1626, 1626, true, MAGENTA);
	_loading->loadImage("로고", "Texture/intro/logo.bmp", 316, 106, true, MAGENTA);

	_loading->loadFrameImage("시작게임", "Texture/intro/startgame_334x88_2x1.bmp", 334, 88, 1, 2);
	_loading->loadFrameImage("시작맵툴", "Texture/intro/maptool_286x88_2x1.bmp", 286, 88, 1, 2);
	_loading->loadFrameImage("시작옵션", "Texture/intro/options_236x88_2x1.bmp", 236, 88, 1, 2);
	_loading->loadFrameImage("시작나가기", "Texture/intro/quit_188x88_2x1.bmp", 188, 88, 1, 2);
}

void loadingScene::loadingTiles()
{
	_loading->loadFrameImage("TILE_BRICK", "Texture/tiles/front/brick_240x432_5x9.bmp", 240, 432, 5, 9);
	_loading->loadFrameImage("TILE_COBBLEBRICK", "Texture/tiles/front/cobblestonebrick_240x432_5x9.bmp", 240, 432, 5, 9);
	_loading->loadFrameImage("TILE_CONCRETE", "Texture/tiles/front/concrete_240x432_5x9.bmp", 240, 432, 5, 9);
	_loading->loadFrameImage("TILE_DARKWOOD", "Texture/tiles/front/darkwood_240x432_5x9.bmp", 240, 432, 5, 9);
	_loading->loadFrameImage("TILE_DIRT", "Texture/tiles/front/dirt_240x432_5x9.bmp", 240, 432, 5, 9);
	_loading->loadFrameImage("TILE_FULLWOOD1", "Texture/tiles/front/fullwood1_240x432_5x9.bmp", 240, 432, 5, 9);
	_loading->loadFrameImage("TILE_FULLWOOD2", "Texture/tiles/front/fullwood2_240x432_5x9.bmp", 240, 432, 5, 9);
	_loading->loadFrameImage("TILE_LOG", "Texture/tiles/front/log_240_432_5x9.bmp", 240, 432, 5, 9);
	_loading->loadFrameImage("TILE_PETALBLOCK", "Texture/tiles/front/petalblock_240x432_5x9.bmp", 240, 432, 5, 9);
	_loading->loadFrameImage("TILE_ROOF", "Texture/tiles/front/rooftiles_240x432_5x9.bmp", 240, 432, 5, 9);

	_loading->loadFrameImage("BACKTILE_BRICK", "Texture/tiles/back/brick_240x432_5x9.bmp", 240, 432, 5, 9);
	_loading->loadFrameImage("BACKTILE_COBBLEBRICK", "Texture/tiles/back/cobblestonebrick_240x432_5x9.bmp", 240, 432, 5, 9);
	_loading->loadFrameImage("BACKTILE_CONCRETE", "Texture/tiles/back/concrete_240x432_5x9.bmp", 240, 432, 5, 9);
	_loading->loadFrameImage("BACKTILE_DARKWOOD", "Texture/tiles/back/darkwood_240x432_5x9.bmp", 240, 432, 5, 9);
	_loading->loadFrameImage("BACKTILE_DIRT", "Texture/tiles/back/dirt_240x432_5x9.bmp", 240, 432, 5, 9);
	_loading->loadFrameImage("BACKTILE_FULLWOOD1", "Texture/tiles/back/fullwood1_240x432_5x9.bmp", 240, 432, 5, 9);
	_loading->loadFrameImage("BACKTILE_FULLWOOD2", "Texture/tiles/back/fullwood2_240x432_5x9.bmp", 240, 432, 5, 9);
	_loading->loadFrameImage("BACKTILE_LOG", "Texture/tiles/back/log_240_432_5x9.bmp", 240, 432, 5, 9);
	_loading->loadFrameImage("BACKTILE_PETALBLOCK", "Texture/tiles/back/petalblock_240x432_5x9.bmp", 240, 432, 5, 9);
	_loading->loadFrameImage("BACKTILE_ROOF", "Texture/tiles/back/rooftiles_240x432_5x9.bmp", 240, 432, 5, 9);
}

void loadingScene::loadingObjects()
{
	_loading->loadFrameImage("나무상자1", "Texture/object/box/woodencrate1_288x864_2x9.bmp", 288, 864, 2, 9);
	_loading->loadImage("나무상자1_아이콘", "Texture/object/box/woodencrate1icon.bmp", 36, 36);
	_loading->loadFrameImage("트리전구", "Texture/object/funiture/fairylights/fairylights_128x32_2x1.bmp", 128, 32, 2, 1);
	_loading->loadImage("트리전구_아이콘", "Texture/object/funiture/fairylights/fairylightsicon.bmp", 36, 36);
	_loading->loadFrameImage("장식등", "Texture/object/funiture/ornatetorch/ornatetorch_256x480_4x5.bmp", 256, 480, 4, 5);
}

void loadingScene::loadingItem()
{
	_loading->loadImage("우주검", "Texture/item/weapons/melee/broadsword/astrosabredeluxe.bmp", 48, 204, true, MAGENTA);
}

void loadingScene::loadingPlayer()
{
	_loading->loadFrameImage("PLAYER_IDLE", "Texture/character/nuru/idle_84x256_1x2.bmp", 84, 256, 1, 2);
	_loading->loadFrameImage("PLAYER_RUN", "Texture/character/nuru/walk,run_672x256_8x2.bmp", 672, 256, 8, 2);
	_loading->loadFrameImage("PLAYER_JUMP", "Texture/character/nuru/jump_336x256_4x2.bmp", 336, 256, 4, 2);
	_loading->loadFrameImage("PLAYER_FALL", "Texture/character/nuru/fall_368x256_4x2.bmp", 368, 256, 4, 2);

	_loading->loadFrameImage("PLAYER_hand", "Texture/character/nuru/hand_84x256_1x2.bmp", 84, 256, 1, 2);
	_loading->loadFrameImage("noHand_PLAYER_IDLE", "Texture/character/nuru/noHand_idle_84x256_1x2.bmp", 84, 256, 1, 2);
	_loading->loadFrameImage("noHand_PLAYER_RUN", "Texture/character/nuru/noHand_walk,run_672x256_8x2.bmp", 672, 256, 8, 2);
	_loading->loadFrameImage("noHand_PLAYER_JUMP", "Texture/character/nuru/noHand_jump_336x256_4x2.bmp", 336, 256, 4, 2);
	_loading->loadFrameImage("noHand_PLAYER_FALL", "Texture/character/nuru/noHand_fall_368x256_4x2.bmp", 368, 256, 4, 2);

	_loading->loadFrameImage("HAIR25", "Texture/character/floran/hair/25.bmp", 129, 258, 1, 2);
	_loading->loadFrameImage("FLORAN_IDLE", "Texture/character/floran/idle_129x258_1x2.bmp", 129, 258, 1, 2);
	_loading->loadFrameImage("FLORAN_WALK", "Texture/character/floran/walk_1032x258_8x2.bmp", 1032, 258, 8, 2);
	_loading->loadFrameImage("FLORAN_RUN", "Texture/character/floran/run_1032x258_8x2.bmp", 1032, 258, 8, 2);
	_loading->loadFrameImage("FLORAN_JUMP", "Texture/character/floran/jump_516x258_4x2.bmp", 516, 258, 4, 2);
	_loading->loadFrameImage("FLORAN_FALL", "Texture/character/floran/fall_516x258_4x2.bmp", 516, 258, 4, 2);
}
