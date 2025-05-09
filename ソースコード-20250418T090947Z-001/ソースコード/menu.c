/*
 * ファイル名	: menu.c
 * 機能			: メニュー表示を行う
 * 特記事項		: なし
 * 修正履歴		:  1  2012/01/10 V01L1 初版
 *				:  2  2012/02/14 V02L1
 */

/* ヘッダーの取り込み */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "common.h"
#include "menu.h"
#include "member.h"
#include "goods.h"
#include "lend.h"
#include "ret.h"

/* 変数宣言 */
/* 【D-1100】スタッフメインメニュー */
MENU mainMenu = {
	"\n*****スタッフメインメニュー*****",
	1, "レンタルメニュー",
	2, "会員情報管理メニュー",
	3, "商品情報管理メニュー",
	0, "終了"
};

/* 【D-1110】レンタルメニュー */
MENU rentalMenu = {
	"\n*****レンタルメニュー*****",
	1, "貸出",
	2, "返却",
	0, "スタッフメインメニューに戻る"
};

/* 【D-1111】商品ID入力画面（レンタル） */
TITLE goodsIDGetRMenu = {
	"商品ID（13桁）を入力してください。（終了:1 / 戻る:0）＞　"
};

/* 【D-1111】商品ID入力画面（商品情報マスタファイル） */
TITLE goodsIDGetSMenu = {
	"商品ID（13桁）を入力してください。（戻る:0）＞　"
};

/* 【D-1112】商品情報確認画面（貸出） */
MENU rentalRentSMenu = {
	"",
	1, "貸出リストに登録",
	2, "再入力",
	0, "レンタルメニューに戻る"
};

/* 【D-1112】商品情報確認画面（返却） */
MENU rentalRetSMenu = {
	"",
	1, "返却リストに登録",
	2, "再入力",
	0, "レンタルメニューに戻る"
};

/* 【D-1120】会員情報管理メニュー */
MENU memberManageMenu = {
	"\n*****会員情報管理メニュー*****",
	1, "登録",
	2, "一覧表示",
	3, "確認/変更/削除",
	0, "スタッフメインメニューに戻る"
};

/* 【D-1121】会員ID入力画面（商品情報マスタファイル） */
TITLE memberIDGetSMenu = {
	"会員ID（12桁）を入力してください。（IDを忘れた:1 / 戻る:0）＞　"
};

/* 【D-1122】新規会員情報入力画面 */
MENU memberRegistInputSMenu = {
	"\n*****新規会員情報入力*****",
	1, "情報入力",
	0, "会員情報管理メニューに戻る"
};

/* 【D-1123】新規会員情報確認画面 */
MENU memberRegistCheckSMenu = {
	"",
	1, "登録",
	2, "変更",
	0, "会員情報管理メニューに戻る"
};

/* 【D-1124】会員情報確認画面 */
MENU memberUpdateSMenu = {
	"",
	1, "変更",
	2, "削除",
	0, "会員情報管理メニューに戻る"
};

/* 【D-1125】会員情報変更入力画面 */
MENU memberUpdateInputSMenu = {
	"\n*****会員情報変更入力*****",
	1, "情報変更",
	0, "会員情報管理メニューに戻る"
};

/* 【D-1126】会員情報変更確認画面 */
MENU memberUpdateCheckSMenu = {
	"",
	1, "登録",
	2, "変更",
	0, "会員情報変更入力画面に戻る"
};

/* 【D-1127】会員情報削除確認画面 */
TITLE memberDeleatCheckSMenu = {
	"\n本当に削除してよろしいですか？"
};

/* 【D-1128】会員一覧整列項目選択画面 */
MENU memberSortKeySMenu = {
	"\n*****会員一覧整列項目選択*****\n"
	"どの項目で並び替えて表示しますか？",
	1, "会員ID",
	2, "生年月日",
	0, "会員情報管理メニューに戻る"
};

/* 【D-1129】会員一覧表示順選択画面 */
MENU memberSortUdSMenu = {
	"\n*****会員一覧表示順選択*****",
	1, "昇順",
	2, "降順",
	0, "会員情報管理メニューに戻る"
};

/* 【D-1130】会員一覧表示画面 */
MENU memberListCheckSMenu = {
	"",
	1, "次ページを表示",
	2, "会員情報を変更する",
	0, "会員情報管理メニューに戻る"
};

/*【D-1131】会員ID検索画面*/
TITLE memberIDSurchMenu = {
	"電話番号(半角ハイフンあり)を入力してください。（戻る:0）＞"
};

/* 【D-1140】商品情報管理メニュー */
MENU goodsManageMenu = {
	"\n*****商品情報管理メニュー*****",
	1, "登録",
	2, "確認/変更/削除",
	3, "一覧表示",
	0, "スタッフメインメニューに戻る"
};

/* 【D-1141】新規商品情報入力画面 */
MENU goodsRegistInputSMenu = {
	"\n*****新規商品情報入力*****",
	1, "情報入力",
	0, "商品情報管理メニューに戻る"
};

/* 【D-1142】新規商品情報確認画面 */
MENU goodsRegistCheckSMenu = {
	"",
	1, "登録",
	0, "商品情報管理メニューに戻る"
};

/* 【D-1143】商品情報確認画面 */
MENU goodsUpdateSMenu = {
	"",
	1, "変更",
	2, "削除",
	0, "商品情報管理メニューに戻る"
};

/* 【D-1144】商品情報変更入力画面 */
MENU goodsUpdateInputSMenu = {
	"\n*****商品情報変更入力*****",
	1, "情報変更",
	0, "商品情報管理メニューに戻る"
};

/* 【D-1145】商品情報変更確認画面 */
MENU goodsUpdateCheckSMenu = {
	"",
	1, "変更",
	0, "商品情報変更入力画面に戻る"
};

/* 【D-1147】商品一覧整列項目選択画面 */
MENU goodsSortKeySMenu = {
	"\n*****商品一覧整列項目選択*****\n"
	"どの項目で並び替えて表示しますか？",
	1, "商品ID",
	2, "保管場所",
	3, "発売日",
	4, "貸出回数",
	0, "商品情報管理メニューに戻る"
};

/* 【D-1148】商品一覧表示順選択画面 */
MENU goodsSortUdSMenu = {
	"\n*****商品一覧表示順選択*****",
	1, "昇順",
	2, "降順",
	0, "商品情報管理メニューに戻る"
};

/* 【D-1149】商品一覧表示画面 */
MENU goodsListCheckSMenu = {
	"",
	1, "次ページを表示",
	0, "商品情報管理メニューに戻る"
};

