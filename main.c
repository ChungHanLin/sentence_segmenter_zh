//
//  main.c
//  sentece_segmenter
//
//  Created by 林重翰 on 2019/9/18.
//  Copyright © 2019 林重翰. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sentence.h"
#include "segment_condition.h"

#define MAX_BUFFER_SIZE 131072
#define true 1
#define false 0

int main() {
    char buffer[MAX_BUFFER_SIZE];
    char body_field[6] = "@body:";
    char *start_of_the_sentence_ptr, *end_of_the_sentence_ptr;
    char *sentence;
    int read_current_line = false;

    // Sentence Struct
    unsigned long leaf_count = 0;
    Sentence *sentence_head = NULL;
    
    FILE *fp = fopen("/Users/lcha105u/Desktop/txt/ettoday.rec", "r");
    FILE *fout = fopen("/Users/lcha105u/Desktop/txt/sort_ettoday.txt", "w");
    
    while(fgets(buffer, MAX_BUFFER_SIZE, fp)){
        // 當遇到 @body 確認接下來為 新聞內容
        // @body: 可能遇到兩種情況 =>
        //  1. @body: + " " + "新聞內容"
        //  2. @body: + "\n"
        //     "新聞內容"
        if(read_current_line == false){
            if(strncmp(buffer, body_field, 6) == 0){
                read_current_line = true;
                // 出現 1 的情況
                if(buffer[6] == ' '){
                    // 指向新聞內容起始位置
                    start_of_the_sentence_ptr = buffer + 7;
                    
                }
                // 理論上應該是 出現 2 的情況，下一行讀進可當作一般內容處理
                else{
                    continue;
                }
            }
        }
        else{
            // 新聞內容範圍直至開頭為 @ 才結束
            if((buffer[0] == '@') && (buffer[1] == '\n')){
                read_current_line = false;
                continue;
            }
            // 若有 '>' 作為開頭的則判定為連結符號
            else if((buffer[0] == '>') && (buffer[1] == '\n')){
                continue;
            }
            else if((buffer[0] == '\n') || (buffer[0] == '\t')){
                continue;
            }
            else{
                // 剔除 buffer 中的亂碼
                // (＊亂碼：當字元 ASCII <= 31 死或 = 127 時則視為控制字元，視為與 content 無關內容)
                filter_garbled(buffer);
                start_of_the_sentence_ptr = buffer;
                
                // 執行完 segmenter 後，若 body_ptr 還不是指向 '\n'，則重複進行呼叫直到 buffer 所有資料皆被進行斷句處理
                while(*start_of_the_sentence_ptr != '\0' && *(start_of_the_sentence_ptr + 1) != '\n'){
                    
                    // 對文章開頭進行過濾，刪除不必要字元
                    start_of_the_sentence_ptr = filter_sentence_head(start_of_the_sentence_ptr);
                    
                    // 若回傳開頭為 '\0' or '\n' 時，則忽略該行
                    if(*start_of_the_sentence_ptr == '\n' || *start_of_the_sentence_ptr == '\0'){
                        break;
                    }
                    
                    // 根據自己制訂的斷句規則，找到斷句的位置，並回傳該位置。
                    end_of_the_sentence_ptr = get_sentence_breakpoint(start_of_the_sentence_ptr);
                    
                    // 萃取出 sentence 內容，回傳完整句子
                    sentence = retrieve_sentence(start_of_the_sentence_ptr, end_of_the_sentence_ptr);
                    
                    // 將 sentence 傳入 二元樹 中，進行統計 or 新增 leaf，回傳 tree 的開頭
                    sentence_head = insert_sentence(sentence, sentence_head, &leaf_count);
                    
                    if(*end_of_the_sentence_ptr == '\n'){
                        break;
                    }
                    else{
                        start_of_the_sentence_ptr = end_of_the_sentence_ptr;
                    }
                }
            }
        }
    }
    
    // 將 tree 使用 inorder traverse，照順序輸出至檔案，同時也 free 掉動態配置之記憶體
    inorder_and_free_memory(sentence_head, fout);

    return 0;
}
