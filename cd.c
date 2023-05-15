/**
 * ����ü�� �����ϰ� �����ϴ� ��� ������ �����
 * ����ü�� ����ϴ� �ٸ� ����(�޼ҵ� ���� ����)������ �ش� ��� ������ ���Խ�Ų��
 * ����ü�� ����ϴ� �ٸ� ���Ͽ����� �ش� ����ü�� �ʱ�ȭ�ϰų� ������ ��, ����ü�� ���� �����͸� ����Ͽ� �����Ѵ�.
 * �켱 �ش� ���Ͽ����� �޼ҵ� ���� �����ϰ� .h ������ ���� �� 
 */

// cd method implementation
// �䱸�Ǵ� ��� ���� :

#define MAX_DIR 50

int currentMove(DirectoryTree* treeDir, char* pathDir){
    TreeNode* tempNode = NULL;
    
    if(!strcmp(pathDir, "..")){
        // ���� ���丮���� ���� ���丮�� �̵��ؾ���
        // ���� ���丮�� �ֻ�� ���丮��� �� �̻� �̵� �Ұ����ϹǷ� ����ó���� ���� Ȯ�� �䱸
        if(treeDir->current == treeDir->root) return 0;
    } else{
        tempNode = dirExistion(treeDir, pathDir, 'd');
        // �̵��ϰ��� �ϴ� ���丮�� �������� �ʴ´ٸ� �̵� �Ұ��� ��ȯ
        if(tempNode == NULL) return -1;
        treeDir->current = tempNode;
    }
    return 0;
}

int pathMove(DirectoryTree* treeDir, char* pathDir){
    TreeNode* tempNode = NULL;
    char tempPath[MAX_DIR];
    char* str = NULL;
    int moving = 0;

    stncpy(tempPath, pathDir, MAX_DIR);
    tempNode = treeDir->current;

    // Move Top Node
    if(!strcmp(pathDir, "/")){
        treeDir->current = treeDir->root;
    } else{
        // Input -> Absolute Route Path
        if(!strcmp(pathDir, "/", 1)){
            if(strtok(pathDir, "/") == NULL) return -1;
            treeDir->current = treeDir->root;
        }
        // Input -> Relative Route Path
        str = strtok(tempPath, "/");
        while(str != NULL){
            moving = currentMove(treeDir, str);
            // If Input Path doesn't exist?
            if(moving != 0){
                treeDir->current = tempNode;
                return -1;
            }
            str = strtok(NULL, "/");
        }
    }
    return 0;
}