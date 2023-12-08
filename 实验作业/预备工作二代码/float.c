#include <stdio.h>

int main() {
    double float_operand1 = 4.0,float_operand2 = 2.0,add_result,sub_result,mul_result,div_result;
    add_result = float_operand1 + float_operand2;
    sub_result = float_operand1 - float_operand2;
    mul_result = float_operand1 * float_operand2;
    div_result = float_operand1 / float_operand2;
    printf("%f %f %f %f\n", add_result, sub_result, mul_result, div_result);
    return 0;
}