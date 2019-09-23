//
//  sentence.h
//  sentece_segmenter
//
//  Created by 林重翰 on 2019/9/19.
//  Copyright © 2019 林重翰. All rights reserved.
//
//  Introduction: 定義結構與 BST 進行實作之方法

#ifndef sentence_h
#define sentence_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sentence{
    char *content;              // 指向經由斷句後儲存的動態記憶體
    unsigned long appearTime;   // 該句總共出現的次數
    struct Sentence *left;      // 指向左子樹
    struct Sentence *right;     // 指向右子樹
}Sentence;

// 將 sentence 傳入 二元樹 中，進行統計 or 新增 leaf，回傳 tree 的開頭
Sentence *insert_sentence(char *sentence, Sentence *sentence_head, unsigned long *leaf_count);

// 宣告葉節點，進行記憶體分配， assign attribute
Sentence *create_sentence_leaf(char *sentence);

// 將 tree 使用 inorder traverse，照順序輸出，同時也 free 掉動態配置之記憶體
void inorder_and_free_memory(Sentence *sentence_ptr, FILE* fout);

#endif /* sentence_h */
