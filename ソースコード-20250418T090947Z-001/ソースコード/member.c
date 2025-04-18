/*
 * ファイル名	: member.c
 * 機能			: 会員管理を行う
 * 特記事項		: なし
 * 修正履歴		:  1  2012/01/10 V01L1 初版
 *				:  2  2012/02/14 V02L1
 */

/* ヘッダーの取り込み */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "menu.h"
#include "member.h"

/* static変数宣言 */
static MEMBER *root = NULL;		/* 会員情報リストの先頭ノード参照用 */

/* static関数宣言 */
static void CreateMemberList(MEMBER **member);
static int GetMemberID(char *id);
static void SortMemberList(const int key, const int ud);

/*
 * 関数名			: int ReadMemberFile(MEMBER **member)
 * 機能				: 会員情報を会員ID順にリスト構造に読み込む
 * 入力パラメータ	: なし
 * 出力パラメータ	: MEMBER **member:読み込んだ会員情報の先頭ノードのアドレス
 * 戻り値			: int	:TRUE
 * 特記事項			: なし
 */
int ReadMemberFile(MEMBER **member)
{
	int retVal = TRUE;
	MEMBER *newone;								/* 会員情報の追加ノード参照用 */
	MEMBER *target;								/* ターゲットノード用 */
	FILE* fp;									/* ファイルポインタ */
	char buf[MEMBER_SIZE+REC_DELIMITER_SIZE];	/* ファイル読込領域（1レコードサイズより余裕を持たせる） */
	errno_t error;
	
	/* 会員情報マスタファイルを読み込む */
	error = fopen_s(&fp, MEMBER_FILE_NAME, "r");
	if(error != 0) {
		printf("\n会員情報マスタファイルがありません。処理を終了します。\n");
		exit(EXIT_FAILURE);
	}
	
	/* ファイル読み込みのための前処理 */
	CreateMemberList(&target);
	*member = root;
	memset(buf, '\0', sizeof(buf));								/* ファイル読み込み領域をクリア */
	
	/* ファイルをEOFまで読み込む */
	while(fgets(buf, sizeof(buf), fp) != NULL) {				/* ファイル終了まで読み込む */
		
		/* 新たなノードを追加しデータを格納する */
		if((newone = (MEMBER*)malloc(sizeof(MEMBER))) == NULL) {	/* ノードを作成 */
			printf("動的メモリの取得に失敗しました。\n");
			exit(EXIT_FAILURE);
		}
		
		/* 会員情報をノードに格納する */
		strncpy_s(newone->id, MEMBER_ID_SIZE+1, &buf[MEMBER_ID_POS], _TRUNCATE);
		strncpy_s(newone->name, MEMBER_NAME_SIZE+1, &buf[MEMBER_NAME_POS], _TRUNCATE);
		strncpy_s(newone->addr, MEMBER_ADDR_SIZE+1, &buf[MEMBER_ADDR_POS], _TRUNCATE);
		strncpy_s(newone->tel, MEMBER_TEL_SIZE+1, &buf[MEMBER_TEL_POS], _TRUNCATE);
		strncpy_s(newone->birth, MEMBER_BIRTH_SIZE+1, &buf[MEMBER_BIRTH_POS], _TRUNCATE);
		
		/* 末尾の空白を削除する */
		TrimSpace(newone->id);
		TrimSpace(newone->name);
		TrimSpace(newone->addr);
		TrimSpace(newone->tel);
		TrimSpace(newone->birth);
		
		/* IDで昇順になるようにノードを追加する */
		target = root;											/* ターゲットを先頭に設定 */
		while(TRUE) {
			/* 次のノードがあるならば、IDをチェックする */
			if(target->next != NULL) {
				/* 追加ノードのIDが小さいならば、ターゲットの後ろにノードを追加して終了する */
				if(strncmp(newone->id, target->next->id, MEMBER_ID_SIZE) < 0) {
					newone->next = target->next;
					target->next = newone;
					break;
				} else {
					target = target->next;						/* ターゲットを更新して次のノードへ */
				}
			} else {
				/* 新しいノードをリストの末尾に追加して終了する */
				newone->next = NULL;
				target->next = newone;
				break;
			}
		}
	}
	fclose(fp);
	return retVal;
}

