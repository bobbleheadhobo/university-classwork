--  Name: Joey Troyer
--  Date: 09/07/22
--  pre: None
--  post: Output to the termial

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure adaTest is

    --test function to be called
    function func return Boolean is
    begin
        Put_Line("This function was called");
        return true;
    end func;

    a : Integer;
    begin   

--start of short circuit operators
        a := 0;
        Put_Line("AND evaluation using short circuit operators");
        while a < 2 loop
        --left hand side starts false then next loop is true
        if a > 0 and then func then
            Put_Line("True");
        else
            put_line("false");
        end if;

        Put_Line("  Next");
        a := a + 1;
        end loop;

        Put_Line("");

        a := 0;
        Put_Line("OR evaluation using short circuit operators");
        while a < 2 loop
        --left hand side starts false then next loop is true
        if a > 0 or else func then
            Put_Line("True");
        else
            put_line("false");
        end if;

        Put_Line("  Next");
        a := a + 1;
        end loop;


-- start of logical operators
        Put_Line("");
        a := 0;

        Put_Line("AND evaluation");
        while a < 2 loop
        --left hand side starts false then next loop is true
        if a > 0 and func then
            Put_Line("True");
        else
            put_line("false");
        end if;

        Put_Line("  Next");
        a := a + 1;
        end loop;

        Put_Line("");

        a := 0;
        Put_Line("OR evaluation");
        while a < 2 loop
        --left hand side starts false then next loop is true
        if a > 0 or func then
            Put_Line("True");
        else
            put_line("false");
        end if;

        Put_Line("  Next");
        a := a + 1;
        end loop;

end adaTest;
