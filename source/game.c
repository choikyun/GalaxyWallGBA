/***************************************************
 GALAXY WALL for GBA
 ver 1.00
 2010.7.27
 choi kyun
 ***************************************************/
//#define GLOBAL_VALUE_DEFINE
#include <stdio.h>
#include <stdlib.h>
#include <gba.h>

#include "game.h"
#include "bg.h"
#include "sprite.h"
#include "score.h"
#include "music.h"

static void
move_ship (void);
static void
blink_star (void);
static void
disp_title (void);
static void
draw_meteo_field (void);
static void
disp_over (void);
static void
set_new_line (int pos);
static void
init_meteo_field (void);
static void
draw_meteo_field (void);
static void
draw_map_meteo (int offset, u16 chr);
static void
create_bg_map (void);
static void
scroll_meteo_field (void);
static void
init_shot (void);
static void
launch_shot (void);
static void
move_shot (void);
static bool
is_hit_shot (int x, int y);
static void
level_up (void);
static void
check_line (void);
static void
set_flash_line (int line);
static void
flash_lines (void);
static void
delete_line (int line);
static void
draw_flash_line (int line);
static void
init_flash_line (void);
static void
set_aim (void);
static void
init_aim (void);
static void
add_score (int line);
static void
add_line (void);
static void
update_scores (void);
static void
update_levels (void);
static void
update_lines (void);
static void
disp_num (int x, int y, u32 num);
static void
disp_num_title (int x, int y, u32 num);
static void
check_over (void);
static void
pause (void);
static void
init_comet (void);
static void
move_comet (void);
static void
appeare_comet (void);
static bool
is_hit_ship (int y);
static void
check_ship_status (void);
static void
set_meteo_x3 (int x, int y);
static void
disp_ready (void);
static void
set_ready (void);
static void
check_over_wait (void);
static bool
is_flash_line (void);
static void
blink_sprite (void);
static void
erase_aim (void);

/***************************************************
 メインループ
 ***************************************************/
void
game (void)
{
  game_state.key = keysDown ();
  game_state.keyr = keysDownRepeat ();

  switch (game_state.scene)
  {
    case GAME_TITLE:
      disp_title ();
      break;

    case GAME_MAIN:
      move_comet ();
      move_ship ();
      move_shot ();
      blink_star ();
      blink_sprite ();
      appeare_comet ();
      launch_shot ();
      draw_meteo_field ();
      scroll_meteo_field ();
      check_line ();
      flash_lines ();
      level_up ();
      set_aim ();
      check_over ();
      pause ();
      check_ship_status ();
      break;

    case GAME_READY:
      blink_star ();
      move_ship ();
      disp_ready ();
      break;

    case GAME_PAUSE:
      pause ();
      break;

    case GAME_OVER:
      disp_over ();
      break;

    case GAME_OVER_PRE:
      check_over_wait ();
      break;
  }
}

/***************************************************
 ゲーム初期化
 ***************************************************/
void
init_game (void)
{
  int i;

  // ゲームステート初期化
  game_state.scene = GAME_TITLE;
  game_state.scroll_speed = game_state.scroll_speed_rel = DEF_METEO_SPEED;
  game_state.scroll_offset = 0;

  // レベル初期化
  for (i = 0; i < MAX_MODE; i++)
  {
    level[i].lv = 1;
    level[i].score = 0;
    level[i].line = 0;
    if (i)
    {
      level[i].up_count = HARD_LEVEL_UP_COUNT;
      level[i].up_count_rel = HARD_LEVEL_UP_COUNT;
    }
    else
    {
      level[i].up_count = NOMAL_LEVEL_UP_COUNT;
      level[i].up_count_rel = NOMAL_LEVEL_UP_COUNT;
    }
  }

  // 自機初期化
  init_ship ();
  // フィールド初期化
  init_meteo_field ();
  // フラッシュライン初期化
  init_flash_line ();
  // コメット初期化
  init_comet ();
}

/***************************************************
 フラッシュライン初期化
 ***************************************************/
static void
init_flash_line (void)
{
  int i;

  for (i = 0; i < FIELD_WIDTH; i++)
  {
    flash_line[i].wait_rel = 0;
    flash_line[i].chr = 0;
    flash_line[i].count = 0;
  }
}

