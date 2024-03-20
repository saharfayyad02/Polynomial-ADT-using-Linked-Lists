//1190119 sahar fayyad
#include <stdio.h>
#include <accctrl.h>
#define MAX 30
#include <math.h>

int j = 0;//number of equations in the file
int nsum=1;//number of equations that were addtioned
int nsub=1;//number of equations that were subtracted
int nmul=1;//number of equations multiplied
int x,s,k;//values of x entered by the user
int sl=0;


struct node;
typedef struct node *ptr;

struct node {
float coff;
int expo;
ptr prev;
ptr next;
};

typedef ptr pos;
typedef ptr list;

list l[MAX] ;//array of list to insert a doubly linked list in it


struct node * insert(list l,float coff,int expo);
void split(char str[50]);
void spli(char ch[30]);
void read();
list add(list k,list g);
list subtraction(list f,list t);
void delet(list temp);
list multiplication(list n,list m);
void print();
void prin();
void prinl(list t,int x);
void save_to_thefile();
void fprinl(list t,FILE *f);


//drive code
int main() {
    for (int i = 0; i < 3; i++) {//intialize the array of list
        l[i] = (list) malloc(sizeof(struct node));
        l[i]->next = NULL;
        l[i]->prev = NULL;
    }

    while(1) {
        //menu
        printf("\nenter the number of the operation:\n");
        printf("1.read from the file:\n");
        printf("2.show equation:\n");
        printf("3.perform addition:\n");
        printf("4.perform subtraction:\n");
        printf("5.perform multiplication:\n");
        printf("6.save to the file:\n");
        printf("7.exit:\n");


        int op;
        scanf("%d", &op);
        switch (op) {
            case 1:
                if(j==0) {
                    //read function
                    read();
                }
                else{
                    printf("you recently read!!!");
                }
               break;
            case 2:
                //show equation function
             print();
                break;

            case 3:
                if(j != 0) {
                    //addetion function
                    prin(add(l[0], l[1]));
                    nsum = 1;
                    printf("\nenter the value of x\n");
                    scanf("%d", &x);
                    prinl(add(l[0], l[1]), x);
                    nsum = 1;
                }
                else{
                    printf("read from the file first!!");
                }
                break;

            case 4:
                if(j != 0) {
                    //subtraction function
                    prin(subtraction(l[0], l[1]));
                    nsub = 1;
                    printf("\nenter the value of x\n");
                    scanf("%d", &s);
                    prinl(subtraction(l[0], l[1]), s);
                }
                else{
                    printf("read from the file first !!!!");
                }
            break;

            case 5:
                if(j != 0) {
                    //multiplication function
                    prin(multiplication(l[0], l[1]));
                    nmul = 1;
                    printf("\nenter the value of x\n");
                    scanf("%d", &k);
                    prinl(multiplication(l[0], l[1]), k);
                }
                else{
                    printf("read from the file first !!!!");
                }
            break;

            case 6:
                if(j !=0) {
                    //save to the file function
                    printf("cheack the output please\n");
                    save_to_thefile();
                }else{
                    printf("read from the file first!!!!");
                }
             break;

            case 7:
                //exit from the system
                printf("Good Bye :)");
                exit(1);
                break;
            default:
                printf("please select from 1 to 7 only");
                break;
        }
    }
    return 0;
}

//to insert to the doubly linked list
struct node  *insert(list l,float coff,int expo) {
    while(l->next != NULL){
        l=l->next;
    }
    pos temp,p;
    temp = (pos) malloc(sizeof(struct node));
    if (temp != NULL)
        temp->prev = NULL;
        temp->coff = coff;
        temp->expo = expo;
        temp->next = NULL;
        p=l;
        temp->next=p->next;
        p->next=temp;
        temp->prev=p;

        return l;
}


//to remove the white spaces
void split(char str[50]) {
    int i = 0, h;
        while (str[i] != '\0') {
            if (str[i] == ' ') {
                h = i;
                while (str[h - 1] != '\0') {
                    str[h] = str[h + 1];
                    h++;
                }
            }
            i++;
        }
}


//to divide the equations into coeff and expo
void spli(char ch[30]) {//0.5x^2-x-17
    int i = 0;

    while (ch[i] != '\0') {
        char r[20] = "\0";
        char y[20] = "\0";

        while (ch[i] != 'x' && ch[i] != '\0') {//check the coeffecitent
            if (ch[i] == '-' || (ch[i] >= '0' && ch[i] <= '9')) {
                char s[2] = "\0";
                s[0] = ch[i];
                strcat(r, s);
            }
            i++;
        }

        if(strcmp(r ,"")==0){
            r[0]='1';
        }

        int v= atoi(r);

        if (ch[i] == 'x') {//check the exponential
            i++;
            if (ch[i] != '^') {
                y[0] = '1';
            } else {
                i++;
                while (ch[i] != '+' && ch[i] != '-') {
                    char d[2] = "\0";
                    d[0] = ch[i];
                    strcat(y, d);
                    i++;
                }
            }
        }

        int c = atoi(y);
        insert(l[j], v, c);
    }
j++;
}


//to read from the file
void read() {

    FILE *file = fopen("C:\\Users\\user\\CLionProjects\\untitled3\\equations.txt", "r");
    char buffer[MAX];

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        split(buffer);
        spli(buffer);
    }
    fclose(file);
}


//to show the eq
void print() {
    for (int i = 0; i < j; i++) {//to print the array if list which contain a doubly linked list in each of them
        list d = l[i];
        d = d->next;
        printf("\n");
        while (d != NULL) {
            if (d->coff == 0) {
                d = d->next;
                continue;
            }
            else if(d->expo == 0){
                printf("+%1.2f",d->coff);
                d = d->next;
            }
            else if(d->expo == 1){
                printf("+%1.2fx",d->coff);
                d = d->next;
            }
            else {
                printf("+%1.2f(x^%d)", d->coff, d->expo);
                d = d->next;
            }
        }
    }
}


