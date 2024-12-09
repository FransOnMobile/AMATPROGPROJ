#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NOTE_NAME 100
#define MAX_NOTE_LENGTH 1000
#define MAX_CATEGORY_LENGTH 100
#define MAX_DATE_LENGTH 20
#define MAX_NOTES 100

struct Note {
    int noteID;
    char name[MAX_NOTE_NAME];
    char content[MAX_NOTE_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    int priority;
    char date[MAX_DATE_LENGTH];
};


struct Note notes[MAX_NOTES];
int noteCount = 0;

void addNote();
void viewNotesMenu();
void viewAllNotes();
void viewNotesByCategory();
void sortNotesMenu();
void sortNotesByDate();
void sortNotesByTaskName();
void sortNotesByTaskNo();
void sortNotesByPriority();
void editNote();
void deleteNote();
void loadNotes(const char *filename);

// Function for prompting user to add new notes
// Notes are saved to local memory
void addNote() {
    if (noteCount >= MAX_NOTES) {
        printf("Note list is full!\n");
        return;
    }

    notes[noteCount].noteID = noteCount + 1; 
    printf("\nAdding a new note:\n");

    // name
    printf("Enter task name (max 15 chars): ");
    scanf(" %[^\n]", notes[noteCount].name);
    if (strlen(notes[noteCount].name) > 15)
        notes[noteCount].name[15] = '\0';

    // description
    printf("Enter description (max 50 chars): ");
    scanf(" %[^\n]", notes[noteCount].content);
    if (strlen(notes[noteCount].content) > 50)
        notes[noteCount].content[50] = '\0'; 

    // category
    printf("Enter category (Work, School, etc., max 10 chars): ");
    scanf(" %[^\n]", notes[noteCount].category);
    if (strlen(notes[noteCount].category) > 10)
        notes[noteCount].category[10] = '\0';

    // priority
    printf("Enter priority (1: High, 2: Medium, 3: Low): ");
    scanf("%d", &notes[noteCount].priority);
    if (notes[noteCount].priority < 1 || notes[noteCount].priority > 3) {
        printf("*Invalid priority! Priority must be between 1 and 3. Note not added.*\n");
        return;
    }

    // date
    printf("Enter date (YYYY-MM-DD): ");
    scanf("%s", notes[noteCount].date);
    if (strlen(notes[noteCount].date) != 10 || notes[noteCount].date[4] != '-' || notes[noteCount].date[7] != '-') {
        printf("*Invalid date format! Use YYYY-MM-DD. Note not added.*\n");
        return;
    }

    noteCount++;
    printf("*Note added successfully with ID %d!*\n", notes[noteCount - 1].noteID);
}

// Function for showing user a menu for modifying notes
void modifyNotesMenu() {
    int modifyChoice;

    printf("\n--- Modify Notes ---\n");
    printf("1. Edit a note\n");
    printf("2. Delete a note\n");
    printf("Enter your choice: ");
    scanf("%d", &modifyChoice);

    if (modifyChoice == 1)
        editNote();
    else if (modifyChoice == 2)
        deleteNote();
    else
        printf("*Invalid choice!*\n");
}

// Function for showing user a menu for viewing notes
void viewNotesMenu() {
    int viewChoice;

    printf("\n--- View Notes ---\n");
    printf("1. View All Notes\n");
    printf("2. View Notes by Category\n");
    printf("Enter your choice: ");
    scanf("%d", &viewChoice);

    if (viewChoice == 1)
        viewAllNotes();
    else if (viewChoice == 2)
        viewNotesByCategory();
    else
        printf("*Invalid choice!*\n");
}

// Function for viewing all local and file notes
void viewAllNotes() {
    if (noteCount == 0) {
        printf("\n*No notes to display.*\n");
        return;
    }

    printf("\n| %-5s | %-15s | %-50s | %-10s | %-8s | %-10s |\n", "No.", "Task Name", "Description", "Category", "Prio", "Date");
    printf("---------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < noteCount; i++) {
        printf("| %-5d | %-15s | %-50s | %-10s | %-8d | %-10s |\n",
            notes[i].noteID,
            notes[i].name,
            notes[i].content,
            notes[i].category,
            notes[i].priority,
            notes[i].date);
        printf("---------------------------------------------------------------------------------------------------------------------\n");
    }
}

// Function for only viewing notes by user-inputted category
void viewNotesByCategory() {
    char category[MAX_CATEGORY_LENGTH];
    printf("Enter category to filter by: ");
    scanf(" %[^\n]", category);

    printf("\n--- Viewing Notes by Category: %s ---\n", category);
    printf("\n| %-5s | %-15s | %-50s | %-10s | %-8s | %-10s |\n", "No.", "Task Name", "Description", "Category", "Prio", "Date");
    printf("---------------------------------------------------------------------------------------------------------------------\n");

    int found = 0;
    
    // finds and prints the notes that has a matching category as user-inputted category
    for (int i = 0; i < noteCount; i++) {
        if (strcmp((*(&notes[i])).category, category) == 0) {
            printf("| %-5d | %-15s | %-50s | %-10s | %-8d | %-10s |\n",
                   i + 1,
                   (*(&notes[i])).name,
                   (*(&notes[i])).content,
                   (*(&notes[i])).category,
                   (*(&notes[i])).priority,
                   (*(&notes[i])).date);
            printf("---------------------------------------------------------------------------------------------------------------------\n");
            found = 1;
        }
    }

    if (!found) 
        printf("No notes found in the category: %s\n", category);
}

// Function for sorting notes by its date lexicographically
void sortNotesByDate(struct Note *notes, int n, int index) {
    if (index >= n - 1)
        return;

    // finds index of smallest date
    int minIndex = index;
    for (int i = index + 1; i < n; i++) {
        if (strcmp((*(&notes[i])).date, (*(&notes[minIndex])).date) < 0)
            minIndex = i;
    }

    // swaps the smallest element with the current element
    if (minIndex != index) {
        struct Note temp = *(notes + index);
        *(notes + index) = *(notes + minIndex);
        *(notes + minIndex) = temp;
    }

    sortNotesByDate(notes, n, index + 1);
}

// Function for sorting notes by name lexicographically
void sortNotesByTaskName(struct Note *notes, int n, int index) {
    if (index >= n - 1)
        return; 

    // finds index of smallest name
    int minIndex = index;
    for (int i = index + 1; i < n; i++) {
        if (strcmp((*(&notes[i])).name, (*(&notes[minIndex])).name) < 0)
            minIndex = i;
    }

    // swaps the smallest element with the current element
    if (minIndex != index) {
        struct Note temp = *(notes + index);
        *(notes + index) = *(notes + minIndex);
        *(notes + minIndex) = temp;
    }

    sortNotesByTaskName(notes, n, index + 1);
}

// Function for sorting notes by task number lexicographically
void sortNotesByTaskNo(struct Note *notes, int n, int index) {
    if (index >= n - 1)
        return;

    // finds index of smallest num
    int minIndex = index;
    for (int i = index + 1; i < n; i++) {
        if (notes[i].noteID < notes[minIndex].noteID)
            minIndex = i;
    }

    // swaps the smallest element with the current element
    if (minIndex != index) {
        struct Note temp = *(notes + index);
        *(notes + index) = *(notes + minIndex);
        *(notes + minIndex) = temp;
    }

    sortNotesByTaskNo(notes, n, index + 1);
}


// Function for sorting notes by priority number (increasing order)
void sortNotesByPriority(struct Note *notes, int n, int index) {
    if (index >= n - 1)
        return;

    // finds index of the smallest priority
    int minIndex = index;
    for (int i = index + 1; i < n; i++) {
        if ((*(&notes[i])).priority < (*(&notes[minIndex])).priority)
            minIndex = i;
    }

    // swaps the smallest element with the current element
    if (minIndex != index) {
        struct Note temp = *(notes + index);
        *(notes + index) = *(notes + minIndex);
        *(notes + minIndex) = temp;
    }

    sortNotesByPriority(notes, n, index + 1);
}

// Function for showing user a menu for sorting notes
void sortNotesMenu() {
    int choice;

    printf("\n--- Sort Notes ---\n");
    printf("1. By Date\n");
    printf("2. By Task Name\n");
    printf("3. By Task No.\n");
    printf("4. By Priority\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            sortNotesByDate(notes, noteCount, 0);
            printf("*Notes sorted by Date successfully!*\n");
            break;
        case 2:
            sortNotesByTaskName(notes, noteCount, 0);
            printf("*Notes sorted by Task Name successfully!*\n");
            break;
        case 3:
            sortNotesByTaskNo(notes, noteCount, 0);
            printf("*Notes sorted by Task No. successfully!*\n");
            break;
        case 4:
            sortNotesByPriority(notes, noteCount, 0);
            printf("*Notes sorted by Priority successfully!*\n");
            break;
        default:
            printf("*Invalid choice!*\n");
    }
}

// Function for editing notes based on note number
void editNote() {
    int noteID;
    printf("Enter the note ID to edit: ");
    scanf("%d", &noteID);

    // finding the note based on note number
    int index = -1;
    for (int i = 0; i < noteCount; i++) {
        if (notes[i].noteID == noteID) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("*Invalid note ID!*\n");
        return;
    }

    printf("Editing Note %d:\n", notes[index].noteID);

    // task Name
    printf("Enter new task name (max 15 chars): ");
    scanf(" %[^\n]", notes[index].name);
    if (strlen(notes[index].name) > 15) {
        notes[index].name[15] = '\0';
        printf("*Task name too long, truncated to fit the table.*\n");
    }

    // description
    printf("Enter new description (max 50 chars): ");
    scanf(" %[^\n]", notes[index].content);
    if (strlen(notes[index].content) > 50) {
        notes[index].content[50] = '\0';
        printf("*Description too long, truncated to fit the table.*\n");
    }

    // category
    printf("Enter new category (Work, School, etc., max 10 chars): ");
    scanf(" %[^\n]", notes[index].category);
    if (strlen(notes[index].category) > 10) {
        notes[index].category[10] = '\0';
        printf("*Category too long, truncated to fit the table.*\n");
    }

    // priority
    printf("Enter new priority (1: High, 2: Medium, 3: Low): ");
    scanf("%d", &notes[index].priority);
    if (notes[index].priority < 1 || notes[index].priority > 3) {
        printf("*Invalid priority! Priority must be between 1 and 3. Changes not saved.*\n");
        return;
    }

    // date
    printf("Enter new date (YYYY-MM-DD): ");
    scanf("%s", notes[index].date);
    if (strlen(notes[index].date) != 10 || notes[index].date[4] != '-' || notes[index].date[7] != '-') {
        printf("*Invalid date format! Use YYYY-MM-DD. Changes not saved.*\n");
        return;
    }

    printf("*Note updated successfully!*\n");
}


// Function for deleting notes based on note number
void deleteNote() {
    int noteID;
    printf("Enter the note ID to delete: ");
    scanf("%d", &noteID);

    // finding the note based on note number
    int index = -1;
    for (int i = 0; i < noteCount; i++) {
        if (notes[i].noteID == noteID) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("*Invalid note ID!*\n");
        return;
    }

    // shift all notes after the deleted one to fill the gap
    for (int i = index; i < noteCount - 1; i++) {
        notes[i] = notes[i + 1];
    }

    noteCount--;
    printf("*Note deleted successfully!*\n");
}

// Function for saving local memory notes to file
void saveNotes(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("*Failed to save notes to file!*\n");
        return;
    }

