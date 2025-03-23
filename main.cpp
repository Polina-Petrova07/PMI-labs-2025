#include "stdio.h"
#include "math.h"
#include "print.cpp"
#include "function.cpp"

struct Values
{
    double val_x_in_t;
    int val_count;
};


int main()
{
    struct Values  test;
    struct Values *p_test = &test; 
    
    const int count_string_teilor_test[10] = {2,3,4,5,6,7,8,9,10,1000000};
    


    int choise_func;
    double rez_val;

    print_menu_func();
    scanf("%i", &choise_func);
    while (choise_func != 5)
    {
      

        switch (choise_func)
        {
        case (1): //sin(x) 
            print_required_val();
            scanf("%lg",&test.val_x_in_t);

            p_test -> val_count = count_string_teilor_test[0];
            print_test_teilor(test.val_count, sin(test.val_x_in_t));
            rez_val = teilor_sin(test.val_x_in_t,test.val_count); // значение при 2 строчках
            print_rez_val_sin(sin(test.val_x_in_t),rez_val);

            p_test -> val_count = count_string_teilor_test[1];
            print_test_teilor(test.val_count, sin(test.val_x_in_t));
            rez_val = teilor_sin(test.val_x_in_t,test.val_count);   //  значение при 3 строчках 
            print_rez_val_sin(sin(test.val_x_in_t),rez_val);

            p_test -> val_count = count_string_teilor_test[2];
            print_test_teilor(test.val_count, sin(test.val_x_in_t));
            rez_val = teilor_sin(test.val_x_in_t,test.val_count);    // значение при 4 строчках
            print_rez_val_sin(sin(test.val_x_in_t),rez_val);

            p_test -> val_count = count_string_teilor_test[3];
            print_test_teilor(test.val_count, sin(test.val_x_in_t));
            rez_val = teilor_sin(test.val_x_in_t,test.val_count);    // значение при 5 строчках
            print_rez_val_sin(sin(test.val_x_in_t),rez_val);

            p_test -> val_count = count_string_teilor_test[4];
            print_test_teilor(test.val_count, sin(test.val_x_in_t));
            rez_val = teilor_sin(test.val_x_in_t,test.val_count);    // значение при 6 строчках
            print_rez_val_sin(sin(test.val_x_in_t),rez_val);

            break;
            
        case(2): // cos(x)
            print_required_val();
            scanf("%lg", &test.val_x_in_t);

            p_test -> val_count = count_string_teilor_test[0];
            print_test_teilor(test.val_count, cos(test.val_x_in_t));
            rez_val = teilor_cos(test.val_x_in_t,test.val_count);
            print_rez_val_cos(cos(test.val_x_in_t),rez_val); // значение при 2 строчках

            p_test -> val_count = count_string_teilor_test[1];
            print_test_teilor(test.val_count, cos(test.val_x_in_t));
            rez_val = teilor_cos(test.val_x_in_t,test.val_count);
            print_rez_val_cos(cos(test.val_x_in_t),rez_val); // Значение при 3 строчках

            p_test -> val_count = count_string_teilor_test[2];
            print_test_teilor(test.val_count, cos(test.val_x_in_t));
            rez_val = teilor_cos(test.val_x_in_t,test.val_count);
            print_rez_val_cos(cos(test.val_x_in_t),rez_val); // значение при 4 строчках

            p_test -> val_count = count_string_teilor_test[3];
            print_test_teilor(test.val_count, cos(test.val_x_in_t));
            rez_val = teilor_cos(test.val_x_in_t,test.val_count);
            print_rez_val_cos(cos(test.val_x_in_t),rez_val); // значение при 5 строчках

            p_test -> val_count = count_string_teilor_test[4];
            print_test_teilor(test.val_count, cos(test.val_x_in_t));
            rez_val = teilor_cos(test.val_x_in_t,test.val_count);
            print_rez_val_cos(cos(test.val_x_in_t),rez_val); // значение при 6 строчках

            p_test -> val_count = count_string_teilor_test[5];
            print_test_teilor(test.val_count, cos(test.val_x_in_t));
            rez_val = teilor_cos(test.val_x_in_t,test.val_count);
            print_rez_val_cos(cos(test.val_x_in_t),rez_val); // значение при 7 строчках 
            break;

        case(3): // exp(x)
            print_required_val();
            scanf("%lg", &test.val_x_in_t);

            p_test -> val_count = count_string_teilor_test[0];
            print_test_teilor(test.val_count, exp(test.val_x_in_t));
            rez_val = teilor_exp(test.val_x_in_t,test.val_count);
            print_rez_val_exp(exp(test.val_x_in_t),rez_val); //значение при 2 строчках

            p_test -> val_count = count_string_teilor_test[1];
            print_test_teilor(test.val_count, exp(test.val_x_in_t));
            rez_val = teilor_exp(test.val_x_in_t,test.val_count);
            print_rez_val_exp(exp(test.val_x_in_t),rez_val); //значение при 3 строчках

            p_test -> val_count = count_string_teilor_test[2];
            print_test_teilor(test.val_count, exp(test.val_x_in_t));
            rez_val = teilor_exp(test.val_x_in_t,test.val_count);
            print_rez_val_exp(exp(test.val_x_in_t),rez_val); //значение при 4 строчках

            p_test -> val_count = count_string_teilor_test[3];
            print_test_teilor(test.val_count, exp(test.val_x_in_t));
            rez_val = teilor_exp(test.val_x_in_t,test.val_count);
            print_rez_val_exp(exp(test.val_x_in_t),rez_val); //значение при 5 строчках

            p_test -> val_count = count_string_teilor_test[4];
            print_test_teilor(test.val_count, exp(test.val_x_in_t));
            rez_val = teilor_exp(test.val_x_in_t,test.val_count);
            print_rez_val_exp(exp(test.val_x_in_t),rez_val); //значение при 6 строчках

            p_test -> val_count = count_string_teilor_test[8];
            print_test_teilor(test.val_count, exp(test.val_x_in_t));
            rez_val = teilor_exp(test.val_x_in_t,test.val_count);
            print_rez_val_exp(exp(test.val_x_in_t),rez_val); // значение при 10 строчках
            
            break;
        case(4): // ln(1+x)
            print_required_val();
            scanf("%lg", &test.val_x_in_t);

            p_test -> val_count = count_string_teilor_test[0];
            print_test_teilor(test.val_count, log(test.val_x_in_t+1));
            rez_val = teilor_ln(test.val_x_in_t,test.val_count);
            print_rez_val_ln(log(test.val_x_in_t+1),rez_val); // значение при 2 строчках

            p_test -> val_count = count_string_teilor_test[1];
            print_test_teilor(test.val_count, log(test.val_x_in_t+1));
            rez_val = teilor_ln(test.val_x_in_t,test.val_count);
            print_rez_val_ln(log(test.val_x_in_t+1),rez_val); // значение при 3 строчках

            p_test -> val_count = count_string_teilor_test[8];
            print_test_teilor(test.val_count, log(test.val_x_in_t+1));
            rez_val = teilor_ln(test.val_x_in_t,test.val_count);
            print_rez_val_ln(log(test.val_x_in_t+1),rez_val); // значение при 10 строчках

            p_test -> val_count = count_string_teilor_test[9];
            print_test_teilor(test.val_count, log(test.val_x_in_t+1));
            rez_val = teilor_ln(test.val_x_in_t,test.val_count);
            print_rez_val_ln(log(test.val_x_in_t+1),rez_val); // значение при 1kk строчках



            break;
        }
        print_menu_func();
        scanf("%i", &choise_func);
    }   
}