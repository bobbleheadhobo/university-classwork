int fib(n of int)
begin
    if (n <= 1) then
        return n;

    return fib(n - 1) + fib(n - 2);
end
  
int main(void)
begin
    int n;
    while(n < 100) do
    begin
        write n;
        write ": ";

        write fib(n);
        write "\n";
        
        n = n + 1;
    end
    
    return 0;
end