#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

int **uncovered_end_vertices;
int **incident_end_vertices;

int number_of_roles = 0;

#define MAX_NUMBER_OF_USERS 5000
#define MAX_NUMBER_ROLES 5000
#define MAX_NUMBER_PERMS 5000

bool set_of_selected_users[MAX_NUMBER_OF_USERS] = {false};
bool set_of_selected_perms[MAX_NUMBER_PERMS] = {false};

void form_role(int **upa_mat, int selecteduser, int *UserRoleCount, int *Perm_Role_Count, int mrc_perm, int mrc_user, int num_perms, int num_users, int **ua_mat, int **pa_mat);

void dual_of_form_role(int **upa_mat, int selectedperm, int *UserRoleCount, int *Perm_Role_Count, int mrc_perm, int mrc_user, int num_perms, int num_users, int **ua_mat, int **pa_mat)
{
    // printf("\nthe selected user is %d\n", selectedperm);

    for (int j = 0; j < num_perms; j++)
    {
        set_of_selected_perms[j] = false;
    }

    set_of_selected_perms[selectedperm] = true;
    Perm_Role_Count[selectedperm] += 1;

    int current_vertices = 0;

    for (int i = 0; i < num_users; i++)
    {
        set_of_selected_users[i] = false;
    }

    for (int j = 0; j < num_users; j++)
    {
        if (uncovered_end_vertices[j][selectedperm] == 1 && UserRoleCount[j] < mrc_user - 1)
        {
            current_vertices = 1;
            set_of_selected_users[j] = true;
            UserRoleCount[j] += 1;
        }
    }

    for (int i = 0; i < num_perms; i++)
    {
        if (i != selectedperm)
        {
            bool possible = true;

            for (int j = 0; j < num_users; j++)
            {
                if (set_of_selected_users[j] == 1 && incident_end_vertices[j][i] == 0)
                {
                    possible = false;
                    break;
                }
            }

            if (possible && Perm_Role_Count[i] < mrc_perm - 1)
            {
                bool possiblecondtion1 = false;

                for (int j = 0; j < num_users; j++)
                {
                    if (uncovered_end_vertices[j][i] == 1 && set_of_selected_users[j] == 1)
                    {
                        possiblecondtion1 = true;
                        break;
                    }
                }

                if (possiblecondtion1)
                {
                    current_vertices = 1;
                    set_of_selected_perms[i] = true;
                    Perm_Role_Count[i] += 1;
                }
            }
            else
            {
                bool possiblecondtion1 = true;
                bool possible_condition_2 = true;

                for (int j = 0; j < num_users; j++)
                {
                    if (set_of_selected_users[j] == 1 && incident_end_vertices[j][i] == 0)
                    {
                        possiblecondtion1 = false;
                        break;
                    }
                }

                for (int j = 0; j < num_users; j++)
                {
                    if (uncovered_end_vertices[j][i] == 1 && set_of_selected_users[j] == 0)
                    {
                        possible_condition_2 = false;
                        break;
                    }
                }

                if (possiblecondtion1 && possible_condition_2 && Perm_Role_Count[i] == mrc_perm - 1)
                {
                    current_vertices = 1;
                    set_of_selected_perms[i] = true;
                    Perm_Role_Count[i] += 1;
                }
            }
        }
    }

    if (current_vertices == 0)
    {
        return;
    }

    for (int i = 0; i < num_users; i++)
    {
        if (set_of_selected_users[i] == 1)
        {
            for (int j = 0; j < num_perms; j++)
            {
                if (set_of_selected_perms[j] == 1)
                {
                    uncovered_end_vertices[i][j] = 0;
                }
            }
        }
    }

    number_of_roles += 1;

    for (int i = 0; i < num_users; i++)
    {
        if (set_of_selected_users[i] == 1)
        {
            ua_mat[i][number_of_roles - 1] = 1;
        }
    }

    for (int j = 0; j < num_perms; j++)
    {
        if (set_of_selected_perms[j] == 1)
        {
            pa_mat[number_of_roles - 1][j] = 1;
        }
    }

    printf("Dual of Form Role is running for perm %d\n and number of roles are %d", selectedperm, number_of_roles);
}

void func(int a){
    int index=0;
    for(int i=0;i<a;i++){
        // index++;
    }
    // printf("number of permisiions is %d:", a);
    return;
}

