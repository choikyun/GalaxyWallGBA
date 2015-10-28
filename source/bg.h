/***************************************************
	GALAXY WALL for GBA
	ver 1.00
	2010.7.27
	choi kyun
***************************************************/

#ifndef _bg_h_
#define _bg_h_

#include <gba.h>

#include "bg_tile.h"
#include "status_tile.h"
#include "meteo_tile.h"
#include "trans_tile.h"
#include "title_tile.h"
#include "shot_tile.h"
#include "flash_tile.h"
#include "num_tile.h"
#include "over_tile.h"
#include "ready_tile.h"
#include "nomal_tile.h"
#include "hard_tile.h"



#ifdef GLOBAL_VALUE_DEFINE
#define GLOBAL
#define GLOBAL_VAL(v) = (v)
#else
#define GLOBAL extern
#define GLOBAL_VAL(v)
#endif


///////////////////////////////////////////////////////////////////// 各種定義

//// BGタイル モード0

// BGコントロールレジスタ
#define DEF_BG_REG REG_BG0CNT

// BGモード
#define DEF_MODE MODE_0

// BGイネーブル
#define DEF_BG_ENABLE BG0_ENABLE

// BGサイズ
#define DEF_BG_SIZE BG_SIZE_0

// BGカラー
#define DEF_BG_COLOR BG_256_COLOR

// BGキャラクタ
#define DEF_CHAR_BASE CHAR_BASE(0)
#define DEF_BG_BASE_ADR CHAR_BASE_ADR(0)
#define MAX_MAP_X (32)
#define MAX_MAP_Y (32)
#define MAP_WIDTH (32)
#define MAP_HEIGHT (32)

// BGマップ
#define DEF_MAP_BASE MAP_BASE(28)
#define DEF_MAP_BASE_ADR MAP_BASE_ADR(28)

// BGビットマップデータ
#define DEF_BG_LEN 0
#define DEF_BG_BITMAP 0

// BGタイルデータ
#define STAR_TILE_LEN (bg_tileTilesLen/2)
#define STAR_TILE bg_tileTiles

// meteoタイルデータ
#define METEO_TILE_LEN (Meteo_tileTilesLen/2)
#define METO_TILE Meteo_tileTiles

// transタイルデータ
#define TRANS_TILE_LEN (trans_tileTilesLen/2)
#define TRANS_TILE trans_tileTiles

// flashタイルデータ
#define FLASH_TILE_LEN (flash_tileTilesLen/2)
#define FLASH_TILE flash_tileTiles

// 数字タイルデータ
#define NUM_TILE_LEN (num_tileTilesLen/2)
#define NUM_TILE num_tileTiles

// GAMEOVERタイルデータ
#define OVER_TILE_LEN (over_tileTilesLen/2)
#define OVER_TILE over_tileTiles

// READYタイルデータ
#define READY_TILE_LEN (ready_tileTilesLen/2)
#define READY_TILE ready_tileTiles

// READYタイルデータ
#define NOMAL_TILE_LEN (nomal_tileTilesLen/2)
#define NOMAL_TILE nomal_tileTiles

// READYタイルデータ
#define HARD_TILE_LEN (hard_tileTilesLen/2)
#define HARD_TILE hard_tileTiles


// BGメテオマップ
#define DEF_METEO_BASE MAP_BASE(30)
#define DEF_METEO_BASE_ADR MAP_BASE_ADR(30)

// BGステータスタイルデータ
#define BG_STATE_TILE_LEN (status_tileTilesLen/2)
#define BG_STATE_TILE status_tileTiles

#define MAP_STATEUS_WIDTH (32)

// BGパレットデータ
#define DEF_BG_PALLET_LEN (bg_tilePalLen/2)
#define DEF_BG_PALLET bg_tilePal



///////////////////////////////////////////////////////////////////// グローバル変数


//////////////////////////////////////////////////////////////////// プロトタイプ
void init_bg( void );
void init_bg_bitmap( void );
void init_bg_bitmap_lz77( void );
void init_bg_tile( void );
void init_title();


#endif	/* _bg_h_ */