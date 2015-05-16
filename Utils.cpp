#include "Utils.h"

int Utils::getSmaller(int number1, int number2){
    if(number1 <= number2)
        return number1;
    else
        return number2;
}

int Utils::isInRange(int start, int end, int target1, int target2){
    return target1 >= start && target1 <= end && target2 >= start && target2 <= end;
}
