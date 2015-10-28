/***************************************************
 GALAXY WALL for GBA
 ver 1.00
 2010.7.27
 choi kyun
 ***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gba.h>

#include "bg.h"
#include "game.h"

/***************************************************
 BG初期化
 ***************************************************/
void
init_bg (void)
{
  // モード設定 BG0, BG1 使用
  SetMode ( DEF_MODE | (BG0_ENABLE | BG1_ENABLE) | OBJ_ENABLE | OBJ_1D_MAP);

  // TILE or BITMAP
  if ( DEF_MODE < MODE_3)
  {
    // BG1　星
    REG_BG1CNT = DEF_BG_SIZE | DEF_BG_COLOR | CHAR_BASE(0) | MAP_BASE(28);
    // BG0　メテオ| タイトル
    REG_BG0CNT = DEF_BG_SIZE | DEF_BG_COLOR | CHAR_BASE(0) | MAP_BASE(30);
  }
}

/***************************************************
 BG ビットマップ転送
 ***************************************************/
void
init_bg_bitmap (void)
{
  u16 *screen = (u16 *) VRAM;

  CpuSet ( DEF_BG_BITMAP, screen, (COPY16 | DEF_BG_LEN));
}

/***************************************************
 BG ビットマップ転送 圧縮LZ77
 ***************************************************/
void
init_bg_bitmap_lz77 (void)
{
  void *screen = (void *) VRAM;

  LZ77UnCompVram ((void *) DEF_BG_BITMAP, screen);
}

/***************************************************
 BG タイル・パレット転送
 ***************************************************/
void
init_bg_tile (void)
{
  // パレット
  CpuSet ( DEF_BG_PALLET, BG_PALETTE, (COPY16 | DEF_BG_PALLET_LEN));

  // タイル　星パターン
  CpuSet ( STAR_TILE, DEF_BG_BASE_ADR, (COPY16 | STAR_TILE_LEN));
  // タイル　ステータス
  CpuSet ( BG_STATE_TILE, (u16 *) DEF_BG_BASE_ADR + STAR_TILE_LEN,
          (COPY16 | BG_STATE_TILE_LEN));
  // タイル　透過
  CpuSet ( TRANS_TILE,
          (u16 *) DEF_BG_BASE_ADR + STAR_TILE_LEN + BG_STATE_TILE_LEN,
          (COPY16 | TRANS_TILE_LEN));
  // タイル　メテオ
  CpuSet (
      METO_TILE,
      (u16 *) DEF_BG_BASE_ADR + STAR_TILE_LEN + BG_STATE_TILE_LEN
          + TRANS_TILE_LEN,
      (COPY16 | METEO_TILE_LEN));
  // タイル　フラッシュ
  CpuSet (
      FLASH_TILE,
      (u16 *) DEF_BG_BASE_ADR + STAR_TILE_LEN + BG_STATE_TILE_LEN
          + TRANS_TILE_LEN + METEO_TILE_LEN,
      (COPY16 | FLASH_TILE_LEN));
  // タイル　透過
  CpuSet (
      TRANS_TILE,
      (u16 *) DEF_BG_BASE_ADR + STAR_TILE_LEN + BG_STATE_TILE_LEN
          + TRANS_TILE_LEN + METEO_TILE_LEN + FLASH_TILE_LEN,
      (COPY16 | TRANS_TILE_LEN));
  // タイル　数字
  CpuSet (
      NUM_TILE,
      (u16 *) DEF_BG_BASE_ADR + STAR_TILE_LEN + BG_STATE_TILE_LEN
          + TRANS_TILE_LEN + METEO_TILE_LEN + FLASH_TILE_LEN + TRANS_TILE_LEN,
      (COPY16 | NUM_TILE_LEN));
  // タイル　ゲームオーバー
  CpuSet (
      OVER_TILE,
      (u16 *) DEF_BG_BASE_ADR + STAR_TILE_LEN + BG_STATE_TILE_LEN
          + TRANS_TILE_LEN + METEO_TILE_LEN + FLASH_TILE_LEN + TRANS_TILE_LEN
          + NUM_TILE_LEN,
      (COPY16 | OVER_TILE_LEN));
  // タイル　レディ
  CpuSet (
      READY_TILE,
      (u16 *) DEF_BG_BASE_ADR + STAR_TILE_LEN + BG_STATE_TILE_LEN
          + TRANS_TILE_LEN + METEO_TILE_LEN + FLASH_TILE_LEN + TRANS_TILE_LEN
          + NUM_TILE_LEN + OVER_TILE_LEN,
      (COPY16 | READY_TILE_LEN));
}

/***************************************************
 タイトル タイル・パレット転送
 ***************************************************/
void
init_title (void)
{
  u16 trans_tile = 0;

  // BG0
  // パレット
  CpuSet ( DEF_BG_PALLET, BG_PALETTE, (COPY16 | DEF_BG_PALLET_LEN));

  // タイル　タイトル
  CpuSet (title_tileTiles, DEF_BG_BASE_ADR, (COPY16 | title_tileTilesLen / 2));
  // タイル　数字
  CpuSet ( NUM_TILE, (u16 *) DEF_BG_BASE_ADR + title_tileTilesLen / 2,
          (COPY16 | NUM_TILE_LEN));
  // タイル　ノーマル
  CpuSet ( NOMAL_TILE,
          (u16 *) DEF_BG_BASE_ADR + title_tileTilesLen / 2 + NUM_TILE_LEN,
          (COPY16 | NOMAL_TILE_LEN));
  // タイル　ハード
  CpuSet (
      HARD_TILE,
      (u16 *) DEF_BG_BASE_ADR
          + title_tileTilesLen / 2+ NUM_TILE_LEN + NOMAL_TILE_LEN,
      (COPY16 | HARD_TILE_LEN));

  // BG0マップ
  CpuSet (&trans_tile, DEF_METEO_BASE_ADR,
          (COPY16 | FILL | MAP_WIDTH * MAP_HEIGHT));

  // BG1マップ
  CpuSet (&trans_tile, DEF_MAP_BASE_ADR,
          (COPY16 | FILL | MAP_WIDTH * MAP_HEIGHT));
  CpuSet (title_tileMap, DEF_MAP_BASE_ADR, (COPY16 | title_tileMapLen / 2));

  // ハイスコア表示
  update_hiscores ();
  // ゲームモード
  disp_game_mode ();
}