/*
 * 関数名			: static void CreateMemberList(MEMBER **member)
 * 機能				: 会員情報リストを初期化する
 * 入力パラメータ	: なし
 * 出力パラメータ	: MEMBER **member	:ダミーノードのアドレス
 * 戻り値			: なし
 * 特記事項			: なし
 */
static void CreateMemberList(MEMBER **member)
{
	/* ダミーノードを作成する */
	FreeMemberList();
	if((root = (MEMBER*)malloc(sizeof(MEMBER))) == NULL) {
		printf("動的メモリの取得に失敗しました。\n");
		exit(EXIT_FAILURE);
	}
	root->next = NULL;
	*member = root;
}

/*
 * 関数名			: void FreeMemberList(void)
 * 機能				: 会員情報リストをメモリから解放する
 * 入力パラメータ	: なし
 * 出力パラメータ	: なし
 * 戻り値			: なし
 * 特記事項			: なし
 */
void FreeMemberList(void)
{
	MEMBER *temp;
	
	while(root != NULL) {
		temp = root;
		root = root->next;
		free(temp);
	}
}

/*
 * 関数名			: int WriteMemberFile(void)
 * 機能				: 会員情報リストをファイルに書き込む
 * 入力パラメータ	: なし
 * 出力パラメータ	: なし
 * 戻り値			: int	:TRUE（書き込み正常）常にTRUEを返す
 * 特記事項			: 会員コードでソートしながら取り込む
 */
int WriteMemberFile(void)
{
	int retVal = TRUE;
	FILE* fp;								/* ファイルポインタ */
	MEMBER *target;							/* ターゲットノード用 */
	char form[WRITEMEMBERFILE_BUF_SIZE];	/* フォーマット用文字列 */
	errno_t error;

	/* ファイルをオープンする */
	error = fopen_s(&fp, MEMBER_FILE_NAME, "w");
	if(error != 0) {
		printf("\n会員情報マスタファイルに書き込みできません。処理を終了します。\n");
		exit(EXIT_FAILURE);
	}
	
	/* fprintfのフォーマットを設定する */
	sprintf_s(form, WRITEMEMBERFILE_BUF_SIZE, "%%-%ds%%-%ds%%-%ds%%-%ds%%-%ds\n",
		MEMBER_ID_SIZE,
		MEMBER_NAME_SIZE,
		MEMBER_ADDR_SIZE,
		MEMBER_TEL_SIZE,
		MEMBER_BIRTH_SIZE
	);
	
	/* 会員情報リストをファイルに書き込む */
	target = root;
	while(target->next != NULL) {
		/* リストの内容を書き込む */
		target = target->next;
		fprintf(fp, form,
			target->id,
			target->name,
			target->addr,
			target->tel,
			target->birth
		);
	}
	fclose(fp);
	return retVal;
}

/*
 * 関数名			: int SearchMember(const char *id, MEMBER **m)
 * 機能				: 【D-1121】指定したIDの会員情報を取得する
 * 入力パラメータ	: const char *id	:検索する会員ID
 * 出力パラメータ	: MEMBER **m		:検索された会員情報ノードへのポインタ
 * 戻り値			: int	:TRUE（会員情報を取得）/FALSE（指定した会員IDがない）
 * 特記事項			: なし
 */
int SearchMember(const char *id, MEMBER **m)
{
	int retVal = FALSE;
	MEMBER *target;				/* 検索ターゲットノード用 */
	
	target = root;
	while(target->next != NULL) {
		target = target->next;
		if(strncmp(target->id, id, MEMBER_ID_SIZE) == 0) {
			*m = target;		/* ヒットしたデータのアドレスを戻り値に設定 */
			retVal = TRUE;
			break;
		}
	}
	return retVal;
}

/*
 * 関数名			: void ClearMemberBuffer(MEMBER *m)
 * 機能				: 【D-1122】会員情報バッファをクリアする
 * 入力パラメータ	: MEMBER *m	:会員情報へのポインタ
 * 出力パラメータ	: なし
 * 戻り値			: なし
 * 特記事項			: なし
 */
