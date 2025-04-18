/*
 * �t�@�C����	: member.h
 * �@�\			: ����Ǘ����s��
 * ���L����		: �Ȃ�
 * �C������		:  1  2012/01/10 V01L1 ����
 *				:  2  
 */

#ifndef MEMBER_H
#define MEMBER_H

/* #define�}�N�� */
/* �o�b�t�@�T�C�Y */
/* WriteMemberFile */
#define WRITEMEMBERFILE_BUF_SIZE		100		/* �t�H�[�}�b�g�p������i�[�p�o�b�t�@�T�C�Y */

/* InputRegistMember */
#define INPUTREGISTMEMBER_BUF_SIZE		128		/* ��������͗p�o�b�t�@�T�C�Y */
	
/* GetMemberID */
#define GETMEMBERID_STR_BUF_SIZE		20		/* �����񑀍�p�o�b�t�@�T�C�Y */
#define GETMEMBERID_DATE_BUF_SIZE		10		/* �{���̓��t������i�[�p�o�b�t�@�T�C�Y */

/* DisplayRegistMember */
#define DISPLAYREGISTMEMBER_BUF_SIZE	16		/* ���t�t�H�[�}�b�g�p������i�[�p�o�b�t�@�T�C�Y */

/* InputUpdateGoods */
#define INPUTUPDATEMEMBER_DATE_BUF_SIZE	16		/* ���t�t�H�[�}�b�g�p������i�[�p�o�b�t�@�T�C�Y */
	
/* DisplayMember */
#define DISPLAYMEMBER_BUF_SIZE			16		/* ���t�t�H�[�}�b�g�p������i�[�p�o�b�t�@�T�C�Y */

/* InputUpdateMember */
#define INPUTUPDATEMEMBER_BUF_SIZE		16		/* ���t�t�H�[�}�b�g�p������i�[�p�o�b�t�@�T�C�Y */

/* DisplayMemberList */
#define DISPLAYMEMBERLIST_HEAD_COL_NUM				30	/* DisplayMemberList �w�b�_�[���ڗ� */
#define DISPLAYMEMBERLIST_HEAD_COL_BUF_SIZE			20	/* DisplayMemberList �w�b�_�[���ڕ�����p�o�b�t�@�T�C�Y */
#define DISPLAYMEMBERLIST_HEAD_BUF_SIZE				200	/* DisplayMemberList �w�b�_�[������p�o�b�t�@�T�C�Y */
#define DISPLAYMEMBERLIST_HEAD_FORMAT_COL_NUM		10	/* DisplayMemberList printf�̃t�H�[�}�b�g������p�� */
#define DISPLAYMEMBERLIST_HEAD_FORMAT_COL_BUF_SIZE	10	/* DisplayMemberList printf�̃t�H�[�}�b�g������p�o�b�t�@�T�C�Y */
#define DISPLAYMEMBERLIST_DATE_BUF_SIZE				20	/* DisplayMemberList ���t�t�H�[�}�b�g�p������p�o�b�t�@�T�C�Y */
#define DISPLAYMEMBERLIST_DSP_BUF_SIZE				40	/* DisplayMemberList �\��������̒��������p�o�b�t�@�T�C�Y */

/* ����ꗗ��ʕ\�� */
#define MEMBER_MON_DSP_NUM		20				/* 1��ʂ̉���\���� */

/* ����ꗗ�\���F������̕\������ */
#define MEMBER_DSP_ID_NUM			12			/* ���ID */
#define MEMBER_DSP_NAME_NUM			12			/* ���� */
#define MEMBER_DSP_ADDR_NUM			24			/* �Z�� */
#define MEMBER_DSP_TEL_NUM			12			/* �d�b�ԍ� */
#define MEMBER_DSP_BIRTH_NUM		10			/* ���N���� */

/* ����ꗗ�\���F���ڕ\���� */
#define MEMBER_DSP_COL_NUM			5			/* �\�����ڐ� */

