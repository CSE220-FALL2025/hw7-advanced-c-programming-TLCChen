#include "hw7.h"

bst_sf *insert_bst_sf(matrix_sf *mat, bst_sf *root)
{
    if (root == NULL)
    {
        bst_sf *newRoot = malloc(sizeof(bst_sf));
        if (!newRoot)
        {

            return NULL;
        }

        newRoot->mat = mat;
        newRoot->left_child = NULL;
        newRoot->right_child = NULL;

        return newRoot;
    }
    if (root->mat->name > mat->name)
    {
        root->left_child = insert_bst_sf(mat, root->left_child);
    }
    else
    {

        root->right_child = insert_bst_sf(mat, root->right_child);
    }

    return root;

    // if (*root == NULL)
    // {
    //     root->mat = mat
    // }
    // else
    // {
    //     bst_sf *new_node;
    //     new_node = malloc(sizeof(bst_sf));
    //     *new_node = *root;

    // while (true)
    // {
    //     if (new_node->mat->name < mat->name)
    //     {
    //         if (new_node->left_child != NULL)
    //         {
    //             new_node->mat = new_node->left_child;
    //             new_node->left_child = new_node->left_child->left_child;
    //             new_node->right_child = new_node->right_child->right_child;
    //         }
    //         else
    //         {
    //             new_node->left_child
    //         }
    //     }
    // }
    // }

    return NULL;
}

matrix_sf *find_bst_sf(char name, bst_sf *root)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (root->mat->name == name)
    {
        return root->mat;
    }
    else
    {

        if (root->mat->name > name)
        {
            return find_bst_sf(name, root->left_child);
        }
        else
        {

            return find_bst_sf(name, root->right_child);
        }
    }
    // return NULL;
}

void free_bst_sf(bst_sf *root)
{
    if (root == NULL)
    {
        return;
    }

    free_bst_sf(root->left_child);
    free_bst_sf(root->right_child);

    if (root->mat != NULL)
    {
        free(root->mat);
    }

    free(root);
}

matrix_sf *add_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2)
{
    int row = mat1->num_rows;
    int col = mat1->num_cols;
    matrix_sf *result;
    result = malloc(sizeof(matrix_sf) + row * col * sizeof(int));
    if (!result)
    {
        printf("No memory.");
        return NULL;
    }
    int resultMatrix[row * col];
    int count = 0;
    int add = 0;
    while (count < row * col)
    {
        add = mat1->values[count] + mat2->values[count];
        resultMatrix[count] = add;
        count++;
    }
    count = 0;
    while (count < row * col)
    {
        result->values[count] = resultMatrix[count];
        count++;
    }
    result->num_cols = col;
    result->num_rows = row;
    result->name = '?';
    return result;

    return NULL;
} //

matrix_sf *mult_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2)
{
    int row = mat1->num_rows;
    int col1 = mat1->num_cols;
    int col2 = mat2->num_cols;

    matrix_sf *result;
    result = malloc(sizeof(matrix_sf) + row * col2 * sizeof(int));
    if (!result)
    {
        printf("No memory");
        return NULL;
    }

    int count = 0;
    int count2 = 0;
    int count3 = 0;
    int add = 0;

    while (count < row)
    {
        while (count2 < col2)
        {

            while (count3 < col1)
            {

                add += mat1->values[count * col1 + count3] * mat2->values[count3 * col2 + count2]; // use pointer math
                count3++;
            }
            result->values[count * col2 + count2] = add;
            count2++;
            count3 = 0;
            add = 0;
        }
        count++;
        count2 = 0;
    }
    result->name = '?';
    result->num_cols = col2;
    result->num_rows = row;

    return result; // rememeber to add name to function calling this function

    return NULL;
}

matrix_sf *transpose_mat_sf(const matrix_sf *mat)
{
    int row = mat->num_rows; // 147, 258, 369
    int col = mat->num_cols; // 123,456,789

    matrix_sf *result;
    result = malloc(sizeof(matrix_sf) + row * col * sizeof(int));
    if (!result)
    {
        return NULL;
    }

    int count = 0;
    int count2 = 0;
    int count3 = 0;

    while (count < col)
    {
        while (count2 < row)
        {
            result->values[count3] = mat->values[count + count2 * col];
            count2++;
            count3++;
        }
        count++;
        count2 = 0;
    }

    result->num_cols = row;
    result->num_rows = col;
    result->name = '?';

    return result;
    return NULL;
} // use count3 much easier.

int isDigit(char a)
{
    if (a >= '0' && a <= '9')
    {
        return 1;
    }
    return 0;
}

matrix_sf *create_matrix_sf(char name, const char *expr)
{
    int num[2];
    int count = 0;
    int row;
    int col;

    const char *copy = expr;
    while (*copy != '[')
    {

        if (isDigit(*copy))
        {
            if (count == 2)
            {
                break;
            }
            num[count] = *copy - '0';
            count++;
        }
        copy++;
    }

    row = num[0];
    col = num[1];

    matrix_sf *new;
    new = malloc(sizeof(matrix_sf) + row * col * sizeof(int));
    if (!new)
    {
        printf("No space");
        return NULL;
    }

    new->num_cols = col;
    new->num_rows = row;
    new->name = name;

    char *letters;
    int count2 = 0;
    int num2 = 0;

    while (*copy != ']')
    {
        if (isDigit(*copy) || *copy == '-')
        {
            num2 = strtol(copy, &letters, 10);
            new->values[count2] = num2;
            copy = letters;
            count2++;
        }
        else
        {
            copy++;
        }
    }

    return new;
    return NULL;
}

