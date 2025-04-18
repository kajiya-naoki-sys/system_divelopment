/*
 * ファイル名	: member.h
 * 機能			: 会員管理を行う
 * 特記事項		: なし
 * 修正履歴		:  1  2012/01/10 V01L1 初版
 *				:  2  
 */

#ifndef MEMBER_H
#define MEMBER_H

/* #defineマクロ */
/* バッファサイズ */
/* WriteMemberFile */
#define WRITEMEMBERFILE_BUF_SIZE		100		/* フォーマット用文字列格納用バッファサイズ */

/* InputRegistMember */
#define INPUTREGISTMEMBER_BUF_SIZE		128		/* 文字列入力用バッファサイズ */
	
/* GetMemberID */
#define GETMEMBERID_STR_BUF_SIZE		20		/* 文字列操作用バッファサイズ */
#define GETMEMBERID_DATE_BUF_SIZE		10		/* 本日の日付文字列格納用バッファサイズ */

/* DisplayRegistMember */
#define DISPLAYREGISTMEMBER_BUF_SIZE	16		/* 日付フォーマット用文字列格納用バッファサイズ */

/* InputUpdateGoods */
#define INPUTUPDATEMEMBER_DATE_BUF_SIZE	16		/* 日付フォーマット用文字列格納用バッファサイズ */
	
/* DisplayMember */
#define DISPLAYMEMBER_BUF_SIZE			16		/* 日付フォーマット用文字列格納用バッファサイズ */

/* InputUpdateMember */
#define INPUTUPDATEMEMBER_BUF_SIZE		16		/* 日付フォーマット用文字列格納用バッファサイズ */

/* DisplayMemberList */
#define DISPLAYMEMBERLIST_HEAD_COL_NUM				30	/* DisplayMemberList ヘッダー項目列数 */
#define DISPLAYMEMBERLIST_HEAD_COL_BUF_SIZE			20	/* DisplayMemberList ヘッダー項目文字列用バッファサイズ */
#define DISPLAYMEMBERLIST_HEAD_BUF_SIZE				200	/* DisplayMemberList ヘッダー文字列用バッファサイズ */
#define DISPLAYMEMBERLIST_HEAD_FORMAT_COL_NUM		10	/* DisplayMemberList printfのフォーマット文字列用列数 */
#define DISPLAYMEMBERLIST_HEAD_FORMAT_COL_BUF_SIZE	10	/* DisplayMemberList printfのフォーマット文字列用バッファサイズ */
#define DISPLAYMEMBERLIST_DATE_BUF_SIZE				20	/* DisplayMemberList 日付フォーマット用文字列用バッファサイズ */
#define DISPLAYMEMBERLIST_DSP_BUF_SIZE				40	/* DisplayMemberList 表示文字列の長さ調整用バッファサイズ */

/* 会員一覧画面表示 */
#define MEMBER_MON_DSP_NUM		20				/* 1画面の会員表示数 */

/* 会員一覧表示：会員情報の表示桁数 */
#define MEMBER_DSP_ID_NUM			12			/* 会員ID */
#define MEMBER_DSP_NAME_NUM			12			/* 氏名 */
#define MEMBER_DSP_ADDR_NUM			24			/* 住所 */
#define MEMBER_DSP_TEL_NUM			12			/* 電話番号 */
#define MEMBER_DSP_BIRTH_NUM		10			/* 生年月日 */

/* 会員一覧表示：項目表示列数 */
#define MEMBER_DSP_COL_NUM			5			/* 表示項目数 */

/* 会員一覧表示：項目表示列番号 */
#define MEMBER_DSP_ROWNO_COL		0			/* 行番号 */
#define MEMBER_DSP_ID_COL			1			/* 会員ID */
#define MEMBER_DSP_NAME_COL			2			/* 氏名 */
#define MEMBER_DSP_ADDR_COL			3			/* 住所 */
#define MEMBER_DSP_TEL_COL			4			/* 電話番号 */
#define MEMBER_DSP_BIRTH_COL		5			/* 生年月日 */

