#include <stdio.h>
#include <stdlib.h>

// structure define
struct node {
    float coeff;
    int expo;
    struct node *link;
};

// insert function inserts all the data scanned from create function
struct node* insert(struct node* head, float co, int ex){
    struct node* temp;
    struct node* newPoly = malloc(sizeof(struct node));
    newPoly -> coeff = co;
    newPoly -> expo = ex;
    newPoly -> link = NULL;

    if (head == NULL || ex > head -> expo){
        newPoly -> link = head;
        head = newPoly;
    }
    else{
        temp = head;
        while (temp -> link != NULL && temp -> link -> expo >= ex){
            temp = temp -> link;
        }
        newPoly -> link = temp -> link;
        temp -> link = newPoly;
    }
    return head;
}

// create function creates nodes
struct node* create (struct node* head){
    int i, n, expo;
    float coeff;

    printf("Enter the number of terms: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++){
        printf("Enter the coefficient for term %d : ", i + 1);
        scanf("%f", &coeff);

        printf("Enter the exponent for term %d : ", i + 1);
        scanf("%d", &expo);

        head = insert(head, coeff, expo);
    }
    return head;
}

// print function prints the polynomial with conditions
void print(struct node* head) {
    if (head == NULL){
        printf("Empty polynomial");
    }
    else {
        struct node* temp = head;
        while (temp != NULL){
            printf("%.1fx^%d", temp -> coeff, temp -> expo);
            temp = temp -> link;
            if (temp != NULL){
                if (temp -> coeff > 0){
                    printf(" + ");
                }
                else {
                    printf(" ");
                }
            }
            else {
                printf("\n");
            }
        }
    }
}

// Polynomial Addition
void polyAdd (struct node* head1, struct node* head2){
    struct node* ptr1 = head1;
    struct node* ptr2 = head2;
    struct node* head3 = NULL;

    while (ptr1 != NULL && ptr2 != NULL){
        if (ptr1 -> expo == ptr2 -> expo){
            head3 = insert(head3, ptr1 -> coeff + ptr2 -> coeff, ptr1 -> expo);
            ptr1 = ptr1 -> link;
            ptr2 = ptr2 -> link;
        }
        else if (ptr1 -> expo > ptr2 -> expo){
            head3 = insert(head3, ptr1 -> coeff, ptr1 -> expo);
            ptr1 = ptr1 -> link;
        }
        else if (ptr1 -> expo < ptr2 -> expo) {
            head3 = insert(head3, ptr2 -> coeff, ptr2 -> expo);
            ptr2 = ptr2 -> link;
        }
    }

    while (ptr1 != NULL){
        head3 = insert(head3, ptr1 -> coeff, ptr1 -> expo);
        ptr1 = ptr1 -> link;
    }

    while (ptr2 != NULL){
        head3 = insert(head3, ptr2 -> coeff, ptr2 -> expo);
        ptr2 = ptr2 -> link;
    }

    printf("The first polynomial is:\n\t\t ");
    print(head1);
    printf("\n");
    printf("The second polynomial is:\n\t\t ");
    print(head2);
    printf("\n");
    printf("The sum of the two polynomials is:\n\t\t");
    print(head3);
    printf("\n");
}

// Polynomial Subtraction
void polySub (struct node* head1, struct node* head2){
    struct node* ptr1 = head1;
    struct node* ptr2 = head2;
    struct node* head3 = NULL;

    while (ptr1 != NULL && ptr2 != NULL){
        if (ptr1 -> expo == ptr2 -> expo){
            head3 = insert(head3, ptr1 -> coeff - ptr2 -> coeff, ptr1 -> expo);
            ptr1 = ptr1 -> link;
            ptr2 = ptr2 -> link;
        }
        else if (ptr1 -> expo > ptr2 -> expo){
            head3 = insert(head3, ptr1 -> coeff, ptr1 -> expo);
            ptr1 = ptr1 -> link;
        }
        else if (ptr1 -> expo < ptr2 -> expo) {
            head3 = insert(head3, -ptr2 -> coeff, ptr2 -> expo);
            ptr2 = ptr2 -> link;
        }
    }

    while (ptr1 != NULL){
        head3 = insert(head3, ptr1 -> coeff, ptr1 -> expo);
        ptr1 = ptr1 -> link;
    }

    while (ptr2 != NULL){
        head3 = insert(head3, ptr2 -> coeff, ptr2 -> expo);
        ptr2 = ptr2 -> link;
    }

    printf("The first polynomial is: ");
    print(head1);
    printf("\n");
    printf("The second polynomial is: ");
    print(head2);
    printf("\n");
    printf("The subtraction of the two polynomials is: ");
    print(head3);
    printf("\n");
}

