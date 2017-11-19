/*
 * Header for different configuration parameters of the system
 */
#ifndef CONFIG_H_
#define CONFIG_H_

#define BLOCK_BIT_LEN 8
#define BLOCK_BYTE_LEN (BLOCK_BIT_LEN / 8)
#define BLOCK_WORD_LEN (BLOCK_BIT_LEN / 32)
#define BLOCK_SPACE (1 << BLOCK_BIT_LEN)

#define PART_BIT_LEN (BLOCK_BIT_LEN / 2)
#define PART_BYTE_LEN (PART_BIT_LEN / 8)
#define PART_WORD_LEN (PART_BIT_LEN / 32)

/* for S-box analysis */
#define SBLOCK_BIT_LEN 8
#define SBLOCK_SPACE (1 << SBLOCK_BIT_LEN)
#define SBLOCK_BIT_MASK (SBLOCK_SPACE - 1)

/* for LAX analysis */
#define LAX_BIT_LEN 16
#define LAX_PART_BIT_LEN (LAX_BIT_LEN / 2)
#define LAX_SPACE (1 << LAX_BIT_LEN)
#define LAX_PART_SPACE (1 << LAX_PART_BIT_LEN)
#define LAX_BIT_MASK (LAX_SPACE - 1)
#define LAX_PART_BIT_MASK (LAX_PART_SPACE - 1)

#define PART_BIT_MASK ((1 << PART_BIT_LEN) - 1)
#define BLOCK_BIT_MASK ((1 << BLOCK_BIT_LEN) - 1)

#define KEY_BIT_LEN PART_BIT_LEN
#define KEY_BYTE_LEN (KEY_BIT_LEN / 8)
#define KEY_WORD_LEN (KEY_BIT_LEN / 32)
#define KEY_SPACE (1 << KEY_BIT_LEN)

#define MAX_TEXT_NUM 10000

#define BLOCK_ROT 1 //3

#define FILE_PATH "/media/sf_Alexander/ARX_new_results/"

#define FILE_PATH_LEN 36

#endif /* CONFIG_H_ */