/* static関数宣言 */
static int RentalMenu(void);
static int GoodsIDGetRMenu(const int size, char *id, GOODS **g);
static int RentalLendSMenu(void);
static int RentalRetSMenu(void);
static int MemberManageMenu(void);
static int MemberRegistInputSMenu(void);
static int MemberRegistCheckSMenu(const MEMBER *m);
static int MemberIDGetSMenu(const int size, char *id, MEMBER **m);
static int MemberUpdateSMenu(void);
static int MemberUpdateInputSMenu(MEMBER *m);
static int MemberUpdateCheckSMenu(MEMBER *m, MEMBER *mBuf);
static int MemberDeleatCheckSMenu(void);
static int MemberSortKeySMenu(void);
static int MemberSortUdSMenu(const int key);
static int MemberListCheckSMenu(const int key, const int ud);
static int MemberIDSerchMenu(const int size, char *tel, MEMBER **m);
static int GoodsManageMenu(void);
static int GoodsRegistInputSMenu(void);
static int GoodsRegistCheckSMenu(const GOODS *goods);
static int GoodsIDGetSMenu(const int size, char *id, GOODS **g);
static int GoodsUpdateSMenu(void);
static int GoodsUpdateInputSMenu(GOODS *goods);
static int GoodsUpdateCheckSMenu(GOODS *goods, GOODS *gBuf);
static int GoodsSortKeySMenu(void);
static int GoodsSortUdSMenu(const int key);
static int GoodsListCheckSMenu(const int key, const int ud);

/*
 * 関数名			: int MainMenu(void)
 * 機能				: 【D-1100】スタッフメインメニュー
 * 入力パラメータ	: なし
 * 出力パラメータ	: なし
 * 戻り値			: int	:選択番号(必ずEXIT_NUMを返す)
 * 特記事項			: なし
 */
int MainMenu(void)
{
	int retVal = ENTER_NUM;		/* 戻り値 */
	int num = ENTER_NUM;			/* 入力番号 */
	
	while(num != EXIT_NUM) {
		num = GetMenuNum(&mainMenu);
		retVal = num;
		switch(num) {
		case 1:	
			RentalMenu();					/* 【D-1110】レンタルメニュー */
			break;
		case 2:
			MemberManageMenu();				/* 【D-1120】会員情報管理メニュー */
			break;
		case 3:
			GoodsManageMenu();				/* 【D-1140】商品情報管理メニュー */
			break;
		case EXIT_NUM:
			if(ExitProgram() == FALSE) {		/* プログラム終了確認 */
				num = ENTER_NUM;
			}
			break;
		default:								/* NOT REACHED */
			break;
		}
	}
	return retVal;
}

/*
 * 関数名			: int ExitProgram(void)
 * 機能				: プログラムの終了確認
 * 入力パラメータ	: なし
 * 出力パラメータ	: なし
 * 戻り値			: int	:終了する:TRUE / 終了しない:FALSE
 * 特記事項			: なし
 */
int ExitProgram(void)
{
	int retVal = FALSE;		/* 戻り値 */
	
	retVal = GetYesNo("プログラムを終了してもよろしいですか?");
	return retVal;
}

/*
 * 関数名			: static int RentalMenu(void)
 * 機能				: 【D-1110】レンタルメニュー
 * 入力パラメータ	: なし
 * 出力パラメータ	: なし
 * 戻り値			: int	:選択番号
 * 特記事項			: なし
 */
static int RentalMenu(void)
{
	int retVal = ENTER_NUM;		/* 戻り値 */
	int num = ENTER_NUM;			/* 入力番号 */
	
	while(num != EXIT_NUM) {
		num = GetMenuNum(&rentalMenu);
		retVal = num;
		switch(num) {
		case 1:
			RentalLendSMenu();	/* 【D-1112】商品情報確認画面（貸出） */
			break;
		case 2:
			RentalRetSMenu();	/* 【D-1112】商品情報確認画面（返却） */
			break;
		case EXIT_NUM:			/* スタッフメインメニューへ */
			break;
		default:					/* NOT REACHED */
			break;
		}
	}
	return retVal;
}

/*
 * 関数名			: static int GoodsIDGetRMenu(const int size, char *id, GOODS **g)
 * 機能				: 【D-1111】商品ID入力画面（レンタル）
 * 入力パラメータ	: const int size	:桁数
 * 出力パラメータ	: char *id	:商品ID
 *					: GOODS **g	:商品情報ノードへのポインタへのアドレス
 * 戻り値			: int	:選択番号（'1'を入力:REGIST_NUM / '0'またはNULLを入力:EXIT_NUM / それ以外を入力:ENTER_NUM）
 * 特記事項			: 無効なIDを入力した場合には再入力を促す
 */
static int GoodsIDGetRMenu(const int size, char *id, GOODS **g)
{
	int retVal = ENTER_NUM;		/* 戻り値 */
	GOODS *search;
	
	while(TRUE) {
		DisplayTitle(&goodsIDGetRMenu);						/* タイトルを表示 */
		GetNumStr(id, size);									/* IDを文字列として取得 */
		if((id[0] == '1') && (id[1] == '\0')) {				/* ID入力が "1"の場合 */
			retVal = REGIST_NUM;								/* 連続貸出/返却処理の終了 */
			break;
		} else if((id[0] == '0') && (id[1] == '\0')) {		/* ID入力が"0"の場合 */
			retVal = EXIT_NUM;								/* 前に戻る */
			break;
		} else if(id[0] == '\0') {							/* ID入力がNULLの場合 */
			retVal = EXIT_NUM;
			break;
		} else {												/* ID入力がある場合 */
			/* 商品情報リストを検索する */
			if(SearchGoods(id, &search) == FALSE) {
				printf("該当する商品IDがありません。\n");
			} else {
				*g = search;
				break;
			}
		}
	}
	return retVal;
}

/*
 * 関数名			: static int RentalLendSMenu(void)
 * 機能				: 【D-1112】商品情報確認画面（貸出）
 * 入力パラメータ	: なし
 * 出力パラメータ	: なし
 * 戻り値			: int	:ENTER_NUM
 * 特記事項			: なし
 */
