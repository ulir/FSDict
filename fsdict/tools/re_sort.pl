#!/usr/bin/perl

use strict;
use lib "/mounts/Users/student/uli/implement/csl/trunk/tools";
use Freqhash;
use Getopt::Long;

$| = 1;


my $permParts;
my $help;
my $sortFile;
my $compile = 0;
GetOptions(
	   'help' => \$help,
	   'PermParts' =>\$permParts,
	   'sortFile=s' =>\$sortFile,
	   );

if($help) {
    shift;
    print <<TEXT;

re_sort.pl


Reads a multi-token .lex file and resorts the items. Finally it brings the list into alphabetical order.
To resort in alphabetical order:
re_sort.pl source.lex > new.lex

OPTIONS
--sortFile=<filename>
To re-sort according to a certain score defined in score.txt:
score.txt is expected to look like:
<token1>#<score1>
<token2>#<score2>

--permParts
To cover permutation among parts, the parts have to be in sorted order. Invoke the sorting with this flag.

--help
prints this message and exits

TEXT

    exit( 1 );
    
}

my $freqlist_file;
my $freqhash;
my $tok_cmp;


if( $sortFile ) {
    $freqhash = new Freqhash( $sortFile );
    $tok_cmp = 	
	sub {
	    return frqcmp( $a, $b );
	};
}
else {
    $tok_cmp = 
	sub {
	    return $a cmp $b;
	};
}

my $permDelimiter = '%';
my $permDelimRex = '\\'.$permDelimiter;

my $noPermDelimiter = '$';
my $noPermDelimRex = '\\'.$noPermDelimiter;

my $tokensDelimiter = ',';
my $tokensDelimRex = '\\'.$tokensDelimiter;

my $compDelimRex = "(?:$permDelimRex|$noPermDelimRex)";
my $allDelimRex = "(?:$compDelimRex|$tokensDelimRex)";

my @lines;
my $lineCount = 0;

while( my $line=<> ) {
    ++$lineCount; # lineCount is 1 for 1st line (not 0) !!!
    unless( $lineCount % 10000 ) { print STDERR "\r$lineCount lines processed."; }
    $line=~s/\r?\n$/\n/; # remove DOS-carriage return and newline


    my @parts = ();
    while( $line =~ m/($compDelimRex)(.+?)(?=$compDelimRex|$ )/gx ) {
	my $delim = $1;
	my $part = $2;
	$part =~ s/,$//;
	my @tokens = split( /$tokensDelimRex/, $part );
	
	if( $delim eq $permDelimiter ) {
	    @tokens = sort $tok_cmp @tokens;
	    push( @parts, $delim.join( $tokensDelimiter, @tokens ).',' );
	}
	else {
	    push( @parts, $delim.$part.',' );
	}
    }

    if( $permParts ) {
	@parts = sort partSort @parts;
    }
    push( @lines, [ join( '', @parts ), $lineCount] );
}

print STDERR "Start sort.\n";
@lines = sort {$a->[0] cmp $b->[0]} @lines;

print STDERR "Start output.\n";

my $firstLine = shift @lines; #take 1st line
my $values = $firstLine->[1]; 
my $lastLine = $firstLine->[0]; 

for my $line (@lines) {
    if($line->[0] ne $lastLine) {
	print $lastLine,"#",$values,"\n";
	$values = "";
	$lastLine = $line->[0];
    }
    $values.= $line->[1].",";
}
print $lastLine,"#",$values,"\n";


sub frqcmp {
    my( $a, $b ) = @_;
    my $x;
    if( $x =( $freqhash->lookup( $a ) <=> $freqhash->lookup( $b ) ) ) {
	return $x;
#	return -$x;
    }
    else {
	return ("$a" cmp "$b");
    }
}


sub partSort {
    $a =~ m/^$compDelimRex(.+?)$tokensDelimRex/;
    my $aa = $1;
    $b =~ m/^$compDelimRex(.+?)$tokensDelimRex/;
    my $bb = $1;
    if( my $x = &$tok_cmp( $aa, $bb ) ) {
	return $x;
    }
    else {
	return ($a cmp $b);
    }
}