/***************************************************
 コメット初期化
 ***************************************************/
static void
init_comet (void)
{
  int i;

  for (i = 0; i < MAX_COMET; i++)
  {
    set_sprite_form (SPRITE_COMET + i, OBJ_SIZE(1), OBJ_SQUARE, OBJ_256_COLOR);
    //set_sprite_tile( SPRITE_COMET + i, TILE_CHR_COMET + i * 8 );
  }

  game_state.comet_num = 0;
}

/***************************************************
 コメット出現
 ***************************************************/
static void
appeare_comet (void)
{
  int x, y;

  if ( RND( 0, APPEAR_COMET_RND) || game_state.comet_num >= MAX_COMET)
    return;

  comet[game_state.comet_num].speed = -DEF_COMET_SPEED;
  comet[game_state.comet_num].kind = RND(0, 2);

  x = SCREEN_WIDTH - 1;
  y = RND( 0, FIELD_HEIGHT-1 ) * DEF_METEO_SIZE + DEF_STATUS_HEIGHT;

  move_sprite (SPRITE_COMET + game_state.comet_num, x, y);
  set_sprite_tile (SPRITE_COMET + game_state.comet_num,
  TILE_CHR_COMET + comet[game_state.comet_num].kind * 8);

  game_state.comet_num++;
}

/***************************************************
 コメット移動
 ***************************************************/
static void
move_comet (void)
{
  int i, x, y, curr, end;
  OBJATTR *sp = (OBJATTR*) OAM + SPRITE_COMET;

  if (!game_state.comet_num)
    return;

  // 後ろからバッファを操作
  curr = end = game_state.comet_num - 1;
  for (i = game_state.comet_num; i > 0; i--, curr--)
  {
    // 移動
    x = read_sprite_x (SPRITE_COMET + curr);
    y = read_sprite_y (SPRITE_COMET + curr);

    x += comet[curr].speed;
    move_sprite (SPRITE_COMET + curr, x, y);

    // 画面外で消去
    if ((((u16) x + COMET_WIDTH) & 511) >= (u16) SCREEN_WIDTH + COMET_WIDTH)
    {
      // 自機との当たり判定
      if (is_hit_ship (y) && !ship.status)
      {
        ship.status = comet[curr].kind + 1; // ステータス異常
        ship.status_time = DEF_STATUS_TIME;
        PlaySound (SOUND_STATUS);
        // 自機絵柄
        set_sprite_tile (SPRITE_SHIP,
        TILE_CHR_SHIP_COMET1 + comet[curr].kind * 8);
      }

      // 弾削除
      comet[curr].kind = comet[end].kind;
      comet[curr].speed = comet[end].speed;
      // スプライト
      CpuSet (sp + end, sp + curr, (COPY16 | sizeof(OBJATTR) / 2));
      // スプライト非表示
      erase_sprite (end + SPRITE_COMET);
      game_state.comet_num--;
      end--;
    }
  }
}

/***************************************************
 自機とコメットさん当たり判定
 ***************************************************/
static bool
is_hit_ship (int y)
{
  if (y == ship.y)
  {
    return true;
  }
  else
  {
    return false;
  }
}

/***************************************************
 レベルアップ
 ***************************************************/
void
level_up (void)
{
  if (--level[game_state.mode].up_count
      || level[game_state.mode].lv >= MAX_LEVEL)
    return;

  level[game_state.mode].up_count = level[game_state.mode].up_count_rel;
  level[game_state.mode].lv++;
  game_state.scroll_speed_rel -= SCROLL_UP_STEP;
  update_levels ();
}

/***************************************************
 自機初期化
 ***************************************************/
void
init_ship (void)
{
  set_sprite_form (SPRITE_SHIP, OBJ_SIZE(1), OBJ_SQUARE, OBJ_256_COLOR);
  set_sprite_tile (SPRITE_SHIP, TILE_CHR_SHIP);

  ship.num = 0;
  ship.status = SHIP_NOMAL;
  ship.status_time = 0;
  ship.x = DEF_SHIP_X;
  ship.y = DEF_SHIP_Y;

  // 弾初期化
  init_shot ();
  // 照準初期化
  init_aim ();
}