static int RentalLendSMenu(void)
{
	int retVal = ENTER_NUM;								/* 戻り値 */
	int num = ENTER_NUM;									/* 入力番号 */
	char gID[GOODS_ID_SIZE+STRING_TERMINATOR_SIZE];		/* 商品ID */
	GOODS *goodslist = NULL;								/* 商品情報リストへのポインタ */
	GOODS *goods = NULL;									/* 商品情報ノードへのポインタ */
	MEMBER *member = NULL;								/* 会員情報ノードへのポインタ */
	LEND lendBuf;										/* 貸出情報 */
	char mID[MEMBER_ID_SIZE+STRING_TERMINATOR_SIZE];		/* 会員ID */
	
	/* 商品情報および会員情報をリスト構造に読み込む */
	ReadGoodsFile(&goodslist);
	ReadMemberFile(&member);
	
	/* 貸出情報リストを作成し、ダミーノードのアドレスを取得する */
	CreateLendList();
	
	/* 商品IDを入力して貸出処理を行う */
	ClearLendBuffer(&lendBuf);									/* 貸出情報バッファをクリア */
	while(num != EXIT_NUM) {
		/* 有効な商品IDが入力されたら貸出商品情報を表示する */
		switch(GoodsIDGetRMenu(GOODS_ID_SIZE, gID, &goods)) {	/* 【D-1111】商品ID入力画面 */
		case EXIT_NUM:											/* 戻る(0) */
			num = EXIT_NUM;
			break;
		case REGIST_NUM:											/* 入力終了(1) */
			if(strlen(lendBuf.id) != 0) {						/* 貸出登録が1回以上行われている ? */
				DisplayLendList();								/* 【D-1113】貸出商品リスト確認画面 */
				if(MemberIDGetSMenu(MEMBER_ID_SIZE, mID, &member) != EXIT_NUM) {	/* 【D-1121】会員ID入力画面 */
					UpdateGoodsLendSts(mID, goodslist);			/* 商品情報マスタファイルの貸出状況を更新 */
					printf("\n貸出処理を完了しました。\n");
				}
				num = EXIT_NUM;
			} else {
				printf("商品IDがまだ一度も入力されていません。\n");
			}
			break;
		default:													/* 有効な商品ID */
			/* 商品の貸出情報を表示する */
			if(DisplayLend(goods, &lendBuf)) {					/* lendBufに値が入る */
				num = GetMenuNum(&rentalRentSMenu);
			} else {
				num = 2;
			}
			switch(num) {
			case 1:												/* リスト登録 */
				RegistLend(&lendBuf);							/* 貸出リストにノードを登録 */
				break;
			case 2:												/* 再入力 */
				break;
			case EXIT_NUM:
				break;
			default:	/* NOT REACHED */
				break;
			}
			break;
		}
	}
	
	/* リストをメモリから解放する */
	FreeGoodsList();
	FreeMemberList();
	FreeLendList();
	
	return retVal;
}

/*
 * 関数名			: static int RentalRetSMenu(void)
 * 機能				: 【D-1112】商品情報確認画面（返却）
 * 入力パラメータ	: なし
 * 出力パラメータ	: なし
 * 戻り値			: int	:ENTER_NUM
 * 特記事項			: なし
 */
static int RentalRetSMenu(void)
{
	int retVal = ENTER_NUM;							/* 戻り値 */
	int num = ENTER_NUM;								/* 入力番号 */
	char gID[GOODS_ID_SIZE+STRING_TERMINATOR_SIZE];	/* 商品ID */
	GOODS *goodslist = NULL;							/* 商品情報リストへのポインタ */
	GOODS *goods = NULL;								/* 商品情報ノードへのポインタ */
	RET retBuf;										/* 返却情報 */
	
	/* 商品情報をリスト構造に読み込む */
	ReadGoodsFile(&goodslist);
	
	/* 返却情報リストを初期化 */
	CreateRetList();
	
	/* 商品IDを入力して返却処理を行う */
	ClearRetBuffer(&retBuf);									/* 返却情報バッファをクリア */
	while(num != EXIT_NUM) {
		/* 有効な商品IDが入力されたら返却商品情報を表示する */
		switch(GoodsIDGetRMenu(GOODS_ID_SIZE, gID, &goods)) {	/* 【D-1111】商品ID入力画面 */
		case EXIT_NUM:											/* 戻る(0) */
			num = EXIT_NUM;
			break;
		case REGIST_NUM:										/* 入力終了(1) */
			if(strlen(retBuf.id) != 0) {						/* 返却登録が1回以上行われている ? */
				DisplayRetList();							/* 【D-1114】返却商品リスト確認画面 */
				if(GetYesNo("返却しますか?") != FALSE) {		/* 返却確認  */
					UpdateGoodsRetSts(goodslist);			/* 商品情報マスタファイルの貸出状況を更新 */
					printf("\n返却処理を完了しました。\n");
				}
				num = EXIT_NUM;
			} else {
				printf("商品IDがまだ一度も入力されていません。\n");
			}
			break;
		default:											/* 有効な商品ID */
			/* 商品の貸出情報を表示する */
			if(DisplayRet(goods, &retBuf)) {
				num = GetMenuNum(&rentalRetSMenu);
			} else {
				num = 2;
			}
			switch(num) {
			case 1:										/* リスト登録 */
				RegistRet(&retBuf);						/* 返却リストにノード登録 */
				break;
			case 2:										/* 再入力 */
				break;
			case EXIT_NUM:
				break;
			default:										/* NOT REACHED */
				break;
			}
			break;
		}
	}
	
	/* リストをメモリから解放する */
	FreeGoodsList();
	FreeRetList();
	
	return retVal;
}

/*
 * 関数名			: static int MemberManageMenu(void)
 * 機能				: 【D-1120】会員情報管理メニュー
 * 入力パラメータ	: なし
 * 出力パラメータ	: なし
 * 戻り値			: int	:選択番号
 * 特記事項			: なし
 */
static int MemberManageMenu(void)
{
	int retVal = ENTER_NUM;		/* 戻り値 */
	int num = ENTER_NUM;			/* 入力番号 */
	MEMBER* member = NULL;		/* 会員情報ノードへのポインタ */

	ReadMemberFile(&member);		/* 会員情報マスタファイルの読込み */
	while(num != EXIT_NUM) {
		num = GetMenuNum(&memberManageMenu);
		retVal = num;
		switch (num) {
		case 1:
			retVal = MemberRegistInputSMenu();	/* 【D-1122】新規会員情報入力画面 */
			if(retVal == 1) {					/* 新規登録がキャンセルされずに完了した場合 */
				num = EXIT_NUM;
			}
			break;
		case 2:
			MemberSortKeySMenu();				/* 【D-1128】会員一覧整列項目選択画面 */
			break;
		case 3:
			retVal = MemberUpdateSMenu();		/* 【D-1124】会員情報確認画面 */
			if (retVal == 1) {					/* 変更もしくは削除がキャンセルされずに完了した場合 */
				num = EXIT_NUM;
			}
			break;
		case EXIT_NUM:
			break;
		default:									/* NOT REACHED */
			break;
		}
	}
	FreeMemberList();							/* 会員情報リストの解放 */
	return retVal;
}

