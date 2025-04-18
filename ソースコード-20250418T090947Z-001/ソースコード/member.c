/*
 * �t�@�C����	: member.c
 * �@�\			: ����Ǘ����s��
 * ���L����		: �Ȃ�
 * �C������		:  1  2012/01/10 V01L1 ����
 *				:  2  2012/02/14 V02L1
 */

/* �w�b�_�[�̎�荞�� */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "menu.h"
#include "member.h"

/* static�ϐ��錾 */
static MEMBER *root = NULL;		/* �����񃊃X�g�̐擪�m�[�h�Q�Ɨp */

/* static�֐��錾 */
static void CreateMemberList(MEMBER **member);
static int GetMemberID(char *id);
static void SortMemberList(const int key, const int ud);

/*
 * �֐���			: int ReadMemberFile(MEMBER **member)
 * �@�\				: ����������ID���Ƀ��X�g�\���ɓǂݍ���
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: MEMBER **member:�ǂݍ��񂾉�����̐擪�m�[�h�̃A�h���X
 * �߂�l			: int	:TRUE
 * ���L����			: �Ȃ�
 */
int ReadMemberFile(MEMBER **member)
{
	int retVal = TRUE;
	MEMBER *newone;								/* ������̒ǉ��m�[�h�Q�Ɨp */
	MEMBER *target;								/* �^�[�Q�b�g�m�[�h�p */
	FILE* fp;									/* �t�@�C���|�C���^ */
	char buf[MEMBER_SIZE+REC_DELIMITER_SIZE];	/* �t�@�C���Ǎ��̈�i1���R�[�h�T�C�Y���]�T����������j */
	errno_t error;
	
	/* ������}�X�^�t�@�C����ǂݍ��� */
	error = fopen_s(&fp, MEMBER_FILE_NAME, "r");
	if(error != 0) {
		printf("\n������}�X�^�t�@�C��������܂���B�������I�����܂��B\n");
		exit(EXIT_FAILURE);
	}
	
	/* �t�@�C���ǂݍ��݂̂��߂̑O���� */
	CreateMemberList(&target);
	*member = root;
	memset(buf, '\0', sizeof(buf));								/* �t�@�C���ǂݍ��ݗ̈���N���A */
	
	/* �t�@�C����EOF�܂œǂݍ��� */
	while(fgets(buf, sizeof(buf), fp) != NULL) {				/* �t�@�C���I���܂œǂݍ��� */
		
		/* �V���ȃm�[�h��ǉ����f�[�^���i�[���� */
		if((newone = (MEMBER*)malloc(sizeof(MEMBER))) == NULL) {	/* �m�[�h���쐬 */
			printf("���I�������̎擾�Ɏ��s���܂����B\n");
			exit(EXIT_FAILURE);
		}
		
		/* ��������m�[�h�Ɋi�[���� */
		strncpy_s(newone->id, MEMBER_ID_SIZE+1, &buf[MEMBER_ID_POS], _TRUNCATE);
		strncpy_s(newone->name, MEMBER_NAME_SIZE+1, &buf[MEMBER_NAME_POS], _TRUNCATE);
		strncpy_s(newone->addr, MEMBER_ADDR_SIZE+1, &buf[MEMBER_ADDR_POS], _TRUNCATE);
		strncpy_s(newone->tel, MEMBER_TEL_SIZE+1, &buf[MEMBER_TEL_POS], _TRUNCATE);
		strncpy_s(newone->birth, MEMBER_BIRTH_SIZE+1, &buf[MEMBER_BIRTH_POS], _TRUNCATE);
		
		/* �����̋󔒂��폜���� */
		TrimSpace(newone->id);
		TrimSpace(newone->name);
		TrimSpace(newone->addr);
		TrimSpace(newone->tel);
		TrimSpace(newone->birth);
		
		/* ID�ŏ����ɂȂ�悤�Ƀm�[�h��ǉ����� */
		target = root;											/* �^�[�Q�b�g��擪�ɐݒ� */
		while(TRUE) {
			/* ���̃m�[�h������Ȃ�΁AID���`�F�b�N���� */
			if(target->next != NULL) {
				/* �ǉ��m�[�h��ID���������Ȃ�΁A�^�[�Q�b�g�̌��Ƀm�[�h��ǉ����ďI������ */
				if(strncmp(newone->id, target->next->id, MEMBER_ID_SIZE) < 0) {
					newone->next = target->next;
					target->next = newone;
					break;
				} else {
					target = target->next;						/* �^�[�Q�b�g���X�V���Ď��̃m�[�h�� */
				}
			} else {
				/* �V�����m�[�h�����X�g�̖����ɒǉ����ďI������ */
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
 * �֐���			: static void CreateMemberList(MEMBER **member)
 * �@�\				: �����񃊃X�g������������
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: MEMBER **member	:�_�~�[�m�[�h�̃A�h���X
 * �߂�l			: �Ȃ�
 * ���L����			: �Ȃ�
 */
static void CreateMemberList(MEMBER **member)
{
	/* �_�~�[�m�[�h���쐬���� */
	FreeMemberList();
	if((root = (MEMBER*)malloc(sizeof(MEMBER))) == NULL) {
		printf("���I�������̎擾�Ɏ��s���܂����B\n");
		exit(EXIT_FAILURE);
	}
	root->next = NULL;
	*member = root;
}

/*
 * �֐���			: void FreeMemberList(void)
 * �@�\				: �����񃊃X�g������������������
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: �Ȃ�
 * ���L����			: �Ȃ�
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
 * �֐���			: int WriteMemberFile(void)
 * �@�\				: �����񃊃X�g���t�@�C���ɏ�������
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:TRUE�i�������ݐ���j���TRUE��Ԃ�
 * ���L����			: ����R�[�h�Ń\�[�g���Ȃ����荞��
 */
int WriteMemberFile(void)
{
	int retVal = TRUE;
	FILE* fp;								/* �t�@�C���|�C���^ */
	MEMBER *target;							/* �^�[�Q�b�g�m�[�h�p */
	char form[WRITEMEMBERFILE_BUF_SIZE];	/* �t�H�[�}�b�g�p������ */
	errno_t error;

	/* �t�@�C�����I�[�v������ */
	error = fopen_s(&fp, MEMBER_FILE_NAME, "w");
	if(error != 0) {
		printf("\n������}�X�^�t�@�C���ɏ������݂ł��܂���B�������I�����܂��B\n");
		exit(EXIT_FAILURE);
	}
	
	/* fprintf�̃t�H�[�}�b�g��ݒ肷�� */
	sprintf_s(form, WRITEMEMBERFILE_BUF_SIZE, "%%-%ds%%-%ds%%-%ds%%-%ds%%-%ds\n",
		MEMBER_ID_SIZE,
		MEMBER_NAME_SIZE,
		MEMBER_ADDR_SIZE,
		MEMBER_TEL_SIZE,
		MEMBER_BIRTH_SIZE
	);
	
	/* �����񃊃X�g���t�@�C���ɏ������� */
	target = root;
	while(target->next != NULL) {
		/* ���X�g�̓��e���������� */
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
 * �֐���			: int SearchMember(const char *id, MEMBER **m)
 * �@�\				: �yD-1121�z�w�肵��ID�̉�������擾����
 * ���̓p�����[�^	: const char *id	:����������ID
 * �o�̓p�����[�^	: MEMBER **m		:�������ꂽ������m�[�h�ւ̃|�C���^
 * �߂�l			: int	:TRUE�i��������擾�j/FALSE�i�w�肵�����ID���Ȃ��j
 * ���L����			: �Ȃ�
 */
int SearchMember(const char *id, MEMBER **m)
{
	int retVal = FALSE;
	MEMBER *target;				/* �����^�[�Q�b�g�m�[�h�p */
	
	target = root;
	while(target->next != NULL) {
		target = target->next;
		if(strncmp(target->id, id, MEMBER_ID_SIZE) == 0) {
			*m = target;		/* �q�b�g�����f�[�^�̃A�h���X��߂�l�ɐݒ� */
			retVal = TRUE;
			break;
		}
	}
	return retVal;
}

/*
 * �֐���			: void ClearMemberBuffer(MEMBER *m)
 * �@�\				: �yD-1122�z������o�b�t�@���N���A����
 * ���̓p�����[�^	: MEMBER *m	:������ւ̃|�C���^
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: �Ȃ�
 * ���L����			: �Ȃ�
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
 * �֐���			: int InputRegistMember(MEMBER *m)
 * �@�\				: �yD-1122�z�V�K�ɓo�^������������͂���
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: MEMBER *m	:���͂���������ւ̃|�C���^
 * �߂�l			: int	:TRUE�i�V�K���ID�擾�j/FALSE�i�V�K���ID�擾�ł��Ȃ��j
 * ���L����			: �Ȃ�
 */
int InputRegistMember(MEMBER *m)
{
	int retVal;
	char buf[INPUTREGISTMEMBER_BUF_SIZE];				/* ������p�o�b�t�@ */
	char id[MEMBER_ID_SIZE+STRING_TERMINATOR_SIZE];		/* ���ID�p������ */
	
	/* ��������͂��� */
	buf[0] = '\0';
	while(strlen(buf) == 0) {
	    printf("%-6s���@", MEMBER_NAME_NAME);
		GetStr(buf, MEMBER_NAME_SIZE);
	}
	strncpy_s(m->name, MEMBER_NAME_SIZE + 1, buf, _TRUNCATE);
	
	/* �Z������͂��� */
	buf[0] = '\0';
	while(strlen(buf) == 0) {
	    printf("%-6s���@", MEMBER_ADDR_NAME);
		GetStr(buf, MEMBER_ADDR_SIZE);
	}
	strncpy_s(m->addr, MEMBER_ADDR_SIZE + 1, buf, _TRUNCATE);
	
	/* �d�b�ԍ�����͂��� */
	buf[0] = '\0';
	while(strlen(buf) == 0) {
	    printf("%-6s���@", MEMBER_TEL_NAME);
		GetStr(buf, MEMBER_TEL_SIZE);
	}
	strncpy_s(m->tel, MEMBER_TEL_SIZE + 1, buf, _TRUNCATE);

	/* ���N��������͂��� */
	printf("%-6s\n", MEMBER_BIRTH_NAME);
	InputYMD(buf);
	strncpy_s(m->birth, MEMBER_BIRTH_SIZE + 1, buf, _TRUNCATE);

	/* ���ID��V�K�ݒ肷�� */
	if(GetMemberID(id) == FALSE) {					/* ID�̍ő�l�𒴂����ꍇ */
		printf("���ID�̎擾�Ɏ��s���܂����B\n");
		retVal = FALSE;
	} else {										/* ID���擾�ł����ꍇ */
		strncpy_s(m->id, MEMBER_ID_SIZE + 1, id, _TRUNCATE);
		retVal = TRUE;
	}
	return retVal;
}

/*
 * �֐���			: static int GetMemberID(char *id)
 * �@�\				: �yD-1122�z�V�K�̉��ID���擾����
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: char *id	:�V�K�Ɏ擾�������ID
 * �߂�l			: int	:TRUE�i�V�K���ID���擾�j/FALSE�i�V�K���ID���擾�ł��Ȃ��j
 * ���L����			: "99"+���t�{2���̐����@�v12��
 */
static int GetMemberID(char *id)
{
	int retVal = FALSE;
	MEMBER* target;							/* �^�[�Q�b�g�m�[�h�p */
	char w[GETMEMBERID_STR_BUF_SIZE];		/* �����񑀍�p */
	char today[GETMEMBERID_DATE_BUF_SIZE];	/* �{���̓��t */
	int newID;								/* �V�KID�i����10���̐����j */
	int listID;								/* ���i��񃊃X�g����ID�i����10���̐����j */

	/* 10���̉��ID���쐬���� */
	GetToday(0, 0, 0, today);					/* �����̓��t���擾 */
	sprintf_s(w, GETMEMBERID_STR_BUF_SIZE, "%08s%02d", today, 1);	/* ���t+"01"��ID���쐬 */
	newID = atoi(w);

	/* ���i��񃊃X�g���������A�V����ID���擾���� */
	target = root;
	if(target != NULL) {
		/* ���X�g���I������܂ŌJ��Ԃ� */
		while(target->next != NULL) {
			target = target->next;

			/* ���X�g�̏��iID�̉���10�P�^���擾���� */
			strncpy_s(w, GETMEMBERID_STR_BUF_SIZE, target->id + 2, 10);
			listID = atoi(w);

			/* ID���r���� */
			if(newID == listID) {
				newID = listID + 1;
			} else if(newID > listID) {
				/* DO NOTHING */
			} else {
				break;
			}
		}

		/* ID�̍ő�l���`�F�b�N���� */
		if((newID % 100) == 0) {				/* 99�𒴂��� */
			retVal = FALSE;
		} else {
			sprintf_s(id, MEMBER_ID_SIZE + 1, "99%010d", newID);	/* '99'��t�����ĕ�����ɕϊ� */
			retVal = TRUE;
		}
	} else {
		retVal = FALSE;
	}
	return retVal;
}

/*
 * �֐���			: void DisplayRegistMember(const MEMBER *m)
 * �@�\				: �yD-1123�z�o�^����������\������
 * ���̓p�����[�^	: const MEMBER *m	:������ւ̃|�C���^
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: �Ȃ�
 * ���L����			: �Ȃ�
 */
void DisplayRegistMember(const MEMBER *m)
{
	char date[DISPLAYREGISTMEMBER_BUF_SIZE];					/* ���t�t�H�[�}�b�g�p */

	printf("\n*****�V�K������m�F*****\n");
	printf("%-10s:%s\n", MEMBER_ID_NAME, m->id);
	printf("%-10s:%s\n", MEMBER_NAME_NAME, m->name);
	printf("%-10s:%s\n", MEMBER_ADDR_NAME, m->addr);
	printf("%-10s:%s\n", MEMBER_TEL_NAME, m->tel);
	ConvFormatDate(date, m->birth);
	printf("%-10s:%s\n", MEMBER_BIRTH_NAME, date);
}

/*
 * �֐���			: int RegistMember(MEMBER *m)
 * �@�\				: �yD-1123�z������������񃊃X�g�ɓo�^����
 * ���̓p�����[�^	: MEMBER *m	:������ւ̃|�C���^
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:TRUE�i����������X�g�ɓo�^�j���TRUE��Ԃ�
 * ���L����			: �Ȃ�
 */
int RegistMember(const MEMBER *m)
{
	int retVal = FALSE;
	MEMBER *newone;				/* ������̒ǉ��m�[�h�Q�Ɨp */
	MEMBER *target;				/* �^�[�Q�b�g�m�[�h�p */
	
	/* �V���ȃm�[�h��ǉ����f�[�^���i�[ */
	if((newone = (MEMBER*)malloc(sizeof(MEMBER))) == NULL) {		/* �m�[�h���쐬 */
		printf("���I�������̎擾�Ɏ��s���܂����B\n");
		exit(EXIT_FAILURE);
	}
	
	strncpy_s(newone->id, MEMBER_ID_SIZE+1, m->id, _TRUNCATE);
	strncpy_s(newone->name, MEMBER_NAME_SIZE+1, m->name, _TRUNCATE);
	strncpy_s(newone->addr, MEMBER_ADDR_SIZE+1, m->addr, _TRUNCATE);
	strncpy_s(newone->tel, MEMBER_TEL_SIZE+1, m->tel, _TRUNCATE);
	strncpy_s(newone->birth, MEMBER_BIRTH_SIZE+1, m->birth, _TRUNCATE);
	
	/* ID�ŏ����ɂȂ�悤�Ƀm�[�h��ǉ����� */
	target = root;												/* �^�[�Q�b�g��擪�ɐݒ� */
	while(TRUE) {
		/* ���̃m�[�h������Ȃ�΁AID���`�F�b�N���� */
		if(target->next != NULL) {
			/* �ǉ��m�[�h��ID���������Ȃ�΁A�^�[�Q�b�g�̌��Ƀm�[�h��ǉ����ďI������ */
			if(strncmp(newone->id, target->next->id, MEMBER_ID_SIZE) < 0) {
				newone->next = target->next;
				target->next = newone;
				break;
			} else {
				target = target->next;							/* �^�[�Q�b�g���X�V���Ď��̃m�[�h�� */
			}
		} else {
			/* �V�����m�[�h�����X�g�̖����ɒǉ����ďI������ */
			newone->next = NULL;
			target->next = newone;
			break;
		}
	}
	return TRUE;
}

/*
 * �֐���			: void DisplayMember(const MEMBER *m)
 * �@�\				: �yD-1124�z�������\������
 * ���̓p�����[�^	: MEMBER *m	:������ւ̃|�C���^
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: �Ȃ�
 * ���L����			: �Ȃ�
 */
void DisplayMember(const MEMBER *m)
{
	char date[DISPLAYMEMBER_BUF_SIZE];					/* ���t�t�H�[�}�b�g�p */

	printf("\n*****������m�F*****\n");
	printf("%-11s:%s\n", MEMBER_ID_NAME, m->id);
	printf("%-11s:%s\n", MEMBER_NAME_NAME, m->name);
	printf("%-11s:%s\n", MEMBER_ADDR_NAME, m->addr);
	printf("%-11s:%s\n", MEMBER_TEL_NAME, m->tel);
	ConvFormatDate(date, m->birth);
	printf("%-11s:%s\n", MEMBER_BIRTH_NAME, date);
}

/*
 * �֐���			: int DisplayMemberList(const int key, const int ud, const int menuNum)
 * �@�\				: �yD-1130�z����̈ꗗ��\������
 * ���̓p�����[�^	: const int key	:�\�[�g�L�[
 * 					: const int ud	:����/�~���i1:����/2:�~���j
 * 					: const int num	:��ʂ���̑I��ԍ��iENTER_NUM:����A�ȊO:2��ڈȍ~�j
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:TRUE(�܂��\������) / FALSE(�Ō�܂ŕ\��)
 * ���L����			: �Ȃ�
 */
int DisplayMemberList(const int key, const int ud, const int menuNum)
{
	int retVal;
	static MEMBER* target;	/* �^�[�Q�b�g�m�[�h�p */
	static int dspNo = 1;	/* �\���̍��� */

	char h[DISPLAYMEMBERLIST_HEAD_COL_NUM][DISPLAYMEMBERLIST_HEAD_COL_BUF_SIZE];	/* �w�b�_�[���� */
	char head[DISPLAYMEMBERLIST_HEAD_BUF_SIZE];	/* �w�b�_�[ */
	char f[DISPLAYMEMBERLIST_HEAD_FORMAT_COL_NUM][DISPLAYMEMBERLIST_HEAD_FORMAT_COL_BUF_SIZE];	/* printf�̃t�H�[�}�b�g�p */
	char date[DISPLAYMEMBERLIST_DATE_BUF_SIZE];	/* ���t�t�H�[�}�b�g�p */
	int fig;									/* ���Ԃ̌��� */
	int cnt;									/* �\���J�E���^ */
	char buf[DISPLAYMEMBERLIST_DSP_BUF_SIZE];	/* �\��������̒��������p */

	/* �ŏ��̓��͂̏ꍇ�̓��X�g��擪�ɖ߂��A�w��L�[�ŏ���/�~���Ƀ\�[�g���� */
	if(menuNum == ENTER_NUM) {
		target = root;
		dspNo = 1;
		SortMemberList(key, ud);
	}

	/* �w�b�_�[��\������ */
	fig = GetFigure(MEMBER_REG_MAX);			/* ���Ԃ̌������擾 */
	printf("\n*****������ꗗ*****\n");
	strncpy_s(h[MEMBER_DSP_ROWNO_COL], DISPLAYMEMBERLIST_HEAD_COL_BUF_SIZE, MEMBER_DSP_ROWNO_NAME, _TRUNCATE);

	/* �i�����ȉ��͕�����̒������ύX�����\�������邽�߁Astrncpy���g���Ă��Ȃ��j */
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

	/* printf�̃t�H�[�}�b�g��ݒ肷�� */
	sprintf_s(f[MEMBER_DSP_ROWNO_COL], DISPLAYMEMBERLIST_HEAD_FORMAT_COL_NUM, "%%0%dd ", fig);
	sprintf_s(f[MEMBER_DSP_ID_COL], DISPLAYMEMBERLIST_HEAD_FORMAT_COL_NUM, "%%-%ds ", MEMBER_DSP_ID_NUM);
	sprintf_s(f[MEMBER_DSP_NAME_COL], DISPLAYMEMBERLIST_HEAD_FORMAT_COL_NUM, "%%-%ds ", MEMBER_DSP_NAME_NUM);
	sprintf_s(f[MEMBER_DSP_ADDR_COL], DISPLAYMEMBERLIST_HEAD_FORMAT_COL_NUM, "%%-%ds ", MEMBER_DSP_ADDR_NUM);
	sprintf_s(f[MEMBER_DSP_TEL_COL], DISPLAYMEMBERLIST_HEAD_FORMAT_COL_NUM, "%%-%ds ", MEMBER_DSP_TEL_NUM);
	sprintf_s(f[MEMBER_DSP_BIRTH_COL], DISPLAYMEMBERLIST_HEAD_FORMAT_COL_NUM, "%%-%ds ", MEMBER_DSP_BIRTH_NUM);

	/* ���i���X�g��\������ */
	cnt = 0;
	while(target->next != NULL) {
		/* ���X�g�̓��e��\������ */
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
		/* �\���y�[�W�𐧌䂷�� */
		cnt++;
		if(cnt == MEMBER_MON_DSP_NUM) {
			break;
		}
	}

	if(target->next == NULL) {
		printf("\n�Ō�܂ŕ\�����܂����B\n");
		retVal = FALSE;
	} else {
		retVal = TRUE;
	}
	return retVal;
}

/*
 * �֐���			: static void SortMemberList(const int key, const int ud)
 * �@�\				: �yD-1129�z���i��񃊃X�g���w��L�[�ŏ���/�~���Ƀ\�[�g����
 * ���̓p�����[�^	: const int key	:�\�[�g�L�[
 * 					: const int ud	:����/�~���i1:����/2:�~���j
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: �Ȃ�
 * ���L����			: �Ȃ�
 */
static void SortMemberList(const int key, const int ud)
{
	MEMBER *sort;		/* �\�[�g��̐擪�m�[�h */
	MEMBER *sTarget;	/* �\�[�g�p�^�[�Q�b�g�m�[�h */
	MEMBER *rTarget;	/* ���[�g�p�^�[�Q�b�g�m�[�h */
	MEMBER *newone;		/* ������̒ǉ��m�[�h�Q�Ɨp */
	MEMBER *temp;		/* ����������p */
	int cmp;			/* strncmp�̖߂�l�p */
	
	/* �\�[�g���X�g�p�̃_�~�[�m�[�h���쐬���� */
	if((sort = (MEMBER*)malloc(sizeof(MEMBER))) == NULL) {			/* �m�[�h���쐬 */
		printf("���I�������̎擾�Ɏ��s���܂����B\n");
		exit(EXIT_FAILURE);
	}
	sort->next = NULL;
	
	/* �^�[�Q�b�g�����[�g�̐擪�ɐݒ肷�� */
	rTarget = root;
	
	/* �\�[�g���X�g���쐬���� */
	while(rTarget->next != NULL) {
		/* ���[�g���̃m�[�h���\�[�g���ɕ��ʂ��� */
		rTarget = rTarget->next;
		if((newone = (MEMBER*)malloc(sizeof(MEMBER))) == NULL) {		/* �m�[�h���쐬 */
			printf("���I�������̎擾�Ɏ��s���܂����B\n");
			exit(EXIT_FAILURE);
		}
		strncpy_s(newone->id, MEMBER_ID_SIZE + 1, rTarget->id, _TRUNCATE);
		strncpy_s(newone->name, MEMBER_NAME_SIZE + 1, rTarget->name, _TRUNCATE);
		strncpy_s(newone->addr, MEMBER_ADDR_SIZE + 1, rTarget->addr, _TRUNCATE);
		strncpy_s(newone->tel, MEMBER_TEL_SIZE + 1, rTarget->tel, _TRUNCATE);
		strncpy_s(newone->birth, MEMBER_BIRTH_SIZE + 1, rTarget->birth, _TRUNCATE);
		
		/* �m�[�h���\�[�g���X�g�ɑ}������ */
		sTarget = sort;
		while(TRUE) {
			/* ���̃m�[�h������Ȃ�΁A�\�[�g�L�[���`�F�b�N���� */
			if(sTarget->next != NULL) {
				/* �\�[�g�L�[��I������ */
				switch(key) {
				case 1:				/* 1:���ID */
					cmp = strncmp(newone->id, sTarget->next->id, MEMBER_ID_SIZE);
					break;
				case 2:				/* 2:���N���� */
					cmp = strncmp(newone->birth, sTarget->next->birth, MEMBER_BIRTH_SIZE);
					break;
				default:			/* ��O */
					cmp = 0;
					break;
				}
				
				/* �ǉ��m�[�h�̃\�[�g�L�[�̏����A�~���̔���*/
				if(ud == 1) {	/* �����Ƀ\�[�g �ǉ��m�[�h�̃\�[�g�L�[�̔�r���ʂ��������Ȃ�΁A�^�[�Q�b�g�̌��Ƀm�[�h��ǉ� */
					if(cmp < 0) {
						newone->next = sTarget->next;
						sTarget->next = newone;
						break;
					} else {
						sTarget = sTarget->next;
					}
				} else {		/* �~���Ƀ\�[�g �ǉ��m�[�h�̃\�[�g�L�[�̔�r���ʂ��傫���Ȃ�΁A�^�[�Q�b�g�̌��Ƀm�[�h��ǉ�*/
					if(cmp > 0) {
						newone->next = sTarget->next;
						sTarget->next = newone;
						break;
					} else {
						sTarget = sTarget->next;
					}
				}
			} else {
				/* �V�����m�[�h�����X�g�̖����ɒǉ����ďI������ */
				newone->next = NULL;
				sTarget->next = newone;
				break;
			}
		}
	}
	
	/* �\�[�g���X�g�ƃ��[�g���X�g�̃��[�g�����ւ��� */
	temp = root->next;
	root->next = sort->next;
	sort->next = temp;
	
	/* �\�[�g���X�g��������� */
	while(sort != NULL) {
		temp = sort;
		sort = sort->next;
		free(temp);
	}
}

/*
 * �֐���			: int InputUpdateMember(MEMBER *m, MEMBER *mBuf)
 * �@�\				: �yD-1125�z������ύX���͉��
 * ���̓p�����[�^	: MEMBER *m	:�ύX���������m�[�h�ւ̃|�C���^
 * �o�̓p�����[�^	: MEMBER *mBuf	:�ύX����������m�[�h�ւ̃|�C���^
 * �߂�l			: int	:TRUE�i��������擾�j/FALSE�i�����񂪂Ȃ��j
 * ���L����			: �����̉�������Q�l�ɐV���ȉ��������͂���
 */
int InputUpdateMember(MEMBER *m, MEMBER *mBuf)
{
	int retVal = TRUE;
	char buf[MEMBER_NAME_SIZE + STRING_TERMINATOR_SIZE];	/* ������p�o�b�t�@ */
	char date[INPUTUPDATEMEMBER_DATE_BUF_SIZE];			/* ���t�t�H�[�}�b�g�p */

	if(m != NULL) {
		printf("\n");
		printf("�ύX���ڂ���͂��Ă��������B\n");
		printf("�����͍��ڂ͕ύX���܂���B\n");
		printf("%s:%s\n", MEMBER_ID_NAME, m->id);

		/* ���ID���R�s�[���� */
		strncpy_s(mBuf->id, MEMBER_ID_SIZE + 1, m->id, _TRUNCATE);

		/* �������X�V���� */
		printf("%s:%s�@���@", MEMBER_NAME_NAME, m->name);
		GetStr(buf, MEMBER_NAME_SIZE);
		if(strlen(buf) != 0) {
			strncpy_s(mBuf->name, MEMBER_NAME_SIZE + 1, buf, _TRUNCATE);
		} else {
			strncpy_s(mBuf->name, MEMBER_NAME_SIZE + 1, m->name, _TRUNCATE);
		}

		/* �Z�����X�V���� */
		printf("%s:%s�@���@", MEMBER_ADDR_NAME, m->addr);
		GetStr(buf, MEMBER_ADDR_SIZE);
		if(strlen(buf) != 0) {
			strncpy_s(mBuf->addr, MEMBER_ADDR_SIZE + 1, buf, _TRUNCATE);
		} else {
			strncpy_s(mBuf->addr, MEMBER_ADDR_SIZE + 1, m->addr, _TRUNCATE);
		}

		/* �d�b�ԍ����X�V���� */
		printf("%s:%s�@���@", MEMBER_TEL_NAME, m->tel);
		GetStr(buf, MEMBER_TEL_SIZE);
		if(strlen(buf) != 0) {
			strncpy_s(mBuf->tel, MEMBER_TEL_SIZE + 1, buf, _TRUNCATE);
		} else {
			strncpy_s(mBuf->tel, MEMBER_TEL_SIZE + 1, m->tel, _TRUNCATE);
		}


		/* ���N�������X�V���� */
		ConvFormatDate(date, m->birth);
		printf("%s�i'/'������8���j:%s�@���@", MEMBER_BIRTH_NAME, date);
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
 * �֐���			: int DeleteMember(const char *id)
 * �@�\				: �yD-1127�z������폜�m�F���
 * ���̓p�����[�^	: const char *id	:���ID
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:1�i�폜�j/EXIT_NUM�i�폜���Ȃ��j
 * ���L����			: �Ȃ�
 */
int DeleteMember(const char *id)
{
	int retVal = EXIT_NUM;
	MEMBER *target;					/* �^�[�Q�b�g�m�[�h�p */
	MEMBER *del;
	
	/* ���X�g����^�[�Q�b�g�m�[�h���폜���� */
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
		WriteMemberFile();						/* �����񃊃X�g�̃t�@�C�������� */
		printf("\n��������폜���܂����B\n");
		retVal = 1;
	return retVal;
}
/*
 * �֐���			: int Searchtel(const char* tel, MEMBER** m)
 * �@�\				: �yD-1131�z�d�b�ԍ��ŉ��ID����������
 * ���̓p�����[�^	: const char *tel	:��������d�b�ԍ�
 * �o�̓p�����[�^	: MEMBER **m	:�������ꂽ������m�[�h�ւ̃|�C���^
 * �߂�l			: int	;TRUE (������擾����) / FALSE (������擾���s)	
 * ���L����			: �Ȃ�
 */
int Searchtel(const char *tel, MEMBER** m)
{
	int retVal = FALSE;
	MEMBER* target;		/* �����^�[�Q�b�g�m�[�h�p */

	target = root;
	while (target->next != NULL) {
		target = target->next;
		if (strncmp(target->tel, tel, MEMBER_TEL_SIZE) == 0) {
			*m = target;	/* �q�b�g�����f�[�^�̃A�h���X��߂�l�ɐݒ� */
			retVal = TRUE;
			break;
		}
	}
	return retVal;
}