void ClearMemberBuffer(MEMBER *m)
{
	m->id[0] = '\0';
	m->name[0] = '\0';
	m->addr[0] = '\0';
	m->tel[0] = '\0';
	m->birth[0] = '\0';
	m->next = NULL;
}

/*
 * 関数名			: int InputRegistMember(MEMBER *m)
 * 機能				: 【D-1122】新規に登録する会員情報を入力する
 * 入力パラメータ	: なし
 * 出力パラメータ	: MEMBER *m	:入力した会員情報へのポインタ
 * 戻り値			: int	:TRUE（新規会員ID取得）/FALSE（新規会員ID取得できない）
 * 特記事項			: なし
 */
int InputRegistMember(MEMBER *m)
{
	int retVal;
	char buf[INPUTREGISTMEMBER_BUF_SIZE];				/* 文字列用バッファ */
	char id[MEMBER_ID_SIZE+STRING_TERMINATOR_SIZE];		/* 会員ID用文字列 */
	
	/* 氏名を入力する */
	buf[0] = '\0';
	while(strlen(buf) == 0) {
	    printf("%-6s＞　", MEMBER_NAME_NAME);
		GetStr(buf, MEMBER_NAME_SIZE);
	}
	strncpy_s(m->name, MEMBER_NAME_SIZE + 1, buf, _TRUNCATE);
	
	/* 住所を入力する */
	buf[0] = '\0';
	while(strlen(buf) == 0) {
	    printf("%-6s＞　", MEMBER_ADDR_NAME);
		GetStr(buf, MEMBER_ADDR_SIZE);
	}
	strncpy_s(m->addr, MEMBER_ADDR_SIZE + 1, buf, _TRUNCATE);
	
	/* 電話番号を入力する */
	buf[0] = '\0';
	while(strlen(buf) == 0) {
	    printf("%-6s＞　", MEMBER_TEL_NAME);
		GetStr(buf, MEMBER_TEL_SIZE);
	}
	strncpy_s(m->tel, MEMBER_TEL_SIZE + 1, buf, _TRUNCATE);

	/* 生年月日を入力する */
	printf("%-6s\n", MEMBER_BIRTH_NAME);
	InputYMD(buf);
	strncpy_s(m->birth, MEMBER_BIRTH_SIZE + 1, buf, _TRUNCATE);

	/* 会員IDを新規設定する */
	if(GetMemberID(id) == FALSE) {					/* IDの最大値を超えた場合 */
		printf("会員IDの取得に失敗しました。\n");
		retVal = FALSE;
	} else {										/* IDを取得できた場合 */
		strncpy_s(m->id, MEMBER_ID_SIZE + 1, id, _TRUNCATE);
		retVal = TRUE;
	}
	return retVal;
}

/*
 * 関数名			: static int GetMemberID(char *id)
 * 機能				: 【D-1122】新規の会員IDを取得する
 * 入力パラメータ	: なし
 * 出力パラメータ	: char *id	:新規に取得した会員ID
 * 戻り値			: int	:TRUE（新規会員IDを取得）/FALSE（新規会員IDを取得できない）
 * 特記事項			: "99"+日付＋2桁の数字　計12桁
 */
static int GetMemberID(char *id)
{
	int retVal = FALSE;
	MEMBER* target;							/* ターゲットノード用 */
	char w[GETMEMBERID_STR_BUF_SIZE];		/* 文字列操作用 */
	char today[GETMEMBERID_DATE_BUF_SIZE];	/* 本日の日付 */
	int newID;								/* 新規ID（下位10桁の数字） */
	int listID;								/* 商品情報リスト内のID（下位10桁の数字） */

	/* 10桁の会員IDを作成する */
	GetToday(0, 0, 0, today);					/* 今日の日付を取得 */
	sprintf_s(w, GETMEMBERID_STR_BUF_SIZE, "%08s%02d", today, 1);	/* 日付+"01"のIDを作成 */
	newID = atoi(w);

	/* 商品情報リストを検索し、新しいIDを取得する */
	target = root;
	if(target != NULL) {
		/* リストが終了するまで繰り返す */
		while(target->next != NULL) {
			target = target->next;

			/* リストの商品IDの下位10ケタを取得する */
			strncpy_s(w, GETMEMBERID_STR_BUF_SIZE, target->id + 2, 10);
			listID = atoi(w);

			/* IDを比較する */
			if(newID == listID) {
				newID = listID + 1;
			} else if(newID > listID) {
				/* DO NOTHING */
			} else {
				break;
			}
		}

		/* IDの最大値をチェックする */
		if((newID % 100) == 0) {				/* 99を超えた */
			retVal = FALSE;
		} else {
			sprintf_s(id, MEMBER_ID_SIZE + 1, "99%010d", newID);	/* '99'を付加して文字列に変換 */
			retVal = TRUE;
		}
	} else {
		retVal = FALSE;
	}
	return retVal;
}