/*
 * 関数名			: static int MemberRegistInputSMenu(void)
 * 機能				: 【D-1122】新規会員情報入力画面
 * 入力パラメータ	: なし
 * 出力パラメータ	: なし
 * 戻り値			: int	:選択番号（登録:1 / 戻る:EXIT_NUM）
 * 特記事項			: なし
 */
static int MemberRegistInputSMenu(void)
{
	int retVal = ENTER_NUM;		/* 戻り値 */
	int num = ENTER_NUM;			/* 入力番号 */
	MEMBER* member = NULL;		/* 会員情報ノードへのポインタ */
	MEMBER mBuf;					/* 変更後の会員情報を仮置きするメンバ */

	/* メニューを表示する */
	while(num != EXIT_NUM) {
		num = GetMenuNum(&memberRegistInputSMenu);
		retVal = num;
		switch (num) {
		case 1:											/* 情報入力 */
			ClearMemberBuffer(&mBuf);					/* バッファをクリア */
			if(InputRegistMember(&mBuf) != FALSE) {		/* 登録する会員情報を入力 */
				retVal = MemberRegistCheckSMenu(&mBuf);	/* 【D-1123】新規会員情報確認画面 */
				num = EXIT_NUM;
			}
			break;
		case EXIT_NUM:									/* 戻る */
			break;
		default:											/* NOT REACHED */
			break;
		}
	}
	return retVal;
}

/*
 * 関数名			: static int MemberRegistCheckSMenu(const MEMBER *m)
 * 機能				: 【D-1123】新規会員情報確認画面
 * 入力パラメータ	: const MEMBER *m:会員情報へのポインタ
 * 出力パラメータ	: なし
 * 戻り値			: int	:選択番号（登録:1 / 戻る:EXIT_NUM）
 * 特記事項			: なし
 */
static int MemberRegistCheckSMenu(const MEMBER *m)
{
	int retVal = ENTER_NUM;	/* 戻り値 */
	int num = ENTER_NUM;		/* 入力番号 */
	MEMBER mBuf;		/* 変更後の会員情報を仮置きするメンバ */
	MEMBER* nm;			/* 新しい会員情報（ファイルに書き込まれると情報はMEMBER *mに代入される） */

	DisplayRegistMember(m);		/* 登録する会員情報を表示 */
	nm = m;
	while(num != EXIT_NUM) {
		num = GetMenuNum(&memberRegistCheckSMenu);
		retVal = num;
		switch (num) {
		case 1:								/* 登録 */
			RegistMember(nm);					/* 会員情報をリストに登録 */
			WriteMemberFile();				/* 会員情報リストのファイル書込み */
			printf("\n会員情報を登録しました。\n");
			num = EXIT_NUM;
			break;
		case 2:								/* 一度登録してそのあと変更 */
			WriteMemberFile();				/* 会員情報リストのファイル書込み */
			ClearMemberBuffer(&mBuf);			/* バッファをクリア */
			if (InputUpdateMember(nm, &mBuf) != FALSE) {		/* 更新する会員情報を入力 */
				strncpy_s(nm->name, MEMBER_NAME_SIZE + 1, mBuf.name, _TRUNCATE);
				strncpy_s(nm->addr, MEMBER_ADDR_SIZE + 1, mBuf.addr, _TRUNCATE);
				strncpy_s(nm->tel, MEMBER_TEL_SIZE + 1, mBuf.tel, _TRUNCATE);
				strncpy_s(nm->birth, MEMBER_BIRTH_SIZE + 1, mBuf.birth, _TRUNCATE);
				DisplayRegistMember(nm);
				printf("\n会員情報を変更しました。\n");
			}
			break;
		case EXIT_NUM:						/* 戻る */
			break;
		default:								/* NOT REACHED */
			break;
		}
	}
	return retVal;
}

/*
 * 関数名			: static int MemberIDGetSMenu(const int size, char *id, MEMBER **m)
 * 機能				: 【D-1121】会員ID入力画面
 * 入力パラメータ	: const int size	:桁数
 * 出力パラメータ	: char *id	:会員ID MEMBER **m:会員情報ノードへのポインタへのアドレス
 * 戻り値			: int	:選択番号（'0'またはNULLを入力:EXIT_NUM / それ以外を入力:ENTER_NUM）
 * 特記事項			: 無効なIDを入力した場合には再入力を促す
 */
static int MemberIDGetSMenu(const int size, char *id, MEMBER **m)
{
	int retVal = ENTER_NUM;		/* 戻り値 */
	MEMBER *search;
	
	while(TRUE) {
		DisplayTitle(&memberIDGetSMenu);				/* タイトルを表示 */
		GetNumStr(id, size);							/* IDを文字列として取得 */
		if ((id[0] == '0') && (id[1] == '\0')) {		/* ID入力が'0'の場合 */
			retVal = EXIT_NUM;
			break;
		} else if((id[0] == '1') &&(id[1] == '\0')) {	/* ID入力が'1'の場合 */
			retVal = ADVANCE_NUM;
			break;
		} else if(id[0] == '\0') {					/* ID入力がNULLの場合 */
			retVal = EXIT_NUM;
			break;
		} else {										/* ID入力がある場合 */
			/* 会員情報リストを検索する */
			if(SearchMember(id, &search) == FALSE) {
				printf("該当する会員IDがありません。\n");
			} else {
				*m = search;
				break;
			}
		}
	}
	return retVal;
}

/*
 * 関数名			: static int MemberUpdateSMenu(void)
 * 機能				: 【D-1124】会員情報確認画面
 * 入力パラメータ	: なし
 * 出力パラメータ	: なし
 * 戻り値			: int	:選択番号（変更・削除:1 / 戻る・変更しない・削除しない:EXIT_NUM）
 * 特記事項			: なし
 */
