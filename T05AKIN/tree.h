#ifndef TREEH
#define TREEH
/* FILE NAME   : tree.h
 * PURPOSE     : Header module.
 * PROGRAMMER  : Matvei Kreinin,
 * LAST UPDATE : 19.11.2020.
 * NOTE        : None.
 */
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#include "onegin.h"

/* Debug memory allocation support */
#ifndef NDEBUG 
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h> 

#define SetDbgMemHooks()                                           \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))      

static class __Dummy
{
public:
  /* Class constructor */
  __Dummy(VOID)
  {
    SetDbgMemHooks();
  } /* End of '__Dummy' constructor */
} __ooppss;

#endif /* _DEBUG */ 

#ifndef NDEBUG
#  ifdef _CRTDBG_MAP_ALLOC 
#    define new new(_NORMAL_BLOCK, __FILE__, __LINE__) 
#  endif /* _CRTDBG_MAP_ALLOC */ 
#endif /* _DEBUG */

#define MAX_STR 100
#define COMMAND_LEN 300
typedef char data_type;
const char ZERO = 0;

/*! Get string from consol.
 * \param[in]  point to the string - char* str
 * \param[out] none
 */
void getstr(char* str);

/*! Add data to the vertex
 * \param[in]  point of data for add - const void* data_add
 * \param[out] none.
 */
int emit(void* source, void* data_add, int size);

//left  - NO
//right - YES
enum status_vertex {
  clear        = 0,
  no_need_free = 1,
  need_free    = 2

};

namespace mk5 {
    
  class vertex {
  public:
    vertex *left = nullptr, *right = nullptr;
    vertex* parent = nullptr;

    status_vertex status = clear;
    char *data   = nullptr;

    vertex(data_type* data_add, status_vertex type) : left(nullptr), right(nullptr), parent(nullptr), status(type) {
      if (type == need_free) {
        data = new data_type[MAX_STR];
        emit(data, data_add, strlen(data_add));
      }
      else if (type == no_need_free)
        data = data_add;
    }

    vertex(vertex* left_add, vertex* right_add, vertex* parent_add, data_type* data_add, status_vertex type) 
      : left(left_add), right(right_add), parent(parent_add), status(type) {
      if (type == need_free) {
        data = new data_type[MAX_STR];
        emit(data, data_add, strlen(data_add));
      }
      else if (type == no_need_free)
        data = data_add;
    }

    /*!Create new vertex and adding to the left
     * \param[in]  point to the vertex of adding - vertex * cur_vertex
     * \param[in]  data for adding - const data_type data
     * \param[in]  status of memory in vertex - status_vertex type
     * \param[out] none.
     */
    int push_left(data_type* data, status_vertex type);

    /*! Create new vertex and adding to the right
     * \param[in]  point to the vertex of adding - vertex* cur_vertex
     * \param[in]  data for adding               - const data_type data
     * \param[in]  status of memory in vertex    - status_vertex type
     * \param[out] none.
     */
    int push_right(data_type* data, status_vertex type);

    /*! Push to data to vertex
     * \param[in]  data for adding            - data_type* new_data
     * \param[in]  status of memory in vertex - status_vertex type
     * \param[out] none.
     */
    int push(data_type* new_data, status_vertex type);
  };

  class tree {
  public:
    vertex* root = nullptr;
    int size_tree = 0;
    char dump_name[MAX_STR] = "";
  

  private:
    line *lines = nullptr, buf = {};
    int num_lines = 0;

    tree operator= (const tree& copy) = delete;
    tree(const tree& copy)            = delete;

  public:
    tree() = default;
    ~tree() {
      if (root != nullptr)
        delete_tree(root);
      
      if (buf.str != nullptr) {
        free(buf.str);
        free(lines);
        buf.len = num_lines = 0;
        buf.str = nullptr;
        lines = nullptr;
      }

      root = nullptr;
      size_tree = 0;
    }


    int dump(void);

    int write(const char* FileName);
   
    int read(const char* FileName);
    
    void delete_tree(vertex* node);

    mk5::line* find_node(data_type* data);

    int init(data_type* data);
    
    int verification(void);

  private:
    int verification_node(vertex* son, vertex* father);

    int auxiliary_find_node(data_type* data, mk5::line *path, vertex* cur_root);

    int make_parent(vertex* son, vertex* father);

    int print_vertex_dump(vertex* node, int num_vertex, FILE* file);

    vertex* read_vertex(int &cur_line, mk5::line* line, vertex* parent);

    int write_vertex(vertex* node, int indent_size, FILE* file);
  };
}
#endif