    for (int i = 0; i < noteCount; i++) {
        fprintf(file, "%d|%s|%s|%s|%d|%s\n",
            notes[i].noteID,
            notes[i].name,
            notes[i].content,
            notes[i].category,
            notes[i].priority,
            notes[i].date);
    }

    fclose(file);
    printf("*Notes saved to file successfully!*\n");
}

// Function for loading notes in file to local memory
void loadNotes(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("*No file found to load notes from!*\n");
        return;
    }

    // loop for clearing empty values in struct before loading
    for (int i = 0; i < MAX_NOTES; i++) {
        notes[i].noteID = 0;
        notes[i].priority = 0;
        strcpy(notes[i].name, "");
        strcpy(notes[i].content, "");
        strcpy(notes[i].category, "");
        strcpy(notes[i].date, "");
    }

    noteCount = 0; // reset note count before loading

    while (fscanf(file, "%d|%[^|]|%[^|]|%[^|]|%d|%[^\n]\n",
              &notes[noteCount].noteID,
              notes[noteCount].name,
              notes[noteCount].content,
              notes[noteCount].category,
              &notes[noteCount].priority,
              notes[noteCount].date) != EOF) {
        noteCount++;
        
        if (noteCount >= MAX_NOTES) {
            printf("*Maximum notes limit reached while loading!*\n");
            break;
        }
    }

    fclose(file);
    printf("*Notes loaded from file successfully!*\n");
}

// Main function
int main() {
    char filename[] = "saved_notes.txt";
    int choice;
    
    loadNotes(filename);
    
    do {
        printf("\n--- Note-Taking Application ---\n");
        printf("[1] Add a Note\n");
        printf("[2] View Notes\n");
        printf("[3] Sort Notes\n");
        printf("[4] Modify a Note\n");
        printf("[5] Exit\n\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addNote();
                break;
            case 2:
                viewNotesMenu();
                break;
            case 3:
                sortNotesMenu();
                break;
            case 4:
                modifyNotesMenu();
                break;
            case 5:
                saveNotes(filename);
                printf("Saving notes and exiting program. Goodbye!\n");
                break;
            default:
                printf("*Invalid choice!*\n");
        }

    } while (choice != 5);

    return 0;
}