static int MemberUpdateSMenu(void)
{
	int retVal = ENTER_NUM;								/* 戻り値 */
	int num = ENTER_NUM;									/* 入力番号 */
	char id[MEMBER_ID_SIZE + STRING_TERMINATOR_SIZE];	/* 会員ID */
	char tel[MEMBER_TEL_SIZE + STRING_TERMINATOR_SIZE];	/* 電話番号 */
	MEMBER* member = NULL;								/* 会員情報ノードへのポインタ */

	while (num != EXIT_NUM) {
		num = MemberIDGetSMenu(MEMBER_ID_SIZE, id, &member);	/* 【D-1121】会員ID入力画面 */
		retVal = num;
		if (num != EXIT_NUM) {		/* 有効な商品IDが入力されたら、会員情報とメニューを表示 */
			if (num == ADVANCE_NUM) {
				num = MemberIDSerchMenu(MEMBER_TEL_SIZE, tel, &member);	/* 【D-1131】会員ID検索画面 */
				if (num != EXIT_NUM) {					/* 正しい電話番号が入力された場合 */
					DisplayMember(member);				/* 会員情報を表示 */
					num = GetMenuNum(&memberUpdateSMenu);
					retVal = num;
					switch (num) {
					case 1:											/* 変更 */
						retVal = MemberUpdateInputSMenu(member);		/* 【D-1125】会員情報変更入力画面 */
						num = EXIT_NUM;					
						break;
					case 2:											/* 削除 */
						num = MemberDeleatCheckSMenu();
						if (num != FALSE) {
							retVal = DeleteMember(id);					/* 会員情報を削除 */
						}
						num = EXIT_NUM;
						break;
					case EXIT_NUM:									/* 戻る */
						break;
					default:											/* NOT REACHED */
						break;
					}
				} else {	/* 会員ID検索画面で'0'(戻る)が入力された場合 */
					/* 【D-1121】会員ID入力画面に戻る */
					num = ADVANCE_NUM;
				}
			} else {
				DisplayMember(member);	/* 会員情報を表示 */
				num = GetMenuNum(&memberUpdateSMenu);
				retVal = num;
				switch (num) {
				case 1:											/* 変更 */
					retVal = MemberUpdateInputSMenu(member);		/* 【D-1125】会員情報変更入力画面 */
					num = EXIT_NUM;					
					break;
				case 2:											/* 削除 */
					num = MemberDeleatCheckSMenu();					/* 【D-1127】会員情報削除確認画面 */
					if (num != FALSE) {
						retVal = DeleteMember(id);					/* 会員情報を削除 */
					}					
					num = EXIT_NUM;
					break;
				case EXIT_NUM:									/* 戻る */
					break;
				default:											/* NOT REACHED */
					break;
				}
			}
		}
	}
	return retVal;
}

/*
 * 関数名			: static int MemberUpdateInputSMenu(MEMBER* m)
 * 機能				: 【D-1125】会員情報変更入力画面
 * 入力パラメータ	: MEMBER *m	:会員情報へのポインタ
 * 出力パラメータ	: なし
 * 戻り値			: int	:選択番号（変更:1 / 戻る:EXIT_NUM）
 * 特記事項			: なし
 */
static int MemberUpdateInputSMenu(MEMBER* m)
{
	int retVal = ENTER_NUM;		/* 戻り値 */
	int num = ENTER_NUM;			/* 入力番号 */
	MEMBER mBuf;					/* 会員情報 */

	while(num != EXIT_NUM) {
		num = GetMenuNum(&memberUpdateInputSMenu);
		retVal = num;
		switch (num) {
		case 1:												/* 変更 */
			ClearMemberBuffer(&mBuf);						/* バッファをクリア */
			if(InputUpdateMember(m, &mBuf) != FALSE) {		/* 更新する会員情報を入力 */
				retVal = MemberUpdateCheckSMenu(m, &mBuf);	/* 【D-1126】会員情報変更確認画面 */
				if(retVal == 1) {
					num = EXIT_NUM;							/* 変更後はメニューを終了 */
					retVal = EXIT_NUM;
				}
			}
			break;
		case EXIT_NUM:										/* 戻る */
			break;
		default:												/* NOT REACHED */
			break;
		}
	}
	return retVal;
}

/*
 * 関数名			: static int MemberUpdateCheckSMenu(MEMBER *m, MEMBER *mBuf)
 * 機能				: 【D-1126】会員情報変更確認画面
 * 入力パラメータ	: MEMBER *m	:変更前の会員情報へのポインタ
 *					: MEMBER *mBuf	:変更後の会員情報へのポインタ
 * 出力パラメータ	: なし
 * 戻り値			: int	:選択番号（変更:1 / 戻る:EXIT_NUM）
 * 特記事項			: なし
 */
static int MemberUpdateCheckSMenu(MEMBER *m, MEMBER *mBuf)
{
	int retVal = ENTER_NUM;		/* 戻り値 */
	int num = ENTER_NUM;			/* 入力番号 */
	MEMBER nm;
	int count = 0;
	
	while(num != EXIT_NUM) {
			DisplayMember(mBuf);							/* 登録する会員情報を表示 */
		num = GetMenuNum(&memberUpdateCheckSMenu);
		retVal = num;
		switch (num) {
		case 1:									/* 登録 */
			if (count == 0) {
				strncpy_s(m->name, MEMBER_NAME_SIZE + 1, mBuf->name, _TRUNCATE);
				strncpy_s(m->addr, MEMBER_ADDR_SIZE + 1, mBuf->addr, _TRUNCATE);
				strncpy_s(m->tel, MEMBER_TEL_SIZE + 1, mBuf->tel, _TRUNCATE);
				strncpy_s(m->birth, MEMBER_BIRTH_SIZE + 1, mBuf->birth, _TRUNCATE);
				WriteMemberFile();					/* 会員情報リストのファイル書込み */

			}
			printf("\n新たな会員情報に更新しました。\n");
			num = EXIT_NUM;
			break;
		case 2:									/* 変更内容をさらに変更する場合*/
			//RegistMember(nm);					/* 会員情報をリストに登録 */
			ClearMemberBuffer(&nm);				/* バッファをクリア */
			if (InputUpdateMember(m, &nm) != FALSE) {/* 2回目以降の変更 */
				//num = MemberUpdateCheckSMenu(nm, &mBuf);	/* 【D-1126】会員情報変更確認画面 */
				strncpy_s(m->name, MEMBER_NAME_SIZE + 1, nm.name, _TRUNCATE);
				strncpy_s(m->addr, MEMBER_ADDR_SIZE + 1, nm.addr, _TRUNCATE);
				strncpy_s(m->tel, MEMBER_TEL_SIZE + 1, nm.tel, _TRUNCATE);
				strncpy_s(m->birth, MEMBER_BIRTH_SIZE + 1, nm.birth, _TRUNCATE);
				WriteMemberFile();					/* 会員情報リストのファイル書込み */
				printf("\n会員情報を変更しました。\n");
				count = 1;
			}
			break;
		case EXIT_NUM:							/* 戻る */
			break;
		default:									/* NOT REACHED */
			break;
		}
	}
	return retVal;
}

/*
 * 関数名			: static int MemberDeleatChecksMenu(void)
 * 機能				: 【D-1127】会員情報削除確認画面
 * 入力パラメータ	: なし
 * 出力パラメータ	: なし
 * 戻り値			: int	: 削除する:TRUE / 削除しない:FALSE
 * 特記事項			: なし
 */
