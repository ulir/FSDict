#!/usr/bin/perl

use strict;
use encoding 'utf8';

my @lines;


for(<>) {
    chomp;
    s/(\#.*)//;
    push(@lines, [scalar(reverse($_)), $1]);
}



my $i = 0;
for(sort {$a->[0] cmp $b->[0]} @lines) {
    ++$i;
    print $_->[0],$_->[1],"\n";
}
