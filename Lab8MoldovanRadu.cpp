#include <iostream>

#define length(x) (sizeof(x)/sizeof(*x))

typedef struct nod
{
    int val;
    struct nod* left;
    struct nod* right;
    struct nod* parent;
}nod;

nod* CreateNode(int val)
{
    nod* ret = (nod*)malloc(sizeof(nod));

    ret->val = val;
    ret->left = NULL;
    ret->right = NULL;
    ret->parent = NULL;

    return ret;
}

void InsertBst(nod* head, int val)
{
    nod* aux = CreateNode(val);
    nod* curr = head;

    while (1)
    {
        if (aux->val > curr->val)
        {
            if (curr->right == NULL)
            {
                curr->right = aux;
                aux->parent = curr;
                break;
            }

            else
                curr = curr->right;
        }

        else
        {
            if (curr->left == NULL)
            {
                curr->left = aux;
                aux->parent = curr;
                break;
            }

            else
                curr = curr->left;

        }
    }
}

nod* CreateBst(int a[], int n)
{
    nod* ret = CreateNode(a[0]);

    for (int i = 1; i < n; i++)
        InsertBst(ret, a[i]);


    return ret;
}

nod* SearchBst(nod* head, int val)
{
    if (head->val == val)
        return head;

    if (val < head->val)
    {
        if (head->left != NULL)
            return SearchBst(head->left, val);

        return NULL;
    }

    if (val > head->val)
    {
        if (head->right != NULL)
            return SearchBst(head->right, val);

        return NULL;
    }

    return NULL;

}

nod* MinBst(nod* head)
{
    nod* curr = head;

    while (curr->left != NULL)
        curr = curr->left;

    return curr;
}

nod* MaxBst(nod* head)
{
    nod* curr = head;

    while (curr->right != NULL)
        curr = curr->right;

    return curr;
}

void preorder(nod* head)
{
    printf("%d ", head->val);
    if (head->left != NULL) preorder(head->left);
    if (head->right != NULL) preorder(head->right);

}

nod* SuccesorBst(nod* x)
{
    if (x->right != NULL)
        return MinBst(x->right);

    else
    {
        nod* y = x->parent;

        while (y != NULL && x == y->right)
        {
            x = y;
            y = y->parent;
        }

        return y;
    }
}

nod* PredecesorBst(nod* x)
{
    if (x->left != NULL)
        return MaxBst(x->left);

    else
    {
        nod* y = x->parent;

        while (y != NULL && x == y->left)
        {
            x = y;
            y = y->parent;
        }

        return y;
    }
}

void DeleteBst(nod* x)
{
    if (x->left == NULL && x->right == NULL)
    {
        if (x);
        free(x);
    }

    else if (x->left == NULL || x->right == NULL && !(x->left != NULL && x->right != NULL))
    {
        if (x->left != NULL)
        {
            x->parent->left = x->left;
            x->left->parent = x->parent;
            free(x);
        }

        else if (x->right != NULL)
        {
            x->parent->right = x->right;
            x->right->parent = x->parent;
            free(x);
        }

    }

    else if (x->left != NULL && x->right != NULL)
    {

    }
}

int main()
{
    int a[] = { 12, 5, 18, 2, 9, 15, 19, 13, 17 };

    nod* tree = CreateBst(a, length(a));
    preorder(tree);

    printf("\n%d", PredecesorBst(tree->right->left->left)->val);


    return 0;

}
