//
//  sentence.c
//  sentece_segmenter
//
//  Created by 林重翰 on 2019/9/19.
//  Copyright © 2019 林重翰. All rights reserved.
//

// 先用普通的 二元樹 實作 -> 當前版本仍需與 array 組成後進行 quicksort 比較速度。
// 如果可以聽說 B-tree 很厲害，可以妥善解決 二元樹 不平衡之問題

#include "sentence.h"

// 將 sentence 傳入 二元樹 中，進行統計 or 新增 leaf，回傳 tree 的開頭
Sentence *insert_sentence(char *sentence, Sentence *sentence_head, unsigned long *leaf_count){
    if(sentence_head == NULL){
        sentence_head = create_sentence_leaf(sentence);
        fprintf(stderr, "Head %lu\n", *leaf_count);
        *leaf_count += 1;
    }
    else{
        Sentence *sentence_ptr = sentence_head;
        Sentence *prev_ptr;
        int compare;
        
        while(sentence_ptr){
            compare = strcmp(sentence, sentence_ptr->content);
            prev_ptr = sentence_ptr;
            if(compare > 0){
                sentence_ptr = sentence_ptr->right;
            }
            else if(compare < 0){
                sentence_ptr = sentence_ptr->left;
            }
            else{
                sentence_ptr->appearTime += 1;
                break;
            }
        }
        if(!sentence_ptr){
            sentence_ptr = create_sentence_leaf(sentence);
            
            // compare 為記錄最後一次進行 strcmp 之結果，用於判斷是由 setence_ptr 為父節點的 left or right leaf
            if(compare > 0){
                prev_ptr->right = sentence_ptr;
            }
            else{
                prev_ptr->left = sentence_ptr;
            }
            fprintf(stderr, "Insert %lu\n", *leaf_count);
            *leaf_count += 1;
        }
    }
    
    return sentence_head;
}

// 宣告葉節點，進行記憶體分配， assign attribute
Sentence *create_sentence_leaf(char *sentence){
    Sentence *new_leaf;
    
    new_leaf = (Sentence *)malloc(sizeof(Sentence));
    new_leaf->content = sentence;
    new_leaf->appearTime = 1;
    new_leaf->left = new_leaf->right = NULL;
    
    return new_leaf;
}

// 將 tree 使用 inorder traverse，照順序輸出，同時也 free 掉動態配置之記憶體
void inorder_and_free_memory(Sentence *sentence_ptr, FILE *fout){
    if(!sentence_ptr){
        return;
    }
    
    inorder_and_free_memory(sentence_ptr->left, fout);
    fprintf(fout, "%lu\t%s\n", sentence_ptr->appearTime, sentence_ptr->content);
    inorder_and_free_memory(sentence_ptr->right, fout);
    
    free(sentence_ptr->content);
    free(sentence_ptr);
    
    return;
}