//to add the equations
list add(list k,list g) {
    sl++;
    list sum;
    sum = (list) malloc(sizeof(struct node));
    sum->next = NULL;
    sum->prev = NULL;

    if (nsum == j) {//check if the summed equation equals the equations in the file
        return (k);
    } else {
        list d = k;
        list d2 = g;

        while (d->next != NULL && d2->next != NULL) {
            if (d->next->expo > d2->next->expo) {//if the epxo of the list one grater than the second
                insert(sum, d->next->coff, d->next->expo);
                d = d->next;
            } else if (d->next->expo < d2->next->expo) {//if the expo of the second is grater than the first
                insert(sum, d2->next->coff, d2->next->expo);
                d2 = d2->next;
            } else {//if the expo is equals ,add the coef of the 2 lists
                insert(sum, d2->next->coff + d->next->coff, d2->next->expo);
                d = d->next;
                d2 = d2->next;
            }
        }
        nsum++;
        return add(sum,l[nsum]);
    }
}


//to subtract the equations
list subtraction(list f,list t) {
    sl++;
    list sub;
    sub = (list) malloc(sizeof(struct node));
    sub->next = NULL;
    sub->prev = NULL;

    if (nsub == j) {//check if the subtracted equation equals the equations in the file
        return (f);
    } else {
        list r = f;
        list r2 = t;

        while (r->next != NULL && r2->next != NULL) {
            if (r->next->expo > r2->next->expo) {//if the epxo of the list one grater than the second
                insert(sub, r->next->coff, r->next->expo);
                r = r->next;
            } else if (r->next->expo < r2->next->expo) {//if the expo of the second is grater than the first
                insert(sub, -1*(r2->next->coff), r2->next->expo);
                r2 = r2->next;
            } else {//if the expo is equals ,add the coef of the 2 lists
                insert(sub, r->next->coff-r2->next->coff, r2->next->expo);
                r = r->next;
                r2 = r2->next;
            }
        }
        nsub++;
        return subtraction(sub,l[nsub]);
    }
}



void delet(list temp){
    if(temp->next != NULL){
        (temp->prev)->next=temp->next;
        (temp->next)->prev=temp->prev;
        free(temp);
    }
}


//to multiply the equations
list multiplication(list n,list m){
    sl++;
    list mul;
    mul = (list) malloc(sizeof(struct node));
    mul->next = NULL;
    mul->prev = NULL;


list t = n;
list t2 = m;
list sop1,sop2,temp;

if(nmul == j){
    return(n);
}
else {
    while (t->next != NULL) {//to multiply the equations
        while (t2->next != NULL) {
            insert(mul,  t->next->coff * t2->next->coff, t->next->expo + t2->next->expo);
            t2 = t2->next;
        }
        t = t->next;
        t2 = m;
    }

    sop1 = mul->next;
    sop2 = mul->next->next;

    while (sop1 != NULL) {// to add the coef to the samr expo in one node
        while (sop2 != NULL) {
            if (sop1->expo == sop2->expo) {
                sop1->coff += sop2->coff;
                temp = sop2;
                sop2 = sop2->next;
                delet(temp);//to remove the node with same expo after adding them
            } else {
                sop2 = sop2->next;
            }
        }
        sop1 = sop1->next;
        if (sop1 != NULL)
            sop2 = sop1->next;
    }
    nmul++;
    return multiplication(mul,l[nmul]);
  }
}


//to print the operations on equations
void prin(list t) {
    list d= t;
    d = d->next;
    while (d != NULL) {
        if (d->coff == 0) {
            d = d->next;
            continue;
        }
        else if(d->expo == 0){
            printf("+%1.2f",d->coff);
            d = d->next;
        }
        else if(d->expo == 1){
            printf("+%1.2fx",d->coff);
            d = d->next;
        }
        else {
            printf("+%1.2f(x^%d)", d->coff, d->expo);
            d = d->next;
        }
  }
}


//to print the result when replaced the value of x
void prinl(list t,int x) {
    list d = t;
    float v,sum=0;
    int ex;
    d = d->next;
    while(d != NULL) {
        ex = pow(x, d->expo);
        v = ex * d->coff;
        sum+=v;
        d=d->next;
    }
        printf("\nthe output prosess is %1.2f",sum);
}


//to print in the file
void fprinl(list t,FILE *f) {
    list d = t;
    d = d->next;
    while(d != NULL) {

        if (d->coff == 0) {
            d = d->next;
            continue;
        }
        else if(d->expo == 0){
            fprintf(f,"+%1.2f",d->coff);
            d = d->next;
        }
        else if(d->expo == 1){
            fprintf(f,"+%1.2fx",d->coff);
            d = d->next;
        }
        else {
            fprintf(f,"+%1.2f(x^%d)", d->coff, d->expo);
            d = d->next;
        }
    }
}


//to save the output to file
void save_to_thefile(){

    FILE *f = fopen("C:\\Users\\user\\CLionProjects\\untitled3\\results.txt", "a");
     if(sl == 0){
     printf("do the operations first !!!");
    }
     else{
         nsum = 1;
         fprinl(add(l[0], l[1]), f);
         fprintf(f, "\n");
         nsub = 1;
         fprinl(subtraction(l[0], l[1]), f);
         nmul = 1;
         fprinl(multiplication(l[0], l[1]), f);
     }
    fclose(f);
}