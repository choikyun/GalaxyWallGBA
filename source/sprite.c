/***************************************************
	GALAXY WALL for GBA
	ver 1.00
	2010.7.27
	choi kyun
***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gba.h>

#include "sprite.h"
#include "bg.h"



/***************************************************
	スプライト初期化
***************************************************/
void
init_sprite( void )
{
	int i;


	//すべて画面外へ
	for( i=0; i < MAX_SPRITE; i++ )
	{
		move_sprite( i, SCREEN_WIDTH, SCREEN_HEIGHT );
	}


}



/***************************************************
	スプライト非表示
***************************************************/
void
erase_sprite( u16 num )
{
	move_sprite( num, SCREEN_WIDTH, SCREEN_HEIGHT );
}



/***************************************************
	スプライト移動
***************************************************/
void
move_sprite( u16 num, s16 x, s16 y )
{
	OBJATTR *sp = (OBJATTR*) OAM + num;


	sp -> attr1 &= 0xfe00;
	sp -> attr0 &= 0xff00;
	sp -> attr1 |= OBJ_X( x );
	sp -> attr0 |= OBJ_Y( y );
}



/***************************************************
	スプライト形状　カラー サイズ
***************************************************/
void
set_sprite_form( u16 num, u16 size, u16 form, u16 col )
{
	OBJATTR *sp = (OBJATTR*) OAM + num;


	sp -> attr0 &= 0x1fff;
	sp -> attr1 &= 0x3fff;
	sp -> attr0 |= col  | form;
	sp -> attr1 |= size;
}



/***************************************************
	タイルキャラクタ設定
 **************************************************/
void
set_sprite_tile( u16 num, u16 tile )
{
	OBJATTR *sp = (OBJATTR*) OAM + num;


	sp -> attr2 &= 0xfc00;
	sp -> attr2 |= tile;
}



/***************************************************
	スプライトX座標読み取り
***************************************************/
s16
read_sprite_x( u16 num )
{
	OBJATTR *sp = (OBJATTR*) OAM + num;


	return sp -> attr1 & ~0xfe00;
}



/***************************************************
スプライトY座標読み取り
***************************************************/
s16
read_sprite_y( u16 num )
{
	OBJATTR *sp = (OBJATTR*) OAM + num;


	return sp -> attr0 & ~0xff00;
}



/***************************************************
	キャラクタ初期化
***************************************************/
void
init_sprite_chr( void )
{
	u16 *oam = DEF_MODE < MODE_3 ? OBJ_BASE_ADR : BITMAP_OBJ_BASE_ADR;	// スプライトデータ
	u16 *pal = OBJ_COLORS;		// スプライトパレット

	// 共通パレット転送
	CpuSet( shipPal, pal, ( COPY16 | shipPalLen/2 ) );


	// データ転送
	// 自機
	CpuSet( SHIP_TILE, oam, ( COPY16 | SHIP_TILE_LEN ) );
	// 照準
	CpuSet( AIM_TILE, oam + SHIP_TILE_LEN, ( COPY16 | AIM_TILE_LEN ) );
	// タイル　ショット
	CpuSet( SHOT_TILE, oam + SHIP_TILE_LEN + AIM_TILE_LEN, ( COPY16 | SHOT_TILE_LEN ) );
	// タイル　ショット2
	CpuSet( SHOT2_TILE, oam + SHIP_TILE_LEN + AIM_TILE_LEN + SHOT_TILE_LEN, ( COPY16 | SHOT2_TILE_LEN ) );
	// タイル　コメット
	CpuSet( COMET_TILE, oam + SHIP_TILE_LEN + AIM_TILE_LEN + SHOT_TILE_LEN + SHOT2_TILE_LEN, ( COPY16 | COMET_TILE_LEN ) );
	// タイル　コメット2
	CpuSet( COMET2_TILE, oam + SHIP_TILE_LEN + AIM_TILE_LEN + SHOT_TILE_LEN + SHOT2_TILE_LEN + COMET_TILE_LEN, ( COPY16 | COMET2_TILE_LEN ) );
	// タイル　コメット3
	CpuSet( COMET3_TILE, oam + SHIP_TILE_LEN + AIM_TILE_LEN + SHOT_TILE_LEN + SHOT2_TILE_LEN + COMET_TILE_LEN + COMET2_TILE_LEN, ( COPY16 | COMET3_TILE_LEN ) );
	// タイル　自機異常1
	CpuSet( SHIP_COMET_TILE, oam + SHIP_TILE_LEN + AIM_TILE_LEN + SHOT_TILE_LEN + SHOT2_TILE_LEN + COMET_TILE_LEN + COMET2_TILE_LEN + COMET3_TILE_LEN, ( COPY16 | SHIP_COMET_TILE_LEN ) );
	// タイル　自機異常2
	CpuSet( SHIP_COMET2_TILE, oam + SHIP_TILE_LEN + AIM_TILE_LEN + SHOT_TILE_LEN + SHOT2_TILE_LEN + COMET_TILE_LEN + COMET2_TILE_LEN + COMET3_TILE_LEN + SHIP_COMET_TILE_LEN, ( COPY16 | SHIP_COMET2_TILE_LEN ) );
	// タイル　自機異常3
	CpuSet( SHIP_COMET3_TILE, oam + SHIP_TILE_LEN + AIM_TILE_LEN + SHOT_TILE_LEN + SHOT2_TILE_LEN + COMET_TILE_LEN + COMET2_TILE_LEN + COMET3_TILE_LEN + SHIP_COMET_TILE_LEN + SHIP_COMET2_TILE_LEN, ( COPY16 | SHIP_COMET3_TILE_LEN ) );

  // タイル　ショットアイコン
  CpuSet( ICON_SHOT_TILE, oam + SHIP_TILE_LEN + AIM_TILE_LEN + SHOT_TILE_LEN + SHOT2_TILE_LEN + COMET_TILE_LEN + COMET2_TILE_LEN + COMET3_TILE_LEN + SHIP_COMET_TILE_LEN + SHIP_COMET2_TILE_LEN + SHIP_COMET3_TILE_LEN, ( COPY16 | ICON_TILE_LEN ) );
	// タイル　ストップアイコン
  CpuSet( ICON_STOP_TILE, oam + SHIP_TILE_LEN + AIM_TILE_LEN + SHOT_TILE_LEN + SHOT2_TILE_LEN + COMET_TILE_LEN + COMET2_TILE_LEN + COMET3_TILE_LEN + SHIP_COMET_TILE_LEN + SHIP_COMET2_TILE_LEN  + SHIP_COMET3_TILE_LEN + ICON_TILE_LEN, ( COPY16 | ICON_TILE_LEN ) );
	// タイル　ボーナスアイコン
  CpuSet( ICON_BONUS_TILE, oam + SHIP_TILE_LEN + AIM_TILE_LEN + SHOT_TILE_LEN + SHOT2_TILE_LEN + COMET_TILE_LEN + COMET2_TILE_LEN + COMET3_TILE_LEN + SHIP_COMET_TILE_LEN + SHIP_COMET2_TILE_LEN + SHIP_COMET3_TILE_LEN + ICON_TILE_LEN * 2, ( COPY16 | ICON_TILE_LEN ) );



}