// Polynomial Multiplication
void polyMult (struct node* head1, struct node* head2){
    struct node* ptr1 = head1;
    struct node* ptr2 = head2;
    struct node* head3 = NULL;

    if(head1 == NULL || head2 == NULL){
        printf("Zero Polynomials");
        return ;
    }

    while (ptr1 != NULL){
        while (ptr2 != NULL){
            head3 = insert(head3, ptr1 -> coeff * ptr2 -> coeff, ptr1 -> expo + ptr2 -> expo);
            ptr2 = ptr2 -> link;
        }
        ptr1 = ptr1 -> link;
        ptr2 = head2;
    }

    struct node* ptr3 = head3;
    struct node* temp = NULL;

    while (ptr3 -> link != NULL) {
        if (ptr3 -> expo == ptr3 -> link -> expo){
            ptr3 -> coeff = ptr3 -> coeff + ptr3 -> link -> coeff;
            temp = ptr3 -> link;
            ptr3 -> link = ptr3 -> link -> link;
            free(temp);
        }
        else {
            ptr3 = ptr3 -> link;
        }
    }
    printf("The first polynomial is: ");
    print(head1);
    printf("\n");
    printf("The second polynomial is: ");
    print(head2);
    printf("\n");
    printf("The multiplication of the two polynomials is: ");
    print(head3);

}

// Polynomial Derivation
void polyDeriv (struct node* head1){
    struct node* ptr1 = head1;
    struct node* head3 = NULL;

    while (ptr1 != NULL){
        head3 = insert(head3, ptr1 -> coeff * ptr1 -> expo, ptr1 -> expo - 1);
        ptr1 = ptr1 -> link;
    }
    printf("The first polynomial is: ");
    print(head1);
    printf("\n");
    printf("The derivative of the polynomial is: ");
    print(head3);
    printf("\n");
}

// Root
int main(){
    struct node* head1 = NULL;
    struct node* head2 = NULL;

    int op;

    printf("\nOperations Available:\n1 - Polynomial Addition\n2 - Polynomial Subtraction\n3 - Polynomial Multiplication\n4 - Polynomial Derivation\n5 - To exit the program\n");
    printf("Enter the operation you want to perform: ");
    scanf("%d", &op);
    
    switch (op) {
    case 1 :
        printf("Enter the first polynomial: \n");
        printf("\n");
        head1 = create(head1);
        printf("\n");
        printf("Enter the second polynomial: \n");
        printf("\n");
        head2 = create(head2);
        printf("\n");
        polyAdd(head1, head2);
        printf("\n");
        break;
    
    case 2 :
        printf("Enter the first polynomial: \n");
        printf("\n");
        head1 = create(head1);
        printf("\n");
        printf("Enter the second polynomial: \n");
        printf("\n");
        head2 = create(head2);
        printf("\n");
        polySub(head1, head2);
        printf("\n");
        break;
    
    case 3 :
        printf("Enter the first polynomial: \n");
        printf("\n");
        head1 = create(head1);
        printf("\n");
        printf("Enter the second polynomial: \n");
        printf("\n");
        head2 = create(head2);
        printf("\n");
        polyMult(head1, head2);
        printf("\n");
        break;

    case 4 :
        printf("Enter the polynomial: \n");
        printf("\n");
        head1 = create(head1);
        printf("\n");
        polyDeriv(head1);
        printf("\n");
        break;

    case 5 :
        printf("Exiting the program...");
        break;

    default:
        printf("Invalid Input, Please Retry Again!");
        break;
    }

    return 0;
}