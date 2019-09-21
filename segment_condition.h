//
//  segment_condition.h
//  sentece_segmenter
//
//  Created by 林重翰 on 2019/9/18.
//  Copyright © 2019 林重翰. All rights reserved.
//
//  定義 所有斷句的情形

#ifndef segment_condition_h
#define segment_condition_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

// 對文章開頭進行過濾，刪除不必要字元
char *filter_sentence_head(char *start_of_the_sentence_ptr);

// 根據自己制訂的斷句規則，找到斷句的位置，並回傳該位置。
char *get_sentence_breakpoint(char *start_of_the_sentence_ptr);

// 萃取出 sentence 內容，回傳完整句子
char *retrieve_sentence(char *start_of_the_sentence_ptr, char *end_of_the_sentence_ptr);

#endif /* segment_condition_h */


/*
 斷句標點符號：
 1. 句號 =>
 1) 單純句號         。
 2) 句號 + 引號      。」 。』
 3) 連續句號
 
 2. 驚嘆號 =>
 1) 單純驚嘆號       ！
 2) 驚嘆號 + 問號    ！？
 3) 驚嘆號 + 引號    ！」 ！』
 4) 連續驚嘆號
 
 4. 刪節號 =>
 1) 單純刪節號       ⋯⋯
 2) 刪節號 + 引號    ⋯⋯」 ⋯⋯』
 3) 連續刪節號
 
 5. 分號 =>
 1) 單純分號        ；
 2) 分號 + 引號     ；」 ；』
 3) 連續分號
 
 6. 換行符號
 
 7. 英文 dot =>
 1) 連續 dot       ......
 2) dot + 引號     .」 .』
 
 8. 英文 驚嘆號 =>
 1) 單純驚嘆號      !
 2) 驚嘆號 + 引號   !」 !』
 3) 連續驚嘆號      !!!!!!
 
 9. 英文 分號 =>
 1) 單純分號        ;
 2) 分號 + 引號     ;」 ;』
 3) 連續分號        ;;;
 */
