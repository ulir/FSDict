#!/usr/bin/perl

use lib '/mounts/data/proj/impact/software/Vaam/perl';
use encoding 'utf8';

use Vaam;

use Data::Dumper;


if( @ARGV < 3 ) {

    print STDERR <<HELP;
 Use like: \.\/vaamDemo.pl <distance> <dicFile> <patternFile>

 A small demo program for the perl Vaam interface.
 Query a word and get a Data::Dumper output of the answer aggregate.
 Note that the non-asscii characters are messed up by Data::Dumper, but
 are ok in the data structure.

HELP

    exit( 1 );
}


my $vaam = new Vaam( distance => shift @ARGV,
		     dicFile =>  shift @ARGV,
		     patternFile =>  shift @ARGV,
    ) or die $!;


while ( my $word = <> ) {
    chomp $word;
    my $answer = $vaam->lookup( $word );
    print Dumper $answer;
}
