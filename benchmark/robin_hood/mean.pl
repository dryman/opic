#!/usr/bin/env perl
use strict;
use warnings;
use 5.010;

my $count = 0;
my $sum = 0;
my $expected_sum = 0;
my @arr = ();

while(<>) {
  chomp;
  next unless /^\d+$/;
  $sum += $&;
  $expected_sum += $& * $count;
  push @arr, $&;
  $count++;
}

my $mean = $expected_sum / $sum;
my $var = 0;

$count = 0;
for my $num (@arr) {
  $var += $num * ($count - $mean)**2;
  $count++;
}
$var /= $sum;

say $mean . "," . $var;
