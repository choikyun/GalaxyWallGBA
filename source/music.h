/***************************************************
 GALAXY WALL for GBA
 ver 1.00
 2010.7.27
 choi kyun
 ***************************************************/

#ifndef _music_h_
#define _music_h_

#include <gba.h>
#include "h/DMA.h"
#include "h/Sound.h"
#include "h/Timer.h"
#include "h/IRQ.h"

#ifdef GLOBAL_VALUE_DEFINE
#define GLOBAL
#define GLOBAL_VAL(v) = (v)
#else
#define GLOBAL extern
#define GLOBAL_VAL(v)
#endif

#define MAX_MUSIC (9)
#define MAX_SOUND (9)

////// http://f1.aaa.livedoor.jp/~progrm/gba/ よりほぼ丸々引用

//*************************************************************
// 楽曲データ
// DirectsoundAで再生
//*************************************************************
extern u8 m0_bin[]; // 曲0 タイトル
extern u8 m1_bin[]; // 曲1 ステージ
extern u8 m2_bin[]; // 曲2 ゲームオーバー
extern u8 m3_bin[]; // 曲3 レディ

#define SAMPLING_M0 152660 // 曲0 サンプリング数
#define SAMPLING_M1 140888 // 曲1 サンプリング数
#define SAMPLING_M2 46346 // 曲2 サンプリング数
#define SAMPLING_M3 15447 // 曲3 サンプリング数

typedef struct
{
  u8 *dataPtr;   // データアドレス
  u32 dataMax;
  int priority;
} WaveListType;

enum
{
  MUSIC_TITLE, MUSIC_STAGE, MUSIC_OVER, MUSIC_READY
};

//*************************************************************
// 効果音データ
// DirectsoundBで再生
//*************************************************************
extern u8 s0_bin[]; // 音0 ショット
extern u8 s1_bin[]; // 音1 ブロック
extern u8 s2_bin[]; // 音2 ポーズ
extern u8 s3_bin[]; // 音3 ステータス異常
extern u8 s4_bin[]; // 音4 ステータス回復

#define SAMPLING_E0 4042 // 音0 ショット
#define SAMPLING_E1 6251 // 音1 ブロック
#define SAMPLING_E2 16551  // 音2 ポーズ
#define SAMPLING_E3 12505  // 音3 ステータス異常
#define SAMPLING_E4 5515  // 音3 ステータス回復

enum
{
  SOUND_SHOT, SOUND_BLOCK, SOUND_PAUSE, SOUND_STATUS, SOUND_STATUS_NOMAL
};

//*************************************************************
// DIRECTサウンド制御構造体
//*************************************************************
struct ds_struc
{
  u32 ds_Count;       // データ（BYTE）カウンタ サンプリングカウント用変数
  u8 ds_Playing;     // 楽曲再生中フラグ 0:停止 1:再生中
  u8 ds_snd_no;      // 再生中の楽曲（効果音）の種類を示す番号 0～
  u8 loopflg;        // ループ演奏 0:ループしません 1:ループ
};

GLOBAL struct ds_struc DSmusic;	// 楽曲用
GLOBAL struct ds_struc DSeffect;	// 効果音用

GLOBAL u16 save_REG_SGCNT0_H;

#define PLAY_LOOP_ON  1 // ループ演奏 1:ループ
#define PLAY_LOOP_OFF 0 // ループ演奏 0:ループ無し

//////////////////////////////////////////////////////////////////// プロトタイプ
void
StopSound ();
void
StopMusic ();
void
PlayMusic (int _no, int loop);
void
PlaySound (int _no);
void
DirectSoundInitialize ();

void
IRQ_Music ();
void
IRQ_Sound ();

#endif	/* _music_h_ */
