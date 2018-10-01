#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init()
{
	//�ε�Ŭ���� �ʱ�ȭ
	_loading = new loading;
	_loading->init(); //�ε�ȭ�� �̹����� �ε� ���α׷�����

	//�̹��� �� ���� �ε�
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release()
{
	//�ε�Ŭ���� ����
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingScene::update()
{
	//�ε�Ŭ���� ������Ʈ
	_loading->update(); //�ε��� ������Ʈ

	//�ε��Ϸ��� ������
	if (_loading->loadingDone()) //loadingImage�� loadingSound�� ���ڰ����� addimage, addframeimage�ϰ� �� �Ǹ� true
	{
		//�ε����� ���� ��۾�, �������� ����
		SetBkMode(getMemDC(), OPAQUE);
		SetTextColor(getMemDC(), RGB(0, 0, 0));
		loadingEffect();
		SCENEMANAGER->loadScene("����"); //���Ӿ����� ��ȯ
	}
}

void loadingScene::render()
{
	//�ε�Ŭ���� ����
	_loading->render();
}

//�ε��̹��� �Լ�(�̰��� �̹����� ���� �־��)
void loadingScene::loadingImage()
{
	//_loading->loadImage();
	//_loading->loadFrameImage();
	//_loading->loadSound();

	//����ui
	loadingMapToolImage();
	
	//��Ʈ��
	loadingIntroImage();

	//Ÿ��
	loadingTiles();

	//���
	_loading->loadImage("���Top0", "Texture/object/background/top/back0.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("���Top1", "Texture/object/background/top/back1.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("���Top2", "Texture/object/background/top/back2.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("���Top3", "Texture/object/background/top/back3.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("���Top4", "Texture/object/background/top/back4.bmp", 1280, 720, true, MAGENTA);

	_loading->loadImage("���Bot0", "Texture/object/background/bot/back0.bmp", 512, 512);
	_loading->loadImage("���Bot1", "Texture/object/background/bot/back1.bmp", 512, 512);
	_loading->loadImage("���Bot2", "Texture/object/background/bot/back2.bmp", 512, 512);
	_loading->loadImage("���Bot3", "Texture/object/background/bot/back3.bmp", 512, 512);

	//���ּ�
	_loading->loadImage("���ּ�", "Texture/ships/ship.bmp", 4752, 1536, true, MAGENTA);
	_loading->loadImage("���ּ��ȼ�", "Texture/ships/shipPixel.bmp", 4752, 1536, true, MAGENTA);
	_loading->loadImage("���ּ����", "Texture/ships/shipBack.bmp", 2731, 1536);
	_loading->loadImage("�ڷ�����", "Texture/ships/hylotlteleporter.bmp", 192, 240, true, MAGENTA);
	_loading->loadImage("����UI", "Texture/ships/warpUI/warpUI.bmp", 372, 334, true, MAGENTA);
	_loading->loadFrameImage("������ư", "Texture/ships/warpUI/warpButton.bmp", 94, 56, 1, 2);
	_loading->loadFrameImage("����_���ּ�", "Texture/ships/warpUI/warpentry_ship.bmp", 340, 80, 1, 2);
	_loading->loadFrameImage("����_��", "Texture/ships/warpUI/warpentry_home.bmp", 340, 80, 1, 2);
	_loading->loadFrameImage("����_����", "Texture/ships/warpUI/warpentry_dungeon.bmp", 340, 80, 1, 2);

	_loading->loadFrameImage("�����ٿ�", "Texture/ships/warpUI/warpdown_240x320_4x1.bmp", 240, 320, 4, 1);	//������
	_loading->loadFrameImage("�����ʵ�", "Texture/ships/warpUI/starfield1.bmp", 1280, 720, true, MAGENTA);	//��������

	//������Ʈ
	loadingObjects();

	//����Ʈ�̹���
	loadingEffectImage();

	//�÷��̾�
	loadingPlayer();

	//������
	loadingItem();

	//����
	loadingMonster();

	//ui
	_loading->loadFrameImage("����", "Texture/ui/numbers.bmp", 160, 16, 10, 1);
	_loading->loadImage("���е�", "Texture/ui/empty.bmp", 18, 18, true, MAGENTA);

	_loading->loadImage("�Ҹ��ɼ�â", "Texture/ui/sound/sound_body.bmp", 404, 266, true, MAGENTA);
	_loading->loadFrameImage("�Ҹ���ư", "Texture/ui/sound/okay.bmp", 108, 56, 1, 2);
	_loading->loadFrameImage("����ȭ��ǥ", "Texture/ui/sound/leftarrow.bmp", 31, 62, 1, 2);
	_loading->loadFrameImage("������ȭ��ǥ", "Texture/ui/sound/rightarrow.bmp", 31, 62, 1, 2);
	
	//IMAGEMANAGER->addImage("mountain", "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	//��׶��� �̹���
	//_loading->loadImage("mountain", "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

}

//�ε����� �Լ�(�̰��� ���带 ���� �־��)
void loadingScene::loadingSound()
{
	//�����
	_loading->loadSound("��Ʈ��", "Music/bgm/title-menu-music.ogg", true, true);
	_loading->loadSound("��", "Music/bgm/on-the-beach-at-night.ogg", true, true);
	_loading->loadSound("���ּ�", "Music/bgm/space_loop3.ogg", true, true);
	_loading->loadSound("����", "Music/bgm/desert_day.ogg", true, true);
	_loading->loadSound("����", "Music/bgm/gravitational-collapse-loop.ogg", true, true);

	//ȿ����
	_loading->loadSound("����", "Music/effect/shotgun1.ogg");
	_loading->loadSound("����Ÿ��", "Music/effect/shotgun_hit_organic.ogg");
	_loading->loadSound("�ö��", "Music/effect/plasma_ar1.ogg");
	_loading->loadSound("�ö��Ÿ��", "Music/effect/plasmabullet_hit_organic.ogg");
	_loading->loadSound("�κ��丮����", "Music/effect/metalbox_open.ogg");
	_loading->loadSound("�κ��丮�ݱ�", "Music/effect/metalbox_close.ogg");
	_loading->loadSound("���ߴ�����", "Music/effect/actionbar_select.ogg");

	_loading->loadSound("��������", "Music/effect/boss/kluexboss_death.ogg");
	_loading->loadSound("�������", "Music/effect/boss/kluexboss_floorlava.ogg");
	_loading->loadSound("��������", "Music/effect/boss/kluexboss_iceeruption1.ogg");
	_loading->loadSound("�����Ҹ�", "Music/effect/boss/kluexboss_phase1.ogg");
	_loading->loadSound("�����Ҹ��߻�", "Music/effect/boss/pulsecannon_blast1.ogg");
	_loading->loadSound("�������ǿø�", "Music/effect/boss/kluexboss_pillarplatform.ogg");

	_loading->loadSound("ȭ�����", "Music/effect/walkers/flamethrower_loop.ogg");

	_loading->loadSound("�������Ҹ�0", "Music/effect/walkers/scaveran_idle1.ogg");
	_loading->loadSound("�������Ҹ�1", "Music/effect/walkers/scaveran_idle2.ogg");
	_loading->loadSound("�������Ҹ�2", "Music/effect/walkers/scaveran_idle3.ogg");
}

void loadingScene::loadingEffectImage()
{
	_loading->loadFrameImage("JUMPDUSTImg", "Texture/character/dust2/jumpDust_64x32_2x1.bmp", 64, 32, 2, 1);					//���� ����
	_loading->loadFrameImage("PLAYERDEAthImg", "Texture/character/playerdeath_1806x129_14x1.bmp", 1806, 129, 14, 1);			//�÷��̾� ����
	_loading->loadFrameImage("PLAYERHITImg", "Texture/character/largehitspark_540x108_5x1.bmp", 540, 108, 5, 1);				//�÷��̾� �ǰ�

	_loading->loadFrameImage("kluexstaffplasmaImg", "Texture/projectiles/kluexstaffplasma.bmp", 432, 51, 8, 1);					//������ ������
	_loading->loadFrameImage("redpulsecannonexplosionImg", "Texture/projectiles/redpulsecannonexplosion.bmp", 468, 117, 4, 1);	//������ ��
	_loading->loadFrameImage("energycrystalImg", "Texture/projectiles/energycrystal.bmp", 192, 24, 4, 1);						//������(�Ҹ�)
	_loading->loadImage("pillarplatformImg", "Texture/projectiles/pillarplatform.bmp", 144, 192, true, MAGENTA);				//����
	_loading->loadImage("pillarplatformPixelImg", "Texture/projectiles/pillarplatformPixel.bmp", 144, 192);						//�����ȼ� - ����Ÿ�� ���⼭ �����ع����� �׸��� ���� �ʷϻ��� ���͹����� �Ʒ��κ��� ��������
	_loading->loadImage("pillarplatformPixelEraserImg", "Texture/projectiles/platformPixelEraser.bmp", 144, 192);				//�����ȼ� - �����
	_loading->loadImage("firefloorhazardImg", "Texture/projectiles/firefloorhazard.bmp", 3072, 48, true, MAGENTA);				//���׸��ø���
	_loading->loadFrameImage("iceeruptionImg", "Texture/projectiles/iceeruption.bmp", 768, 168, 4, 1);							//�������
	_loading->loadFrameImage("energywaveImg", "Texture/projectiles/energywave.bmp", 576, 66, 3, 1);								//����ĵ�(�Ҹ�)

	_loading->loadFrameImage("flameImg", "Texture/projectiles/flame_576x48_12x1.bmp", 576, 48, 12, 1);							//ȭ�����

	_loading->loadFrameImage("muzzleflashImg", "Texture/item/weapons/ranged/muzzleflash_135x90_3x2.bmp", 135, 90, 3, 2);		//�����÷���
	_loading->loadFrameImage("plasmaflashImg", "Texture/item/weapons/ranged/plasmaflash_120x64_3x2.bmp", 120, 64, 3, 2);		//�ö���÷���

	_loading->loadFrameImage("iceShardImg", "Texture/projectiles/iceshard_120x24_5x1.bmp", 120, 24, 5, 1);						//��������

	_loading->loadFrameImage("standardBullet", "Texture/item/weapons/ranged/standardbullet.bmp", 51, 9, 1, 1);					//�⺻�Ҹ�
	_loading->loadFrameImage("bulletEffectImg", "Texture/item/weapons/ranged/bulletEffect_160x40_4x1.bmp", 160, 40, 4, 1);		//�Ҹ�����Ʈ
	_loading->loadFrameImage("plasmaBullet", "Texture/item/weapons/ranged/plasma_288x44_4x1.bmp", 288, 44, 4, 1);				//�ö���Ҹ�
	_loading->loadFrameImage("plasmaEffectImg", "Texture/item/weapons/ranged/plasmaEffect_156x78_2x1.bmp", 156, 78, 2, 1);		//�ö������Ʈ
	_loading->loadFrameImage("drillBullet", "Texture/item/weapons/ranged/drill_210x27_5x1.bmp", 210, 27, 5, 1);					//�帱�Ҹ�
	_loading->loadFrameImage("drillEffectImg", "Texture/item/weapons/ranged/drillEffect_128x32_4x1.bmp", 256, 64, 4, 1);		//�帱����Ʈ

	_loading->loadFrameImage("tearswoosh1Img", "Texture/item/weapons/melee/broadsword/tearswoosh1_732x295_3x2.bmp", 732, 295, 3, 2);	//Į����1��
	_loading->loadFrameImage("tearswoosh2Img", "Texture/item/weapons/melee/broadsword/tearswoosh2_363x116_3x2.bmp", 363, 116, 3, 2);	//Į����2��
	_loading->loadFrameImage("tearswoosh3Img", "Texture/item/weapons/melee/broadsword/tearswoosh3_412x68_3x2.bmp", 412, 68, 3, 2);		//Į����3��

	_loading->loadFrameImage("kluexCrystalImg", "Texture/enemy/monsters/boss/death/kluexcrystal.bmp", 48, 48, 1, 1);				//������������
	_loading->loadFrameImage("kluexCrystalShardImg", "Texture/enemy/monsters/boss/death/kluexcrystalshard.bmp", 48, 48, 1, 1);		//������������2
	_loading->loadFrameImage("kluexStatueShardImg", "Texture/enemy/monsters/boss/death/kluexstatueshard.bmp", 48, 48, 1, 1);		//������������
}

void loadingScene::loadingEffect()
{
	EFFECTMANAGER->addEffect("JUMP_DUST", "JUMPDUSTImg", 0.05f, 10);
	EFFECTMANAGER->addEffect("PLAYER_DEATH", "PLAYERDEAthImg", 0.3f, 1);
	EFFECTMANAGER->addEffect("PLAYER_HIT", "PLAYERHITImg", 0.7f, 1);

	EFFECTMANAGER->addEffect("muzzleflash", "muzzleflashImg", 0.4f, 10);
	EFFECTMANAGER->addEffect("bulletEffect", "bulletEffectImg", 1.4f, 15);

	EFFECTMANAGER->addEffect("plasmaflash", "plasmaflashImg", 0.4f, 10);
	EFFECTMANAGER->addEffect("plasmaEffect", "plasmaEffectImg", 2.0f, 15);

	EFFECTMANAGER->addEffect("drillEffect", "drillEffectImg", 0.4f, 8);

	EFFECTMANAGER->addEffect("kluex_Staff_Plasma", "kluexstaffplasmaImg", 0.05f, 20);
	EFFECTMANAGER->addEffect("red_Pulse_Cannon_Explosion", "redpulsecannonexplosionImg", 0.05, 20);
	EFFECTMANAGER->addEffect("energy_Crystal", "energycrystalImg", 0.05f, 20);
	EFFECTMANAGER->addEffect("ice_Eruption", "iceeruptionImg", 0.05f, 10);
	EFFECTMANAGER->addEffect("energy_Wave", "energywaveImg", 0.05f, 10);
	EFFECTMANAGER->addEffect("iceShard", "iceShardImg", 0.2f, 90);

	EFFECTMANAGER->addEffect("tearswoosh2", "tearswoosh2Img", 0.05f, 1);
	EFFECTMANAGER->addEffect("tearswoosh3", "tearswoosh3Img", 0.05f, 1);
}

void loadingScene::loadingMapToolImage()
{
	//Ÿ��
	_loading->loadFrameImage("Ÿ�Ͼ�����", "Texture/mapTool/icons/TileIcons_360x216x10x6.bmp", 360, 216, 10, 6);
	_loading->loadFrameImage("������Ʈ������", "Texture/mapTool/icons/ObjectIcons_360x216_10x6.bmp", 360, 216, 10, 6);
	_loading->loadFrameImage("�����۾�����", "Texture/mapTool/icons/itemIcons_360x216_10x6.bmp", 360, 216, 10, 6);
	_loading->loadFrameImage("���;�����", "Texture/mapTool/icons/actorIcons_360x216_10x6.bmp", 360, 216, 10, 6);

	_loading->loadImage("ū����", "Texture/maptool/ui/bigWorld_36x36.bmp", 36, 36, true, MAGENTA);
	_loading->loadImage("�߰�����", "Texture/maptool/ui/midWorld_36x36.bmp", 36, 36, true, MAGENTA);
	_loading->loadImage("��������", "Texture/maptool/ui/smallWorld_36x36.bmp", 36, 36, true, MAGENTA);
	_loading->loadImage("�������", "Texture/maptool/ui/eraseWorld_36x36.bmp", 36, 36, true, MAGENTA);

	//������
	_loading->loadImage("FENNIX������", "Texture/spawner/fennixSpawner.bmp", 48, 86, true, MAGENTA);
	_loading->loadImage("SCAVERAN������", "Texture/spawner/scaveranSpawner.bmp", 48, 86, true, MAGENTA);
	_loading->loadImage("BOSS������", "Texture/spawner/kluexBossSpawner.bmp", 48, 86, true, MAGENTA);

	//UI
	_loading->loadImage("����UI", "Texture/maptool/ui/CtrlInterface_503x486.bmp", 503, 486, true, MAGENTA);
	_loading->loadFrameImage("����ǥ����", "Texture/maptool/ui/mapTool_134x70_1x2.bmp", 134, 70, 1, 2);
	_loading->loadFrameImage("�����ּ�ȭ", "Texture/maptool/ui/underbar_44x70_1x2.bmp", 44, 70, 1, 2);
	_loading->loadFrameImage("�ʼ��̺�UI", "Texture/maptool/ui/save_134x70_1x2.bmp", 134, 70, 1, 2);
	_loading->loadFrameImage("�ʷε�UI", "Texture/maptool/ui/load_134x70_1x2.bmp", 134, 70, 1, 2);
	_loading->loadFrameImage("ũ���±�", "Texture/maptool/ui/worldTag2_260x38_4x1.bmp", 260, 38, 4, 1);
	_loading->loadFrameImage("�����±�", "Texture/maptool/ui/terrainTag_260x38_4x1.bmp", 260, 38, 4, 1);
	_loading->loadFrameImage("�������±�", "Texture/maptool/ui/itemTag_260x38_4x1.bmp", 260, 38, 4, 1);
	_loading->loadFrameImage("������Ʈ�±�", "Texture/maptool/ui/furnitureTag_260x38_4x1.bmp", 260, 38, 4, 1);
	_loading->loadFrameImage("���ʹ��±�", "Texture/maptool/ui/enemyTag_260x38_4x1.bmp", 260, 38, 4, 1);
	_loading->loadImage("�巡��", "Texture/maptool/ui/dragRc.bmp", 1280, 720);
}

void loadingScene::loadingIntroImage()
{
	_loading->loadImage("����", "Texture/intro/space.bmp", 1280, 720);
	_loading->loadImage("��", "Texture/intro/introStar.bmp", 1280, 720, true, MAGENTA);
	_loading->loadImage("����", "Texture/intro/planet2.bmp", 1626, 1626, true, MAGENTA);
	_loading->loadImage("�ΰ�", "Texture/intro/logo.bmp", 316, 106, true, MAGENTA);

	_loading->loadFrameImage("���۰���", "Texture/intro/startgame_334x88_2x1.bmp", 334, 88, 1, 2);
	_loading->loadFrameImage("���۸���", "Texture/intro/maptool_286x88_2x1.bmp", 286, 88, 1, 2);
	_loading->loadFrameImage("���ۿɼ�", "Texture/intro/options_236x88_2x1.bmp", 236, 88, 1, 2);
	_loading->loadFrameImage("���۳�����", "Texture/intro/quit_188x88_2x1.bmp", 188, 88, 1, 2);
}

void loadingScene::loadingTiles()
{
	_loading->loadFrameImage("TILE_PIXEL", "Texture/tiles/pixel.bmp", 192, 48, 4, 1);

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

	_loading->loadFrameImage("FLATFORM_WOOD", "Texture/tiles/flatform/woodplatform_240x432_5x9.bmp", 240, 432, 5, 9);
}

void loadingScene::loadingObjects()
{
	_loading->loadFrameImage("��������1", "Texture/object/box/woodencrate1_288x864_2x9.bmp", 288, 864, 2, 9);
	_loading->loadImage("��������1_������", "Texture/object/box/woodencrate1icon.bmp", 36, 36);
	_loading->loadFrameImage("Ʈ������", "Texture/object/funiture/fairylights/fairylights_128x32_2x1.bmp", 128, 32, 2, 1);
	_loading->loadImage("Ʈ������_������", "Texture/object/funiture/fairylights/fairylightsicon.bmp", 36, 36);
	_loading->loadFrameImage("��ĵ�", "Texture/object/funiture/ornatetorch/ornatetorch_256x480_4x5.bmp", 256, 480, 4, 5);
	_loading->loadImage("��ĵ�_������", "Texture/object/funiture/ornatetorch/ornatetorchicon.bmp", 36, 36);
}

void loadingScene::loadingItem()
{
	_loading->loadFrameImage("���ְ�", "Texture/item/weapons/melee/broadsword/astrosabredeluxe_330x116_1x2.bmp", 330, 116, 1, 2);
	_loading->loadImage("���ְ˾�����", "Texture/item/weapons/melee/broadsword/astrosabredeluxeIcon.bmp", 40, 40, true, MAGENTA);

	_loading->loadFrameImage("����", "Texture/item/weapons/ranged/shotgun_207x96_2x1.bmp", 207, 96, 1,2);
	_loading->loadImage("���Ǿ�����", "Texture/item/weapons/ranged/shotgunIcon.bmp", 40, 40, true, MAGENTA);

	_loading->loadFrameImage("�ö����", "Texture/item/weapons/ranged/plasmarifle_207x96_2x1.bmp", 207, 96, 1, 2);
	_loading->loadImage("�ö���Ǿ�����", "Texture/item/weapons/ranged/plasmarifleIcon.bmp", 40, 40, true, MAGENTA);

	_loading->loadFrameImage("�帱��", "Texture/item/weapons/ranged/exmachina_207x96_2x1.bmp", 207, 96, 1, 2);
	_loading->loadImage("�帱�Ǿ�����", "Texture/item/weapons/ranged/exmachinaIcon.bmp", 40, 40, true, MAGENTA);
}

void loadingScene::loadingPlayer()
{
	//�÷��̾�
	_loading->loadFrameImage("PLAYER_IDLE", "Texture/character/nuru/idle_84x256_1x2.bmp", 84, 256, 1, 2);
	_loading->loadFrameImage("PLAYER_RUN", "Texture/character/nuru/walk,run_672x256_8x2.bmp", 672, 256, 8, 2);
	_loading->loadFrameImage("PLAYER_JUMP", "Texture/character/nuru/jump_336x256_4x2.bmp", 336, 256, 4, 2);
	_loading->loadFrameImage("PLAYER_FALL", "Texture/character/nuru/fall_368x256_4x2.bmp", 368, 256, 4, 2);

	_loading->loadFrameImage("PLAYER_hand", "Texture/character/nuru/hand_84x256_1x2.bmp", 84, 256, 1, 2);
	_loading->loadFrameImage("noHand_PLAYER_IDLE", "Texture/character/nuru/noHand_idle_84x256_1x2.bmp", 84, 256, 1, 2);
	_loading->loadFrameImage("noHand_PLAYER_RUN", "Texture/character/nuru/noHand_walk,run_672x256_8x2.bmp", 672, 256, 8, 2);
	_loading->loadFrameImage("noHand_PLAYER_JUMP", "Texture/character/nuru/noHand_jump_336x256_4x2.bmp", 336, 256, 4, 2);
	_loading->loadFrameImage("noHand_PLAYER_FALL", "Texture/character/nuru/noHand_fall_368x256_4x2.bmp", 368, 256, 4, 2);

	//�κ��丮
	_loading->loadImage("inventory_body", "Texture/ui/inventory/inventoryBody_407x465.bmp", 407, 465, true, MAGENTA);
	_loading->loadFrameImage("invenTag_item", "Texture/ui/inventory/itemTag_260x38_4x1.bmp", 260, 38, 4, 1);
	_loading->loadFrameImage("invenTag_object", "Texture/ui/inventory/objectTag_260x38_4x1.bmp", 260, 38, 4, 1);
	_loading->loadFrameImage("invenTag_tiles", "Texture/ui/inventory/tilesTag_260x38_4x1.bmp", 260, 38, 4, 1);
	_loading->loadFrameImage("invenTag_weapon", "Texture/ui/inventory/weaponTag_260x38_4x1.bmp", 260, 38, 4, 1);
	_loading->loadFrameImage("inven_esc", "Texture/ui/inventory/escBar_35x56_1x2.bmp", 35, 56, 1, 2);
	_loading->loadFrameImage("inven_itemBorder", "Texture/ui/inventory/itemborder_225x45_5x1.bmp", 225, 45, 5, 1);

	//ȭ��UI
	_loading->loadImage("portraitUI", "Texture/character/NURU_playerbar.bmp", 210, 78, true, MAGENTA);

	//�׽�Ʈ
	_loading->loadFrameImage("HAIR25", "Texture/character/floran/hair/25.bmp", 129, 258, 1, 2);
	_loading->loadFrameImage("FLORAN_IDLE", "Texture/character/floran/idle_129x258_1x2.bmp", 129, 258, 1, 2);
	_loading->loadFrameImage("FLORAN_WALK", "Texture/character/floran/walk_1032x258_8x2.bmp", 1032, 258, 8, 2);
	_loading->loadFrameImage("FLORAN_RUN", "Texture/character/floran/run_1032x258_8x2.bmp", 1032, 258, 8, 2);
	_loading->loadFrameImage("FLORAN_JUMP", "Texture/character/floran/jump_516x258_4x2.bmp", 516, 258, 4, 2);
	_loading->loadFrameImage("FLORAN_FALL", "Texture/character/floran/fall_516x258_4x2.bmp", 516, 258, 4, 2);
}

void loadingScene::loadingMonster()
{
	_loading->loadImage("BIRDBOSS1", "Texture/enemy/monsters/boss/kluexbossstatue/kluexbossstatue_4719x1089_13x3.bmp", 4719, 1089, true, MAGENTA);
	_loading->loadImage("FENNIX_R", "Texture/enemy/monsters/walkers/fennix/fennix_R_960x288.bmp", 960, 288, true, MAGENTA);
	_loading->loadImage("FENNIX_L", "Texture/enemy/monsters/walkers/fennix/fennix_L_960x288.bmp", 960, 288, true, MAGENTA);
	_loading->loadImage("SCAVERAN_L", "Texture/enemy/monsters/walkers/scaveran/scaveran_L_924x510.bmp", 924, 510, true, MAGENTA);
	_loading->loadImage("SCAVERAN_R", "Texture/enemy/monsters/walkers/scaveran/scaveran_R_924x510.bmp", 924, 510, true, MAGENTA);
}
