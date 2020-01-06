/*******************************************************************************
* Programmer: Avihay Asraf
* bst.c
* File: bst code
* Date: 
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* malloc realloc                           */
#include "bst.h"

#define  DEADBEEF ((void*)(0xDEADBEEF))
#define UNUSED(a)   ((void)(a))

typedef struct bst_node bnode_t;
/*--------------------------------------------------------------------------- */
static bnode_t *FindSuitablePlace(const bst_t *tree, const void *data); 
static bnode_t *RunMostRight(iter_t iter);
static bnode_t *RunMostLeft(iter_t iter);
static bnode_t *RunUpTree(iter_t iter, int(*is_son)(iter_t, iter_t)); 
static int NodeCount(const void *data, void *param);
static int IsRightSon(iter_t dad, iter_t son);
static int IsLeftSon(iter_t dad, iter_t son);
static void SwapData(void **a, void **b);

/*----------------------------------------------------------------------------*/
struct binary_search_tree
{
	bnode_t *root;  
	int (*cmp_func)(const void *, const	void *); 	
}; 

struct bst_node
{
	bnode_t *left;
	bnode_t *right; 
	bnode_t *parent; 
	void *data; 
}; 

static iter_t BSTCreateNode(void *data)
{
    bnode_t *node = (bnode_t*)malloc(sizeof(bnode_t));
    if (NULL == node)
    {
        return NULL; 
    }
    
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->data = data;
    
    return node; 
}

bst_t *BSTCreate(int (*compare)(const void *dataA, const void *dataB)) 
{
    bst_t *tree = (bst_t*)malloc(sizeof(bst_t)); 

    if (NULL == tree)   
    {
        return NULL; 
    }
    
    tree->root = BSTCreateNode(DEADBEEF); 
    if (NULL == tree->root)
    {
        free(tree); 
        tree = NULL; 
        return NULL; 
    }
    tree->cmp_func = compare;  
    
    return tree; 
}

int BSTIsEmpty(const bst_t *tree)
{
    assert(tree);
    
    return (NULL == tree->root->left);
}

const void *BSTGetData(const iter_t iter)
{
    assert(iter);

    return iter->data; 
}

 void BSTDestroy(bst_t *tree)
{
    bnode_t *runner = NULL; 
    if (NULL == tree)
    {
        return;
    }
    
    for (runner = BSTBegin(tree); runner != BSTEnd(tree); runner = BSTBegin(tree))
    {
        BSTRemove(runner);
    }

    free(tree->root);
    free(tree); 
    tree = NULL; 
} 

iter_t BSTInsert(bst_t *tree, void *data)
{
    bnode_t *node = NULL; 
    iter_t parent = NULL;  

    assert (tree);
    assert (data); 
    
    node = BSTCreateNode(data);
    if (NULL == node)
    {
        return NULL; 
    }
    
    parent = FindSuitablePlace(tree, data);
    node->parent = parent;
    
    if (parent->data == DEADBEEF)
    {
        parent->left = node; 

        return node; 
    }
    
    if (tree->cmp_func(BSTGetData(parent), data) > 0)
    {
        parent->left = node;       
    }
    
    else
    {
        parent->right = node; 
    }

    return node; 
}

iter_t BSTFind(const bst_t *tree, const void *search_param)
{
    bnode_t *found = NULL; 
    
    assert(tree);
    assert(search_param); 
    
    found = FindSuitablePlace(tree, search_param); 
    
    return ((search_param != found->data) ? (NULL) : (found)); 
}

