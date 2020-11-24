/* FILE NAME   : vertex.cpp
 * PURPOSE     : Module of vertex class.
 * PROGRAMMER  : Matvei Kreinin,
 * LAST UPDATE : 19.11.2020.
 * NOTE        : None.
 */

#include "akin.h"

/*! Create new vertex and adding to the left
 * \param[in]  point to the vertex of adding - vertex* cur_vertex
 * \param[in]  data for adding               - const data_type data
 * \param[in]  status of memory in vertex    - status_vertex type
 * \param[out] none.
 */
int mk5::vertex::push_left(data_type* data, status_vertex type) {
  
  if (left != nullptr)
    return 0;
    
  left = new vertex(nullptr, nullptr, this, data, type);

  return 1;
}/* End of 'push_left' function */

/*! Create new vertex and adding to the right
 * \param[in]  point to the vertex of adding - vertex* cur_vertex
 * \param[in]  data for adding               - const data_type data
 * \param[in]  status of memory in vertex    - status_vertex type
 * \param[out] none.
 */
int mk5::vertex::push_right(data_type* data, status_vertex type) {
  
  if (right != nullptr)
    return 0;

  right = new vertex(nullptr, nullptr, this, data, type);

  return 1;
}/* End of 'push_right' function */

/*! Push to data to vertex
 * \param[in]  data for adding            - data_type* new_data
 * \param[in]  status of memory in vertex - status_vertex type
 * \param[out] none.
 */
int mk5::vertex::push(data_type* new_data, status_vertex type) {
  
  if (status == need_free)
    delete[] data;

  if (type == no_need_free)
    data = new_data;
  else if (type == need_free) {
    data = new data_type[MAX_STR];
    emit(data, new_data, strlen(new_data));
  }

  return 1;
}/* End of 'push' function */

/*! Add data to the vertex
 * \param[in]  point of data for add - const void* data_add
 * \param[out] none.
 */
int emit(void* source, void* data_add, int size) {

  memcpy(source, data_add, size);
  return 1;
}/* End of 'emit' function */

/*! Get string from console.
 * \param[in]  point to the string - char* str
 * \param[out] none
 */
void getstr(char* str) {
  
  int i = 0;
  char c;

  while ((c = getchar()) != '\n')
    if (str != nullptr && i < MAX_STR - 1)
      str[i++] = c;

  if (str != nullptr && i < MAX_STR)
    str[i] = 0;

}/* End of 'getstr' function */