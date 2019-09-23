//
//  segment_condition.h
//  sentece_segmenter
//
//  Created by 林重翰 on 2019/9/18.
//  Copyright © 2019 林重翰. All rights reserved.
//
//  Introduction: 對讀入的資料進行可用資訊的萃取

#ifndef segment_condition_h
#define segment_condition_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

// 剔除 buffer 中的亂碼
// (＊亂碼：當字元 ASCII <= 31 死或 = 127 時則視為控制字元，視為與 content 無關內容)
void filter_garbled(char *line_buffer);

// 對文章開頭進行過濾，刪除不必要字元
char *filter_sentence_head(char *start_of_the_sentence_ptr);

// 根據自己制訂的斷句規則，找到斷句的位置，並回傳該位置。
char *get_sentence_breakpoint(char *start_of_the_sentence_ptr);

// 萃取出 sentence 內容，回傳完整句子
char *retrieve_sentence(char *start_of_the_sentence_ptr, char *end_of_the_sentence_ptr);

#endif /* segment_condition_h */
