/**
 * 구조체를 정의하고 선언하는 헤더 파일을 만들고
 * 구조체를 사용하는 다른 파일(메소드 생성 파일)에서는 해당 헤더 파일을 포함시킨다
 * 구조체를 사용하는 다른 파일에서는 해당 구조체를 초기화하거나 수정할 때, 구조체에 대한 포인터를 사용하여 접근한다.
 * 우선 해당 파일에서는 메소드 먼저 구현하고 .h 파일을 만들 때 
 */

// cd method implementation
// 요구되는 헤더 파일 :

#define MAX_DIR 50

int currentMove(DirectoryTree* treeDir, char* pathDir){
    TreeNode* tempNode = NULL;
    
    if(!strcmp(pathDir, "..")){
        // 현재 디렉토리에서 상위 디렉토리로 이동해야함
        // 현재 디렉토리가 최상단 디렉토리라면 더 이상 이동 불가능하므로 예외처리를 위해 확인 요구
        if(treeDir->current == treeDir->root) return 0;
    } else{
        tempNode = dirExistion(treeDir, pathDir, 'd');
        // 이동하고자 하는 디렉토리가 존재하지 않는다면 이동 불가능 반환
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