/***************************************************
 自機移動
 ***************************************************/
static void
move_ship (void)
{
  u16 key = game_state.keyr;

  if ((key & KEY_UP) && ship.y > 0 + SHIP_MOVE_STEP
      && ship.status != SHIP_DONTMOVE)
  {
    ship.y -= SHIP_MOVE_STEP;
    game_state.shot_interval = 1;
  }
  else if ((key & KEY_DOWN) && ship.y < SCREEN_HEIGHT - SHIP_MOVE_STEP
      && ship.status != SHIP_DONTMOVE)
  {
    ship.y += SHIP_MOVE_STEP;
    game_state.shot_interval = 1;
  }

  move_sprite (ship.num, ship.x, ship.y);
}

/***************************************************
 自機ステータス異常カウント
 ***************************************************/
static void
check_ship_status (void)
{
  if (!ship.status)
    return;

  if (!--ship.status_time)
  {
    ship.status = SHIP_NOMAL;
    set_sprite_tile (SPRITE_SHIP, TILE_CHR_SHIP);
    PlaySound (SOUND_STATUS_NOMAL);
  }

  // 点滅セット
  if (ship.status_time == SPRITE_BLINK_COUNT * SPRITE_BLINK_WAIT)
  {
    sprite_blink.blink = false;
    sprite_blink.count = SPRITE_BLINK_COUNT;
    sprite_blink.wait = sprite_blink.wait_rel = SPRITE_BLINK_WAIT;
  }
}

/***************************************************
 スプライトの点滅
 ***************************************************/
static void
blink_sprite (void)
{
  if (!sprite_blink.count)
    return;

  if (!--sprite_blink.wait)
  {
    sprite_blink.wait = sprite_blink.wait_rel;
    sprite_blink.blink ^= 1;
    sprite_blink.count--;
  }

  if (sprite_blink.blink)
  {
    erase_sprite (ship.num);
  }
}

/***************************************************
 弾初期化
 ***************************************************/
static void
init_shot (void)
{
  int i;

  for (i = 0; i < MAX_SHOT; i++)
  {
    set_sprite_form (SPRITE_SHOT + i, OBJ_SIZE(1), OBJ_SQUARE, OBJ_256_COLOR);
    set_sprite_tile (SPRITE_SHOT + i, TILE_CHR_SHOT);
  }

  game_state.shot_num = 0;
  game_state.shot_kind = SHOT_NOMAL;
  game_state.shot_interval = 1; // ノーウェイト
}

/***************************************************
 照準初期化
 ***************************************************/
static void
init_aim (void)
{
  set_sprite_form (SPRITE_AIM, OBJ_SIZE(1), OBJ_SQUARE, OBJ_256_COLOR);
  set_sprite_tile (SPRITE_AIM, TILE_CHR_AIM);

  // オプション照準
  set_sprite_form (SPRITE_ICON_SHOT, OBJ_SIZE(1), OBJ_SQUARE, OBJ_256_COLOR);
  set_sprite_tile (SPRITE_ICON_SHOT, TILE_CHR_ICON_SHOT);

  set_sprite_form (SPRITE_ICON_STOP, OBJ_SIZE(1), OBJ_SQUARE, OBJ_256_COLOR);
  set_sprite_tile (SPRITE_ICON_STOP, TILE_CHR_ICON_STOP);

  set_sprite_form (SPRITE_ICON_BONUS, OBJ_SIZE(1), OBJ_SQUARE, OBJ_256_COLOR);
  set_sprite_tile (SPRITE_ICON_BONUS, TILE_CHR_ICON_BONUS);
}

/***************************************************
 弾を撃つ
 ***************************************************/
static void
launch_shot (void)
{
  u16 key = game_state.key;

  if (game_state.shot_num < MAX_SHOT && (key & KEY_A))
  {
    // スプライト
    move_sprite (game_state.shot_num + SPRITE_SHOT, ship.x + DEF_SHOT_X,
                 ship.y);
    shot[game_state.shot_num].speed = DEF_SHOT_SPEED;
    shot[game_state.shot_num].kind = game_state.shot_kind;

    game_state.shot_num++;
    PlaySound (SOUND_SHOT);
  }
}

/***************************************************
 弾移動
 ***************************************************/