void *BSTRemove(iter_t iter)
{
    void *data = NULL; 
    bnode_t *swap_node = NULL;

    assert (iter);

    data = iter->data; 
    
    if (iter->left == iter->right)
    {
        if (IsLeftSon(iter->parent, iter))
        {
            iter->parent-> left = NULL; 
        } 
        else
        {
            iter->parent->right = NULL; 
        }   
        
        free(iter); 
        
        return (data);
    }

    else if (NULL != iter->right)
    {
        swap_node = RunMostLeft(iter->right);

        if (IsLeftSon(swap_node->parent, swap_node))
        {
            swap_node->parent->left = swap_node->right; 
        }
        else 
        {
            swap_node->parent->right = swap_node->right; 
        }
        if (NULL != swap_node->right)
        {
            swap_node->right->parent = swap_node->parent; 
        } 
    }
    else 
    {
        swap_node = RunMostRight(iter->left);

        if (IsLeftSon(swap_node->parent, swap_node))
        {
            swap_node->parent->left = swap_node->left; 
        }
        else 
        {
            swap_node->parent->right = swap_node->left; 
        }
        
        if (NULL != swap_node->left)
        {
            swap_node->left->parent = swap_node->parent; 
        } 
    }

    SwapData(&iter->data, &swap_node->data); 
    free(swap_node); 
    swap_node = NULL; 

    return data; 
}
 
int BSTForEach(iter_t from, iter_t to, 
                int (*action)(const void *data, void *param), void *param)
{
    int status = 0; 
    
    assert(from && to);
    
    while (from != to)
    {   
        status = action(BSTGetData(from), param); 
        if (0 != status)
        {
            return status; 
        }
        
        from = BSTNext(from);
    }

    return 0;
}
															
iter_t BSTBegin(const bst_t *tree) 
{
   assert(tree); 
   
   return RunMostLeft(tree->root);
}

iter_t BSTEnd(const bst_t *tree) 
{
    assert(tree);
    
    return (tree->root); 
}

iter_t BSTNext(iter_t iter)
{
    assert(iter);
    if (NULL != iter->right)
    {
        return(RunMostLeft(iter->right));  
    } 

    return RunUpTree(iter, IsRightSon);   
}

iter_t BSTPrev(iter_t iter) 
{
    assert(iter);

    if (NULL != iter->left)
    {
        return RunMostRight(iter->left);
    }

    return RunUpTree(iter, IsLeftSon);
}

size_t BSTSize(const bst_t *tree)
{
    size_t count = 0; 

    assert(tree); 

    BSTForEach(BSTBegin(tree), BSTEnd(tree), NodeCount, &count);
    
    return (count);
}

/*----------------HELPER FUNCTIONS---------------------------------- */

static int NodeCount(const void *data, void *param)
{
    UNUSED(data); 
    ++*(size_t*)param; 
    
    return (0);
}

static iter_t FindSuitablePlace(const bst_t *tree, const void *data)
{
    bnode_t *parent = NULL;
    bnode_t *runner = NULL; 
    int cmp = 0; 

    assert(tree && data); 
    
    parent = tree->root; 
    runner = parent->left;

    while ((NULL != runner) && (0 != (cmp = (tree->cmp_func(BSTGetData(runner), data))))) 
    {
        parent = runner;
        if (cmp > 0 )
        {
            runner = runner->left; 
        }    
        else
        {
            runner = runner->right; 
        }

    }

    if (NULL != runner)
    {
        return runner; 
    } 
    
    return parent; 

}

static void SwapData(void **a, void **b)
{
    void *tmp = *a; 
    *a        = *b; 
    *b        = tmp;  
}

static iter_t RunMostLeft(iter_t iter)
{
    assert(iter);

    while (iter->left != NULL)
    { 
        iter = iter->left;  
    }

    return iter;
}

static iter_t RunMostRight(iter_t iter)
{
    assert(iter);

    while (NULL != iter->right)
    { 
        iter = iter->right;  
    }

    return iter;
}

static int IsRightSon(iter_t dad, iter_t son)
{
    assert(dad && son);

    return (dad->right == son); 
}


static int IsLeftSon(iter_t dad, iter_t son)
{
    assert(dad && son);

    return (dad->left == son); 
}

static iter_t RunUpTree(iter_t iter, int(*is_son)(iter_t, iter_t))
{
    assert(iter && is_son);  
    
    while (NULL != iter->parent  && is_son(iter->parent, iter))
    {
        iter = iter->parent; 
    } 

    return iter->parent; 
}