static int MemberDeleatCheckSMenu(void)
{
	int retVal = TRUE;		/* 戻り値 */
	DisplayTitle(&memberDeleatCheckSMenu);
	retVal = GetYesNo("");
	return retVal;
}

/*
 * 関数名			: static int MemberSortKeySMenu(void)
 * 機能				: 【D-1128】会員一覧整列項目選択画面
 * 入力パラメータ	: なし
 * 出力パラメータ	: なし
 * 戻り値			: int	:選択番号
 * 特記事項			: なし
 */
static int MemberSortKeySMenu(void)
{
	int retVal = ENTER_NUM;		/* 戻り値 */
	int num = ENTER_NUM;			/* 入力番号 */
	MEMBER* member = NULL;		/* 会員情報ノードへのポインタ */

	/* メニューを表示する */
	while(num != EXIT_NUM) {
		num = GetMenuNum(&memberSortKeySMenu);
		retVal = num;
		switch (num) {
		case 1:								/* 会員ID */
			/* FALL THROUGH */
		case 2:											
			num = MemberSortUdSMenu(num); 	/* 【D-1129】会員一覧表示順選択画面 */
			break;
		case EXIT_NUM:
			break;
		default:								/* NOT REACHED */
			break;
		}
	}
	return retVal;
}

/*
 * 関数名			: static int MemberSortUdSMenu(const int key)
 * 機能				: 【D-1129】会員一覧表示順選択画面
 * 入力パラメータ	: const int key	:ソートキー
 * 出力パラメータ	: なし
 * 戻り値			: int	:EXIT_NUM
 * 特記事項			: なし
 */
static int MemberSortUdSMenu(const int key)
{
	int retVal = ENTER_NUM;		/* 戻り値 */
	int num = ENTER_NUM;			/* 入力番号 */

	while(num != EXIT_NUM) {
		num = GetMenuNum(&memberSortUdSMenu);
		retVal = num;
		switch (num) {
		case 1:										/* 昇順 */
			/* FALL THROUGH */
		case 2:										/* 降順 */
			num = MemberListCheckSMenu(key, num);	/* 【D-1130】会員一覧表示画面 */
			retVal = EXIT_NUM;
			break;
		case EXIT_NUM:
			break;
		default:										/* NOT REACHED */
			break;
		}
	}
	return retVal;
}

/*
 * 関数名			: static int MemberListCheckSMenu(const int key, const int ud)
 * 機能				: 【D-1130】会員一覧表示画面
 * 入力パラメータ	: const int key	:ソートキー
 * 					: const int ud	:昇順/降順（1:昇順/2:降順）
 * 出力パラメータ	: なし
 * 戻り値			: int	:EXIT_NUM
 * 特記事項			: なし
 */
static int MemberListCheckSMenu(const int key, const int ud)
{
	int retVal = ENTER_NUM;		/* 戻り値 */
	int num = ENTER_NUM;			/* 入力番号 */
	char id[MEMBER_ID_SIZE + STRING_TERMINATOR_SIZE];	/* 会員ID */

	while(num != EXIT_NUM) {
		/* 商品一覧を表示する */
		if(DisplayMemberList(key, ud, num) == FALSE) {	/* 最後まで表示したかどうか */
			num = GetMenuNum(&memberListCheckSMenu);			/* 選択メニューを表示する */
			if (num == EXIT_NUM) {							/* 選択０の時 */
				retVal = EXIT_NUM;
			} else if((num == ADVANCE_NUM) || (num == NULL_NUM)) {		/* 選択１の時 */
				printf("最後のページです\n");
				printf("会員情報管理メニューに戻ります\n");
				num = EXIT_NUM;
				retVal = EXIT_NUM;
			} else {										/* 選択２の時 */
				retVal = MemberUpdateSMenu();		/* 【D-1124】会員情報確認画面 */
				num = EXIT_NUM;
				retVal = EXIT_NUM;
			}
		} else {
			num = GetMenuNum(&memberListCheckSMenu);		/* 選択メニューを表示する */
			if (num == EXIT_NUM) {							/* 選択０の時 */
				retVal = EXIT_NUM;
			} else if((num == ADVANCE_NUM) || (num == NULL_NUM)) {
															/* 選択１の時は何もしない */
			} else {										/* 選択２の時 */
				retVal = MemberUpdateSMenu();		/* 【D-1124】会員情報確認画面 */
				num = EXIT_NUM;
			}
			retVal = num;
		}
	}
	return retVal;
}

/*
 * 関数名			: static int MemberIDSerchMenu(const int size, char *tel, MEMBER **m)
 * 機能				: 【D-1131】会員ID検索画面
 * 入力パラメータ	: const int size	:桁数 
 * 出力パラメータ	: char *tel	:電話番号	MEMBER **m	:会員情報ノードへのポインタへのアドレス
 * 戻り値			: int	:ENTER_NUM
 * 特記事項			: 無効な番号を入力した場合は再入力を促す
 */
static int MemberIDSerchMenu(const int size, char *tel, MEMBER** m) {
	int retVal = ENTER_NUM;		/* 戻り値 */
	MEMBER* search;

	while (TRUE) {
		DisplayTitle(&memberIDSurchMenu);	/* タイトル表示 */
		GetTelNumStr(tel, size);			/* 電話番号を文字列として取得 */
		if((tel[0] == '0') && (tel[1] == '\0')) {	/* 0が入力された場合 */
			retVal = EXIT_NUM;
			break;
		} else if(tel[0] == NULL) {	/* NULLが入力された場合 */
			retVal = EXIT_NUM;
			break;
		} else {	/* 電話番号入力 */
			/* 会員情報リストを検索する */
			if (Searchtel(tel, &search) == FALSE) {
				printf("該当する電話番号がありません。\n");
			} else {
				*m = search;
				break;
			}
		}
	}
	return retVal;

}

/*
 * 関数名			: static int GoodsManageMenu(void)
 * 機能				: 【D-1140】商品情報管理メニュー
 * 入力パラメータ	: なし
 * 出力パラメータ	: なし
 * 戻り値			: int	:選択番号
 * 特記事項			: なし
 */
static int GoodsManageMenu(void)
{
	int retVal = ENTER_NUM;		/* 戻り値 */
	int num = ENTER_NUM;			/* 入力番号 */
	GOODS *goods = NULL;			/* 商品情報ノードへのポインタ */
	
	ReadGoodsFile(&goods);				/* 商品情報マスタファイルの読込み */
	while(num != EXIT_NUM) {
		num = GetMenuNum(&goodsManageMenu);
		retVal = num;
		switch(num) {
		case 1:
			GoodsRegistInputSMenu();		/* 【D-1141】新規商品情報入力画面 */
			break;
		case 2:
			GoodsUpdateSMenu();			/* 【D-1143】商品情報確認画面 */
			break;
		case 3:
			GoodsSortKeySMenu();			/* 【D-1147】商品一覧整列項目選択画面 */
			break;
		case EXIT_NUM:
			break;
		default:							/* NOT REACHED */
			break;
		}
	}
	FreeGoodsList();						/* 商品情報リストの解放 */
	return retVal;
}

