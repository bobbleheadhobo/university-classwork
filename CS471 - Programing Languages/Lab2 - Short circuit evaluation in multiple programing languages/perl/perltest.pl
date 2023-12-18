# file perltest.pl
# author Joey Troyer
# date 2022-09-07
# pre none
# post output to the terminal

#test functin to be called
sub func() {
	print "I have been evaluated!!!\n";
	return 1;
}# end func

#start of short circuit operators
$var = 1;
print "\nAND evaluation using short circuit operator &&\n";
for($i = 0; $i < 2; $i++) {
	#left hand side starts false then next loop is true
	if( $i == 1 && func()) {
		print "true\n";
	}else {
		print "false\n";
	}

	print "  next\n";
}# end for

print "\n";
print "OR evaluation using short circuit operator ||\n";
for($i = 0; $i < 2; $i++) {
	#left hand side starts false then next loop is true
	if( $i == 1 || func()) {
		print "true\n";
	}else {
		print "false\n";
	}

	print "  next\n";
}# end for


#start of other short circuit operators
$var = 1;
print "\nAND evaluation using and\n";
for($i = 0; $i < 2; $i++) {
	#left hand side starts false then next loop is true
	if( $i == 1 and func()) {
		print "true\n";
	}else {
		print "false\n";
	}

	print "  next\n";
}# end for

print "\n";
print "OR evaluation using or\n";
for($i = 0; $i < 2; $i++) {
	#left hand side starts false then next loop is true
	if( $i == 1 or func()) {
		print "true\n";
	}else {
		print "false\n";
	}

	print "  next\n";
}# end for


#start of logical operators 
$var = 1;
print "\nAND evaluation using &\n";
for($i = 0; $i < 2; $i++) {
	#left hand side starts false then next loop is true
	if( $i == 1 & func()) {
		print "true\n";
	}else {
		print "false\n";
	}

	print "  next\n";
}# end for

print "\n";
print "OR evaluation using |\n";
for($i = 0; $i < 2; $i++) {
	#left hand side starts false then next loop is true
	if( $i == 1 | func()) {
		print "true\n";
	}else {
		print "false\n";
	}

	print "  next\n";
}# end for
