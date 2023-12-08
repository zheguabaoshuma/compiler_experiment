#include <stdio.h>

int main() {
    int operand1 = 12,operand2 = 34;
    int or_result, and_result, not_result,left_shift,right_shift,eor_result;
    or_result = operand1 | operand2;
    and_result = operand1 & operand2;
    not_result = ~operand1;
    left_shift = operand1 << 1;
    right_shift = operand1 >> 1;
    eor_result = operand1 ^ operand2;
    printf("%d %d %d %d %d %d\n", or_result, and_result, not_result,left_shift,right_shift,eor_result);
    return 0;

}