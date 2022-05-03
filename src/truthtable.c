#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct circuit {
    char gate[15];
    int n;
    int s;
    int *inputs;
    int *outputs;
    int *selectors;
};

void gate(int *vars, int in1, int in2, int out, int command);
void PASS(int *vars, int in, int out);
void multiplexer(int *vars, int n, int *in, int *index, int out);
void decoder(int *vars, int n, int *in, int *out);
int getVal(char **arr, char *var, int size);
void reset(int *arr, int size);
int indexOf(char **arr, char *var, int size);


int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Error. There is no file provided. \n");
        return EXIT_FAILURE;
    }

    FILE *test = fopen(argv[1], "r");
    if (test == NULL) {
        return EXIT_FAILURE;
    }

    //makes the directives with the circuit
    int count = 0;
    struct circuit* directives = NULL;
    int total = 0;
    int size = 2;
    int in_var = 0;
    int op_var = 0;
    int *variables; 
    char dir[20];
    char **avars;
    

    //scans the input info and stores it in the array
    fscanf(test, "%s %d", dir, &in_var);
    size += in_var;
    avars = malloc(sizeof(char *) * size);
   
    avars[0] = "0\0";
   
    avars[1] = "1\0";

    int i =0;
    while (i < in_var) {
        avars[i + 2] = malloc(20 * sizeof(char));
        fscanf(test, "%16s", avars[i + 2]);
        i++;
    }

    //scans the output info and stores it in the array
    fscanf(test, " %s %d", dir, &op_var);
    size += op_var;
    avars = realloc(avars, size * sizeof(char *));
    for (i = 0; i < op_var; i++) {
        avars[2 + in_var + i] = malloc(20 * sizeof(char));
        fscanf(test, "%16s", avars[2 + i + in_var]);
    }
    struct circuit current; 
    int tempcount = 0; 

    //lists out all the directives
    while (!feof(test)) {
	    tempcount++;
        int ni = 2, no = 1;
        
        int sc = fscanf(test, " %s", dir); 
        if (sc != 1) break;
        count++;
        current.s = 0;
        current.n = 0;
        strcpy(current.gate, dir);

        if (strcmp(dir, "PASS") == 0) {
            ni = 1;
        }
        if (strcmp(dir, "NOT") == 0) ni = 1;
        if (strcmp(dir, "MULTIPLEXER") == 0) {
            fscanf(test, "%d", &ni);
            current.s = ni;
            ni = pow(2, ni);
        }
        if (strcmp(dir, "DECODER") == 0) { 
            fscanf(test, "%d", &ni);
            current.n = ni;
            no = pow(2, ni);
        }
        


        current.inputs = malloc(ni * sizeof(int));
        current.outputs = malloc(no * sizeof(int));
        current.selectors = malloc(current.s * sizeof(int));
        
        char vord[17];

        for (i = 0; i < ni; i++) {
            fscanf(test, "%16s", vord);
            current.inputs[i] = indexOf(avars, vord, size);
        }
         for (i = 0; i < current.s; i++) {
            fscanf(test, "%16s", vord);
            current.selectors[i] = indexOf(avars, vord,size);
        }
 
        for (i = 0; i < no; i++) {
            fscanf(test, "%16s", vord);
            int idx = getVal(avars, vord, size);
            if (idx == -1) {
                total++;
                size++;
                avars = realloc(avars, size * sizeof(char *));
                avars[size - 1] = malloc(20 * sizeof(char));
                strcpy(avars[size - 1], vord);
                current.outputs[i] = size - 1;
            }
            else current.outputs[i] = idx;
        }
        
        //adds the current directive to list of directives
        if (!directives) directives = malloc(sizeof(struct circuit));
        else directives = realloc(directives, count * sizeof(struct circuit));
        
        
        directives[count - 1] = current;
  
    }

    // initializes the variables array 
    variables = malloc(sizeof(int) * size);
    reset(variables, size);
   

    //run this infinitely until we break within loop; then print truthtable
    while(10 < 100){
        for(int i = 0; i < in_var; i++ ){
             printf("%d ", variables[i + 2]);
        }
        printf("|");

         for (i = 0; i < count; i++) {
            current = directives[i];
            if (strcmp(current.gate, "NOT") == 0) gate(variables, current.inputs[0], 0, current.outputs[0], 3);
            else if (strcmp(current.gate, "AND") == 0) gate(variables, current.inputs[0], current.inputs[1], current.outputs[0], 1);
            else if (strcmp(current.gate, "OR") == 0) gate(variables, current.inputs[0], current.inputs[1], current.outputs[0], 2);
            else if (strcmp(current.gate, "XOR") == 0) gate(variables, current.inputs[0], current.inputs[1], current.outputs[0], 4);
            else if (strcmp(current.gate, "NAND") == 0) gate(variables, current.inputs[0], current.inputs[1], current.outputs[0], 6);
            else if (strcmp(current.gate, "NOR") == 0) gate(variables, current.inputs[0], current.inputs[1], current.outputs[0], 5);
            else if(strcmp(current.gate, "DECODER") == 0){
                decoder(variables, current.n, current.inputs, current.outputs);
            }
            else if(strcmp(current.gate, "MULTIPLEXER") == 0){
                multiplexer(variables, current.s, current.inputs, current.selectors, current.outputs[0]);
            }
        }

        for (i = 0; i < op_var; i++) 
            printf(" %d", variables[in_var + i + 2]);
       
        printf("\n");

        int br = 0;
        for (i = in_var + 1; i > 1; i--) {
            variables[i] = !variables[i];
            if (variables[i] == 1) {
                br = 1;
                break;
            }
        }

        if (!br) break;
    }
   
    
        //printf("%d\n", size);
    for (i = size-1; i >= 2; i--) {
    	free(avars[i]);
    }
   
    if(in_var > 25){
	    for(i = 0; i < tempcount; i++){
		    free(directives[i].inputs);
		}
        for(i = 0; i < tempcount; i++){
            free(directives[i].selectors);
	    }
        for(i = 0; i < tempcount; i++){
		    free(directives[i].outputs);
	    }
    }else {
        for(i = 0; i < tempcount-1; i++){
            free(directives[i].inputs);
            free(directives[i].outputs);
            free(directives[i].selectors);

            //free(directives[i]);
        }
    }

    free(variables);
    free(directives);
    free(avars);

    
    fclose(test);
}



