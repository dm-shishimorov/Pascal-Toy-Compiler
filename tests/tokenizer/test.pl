use strict;
use warnings;

for (my $i = 1; $i <= 15; $i++) {
	unlink "${i}_result.txt";
	system("ptc.exe ${i}_test.txt -t >> ${i}_result.txt");

	open(RES, "< ${i}_result.txt") or die;
	my $t1;
	while (<RES>) {
		$t1 .= $_;
	}
	close(RES) or die;

	open(EXP, "< ${i}_expected.txt") or die;
	my $t2;
	while (<EXP>) {
		$t2 .= $_;
	}
	close(EXP) or die;

	if ($t1 ne $t2) {
		print "test $i:\tfailed.\n";
	}
	else {
		print "test $i:\tok\n";
	}
}