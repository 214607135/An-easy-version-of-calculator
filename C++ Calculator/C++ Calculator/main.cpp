//
//  main.cpp
//  C++ Calculator
//
//  Created by blank. on 1/8/19.
//  Copyright © 2019 blank. All rights reserved.
//

#include <iostream>
#include <stack>
#include <queue>

using namespace std;

void show_stack(stack<string> wanted){
    auto len = wanted.size();
    for(int i=0; i<len; i++){
        cout << wanted.top() << "\t";
        wanted.pop();
    }
    cout << endl;
}

void show_queue(queue<string> wanted){
    auto len = wanted.size();
    for(int i=0; i<len; i++){
        cout << wanted.front() << "\t";
        wanted.pop();
    }
    cout << endl;
}

queue<string> add_formula_into_queue(string formula){
    //  Done: The formula is stored into a queue, but the input is restricted of starting with '(' and ending with ')'
    queue<string> target;
    bool pre_num_flag = false;
    int num = 0;
    for(int i=0; i<formula.length(); i++){
        
        // Todo: How to deal with decimal mark???
        if(!isdigit(formula[i])){
            if(pre_num_flag){
                string a = to_string(num);
                num = 0;
                target.push(a);
            }
            string s(1,formula[i]);
            target.push(s);
            pre_num_flag = false;
        }else{
            num = 10*num + formula[i] - '0';
            pre_num_flag = true;
        }
    }
    return target;
}

bool isNum(string str){
    for(char x:str){
        if(!isdigit(x)){
            return false;
            break;
        }
    }
    return true;
}

int main(){
    queue<string> aim;
    string formula;
    cin >> formula;
    aim = add_formula_into_queue(formula);
    //  Done: Change the order of queue to Reverse Polish notation
    queue<string> reverse_notation;
    stack<string> temp;
    string queue_item;
    string stack_item;
    
    while(!aim.empty()){
        queue_item = aim.front();
        aim.pop();
        if(isNum(queue_item)){
            reverse_notation.push(queue_item);
        }
        else if(queue_item == "("){
            temp.push(queue_item);
        }
        else if(queue_item == ")"){
            stack_item = temp.top();
            while(stack_item != "("){
                reverse_notation.push(stack_item);
                temp.pop();
                stack_item = temp.top();
            }
            temp.pop();
        }
        else{
            while(queue_item == "+" or queue_item == "-"){
                stack_item = temp.top();
                if(stack_item != "("){
                    temp.pop();
                    reverse_notation.push(stack_item);
                }else{
                    temp.push(queue_item);
                    break;
                }
            }
            while(queue_item == "*" or queue_item == "/") {
                stack_item = temp.top();
                if(stack_item != "(" and stack_item != "+" and stack_item != "-"){
                    temp.pop();
                    reverse_notation.push(stack_item);
                }else{
                    temp.push(queue_item);
                    break;
                }
            }
        }
    }
    
    while(!temp.empty()){
        stack_item = temp.top();
        temp.pop();
        if(stack_item != "(" and stack_item != ")"){
            reverse_notation.push(stack_item);
        }
    }
    
//        show_queue(reverse_notation);
    
    //  Done: Compute the value of this reverse polish notation
    stack<string> op;
    string element;
    element = reverse_notation.front();
    reverse_notation.pop();
    op.push(element);
    double fir_num = 0;
    double sec_num = 0;
    double result = 0;
    string str_result;
    
    // When there is only one element in op stack and nothing in reverse_notation, that is the answer.
    while (!(op.size() == 1 and reverse_notation.empty())){
        element = reverse_notation.front();
        reverse_notation.pop();
        
        if(isNum(element)){
            op.push(element);
        }else{
            fir_num = stod(op.top());
            op.pop();
            sec_num = stod(op.top());
            op.pop();
            if(element == "+"){
                result = sec_num + fir_num;
            }
            else if(element == "-"){
                result = sec_num - fir_num;
            }
            else if(element == "*"){
                result = sec_num * fir_num;
            }
            else{
                result = sec_num / fir_num;
            }
            str_result = to_string(result);
            op.push(str_result);
        }
    }
    result = stod(op.top());
    cout << result << endl;
}
