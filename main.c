

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 50
#define M 30
double currentincome = 0;
double currentexpense = 0;

struct node {
  char date[M];
  double amount;
  char category[N];
  struct node *next;
} *income = NULL, *expense = NULL;

struct record {
  double x, y;
} *point = NULL;

void create(char x[], double y, char z[], struct node **temp);
void display(int a3);
struct node *readnext(struct node *ptr, FILE *fpointer);
void writeincome(struct node *ptr);
void writeexpense(struct node *ptr);
void deleterecord(struct node *ptr);
void deleteIncomeRecord(int id);
void deleteExpenseRecord(int id);
struct node *readincome(struct node *ptr);
struct node *readexpense(struct node *ptr);
void write(struct record *point);
struct record *readrecord();

int main() {
  int option, value;

  double b;
  char c[N], a[M];
  char s1[15], s2[15], s3[15];

  if (fopen("Record.bin", "rb") !=
      NULL) /*first time it will give null bcoz there is no file name
record.bin,therefor it will not take income and expense from file,assign value
will be displayed i.e 0,0..after creating income and expense first time user
exits then record.bin will be create and again  when user runs program then this
if will execute and take income and expense from file*/
  {
    point = readrecord();
    currentincome = point->x;
    currentexpense = point->y;
  }

  if (fopen("myincome.bin", "rb") !=
      NULL) /*it means file is already created and some data is already
           there,and we have to get that and create linked list,address of first
           node will be in income pointer. step bcoz if we dont do this than
             after closing terminal if we create income and saved it than
           previous data will be deleted and it overrides in file...after doing
           this income will point to first node and all data will become in*/
  {
    income = readincome(income);
  }
  if (fopen("myexpense.bin", "rb") != NULL) {
    expense = readexpense(expense);
  }

  do {

    printf("                                           "
           "_______________________________________________\n  ");
    printf("                                         |     YOUR INCOME   =     "
           " %.2lf TND      \n ",
           currentincome);
    printf("                                          |     YOUR EXPENSE  =    "
           "  %.2lf TND     \n ",
           currentexpense);
    printf("                                          |     YOUR BALANCE  =    "
           "  %.2lf TND     \n ",
           currentincome - currentexpense);
    printf("                                          "
           "|_______________________________________________\n");
    printf("ENTER AN OPTION FROM THE BELOW MENU \n\n");
    printf("1.INSERT INCOME \n");
    printf("2.INSERT EXPENSE \n");
    printf("3.VIEW INCOME RECORDS \n");
    printf("4.VIEW EXPENSE RECORDS \n");
    printf("5.DELETE INCOME RECORD\n");
    printf("6.DELETE EXPENSE RECORD\n");
    printf("7.EXIT\n");
    scanf("%d", &option);
    printf("\n\n\n");

    switch (option) {
    case 1:
      printf("**************   ADD INCOME   *****************\n\n");
      printf("Enter The Date(e.g day month year)\n");
      scanf("%s %s %s", s1, s2, s3); // gets,fgets and other functions are not
                                     // working thats why these stepes have done
      strcpy(a, "");
      strcat(a, s1);
      strcat(a, "-");
      strcat(a, s2);
      strcat(a, "-");
      strcat(a, s3);
      printf("Enter The Amount\n");
      scanf("%lf", &b);
      printf("Enter the Category\n");
      scanf("%s", c);

      currentincome = currentincome + b;
      create(a, b, c, &income);
      writeincome(income);

      break;
    case 2:
      printf("**************    ADD EXPENSE   *****************\n\n");
      printf("Enter The Date(e.g day month year)\n");

      scanf("%s %s %s", s1, s2, s3);
      strcpy(a, "");
      strcat(a, s1);
      strcat(a, "-");
      strcat(a, s2);
      strcat(a, "-");
      strcat(a, s3);

      printf("Enter The Amount\n");
      scanf("%lf", &b);
      printf("Enter The Category\n");
      scanf("%s", c);

      currentexpense = currentexpense + b;
      create(a, b, c, &expense);
      writeexpense(expense);

      break;
    case 3:
      printf("*********   YOUR INCOME RECORDS ARE   *******\n\n");
      display(3);
      break;
    case 4:
      printf("*********   YOUR EXPENSE RECORDS ARE   *******\n\n");
      display(4);
      break;
    case 5:
      printf("*********   YOUR INCOME RECORDS ARE   *******\n\n");
      display(3);
      printf("*********   PLEASE PROVIDE THE ID OF THE RECORD TO DELETE "
             "  *******\n\n");
      scanf("%d", &value);
      deleteIncomeRecord(value);
      break;
    case 6:
      printf("*********   YOUR EXPENSE RECORDS ARE   *******\n\n");
      display(4);
      printf("*********   PLEASE PROVIDE THE ID OF THE RECORD TO DELETE "
             "  *******\n\n");
      scanf("%d", &value);
      deleteExpenseRecord(value);
      break;
    case 7:
      point = (struct record *)malloc(sizeof(struct record));
      point->x = currentincome;
      point->y = currentexpense;
      write(point);
      break;
    default:
      printf("WRONG OPTION SELECTED -Enter Valid Option");
      break;
    }
  } while (option != 7);

  return 0;
}

