#ifndef AKINH
#define AKINH
/* FILE NAME   : akin.h
 * PURPOSE     : Header module.
 * PROGRAMMER  : Matvei Kreinin,
 * LAST UPDATE : 15.11.2020.
 * NOTE        : None.
 */

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>



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

typedef char data_type;
const data_type POISON = 0;

/* Get string from consol.
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

namespace mk5 {
  class vertex {
  public:
    vertex *left = nullptr, *right = nullptr, *parent = nullptr;
    char data[MAX_STR] = {};
  
    vertex(data_type* data_add): left(nullptr), right(nullptr), parent(nullptr) {
      emit(data, data_add, strlen(data_add) * sizeof(char));
    }

    vertex(vertex* left_add, vertex* right_add, vertex* parent_add, data_type* data_add): left(left_add), right(right_add), parent(parent_add) {
      emit(data, data_add, strlen(data_add) * sizeof(char));
    }

    ~vertex() {
    }

    /*! akinator_initialize vertex
     * \param[in]  data in a left vertex  - const data_type* data_left
     * \param[in]  data in a right vertex - const data_type* data_right
     * \param[in]  data in cur vertex     - const data_type* data_cur
     */
    int akinator_init_vert(data_type* const data_left, data_type* data_right, data_type* data_cur);

    /*! Create new vertex and adding to the left
     * \param[in]  point to the vertex of adding - vertex* cur_vertex
     * \param[in]  data for adding               - const data_type data
     * \param[out] none.
     */
    int push_left(data_type* data);

    /*! Create new vertex and adding to the right
     * \param[in]  point to the vertex of adding - vertex* cur_vertex
     * \param[in]  data for adding               - const data_type data
     * \param[out] none.
     */
    int push_right(data_type* data);

  };

  class tree {
  public:
    /*! Make picture with a graphviz.
     * \param[in]  none.
     * \param[out] none.
     */
    int dump(void);

    /*! Write tree in the file.
     * \param[in]  name of file - const char* FileName
     * \param[out] none
     */
    int write(const char* FileName) {
      file = fopen(FileName, "wb");

      if (file == nullptr)
        return 0;
      fprintf(file, "{It's a base of animals}\n");
      fprintf(file, "{version 1.0}\n");
      fprintf(file, "{ENG}\n");

      write_vertex(root, 0);

      fclose(file);

      return 1;
    }/* End of 'write' function */

  protected:
    vertex* root = nullptr;
    int size_tree = 0;
    
    FILE *file = nullptr;
    tree() {;}

    ~tree() {
      delete_tree(root);
      
      root = nullptr;
      size_tree = 0;
    }

    /*! Print information of cur node.
     * \param[in]  point to node - vetex* node
     * \param[out] none.
     */
    int print_vertex(vertex* node);

    /*! Write cur node in the file
     * \param[in]  point to the node - vertex* node
     * \param[out] none
     */
    int write_vertex(vertex* node, int indent_size) {
      if (indent_size != 0)
        fprintf(file, "%*c[\n", indent_size, ' ');
      else
        fprintf(file, "[\n");
      indent_size += 4;
      
      if (node->right != nullptr && node->left != nullptr) {
        fprintf(file, "%*c?%s?\n", indent_size, ' ', node->data);
        write_vertex(node->left, indent_size);

        write_vertex(node->right, indent_size);
      }
      else {
        fprintf(file, "%*c'%s'\n", indent_size, ' ', node->data);
      }
      
      indent_size -= 4;
      if (indent_size != 0)
        fprintf(file, "%*c[\n", indent_size, ' ');
      else
        fprintf(file, "[\n");
      
      return 1;
    }/*End of 'write_vertex' function */
    
    /*! Delete all vertexes in the tree
     * \param[in]  point to the root - vertex* node
     * \param[out] none
     */
    void delete_tree(vertex* node);
  };

  class akinator: public tree {
    public:

    /*! akinator_initialize a vertex
     * \param[in]  point to the vertex - vertex* cur_vertex
     * \param[out] none
     */
    void akinator_init(vertex* cur_vertex);

    /*! Game for findins answers, adding new answers and questions
     * \param[in]  none
     * \param[out] none
     */
    int game(void) {
      
      if (root == nullptr)
        (root);

      game_loop(root);
      
      return 1;
    }/* End of 'game' function */

    /*! Loop for game mode.
     * \param[in]  point to the current root - vertex* cur_root
     * \param[out] none
     */
    int game_loop(vertex* cur_root) {
      char ans[MAX_STR], qst[MAX_STR];
      char button;

      while (1)
      {
        printf("%s", cur_root->data);
        
        button = getchar();
        getchar();

        printf((button == 'Y' || button == 'y') ? " Yes\n" : " No\n");

        if (button == 0)
          return 1;
        else if (cur_root->right != nullptr && cur_root->left != nullptr) {
          (button == 'Y' || button == 'y') ? cur_root = cur_root->right : cur_root = cur_root->left;
          game_loop(cur_root);

          return 1;
        }
        else if ((button == 'Y' || button == 'y') && cur_root->right == nullptr) {
          printf("I win...\n");

          return 1;
        }
        else if ((button == 'N' || button == 'n') && cur_root->left == nullptr)
        {
          printf("Input a new question:");
          getstr(qst);
          printf("Input a correct answer:");
          getstr(ans);
          
          size_tree += 2;

          cur_root->akinator_init_vert(cur_root->data, ans, qst);
        }
        else
          printf("You need to enter 'n' for (NO) and 'y' for (YES)\n");
      }
    }
  };
}

#endif