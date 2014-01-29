#!/usr/bin/perl

use strict;

use lib '../../';
use CSL::MinDicString;

use IPC::Open2;

my $dicFile = shift;

# Create a Cislex object.
my $lex = new MinDicString( dicFile => $dicFile );

if( !$lex ) {
    printf( "Obvioulsly the Cislex constructor has failed.\n");
    die;
}

binmode(STDIN, "utf8:");

while( my $key = <> ) {
    chomp $key;
    my $output = $lex->lookup( $key );

    print "$output\n";
}






# open2(*README, *WRITEME, "../bin/lookupCislex ");
# print WRITEME "here's your input\n";
# $output = <README>;
# close(WRITEME);
# close(README);