void create(char x[], double y, char z[],
            struct node **temp) /* it isokay to write *temp if we pass only
                                   income rather than &income*/
{
  struct node *newnode, *ptr;
  newnode = (struct node *)malloc(sizeof(struct node));
  if (*temp == NULL) {
    strcpy(newnode->date, x);
    newnode->amount = y;
    strcpy(newnode->category, z);
    newnode->next = NULL;
    *temp = newnode;
  } else {
    ptr = *temp;
    while (ptr->next != NULL) {
      ptr = ptr->next;
    }
    strcpy(newnode->date, x);
    newnode->amount = y;
    strcpy(newnode->category, z);
    newnode->next = NULL;
    ptr->next = newnode;
  }
}

void deleterecord(struct node *ptr) {
  struct node *freeme = ptr;
  struct node *holdme = NULL;
  while (freeme != NULL) {
    holdme = freeme->next;
    free(freeme);
    freeme = holdme;
  }
}

struct node *readnext(struct node *ptr, FILE *fpointer) {

  if (ptr == NULL) {
    ptr = (struct node *)malloc(sizeof(struct node));
    fread(ptr, sizeof(struct node), 1, fpointer);
    ptr->next = NULL;
  } else {
    struct node *ptr1 = ptr;
    struct node *ptr2 = (struct node *)malloc(sizeof(struct node));
    while (ptr1->next != NULL) {
      ptr1 = ptr1->next;
    }
    fread(ptr2, sizeof(struct node), 1, fpointer);
    ptr1->next = ptr2;
    ptr2->next = NULL;
  }
  return ptr;
}

struct node *readincome(struct node *ptr) {
  FILE *fpointer;
  fpointer = fopen("myincome.bin", "rb");
  if (fpointer != NULL) {
    deleterecord(ptr);
    ptr = NULL;
    fseek(fpointer, 0, SEEK_END);
    long filesize = ftell(fpointer);
    rewind(fpointer);
    int entries = (int)(filesize / (sizeof(struct node)));
    for (int i = 0; i < entries; i++) {
      fseek(fpointer, (sizeof(struct node) * i), SEEK_SET);
      ptr = readnext(ptr, fpointer);
    }
  } else {
    printf("ERROR IN OPENINNG FILE\n");
  }
  return ptr;
}

void display(int a3) {
  if (a3 == 3) // if case 3 is executed,we have to print income record
  {

    if (fopen("myincome.bin", "rb") ==
        NULL) /*if user try to view record when there is no any record,i.e when
                user runs program first time and wants to view record i.e there
                is no any file created yet as myincome.bin,then it will =NULL */

    {
      printf("NO RECORDS AVAILABLE\n\n");
      printf("_________________________________________________________________"
             "_______________________________________________\n\n");

    } else {
      // income=readincome(income);
      struct node *ptr2 = income;
      int i = 0;
      while (ptr2 != NULL) {
        i++;
        printf("ID: %d\nDate: %s\nAmount: %.2lf TND\nCategory: %s\n\n", i,
               ptr2->date, ptr2->amount, ptr2->category);
        ptr2 = ptr2->next;
      }
      printf("_________________________________________________________________"
             "_______________________________________________\n\n");
    }
  } else if (a3 ==
             4) // if case 4 is executed then we have to print expenese record
  {

    if (fopen("myexpense.bin", "rb") ==
        NULL) /*if user try to view record when there is no any record,i.e when
               user runs program first time and wants to view record i.e there
               is no any file created yet as myexpense.bin,then it will =NULL */

    {
      printf("NO RECORDS AVAILABLE\n\n");
      printf("_________________________________________________________________"
             "_______________________________________________\n\n");
    } else {

      //   expense=readexpense(expense);
      struct node *ptr2 = expense;
      int i = 0;
      while (ptr2 != NULL) {
        i++;
        printf("ID: %d\nDate: %s\nAmount: %.2lf TND\nCategory: %s\n\n", i,
               ptr2->date, ptr2->amount, ptr2->category);
        ptr2 = ptr2->next;
      }
      printf("_________________________________________________________________"
             "_______________________________________________\n\n");
    }
  }
}

