#!/usr/bin/perl

use strict;


my $db_file = shift;

$db_file =~ m /(.*?\/?)([^\/]*)$/;
my $name = $2;

my $dir = $1."/".$name."_files";
unless(-d $dir) {
    mkdir($dir) or die $!;
}

print "GET alphabet.azb\n"; system("./tools/get_alph.pl $db_file > $dir/alphabet.azb") and die "get_alph.pl failed";

print "GET tokens.alph.lex\n"; system("./tools/multi2single.pl $db_file > $dir/tokens.alph.lex") and die "multi2single.pl failed";
print "GET tokens.alph.dic\n"; system("./bin/compileTrie $dir/alphabet.azb $dir/tokens.alph.lex $dir/tokens.alph.dic") and die "compileTrie failed";

print "GET tokens.freq.lex\n"; system("./tools/multi2single.pl --freq $db_file > $dir/tokens.freq.lex") and die "multi2single.pl failed";
print "GET tokens.freq.dic\n"; system("./bin/compileTrie $dir/alphabet.azb $dir/tokens.freq.lex $dir/tokens.freq.dic") and die "compileTrie failed";

print "GET tokens.cs.lex\n"; system("./bin/getCandscore $dir/alphabet.azb $dir/tokens.alph.dic $dir/tokens.freq.lex > $dir/tokens.cs.lex");

print "GET tokens.cs.dic\n"; system("./bin/compileTrie $dir/alphabet.azb $dir/tokens.cs.lex $dir/tokens.cs.dic") and die "compileTrie failed";;

print "GET db.alph.perm_tok.lex\n"; system("./tools/re_sort.pl --perm=tokens $db_file > $dir/db.alph.perm_tok.lex") and die "re_sort failed";
print "GET db.alph.perm_tok.dic\n"; system("./bin/compileTrie $dir/alphabet.azb $dir/db.alph.perm_tok.lex $dir/db.alph.perm_tok.dic") and die "compileTrie failed";;

print "GET db.cs.perm_tok.lex\n"; system("./tools/re_sort.pl --perm=tokens --sortFile=$dir/tokens.freq.lex $db_file > $dir/db.freq.perm_tok.lex") and die "re_sort failed";
print "GET db.freq.perm_tok.dic\n"; system("./bin/compileTrie $dir/alphabet.azb $dir/db.freq.perm_tok.lex $dir/db.freq.perm_tok.dic") and die "compileTrie failed";;


print "GET db.cs.perm_tok.lex\n"; system("./tools/re_sort.pl --perm=tokens --sortFile=$dir/tokens.cs.lex $db_file > $dir/db.cs.perm_tok.lex") and die "re_sort failed";
print "GET db.cs.perm_tok.dic\n"; system("./bin/compileTrie $dir/alphabet.azb $dir/db.cs.perm_tok.lex $dir/db.cs.perm_tok.dic") and die "compileTrie failed";;


