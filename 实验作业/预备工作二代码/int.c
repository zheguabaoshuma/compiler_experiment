#include <stdio.h>
int main() {
    int int_operand1 = 4,int_operand2 = 2,add_result,sub_result,mul_result,div_result;
    add_result = int_operand1 + int_operand2;
    sub_result = int_operand1 - int_operand2;
    mul_result = int_operand1 * int_operand2;
    div_result = int_operand1 / int_operand2;
    printf("%d %d %d %d\n", add_result, sub_result, mul_result, div_result);
    return 0;
}