static void
move_shot (void)
{
  int i, curr, end, x, y;
  OBJATTR *sp = (OBJATTR*) OAM + SPRITE_SHOT;

  if (!game_state.shot_num)
    return;

  // 後ろからバッファを操作
  curr = end = game_state.shot_num - 1;
  for (i = game_state.shot_num; i > 0; i--, curr--)
  {
    // 移動
    x = read_sprite_x (curr + SPRITE_SHOT) + shot[curr].speed;
    y = read_sprite_y (curr + SPRITE_SHOT);
    move_sprite (curr + SPRITE_SHOT, x, y);

    if (is_hit_shot (x, y))
    {
      // 弾削除
      shot[curr].kind = shot[end].kind;
      shot[curr].speed = shot[end].speed;
      // スプライト
      CpuSet (sp + end, sp + curr, (COPY16 | sizeof(OBJATTR) / 2));
      // スプライト非表示
      erase_sprite (end + SPRITE_SHOT);
      game_state.shot_num--;
      end--;
    }
  }
}

/***************************************************
 弾当たり判定
 ***************************************************/
static bool
is_hit_shot (int x, int y)
{
  // フィールド座標に変換
  x = (x + game_state.scroll_offset) / DEF_METEO_SIZE;
  y = (y - DEF_STATUS_HEIGHT) / DEF_METEO_SIZE;

  // 終端
  if (x == (FIELD_WIDTH - 1) && game_state.scroll_offset != 0)
  {
    if (!meteo_field[y * FIELD_WIDTH + x])
    {
      // ブロックセット
      meteo_field[y * FIELD_WIDTH + x] = CHR_METEO;
      set_meteo_x3 (x - 1, y);
      return true;
    }
  }
  else if (x == (FIELD_WIDTH - 1) && game_state.scroll_offset == 0)
  {
    if (!meteo_field[y * FIELD_WIDTH + x - 1])
    {
      // ブロックセット
      meteo_field[y * FIELD_WIDTH + x - 1] = CHR_METEO;
      set_meteo_x3 (x - 1 - 1, y);
      return true;
    }
  }

  if (meteo_field[y * FIELD_WIDTH + x + 1])
  {
    // ブロックセット
    meteo_field[y * FIELD_WIDTH + x] = CHR_METEO;
    set_meteo_x3 (x - 1, y);
    return true;
  }

  return false;
}

/***************************************************
 3連射
 ***************************************************/
static void
set_meteo_x3 (int x, int y)
{
  int i;

  if (ship.status != SHIP_SHOTX3)
    return;

  for (i = 0; i < 2; i++)
  {
    if (!(FIELD_WIDTH + x - i))
      break;
    meteo_field[y * FIELD_WIDTH + x - i] = CHR_METEO;
  }
}

/***************************************************
 ライン判定
 ***************************************************/
static void
check_line (void)
{
  int i, j, flg;

  for (i = 0; i < FIELD_WIDTH; i++)
  {
    flg = 0;
    for (j = 0; j < FIELD_HEIGHT; j++)
    {
      flg += meteo_field[j * FIELD_WIDTH + i];
    }

    if (flg == LINE_DELETE_FLG)
    {
      // フラッシュライン
      set_flash_line (i);
      // スコア加算
      add_score (i);
      // ライン加算
      add_line ();
    }
  }
}

/***************************************************
 ライン点滅セット
 ***************************************************/
static void
set_flash_line (int line)
{
  // フラッシュパラメータ
  flash_line[line].wait = DEF_FLASH_WAIT;
  flash_line[line].wait_rel = DEF_FLASH_WAIT;
  flash_line[line].chr = 0;
  flash_line[line].count = DEF_FLASH_COUNT;

  // 一定時間停止
  game_state.scroll_speed += LINE_DELETE_INTERVAL;

  draw_flash_line (line);
  PlaySound (SOUND_BLOCK);
}

/***************************************************
 ライン点滅
 ***************************************************/
static void
flash_lines (void)
{
  int i;

  for (i = 0; i < FIELD_WIDTH; i++)
  {
    if (!flash_line[i].wait_rel)
      continue;

    if (!--flash_line[i].wait)
    {
      flash_line[i].wait = flash_line[i].wait_rel;
      flash_line[i].chr ^= 1;
      draw_flash_line (i);
      if (!--flash_line[i].count)
      {
        // ライン削除
        delete_line (i);
      }
    }
  }
}

