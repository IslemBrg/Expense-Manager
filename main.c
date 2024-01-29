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

void create(char x[], double y, char z[], struct node **temp);
void display(int a3);
struct node *readnext(struct node *ptr, FILE *fpointer);
void writeincome(struct node *ptr);
void writeexpense(struct node *ptr);
void deleterecords(struct node *ptr);
void deleteIncomeRecord(int id);
void deleteExpenseRecord(int id);
void updateIncomeRecord(int id);
void updateExpenseRecord(int id);
struct node *readincome(struct node *ptr);
struct node *readexpense(struct node *ptr);
void verifyAndUpdateIncome();
void verifyAndUpdateExpense();
void credits();

int main() {
  system("clear");
  credits();
  int option, value;

  double b;
  char c[N], a[M];
  char s1[15], s2[15], s3[15];

  if (fopen("myincome.bin", "rb") !=
      NULL)
  {
    income = readincome(income);
  }
  if (fopen("myexpense.bin", "rb") != NULL) {
    expense = readexpense(expense);
  }

  do {

    verifyAndUpdateIncome(); 
    verifyAndUpdateExpense();

    printf("                                           "
           " _______________________________________________\n  ");
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
    printf("5.UPDATE INCOME RECORD\n");
    printf("6.UPDATE EXPENSE RECORD\n");
    printf("7.DELETE INCOME RECORD\n");
    printf("8.DELETE EXPENSE RECORD\n");
    printf("9.EXIT\n");
    printf("\n");
    printf("OPTION: ");
    scanf(" %d", &option);
    printf("\n\n\n");

    switch (option) {
    case 1:
      printf("**************   ADD INCOME   *****************\n\n");
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
      printf("Enter the Category\n");
      scanf("%s", c);

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
      printf("*********   PLEASE PROVIDE THE ID OF THE RECORD TO UPDATE "
             "  *******\n\n");
      scanf("%d", &value);
      updateIncomeRecord(value);
      break;
    case 6:
      printf("*********   YOUR EXPENSE RECORDS ARE   *******\n\n");
      display(4);
      printf("*********   PLEASE PROVIDE THE ID OF THE RECORD TO UPDATE "
             "  *******\n\n");
      scanf("%d", &value);

      break;
    case 7:
      printf("*********   YOUR INCOME RECORDS ARE   *******\n\n");
      display(3);
      printf("*********   PLEASE PROVIDE THE ID OF THE RECORD TO DELETE "
             "  *******\n\n");
      scanf("%d", &value);
      deleteIncomeRecord(value);
      break;
    case 8:
      printf("*********   YOUR EXPENSE RECORDS ARE   *******\n\n");
      display(4);
      printf("*********   PLEASE PROVIDE THE ID OF THE RECORD TO DELETE "
             "  *******\n\n");
      scanf("%d", &value);
      deleteExpenseRecord(value);
      break;
    case 9:
      printf("*********   THANK YOU FOR USING OUR APPLICATION   "
             "*******\n\n");
      break;
    default:
      printf("WRONG OPTION SELECTED -Enter Valid Option");
      break;
    }
  } while (option != 9);
  return 0;
}

void create(char x[], double y, char z[],
            struct node **temp)
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

void deleterecords(struct node *ptr) {
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
    deleterecords(ptr);
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
  if (a3 == 3)
  {

    if (fopen("myincome.bin", "rb") ==
        NULL) 

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
             4)
  {

    if (fopen("myexpense.bin", "rb") ==
        NULL)

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
             fpointer); 
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
             fpointer); 
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
    deleterecords(ptr);
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

void deleteIncomeRecord(int id) {
  struct node *ptr = income;
  struct node *prev = NULL;
  int i = 0;
  while (ptr != NULL) {
    i++;
    if (i == id) {
      if (prev == NULL) {
        income = ptr->next;
        free(ptr);
        ptr = NULL;
        break;
      } else {
        prev->next = ptr->next;
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
        free(ptr);
        ptr = NULL;
        break;
      } else {
        prev->next = ptr->next;
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

void updateIncomeRecord(int id) {
  struct node *ptr = income;
  int i = 0;
  char s1[15], s2[15], s3[15];

  while (ptr != NULL) {
    i++;
    if (i == id) {
      printf("Enter the updated Date (e.g., day month year): ");
      scanf("%s %s %s", s1, s2, s3); 
      strcpy(ptr->date, "");
      strcat(ptr->date, s1);
      strcat(ptr->date, "-");
      strcat(ptr->date, s2);
      strcat(ptr->date, "-");
      strcat(ptr->date, s3);

      printf("Enter the updated Amount: ");
      scanf("%lf", &ptr->amount);

      printf("Enter the updated Category: ");
      scanf("%s", ptr->category);

      printf("Income record with ID %d updated successfully.\n", id);
      writeincome(income);
      return;
    }

    ptr = ptr->next;
  }

  
  printf("Income record with ID %d not found.\n", id);
}

void updateExpenseRecord(int id) {
  struct node *ptr = expense;
  int i = 0;

  while (ptr != NULL) {
    i++;
    if (i == id) {
      
      printf("Enter the updated Date (e.g., day month year): ");
      scanf("%s %s %s", ptr->date, ptr->date + 3, ptr->date + 8);

      printf("Enter the updated Amount: ");
      scanf("%lf", &ptr->amount);

      printf("Enter the updated Category: ");
      scanf("%s", ptr->category);


      printf("Expense record with ID %d updated successfully.\n", id);
      writeexpense(expense);
      return;
    }

    ptr = ptr->next;
  }

  printf("Expense record with ID %d not found.\n", id);
}

void verifyAndUpdateIncome() {
  double totalIncome = 0.0;

  struct node *ptr = income;
  while (ptr != NULL) {
    totalIncome += ptr->amount;
    ptr = ptr->next;
  }

  currentincome = totalIncome;
}

void verifyAndUpdateExpense() {
  double totalExpense = 0.0;

  struct node *ptr = expense;
  while (ptr != NULL) {
    totalExpense += ptr->amount;
    ptr = ptr->next;
  }

  currentexpense = totalExpense;
}

void credits() {
  int terminalWidth = 80;

  int padding =
      (terminalWidth - 39) / 2;

  printf("%*s*********   APPLICATION DEVELOPED BY   *******\n", padding, "");
  printf("%*s*********   1. MOHAMED MAHDI CHIHAOUI  *******\n", padding, "");
  printf("%*s*********   2. ISLEM BARGAOUI          *******\n", padding, "");
  printf("%*s*********   3. OUMAIMA AYARI           *******\n\n\n", padding,
         "");
}