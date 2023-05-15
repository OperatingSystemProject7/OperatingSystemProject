#define MAX_BUFFER 512
#define MAX_NAME 20

int conCatenate(DirectoryTree* treeDir, char* fName, int o){
    UserNode* tempUser = NULL;
    TreeNode* tempNode = NULL;
    FILE* fp;

    char* str;
    char buffer[MAX_BUFFER];
    char tempName[MAX_NAME];

    int cnt = 1;
    int tempSize = 0;

    // File 읽는 기능 동작
    if(o){
        if(o==4){
            tempUser = UserList->head;
            while(tempUser != NULL){
                printf("%s:x:%d:%d:%s:%s\n", tempUser->name, tempUser->UID, tempUser->GID, tempUser->name, tempUser->dir);
                tempUser = tempUser->LinkNode;
            }
            return 0;
        }
        tempNode = DirExistion(treeDir, fName, 'f');
        if(tempNode == -1) return -1;

        fp = fopen(fName, "r");
        while(feof(fp)) {
            fgets(buffer, sizeof(buffer), fp);
            if (feof(fp)) {
                break;
            }
            switch (o){
            case 2:
                if (buffer[strlen(buffer)-1] == '\n') {
                    printf("     %d ", cnt);
                    cnt++;
                }
                break;
            case 3:
                if (buffer[strlen(buffer)-1] == '\n' && buffer[0] != '\n') {
                    printf("     %d ", cnt);
                    cnt++;
                }
            }
            fputs(buffer, stdout);
        }
        fclose(fp);
    } else{
        fp = fopen(fName, "w");
        while (strcmp(buffer, ":wq") != 0|| strcmp(buffer, ":q") != 0) {
            gets(buffer);
            if (strcmp(buffer, ":wq") == 0 || strcmp(buffer, ":q") == 0) break;
            fprintf(fp, "%s\n", buffer);
            tempSize += strlen(buffer) - 1;
        }
        fclose(fp);

        tempNode = dirExistion(treeDir, fName, 'f');
        if (tempNode != NULL) {
            time(&ltime);
            today = localtime(&ltime);
            tempNode->month = today->tm_mon + 1;
            tempNode->day = today->tm_mday;
            tempNode->hour = today->tm_hour;
            tempNode->min = today->tm_min;
        }
        else {
            MakeDir(treeDir, fName, 'f');
        }
        tempNode = dirExistion(treeDir, fName, 'f');
        tempNode->SIZE = tempSize;
    }
    return 0;
}