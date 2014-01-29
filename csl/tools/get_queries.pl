#!/usr/bin/perl

use strict;
use Getopt::Long;
use encoding 'utf8';
#####CONFIG###########
# These are default values - most of them can be overwritten by command-line flags
my $structured = 0;
my $permDelimiter = '%';
my $noPermDelimiter = '$';
my $tokensDelimiter = ',';


my $permuteTokens = 0; # 0 / 1
my $permuteParts = 0; # 0 / 1
my $groundtruth = 0; # 0 / 1

my $symbol_error_rate = 0;   # 0 <= $symbol_error_rate <= 1
my $errors = 0;
my $glob = 0;
#####################

my $permDelimRex = '\\'.$permDelimiter;
my $noPermDelimRex = '\\'.$noPermDelimiter;
my $compDelimRex = "(?:$permDelimRex|$noPermDelimRex)";
my $tokensDelimRex = '\\'.$tokensDelimiter;
my $allDelimRex = "(?:$compDelimRex|$tokensDelimRex)";

my $help;
GetOptions(
	   'help' => \$help,
	   'error_rate=f' => \$symbol_error_rate,
	   'errors=i' => \$errors,
	   'glob=i' => \$glob,
	   'structured' => \$structured,
	   'permuteParts' => \$permuteParts,
	   'groundtruth!' => \$groundtruth,
	   );

if(@ARGV<3 or $help) {
    print STDERR <<TXT;

 Use like: ./get_queries.pl <alph_file> <text_db_file> <nr_of_queries>

 One line in <text_db_file> would look like:
 \%this,will,be,permuted\$this,will,not,be,permuted#42
 Formally:
 ((\%|\$)(\\w+,)*\\w+)+(#\\d+)?

Mark parts that are to be permuted with a '%', others with a '$'

Flags:
--help             display this message and quit

--error_rate N     specify a symbol-error rate (0 <= N <= 1, default 0)
--errors N         specify number of errors for each line (N>=0, default 0)
--glob N           transform one area of N characters into a single '_'

--structured       
--permuteParts     Set this option to allow permutation of complete parts 
                   among each other
--groundtruth      print pairs "groundtruth<SPACE>query";
--nogroundtruth    do not add the groundtruth (default)

Uli Reffle, 2006

TXT
    exit(1);
}

my $alph_file = $ARGV[0];
my $db_file = $ARGV[1];
my $nr_of_queries = $ARGV[2];



open(ALPH,"<$alph_file") or die $!;
my $alphLine = <ALPH>;
close(ALPH);
$alphLine =~ s/$allDelimRex//g; # remove delimiter symbols from alphabet
my @alph = split( //, $alphLine );

open(DB,"<$db_file") or die $!;
my @db = <DB>;
close(DB);

my $count = 0;
for(1..$nr_of_queries) {
    print STDERR "$count tokens produced\n" unless( ++$count % 10000 );
    my $rand_index = int( rand( $#db + 1 ) );

    chomp $db[$rand_index];
    $db[$rand_index] =~ s/\#.*//g;

    my $entry = $db[$rand_index];

    if($symbol_error_rate > 0) { # create symbol errors by error rate
	my @entry = split(//,$entry); #split into characters
	for my $c (@entry) {
	    if($c !=~ m/$allDelimRex/) {
		$_ = $alph[int(rand($#alph))];
	    }
	}
	$entry = join('',@entry);
    }


    if($glob > 0) {
	my $randPos = int(rand(length($entry) - $glob + 1)) ;
	substr($entry,$randPos,$glob) = 'x'x$glob;
	
    }

    # PERMUTATIONS

    if( $structured ) {
	my @parts = ();
	while( $entry =~ m/($compDelimRex)(.+?)(?=$compDelimRex|$ )/gx ) {
	    my $delim = $1;
	    my $part = $2;
	    $part =~ s/,$//; # remove trailing delimiter
	    my @tokens = split( /$tokensDelimRex/, $part );
	    
	    if( $delim eq $permDelimiter ) {
		shuffle( \@tokens );
#	    @tokens = sort { reverse($a) cmp reverse($b )} @tokens;
		
		push( @parts, join( $tokensDelimiter, @tokens ).',' );
	    }
	    else {
		push( @parts, $part.',' );
	    }
	}
	
	if( $permuteParts ) {
	    $entry = '';
	    while(@parts) {
		# take a random elt out of @parts, add it to $entry
		$entry .= splice(@parts,int(rand(@parts)),1);
	    }
	}
	else {
	    $entry = join( '', @parts ).$tokensDelimiter;
	}
	
	# do this at the end so you can throw away the different delimiters
	if($errors > 0) { # create symbol errors by number (not so terribly correct, caus deletions wrack the seen-array ... :-/)
	    my @tokens=split(/$allDelimRex+/,$entry);
	    for(@tokens) {
		$_ = addErrors($_,$errors);
	    }
	    $entry = join($tokensDelimiter, @tokens).$tokensDelimiter;
	}
	
	$entry =~ s/$compDelimRex/$tokensDelimiter/g; # Finally remove all structure from the query
    } # if structured
    else {
	$entry = addErrors( $entry, $errors );
    }

    if($groundtruth) {
	print STDOUT "$db[$rand_index]\t$entry\n";
    }
    else {
	print STDOUT $entry,"\n";
    }
}

sub randomChar {
    return $alph[int(rand($#alph))];
}

sub addErrors {
    my $word = shift;
    my $errors = shift;
    my @seen;
    for (1..$errors) {
	my $rand = rand(3);
	$rand = 2;
	my $randPos = int(rand(length($word)));
	
	if($rand < 1) { #insertion
	    substr($word,$randPos,0) = randomChar();
	    $seen[$randPos] = 1;
	}
	elsif($rand<2) { #deletion
	    unless(length($word)<2) { # don't kill a very last char
		substr($word,$randPos,1) = "";
	    }
	}
	elsif($_ <= length($word)) { # substitution (don't try to sub. more chars than there are in $word)
	    substr($word,$randPos,1) = randomChar();
	    $seen[$randPos] = 1;
	}
    }
    return $word;
}

sub shuffle {
    my $arrRef = shift @_;
    my $len = @$arrRef;
    for( 1 .. $len ) {
	my $rand1 = int( rand( $len ) );
	my $rand2 = int( rand( $len ) );
	my $tmp = $arrRef->[$rand1];
	$arrRef->[$rand1] = $arrRef->[$rand2];
	$arrRef->[$rand2] = $tmp;
    }
}
