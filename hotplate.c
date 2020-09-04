/* A program to solve the hotplate problem 

  Author: Bukola Grace Omotoso
  MNumber: M01424979
  ID: bgo2e
  Last Modified: 09/07/2018
  
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

float** buildHotplate(int rows, int columns) {
float** hotplate;
hotplate = (float**) malloc(rows*sizeof(float*));
for (int i = 0; i < rows; i++)
   hotplate[i] = (float*) malloc(columns*sizeof(float));
   return hotplate;
}

 void initializeHotPlate(int num_rows, int num_cols, float** hotplate, float** hotplateClone, int top_temp, int left_temp, int right_temp, int bottom_temp)	{
 	int num_outer_grid = (2 * num_rows) + (2 * (num_cols - 2));
	float outer_grid_sum = (top_temp * (num_cols - 2)) + (left_temp * (num_rows - 1)) + (bottom_temp * num_cols) + (right_temp * (num_rows - 1));
    float initial_inner_val = outer_grid_sum / num_outer_grid;

    for (int row = 0; row < num_rows; row++) {
            for (int column = 0; column < num_cols; column++) {

                //top values override the top row except the edges
                 if ((row == 0) & (column != 0 & column != num_cols - 1)) {
                	hotplate[row][column] = top_temp;
                    hotplateClone[row][column] = top_temp;
                } 
                else if (column == 0 && (row != (num_rows-1))) {
                    hotplate[row][column] = left_temp;
                    hotplateClone[row][column] = left_temp;
                }
                else if (column == (num_cols - 1) && (row != (num_rows-1))) {
                    hotplate[row][column] = right_temp;
                    hotplateClone[row][column] = right_temp;
                }
                else if(row == (num_rows -1 )){
                    hotplate[row][column] = bottom_temp;
                    hotplateClone[row][column] = bottom_temp;
                }
                if ((row != 0) && (row != num_rows - 1) && (column != 0) && (column != num_cols - 1))
                    hotplate[row][column] = initial_inner_val;
            }
        }

 }

 void swapHotplate(float *a, float *b) {

    float tmp = *a;
    *a = *b;
    *b = tmp;
} 


void generateHeat(int num_rows, int num_cols, float** hotplate, float** hotplateClone, float epsilon) {
        float max_difference = 0;
        int counter = 0;
        float previous_val;
        float current_val;
        float diff;
         printf("%10s%10s\n", "Iteration", "Epsilon");

        //kills process after running for 60 mins
         
        alarm(3600);
        while (true) {
            max_difference = 0;
            for (int row = 1; row < (num_rows - 1); row++) {

                for (int column = 1; column < (num_cols - 1); column++) {
                    previous_val = hotplate[row][column];
                    current_val = ((hotplate[row - 1][column] + hotplate[row][column - 1] + hotplate[row + 1][column] + hotplate[row][column + 1]) / 4);
                    diff = fabsf(previous_val - current_val);
                    if (diff > max_difference){
                        max_difference = diff;
                    }
                    hotplateClone[row][column] = current_val;

                }
            }
            swapHotplate((float*)&hotplate, (float*)&hotplateClone);

            if (counter > 0 && (counter & (counter - 1)) == 0)
                printf("%6d%15.6f\n", counter, max_difference);
            if (max_difference < epsilon) {
                printf("%6d%15.6f\n", counter, max_difference);
                break;
            }
            counter++;
    }
}


int main(int argc, char const *argv[])
{		int num_rows = atoi(argv[1]);
		int num_cols = atoi(argv[2]);
		int top_temp = atoi(argv[3]);
		int left_temp = atoi(argv[4]);
		int right_temp = atoi(argv[5]);
		int bottom_temp = atoi(argv[6]);
		float epsilon = atof(argv[7]);

        float** hotplate =  buildHotplate(num_rows, num_cols);
        float** hotplateClone = buildHotplate(num_rows, num_cols);

        initializeHotPlate(num_rows, num_cols, hotplate, hotplateClone, top_temp, left_temp, right_temp, bottom_temp);    
        generateHeat(num_rows, num_cols, hotplate, hotplateClone, epsilon);

	return 0;
}