void writeincome(struct node *ptr) {
  FILE *fpointer;
  fpointer = fopen("myincome.bin", "wb");
  if (fpointer != NULL) {
    struct node *ptr1 = ptr;
    struct node *holdnext = NULL;
    while (ptr1 != NULL) {
      holdnext = ptr1->next;
      ptr1->next = NULL;
      fseek(fpointer, 0, SEEK_END);
      fwrite(ptr1, sizeof(struct node), 1,
             fpointer); /*everytime we write into file,it will overwrite the
                           data...... whole data will be deleted and new data
                           willl be written intofile*/
      ptr1->next = holdnext;
      holdnext = NULL;
      ptr1 = ptr1->next;
    }
    fclose(fpointer);
    fpointer = NULL;
    printf("\nINCOME SAVED SUCCESSFULLY\n\n");
    printf("___________________________________________________________________"
           "_____________________________________________\n\n");

  } else {
    printf("\nCANNOT SAVE INCOME..TRY AGAIN\n");
    printf("___________________________________________________________________"
           "_____________________________________________\n\n");
  }
}

void writeexpense(struct node *ptr) {
  FILE *fpointer;
  fpointer = fopen("myexpense.bin", "wb");
  if (fpointer != NULL) {
    struct node *ptr1 = ptr;
    struct node *holdnext = NULL;
    while (ptr1 != NULL) {
      holdnext = ptr1->next;
      ptr1->next = NULL;
      fseek(fpointer, 0, SEEK_END);
      fwrite(ptr1, sizeof(struct node), 1,
             fpointer); /*everytime we write into file,it will overwrite the
                           data..... whole data will be deleted and new data
                           willl be written intofile*/
      ptr1->next = holdnext;
      holdnext = NULL;
      ptr1 = ptr1->next;
    }
    fclose(fpointer);
    fpointer = NULL;
    printf("\nEXPENSE SAVED SUCCESSFULLY\n\n");
    printf("___________________________________________________________________"
           "_____________________________________________\n\n");

  } else {
    printf("\nCANNOT SAVE EXPENSE..TRY AGAIN\n\n");
    printf("___________________________________________________________________"
           "_____________________________________________\n\n");
  }
}

struct node *readexpense(struct node *ptr) {
  FILE *fpointer;
  fpointer = fopen("myexpense.bin", "rb");
  if (fpointer != NULL) {
    deleterecord(ptr);
    ptr = NULL;
    fseek(fpointer, 0, SEEK_END);
    long filesize = ftell(fpointer);
    rewind(fpointer);
    int entries = (int)(filesize / (sizeof(struct node)));
    for (int i = 0; i < entries; i++) {
      fseek(fpointer, (sizeof(struct node) * i), SEEK_SET);
      ptr = readnext(ptr, fpointer);
    }
  } else {
    printf("cannonot open file\n");
  }
  return ptr;
}

void write(struct record *point) {
  FILE *fpointer;
  fpointer = fopen("Record.bin", "wb");
  if (fpointer != NULL) {

    fseek(fpointer, 0, SEEK_END);
    fwrite(point, sizeof(struct record), 1,
           fpointer); /*everytime we write into file,it will overwrite the
                         data..... whole data will be deleted and new data willl
                         be written intofile*/
  } else {
    printf("FILEOPEN ERROR\n");
  }
  fclose(fpointer);
  fpointer = NULL;
}

struct record *readrecord() {
  FILE *fpointer;
  fpointer = fopen("Record.bin", "rb");
  struct record *ptr = NULL;

  if (fpointer != NULL) {

    fseek(fpointer, 0, SEEK_SET);

    ptr = (struct record *)malloc(sizeof(struct record));
    fread(ptr, sizeof(struct record), 1, fpointer);

  } else {
    printf("CANNOT OPEN FILE\n");
  }
  return ptr;
}

void deleteIncomeRecord(int id) {
  struct node *ptr = income;
  struct node *prev = NULL;
  int i = 0;
  while (ptr != NULL) {
    i++;
    if (i == id) {
      if (prev == NULL) {
        income = ptr->next;
        currentincome = currentincome - ptr->amount;
        free(ptr);
        ptr = NULL;
        break;
      } else {
        prev->next = ptr->next;
        currentincome = currentincome - ptr->amount;
        free(ptr);
        ptr = NULL;
        break;
      }
    }
    prev = ptr;
    ptr = ptr->next;
  }
  writeincome(income);
}

void deleteExpenseRecord(int id) {
  struct node *ptr = expense;
  struct node *prev = NULL;
  int i = 0;
  while (ptr != NULL) {
    i++;
    if (i == id) {
      if (prev == NULL) {
        expense = ptr->next;
        currentexpense = currentexpense - ptr->amount;
        free(ptr);
        ptr = NULL;
        break;
      } else {
        prev->next = ptr->next;
        currentexpense = currentexpense - ptr->amount;
        free(ptr);
        ptr = NULL;
        break;
      }
    }
    prev = ptr;
    ptr = ptr->next;
  }
  writeexpense(expense);
}
