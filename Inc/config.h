/*
 * Header for different configuration parameters of the system
 */
#ifndef CONFIG_H_
#define CONFIG_H_

#define BLOCK_BIT_LEN 8
#define BLOCK_BYTE_LEN (BLOCK_BIT_LEN / 8)
#define BLOCK_WORD_LEN (BLOCK_BIT_LEN / 32)
#define BLOCK_SPACE (1 << (BLOCK_BIT_LEN))

#define PART_BIT_LEN (BLOCK_BIT_LEN / 2)
#define PART_BYTE_LEN (PART_BIT_LEN / 8)
#define PART_WORD_LEN (PART_BIT_LEN / 32)
#define SBLOCK_VAL_COUNT 256 //???????????

#define PART_BIT_MASK ((1 << PART_BIT_LEN) - 1)
#define BLOCK_BIT_MASK ((1 << BLOCK_BIT_LEN) - 1)

#define KEY_BIT_LEN PART_BIT_LEN
#define KEY_BYTE_LEN (KEY_BIT_LEN / 8)
#define KEY_WORD_LEN (KEY_BIT_LEN / 32)
#define KEY_SPACE (1 << (KEY_BIT_LEN))

#define MAX_TEXT_NUM 10000

#define BLOCK_ROT 1 //3

#endif /* CONFIG_H_ */