/* ����ꗗ�\���F���ڕ\����ԍ� */
#define MEMBER_DSP_ROWNO_COL		0			/* �s�ԍ� */
#define MEMBER_DSP_ID_COL			1			/* ���ID */
#define MEMBER_DSP_NAME_COL			2			/* ���� */
#define MEMBER_DSP_ADDR_COL			3			/* �Z�� */
#define MEMBER_DSP_TEL_COL			4			/* �d�b�ԍ� */
#define MEMBER_DSP_BIRTH_COL		5			/* ���N���� */

/* ����ꗗ�\���F�\�����ږ��i�S�p��5�����ȓ��j */
#define MEMBER_DSP_ROWNO_NAME	"No."			/* �s�ԍ� */
#define MEMBER_DSP_ID_NAME		"���ID"		/* ���ID */
#define MEMBER_DSP_NAME_NAME	"����"			/* ���� */
#define MEMBER_DSP_ADDR_NAME	"�Z��"			/* �Z�� */
#define MEMBER_DSP_TEL_NAME		"�d�b�ԍ�"		/* �d�b�ԍ� */
#define MEMBER_DSP_BIRTH_NAME	"���N����"		/* ���N���� */

/* ������}�X�^�t�@�C�� */
#define MEMBER_FILE_NAME	"memberMST.dat"		/* ������}�X�^�t�@�C���� */
#define MEMBER_REG_MAX		10000				/* ����ő�o�^�� */

/* ������}�X�^�t�@�C���F���ږ��i�S�p��5�����ȓ��j */
#define MEMBER_ID_NAME		"���ID"			/* ���ID */
#define MEMBER_NAME_NAME	"���O"				/* ���O */
#define MEMBER_ADDR_NAME	"�Z��"				/* �Z�� */
#define MEMBER_TEL_NAME		"�d�b�ԍ�"			/* �d�b�ԍ� */
#define MEMBER_BIRTH_NAME	"���N����"			/* ���N���� */

/* ������}�X�^�t�@�C���F������̊e�����i�\���̃����o�[�̑傫���j */
#define MEMBER_ID_SIZE		12					/* ���ID */
#define MEMBER_NAME_SIZE	16					/* ���O */
#define MEMBER_ADDR_SIZE	60					/* �Z�� */
#define MEMBER_TEL_SIZE		12					/* �d�b�ԍ� */
#define MEMBER_BIRTH_SIZE	8					/* ���N���� */

/* ������}�X�^�t�@�C���F�����񃌃R�[�h���̐擪�ʒu */
#define MEMBER_ID_POS		0										/* ���ID */
#define MEMBER_NAME_POS		MEMBER_ID_POS + MEMBER_ID_SIZE			/* ���O */
#define MEMBER_ADDR_POS		MEMBER_NAME_POS + MEMBER_NAME_SIZE		/* �Z�� */
#define MEMBER_TEL_POS		MEMBER_ADDR_POS + MEMBER_ADDR_SIZE		/* �d�b�ԍ� */
#define MEMBER_BIRTH_POS	MEMBER_TEL_POS + MEMBER_TEL_SIZE		/* ���N���� */

/* ������}�X�^�t�@�C���F�����񃌃R�[�h�̃T�C�Y */
#define MEMBER_SIZE			MEMBER_BIRTH_POS + MEMBER_BIRTH_SIZE

/* struct�^�O��` */
/* ������ */
typedef struct member {
	char id[MEMBER_ID_SIZE+1];					/* ���ID */
	char name[MEMBER_NAME_SIZE+1];				/* ���O */
	char addr[MEMBER_ADDR_SIZE+1];				/* �Z�� */
	char tel[MEMBER_TEL_SIZE+1];				/* �d�b�ԍ� */
	char birth[MEMBER_BIRTH_SIZE+1];			/* ���N���� */
	struct member *next;						/* ���ȎQ�ƃ|�C���^ */
}MEMBER;

/* �֐��v���g�^�C�v�錾 */
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

