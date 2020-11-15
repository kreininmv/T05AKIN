/* FILE NAME   : T04AKIN.cpp
 * PURPOSE     : Main start module.
 * PROGRAMMER  : Matvei Kreinin,
 * LAST UPDATE : 15.11.2020.
 * NOTE        : None.
 */

#include "akin.h"

/* Plan of making list.
$* 1. Make class tree, with a node and size of tree
$* 2. Add vertex to right and left
$* 3. Add dump for tree
 * 4. Add write tree to the file
 * 5. Add read tree from the file
$* 6. Add game to the akinator
$* 7. Add adding new vertex if akinator did't find the truth
 * 8. Add similar and different ways to two vertexes
 * 9. Automatical save at the ending.
 */
int main(void) {

  mk5::akinator game;
  game.game();
  game.write("BASA.mk5");
  game.dump();
}/* End of 'main' function */