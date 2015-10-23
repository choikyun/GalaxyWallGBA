/***************************************************
	GALAXY WALL for GBA
	ver 1.00
	2010.7.27
	choi kyun
***************************************************/

#ifndef _game_h_
#define _game_h_

#include <gba.h>
#include "bg.h"

#ifdef GLOBAL_VALUE_DEFINE
#define GLOBAL
#define GLOBAL_VAL(v) = (v)
#else
#define GLOBAL extern
#define GLOBAL_VAL(v)
#endif


///////////////////////////////////////////////////////////////////// 各種定義

#define DEF_SHIP_X (0)
#define DEF_SHIP_Y (80)
#define SHIP_MOVE_STEP (16)

#define DEF_KEY_DELAY (1)
#define DEF_KEY_REPEAT (8)

// レベル
#define MAX_LEVEL (9)
#define NOMAL_LEVEL_UP_COUNT (2000)
#define HARD_LEVEL_UP_COUNT (1000)
#define SCROLL_UP_STEP (2)


// ゲーム管理
typedef struct {
	int scene;
	u16 key;
	u16 keyr;
	int scroll_speed;
	int scroll_speed_rel;
	int scroll_offset;
	int shot_kind;
	int shot_num;
	int shot_interval;
	int comet_num;
	int mode;
} GameStateType;


// レベル
typedef struct {
	int lv;
	int up_count;
	int up_count_rel;
	int line;
	u32 score;
	u32 hiscore;
} LevelType;


// 自機
typedef struct {
	u16 num;
	int x;
	int y;
	int status;
	int status_time;
} SpriteChrType;


// ショット
typedef struct {
	int kind;
	int speed;
} ShotType;


// ラインフラッシュ
typedef struct {
	int count;
	int wait;
	int wait_rel;
	u16 chr;
} FlashLineType;


// コメット
typedef struct {
	int kind;
	int speed;
} CometType;


// 点滅メッセージ
typedef struct {
	int x;
	int y;
	u16 save_map[30];
	int wait;
	int wait_rel;
	int chr;
	int count;
} BlinkMessageType;

// ウェイト
typedef struct {
	int wait;
} WaitType;


// スプライト点滅
typedef struct {
  int wait;
  int wait_rel;
  int count;
  bool blink;
} SpriteBlinkType;



// シーン
enum {
	GAME_MAIN = 0,
	GAME_TITLE = 1,
	GAME_PAUSE = 2,
	GAME_OVER = 4,
	GAME_READY = 8,
	GAME_OVER_PRE = 16
};


// ゲームモード
enum {
	LV_NOMAL,
	LV_HARD
};


// スプライトキャラクタ
enum {
	SPRITE_SHIP,
	SPRITE_SHOT,
	SPRITE_SHOT2 = 5,
	SPRITE_COMET = 8,
  SPRITE_AIM = 11,
  SPRITE_ICON_SHOT,
	SPRITE_ICON_STOP,
	SPRITE_ICON_BONUS,
};


// フィールドキャラクタ
enum {
	CHR_NONE,
	CHR_METEO,
	CHR_FLASH,
};


// ショットの種類
enum {
	SHOT_NOMAL,
	SHOT_X3
};


// 自機のステータス異常
enum {
	SHIP_NOMAL,
	SHIP_SHOTX3,
	SHIP_DONTMOVE,
	SHIP_BONUS
};



// 星
#define STAR_RND (8)
#define DEF_STAR_INTERVAL (16)
#define MAX_STAR_INTERVAL (8)
#define NOMAL_BG_CHR (4)

// 隕石
#define FIELD_WIDTH (16)
#define FIELD_HEIGHT (9)
#define DEF_METEO_SPEED (20)
#define DEF_NEW_LINE (FIELD_WIDTH-1)
#define LIMIT_SCROLL_OFFSET (15)
#define DEF_METEO_SIZE (16)

// タイル番号

// スプライト
#define TILE_CHR_SHIP (0)
#define TILE_CHR_AIM (8)
#define TILE_CHR_SHOT (16)
#define TILE_CHR_SHOT2 (24)
#define TILE_CHR_COMET (32)
#define TILE_CHR_COMET2 (40)
#define TILE_CHR_COMET3 (48)
#define TILE_CHR_SHIP_COMET1 (56)
#define TILE_CHR_SHIP_COMET2 (64)
#define TILE_CHR_SHIP_COMET3 (72)
#define TILE_CHR_ICON_SHOT (80)
#define TILE_CHR_ICON_STOP (88)
#define TILE_CHR_ICON_BONUS (96)