/***************************************************
 ライン描画
 ***************************************************/
static void
draw_flash_line (int line)
{
  int i;

  for (i = 0; i < FIELD_HEIGHT; i++)
  {
    meteo_field[i * FIELD_WIDTH + line] = CHR_FLASH + flash_line[line].chr;
  }
}

/***************************************************
 フラッシュ中か判定
 ***************************************************/
static bool
is_flash_line (void)
{
  int i;

  for (i = 0; i < FIELD_HEIGHT; i++)
  {
    if (flash_line[i++].count)
      return true;
  }

  return false;
}

/***************************************************
 1列削除
 ***************************************************/
static void
delete_line (int line)
{
  int i, j;

  for (i = line; i > 0; i--)
  {
    for (j = 0; j < FIELD_HEIGHT; j++)
    {
      meteo_field[j * FIELD_WIDTH + i] = meteo_field[j * FIELD_WIDTH + i - 1];
    }
  }

  // 先頭
  for (j = 0; j < FIELD_HEIGHT; j++)
  {
    meteo_field[j * FIELD_WIDTH + 0] = CHR_NONE;
  }

  // フラッシュラインも消去
  for (i = line; i > 0; i--)
  {
    flash_line[i].wait = flash_line[i - 1].wait;
    flash_line[i].wait_rel = flash_line[i - 1].wait_rel;
    flash_line[i].chr = flash_line[i - 1].chr;
    flash_line[i].count = flash_line[i - 1].count;
  }
  flash_line[0].wait = 0;
  flash_line[0].wait_rel = 0;
  flash_line[0].chr = 0;
  flash_line[0].count = 0;

}

/***************************************************
 星点滅
 ***************************************************/
static void
blink_star (void)
{
  int i;
  u16 *map = (u16 *) DEF_MAP_BASE_ADR;

  for (i = MAX_MAP_X; i < MAX_MAP_X * MAX_MAP_Y; i++)
  {
    if (map[i] != NOMAL_BG_CHR)
    {
      if (!(--blink_star_interval_work[i]))
      {
        blink_star_interval_work[i] = blink_star_interval[i];
        map[i] = (map[i] + 1) & 3;
      }
    }
  }
}

/***************************************************
 タイトル表示
 ***************************************************/
static void
disp_title (void)
{
  u16 key = game_state.key;
  u32 time;

  if (key & KEY_START)
  {
    game_state.scene = GAME_READY;

    // 背景初期化
    init_bg_tile ();

    // ランダマイズ
    time = REG_TM0CNT;
    srand (time);
    create_bg_map ();

    // メテオ用BGのオフセット
    BG_OFFSET[0].x = 0;
    BG_OFFSET[0].y = 0;
    // フィールド初期化
    init_meteo_field ();
    draw_meteo_field ();

    // 各種数値
    update_levels ();
    update_lines ();
    update_scores ();

    set_ready ();
    PlayMusic (MUSIC_READY, PLAY_LOOP_OFF);
  }
  else if ((key & KEY_R) && (key & KEY_B))
  {
    clear_hiscore ();
  }
  else if (key & KEY_SELECT)
  {
    game_state.mode ^= 1;
    disp_game_mode ();
    update_hiscores ();
    PlaySound (SOUND_SHOT);
  }
}

/***************************************************
 READYセット
 ***************************************************/
static void
set_ready (void)
{
  int i;
  u16 *map = (u16 *) DEF_METEO_BASE_ADR + DEF_READY_Y * MAX_MAP_X + DEF_READY_X;

  mes.x = DEF_READY_X;
  mes.y = DEF_READY_Y;
  mes.wait = DEF_READY_WAIT;
  mes.wait_rel = DEF_READY_WAIT;
  mes.chr = 0;
  mes.count = DEF_READY_COUNT;

  for (i = 0; i < READY_WIDTH; i++)
  {
    mes.save_map[i] = map[i];
  }
}

/***************************************************
 READY表示
 ***************************************************/
