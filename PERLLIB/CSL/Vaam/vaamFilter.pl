#!/usr/bin/perl

use strict;
use Data::Dumper;

use lib '/mounts/data/proj/impact/software/uli/PERLLIB';
use CSL::Vaam;

use Getopt::Long;

my ( $minNrOfPatterns, $maxNrOfPatterns, $help );

GetOptions(
    "help" => \$help,
    "minNrOfPatterns:i" => \$minNrOfPatterns,
    "maxNrOfPatterns:i" => \$maxNrOfPatterns,
    );

if( $help || @ARGV < 3 ) {

    print STDERR <<HELP;
 Use like: \.\/vaamFilter.pl <distance> <dicFile> <patternFile>

 A small query program for the perl Vaam interface.
 Query a word to STDIN and get the vaam answer in a single string representation.

 Instead of trying to parse the output with a Perl program, it might be MUCH easier
 to use the Perl interface directly. This program is a very simple example for using it.


OPTIONS:
--minNrOfPatterns N        restrict to results with at least N patterns
--maxNrOfPatterns N        restrict to results with at most N patterns

Ulrich Reffle, 2011

HELP

    exit( 1 );
}


my $vaam = new Vaam( distance => shift @ARGV,
		     dicFile =>  shift @ARGV,
		     patternFile =>  shift @ARGV,
		     minNrOfPatterns => $minNrOfPatterns,
		     maxNrOfPatterns => $maxNrOfPatterns,
    ) or die $!;



#$vaam->setSlimMode( 1 );


while ( my $word = <> ) {
    chomp $word;
    my $answer = $vaam->lookup( $word );

    #print Dumper $answer;
    print $word, "\t", $answer->{vaamString}, "\n";

}
