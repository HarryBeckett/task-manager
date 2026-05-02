// Librarys
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// Main loop
int main(int argc, char* argv[]) {
    
    // CHECKS BEFORE RUNNING
    
    // Check if there are 3 arguments
    if(argc < 2) {
        printf("Usage: %s | add / remove / list | \"task\"\n", argv[0]);
        printf("List can be ran on it's own, add and remove both need 2 arugemnts (e.g. add \"go shopping\")");
        printf("Note that the task must be in double quotes or only the first word will be inputed\n");
        printf("Use help after executable to see all cases with explanations.");
        return 1;
    }
    



    // ADD FUNCTION
    if(!strcmp(argv[1], "add")) {

        // Check there is a file to add
        if(argc < 3) {
            printf("There is nothing to add to the file. Use the help function to see usage\n");
            return 1;
        }


        FILE *fileptr = fopen("list.txt", "a"); //Create file pointer and open list in append mode

        // Make sure file opened succesfully
        if(fileptr == NULL) {
            printf("Failed to open file");
            return 1;
        }


        fprintf(fileptr, "%s\n", argv[2]); //Write into the file

        fclose(fileptr); //Close file
        printf("Task \"%s\" added succesfully.", argv[2]);
        return 0;
    }





    // LIST FUNCTION
    if(!strcmp(argv[1], "list")) {
        // Allocate memory in the heap to avoid stack overflow
        char* filebuffer = calloc(10000, 1); // This is where the string will be stored when reading form the txt file

        // Check memory was allocated successfully
        if(filebuffer == NULL) {
            printf("Memory was not allocated sucessfully.");
            return 1;
        }
        FILE *fileptr = fopen("list.txt", "r"); // Create a file pointer and open in read mode

        if(fileptr == NULL) { // Check file was opened correctly
            printf("Failed to open file");
            return 1;
        }



        printf("---TODO LIST---\n");

        while(fgets(filebuffer, 10000, fileptr)) { // Write the string to file, 10000 bit buffer for writing, and the file we are getting from. The while look is for each line
            printf("%s", filebuffer); // Print the string that was written to file
        }

        fclose(fileptr); // Close the file
        free(filebuffer); // Free the memory from the heap
        filebuffer = NULL; // avoid folating pointer errors
        return 0;

    }




    // REMOVE FUNCTION

    // 2 ways to remove
    // First one is to list the thing you want then it removes it (exe, remove, "task")
    // Second is to just remove all task (exe, remove, all)

    if(!strcmp(argv[1], "remove")) {

        // check there is something to remove
        if(argc < 3) {
            printf("Use the help function to see usage\n");
            return 1;
        }




        // All task removal
        if(!strcmp(argv[2], "all")) {
            FILE *fileptr = fopen("list.txt", "w");
            fclose(fileptr);
            printf("Sucessfully deleted all tasks.");
            return 0;





        }

        // Specific task removal

        FILE *original_file_ptr = fopen("list.txt", "r"); // Open the original file in read mode 

        FILE *copy_file_ptr = fopen("newlist.txt", "w"); // Create new file in write mode 

        int Found = 0; // Variable to see if you have found the task
        
        char* removaltask = argv[2]; // Make a variable called removal task for readability
        char* currentstring = calloc(1000, 1); // Make a variable to hold the current string read 
        
        // Check memory was allocated successfully
        if (currentstring == NULL) {
            printf("Memory was not allocated successfully.");
            return 1;
        }

        while(fgets(currentstring, 10000, original_file_ptr)) { // Go through every string 
            char *StringSearch = strstr(currentstring, removaltask); // Create a pointer as required by syntax of strstr

            if(StringSearch == NULL) { // Check if it came back with nothing because you're searching FOR the removal task
                fprintf(copy_file_ptr, "%s", currentstring); // copy to the copy file
            } else {
                Found = 1; // If the string does contain the remove task then you have found something so change the varibale to true
            }
        }


        // Close files
        fclose(copy_file_ptr);
        fclose(original_file_ptr);

        remove("list.txt"); // Remove file
        
        rename("newlist.txt", "list.txt"); // Rename file

        if (Found == 1) {
            printf("Succesfully removed task \"%s\"", removaltask); // if sucessful print this
        } else {
            printf("Unable to find task \"%s\"", removaltask); // if not print this
        }
        
        
        // free memory
        free(currentstring);
        currentstring = NULL;
        return 0;
    }




    // HELP FUCTION
    // Simply shows all syntax and help
    if(!(strcmp(argv[1], "help"))) {

        printf("HELP\n\n");

        printf("--ADD--\n");
        printf("The add function requires 2 extra arguments in the format: Executable, add, task\n");
        printf("For example:  main.exe add \"Go Shopping\"\n\n");

        printf("--REMOVE--\n");
        printf("The remove function requires 2 extra arguments in the format: Executable, remove, task\n");
        printf("For example: main.exe remove \"Go Shopping\"\n");
        printf("The remove function is capital sensitive so \"go shopping\" would return a \"Failed to find task\" erorr message\n");
        printf("You can also remove all items on the list using the format: Executable, remove, all\n");
        printf("For this function \"all\" must remain uncapitalised. For this reason you cannot name any task \"all\", however you can name it \"All\"\n\n");

        printf("--LIST--\n");
        printf("The list function only requires 1 extra argument in the format: Executable, list\n");
        printf("This will simply list all tasks in the To-Do list\n\n");

        printf("Any extra arguments used for any of these functions will be treated as \"NULL\" and not affect the program\n");
        printf("e.g.: Executable, add, \"Go Shopping\" will act the same as: Executable, add, \"Go Shopping\", blah\n");
        return 0;


    }

    printf("Commands: add, remove, list"); // I can put this here because I know it was no other commands otherwise it wouldve returned and not gotten to this stage
    return 0;



}
