#!/usr/bin/env perl
use strict;
use warnings;
use 5.010;

say ",linear probing,quadratic probing,double hashing";
for my $i (1..100) {
  my $cnt = 2; # left and right margin
  for my $j (1..$i) {
    for my $k (1..100) {
      my $idx = $j + $k * $k;
      last if $idx > $i + 1;
      $cnt++ if $idx == $i + 1;
    }
  }
  my $lp = $i + 2;
  my $dh = 2;
  say "$i,$lp,$cnt,$dh";
}

