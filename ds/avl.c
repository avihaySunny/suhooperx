/*******************************************************************************
* Programmer: Avihay Asraf
* avl.c
* File: avl code
* Date: 
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <sys/types.h>      /* ssize_t                                  */

#include "avl.h"

#define  DEADBEEF ((void*)(0xDEADBEEF))
#define UNUSED(a)   ((void)(a))
#define MAX(a,b)    ((a > b) ? (a) : (b)) 

typedef struct avl_node avl_node_t;

struct avl
{
    int (*cmp)(const void *data, const void *key);
     avl_node_t *root;  
};

struct avl_node
{
    void *data;
    avl_node_t *child[2];
    ssize_t height;
}; 
/* ----------------------------------HELPER FUNCS- -------------------------- */
        /*FOR AVLDestroy HELPER*/
static void AVLDestroyNodes(avl_node_t *node);

static avl_node_t *AVLCreateNode(const void *data);

        /*AVLSIZE HELPER*/
static int NodeCount(const void *data, void *param);

        /*ForEachNode HELPER*/
int ForEachNode(avl_node_t *node, int (*action)(const void *data, void *param), void *param);

         /*AVLRemove :HELPER*/
static avl_node_t *FindMin(avl_node_t *node);
static avl_node_t *DeleteNode(avl_t *tree , avl_node_t *node, const void *data);
static avl_node_t *Finder(avl_node_t *node, const avl_t *tree, const void *key);

static void InsertNode(avl_t *tree, avl_node_t *candidate, avl_node_t *to_insert);

/*--------------------- Balacing Functions :  ---------------------------------*/
static void AVLBalanceTree(avl_node_t *node);

ssize_t GetNodeHeight(avl_node_t *node);
void UpdateNodeHeight(avl_node_t *node);

static void RotateLeft(avl_node_t *node); 
static void RotateRight(avl_node_t *node); 

static void SwapData(void **dataA, void **dataB);
/* --------------------------------------------------------------------------------- */

avl_t *AVLCreate(int (*compare)(const void *data, const void *key)) 
{
    avl_t *tree = (avl_t*)malloc(sizeof(avl_t)); 
    if (NULL == tree)
    {
        return NULL; 
    }

    tree->root = NULL; 
    tree->cmp = compare;

    return tree; 
}
/* --------------------------------------------------------------------------------- */
static avl_node_t *AVLCreateNode(const void *data)
{
    avl_node_t *node = NULL; 
    
    node = (avl_node_t*)malloc(sizeof(avl_node_t));
    if (NULL == node)
    {
        return node; 
    }

    node->data = (void*)data; 
    node->child[0] = NULL; 
    node->child[1] = NULL; 
    node->height = 0; 

    return node;
}
/* --------------------------------------------------------------------------------- */
void AVLDestroy(avl_t *tree)
{
    if (NULL == tree)
    {
        return; 
    }

    AVLDestroyNodes(tree->root);
    tree->root = NULL; 
    free (tree);
    tree = NULL;    
}
/* --------------------------------------------------------------------------------- */

static void AVLDestroyNodes(avl_node_t *node)
{
    if (NULL == node)
    {
        return; 
    }
    
    AVLDestroyNodes(node->child[0]); 
    AVLDestroyNodes(node->child[1]);

    free(node); 
    node = NULL;  
}
/* --------------------------------------------------------------------------------- */

int AVLIsEmpty(const avl_t *tree) 
{
    return (tree->root == NULL); 
}
/* --------------------------------------------------------------------------------- */

int AVLInsert(avl_t *tree, void *key)
{
    avl_node_t *node = NULL; 
   
    assert (tree); 
    assert (key); 
    
    node = AVLCreateNode(key); 
    if (NULL == node)
    {
        return 1; 
    }

    if (NULL == tree->root)
    {
        tree->root = node; 
        return 0; 
    }

    InsertNode(tree, tree->root, node);
    
    return 0; 
}

/* --------------------------------------------------------------------------------- */

static void InsertNode(avl_t *tree, avl_node_t *candidate, avl_node_t *to_insert)
{
    int cmp = 0; 
    
    assert(tree);
    assert(candidate); 
    assert(to_insert); 

    cmp = tree->cmp(candidate->data, to_insert->data) < 0 ; 
    if (NULL != candidate->child[cmp])
    {
        InsertNode(tree, candidate->child[cmp], to_insert);
    }
    else
    {
        candidate->child[cmp] = to_insert; 
    }

    AVLBalanceTree(candidate);  
    UpdateNodeHeight(candidate);
}

/* --------------------------------------------------------------------------------- */

ssize_t GetNodeHeight(avl_node_t * node)
{
    if (NULL == node)
    {
        return -1; 
    }

    return node->height; 
}

/* --------------------------------------------------------------------------------- */

void UpdateNodeHeight(avl_node_t *node)
{
    if (NULL == node)
    {
        return;
    }
    
    node->height = MAX(GetNodeHeight(node->child[0]), GetNodeHeight(node->child[1])) + 1; 
}

/* --------------------------------------------------------------------------------- */

void AVLRemove(avl_t *tree, const void *key)
{
    assert(tree);
    assert(key); 

    tree->root = DeleteNode(tree, tree->root, key);
}

/* --------------------------------------------------------------------------------- */

