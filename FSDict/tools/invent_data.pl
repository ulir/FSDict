#!/usr/bin/perl

use strict;
use Getopt::Long;
use Tie::File;

$| = 1;

my ($nrOfLines,$nrOfTokens, $nrOfParts, $memMode);
$memMode = 'DISK';
GetOptions('tokens=i' => \$nrOfTokens,
	   'parts=i' => \$nrOfParts,
	   'nrOfLines=i' => \$nrOfLines,
	   'memmode=s' => \$memMode,
	   );

my $tokenFile = shift;

my @tokens;
my $size = 0;

if($memMode eq 'RAM') {
    open(FILE,$tokenFile) or die $!;
    print STDERR "Load tokens to RAM\n";
    while(<FILE>) {
	chomp;
	push(@tokens,$_);
	print STDERR $.,"\r"  unless($.%100000);
	++$size;
    }
    close FILE;
    print STDERR "ok\n";
}
elsif($memMode eq 'DISK') {
    print STDERR "Keep tokens on harddisk\n";
    tie(@tokens,'Tie::File', $tokenFile) or die $!;
    `wc -l $tokenFile` =~ m/^(\d+)/;
    $size = $1;
    print STDERR "Initialize index\n";
    $tokens[$size-1];
    print STDERR "ok\n";
}

print STDERR "$size lines in source\n";

for(1..$nrOfLines) {
    my $partsCount = 0;
    do { # do the parts-loop at least once, even for nrOfParts==0
	for(1..$nrOfTokens) {
	    my $index = int(rand($size));
	    print $tokens[$index],",";
	}
	print chr(8),"\$" if $nrOfParts > 0; # replace last tokensDelim by partsDelim, only in "parts-mode"
    } while(++$partsCount <= $nrOfParts);
    print "\n";
    print STDERR $_," lines produced\r"  unless($_ % 100);
}
print STDERR "\nEnd.\n";