/*
 * 関数名			: static int GoodsRegistInputSMenu(void)
 * 機能				: 【D-1141】新規商品情報入力画面
 * 入力パラメータ	: なし
 * 出力パラメータ	: なし
 * 戻り値			: int	:選択番号（登録しない:1 / 戻る:EXIT_NUM）
 * 特記事項			: なし
 */
static int GoodsRegistInputSMenu(void)
{
	int retVal = ENTER_NUM;		/* 戻り値 */
	int num = ENTER_NUM;			/* 入力番号 */
	GOODS *goods = NULL;			/* 商品情報ノードへのポインタ */
	GOODS gBuf;					/* 商品情報 */
	
	/* メニューを表示する */
	while(num != EXIT_NUM) {
		num = GetMenuNum(&goodsRegistInputSMenu);
		retVal = num;
		switch(num) {
		case 1:											/* 情報入力 */
			ClearGoodsBuffer(&gBuf);						/* バッファをクリア */
			if(InputRegistGoods(&gBuf) != FALSE) {		/* 登録する商品情報を入力 */
				num = GoodsRegistCheckSMenu(&gBuf);		/* 【D-1142】新規商品情報確認画面 */
			}
			break;
		case EXIT_NUM:									/* 戻る */
			break;
		default:											/* NOT REACHED */
			break;
		}
	}
	return retVal;
}

/*
 * 関数名			: static int GoodsRegistCheckSMenu(const GOODS *goods)
 * 機能				: 【D-1142】新規商品情報確認画面
 * 入力パラメータ	: const GOODS *goods	:商品情報へのポインタ
 * 出力パラメータ	: なし
 * 戻り値			: int	:選択番号（登録:1 / 戻る:EXIT_NUM）
 * 特記事項			: なし
 */
static int GoodsRegistCheckSMenu(const GOODS *goods)
{
	int retVal = ENTER_NUM;		/* 戻り値 */
	int num = ENTER_NUM;			/* 入力番号 */
	
	DisplayRegistGoods(goods);					/* 登録する商品情報を表示 */
	while(num != EXIT_NUM) {
		num = GetMenuNum(&goodsRegistCheckSMenu);
		retVal = num;
		switch(num) {
		case 1:									/* 登録 */
			RegistGoods(goods);					/* 商品情報をリストに登録 */
			WriteGoodsFile();					/* 商品情報リストのファイル書込み */
			printf("\n商品情報を登録しました。\n");
			num = EXIT_NUM;
			break;
		case EXIT_NUM:							/* 戻る */
			break;
		default:									/* NOT REACHED */
			break;
		}
	}
	return retVal;
}

/*
 * 関数名			: static int GoodsIDGetSMenu(const int size, char *id, GOODS **g)
 * 機能				: 【D-1111】商品ID入力画面（商品情報マスタファイル）
 * 入力パラメータ	: const int size	:桁数
 * 出力パラメータ	: char *id	:商品ID
 * 					: GOODS **g	:商品情報ノードへのポインタへのアドレス
 * 戻り値			: int	:選択番号（'0'またはNULLを入力:EXIT_NUM / それ以外を入力:ENTER_NUM）
 * 特記事項			: 無効なIDを入力した場合には再入力を促す
 */
static int GoodsIDGetSMenu(const int size, char *id, GOODS **g)
{
	int retVal = ENTER_NUM;		/* 戻り値 */
	GOODS *search;
	
	while(TRUE) {
		DisplayTitle(&goodsIDGetSMenu);					/* タイトルを表示 */
		GetNumStr(id, size);								/* IDを文字列として取得 */
		if((id[0] == '0') && (id[1] == '\0')) {			/* ID入力が'0'の場合 */
			retVal = EXIT_NUM;
			break;
		} else if(id[0] == '\0') {						/* ID入力がNULLの場合 */
			retVal = EXIT_NUM;
			break;
		} else {											/* ID入力がある場合 */
			/* 商品情報リストを検索する */
			if(SearchGoods(id, &search) == FALSE) {
				printf("該当する商品IDがありません。\n");
			} else {
				*g = search;
				break;
			}
		}
	}
	return retVal;
}

/*
 * 関数名			: static int GoodsUpdateSMenu(void)
 * 機能				: 【D-1143】商品情報確認画面
 * 入力パラメータ	: なし
 * 出力パラメータ	: なし
 * 戻り値			: int	:選択番号（戻る:EXIT_NUM / 変更しない:1 / 削除しない:2）
 * 特記事項			: なし
 */
static int GoodsUpdateSMenu(void)
{
	int retVal = ENTER_NUM;							/* 戻り値 */
	int num = ENTER_NUM;								/* 入力番号 */
	char id[GOODS_ID_SIZE+STRING_TERMINATOR_SIZE];	/* 商品ID */
	GOODS *goods = NULL;								/* 商品情報ノードへのポインタ */
	
	while(num != EXIT_NUM) {
		num = GoodsIDGetSMenu(GOODS_ID_SIZE, id, &goods);	/* 【D-1111】商品ID入力画面 */
		retVal = num;
		if(num != EXIT_NUM) {								/* 有効な商品IDが入力されたら、商品情報とメニューを表示 */
			DisplayGoods(goods);								/* 商品情報を表示 */
			num = GetMenuNum(&goodsUpdateSMenu);
			retVal = num;
			switch(num) {
			case 1:											/* 変更 */
				num = GoodsUpdateInputSMenu(goods);			/* 【D-1144】商品情報変更入力画面 */
				break;
			case 2:											/* 削除 */
				num = DeleteGoods(id);						/* 商品情報を削除 */
				break;
			case EXIT_NUM:									/* 戻る */
				break;
			default:											/* NOT REACHED */
				break;
			}
		}
	}
	return retVal;
}

/*
 * 関数名			: static int GoodsUpdateInputSMenu(GOODS* g)
 * 機能				: 【D-1144】商品情報変更入力画面
 * 入力パラメータ	: GOODS *g:商品情報へのポインタ
 * 出力パラメータ	: なし
 * 戻り値			: int	:選択番号（変更:1 / 戻る:EXIT_NUM）
 * 特記事項			: なし
 */
