#ifndef _HW2_H
#define _HW2_H

/**
* This program loads students, courses, assignments and scores data from simple-data.txt file
  and allows the user to perform queries on the loaded data from a command line interface.
*
* Completion time: (6 hours)
*
* @author (Mohammad Hamdan), (Acuna)
* @version (1.0)
*
*/

////////////////////////////////////////////////////////////////////////////////
// INCLUDES
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

////////////////////////////////////////////////////////////////////////////////
// MACROS: CONSTANTS
#define MAX_STUDENT_NAME_LENGTH 20
#define MAX_COURSE_NAME_LENGTH 10
#define MAX_TEACHER_NAME_LENGTH 20
#define MAX_COMMENT_LENGTH 20
#define MAX_ASSIGN_NAME_LENGTH 20
#define MAX_FILENAME_LENGTH 30

////////////////////////////////////////////////////////////////////////////////
//DATA STRUCTURES

typedef enum AcademicLevel{Freshman=1, Sophomore, Junior, Senior} AcademicLevel;
char *AcademicLevelName[]={"Freshman", "Sophomore", "Junior", "Senior"};

typedef struct ScoreStruct {

char *ScoreName;
double score;
int StudentID;
int AssignmentID;


} ScoreStruct;

typedef struct Assign {

char *AssignName;
int NumberOfAssignments;
int AssignmentID;


} Assign;

typedef struct Student {

char *StudentName;
int StudentID;
AcademicLevel level;
} Student;

typedef struct Course {

char *name;
char *TeacherName;
int CourseID;
int NumberOfAssignments;
Assign *assignments;
ScoreStruct **scores;

} Course;

////////////////////////////////////////////////////////////////////////////////
//GLOBAL VARIABLES
//place to store student information
Student* students = NULL;
//place to store course information
Course* courses = NULL;
int numCourses, numStudents;

////////////////////////////////////////////////////////////////////////////////
//FORWARD DECLARATIONS

// the following should be used to read student/course data in from the file
void readFile(char* filename);
void readString(FILE* file, char** dst, int max_length);
Student* readStudents(FILE* file);
Course* readCourses(FILE* file);
Assign* readAssigns(FILE* file, int numAssigns);
ScoreStruct** readScores(FILE* file, int numAssigns);

// the following should be used to free all heap data allocated during the programs runtime
// and handle dangling pointers
void terminate();
void studentsDestructor(){

free(students);

}
void coursesDestructor(){

free(courses);
}
void assignsDestructor(Assign** assigns, int numAssign){

free(courses->assignments);

}
void scoresDestructor(ScoreStruct*** scores, int numAssigns){
for (int i=0; i<numAssigns; i++){

free(courses->scores[i]);
}

free(courses->scores);
}

// the following should be used to cleanly print the data used in the program
void printStudents();
void printAssigns(Assign* assigns, int numAssigns);
void printGrades(ScoreStruct** scores, int numAssigns);
void printCourse(Course course);

// the following are mostly complete functions that define and
// control the CLI menu associated with the program
void mainMenu();
void mainMenuBranch(int option);
void subMenu(Course course);
void subMenuBranch(int option, Course course);

// these are the 'special' functions that you are being asked to implement
void studentMenu(Course course);
void getStudentScores(Course course, int studentNo);
void assignmentMenu(Course course);
void getAssignmentScore(Course course, int assignmentNo);

// this is an optional function that parses and executes instructions defined in an input file
void performInstructions(char* iFile);

// this is a utility function to be called when input filenames are invalid
void printUsage();

/////////////////////////////////////////////////////////////////////////////////
//IMPLEMENTATION

/**
* Loads data from student/course data file
* @param filename is the name of the file
*/
void readFile(char* filename){
  FILE* file = fopen(filename, "r");
  //FOR YOU TO IMPLEMENT
  if (file == NULL){

  printf("no such file");
  return;
  }
/*
Reading students, courses, assignments and scores
information from the text file.
*/
readStudents(file);
readCourses(file);

/*
After reading the data the user will see the main
menu which contain the list of imported courses
*/
mainMenu();

  fclose(file);
}

