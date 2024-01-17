/**
 * @file list.h
 * @brief 可変長配列を実現するプログラムのヘッダファイル
 * @author tatsumi
 * @date 2024/01/17
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

//! 可変長配列の操作時に拡張・縮小されるインデクスの単位
#define LIST_BUF_SIZE 4

/**
* @struct List
* @brief 可変長配列を定義する構造体
* @details 可変長配列を定義する構造体です．List型変数を操作する場合，list.c で定義された関数を介する必要があります．
*/
typedef struct
{
    //! 要素が文字列である場合はtrue，そうでない場合はfalseをとるメンバ
    bool is_string;
    //! 可変長配列の要素数
    unsigned long size;
    //! 可変長配列の要素のデータサイズ
    unsigned long data_size;
    //! 確保された領域の大きさ
    unsigned long capacity;
    //! 確保された文字列領域の大きさ
    unsigned long allocated;
    //! 可変長配列の先頭要素へのアドレス
    void *base_addr;
} List;

/**
* @fn void init_List(List *_list, const int _data_size, const bool _is_string)
* @brief List型変数を初期化する関数
* @param[out] _list 初期化するList型変数
* @param[in] _data_size 要素1つあたりのデータサイズ
* @param[in] _is_string 要素が文字列である場合はtrue，そうでない場合はfalse
* @return なし
* @details 第1引数に指定されたList型変数を要素となるデータに合わせて初期化します．初期化時，可変長配列として，要素のデータサイズ×4バイトの領域が確保されます．
*/
void init_List(List *_list, const int _data_size, const bool _is_string);
/**
* @fn void free_List(List *_list)
* @brief List型変数が確保した領域を開放する関数
* @param[out] _list 開放するList型変数
* @return なし
* @details 第1引数に指定されたList型変数が確保した領域を開放します．なお，可変長配列の要素ごとにメモリを動的に確保している場合（文字列を除く），それらの領域を確保した後にこの関数を実行してください．
*/
void free_List(List *_list);
/**
* @fn void asList_List(List *_list, const void *_array, const long _size, const long _data_size, const int _is_string, void (*_copy)(const void *, const void *));
* @brief 指定された配列に連動する可変長配列を定義するList型変数を設定する関数
* @param[out] _list 可変長配列を定義するList型変数
* @param[in] _array 可変長配列の基となる配列
* @param[in] _size 配列の要素数
* @param[in] _data_size 配列の要素1つあたりのデータサイズ
* @param[in] _is_string 配列の要素が文字列である場合はtrue，そうでない場合はfalse
* @param[in] _copy 連動方法を記述した関数のポインタ
* @return なし
* @details 第6引数に指定された方法で，第2引数に指定された配列に連動する可変長配列を定義するList型変数を設定します．
* 第6引数がNULLである場合，要素ごとに関数strcpyを用いて連動します．
* なお，第1引数である_listを初期化する必要はありません．
*/
void asList_List(List *_list, const void *_array, const long _size, const long _data_size, const int _is_string, void (*_copy)(const void *, const void *));
/**
* @fn void copy_List(List *_list_dst, const List *_list_src, void (*_copy)(const void *, const void *));
* @brief List型変数をコピーする関数
* @param[out] _list_dst コピー先となるList型変数
* @param[in] _list_src コピー元となるList型変数
* @param[in] _copy コピー方法を記述した関数のポインタ
* @return なし
* @details 第3引数に指定された方法で，第2引数に指定されたList型変数を第1引数に指定されたList型変数にコピーします．
* なお，第3引数がNULLである場合，要素ごとに関数strcpyを用いてコピーします．
*/
void copy_List(List *_list_dst, const List *_list_src, void (*_copy)(const void *, const void *));
/**
* @fn void *get_List(const List *_list, const long _idx);
* @brief 指定された位置にある要素をコピーしたデータのポインタを返す関数
* @param[in] _list 可変長配列を定義するList型変数
* @param[in] _idx 返される要素のインデクス
* @return void* 第2引数に指定された位置にある要素のポインタ
* @details 第2引数に指定された位置にある要素をディープコピーしたデータのポインタを返します．
* void型ポインタで返されるため，キャストする必要があります．
* なお，返されたポインタに格納されたデータは，get_Listを呼び出すごとに更新されるため，
* 取得したデータを長期間扱う場合，呼び出し元でデータをディープコピーする必要があります．
*/
void *get_List(const List *_list, const long _idx);
/**
* void set_List(List *_list, const void *_element, const long _idx);
* @brief 指定された位置にある要素を，指定されたポインタにあるデータで置き換える関数
* @param[inout] _list 可変長配列を定義するList型変数
* @param[in] _elements 指定された位置に格納されるデータのポインタ
* @param[in] _idx 置き換える要素のインデクス
* @return なし
* @details 第3引数に指定された位置にある要素を，第2引数に指定されたポインタが示すデータで置き換えます．
*/
void set_List(List *_list, const void *_element, const long _idx);
/**
* void add_List(List *_list, const void *_element, const long _idx);
* @brief 指定された位置に，指定されたポインタにあるデータをコピーし，追加する関数
* @param[inout] _list 可変長配列を定義するList型変数
* @param[in] _elements 指定された位置に追加するデータのポインタ
* @param[in] _idx 追加する要素のインデクス
* @return なし
* @details 第3引数に指定された位置に，第2引数に指定されたポインタが示すデータをディープコピーし，追加します．
*/
void add_List(List *_list, const void *_elements, const long _idx);
/**
* void set_List(List *_list, const void *_element, const long _idx);
* @brief 指定された位置にある要素を削除する関数
* @param[inout] _list 可変長配列を定義するList型変数
* @param[in] _idx 削除する要素のインデクス
* @return なし
* @details 第2引数に指定された位置にある要素を削除します．
*/
void remove_List(List *_list, const long _idx);
/**
* void push_List(List *_list, const void *_elements);
* @brief 可変長配列の最後に，指定されたポインタにあるデータをコピーし，追加する関数
* @param[inout] _list 可変長配列を定義するList型変数
* @param[in] _elements 可変長配列の最後に追加するデータのポインタ
* @return なし
* @details 可変長配列の最後に，第2引数に指定されたポインタが示すデータをディープコピーし，追加します．
*/
void push_List(List *_list, const void *_elements);
/**
* @fn void *peek_List(const List *_list);
* @brief 可変長配列の最後にある要素をコピーしたデータのポインタを返す関数
* @param[inout] _list 可変長配列を定義するList型変数
* @return void* 可変長配列の最後にある要素のポインタ
* @details 可変長配列の最後にある要素をディープコピーしたデータのポインタを返します．
* void型ポインタで返されるため，キャストする必要があります．
* なお，返されたポインタに格納されたデータは，peek_Listを呼び出すごとに更新されるため，
* 取得したデータを長期間扱う場合，呼び出し元でデータをディープコピーする必要があります．
*/
void *peek_List(const List *_list);
/**
* @fn void *pop_List(List *_list);
* @brief 可変長配列の最後にある要素を削除し，その要素をコピーしたデータのポインタを返す関数
* @param[in] _list 可変長配列を定義するList型変数
* @return void* 可変長配列の最後にある要素のポインタ
* @details 可変長配列の最後にある要素を削除し，その要素をディープコピーしたデータのポインタを返します．
* void型ポインタで返されるため，キャストする必要があります．
* なお，返されたポインタに格納されたデータは，peek_Listを呼び出すごとに更新されるため，
* 取得したデータを長期間扱う場合，呼び出し元でデータをディープコピーする必要があります．
*/
void *pop_List(List *_list);
/**
* @fn qsort_List(List *_list, const long _left, const long _right, int (*compare)(const void *, const void *), void (*_swap)(const void *, const void *));
* @brief 可変長配列を第3引数に指定された比較方法で昇順に並べ替える関数
* @param[inout] _list 可変長配列を定義するList型変数
* @param[in] _left ソートを開始する位置となるインデクス（範囲外のインデクスを指定した場合，0として扱う）
* @param[in] _right ソートを終了する位置となるインデクス（範囲外のインデクスを指定した場合，最後のインデクスを値として扱う）
* @param[in] _compare 2つの要素を比較する方法を記述した関数のポインタ
* @param[in] _swap 2つの要素を交換する方法を記述した関数のポインタ
* @return なし
* @details 可変長配列における第2引数で指定されたインデクスから第3引数で指定されたインデクスまでの範囲を第3引数に指定された比較方法で昇順に並べ替えます．
*/
void qsort_List(List *_list, const long _left, const long _right, int (*compare)(const void *, const void *), void (*_swap)(const void *, const void *));
/**
* @fn long indexOf_List(const List *_list, const void *_elements, int (*_compare)(const void *, const void *));
* @brief 可変長配列内で，指定されたデータと一致すると判定された要素が最初に出現する位置のインデクスを返す関数
* @param[in] _list 可変長配列を定義するList型変数
* @param[in] _elements 検索するデータのポインタ
* @param[in] _compare 2つの要素を比較する方法を記述した関数のポインタ
* @return 指定されたデータが最初に出現する位置のインデクス（指定されたデータが存在しない場合は-1）
* @details 可変長配列内で，第3引数に指定された比較方法で第2引数に指定されたデータと一致すると判定された要素が最初に出現する位置のインデクスを返します．
*/
long indexOf_List(const List *_list, const void *_elements, int (*_compare)(const void *, const void *));
/**
* @fn void inputFile_List(List *_list, const char *_file_name, const char *_token, const bool _LINE_SPLIT);
* @brief ファイルから読み込まれた文字列を分割することにより生成された文字列の配列に連動する可変長配列を定義するList型変数を設定する関数
* @param[out] _list 可変長配列を定義するList型変数
* @param[in] _file_name 読み込むファイルの名前
* @param[in] _token 区切り文字，または文字列（NULLを指定した場合，改行文字として扱う）
* @param[in] _LINE_SPLIT ファイルから読み込まれた文字列を改行ごとに区切る場合はtrue，そうでない場合はfalse
* @return なし
* @details 第3引数に指定された文字列を区切り文字として，
* ファイルから読み込まれた文字列を分割することにより生成された文字列の配列に連動する可変長配列を定義するList型変数を設定します．
* なお，第3引数にNULLが指定された場合，第4引数の値に関わらず改行文字で区切られます．
*/
void inputFile_List(List *_list, const char *_file_name, const char *_token, const bool _LINE_SPLIT);