static int GoodsUpdateInputSMenu(GOODS* g)
{
	int retVal = ENTER_NUM;		/* 戻り値 */
	int num = ENTER_NUM;			/* 入力番号 */
	GOODS gBuf;					/* 商品情報 */

	while(num != EXIT_NUM) {
		num = GetMenuNum(&goodsUpdateInputSMenu);
		retVal = num;
		switch(num) {
		case 1:												/* 変更 */
			ClearGoodsBuffer(&gBuf);							/* バッファをクリア */
			if(InputUpdateGoods(g, &gBuf) != FALSE) {		/* 更新する商品情報を入力 */
				retVal = GoodsUpdateCheckSMenu(g, &gBuf);	/* 【D-1145】商品情報変更確認画面 */
				if(retVal == 1){
					num = EXIT_NUM;							/* 変更後はメニューを終了 */
				}
			}
			break;
		case EXIT_NUM:										/* 戻る */
			break;
		default:												/* NOT REACHED */
			break;
		}
	}
	return retVal;
}

/*
 * 関数名			: static int GoodsUpdateCheckSMenu(GOODS *g, GOODS *gBuf)
 * 機能				: 【D-1145】商品情報変更確認画面
 * 入力パラメータ	: GOODS *g	:変更前の商品情報へのポインタ
 *					: GOODS *gBuf	:変更後の商品情報へのポインタ
 * 出力パラメータ	: なし
 * 戻り値			: int	:選択番号（変更:1 / 戻る:EXIT_NUM）
 * 特記事項			: なし
 */
static int GoodsUpdateCheckSMenu(GOODS *g, GOODS *gBuf)
{
	int retVal = ENTER_NUM;		/* 戻り値 */
	int num = ENTER_NUM;			/* 入力番号 */
	
	DisplayGoods(gBuf);							/* 登録する商品情報を表示 */
	while(num != EXIT_NUM) {
		num = GetMenuNum(&goodsUpdateCheckSMenu);
		retVal = num;
		switch(num) {
		case 1:									/* 変更 */
			strncpy_s(g->title, GOODS_TITLE_SIZE+1, gBuf->title, _TRUNCATE);
			strncpy_s(g->genre, GOODS_GENRE_SIZE+1, gBuf->genre, _TRUNCATE);
			strncpy_s(g->sellDat, GOODS_SELL_DATE_SIZE+1, gBuf->sellDat, _TRUNCATE);
			strncpy_s(g->rentDat, GOODS_RENT_DATE_SIZE+1, gBuf->rentDat, _TRUNCATE);
			strncpy_s(g->lendMID, GOODS_LEND_MID_SIZE+1, gBuf->lendMID, _TRUNCATE);
			strncpy_s(g->lendSts, GOODS_LEND_STS_SIZE+1, gBuf->lendSts, _TRUNCATE);
			strncpy_s(g->lendNum, GOODS_LEND_NUM_SIZE+1, gBuf->lendNum, _TRUNCATE);
			strncpy_s(g->keep, GOODS_KEEP_SIZE+1, gBuf->keep, _TRUNCATE);
			WriteGoodsFile();					/* 商品情報リストのファイル書込み */
			printf("\n商品情報を変更しました。\n");
			num = EXIT_NUM;
			break;
		case EXIT_NUM:							/* 戻る */
			break;
		default:									/* NOT REACHED */
			break;
		}
	}
	return retVal;
}

/*
 * 関数名			: static int GoodsSortKeySMenu(void)
 * 機能				: 【D-1147】商品一覧整列項目選択画面
 * 入力パラメータ	: なし
 * 出力パラメータ	: なし
 * 戻り値			: int	:選択番号
 * 特記事項			: なし
 */
static int GoodsSortKeySMenu(void)
{
	int retVal = ENTER_NUM;		/* 戻り値 */
	int num = ENTER_NUM;			/* 入力番号 */
	GOODS *goods = NULL;			/* 商品情報ノードへのポインタ */
	
	/* メニューを表示する */
	while(num != EXIT_NUM) {
		num = GetMenuNum(&goodsSortKeySMenu);
		retVal = num;
		switch(num) {
		case 1:										/* 商品ID */
			/* FALL THROUGH */
		case 2:										/* 保管場所 */
			/* FALL THROUGH */
		case 3:										/* 発売日 */
			num = GoodsSortUdSMenu(num);				/* 【D-1148】商品一覧表示順選択画面 */
			break;
		case 4:										/* 貸出回数 */
			num = GoodsListCheckSMenu(num, 2); 		/* 【D-1149】商品一覧表示画面 */
			break;
		case EXIT_NUM:
			break;
		default:										/* NOT REACHED */
			break;
		}
	}
	return retVal;
}

/*
 * 関数名			: static int GoodsSortUdSMenu(const int key)
 * 機能				: 【D-1148】商品一覧表示順選択画面
 * 入力パラメータ	: const int key	:ソートキー
 * 出力パラメータ	: なし
 * 戻り値			: int	:EXIT_NUM
 * 特記事項			: なし
 */
static int GoodsSortUdSMenu(const int key)
{
	int retVal = ENTER_NUM;		/* 戻り値 */
	int num = ENTER_NUM;			/* 入力番号 */
	
	while(num != EXIT_NUM) {
		num = GetMenuNum(&goodsSortUdSMenu);
		retVal = num;
		switch(num) {
		case 1:										/* 昇順 */
			/* FALL THROUGH */
		case 2:										/* 降順 */
			num = GoodsListCheckSMenu(key, num);		/* 【D-1149】商品一覧表示画面 */
			retVal = EXIT_NUM;
			break;
		case EXIT_NUM:
			break;
		default:										/* NOT REACHED */
			break;
		}
	}
	return retVal;
}

/*
 * 関数名			: static int GoodsListCheckSMenu(const int key, const int ud)
 * 機能				: 【D-1149】商品一覧表示画面
 * 入力パラメータ	: const int key	:ソートキー
 * 					: const int ud	:昇順/降順（1:昇順/2:降順）
 * 出力パラメータ	: なし
 * 戻り値			: int	:EXIT_NUM
 * 特記事項			: なし
 */
static int GoodsListCheckSMenu(const int key, const int ud)
{
	int retVal = ENTER_NUM;		/* 戻り値 */
	int num = ENTER_NUM;			/* 入力番号 */
	
	while(num != EXIT_NUM) {
		/* 商品一覧を表示する */
		if(DisplayGoodsList(key, ud, num) == FALSE) {	/* 最後まで表示 ? */
			num = EXIT_NUM;								/* while文を抜ける */
			retVal = EXIT_NUM;
		} else {
			num = GetMenuNum(&goodsListCheckSMenu);		/* 選択メニューを表示する */
			retVal = num;
		}
	}
	return retVal;
}