/*
The function readString below is used to read strings from the input text file.
*/

void readString(FILE* file, char** dst, int max_length){

char buffer[max_length+1];
static char format[16];
sprintf(format, "%%%ds", max_length);

fscanf(file, format, &buffer);

char *str= malloc(strlen(buffer)+1);

strcpy(str, buffer);

*dst= str;

}
Student* readStudents(FILE* file){

fscanf(file, "%d" , &numStudents);
students = malloc(numStudents * sizeof (Student));

for (int i=0; i<numStudents; i++){

fscanf(file, "%d", &students[i].StudentID);
readString(file, &students[i].StudentName, MAX_STUDENT_NAME_LENGTH);
fscanf(file, "%d", (int*)&students[i].level);

}

}
Course* readCourses(FILE* file){

fscanf(file, "%d" , &numCourses);
courses = malloc(numCourses * sizeof (Course));

for (int i=0; i<numCourses; i++){

fscanf(file, "%d", &courses[i].CourseID);
readString(file, &courses[i].name, MAX_COURSE_NAME_LENGTH);
readString(file, &courses[i].TeacherName, MAX_TEACHER_NAME_LENGTH);
int NumberOfAssignments;
fscanf(file, "%d", &NumberOfAssignments);
courses[i].NumberOfAssignments=NumberOfAssignments;
courses[i].assignments=readAssigns(file, NumberOfAssignments);
courses[i].scores=readScores(file, NumberOfAssignments);

}


}
Assign* readAssigns(FILE* file, int numAssigns){

Assign *assignments = malloc(numAssigns* sizeof(Assign));

for (int i=0; i<numAssigns; i++){

fscanf(file, "%d", &assignments[i].AssignmentID);
readString(file, &assignments[i].AssignName, MAX_ASSIGN_NAME_LENGTH);

}
return assignments;
}

ScoreStruct** readScores(FILE* file, int numAssigns){

int NumberOfScores = numAssigns*numStudents;

ScoreStruct **scores = malloc(numAssigns* sizeof(ScoreStruct*));

for (int i=0; i<numAssigns; i++){

scores[i] = malloc(numStudents* sizeof(ScoreStruct));

}

/*
The two for loops below loads the data into the scores 2D array
defined for each course based on the studentID and assignmentID values.
*/

for (int j=0; j<numAssigns; j++){
for (int k=0; k<numStudents; k++ ){

fscanf(file, "%d", &scores[j][k].AssignmentID);
fscanf(file, "%d", &scores[j][k].StudentID);
fscanf(file, "%lf", &scores[scores[j][k].AssignmentID -1 ][scores[j][k].StudentID-1].score);
readString(file, &scores[scores[j][k].AssignmentID -1][scores[j][k].StudentID-1].ScoreName, MAX_COMMENT_LENGTH);

}

}
return scores;
}

