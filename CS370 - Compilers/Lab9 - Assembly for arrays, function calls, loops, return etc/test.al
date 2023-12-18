int result1;
int result2;

int add(LHS of int, RHS of int)
begin
    write "\nLeft: ";
    write LHS;
    write "\n";
    
    write "Right: ";
    write RHS;
    write "\n";

    return LHS + RHS;
end

void main(void)
begin
    int x;
    int y[10];

    x = 10;
    write "x = ";
    write x;
    write "\n";

    y[5] = 20;
    write "y[5] = ";
    write y[5];

    result1 = add(x, y[5]);


    write "first result: ";
    write result1;
    write "\n";

     result2 = add(add(x, y[5]), add(result1, x));

    write "second result: ";
    write result2;    
end


