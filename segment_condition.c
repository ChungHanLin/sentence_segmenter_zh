//
//  segment_condition.c
//  sentece_segmenter
//
//  Created by 林重翰 on 2019/9/18.
//  Copyright © 2019 林重翰. All rights reserved.
//

#include "segment_condition.h"

// 剔除 buffer 中的亂碼
// (＊亂碼：當字元 ASCII <= 31 死或 = 127 時則視為控制字元，視為與 content 無關內容)
void filter_garbled(char *line_buffer){
    char *buffer_in, *buffer_out;
    
    buffer_in = buffer_out = line_buffer;
    while(*buffer_in != '\0'){
        if((*buffer_in <= 31 && *buffer_in >= 0) || *buffer_in == 127){
            buffer_in++;
        }
        else{
            *buffer_out = *buffer_in;
            buffer_out++;
            buffer_in++;
        }
        
    }
    *buffer_out = '\0';
}

// 對文章開頭進行過濾，刪除不必要字元
char *filter_sentence_head(char *start_of_the_sentence_ptr){
    char *ptr = start_of_the_sentence_ptr;
    
    while(*ptr != '\0'){
        if(*ptr == ' ' || *ptr == '>' || *ptr == '.' || *ptr == ',' ||
           *ptr == ';' || *ptr == ':' || *ptr == '!' || *ptr == '?'){
            ptr++;
        }
        else if((strncmp("▲", ptr, 3) == 0) || (strncmp("►", ptr, 3) == 0) ||
                (strncmp("▼", ptr, 3) == 0) || (strncmp("，", ptr, 3) == 0) ||
                (strncmp("＞", ptr, 3) == 0) || (strncmp("、", ptr, 3) == 0) ||
                (strncmp("：", ptr, 3) == 0) || (strncmp("　", ptr, 3) == 0) ||
                (strncmp("｀", ptr, 3) == 0) || (strncmp("；", ptr, 3) == 0)){
            ptr = ptr + 3;
        }
        else{
            break;
        }
    }
    
    return ptr;
}

// 根據自己制訂的斷句規則，找到斷句的位置，並回傳該位置。
char *get_sentence_breakpoint(char *start_of_the_sentence_ptr){
    char *end_of_the_sentence_ptr;
    int extend_sentence = false;
    
    end_of_the_sentence_ptr = start_of_the_sentence_ptr;
    
    while(*end_of_the_sentence_ptr != '\0' && *end_of_the_sentence_ptr != '\n'){
        if((strncmp("。", end_of_the_sentence_ptr, 3) == 0) ||
           (strncmp("！", end_of_the_sentence_ptr, 3) == 0) ||
           (strncmp("？", end_of_the_sentence_ptr, 3) == 0) ||
           (strncmp("...", end_of_the_sentence_ptr, 3) == 0) ||
           (strncmp("；", end_of_the_sentence_ptr, 3) == 0)){
            end_of_the_sentence_ptr += 3;
            if(extend_sentence == false){
                extend_sentence = true;
            }
        }
        else if(strncmp("⋯⋯", end_of_the_sentence_ptr, 6) == 0){
            end_of_the_sentence_ptr += 6;
            if(extend_sentence == false){
                extend_sentence = true;
            }
        }
        else if(*end_of_the_sentence_ptr == '.' || *end_of_the_sentence_ptr == '?' || *end_of_the_sentence_ptr == '!'){
            end_of_the_sentence_ptr++;
            if(extend_sentence == false){
                extend_sentence = true;
            }
        }
        else if(extend_sentence == true){
                if((strncmp("」", end_of_the_sentence_ptr, 3) == 0) || (strncmp("』", end_of_the_sentence_ptr, 3) == 0) ||
                   (strncmp("｣", end_of_the_sentence_ptr, 3) == 0)){
                    end_of_the_sentence_ptr += 3;
                }
                else if(*end_of_the_sentence_ptr == '"' || *end_of_the_sentence_ptr == ' '){
                    end_of_the_sentence_ptr++;
                }
                else{
                    break;
                }
        }
        else{
            end_of_the_sentence_ptr++;
        }
    }
    
    return end_of_the_sentence_ptr;
}


// 萃取出 sentence 內容，回傳完整句子
char *retrieve_sentence(char *start_of_the_sentence_ptr, char *end_of_the_sentence_ptr){
    // 動態宣告記憶體 sentence，程式結束前需將 sentence_list 中的 sentence 欄位一一執行 free()
    char *sentence = (char *)malloc(end_of_the_sentence_ptr - start_of_the_sentence_ptr + 1);
    char *ptr, *sentence_ptr;
    
    sentence_ptr = sentence;
    
    for(ptr = start_of_the_sentence_ptr; ptr != end_of_the_sentence_ptr; ptr++){
        *sentence_ptr = *ptr;
        sentence_ptr++;
    }
    
    *sentence_ptr = '\0';
    
    return sentence;
}
