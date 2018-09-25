#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OPTIONS 6
#define OPTION_NAME_SIZE    20
#define MENU_NAME_SIZE      20

typedef struct __Option
{
    char name[OPTION_NAME_SIZE];
    char status;
    int *data1;
    int *data2;
} Option;

typedef struct __Menu
{
    char            name[MENU_NAME_SIZE];
    char            menu_items;
    char            selected_item;
    struct __Menu   *next;
    Option          *opt;
} Menu;

char *string_array[] =
{
    "Option 1",
    "Option 2",
    "Option 3",
    "Option 4",
    "Option 5",
    "Option 6"
};

Option * create_menu_list(char **item_list, int items_number)
{
    int i;
    Option *pOptTemp;

    if ((item_list == NULL) || (items_number == 0))
    {
        printf("Error: No items for creating a list.\n");
        return NULL;
    }

    pOptTemp = (Option *)malloc(sizeof(Option) * items_number);

    for (i = 0; i < items_number; i++)
    {
        strcpy(pOptTemp[i].name, item_list[i]);
        pOptTemp[i].data1 = NULL;
        pOptTemp[i].data2 = NULL;
        pOptTemp[i].status = i + 1;
    }

    return pOptTemp;
}

Menu * create_menu(char * pName, Option *pOpt, int menu_items)
{
    Menu *pMenuLocal = NULL;

    pMenuLocal = (Menu *)malloc(sizeof(Menu));

    if ((pName == NULL) || (pName == ""))
    {
        printf("Error: Menu name is missing.\n");
        return NULL;
    }
    if (strlen(pName) > MENU_NAME_SIZE)
    {
        printf("Error: Menu name is invalid.\n");
        return NULL;
    }
    if ((pOpt == NULL) || (menu_items == 0))
    {
        printf("Error: Empty menu. No items detected.\n");
        return NULL;
    }

    pMenuLocal->menu_items = menu_items;
    strcpy(pMenuLocal->name, pName);
    pMenuLocal->opt = pOpt;
    pMenuLocal->next = NULL;
    pMenuLocal->selected_item = 3;

    return pMenuLocal;
}

void print_menu(Menu *pMenu)
{
    int i;

    printf("--------------\n");
    printf("%s\n", pMenu->name);
    printf("--------------\n");
    for (i = 0; i < pMenu->menu_items; i++)
    {
        printf("%c%s\n", (pMenu->selected_item == i) ? '>' : ' ', pMenu->opt[i].name);
    }
    printf("--------------\n");
}

int main()
{
    Option *pMenuList;
    Menu *pMenu;

    pMenuList = create_menu_list(string_array, MAX_OPTIONS);
    pMenu = create_menu("MyMenu", pMenuList, MAX_OPTIONS);

    if (pMenu != NULL)
        print_menu(pMenu);

    free(pMenuList);
    free(pMenu);

    return 0;
}
