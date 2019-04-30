#include "tree.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Creates a new node structure and allocates the nedded memory
 *
 * @param token Operation Identifier
 */
Node* new_node(Lexeme* lexeme)
{
    Node* node = (Node*) malloc(sizeof(Node));

    node->lexeme = lexeme;
    node->children_count = 0;
    node->children = (Node**) malloc(sizeof(Node**));

    return node;
}

/**
 * Adds a new child to a existing node
 *
 * @param node Pointer to the parent node
 * @param child Pointer to the child node
 */
void add_child(Node* node, Node* child)
{
    node->children_count++;
    node->children = (Node**) realloc(
            node->children,
            node->children_count * sizeof(Node**)
        );

    node->children[node->children_count - 1] = child;
}

/**
 * Generates a source code based on a Abstract Syntax Tree (AST)
 *
 * @param root AST Pointer
 */
void decompile(Node* root)
{
    if(root != NULL)
    {
        print_lexeme(root->lexeme);

        for(int i = 0; i < root->children_count; i++)
        {
            Node* child = *(root->children + i);

            if(child != NULL) {
                decompile(child);
            }
        }
    }
}

/**
 * Frees memory previously allocated to the AST structure
 *
 * @param root AST Pointer
 */
void free_tree(Node* root)
{
    if(root != NULL) // NULL
    {
        if(root->lexeme != NULL)
        {
            free_lexeme(root->lexeme);
        }

        for(int i = 0; i < root->children_count; i++)
        {
            Node* child = *(root->children + i);

            if(child != NULL) {
                free_tree(child);
            }
        }

        free(root->children);
        free(root);
    }
}


/**
 * Frees memory allocated for a Lexeme
 *
 * @param lex Lexeme Pointer
 * @return Allways 0, to override old pointer
 */
int free_lexeme(Lexeme* lex)
{
    if(lex != NULL)
    {
        // Free string value if allocated
        if(lex->token_type != SPECIAL_CHAR &&
            lex->literal_type != INT &&
            lex->literal_type != FLOAT &&
            lex->literal_type != BOOL &&
            lex->literal_type != CHAR )
        {
            free(lex->token_value.v_string);
        }

        free(lex);
    }

    return 1;
}

/**
 * Prints a Lexeme's value
 *
 * @param lex Lexeme
 */
void print_lexeme(Lexeme* lex)
{
    if(lex != NULL)
    {
        if(lex->token_type == SPECIAL_CHAR)
        {
            printf("%c ", lex->token_value.v_char);
        }
        else
        {
            switch(lex->literal_type)
            {
                case INT:
                    printf("%d ", lex->token_value.v_int);
                    break;
                case FLOAT:
                    printf("%f ", lex->token_value.v_float);
                    break;
                case BOOL:
                    printf("%s ", lex->token_value.v_bool ? "true" : "false");
                    break;
                case CHAR:
                    printf("\'");
                    print_char(lex->token_value.v_char);
                    printf("\' ");
                    break;
                case STRING:
                    print_string(lex->token_value.v_string);
                    printf(" ");
                    break;
                default:
                    printf("%s ",lex->token_value.v_string);
                    break;
            }
        }
    }
}
void print_char (char v_char){
  switch(v_char){
    case '\n':
      printf("\\n");
    break;

    case '\a':
      printf("\\a");
    break;

    case '\b':
      printf("\\b");
    break;

    case '\f':
      printf("\\f");
    break;

    case '\r':
      printf("\\r");
    break;

    case '\t':
      printf("\\t");
    break;

    case '\v':
      printf("\\v");
    break;

    case '\\':
      printf("\\\\");
    break;

    case '\'':
      printf("\\\'");
    break;

    case '\"':
      printf("\\\"");
    break;

    case '\?':
      printf("\\\?");
    break;

    default:
        printf("%c", v_char);
    break;
  }
}

void print_string(char* v_string){
  int i;
  printf("\"");
  for(i=0;i<strlen(v_string);i++){
    print_char(v_string[i]);
  }
  printf("\"");
}