static avl_node_t *DeleteNode(avl_t *tree , avl_node_t *node, const void *data)
{
    avl_node_t *to_replace = NULL;   
    int cmp = 0; 
    
    if (node == NULL)
    {
        return NULL; 
    }

    if (tree->cmp(node->data, data) > 0)
    {
        node->child[0] = DeleteNode(tree ,node->child[0], data);
    }
    else if (tree->cmp(node->data, data) < 0)
    {
        node->child[1] = DeleteNode(tree, node->child[1], data);
    }
    else
    {
             /*No child to consider*/
        if (node->child[0] == node->child[1])
        {
            free(node); 
            node = NULL; 
            return node;
        }
            /*one child */
        else if (NULL == node->child[0] || NULL == node->child[1] )
        {
            if (NULL == node->child[0])
            {
                to_replace = node->child[1];
            }
            else
            {
                to_replace = node->child[0]; 
            }

            free(node);
            node = NULL; 

            return to_replace; 
        }
            /*case there's two child*/
        else
        {
            to_replace = FindMin(node->child[1]); 
            node->data = to_replace->data; 
            node->child[1] = DeleteNode(tree ,node->child[1], to_replace->data);
            
        }
    }

    UpdateNodeHeight(node);
    AVLBalanceTree(node);
    UpdateNodeHeight(node);

    return node;
} 

/* --------------------------------------------------------------------------------- */

static avl_node_t *FindMin(avl_node_t *node)
{
    if (NULL == node->child[0])
    {
        return node; 
    }    

    return FindMin(node->child[0]);
}

/* --------------------------------------------------------------------------------- */
int AVLForEach(const avl_t *tree, 
    int (*action)(const void *data, void *param), void *param)
{
    assert(tree);

    return ForEachNode(tree->root, action, param);
}

/* --------------------------------------------------------------------------------- */

int ForEachNode(avl_node_t *node, int (*action)(const void *data, void *param), void *param)
{
 int result = 0;

    if (NULL == node)
    {
        return 0; 
    }

    if (0 != action(node->data, param)) /* PREORDER */
    {
        return 1; 
    }

    result = ForEachNode(node->child[0],  action, param);
    if (1 == result)
    {
        return result;
    }
    #if 0
    if (0 != action(node->data, param)) /* INORDER */
    {
        return 1; 
    }
    #endif
    result = ForEachNode(node->child[1], action, param);
    
    return result; 
}

/* --------------------------------------------------------------------------------- */

const void *AVLFind(const avl_t *tree, const void *key)
{   
    assert(tree); 
    assert(key);

    return Finder(tree->root, tree, key)->data;
}

/* --------------------------------------------------------------------------------- */
static avl_node_t *Finder(avl_node_t *node, const avl_t *tree, const void *key)
{
    int cmp = 0; 

    if ((NULL == node) || 0 == tree->cmp(node->data, key))
    {
        return node; 
    }

    cmp = tree->cmp(node->data, key) < 0 ;  

    return Finder(node->child[cmp], tree, key);    
}

/* --------------------------------------------------------------------------------- */

size_t AVLSize(const avl_t *tree)
{
    size_t count = 0; 

    assert(tree); 

    AVLForEach(tree, NodeCount, &count);
    
    return (count);
}
/* --------------------------------------------------------------------------------- */

static int NodeCount(const void *data, void *param)
{
    UNUSED(data); 
    ++*(size_t*)param; 
    
    return (0);
}
/* --------------------------------------------------------------------------------- */

size_t AVLHeight(const avl_t *tree)
{
    assert(tree); 

    return tree->root->height;
}
/* --------------------------------------------------------------------------------- */

static ssize_t BalanceFactor(const avl_node_t *node)
{
    if (node == NULL)
    {
        return 0; 
    }
    return (GetNodeHeight(node->child[1])- GetNodeHeight(node->child[0])); 
}
/* --------------------------------------------------------------------------------- */

static void AVLBalanceTree(avl_node_t *node)
{   
    if (BalanceFactor(node) < -1) /*if left heavy*/
    {   
        if (BalanceFactor(node->child[0]) > 0) /*if left subtree is right side heavy*/
        {
            RotateLeft(node->child[0]);
            RotateRight(node); 
        }
        else 
        {
           RotateRight(node);
        }
    }
    else if (BalanceFactor(node) > 1) /*is right side heavy*/
    {
        if (BalanceFactor(node->child[1]) < 0) /*is right subtree left heavy?*/
        {
            RotateRight(node->child[1]); 
            RotateLeft(node);
        }
        else 
        {
            RotateLeft(node);
        }
    }
}
/* --------------------------------------------------------------------------------- */

static void RotateLeft(avl_node_t *nodeA)
{
    avl_node_t *nodeB = nodeA->child[1];  /* A < B < C */ 
    avl_node_t *nodeC = nodeB->child[1]; 

    SwapData(&nodeA->data, &nodeB->data);

    nodeA->child[1] = nodeC; 
    nodeB->child[1] = nodeB->child[0];
    nodeB->child[0] = nodeA->child[0];
    nodeA->child[0] = nodeB; 
   
    UpdateNodeHeight(nodeC);
    UpdateNodeHeight(nodeB); 
    --nodeA->height;  
}
/* --------------------------------------------------------------------------------- */

static void RotateRight(avl_node_t *nodeA)
{
    avl_node_t *nodeB = nodeA->child[0];  /* A > B > C */
    avl_node_t *nodeC = nodeB->child[0];  

    SwapData(&nodeA->data, &nodeB->data);     
    
    nodeA->child[0] = nodeC; 
    nodeB->child[0] = nodeB->child[1];
    nodeB->child[1] = nodeA->child[1];
    nodeA->child[1] = nodeB; 

    UpdateNodeHeight(nodeC);
    UpdateNodeHeight(nodeB);
    --nodeA->height;
}
/* --------------------------------------------------------------------------------- */

ssize_t AVLGetBF(avl_t *tree)
{
    return BalanceFactor(tree->root);
}
/* --------------------------------------------------------------------------------- */

static void SwapData(void **dataA, void **dataB)
{
    void *temp  = *dataA;
    *dataA      = *dataB;
    *dataB      = temp;
}
/* --------------------------------------------------------------------------------- */