/* 会員一覧表示：表示項目名（全角で5文字以内） */
#define MEMBER_DSP_ROWNO_NAME	"No."			/* 行番号 */
#define MEMBER_DSP_ID_NAME		"会員ID"		/* 会員ID */
#define MEMBER_DSP_NAME_NAME	"氏名"			/* 氏名 */
#define MEMBER_DSP_ADDR_NAME	"住所"			/* 住所 */
#define MEMBER_DSP_TEL_NAME		"電話番号"		/* 電話番号 */
#define MEMBER_DSP_BIRTH_NAME	"生年月日"		/* 生年月日 */

/* 会員情報マスタファイル */
#define MEMBER_FILE_NAME	"memberMST.dat"		/* 会員情報マスタファイル名 */
#define MEMBER_REG_MAX		10000				/* 会員最大登録数 */

/* 会員情報マスタファイル：項目名（全角で5文字以内） */
#define MEMBER_ID_NAME		"会員ID"			/* 会員ID */
#define MEMBER_NAME_NAME	"名前"				/* 名前 */
#define MEMBER_ADDR_NAME	"住所"				/* 住所 */
#define MEMBER_TEL_NAME		"電話番号"			/* 電話番号 */
#define MEMBER_BIRTH_NAME	"生年月日"			/* 生年月日 */

/* 会員情報マスタファイル：会員情報の各桁数（構造体メンバーの大きさ） */
#define MEMBER_ID_SIZE		12					/* 会員ID */
#define MEMBER_NAME_SIZE	16					/* 名前 */
#define MEMBER_ADDR_SIZE	60					/* 住所 */
#define MEMBER_TEL_SIZE		12					/* 電話番号 */
#define MEMBER_BIRTH_SIZE	8					/* 生年月日 */

/* 会員情報マスタファイル：会員情報レコード内の先頭位置 */
#define MEMBER_ID_POS		0										/* 会員ID */
#define MEMBER_NAME_POS		MEMBER_ID_POS + MEMBER_ID_SIZE			/* 名前 */
#define MEMBER_ADDR_POS		MEMBER_NAME_POS + MEMBER_NAME_SIZE		/* 住所 */
#define MEMBER_TEL_POS		MEMBER_ADDR_POS + MEMBER_ADDR_SIZE		/* 電話番号 */
#define MEMBER_BIRTH_POS	MEMBER_TEL_POS + MEMBER_TEL_SIZE		/* 生年月日 */

/* 会員情報マスタファイル：会員情報レコードのサイズ */
#define MEMBER_SIZE			MEMBER_BIRTH_POS + MEMBER_BIRTH_SIZE

/* structタグ定義 */
/* 会員情報 */
typedef struct member {
	char id[MEMBER_ID_SIZE+1];					/* 会員ID */
	char name[MEMBER_NAME_SIZE+1];				/* 名前 */
	char addr[MEMBER_ADDR_SIZE+1];				/* 住所 */
	char tel[MEMBER_TEL_SIZE+1];				/* 電話番号 */
	char birth[MEMBER_BIRTH_SIZE+1];			/* 生年月日 */
	struct member *next;						/* 自己参照ポインタ */
}MEMBER;

/* 関数プロトタイプ宣言 */
extern int ReadMemberFile(MEMBER **member);
extern void FreeMemberList(void);
extern int WriteMemberFile(void);
extern int SearchMember(const char *id, MEMBER **m);
extern void ClearMemberBuffer(MEMBER *m);
extern int InputRegistMember(MEMBER *m);
extern void DisplayRegistMember(const MEMBER *m);
extern int RegistMember(const MEMBER *m);
extern void DisplayMember(const MEMBER *m);
extern int DisplayMemberList(const int key, const int ud, const int menuNum);
extern int InputUpdateMember(MEMBER *m, MEMBER *mBuf);
extern int DeleteMember(const char *id);

#endif		/* end MEMBER_H */