/*
 * 関数名			: void DisplayRegistMember(const MEMBER *m)
 * 機能				: 【D-1123】登録する会員情報を表示する
 * 入力パラメータ	: const MEMBER *m	:会員情報へのポインタ
 * 出力パラメータ	: なし
 * 戻り値			: なし
 * 特記事項			: なし
 */
void DisplayRegistMember(const MEMBER *m)
{
	char date[DISPLAYREGISTMEMBER_BUF_SIZE];					/* 日付フォーマット用 */

	printf("\n*****新規会員情報確認*****\n");
	printf("%-10s:%s\n", MEMBER_ID_NAME, m->id);
	printf("%-10s:%s\n", MEMBER_NAME_NAME, m->name);
	printf("%-10s:%s\n", MEMBER_ADDR_NAME, m->addr);
	printf("%-10s:%s\n", MEMBER_TEL_NAME, m->tel);
	ConvFormatDate(date, m->birth);
	printf("%-10s:%s\n", MEMBER_BIRTH_NAME, date);
}

/*
 * 関数名			: int RegistMember(MEMBER *m)
 * 機能				: 【D-1123】会員情報を会員情報リストに登録する
 * 入力パラメータ	: MEMBER *m	:会員情報へのポインタ
 * 出力パラメータ	: なし
 * 戻り値			: int	:TRUE（会員情報をリストに登録）常にTRUEを返す
 * 特記事項			: なし
 */
int RegistMember(const MEMBER *m)
{
	int retVal = FALSE;
	MEMBER *newone;				/* 会員情報の追加ノード参照用 */
	MEMBER *target;				/* ターゲットノード用 */
	
	/* 新たなノードを追加しデータを格納 */
	if((newone = (MEMBER*)malloc(sizeof(MEMBER))) == NULL) {		/* ノードを作成 */
		printf("動的メモリの取得に失敗しました。\n");
		exit(EXIT_FAILURE);
	}
	
	strncpy_s(newone->id, MEMBER_ID_SIZE+1, m->id, _TRUNCATE);
	strncpy_s(newone->name, MEMBER_NAME_SIZE+1, m->name, _TRUNCATE);
	strncpy_s(newone->addr, MEMBER_ADDR_SIZE+1, m->addr, _TRUNCATE);
	strncpy_s(newone->tel, MEMBER_TEL_SIZE+1, m->tel, _TRUNCATE);
	strncpy_s(newone->birth, MEMBER_BIRTH_SIZE+1, m->birth, _TRUNCATE);
	
	/* IDで昇順になるようにノードを追加する */
	target = root;												/* ターゲットを先頭に設定 */
	while(TRUE) {
		/* 次のノードがあるならば、IDをチェックする */
		if(target->next != NULL) {
			/* 追加ノードのIDが小さいならば、ターゲットの後ろにノードを追加して終了する */
			if(strncmp(newone->id, target->next->id, MEMBER_ID_SIZE) < 0) {
				newone->next = target->next;
				target->next = newone;
				break;
			} else {
				target = target->next;							/* ターゲットを更新して次のノードへ */
			}
		} else {
			/* 新しいノードをリストの末尾に追加して終了する */
			newone->next = NULL;
			target->next = newone;
			break;
		}
	}
	return TRUE;
}

/*
 * 関数名			: void DisplayMember(const MEMBER *m)
 * 機能				: 【D-1124】会員情報を表示する
 * 入力パラメータ	: MEMBER *m	:会員情報へのポインタ
 * 出力パラメータ	: なし
 * 戻り値			: なし
 * 特記事項			: なし
 */
