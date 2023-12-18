#Name: Joey Troyer
#Date: 09/02/22
#pre: none
#post: Output to the termial
#!/bin/csh

echo 'C-SHELL Short circuit evaluation'

#start of logical operators
echo 'AND test using &&'

    false && echo "foo"
    echo " next"
    true && echo "foo"

echo ""

echo 'OR test using ||'
    false || echo "foo"
    echo " next"
    true || echo "foo"

echo ""

#bitwise and
echo 'AND test using &'

    false & echo "foo"
    echo " next"
    true & echo "foo"

echo ""

#bitwise or
echo 'OR test'
    false | echo "foo"
    echo " next"
    true | echo "foo"

