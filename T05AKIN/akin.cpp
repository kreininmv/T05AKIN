/* FILE NAME   : T04AKIN.cpp
 * PURPOSE     : Main start module.
 * PROGRAMMER  : Matvei Kreinin,
 * LAST UPDATE : 15.11.2020.
 * NOTE        : None.
 */

#include "akin.h"

/*! Add data to the vertex
 * \param[in]  point of data for add - const void* data_add
 * \param[out] none.
 */
int emit(void* source, void* data_add, int size) {
  memcpy(source, data_add, size);
  return 1;
}/* End of 'emit' function */

/*! akinator_initialize vertex
 * \param[in]  data in a left vertex  - data_type* data_left
 * \param[in]  data in a right vertex - data_type* data_right
 * \param[in]  data in cur vertex     - data_type* data_cur
 */
int mk5::vertex::akinator_init_vert(data_type* data_left, data_type* data_right, data_type* data_cur) {
  
  push_left(data_left);
  push_right(data_right);
  emit(data, data_cur, strlen(data_cur) * sizeof(char));

  return 1;
}/* End of 'akinator_init_vert' function */

/*! Create new vertex and adding to the left
 * \param[in]  point to the vertex of adding - vertex* cur_vertex
 * \param[in]  data for adding               - const data_type data
 * \param[out] none.
 */
int mk5::vertex::push_left(data_type* data) {
  left = new vertex(nullptr, nullptr, this, data);
  
  return 1;
}/* End of 'push_left' function */

/*! Create new vertex and adding to the right
 * \param[in]  point to the vertex of adding - vertex* cur_vertex
 * \param[in]  data for adding               - const data_type data
 * \param[out] none.
 */
int mk5::vertex::push_right(data_type* data) {
  right = new vertex(nullptr, nullptr, this, data);

  return 1;
}/* End of 'push_right' function */

/*! Print information of cur node.
 * \param[in]  point to node - vetex* node
 * \param[out] none.
 */
int mk5::tree::print_vertex(vertex* node) {
 
  static int num_vertex = size_tree;
  num_vertex--;

  if (num_vertex < 1)
    return 0;
  
  if (node->right != nullptr) {
    fprintf(file, "struct%i [style=\"filled\", fillcolor=\"#9cfff4\", label=\"<f0> NO | <f1> data (%s) | <f2> YES \"];\n", (int)node, node->data);
    fprintf(file, "struct%i:f2 -> struct%i:f1;\n  ", (int)node, (int)(node->right));
    
    print_vertex(node->right);
  }

  if (node->left != nullptr) {
    fprintf(file, "struct%i [style=\"filled\", fillcolor=\"#9cfff4\", label=\"<f0> NO | <f1> data (%s) | <f2> YES \"];\n", (int)node, node->data);
    fprintf(file, "struct%i:f0 -> struct%i:f1;\n  ", (int)node, (int)(node->left));
    
    print_vertex(node->left);
  }

  if (node->right == nullptr && node->left == nullptr)
    fprintf(file, "struct%i [style=\"filled\", fillcolor=\"#89F09B\", label=\"<f0> NO | <f1> data (%s) | <f2> YES \"];\n", (int)node, node->data);

  return 1;
}/* End of 'print' fucntion */

/*! Delete all vertexes in the tree
 * \param[in]  point to the root - vertex* node
 * \param[out] none
 */
void mk5::tree::delete_tree(vertex* node) {
  if (node->left != nullptr)
    delete_tree(node->left);
  if (node->right != nullptr)
    delete_tree(node->right);

  delete node;
}/* End of 'delete_tree' function */

/*! Make picture with a graphviz.
 * \param[in]  none.
 * \param[out] none.
 */
int mk5::tree::dump(void) {
  static int old_size = size_tree;

  file = fopen("tree.dot", "wb");

  if (file == nullptr)
    return 0;
  fprintf(file, "digraph G{\n");


  fprintf(file, "node [color=\"#000000\", shape=record];\n");
  fprintf(file, "struct%i [style=\"filled\", fillcolor=\"#FF019A\", label=\"<f0> NO  |<f1> data (%s)\ | <f2> YES\"];\n", (int)root, root->data);
  fprintf(file, "edge[color = \"black\"];\n");

  if (root->right != nullptr) {
    fprintf(file, "struct%i:f2 -> struct%i:f1;\n  ", (int)root, (int)(root->right));
    
    print_vertex(root->right);
  }

  if (root->left != nullptr) {
    fprintf(file, "struct%i:f0 -> struct%i:f1;\n  ", (int)root, (int)(root->left));
    
    print_vertex(root->left);
  }

  fprintf(file, "}");
  fclose(file);
  if (system("C:\\Users\\MK5\\Desktop\\MIPT\\Programming\\Graphviz\\bin\\dot.exe -Tpdf"
    " C:\\Users\\MK5\\Desktop\\MIPT\\Programming\\T05AKIN\\T05AKIN\\tree.dot "
    "> C:\\Users\\MK5\\Desktop\\MIPT\\Programming\\T05AKIN\\T05AKIN\\TREE\\tree_out.pdf"))
    assert(0);

  size_tree = old_size;

  return 1;
}/* End of 'dump' function */

/* akinator_initialize a vertex
 * \param[in]  point to the vertex - vertex* cur_vertex
 * \param[out] none
 */
void mk5::akinator::akinator_init(vertex* cur_vertex) {
  char ans[MAX_STR], qst[MAX_STR], false_ans[MAX_STR];

  printf("Your tree is clear!!!\n");

  printf("Add new question for it: ");
  getstr(qst);

  printf("Add new answer for it: ");
  getstr(ans);

  printf("Add false answer for it: ");
  getstr(false_ans);

  size_tree += 3;
  root = new vertex(qst);
  root->push_left(false_ans);
  root->push_right(ans);
  root->parent = nullptr;

}/* End of 'akinator_init' function */

/* Get string from consol.
 * \param[in]  point to the string - char* str
 * \param[out] none
 */
void getstr(char* str) {
  INT i = 0;
  CHAR c;

  while ((c = getchar()) != '\n')
    if (str != nullptr && i < MAX_STR - 1)
      str[i++] = c;
  if (str != nullptr && i < MAX_STR)
    str[i] = 0;
}/* End of 'getstr' function */