void DisplayMember(const MEMBER *m)
{
	char date[DISPLAYMEMBER_BUF_SIZE];					/* 日付フォーマット用 */

	printf("\n*****会員情報確認*****\n");
	printf("%-11s:%s\n", MEMBER_ID_NAME, m->id);
	printf("%-11s:%s\n", MEMBER_NAME_NAME, m->name);
	printf("%-11s:%s\n", MEMBER_ADDR_NAME, m->addr);
	printf("%-11s:%s\n", MEMBER_TEL_NAME, m->tel);
	ConvFormatDate(date, m->birth);
	printf("%-11s:%s\n", MEMBER_BIRTH_NAME, date);
}

/*
 * 関数名			: int DisplayMemberList(const int key, const int ud, const int menuNum)
 * 機能				: 【D-1130】会員の一覧を表示する
 * 入力パラメータ	: const int key	:ソートキー
 * 					: const int ud	:昇順/降順（1:昇順/2:降順）
 * 					: const int num	:画面からの選択番号（ENTER_NUM:初回、以外:2回目以降）
 * 出力パラメータ	: なし
 * 戻り値			: int	:TRUE(まだ表示あり) / FALSE(最後まで表示)
 * 特記事項			: なし
 */
int DisplayMemberList(const int key, const int ud, const int menuNum)
{
	int retVal;
	static MEMBER* target;	/* ターゲットノード用 */
	static int dspNo = 1;	/* 表示の項番 */

	char h[DISPLAYMEMBERLIST_HEAD_COL_NUM][DISPLAYMEMBERLIST_HEAD_COL_BUF_SIZE];	/* ヘッダー項目 */
	char head[DISPLAYMEMBERLIST_HEAD_BUF_SIZE];	/* ヘッダー */
	char f[DISPLAYMEMBERLIST_HEAD_FORMAT_COL_NUM][DISPLAYMEMBERLIST_HEAD_FORMAT_COL_BUF_SIZE];	/* printfのフォーマット用 */
	char date[DISPLAYMEMBERLIST_DATE_BUF_SIZE];	/* 日付フォーマット用 */
	int fig;									/* 項番の桁数 */
	int cnt;									/* 表示カウンタ */
	char buf[DISPLAYMEMBERLIST_DSP_BUF_SIZE];	/* 表示文字列の長さ調整用 */

	/* 最初の入力の場合はリストを先頭に戻し、指定キーで昇順/降順にソートする */
	if(menuNum == ENTER_NUM) {
		target = root;
		dspNo = 1;
		SortMemberList(key, ud);
	}

	/* ヘッダーを表示する */
	fig = GetFigure(MEMBER_REG_MAX);			/* 項番の桁数を取得 */
	printf("\n*****会員情報一覧*****\n");
	strncpy_s(h[MEMBER_DSP_ROWNO_COL], DISPLAYMEMBERLIST_HEAD_COL_BUF_SIZE, MEMBER_DSP_ROWNO_NAME, _TRUNCATE);

	/* （ここ以下は文字列の長さが変更される可能性があるため、strncpyを使っていない） */
	strcpy_s(h[MEMBER_DSP_ID_COL], DISPLAYMEMBERLIST_HEAD_COL_BUF_SIZE, MEMBER_DSP_ID_NAME);
	strcpy_s(h[MEMBER_DSP_NAME_COL], DISPLAYMEMBERLIST_HEAD_COL_BUF_SIZE, MEMBER_DSP_NAME_NAME);
	strcpy_s(h[MEMBER_DSP_ADDR_COL], DISPLAYMEMBERLIST_HEAD_COL_BUF_SIZE, MEMBER_DSP_ADDR_NAME);
	strcpy_s(h[MEMBER_DSP_TEL_COL], DISPLAYMEMBERLIST_HEAD_COL_BUF_SIZE, MEMBER_DSP_TEL_NAME);
	strcpy_s(h[MEMBER_DSP_BIRTH_COL], DISPLAYMEMBERLIST_HEAD_COL_BUF_SIZE, MEMBER_DSP_BIRTH_NAME);
	sprintf_s(head, DISPLAYMEMBERLIST_HEAD_BUF_SIZE, "%%-%ds %%-%ds %%-%ds %%-%ds %%-%ds %%-%ds\n",
		fig,
		MEMBER_DSP_ID_NUM,
		MEMBER_DSP_NAME_NUM,
		MEMBER_DSP_ADDR_NUM,
		MEMBER_DSP_TEL_NUM,
		MEMBER_DSP_BIRTH_NUM
	);
	printf(head,
		h[MEMBER_DSP_ROWNO_COL],
		h[MEMBER_DSP_ID_COL],
		h[MEMBER_DSP_NAME_COL],
		h[MEMBER_DSP_ADDR_COL],
		h[MEMBER_DSP_TEL_COL],
		h[MEMBER_DSP_BIRTH_COL]
	);

	/* printfのフォーマットを設定する */
	sprintf_s(f[MEMBER_DSP_ROWNO_COL], DISPLAYMEMBERLIST_HEAD_FORMAT_COL_NUM, "%%0%dd ", fig);
	sprintf_s(f[MEMBER_DSP_ID_COL], DISPLAYMEMBERLIST_HEAD_FORMAT_COL_NUM, "%%-%ds ", MEMBER_DSP_ID_NUM);
	sprintf_s(f[MEMBER_DSP_NAME_COL], DISPLAYMEMBERLIST_HEAD_FORMAT_COL_NUM, "%%-%ds ", MEMBER_DSP_NAME_NUM);
	sprintf_s(f[MEMBER_DSP_ADDR_COL], DISPLAYMEMBERLIST_HEAD_FORMAT_COL_NUM, "%%-%ds ", MEMBER_DSP_ADDR_NUM);
	sprintf_s(f[MEMBER_DSP_TEL_COL], DISPLAYMEMBERLIST_HEAD_FORMAT_COL_NUM, "%%-%ds ", MEMBER_DSP_TEL_NUM);
	sprintf_s(f[MEMBER_DSP_BIRTH_COL], DISPLAYMEMBERLIST_HEAD_FORMAT_COL_NUM, "%%-%ds ", MEMBER_DSP_BIRTH_NUM);

	/* 商品リストを表示する */
	cnt = 0;
	while(target->next != NULL) {
		/* リストの内容を表示する */
		target = target->next;
		printf(f[MEMBER_DSP_ROWNO_COL], dspNo++);
		printf(f[MEMBER_DSP_ID_COL], target->id);
		strncpy_s(buf, MEMBER_DSP_NAME_NUM + 1, target->name, _TRUNCATE);
		printf(f[MEMBER_DSP_NAME_COL], buf);
		strncpy_s(buf, MEMBER_DSP_ADDR_NUM + 1, target->addr, _TRUNCATE);
		printf(f[MEMBER_DSP_ADDR_COL], buf);
		printf(f[MEMBER_DSP_TEL_COL], target->tel);
		ConvFormatDate(date, target->birth);
		printf(f[MEMBER_DSP_BIRTH_COL], date);
		printf("\n");
		/* 表示ページを制御する */
		cnt++;
		if(cnt == MEMBER_MON_DSP_NUM) {
			break;
		}
	}

	if(target->next == NULL) {
		printf("\n最後まで表示しました。\n");
		retVal = FALSE;
	} else {
		retVal = TRUE;
	}
	return retVal;
}

