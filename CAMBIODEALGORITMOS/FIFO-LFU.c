#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define NUM_FRAMES 4   

typedef struct Frame {
    int page;           
    int count;         
    bool valid;         
    struct Frame *prev; 
    struct Frame *next; 
} Frame;

typedef struct FrameList {
    int numFrames;      
    Frame *head;        
    Frame *tail;        
} FrameList;

Frame* createFrame(int page, int count) {
    Frame *frame = (Frame *)malloc(sizeof(Frame));
    if (frame != NULL) {
        frame->page = page; 
        frame->count = count; 
        frame->valid = true;
        frame->prev = NULL;
        frame->next = NULL;
    }
    return frame;
}

FrameList* createFrameList() {
    FrameList *frameList = (FrameList *)malloc(sizeof(FrameList));
    if (frameList != NULL) {
        frameList->numFrames = 0;
        frameList->head = NULL;
        frameList->tail = NULL;
    }
    return frameList;
}

void insertFrame(FrameList *frameList, Frame *frame) {
    if (frameList->head == NULL) {
        frameList->head = frame;
        frameList->tail = frame;
    } else {
        frame->next = frameList->head;
        frameList->head->prev = frame;
        frameList->head = frame;
    }
    frameList->numFrames++;
}

void removeFrame(FrameList *frameList, Frame *frame) {
    if (frame->prev != NULL) {
        frame->prev->next = frame->next;
    } else {
        frameList->head = frame->next;
    }
    if (frame->next != NULL) {
        frame->next->prev = frame->prev;
    } else {
        frameList->tail = frame->prev;
    }
    frameList->numFrames--;
    free(frame);
}

Frame* findFrame(FrameList *frameList, int page) {
    Frame *current = frameList->head;
    while (current != NULL) {
        if (current->page == page) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void loadPage(FrameList *frameList, int page) {
    Frame *frame = findFrame(frameList, page);
    if (frame != NULL) {
        frame->count++;
        return;
    }
    if (frameList->numFrames == NUM_FRAMES) {
        Frame *lfuFrame = frameList->head;
        Frame *current = frameList->head->next;
     while (current != NULL) {
            if (current->count < lfuFrame->count) {
                lfuFrame = current;
            }
            current = current->next;
        }
        removeFrame(frameList, lfuFrame);
    }
    int count = rand() % 10 + 1; 
    frame = createFrame(page, count);
    insertFrame(frameList, frame);
}

void printFrameList(FrameList *frameList) {
    printf("Estado actual de la lista de frames:\n");
    Frame *current = frameList->head;
    while (current != NULL) {
        printf("Pagina: %d, Conteo: %d, ", current->page, current->count);
        if (current->valid) {
            printf("Estado: Ocupado\n");
        } else {
            printf("Estado: Vacio\n");
        }
        current = current->next;
    }
    printf("\n");
}

int main() {
    srand(time(NULL)); 
    FrameList *frameList = createFrameList();
    for (int i = 0; i < 5; i++) {
        loadPage(frameList, 1);
        loadPage(frameList, 2);
        loadPage(frameList, 3);
        loadPage(frameList, 4);
        printFrameList(frameList);  
        loadPage(frameList, 5);
        printFrameList(frameList);  
    }
    free(frameList);

    return 0;
}
