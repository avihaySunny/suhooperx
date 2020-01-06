/*******************************************************************************
* Programmer: Avihay
* sll.h
* File: sll header
* Date: ב' מאי 13 16:41:56 IDT 2019
*******************************************************************************/

#ifndef __SLL_H__
#define __SLL_H__

/*typedef int(*ismatch_t)(void *data, void *param);*/

#define UNUSED(a)   ((void)(a))  /* for unusued variables   */

#include <sys/types.h>                 /*For ssize_t usage  */
#include <strings.h>                   /* strcasecmp        */
        /*Color Scheme*/
#define RED       "\x1b[31m"
#define YELLOW    "\x1b[1;33m"  
#define CYAN      "\x1b[36m\x1b[1m"
#define GREEN     "\x1B[32m"
#define MAGENTA   "\x1B[35m"
#define WHITE     "\x1B[37m"
#define RESET     "\x1b[0m"

        /*Debug define */
#ifndef  NDEBUG 
#define DBG(x)  x 
#else 
#define DBG(x) 
#endif

typedef struct singly_list node_t;
 
struct singly_list 
{
    void *data; 
    node_t *next; 
}; 

/* Return pointer to node of type node_t */
node_t *SLLCreateNode(const void *data, node_t *next); 

/* frees the specific node */
void SLLFreeNode(node_t *node); /*done*/

/* frees all the list nodes */
void SLLFreeAll(node_t *head);  /*done*/

/* inserts a block after the index */
node_t *SLLInsertAfter(node_t *where, node_t *node);    

/* inserts a block before the index */
node_t *SLLInsertBefore(node_t *where, node_t *node);

/* removes a block after the index */
node_t *SLLRemoveAfter(node_t *node);                   

/* removes a block before the index returns null if last element*/
node_t *SLLRemoveCurrent(node_t *node);

/* calls a function, given by user.  
*  given function success is 0, fail is > 0 for every node data in list
*  behaviour is undefined for null function, 
*  upon action failure returns failed node.
*/
int SLLForEach(node_t *head, int(*action)(void *data, void *param), 
               void *param, node_t **failed_node);

/* counts how many elements in list */
size_t SLLCount(const node_t *head);                   

/* Function finds using ismatch function (given by user). 
*  for data specified by user. returns NULL if search failed.  
*/
node_t *SLLFind(const node_t *head, int (*ismatch)(const void *data,
                const void *param), const void *param);

/* returns boolean 0 if there is a loop otherwise 1 */
int SLLHasLoop(const node_t *head);             /*done  */

/* given two heads finds if lists are connected, returns NULL is  
*  two lists are forgein/are the same, returns link in case of connected lists 
*/
node_t *SLLFindIntersection(const node_t *head_a, const node_t *head_b);

/* Returns a pointer to the new head */
node_t *SLLFlip(node_t *head);                         

node_t  *FlipRec (node_t *head);

#endif     /* __SLL_H__ */






