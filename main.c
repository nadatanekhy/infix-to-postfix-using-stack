#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct
{
    float data;
    struct Node *next;
} Node;

typedef struct
{
    Node *top;
} Stack;

Node * newNode(float x)
{
    Node *n = malloc(sizeof(Node));
    n->data = x;
    n->next = NULL;
    return n;
}

Stack * initialize()
{
    Stack * s = malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}

void push(Stack * s , float x)
{
    Node * p = newNode(x);
    p->next = s->top;
    s->top = p;
}

float pop(Stack * s)
{
    if(s->top == NULL)
    {
        printf("Stack is Empty!");
        return;
    }
    Node * p = s->top;
    float data = p->data;
    s->top = p->next;
    free(p);
    return data;
}

float peak(Stack *s)
{

    if(s->top == NULL)
    {
        printf("Stack is Empty!");
        return;
    }
    else return s->top->data;
}

int isEmpty(Stack *s)
{
    if(s->top == NULL)
        return 1;
    else return 0;
}

void display(Stack *s)
{
    Stack * copy = initialize();
    while (!isEmpty(s))
    {
        float x = pop(s);
        printf("%.2f ",x);
        push(copy,x);
    }
    while(!isEmpty(copy))
        push(s,pop(copy));
}

int priority(char x)
{
    if(x == '*' || x == '/')
        return 2;
    else if(x == '-' || x == '+')
        return 1;
}

/*char* infixTopost(char* infix)
{
    int i, k = 0;
    Stack* s = initialize();
    char* post = malloc(strlen(infix) + 1);
    char in[100] = {};
    char * token = strtok(infix, " ");
    while(token != NULL)
    {
        strcat(in, token);
        token = strtok(NULL, " ");
    }
    for( i = 0 ; i < strlen(infix) ; i++)
    {
        if(isdigit(infix[i]) || infix[i] == '.')
            post[k++] = infix[i];
        else if(isEmpty(s) || peak(s) == '(')
                    push(s, infix[i]);
        else if(infix[i] == ')')
        {
            while(peak(s) != '(')
                    post[k++] = pop(s);
            pop(s);
        }
        else
        {
            while(!isEmpty(s) && priority(peak(s)) >= priority(infix[i]))
                post[k++] = pop(s);
            push(s, infix[i]);
        }
    }
    while(!isEmpty(s))
        post[k++] = pop(s);
    post[k] = '\0';
    return post;
}
*/
char* infixToPost(char* infix)
{
    int i, k = 0;
    Stack* s = initialize();
    char* post = malloc(strlen(infix) + 1);
    char * token = strtok(infix, " ");
    while(token != NULL)
    {
        if(isdigit(token[0]) || isdigit(token[1]))
        {
            for(i = 0 ; i < strlen(token) ; i++)
            {
            post[k++] = token[i];
            }
            post[k++] = ' ';
        }
        else if(isEmpty(s) || peak(s) == '(')
                    push(s, token[0]);
        else if(token[0] == ')')
        {
            while(peak(s) != '(')
            {
                    post[k++] = pop(s);
                    post[k++] = ' ';
            }
            pop(s);
        }
        else
        {
            while(!isEmpty(s) && priority(peak(s)) >= priority(token[0]))
            {
                post[k++] = pop(s);
                post[k++] = ' ';
            }
            push(s, token[0]);
        }
        token = strtok(NULL, " ");
    }
    while(!isEmpty(s))
    {
        post[k++] = pop(s);
        post[k++] = ' ';
    }
    post[k] = '\0';
    return post;
}
float calculate(float val1, float val2,char op)
{
    switch(op)
    {
        case '+' :
              return  val1 + val2;

        case '-':
                return  val1 - val2;

        case '*':
                return  val1 * val2;

        case '/':
           return val1 / val2;
        case '^':
           return pow(val1,val2);

    }
}

float evaluate(char * post)
{
    Stack * s = initialize();
    int i;
    for(i = 0 ; i < strlen(post) ; i++)
    {
        if(isdigit(post[i]))
            push(s, post[i] - 48);
        else
        {
            float x = pop(s);
            float y = pop(s);

            float z = calculate(y, x, post[i]);
            push(s, z);
        }
    }
    return pop(s);
}

int main()
{
Stack *s = initialize();
char in[100];
int i;
printf("Input(Infix) : ");
gets(in);
char* post = infixToPost(in);
printf("Output(Postfix) : ");
for(i = 0 ; i < strlen(post) ; i++)
{
  printf("%c", post[i]);
}
//printf("\n");
//float y = evaluate(post);
//printf("Value : %f", y);

    return 0;
}
