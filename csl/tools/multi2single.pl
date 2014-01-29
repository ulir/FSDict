#!/usr/bin/perl

# extracts all single tokens of a multi-lexeme dictionary
# can easily be adapted to produce either word lists or frequency lists

use strict;

my $mode;
my $mode;
if($ARGV[0]=~/--?h(elp)?/) {
    shift;
    print <<TXT;
multi2single.pl
Converts a multiword database from STDIN into a corresponding token lexicon and prints it to STDOUT.
With flag --freq a frequency list is printed.

TXT
exit;
}


if( $ARGV[0] eq "--freq" ) {
    shift;
    $mode = "freq";
}

my %lex;
while(<>) {
    chomp;
#    s/\r\n$/\n/;
    s/\#.*$//; # delete annotations
    s/^(?:\$|\%|,)//; # delete leading delimiters
    for( split(/[\$\%,]+/ ) ) { $lex{$_}++; } # specify all special chars here!!!
}

if($mode eq "freq") {
    # to get frequency list
    for (sort  keys(%lex)) {
	print $_,"#",$lex{$_},"\n";
    }
}
else {
    # to get plain wordlist
    my $i = 0;
    for (sort keys(%lex)) {
	print $_,"#",$i,"\n";
	++$i;
    }
}

sub valueSort {
    return ($lex{$b}<=>$lex{$a});
}