/*
The function studentMenu below is defined to show
a list of students names and their academic level.
*/
void studentMenu(Course course){

printf("Please choose from the following students:\n");
for (int i=0; i<numStudents; i++){

printf("%d %s (%s)\n", students[i].StudentID, students[i].StudentName, AcademicLevelName[students[i].level -1] );
}

printf("0 RETURN TO PREVIOUS MENU\n");

int opt;
printf("please enter your choice--->");
scanf("%d", &opt);

if (opt !=0){

getStudentScores(course, opt);


}

else {subMenuBranch(opt, course);}


}
/*
The function getStudentScores shows the scores of a specifc student
in all assignments in a course and their final grade.
*/
void getStudentScores(Course course, int studentNo){

printf("%s's assignments specifc grades were:\n", students[studentNo-1].StudentName);
printf("Assign Name        Score          Comment\n");
printf("--------------------------------------------\n");
double finalGrade=0;
for (int i=0; i < course.NumberOfAssignments; i++){

printf("%s        %lf           %s\n", course.assignments[i].AssignName, course.scores[i][studentNo-1].score, course.scores[i][studentNo-1].ScoreName);
double temp =  course.scores[i][studentNo-1].score;
finalGrade= finalGrade + temp;
}


finalGrade= finalGrade/(course.NumberOfAssignments);
printf("%s's final grade is %lf ", students[studentNo-1].StudentName, finalGrade);

}
/*
The function assignmentMenu below is defined to show a list of
assignments for the selected course.
*/
void assignmentMenu(Course course){

printf("Please choose from the following assignments:\n");

for (int i=0; i < course.NumberOfAssignments; i++){

printf("%d  %s\n", course.assignments[i].AssignmentID, course.assignments[i].AssignName);

}

printf("0 RETURN TO PREVIOUS MENU");
int opt;
printf("please enter your choice--->");
scanf("%d", &opt);

if (opt!=0){getAssignmentScore(course, opt);}

else {subMenuBranch(opt, course);}
}
/*
The function getAssignmentScore calculates the average grades
for a selected assignment in a course.
*/
void getAssignmentScore(Course course, int assignmentNo){

double score=0;
int count=0;
for (int i=0; i<numStudents; i++ ){
count=count+1;
double temp= course.scores[assignmentNo-1][i].score;
score = score+temp;
}

double averageScore = score/count;

printf("The average grade on %s was %lf\n", course.assignments[assignmentNo-1].AssignName, averageScore);


}
/*
The function printCourse print all details for a selected course.
*/
void printCourse(Course course){

for(int i=0; i<numCourses; i++){
printf("Course ID: %d\n", courses[i].CourseID);

printf("Course Name: %s\n", courses[i].name );
printf("Teacher: %s\n", courses[i].TeacherName);
printf("Assigns:\n");
printAssigns(courses[i].assignments, course.NumberOfAssignments);
printf("Grade Data:\n");
printGrades(courses[i].scores, courses[i].NumberOfAssignments);

}


}


void printAssigns(Assign* assigns, int numAssigns){

for (int i=0; i< numAssigns; i++){

printf("%d %s\n", assigns[i].AssignmentID, assigns[i].AssignName);

}

}

void printGrades(ScoreStruct** scores, int numAssigns){

for (int i=0; i<numAssigns; i++ ){
for (int j=0; j<numStudents; j++){

printf("%d %d %lf %s\n", scores[i][j].StudentID, scores[i][j].AssignmentID, scores[scores[i][j].AssignmentID -1][scores[i][j].StudentID -1].score,
scores[scores[i][j].AssignmentID -1][scores[i][j].StudentID -1].ScoreName);

}
}

}

/**
* Implements main menu functionality, which allows user to select a course to interact with
*/
void mainMenu(){
  int input_buffer;
  printf("Course Searcher");
  do {
	printf("\n-----------------------------------\n");
    printf("Course Options");
	printf("\n-----------------------------------\n");
	int i;
	for(i = 0; i < numCourses; i++){
      //FOR YOU TO IMPLEMENT
      printf("   %d %s\n", courses[i].CourseID, courses[i].name);
    }
	printf("   0 REPEAT OPTIONS\n");
    printf("  -1 TERMINATE PROGRAM\n");
	printf("Please enter your choice ---> ");
	scanf(" %d", &input_buffer);
    mainMenuBranch(input_buffer);
  } while (1);
}

/**
* Handles menu options of main menu
* @param option is the chosen operation's option #
*/
void mainMenuBranch(int option){
  if (option < -1 || option > numCourses){
    printf("Invalid input. Please try again...\n");;
    while(option < -1 || option > numCourses){
  	  printf("Please enter a valid option ---> ");
      scanf(" %d", &option);
    }
  }
  if(option == -1){
	printf("Terminating program...\n");
    terminate();
  } else if (option == 0) {
	printf("Repeating options...\n");
  } else {
    Course course = courses[option - 1];
	//FOR YOU TO IMPLEMENT
    printf("Course with name %s selected.\n", course.name);
	subMenu(course);
  }
}

/**
* Implements sub menu functionality, which allows users to select how they want to interact with course
* @course is the course to be queried
*/