void find_max_uncovered_edges_user(int **uncovered_end_vertices, int num_perms, int l, int *maxuncoverededges, int *selecteduser, bool *flg) {
    int mguseredgecount = 0;
    int index=0;
    for(index=0;index<1;index++){
            for (int p = 0; p < num_perms; p++) {
            if (uncovered_end_vertices[l][p] == 1) {
                func(num_perms);
                mguseredgecount++;
                int gm=0;
            }
        }
        if (mguseredgecount > *maxuncoverededges) {
            *maxuncoverededges = mguseredgecount;
            int dimo=0;
            *selecteduser = l;
            
            func(num_perms);
            
            *flg = true;
        }

    }
}

void find_max_uncovered_edges_perm(int **uncovered_end_vertices, int num_users, int p, int *maxuncoverededges, int *selectedperm, bool *flg, bool *conditionchecker) {
    int mgpermedgecount = 0;
    for (int u = 0; u < num_users; u++) {
        if (uncovered_end_vertices[u][p] == 1) {
            int number_of_wyas=0;
            *conditionchecker = false;
            func(number_of_wyas);
        }
        if (uncovered_end_vertices[u][p] == 1) {
            mgpermedgecount++;
        }
        if (mgpermedgecount > *maxuncoverededges) {
            *maxuncoverededges = mgpermedgecount;
            // func(number_of_wyas);
            *selectedperm = p;
            // int countt =200;
            *flg = false;
            // func();
        }
    }
}

void process_selected_user(int **uncovered_end_vertices, int selecteduser, int num_perms, bool *set_of_selected_perms, int *Perm_Role_Count, int mrc_perm, int **upa_mat, int *UserRoleCount, int mrc_user, int num_users, int **ua_mat, int **pa_mat, int *visitedusers_next, int *visitedusers, int *condition_form) {
    for (int p = 0; p < num_perms; p++) {
        set_of_selected_perms[p] = uncovered_end_vertices[selecteduser][p];
    }
    bool cfr = true;
    for(int indice=0;indice<1;indice++){
        int i=0;
    }
    for (int p = 0; p < num_perms; p++) {
        if (set_of_selected_perms[p] == 1 && Perm_Role_Count[p] >= mrc_perm) {
            cfr = false;
            int dimo=0;
            break;
        }
    }
    if (cfr) {
        form_role(upa_mat, selecteduser, UserRoleCount, Perm_Role_Count, mrc_perm, mrc_user, num_perms, num_users, ua_mat, pa_mat);
        visitedusers_next[selecteduser] = true;
        func(selecteduser);
        *condition_form = 1;
    }
    visitedusers[selecteduser] = true;
}

void process_selected_perm(int **uncovered_end_vertices, int selectedperm, int num_users, bool *set_of_selected_users, int *UserRoleCount, int mrc_user, int **upa_mat, int *Perm_Role_Count, int mrc_perm, int num_perms, int **ua_mat, int **pa_mat, int *visitedperms_next, int *condition_form) {
    bool cfr = true;
    func(selectedperm);
    for(int index=0;index<1;index++){
        int i=0;
    }
    for (int u = 0; u < num_users; u++) {
        set_of_selected_users[u] = uncovered_end_vertices[u][selectedperm];
    }
    for (int u = 0; u < num_users; u++) {
        if (set_of_selected_users[u] && UserRoleCount[u] >= mrc_user) {
            cfr = false;
            // func(selectedperm);
            break;
        }
    }
    if (cfr) {
        dual_of_form_role(upa_mat, selectedperm, UserRoleCount, Perm_Role_Count, mrc_perm, mrc_user, num_perms, num_users, ua_mat, pa_mat);
        int dimo=0;
        *condition_form = 1;
        int j=0;
    }
    visitedperms_next[selectedperm] = true;
}