/*
 * 関数名			: static void SortMemberList(const int key, const int ud)
 * 機能				: 【D-1129】商品情報リストを指定キーで昇順/降順にソートする
 * 入力パラメータ	: const int key	:ソートキー
 * 					: const int ud	:昇順/降順（1:昇順/2:降順）
 * 出力パラメータ	: なし
 * 戻り値			: なし
 * 特記事項			: なし
 */
static void SortMemberList(const int key, const int ud)
{
	MEMBER *sort;		/* ソート後の先頭ノード */
	MEMBER *sTarget;	/* ソート用ターゲットノード */
	MEMBER *rTarget;	/* ルート用ターゲットノード */
	MEMBER *newone;		/* 会員情報の追加ノード参照用 */
	MEMBER *temp;		/* メモリ解放用 */
	int cmp;			/* strncmpの戻り値用 */
	
	/* ソートリスト用のダミーノードを作成する */
	if((sort = (MEMBER*)malloc(sizeof(MEMBER))) == NULL) {			/* ノードを作成 */
		printf("動的メモリの取得に失敗しました。\n");
		exit(EXIT_FAILURE);
	}
	sort->next = NULL;
	
	/* ターゲットをルートの先頭に設定する */
	rTarget = root;
	
	/* ソートリストを作成する */
	while(rTarget->next != NULL) {
		/* ルート側のノードをソート側に複写する */
		rTarget = rTarget->next;
		if((newone = (MEMBER*)malloc(sizeof(MEMBER))) == NULL) {		/* ノードを作成 */
			printf("動的メモリの取得に失敗しました。\n");
			exit(EXIT_FAILURE);
		}
		strncpy_s(newone->id, MEMBER_ID_SIZE + 1, rTarget->id, _TRUNCATE);
		strncpy_s(newone->name, MEMBER_NAME_SIZE + 1, rTarget->name, _TRUNCATE);
		strncpy_s(newone->addr, MEMBER_ADDR_SIZE + 1, rTarget->addr, _TRUNCATE);
		strncpy_s(newone->tel, MEMBER_TEL_SIZE + 1, rTarget->tel, _TRUNCATE);
		strncpy_s(newone->birth, MEMBER_BIRTH_SIZE + 1, rTarget->birth, _TRUNCATE);
		
		/* ノードをソートリストに挿入する */
		sTarget = sort;
		while(TRUE) {
			/* 次のノードがあるならば、ソートキーをチェックする */
			if(sTarget->next != NULL) {
				/* ソートキーを選択する */
				switch(key) {
				case 1:				/* 1:会員ID */
					cmp = strncmp(newone->id, sTarget->next->id, MEMBER_ID_SIZE);
					break;
				case 2:				/* 2:生年月日 */
					cmp = strncmp(newone->birth, sTarget->next->birth, MEMBER_BIRTH_SIZE);
					break;
				default:			/* 例外 */
					cmp = 0;
					break;
				}
				
				/* 追加ノードのソートキーの昇順、降順の判定*/
				if(ud == 1) {	/* 昇順にソート 追加ノードのソートキーの比較結果が小さいならば、ターゲットの後ろにノードを追加 */
					if(cmp < 0) {
						newone->next = sTarget->next;
						sTarget->next = newone;
						break;
					} else {
						sTarget = sTarget->next;
					}
				} else {		/* 降順にソート 追加ノードのソートキーの比較結果が大きいならば、ターゲットの後ろにノードを追加*/
					if(cmp > 0) {
						newone->next = sTarget->next;
						sTarget->next = newone;
						break;
					} else {
						sTarget = sTarget->next;
					}
				}
			} else {
				/* 新しいノードをリストの末尾に追加して終了する */
				newone->next = NULL;
				sTarget->next = newone;
				break;
			}
		}
	}
	
	/* ソートリストとルートリストのルートを入れ替える */
	temp = root->next;
	root->next = sort->next;
	sort->next = temp;
	
	/* ソートリストを解放する */
	while(sort != NULL) {
		temp = sort;
		sort = sort->next;
		free(temp);
	}
}