int order(char op)
{
    if (op == '\'')
    {
        return 3;
    }
    else if (op == '*')
    {
        return 2;
    }
    else if (op == '+')
    {
        return 1;
    }
    else
        return 0;
}

int isAlpha(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return 1;
    }
    return 0;
}
char *infix2postfix_sf(char *infix) // consider using top to prevent -1 index
{
    char stack[100];
    char *postfix = malloc(100);
    if (!postfix)
    {
        printf("No memory");
        return NULL;
    }
    char *sptr = stack;
    char *pPtr = postfix;

    while (*infix != '\0')
    {

        if (isAlpha(*infix))
        {
            *pPtr = *infix;
            pPtr++;
        }
        if (*infix == '(')
        {
            *sptr = *infix;
            sptr++;
        }
        if (*infix == ')')
        {
            sptr--;
            while (sptr > stack && *sptr != '(')
            {
                *pPtr = *sptr;
                pPtr++;
                sptr--;
            }
        }
        if (order(*infix) > 0)
        {
            while (sptr > stack && order(*(sptr - 1)) >= order(*infix))
            {
                *pPtr = *(sptr - 1);
                pPtr++;
                sptr--;
            }

            *sptr = *infix;
            sptr++;
        }

        infix++;
    }

    while (sptr > stack)
    {
        *pPtr = *(sptr - 1);
        pPtr++;
        sptr--;
    }

    *pPtr = '\0';

    return postfix;

    // return NULL;
}

matrix_sf *evaluate_expr_sf(char name, char *expr, bst_sf *root)
{

    matrix_sf *stack[50];
    char str[100];
    matrix_sf **stackP = stack;
    char *sptr = str;
    sptr = infix2postfix_sf(expr);
    char *delete = sptr;

    while (*sptr != '\0')
    {

        if (isAlpha(*sptr))
        {
            *stackP = find_bst_sf(*sptr, root);
            stackP++;
        }

        if (order(*sptr) == 2)
        {
            *(stackP - 2) = mult_mats_sf(*(stackP - 2), *(stackP - 1));
            stackP--;
        }

        if (order(*sptr) == 1)
        {
            *(stackP - 2) = add_mats_sf(*(stackP - 2), *(stackP - 1));
            stackP--;
        }
        if (order(*sptr) == 3)
        {
            *(stackP - 1) = transpose_mat_sf(*(stackP - 1));
        }

        sptr++;
    }
    stackP--;

    matrix_sf *result = *stackP;
    result->name = name;

    while (*stackP > stack)
    {
        free(stackP);
        stackP--;
    }
    free(delete);
    return result;
    return NULL;
}

matrix_sf *execute_script_sf(char *filename)
{
    FILE *input = fopen(filename, "r");

    bst_sf *root;
    root = malloc(sizeof(bst_sf));
    matrix_sf *result;

    char *line = NULL;
    size_t max_line_size = MAX_LINE_LEN;

    while (getline(&line, &max_line_size, input) != -1)
    {
        if (*line == '\0' || *line == '\n')
        {
            continue;
        }
        char name;
        int count = 0;
        int isM = 0;

        name = *line;
        line = strchr(line, '=');
        while (*line = ' ')
        {
            line++;
        }
        if (isDigit(*line))
        {
            // matrix_sf *temp = create_matrix_sf(name, line);
            insert_bst_sf(create_matrix_sf(name, line), root);
        }
        if (isAlpha(*line))
        {
            result = evaluate_expr_sf(name, line, root);
        }
    }

    free(line);
    free_bst_sf(root);
    fclose(input);

    return result;

    return NULL;
}

// This is a utility function used during testing. Feel free to adapt the code to implement some of
// the assignment. Feel equally free to ignore it.
matrix_sf *copy_matrix(unsigned int num_rows, unsigned int num_cols, int values[])
{
    matrix_sf *m = malloc(sizeof(matrix_sf) + num_rows * num_cols * sizeof(int));
    m->name = '?';
    m->num_rows = num_rows;
    m->num_cols = num_cols;
    memcpy(m->values, values, num_rows * num_cols * sizeof(int));
    return m;
}

// Don't touch this function. It's used by the testing framework.
// It's been left here in case it helps you debug and test your code.
void print_matrix_sf(matrix_sf *mat)
{
    assert(mat != NULL);
    assert(mat->num_rows <= 1000);
    assert(mat->num_cols <= 1000);
    printf("%d %d ", mat->num_rows, mat->num_cols);
    for (unsigned int i = 0; i < mat->num_rows * mat->num_cols; i++)
    {
        printf("%d", mat->values[i]);
        if (i < mat->num_rows * mat->num_cols - 1)
            printf(" ");
    }
    printf("\r\n");
}