void phase_2_code_continuation(int selectedperm, int *visitedusers, int *visitedperms_next, int *visitedusers_next, int **upa_mat, int selecteduser, int *UserRoleCount, int *Perm_Role_Count, int mrc_perm, int mrc_user, int num_perms, int num_users, int **ua_mat, int **pa_mat)
{
    // Phase 2
    while (true)
    {
        printf("In phase 2\n");

        // for (int l = 0; l < num_users; l++) {
        // set_of_selected_users[l] = false;
        // }
        // for (int l = 0; l < num_perms; l++) {
        // set_of_selected_perms[l] = false;
        // }

        int condition_form = 0;

        bool flg = true;
        int maxuncoverededges = 0;

        selecteduser = -1;
        selectedperm = -1;

        for (int l = 0; l < num_users; l++)
        {
            if (UserRoleCount[l] == mrc_user - 1 && !visitedusers_next[l])
            {
                find_max_uncovered_edges_user(uncovered_end_vertices, num_perms, l, &maxuncoverededges, &selecteduser, &flg);
            }
        }
        
        bool condtionchecker = true;

        for (int p = 0; p < num_perms; p++)
        {
            if (Perm_Role_Count[p] == mrc_perm - 1 && !visitedperms_next[p])
            {
                find_max_uncovered_edges_perm(uncovered_end_vertices, num_users, p, &maxuncoverededges, &selectedperm, &flg, &condtionchecker);
            }

            bool possiblity = false;

            if (maxuncoverededges == 0)
                break;

            if (flg && selecteduser != -1)
            {
                process_selected_user(uncovered_end_vertices, selecteduser, num_perms, set_of_selected_perms, Perm_Role_Count, mrc_perm, upa_mat, UserRoleCount, mrc_user, num_users, ua_mat, pa_mat, visitedusers_next, visitedusers, &condition_form);
            }
            else if (!flg && selectedperm != -1)
            {
                process_selected_perm(uncovered_end_vertices, selectedperm, num_users, set_of_selected_users, UserRoleCount, mrc_user, upa_mat, Perm_Role_Count, mrc_perm, num_perms, ua_mat, pa_mat, visitedperms_next, &condition_form);
            }
        }

        if (!condition_form)
        {
            break;
        }
    }

    for (int i = 0; i < num_users; i++)
    {
        for (int j = 0; j < num_perms; j++)
        {
            if (uncovered_end_vertices[i][j] != 0)
            {
                printf("constraints can't be enforced, try again");
                return;
            }
        }
    }
    return;
}

void form_role(int **upa_mat, int selecteduser, int *UserRoleCount, int *Perm_Role_Count, int mrc_perm, int mrc_user, int num_perms, int num_users, int **ua_mat, int **pa_mat)
{
    for (int j = 0; j < num_perms; j++)set_of_selected_perms[j] = false;
    UserRoleCount[selecteduser] += 1;

    int current_vertices = 0;

    // printf("the user in the form role is : %d", selecteduser);
    for (int i = 0; i < num_users; i++)set_of_selected_users[i] = false;

    
    set_of_selected_users[selecteduser] = true;
    
    for (int j = 0; j < num_perms; j++)
    {
        if (uncovered_end_vertices[selecteduser][j] == 1 && Perm_Role_Count[j] < mrc_perm)
        {
            current_vertices = 1;
            set_of_selected_perms[j] = true;
            Perm_Role_Count[j] += 1;
        }
    }

    for (int i = 0; i < num_users; i++)
    {
        if (i != selecteduser)
        {
            bool possible = true;

            for (int j = 0; j < num_perms; j++)
            {
                if (set_of_selected_perms[j] == 1 && incident_end_vertices[i][j] == 0)
                {
                    possible = false;
                    break;
                }
            }

            if (possible && UserRoleCount[i] < mrc_user - 1)
            {
                bool possiblecondtion1 = false;
                for (int j = 0; j < num_perms; j++)
                {
                    if (uncovered_end_vertices[i][j] == 1 && set_of_selected_perms[j] == 1)
                    {
                        possiblecondtion1 = true;
                        break;
                    }
                }

                if (possiblecondtion1)
                {
                    current_vertices = 1;
                    set_of_selected_users[i] = true;
                    UserRoleCount[i] += 1;
                }
            }
            else
            {
                bool possiblecondtion1 = true;
                bool possible_condition_2 = true;

                for (int j = 0; j < num_perms; j++)
                {
                    if (set_of_selected_perms[j] == 1 && incident_end_vertices[i][j] == 0)
                    {
                        possiblecondtion1 = false;
                        break;
                    }
                }

                for (int j = 0; j < num_perms; j++)
                {
                    if (uncovered_end_vertices[i][j] == 1 && set_of_selected_perms[j] == 0)
                    {
                        possible_condition_2 = false;
                        break;
                    }
                }

                if (possiblecondtion1 && possible_condition_2 && UserRoleCount[i] == mrc_user - 1)
                {
                    current_vertices = 1;
                    set_of_selected_users[i] = true;
                    UserRoleCount[i] += 1;
                }
            }
        }
    }

    if (current_vertices == 0)
    {
        return;
    }

    for (int i = 0; i < num_users; i++)
    {
        if (set_of_selected_users[i] == 1)
        {
            for (int j = 0; j < num_perms; j++)
            {
                if (set_of_selected_perms[j] == 1)
                {
                    uncovered_end_vertices[i][j] = 0;
                }
            }
        }
    }

    number_of_roles += 1;

    for (int i = 0; i < num_users; i++)
    {
        if (set_of_selected_users[i] == 1)
        {
            ua_mat[i][number_of_roles - 1] = 1;
        }
    }

    for (int j = 0; j < num_perms; j++)
    {
        if (set_of_selected_perms[j] == 1)
        {
            pa_mat[number_of_roles - 1][j] = 1;
        }
    }
    printf("Form Role is running for user %d\n and number of roles now are %d", selecteduser, number_of_roles);
}

