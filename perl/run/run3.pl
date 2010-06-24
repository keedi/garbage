#!/usr/bin/env perl

use 5.010;
use common::sense;
use IPC::Run3;

open my $out, '>', 'log'
    or die "cannot open log file: $!\n";

my @cmd = qw| ./run.sh |;

run3 \@cmd, \*STDIN, $out, \*STDERR;

close $out;