static void
disp_ready (void)
{
  int i;
  u16 *map = (u16 *) DEF_METEO_BASE_ADR + mes.y * MAX_MAP_X + mes.x;
  u16 tile;

  if (--mes.wait)
    return;
  mes.wait = mes.wait_rel;

  mes.chr ^= 1;

  if (mes.chr)
  {
    // 文字表示
    tile = MAP_READY_TILE;
    for (i = 0; i < READY_WIDTH; i++)
    {
      map[i] = tile++;
    }
  }
  else
  {
    // 文字消去
    for (i = 0; i < READY_WIDTH; i++)
    {
      map[i] = mes.save_map[i];
    }
  }

  if (!--mes.count)
  {
    game_state.scene = GAME_MAIN;
    PlayMusic (MUSIC_STAGE, PLAY_LOOP_ON);
  }
}

/***************************************************
 ゲームモード表示
 ***************************************************/
void
disp_game_mode (void)
{
  int i;
  u16 *map = (u16 *) DEF_MAP_BASE_ADR + GAME_MODE_Y * MAX_MAP_X + GAME_MODE_X;
  u16 tile;

  if (game_state.mode)
  {
    // ハード
    tile = HARD_MODE_TILE;
    for (i = 0; i < GAME_MODE_WIDTH; i++)
    {
      map[i] = tile++;
    }
  }
  else
  {
    // ノーマル
    tile = NOMAL_MODE_TILE;
    for (i = 0; i < GAME_MODE_WIDTH; i++)
    {
      map[i] = tile++;
    }
  }
}

/***************************************************
 フィールド初期化
 ***************************************************/
static void
init_meteo_field (void)
{
  int i;

  for (i = 0; i < FIELD_WIDTH * FIELD_HEIGHT; i++)
  {
    meteo_field[i] = CHR_NONE;
  }

  // あたらしい隕石
  for (i = FIELD_WIDTH / 2; i < FIELD_WIDTH; i++)
  {
    set_new_line (i);
  }
}

/***************************************************
 隕石セット
 ***************************************************/
static void
set_new_line (int pos)
{
  int i;

  // 1列クリア
  for (i = 0; i < FIELD_HEIGHT; i++)
  {
    meteo_field[i * FIELD_WIDTH + pos] = CHR_NONE;
  }

  meteo_field[pos + FIELD_WIDTH * RND(0, FIELD_HEIGHT-1)] = CHR_METEO; // 必ずひとつ出現

  for (i = 0; i < FIELD_HEIGHT - 1; i++)
  {
    if (!RND(0, 1))
    {
      meteo_field[pos + FIELD_WIDTH * RND(0, FIELD_HEIGHT-1)] = CHR_METEO;
    }
  }
}

/***************************************************
 フィールド描画
 ***************************************************/
static void
draw_meteo_field (void)
{
  int i, j;
  int base = MAX_MAP_X * 2;

  for (i = 0; i < FIELD_HEIGHT; i++)
  {
    for (j = 0; j < FIELD_WIDTH; j++)
    {
      draw_map_meteo (i * base + j * 2, meteo_field[i * FIELD_WIDTH + j]);
    }
  }
}

/***************************************************
 マップに描画 - 隕石 or 透明
 ***************************************************/
static void
draw_map_meteo (int offset, u16 chr)
{
  u16 *map = DEF_METEO_BASE_ADR + MAX_MAP_X * 2 * 2;

  chr = chr * 4 + MAP_CHR_TRANS;
  map[offset] = chr;
  map[offset + 1] = chr + 1;
  map[offset + MAX_MAP_X] = chr + 2;
  map[offset + MAX_MAP_X + 1] = chr + 3;
}

/***************************************************
 スクロール
 ***************************************************/