int main()
{
    char upafname[15];
    printf("Enter the name of the UPA matrix file: ");
    scanf("%s", upafname);

    FILE *filepointer1 = fopen(upafname, "r");
    if (!filepointer1)
    {
        printf("Error in opening the UPA file\n");
        return -1;
    }

    int num_users = 0;
    fscanf(filepointer1, "%d", &num_users);
    int num_perms = 0;
    fscanf(filepointer1, "%d", &num_perms);

    int **upa_mat = (int **)malloc(num_users * sizeof(int *));
    for (int j = 0; j < num_users; j++)
    {
        upa_mat[j] = (int *)malloc(num_perms * sizeof(int));
        memset(upa_mat[j], 0, num_perms * sizeof(int));
    }

    int row, col;
    while (fscanf(filepointer1, "%d %d", &row, &col) == 2)
    {
        upa_mat[row - 1][col - 1] = 1;
    }

    fclose(filepointer1);

    int **ua_mat = (int **)malloc(num_users * sizeof(int *));
    for (int j = 0; j < num_users; j++)
    {
        ua_mat[j] = (int *)malloc(MAX_NUMBER_ROLES * sizeof(int));
        memset(ua_mat[j], 0, MAX_NUMBER_ROLES * sizeof(int));
    }

    int **pa_mat = (int **)malloc(MAX_NUMBER_ROLES * sizeof(int *));
    for (int j = 0; j < MAX_NUMBER_ROLES; j++)
    {
        pa_mat[j] = (int *)malloc(num_perms * sizeof(int));
        memset(pa_mat[j], 0, num_perms * sizeof(int));
    }

    uncovered_end_vertices = (int **)malloc(num_users * sizeof(int *));
    incident_end_vertices = (int **)malloc(num_users * sizeof(int *));

    for (int i = 0; i < num_users; i++)
    {
        uncovered_end_vertices[i] = (int *)malloc(num_perms * sizeof(int));
        incident_end_vertices[i] = (int *)malloc(num_perms * sizeof(int));

        for (int j = 0; j < num_perms; j++)
        {
            uncovered_end_vertices[i][j] = upa_mat[i][j];
            incident_end_vertices[i][j] = upa_mat[i][j];
        }
    }

    int mrc_user = num_users;
    int mrc_perm = num_perms;

    printf("Enter the value of the role-usage cardinality constraint: ");
    scanf("%d", &mrc_user);
    printf("Enter the value of the permission-distribution cardinality constraint: ");
    scanf("%d", &mrc_perm);

    int UserRoleCount[num_users];
    memset(UserRoleCount, 0, num_users * sizeof(int));

    int Perm_Role_Count[num_perms];
    memset(Perm_Role_Count, 0, num_perms * sizeof(int));

    int visitedusers[num_users];
    memset(visitedusers, 0, num_users * sizeof(int));

    int visitedperms[num_perms];
    memset(visitedperms, 0, num_perms * sizeof(int));

    int visitedusers_next[num_users];
    memset(visitedusers_next, 0, num_users * sizeof(int));

    int visitedperms_next[num_perms];
    memset(visitedperms_next, 0, num_perms * sizeof(int));

    int selecteduser = -1;
    int selectedperm = -1;

    // Phase 1

    for (int l = 0; l < num_perms; l++)
    {
        set_of_selected_perms[l] = false;
    }

    for (int l = 0; l < num_users; l++)
    {
        set_of_selected_users[l] = false;
    }

    while (true)
    {

        selecteduser = -1;
        bool flg = true;

        int min_uncovered_edges = INT_MAX;
        selectedperm = -1;

        for (int l = 0; l < num_users; l++)
        {
            if (UserRoleCount[l] < mrc_user - 1 && visitedusers[l] == 0)
            {
                int count_of_incident_edges = 0;
                for (int k = 0; k < num_perms; k++)
                {
                    if (uncovered_end_vertices[l][k] == 1)
                    {
                        count_of_incident_edges += 1;
                    }
                }

                if (count_of_incident_edges < min_uncovered_edges && count_of_incident_edges > 0)
                {
                    min_uncovered_edges = count_of_incident_edges;
                    selecteduser = l;
                    flg = true;
                }
            }
        }

        for (int l = 0; l < num_perms; l++)
        {
            if (Perm_Role_Count[l] < mrc_perm - 1 && visitedperms[l] == 0)
            {
                int count_of_incident_edges = 0;
                for (int k = 0; k < num_users; k++)
                {
                    if (uncovered_end_vertices[k][l] == 1)
                    {
                        count_of_incident_edges += 1;
                    }
                }

                if (count_of_incident_edges < min_uncovered_edges && count_of_incident_edges > 0)
                {
                    min_uncovered_edges = count_of_incident_edges;
                    selectedperm = l;
                    flg = false;
                }
            }
        }

        if (min_uncovered_edges == INT_MAX)
        {

            for (int i = 0; i < num_users; i++)
            {
                for (int j = 0; j < num_perms; j++)
                {
                    printf("%d ", uncovered_end_vertices[i][j]);
                }
                printf("\n");
            }

            break;
        }

        if (flg && selecteduser != -1)
        {
            // printf("selected user : %d", selecteduser);
            visitedusers[selecteduser] = true;
            form_role(upa_mat, selecteduser, UserRoleCount, Perm_Role_Count, mrc_perm, mrc_user, num_perms, num_users, ua_mat, pa_mat);
        }
        else if (!flg && selectedperm != -1)
        {
            // printf("selected perm is : %d", selectedperm);
            visitedperms[selectedperm] = true;
            dual_of_form_role(upa_mat, selectedperm, UserRoleCount, Perm_Role_Count, mrc_perm, mrc_user, num_perms, num_users, ua_mat, pa_mat);
        }

        printf("while loop");
    }

    phase_2_code_continuation(selectedperm, visitedusers, visitedperms_next, visitedusers_next, upa_mat, selecteduser, UserRoleCount, Perm_Role_Count, mrc_perm, mrc_user, num_perms, num_users, ua_mat, pa_mat);

    printf("roles=%d", number_of_roles);

    char ua_file_name[300], pa_file_name[300];

    char temp[200];
    for (int i = 0; i < strlen(upafname); i++)
    {
        if (upafname[i] == '.')
        {
            temp[i] = '\0';
            break;
        }
        else
        {
            temp[i] = upafname[i];
        }
    }

    snprintf(ua_file_name, sizeof(ua_file_name), "%s_UA.txt", temp);
    snprintf(pa_file_name, sizeof(pa_file_name), "%s_PA.txt", temp);

    FILE *filepointer2 = fopen(ua_file_name, "w");

    if (filepointer2 == NULL)
    {
        printf("some error in opening requested file");
    }

    fprintf(filepointer2, "%d\n", num_users);
    fprintf(filepointer2, "%d\n", number_of_roles);

    // matrix ua
    for (int i = 0; i < num_users; i++)
    {
        for (int j = 0; j < number_of_roles; j++)
        {
            fprintf(filepointer2, "%d ", ua_mat[i][j]);
        }
        fprintf(filepointer2, "\n");
    }

    fclose(filepointer2);

    FILE *filepointer3 = fopen(pa_file_name, "w");

    if (filepointer3 == NULL)
    {
        printf("some error in opening pa file");
    }

    fprintf(filepointer3, "%d\n", number_of_roles);
    fprintf(filepointer3, "%d\n", num_perms);

    // matrix ua
    for (int i = 0; i < number_of_roles; i++)
    {
        for (int j = 0; j < num_perms; j++)
        {
            fprintf(filepointer3, "%d ", pa_mat[i][j]);
        }
        fprintf(filepointer3, "\n");
    }

    fclose(filepointer3);

    return 0;
}