// BG
// タイル番号
#define BG_STATUS_TILE (5)
#define MAP_CHR_TRANS (35)
#define MAP_CHR_METEO (39)
#define SCORE_NUM_TILE (51)
#define MAP_OVER_TILE (61)
#define MAP_READY_TILE (71)

// タイトル
#define HISCORE_NUM_TILE (217)
#define NOMAL_MODE_TILE (227)
#define HARD_MODE_TILE (233)

// ショット
#define MAX_SHOT (3)
#define DEF_SHOT_INTERVAL (2)
#define DEF_SHOT_SPEED (8)
#define DEF_SHOT_X (0)

// BGステータス
#define DEF_STATUS_HEIGHT (16)

// ライン
#define LINE_DELETE_FLG (FIELD_HEIGHT * CHR_METEO)
#define DEF_FLASH_WAIT (6)
#define DEF_FLASH_COUNT (4)
#define LINE_DELETE_INTERVAL (60*1)

// aim
#define DEF_AIM_SIZE (16)

// スコア
#define BASE_SCORE (100)
#define DEF_SCORE_X (21)
#define DEF_SCORE_Y (0)
#define SCORE_DIGIT (8)
#define NUM_WIDTH (1)

// ハイスコア
#define DEF_HISCORE_X (21)
#define DEF_HISCORE_Y (17)

// レベル
#define DEF_LV_X (5)
#define DEF_LV_Y (0)
#define LV_DIGIT (1)

// ライン
#define DEF_LINE_X (12)
#define DEF_LINE_Y (0)
#define LINE_DIGIT (3)


// コメット
#define MAX_COMET (3)
#define DEF_COMET_SPEED (3)
#define COMET_WIDTH (16)
#define COMET_HEIGHT (9)
#define APPEAR_COMET_RND (31)


// ゲームオーバー
#define DEF_OVER_X (11)
#define DEF_OVER_Y (10)
#define OVER_WIDTH (10)
#define DEF_OVER_WAIT (1*60+30)


// レディ
#define DEF_READY_X (12)
#define DEF_READY_Y (10)
#define READY_WIDTH (6)
#define DEF_READY_WAIT (8)
#define DEF_READY_COUNT (2 * 6)


// ステータス異常
#define DEF_STATUS_TIME (60*6)
#define BONUS_RATE (10)


// SRAM
#define SRAM_CHECK_HISC (0)
#define SRAM_HISCORE_NOMAL (4)
#define SRAM_HISCORE_HARD (8)


#define SRAM_ON (63)

// ゲームモード
#define MAX_MODE (2)
#define GAME_MODE_WIDTH (6)
#define GAME_MODE_X (18)
#define GAME_MODE_Y (14)

// スプライトの点滅
#define SPRITE_BLINK_WAIT (4)
#define SPRITE_BLINK_COUNT (8*2)// 点滅回数 * 2

////////// timer

#define DEF_TIMER_RELOAD (0)

///////////////////////////////////////////////////////////////////// マクロ

#define RND(MIN,MAX) ((MIN)+(int)(rand()/(float)RAND_MAX*((MAX)-(MIN)+1)))


///////////////////////////////////////////////////////////////////// グローバル変数

// ゲーム管理
GLOBAL GameStateType game_state;
GLOBAL LevelType level[MAX_MODE];

// 自機
GLOBAL SpriteChrType ship;

// タマ
GLOBAL ShotType shot[MAX_SHOT];

// 星点滅間隔
GLOBAL s8 blink_star_interval[MAX_MAP_X * MAX_MAP_Y];
GLOBAL s8 blink_star_interval_work[MAX_MAP_X * MAX_MAP_Y];

// 隕石フィールド
GLOBAL int meteo_field[FIELD_WIDTH*FIELD_HEIGHT];

// ライン点滅
GLOBAL FlashLineType flash_line[FIELD_WIDTH];

// 流星
GLOBAL CometType comet[MAX_COMET];

// メッセージ
GLOBAL BlinkMessageType mes;

// ゲームオーバーのウェイト
GLOBAL WaitType over_wait;

// スプライトの点滅
GLOBAL SpriteBlinkType sprite_blink;

// 照準x
GLOBAL int aim_x;

///////////////////////////////////////////////////////////////////// グローバルプロトタイプ
void init_ship( void );
void game( void );
void init_game( void );
void update_hiscores( void );
void disp_game_mode( void );


#endif	/* _game_h_ */