void gate(int *vars, int in1, int in2, int out, int command) {
    if (command==1) vars[out] = vars[in1] && vars[in2];
    else if (command ==2) vars[out] = vars[in1] || vars[in2];
    else if (command == 3) vars[out] = !vars[in1];
    else if (command ==4) vars[out] = vars[in1] ^ vars[in2];
    else if (command == 5) vars[out] = !(vars[in1] || vars[in2]);
    else if (command == 6) vars[out] = !(vars[in1] && vars[in2]);
}


void PASS(int *vars, int in, int out) {
    vars[out] = vars[in];
}

void decoder(int *vars, int n, int *in, int *out) {
    int s = 0;
    int i;
    for (i = 0; i < pow(2, n); i++) {
        vars[out[i]] = 0;
    }
    for (i = 0; i < n; i++) {
        s += vars[in[i]] * pow(2, n-1-i);
    }
    vars[out[s]] = 1;
}

void multiplexer(int *vars, int n, int *in, int *index, int out) {
    int t = 0;
    int i;
    for (i = 0; i < n; i++) {
        t += vars[index[i]] * pow(2, n-1-i);
    }
    vars[out] = vars[in[t]];
}


int getVal(char **arr, char *var, int size) {
    int j = 0;
    while (j < size) {
        if (strcmp(arr[j], var) == 0) return j;
        j++;
    }
    return -1;
}

void reset(int *arr, int size) {
    int i = 0;
    while (i < size) {
        arr[i] = 0;
        i++;
    }
    arr[1] = 1;
}


int indexOf(char **arr, char *var, int size) {
    int i =0;
    while (i <size) {
        if (strcmp(arr[i], var) == 0) {
            return i;
        }
        i++;
    }
    return -1;
}
