/***************************************************
 GALAXY WALL for GBA
 ver 1.00
 2010.7.27
 choi kyun
 ***************************************************/

#ifndef _sprite_h_
#define _sprite_h_

#include <gba.h>
#include "bg.h"
#include "ship.h"
#include "shot_tile.h"
#include "shot2_tile.h"
#include "aim_tile.h"
#include "comet_tile.h"
#include "comet2_tile.h"
#include "comet3_tile.h"
#include "ship_comet1_tile.h"
#include "ship_comet2_tile.h"
#include "ship_comet3_tile.h"
#include "option_stop.h"
#include "option_shot.h"
#include "option_bonus.h"

#ifdef GLOBAL_VALUE_DEFINE
#define GLOBAL
#define GLOBAL_VAL(v) = (v)
#else
#define GLOBAL extern
#define GLOBAL_VAL(v)
#endif

///////////////////////////////////////////////////////////////////// 各種定義

// スプライト最大数
#define MAX_SPRITE 128

// 自機タイルデータ
#define SHIP_TILE_LEN (shipTilesLen/2)
#define SHIP_TILE shipTiles

// aimタイルデータ
#define AIM_TILE_LEN (aim_tileTilesLen/2)
#define AIM_TILE aim_tileTiles

// shotタイルデータ
#define SHOT_TILE_LEN (shot_tileTilesLen/2)
#define SHOT_TILE shot_tileTiles

// shot2タイルデータ
#define SHOT2_TILE_LEN (shot2_tileTilesLen/2)
#define SHOT2_TILE shot2_tileTiles

// comteタイルデータ
#define COMET_TILE_LEN (comet_tileTilesLen/2)
#define COMET_TILE comet_tileTiles

// comet2タイルデータ
#define COMET2_TILE_LEN (comet2_tileTilesLen/2)
#define COMET2_TILE comet2_tileTiles

// comet3タイルデータ
#define COMET3_TILE_LEN (comet3_tileTilesLen/2)
#define COMET3_TILE comet3_tileTiles

// 自機ステータス異常タイルデータ
#define SHIP_COMET_TILE_LEN (ship_comet1_tileTilesLen/2)
#define SHIP_COMET_TILE ship_comet1_tileTiles

#define SHIP_COMET2_TILE_LEN (ship_comet2_tileTilesLen/2)
#define SHIP_COMET2_TILE ship_comet2_tileTiles

#define SHIP_COMET3_TILE_LEN (ship_comet3_tileTilesLen/2)
#define SHIP_COMET3_TILE ship_comet3_tileTiles

// アイコン
#define ICON_TILE_LEN (option_stopTilesLen/2)
#define ICON_STOP_TILE option_stopTiles
#define ICON_SHOT_TILE option_shotTiles
#define ICON_BONUS_TILE option_bonusTiles

///////////////////////////////////////////////////////////////////// グローバル変数

//////////////////////////////////////////////////////////////////// プロトタイプ
void
init_sprite (void);
void
move_sprite (u16 num, s16 x, s16 y);
void
set_sprite_form (u16 num, u16 size, u16 form, u16 col);
void
set_sprite_tile (u16 num, u16 tile);
void
init_sprite_chr (void);
void
erase_sprite (u16 num);
s16
read_sprite_x (u16 num);
s16
read_sprite_y (u16 num);

#endif	/* _sprite_h_ */
