#!/bin/sh


# constructs a lexicon of all words of the given text, with frequency attached. 

cat $* | tokenizer -Lde-u8 -s | perl -pe '$_ = lc' |  sort | uniq -c | perl -ne 'm/\s*(\d+?)\s+(.*)/;$word=$2;$freq=$1;print "$word#$freq\n" if($word =~ m/[a-zäöüß]/i);' | LC_ALL=C sort -t'#' -k1,1

