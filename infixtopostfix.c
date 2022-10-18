

#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include "infixtopostfix.h"


struct Stack* createStack()
{
    struct Stack* stack = (struct Stack*)
            malloc(sizeof(struct Stack));

    if (!stack)
        return NULL;

    stack->top = -1;

    return stack;
}
int isEmpty(struct Stack* stack)
{
    return stack->top == -1 ;
}

void pop(struct Stack* stack)
{
    if (!isEmpty(stack))
        stack->top--;

}
void push(struct Stack* stack, char op[])
{
    int i;
    ++stack->top;

    strcpy(stack->array[stack->top] , op);

}

int Prec(char ch)
{
    switch (ch)
    {
        case 't':
        case 's':
            return 0;

        case '+':
        case '-':
            return 1;

        case '*':
        case '/':
            return 2;

    }
    return -1;
}
int isOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' ;
}

void initializeNode(struct node_for_dll** node_ref)
{
    (*node_ref)->is_scalar = 0;
    (*node_ref)->is_vector = 0;
    (*node_ref)->is_matrix = 0;
    (*node_ref)->size = -1;
    (*node_ref)->row_size = -1;
    (*node_ref)->column_size = -1;

    return;
}


void append(struct node_for_dll** head_ref, char* new_data)
{
    struct node_for_dll* new_node = (struct node_for_dll*)malloc(sizeof(struct node_for_dll));

    struct node_for_dll* last = *head_ref;


    initializeNode(&new_node);
    strcpy(new_node->data , new_data);

    new_node->next = NULL;

    if (*head_ref == NULL) {
        new_node->prev = NULL;
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL)
        last = last->next;


    last->next = new_node;

    new_node->prev = last;

    return;
}

void appendChar(char* s, char c) {
    int len = strlen(s);
    s[len] = c;
    s[len+1] = '\0';
}


int infixToPostfix(char* exp , struct node_for_dll** head_ref)
{
    //printf("%s\n" , exp);

    int i, k = 0;

    struct Stack* stack = createStack();
    if(!stack)
        return -1 ;

    char var_name[200] = "";

    int tr_flag = 0;
    int sqrt_flag = 0;

    for (i = 0 ; i< strlen(exp); i++)
    {
        //printf("%d %c\n" , i , exp[i]);
        //printf("%s\n" , var_name);
        tr_flag = 0;
        sqrt_flag = 0;

        if(i+2 < strlen(exp) && exp[i] == 't' && exp[i+1] == 'r' && exp[i+2] == '(')
        {
            tr_flag = 1;
        }

        if(i+4 < strlen(exp) && exp[i] == 's' && exp[i+1] == 'q' && exp[i+2] == 'r' && exp[i+3] == 't' && exp[i+4] == '(')
        {
            sqrt_flag = 1;
        }

        if(i+6 < strlen(exp) && exp[i] == 'c' && exp[i+1] == 'h' && exp[i+2] == 'o' && exp[i+3] == 'o' && exp[i+4] == 's' &&
        exp[i+5] == 'e' && exp[i+6] == '(')
        {
            char temp_str[1024] = "choose(";

            int parantheses_count = 1;
            int j = i+7;

            while(j < strlen(exp) && parantheses_count > 0)
            {
                appendChar(temp_str , exp[j]);

                if(exp[j] == '(')
                {
                    parantheses_count++;
                }
                else if(exp[j] == ')')
                {
                    parantheses_count--;
                }

                j++;
            }

            append(head_ref , temp_str);
            i=j-1;

        }
        else if(isOperator(exp[i]) || exp[i] == '(' || exp[i] == ')' || tr_flag == 1 || sqrt_flag == 1)
        {
            //printf("entered");
            if(strlen(var_name) != 0)
            {
                //printf("entered");
                append(head_ref , var_name);
                k=0;
                memset(var_name, 0, sizeof(var_name));
                //printf("entered");
            }

            if(tr_flag == 1)
            {
                char tmp[50] = "";
                tmp[0] = 't';
                tmp[1] = 'r';

                push(stack, tmp);

                i += 2;
            }

            else if(sqrt_flag == 1)
            {
                char tmp[50] = "";
                tmp[0] = 's';
                tmp[1] = 'q';
                tmp[2] = 'r';
                tmp[3] = 't';

                push(stack, tmp);

                i += 4;
            }

            else if (exp[i] == '(')
            {
                char tmp[50] = "";
                tmp[0] = exp[i];

                push(stack, tmp);
            }

            else if (exp[i] == ')')
            {
                while (!isEmpty(stack) && (stack->array[stack->top][0] != '(' && stack->array[stack->top][0] != 't'  && stack->array[stack->top][0] != 's'))
                {
                    append(head_ref , stack->array[stack->top]);
                    pop(stack);
                }

                if (!isEmpty(stack) && (stack->array[stack->top][0] != '(' && stack->array[stack->top][0] != 't'  && stack->array[stack->top][0] != 's'))
                    return -1;
                else
                {
                    if(stack->array[stack->top][0] == 't' || stack->array[stack->top][0] == 's')
                    {
                        append(head_ref , stack->array[stack->top]);
                    }

                    pop(stack);
                }

            }
            else
            {
                //printf("%d" , isEmpty(stack));
                while (!isEmpty(stack) && Prec(exp[i]) <= Prec(stack->array[stack->top][0]))
                {
                    //printf("entered");
                    append(head_ref , stack->array[stack->top]);
                    pop(stack);
                }

                char tmp[50] = "";
                tmp[0] = exp[i];

                push(stack, tmp);
            }

        }
        else
        {
            var_name[k++] = exp[i];
        }


    }

    if(strlen(var_name) != 0)
    {
        append(head_ref , var_name);
    }

    // pop all the operators from the stack
    while (!isEmpty(stack))
    {
        append(head_ref , stack->array[stack->top]);
        pop(stack);
    }

}


