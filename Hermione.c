    char** first_multiple_input = split_string(rtrim(readline()));

    int D = parse_int(*(first_multiple_input + 0));

    int S = parse_int(*(first_multiple_input + 1));
    
    if ((S>9*D) || (S == 0 && D > 1)) {
        printf("-1\n");
        return 0;
    }
    
    char* digits = malloc(sizeof(char)*(D + 1));
    
    S = S - 1;
    for (int i=D-1;i>=0;i--) {
        if (S>9) {
            digits[i] = '9';
            S = S-9;
        } else {
            digits[i] = S + '0';
            S = 0;
        }
    }
    
    digits[0] = digits[0]+1;
    
    digits[D] = '\0';

    printf("%s\n", digits);
    
    free(digits);
    
    return 0;