static void
scroll_meteo_field (void)
{
  int i, j;

  // BGスクロール
  BG_OFFSET[0].x = game_state.scroll_offset;

  if (--game_state.scroll_speed)
    return;
  game_state.scroll_speed = game_state.scroll_speed_rel;

  if (++game_state.scroll_offset > LIMIT_SCROLL_OFFSET)
    game_state.scroll_offset = 0;

  if (game_state.scroll_offset)
    return;

  // フィールドマップをスクロール
  for (i = 0; i < FIELD_HEIGHT; i++)
  {
    for (j = 0; j < FIELD_WIDTH - 1; j++)
    {
      meteo_field[i * FIELD_WIDTH + j] = meteo_field[i * FIELD_WIDTH + j + 1];
    }
  }

  // フラッシュラインもスクロール
  for (i = 0; i < FIELD_WIDTH - 1; i++)
  {
    flash_line[i].wait = flash_line[i + 1].wait;
    flash_line[i].wait_rel = flash_line[i + 1].wait_rel;
    flash_line[i].chr = flash_line[i + 1].chr;
    flash_line[i].count = flash_line[i + 1].count;
  }
  flash_line[ FIELD_WIDTH - 1].wait = 0;
  flash_line[ FIELD_WIDTH - 1].wait_rel = 0;
  flash_line[ FIELD_WIDTH - 1].chr = 0;
  flash_line[ FIELD_WIDTH - 1].count = 0;

  set_new_line ( DEF_NEW_LINE);
}

/***************************************************
 ゲームオーバー判定
 ***************************************************/
static void
check_over (void)
{
  int i, flg = 0;

  for (i = 0; i < FIELD_HEIGHT; i++)
  {
    flg += meteo_field[i * FIELD_WIDTH + 0];
  }

  if (flg != 0 && flg != (CHR_FLASH * FIELD_HEIGHT)
      && flg != ((CHR_FLASH + 1) * FIELD_HEIGHT)
      && !is_flash_line () /*&& ! game_state.scroll_offset*/)
  {
    game_state.scene = GAME_OVER_PRE;
    over_wait.wait = DEF_OVER_WAIT;
  }
}

/***************************************************
 ゲームオーバー時のウェイト
 ***************************************************/
static void
check_over_wait (void)
{
  u16 *map;
  u16 chr;
  int i;

  if (--over_wait.wait)
    return;

  // スコア更新
  save_hiscore (level[game_state.mode].score);

  // ゲームオーバー表示
  map = (u16 *) DEF_METEO_BASE_ADR + DEF_OVER_Y * MAX_MAP_X + DEF_OVER_X;
  chr = MAP_OVER_TILE;
  for (i = 0; i < OVER_WIDTH; i++)
  {
    map[i] = chr++;
  }
  erase_sprite (SPRITE_AIM);
  game_state.scene = GAME_OVER;
  PlayMusic (MUSIC_OVER, PLAY_LOOP_OFF);
}

/***************************************************
 ゲームオーバー
 ***************************************************/
static void
disp_over (void)
{
  u16 key = game_state.key;

  if (key & KEY_START)
  {
    init_sprite ();
    init_hiscore ();
    init_title ();
    init_game ();
    PlayMusic (MUSIC_TITLE, PLAY_LOOP_ON);
  }
}

/***************************************************
 ポーズ
 ***************************************************/
static void
pause (void)
{
  u16 key = game_state.key;

  if (key & KEY_SELECT)
  {
    game_state.scene ^= GAME_PAUSE;
    PlaySound (SOUND_PAUSE);
    if (game_state.scene & GAME_PAUSE)
    {
      StopMusic ();
    }
    else
    {
      PlayMusic (MUSIC_STAGE, PLAY_LOOP_ON);
    }
  }
}

/***************************************************
 スコア加算
 ***************************************************/
static void
add_score (int line)
{
  if (ship.status != SHIP_BONUS)
  {
    level[game_state.mode].score += (FIELD_WIDTH - line) * BASE_SCORE;
  }
  else
  {
    level[game_state.mode].score += (FIELD_WIDTH - line) * BASE_SCORE
        * BONUS_RATE;
  }
  update_scores ();
}

/***************************************************
 ライン加算
 ***************************************************/
static void
add_line (void)
{
  level[game_state.mode].line++;
  update_lines ();
}

/***************************************************
 スコア表示
 ***************************************************/
static void
update_scores (void)
{
  int i;
  int pos = SCORE_DIGIT * NUM_WIDTH;
  u32 sc = level[game_state.mode].score;

  for (i = 0; i < SCORE_DIGIT; i++)
  {
    disp_num ( DEF_SCORE_X + pos, DEF_SCORE_Y, sc % 10);
    sc /= 10;
    pos -= NUM_WIDTH;
  }
}