/*
 * 関数名			: int InputUpdateMember(MEMBER *m, MEMBER *mBuf)
 * 機能				: 【D-1125】会員情報変更入力画面
 * 入力パラメータ	: MEMBER *m	:変更する会員情報ノードへのポインタ
 * 出力パラメータ	: MEMBER *mBuf	:変更した会員情報ノードへのポインタ
 * 戻り値			: int	:TRUE（会員情報を取得）/FALSE（会員情報がない）
 * 特記事項			: 既存の会員情報を参考に新たな会員情報を入力する
 */
int InputUpdateMember(MEMBER *m, MEMBER *mBuf)
{
	int retVal = TRUE;
	char buf[MEMBER_NAME_SIZE + STRING_TERMINATOR_SIZE];	/* 文字列用バッファ */
	char date[INPUTUPDATEMEMBER_DATE_BUF_SIZE];			/* 日付フォーマット用 */

	if(m != NULL) {
		printf("\n");
		printf("変更項目を入力してください。\n");
		printf("未入力項目は変更しません。\n");
		printf("%s:%s\n", MEMBER_ID_NAME, m->id);

		/* 会員IDをコピーする */
		strncpy_s(mBuf->id, MEMBER_ID_SIZE + 1, m->id, _TRUNCATE);

		/* 氏名を更新する */
		printf("%s:%s　＞　", MEMBER_NAME_NAME, m->name);
		GetStr(buf, MEMBER_NAME_SIZE);
		if(strlen(buf) != 0) {
			strncpy_s(mBuf->name, MEMBER_NAME_SIZE + 1, buf, _TRUNCATE);
		} else {
			strncpy_s(mBuf->name, MEMBER_NAME_SIZE + 1, m->name, _TRUNCATE);
		}

		/* 住所を更新する */
		printf("%s:%s　＞　", MEMBER_ADDR_NAME, m->addr);
		GetStr(buf, MEMBER_ADDR_SIZE);
		if(strlen(buf) != 0) {
			strncpy_s(mBuf->addr, MEMBER_ADDR_SIZE + 1, buf, _TRUNCATE);
		} else {
			strncpy_s(mBuf->addr, MEMBER_ADDR_SIZE + 1, m->addr, _TRUNCATE);
		}

		/* 電話番号を更新する */
		printf("%s:%s　＞　", MEMBER_TEL_NAME, m->tel);
		GetStr(buf, MEMBER_TEL_SIZE);
		if(strlen(buf) != 0) {
			strncpy_s(mBuf->tel, MEMBER_TEL_SIZE + 1, buf, _TRUNCATE);
		} else {
			strncpy_s(mBuf->tel, MEMBER_TEL_SIZE + 1, m->tel, _TRUNCATE);
		}


		/* 生年月日を更新する */
		ConvFormatDate(date, m->birth);
		printf("%s（'/'を除く8桁）:%s　＞　", MEMBER_BIRTH_NAME, date);
		GetDateStr(buf);
		if(strlen(buf) != 0) {
			strncpy_s(mBuf->birth, MEMBER_BIRTH_SIZE + 1, buf, _TRUNCATE);
		} else {
			strncpy_s(mBuf->birth, MEMBER_BIRTH_SIZE + 1, m->birth, _TRUNCATE);
		}

	} else {
		retVal = FALSE;
	}
	return retVal;

}