void subMenu(Course course){
  int input_buffer;
  do {
    printf("\n-----------------------------------\n");
    printf("Menu Options");
	printf("\n-----------------------------------\n");
    printf("   1 Get a student's final grades in the course\n");
	printf("   2 Get the average grade of an assignment in the course\n");
    printf("   3 Print all course data\n");
	printf("   0 REPEAT OPTIONS\n");
	printf("  -1 RETURN TO PREVIOUS MENU\n");
    printf("  -2 TERMINATE PROGRAM\n");
	printf("Please enter your choice ---> ");
	scanf(" %d", &input_buffer);
    subMenuBranch(input_buffer, course);
  } while (input_buffer != -1);
}

/**
* Handles menu options of submenu
* @param option is the chosen operation's option #
* @param course is the course struct to be queried
*/
void subMenuBranch(int option, Course course){
  if (option < -2 || option > 3){
    printf("Invalid input. Please try again...\n");;
    while(option < -2 || option > 3){
  	  printf("Please enter a valid option ---> ");
      scanf(" %d", &option);
    }
  }
  if(option == -2){
    printf("Terminating program...\n");
	terminate();
  } else if (option == -1){
	printf("Returning to previous menu...\n");
  } else if (option == 0){
    printf("Repeating options...\n");
  } else if (option == 1){
    //FOR YOU TO IMPLEMENT

    studentMenu(course);
  } else if (option == 2){

   assignmentMenu(course);
    //FOR YOU TO IMPLEMENT
  } else if (option == 3){
    //FOR YOU TO IMPLEMENT
    printCourse(course);
  }
}


/**
* Prints basic usage instructions for the program to the command line
*/
void print_usage(){
  printf("USAGE:\n./LastNameCourseReader -d <data_file_name(char*)> -c <instruction_file_name(char*)>\n");
  printf("-d refers to the required input data file containing student & course information; this must be a valid .txt file\n");
  printf("-i refers to the optionally supported 'instruction file' that provides directions for how the program should execute without CLI input; \n\t must be a valid .txt.file\n");
}

void terminate(){
  //FREE EVERYTHING HERE
  studentsDestructor();
  coursesDestructor();
  assignsDestructor(courses->assignments, courses->NumberOfAssignments );
  scoresDestructor(courses->scores, courses->NumberOfAssignments);
  exit(1);
}

int main(int argc, char* argv[]){
  char* datafile;
  char* instructionfile;
  int opt;
  while((opt = getopt(argc, argv, ":d:i:")) != -1){
    switch(opt){
      case 'd':
        datafile = optarg;
        break;
      case 'i':
        instructionfile = optarg;
        break;
      case ':':
		printf("option needs a value\n");
		break;
      case '?':
        printf("unknown option: %c\n", optopt);
        break;
    }
  }
  for (; optind < argc; optind++){
    printf("Given extra arguments: %s\n", argv[optind]);
  }

  int dflen;
  if(datafile != NULL){
    dflen = strlen(datafile);
    if(dflen >= 5
		&& (strcmp(&datafile[dflen-4], ".txt") == 0)
        && (access(datafile, F_OK) != -1)){
      printf("Importing data from %s\n\n", datafile);
	  readFile(datafile);
    } else {
	  printf("Data file has an invalid name or does not exist.\n");
      print_usage();
	  exit(1);
    }
  } else {
    printf("No data file name provided. This is a required field.\n");
    print_usage();
	exit(1);
  }

  int iflen;
  int ifval;
  if(instructionfile != NULL){
    iflen = strlen(instructionfile);
	if(iflen >= 5
		&& (strcmp(&instructionfile[iflen-4], ".txt") == 0)
		&& (access(instructionfile, F_OK) != -1)){
	  printf("Performing instructions defined in %s:\n", instructionfile);
	  //uncomment below if doing this optional part of the assignment
	  //performInstructions(instructionfile);
	} else {
      printf("Instruction file has an invalid name or does not exist.\n");
	  print_usage();
	  exit(1);
    }
  } else {
	printf("No instruction file provided. Using CLI:\n");
    mainMenu();
  }
  return 0;
}

#endif