/***************************************************
 ハイスコア表示
 ***************************************************/
void
update_hiscores (void)
{
  int i;
  int pos = SCORE_DIGIT * NUM_WIDTH;
  u32 sc = level[game_state.mode].hiscore;

  for (i = 0; i < SCORE_DIGIT; i++)
  {
    disp_num_title ( DEF_HISCORE_X + pos, DEF_HISCORE_Y, sc % 10);
    sc /= 10;
    pos -= NUM_WIDTH;
  }
}

/***************************************************
 レベル表示
 ***************************************************/
static void
update_levels (void)
{
  int i;
  int pos = LV_DIGIT * NUM_WIDTH;
  u32 sc = level[game_state.mode].lv;

  for (i = 0; i < LV_DIGIT; i++)
  {
    disp_num ( DEF_LV_X + pos, DEF_LV_Y, sc % 10);
    sc /= 10;
    pos -= NUM_WIDTH;
  }
}

/***************************************************
 ライン表示
 ***************************************************/
static void
update_lines (void)
{
  int i;
  int pos = LINE_DIGIT * NUM_WIDTH;
  u32 sc = level[game_state.mode].line;

  for (i = 0; i < LINE_DIGIT; i++)
  {
    disp_num ( DEF_LINE_X + pos, DEF_LINE_Y, sc % 10);
    sc /= 10;
    pos -= NUM_WIDTH;
  }
}

/***************************************************
 数字表示　BG1
 ***************************************************/
static void
disp_num (int x, int y, u32 num)
{
  u16 *map = (u16 *) DEF_MAP_BASE_ADR + y * MAX_MAP_X + x;

  map[0] = num + SCORE_NUM_TILE;
}

/***************************************************
 数字表示　BG1 タイトル画面
 ***************************************************/
static void
disp_num_title (int x, int y, u32 num)
{
  u16 *map = (u16 *) DEF_MAP_BASE_ADR + y * MAX_MAP_X + x;

  map[0] = num + HISCORE_NUM_TILE;
}

/***************************************************
 照準
 ***************************************************/
static void
set_aim (void)
{
  int y = (ship.y - DEF_STATUS_HEIGHT) / DEF_METEO_SIZE;
  int i;

  erase_aim ();

  for (i = 0; i < FIELD_WIDTH; i++)
  {
    if (meteo_field[y * FIELD_WIDTH + i])
      break;
  }

  if (i == FIELD_WIDTH)
  {
    i = SCREEN_WIDTH - DEF_AIM_SIZE;
  }
  else
  {
    i = (i - 1) * DEF_METEO_SIZE - game_state.scroll_offset;
  }
  aim_x = i;
  move_sprite (SPRITE_AIM + ship.status, i, ship.y);
}

/***************************************************
 BG星マップ作成
 ***************************************************/
static void
erase_aim (void)
{
  int i;

  for (i = 0; i < 4; i++)
    erase_sprite (SPRITE_AIM + i);
}

/***************************************************
 BG星マップ作成
 ***************************************************/
static void
create_bg_map (void)
{
  int i;
  u16 *map = (u16 *) DEF_MAP_BASE_ADR;
  u16 st_chr = BG_STATUS_TILE;

  // BG1
  // 星
  for (i = MAX_MAP_X; i < MAX_MAP_X * MAX_MAP_Y; i++)
  {
    if (!(RND(0, STAR_RND)))
    {
      map[i] = RND(0, 3);
      // 点滅ウェイト
      blink_star_interval[i] = DEF_STAR_INTERVAL
          + RND( 0, MAX_STAR_INTERVAL ) * 4;
      blink_star_interval_work[i] = blink_star_interval[i];
    }
    else
    {
      map[i] = NOMAL_BG_CHR;
    }
  }

  // ステータス
  map = (u16 *) DEF_MAP_BASE_ADR;
  for (i = 0; i < MAX_MAP_X; i++)
  {
    map[i] = st_chr++;
  }

  // BG0 メテオ用
  map = (u16 *) DEF_METEO_BASE_ADR;
  for (i = 0; i < MAX_MAP_X * MAX_MAP_Y; i++)
  {
    map[i] = MAP_CHR_TRANS;
  }
}