/*
 * 関数名			: int DeleteMember(const char *id)
 * 機能				: 【D-1127】会員情報削除確認画面
 * 入力パラメータ	: const char *id	:会員ID
 * 出力パラメータ	: なし
 * 戻り値			: int	:1（削除）/EXIT_NUM（削除しない）
 * 特記事項			: なし
 */
int DeleteMember(const char *id)
{
	int retVal = EXIT_NUM;
	MEMBER *target;					/* ターゲットノード用 */
	MEMBER *del;
	
	/* リストからターゲットノードを削除する */
	target = root;
	while(target->next != NULL) {
		if(strncmp(target->next->id, id, MEMBER_ID_SIZE) == 0) {
			del = target->next;
			target->next = target->next->next;
			free(del);
			break;
		}
		target = target->next;
	}
		WriteMemberFile();						/* 会員情報リストのファイル書込み */
		printf("\n会員情報を削除しました。\n");
		retVal = 1;
	return retVal;
}
/*
 * 関数名			: int Searchtel(const char* tel, MEMBER** m)
 * 機能				: 【D-1131】電話番号で会員IDを検索する
 * 入力パラメータ	: const char *tel	:検索する電話番号
 * 出力パラメータ	: MEMBER **m	:検索された会員情報ノードへのポインタ
 * 戻り値			: int	;TRUE (会員情報取得成功) / FALSE (会員情報取得失敗)	
 * 特記事項			: なし
 */
int Searchtel(const char *tel, MEMBER** m)
{
	int retVal = FALSE;
	MEMBER* target;		/* 検索ターゲットノード用 */

	target = root;
	while (target->next != NULL) {
		target = target->next;
		if (strncmp(target->tel, tel, MEMBER_TEL_SIZE) == 0) {
			*m = target;	/* ヒットしたデータのアドレスを戻り値に設定 */
			retVal = TRUE;
			break;
		}
	}
	return retVal;
}