#include <stdio.h>

#define NUM_STUDENTS 25
#define NUM_QUESTIONS 10

int correct_answers[NUM_QUESTIONS] = {4,4,3,2,1,3,4,1,1,2}; // Set of right answers 

float calculatePercentile(int score, int student_scores[], int num_students) 
{   // Function to calculate percentile
    int num_students_below = 0;
    
    for (int i = 0; i < num_students; i++) 
    {
        if (student_scores[i] <= score) 
        {
            num_students_below++;
        }
    }
    
    return ((float)num_students_below / num_students) * 100.0;   // Formula to calculate percentile
}

int check_if_correct(int student_scores[])
{   // Function to check if still any two candidates have equal scores. Hence, to run the loop again to change their priority
    for(int i = 0; i < NUM_STUDENTS; i++)
    {
        for(int j = 0; j < NUM_STUDENTS; j++)
        {
            if(i == j)
            {
                continue;
            }
            else if(student_scores[i]==student_scores[j])
            {
                return 1;
            }
        }
    }
    return 0;
}

int main() 
{
    int student_scores[NUM_STUDENTS] = { 0 };
    int student_degree_score[NUM_STUDENTS] = {58, 72, 96, 62, 75, 89, 54, 88, 67, 55, 82, 61, 91, 76, 70, 51, 98, 64, 93, 57, 83, 59, 97, 69, 84};
    FILE *file = fopen("student_answers.txt", "r");  // Fetching data from a file
    if (file == NULL) 
    {
        printf("Error opening file.\n");
        return 1;
    }
    // Read student answers from the file
    for (int student_id = 0; student_id < NUM_STUDENTS; student_id++) 
    {
        for (int question = 0; question < NUM_QUESTIONS; question++) 
        {
            int answer;
            fscanf(file, "%d", &answer);
            if (answer == correct_answers[question]) 
            {
                student_scores[student_id] += 2;  // Correct answer
            } 
            else if (answer == 0) 
            {
                student_scores[student_id] += 0;  // Question not attempted
            } 
            else 
            {
                student_scores[student_id] -= 1;  // Wrong answer
            }
        }
    }

    fclose(file);
    
    int flag = 1;
    // To check if any candidates have equal scores ... If so, to compare their degree scores to generate percentile on it's priority
    while(flag == 1)
    {
        for(int i = 0; i < NUM_STUDENTS; i++)
        {
            for(int j = 0; j < NUM_STUDENTS; j++)
            {
                if(student_scores[i]==student_scores[j])
                {
                    if(i == j)
                    {
                        continue;
                    }
                    else
                    {
                        if(student_degree_score[i] > student_degree_score[j])
                        {
                            student_scores[i] = student_scores[i] + 2;
                        }
                        else
                        {
                            student_scores[j] = student_scores[j] + 2;
                        }
                    }
                }
            }
        }
        flag = check_if_correct(student_scores); 
    }

    printf("Student ID\tPercentile\n");

    // Calculate and display percentiles for each student
    for (int student_id = 0; student_id < NUM_STUDENTS; student_id++) 
    {
        float percentile = calculatePercentile(student_scores[student_id], student_scores, NUM_STUDENTS);
        printf("%d\t\t%.2f%%\n", student_id + 1, percentile);
    }

    return 0;
}
