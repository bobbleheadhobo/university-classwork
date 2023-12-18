int A, complex;
int a, b[100], c, d[5], e;
int alpha[3], beta[4], charlie, delta[3], epsilon;
void x_of_void;
boolean bool_flag;
//int localInt[5];

void main(void)
begin
// LOCAL DECLARATIONS
    int myArray[20];
    int result;


// SELECTION IF statement
    //a = 20;
    if (a > 10) then // GREATER
        begin
        write "Enter a: ";
        read a;
        write a;
        write "\n";
        end

 // SELECTION IF-ELSE tree
    a = 100;
    //e = 1;
    if (a < (30 + d[10 - b[1]])) then // LESS THAN
        begin
        write "Enter complex: ";
        read complex;
        write complex;
        write "\n";
        end
    else
        begin
            // ITERATION statement with loop
            int localInt[5];
            while (c < 5) and (not e) do    // GREATER/EQUAL | NOT //problem with e in (c < 5 and not e) in while condition
            begin
                write "Enter localInt[";
                write c;
                write "]: ";
                read localInt[c];
                c = c + 1;
            end
        c = 0;
        write "\n";
        while (c < 5) do
            begin
            write "localInt[";
            write c;
            write "] =  ";
            write localInt[c];
            write "\n";
            c = c + 1;
            end
        end

    // SELECTION IF TREE
    if (a <= c) or (not a) and (c != 1) then
        write "var_LESS_OR_EQUAL\n";

    
    // SEG-FAULT TEST
    ;;;;;;;;;;;;;

    // ASSIGNMENT STATEMENT
    a = 5 + 10 * (b[40 - 1 / 2] / 2 + 1) / 50;
    write a;
    write "\n";

    if(false) then begin
    // WRITE STATEMENT
    write 10 + 100 - a * 4 / 2;
    write "\n";

    write 5 < 9; //1
    write "\n";
    write 5 < 1; //0
    write "\n";

    write 5 <= 9; //1
    write "\n";
    write 5 <= 1; //0
    write "\n";

    write 5 > 9; //0
    write "\n";
    write 5 > 1; //1
    write "\n";

    write 5 >= 9; //0
    write "\n";
    write 5 >= 1; //1
    write "\n";
    write "\n";
    write "\n";


    bool_flag = true;
    write bool_flag;
    write "\n";
    bool_flag = false;
    write bool_flag;

    end


end