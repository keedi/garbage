#!/usr/bin/env perl

use 5.010;
use common::sense;

my %function;
my @out_lines;
my $current_function;

while (<>) {
    my $in = check_brace($_);
    if (/^ \s* function \s* (\w+) \s* \( \s* [^)]* \s* \)/x) {
        $current_function = $1;
        $function{$current_function}{line} = $_;
    }
    else {
        if ($in) {
            while (/ ( (?: \$|\. )? \w+ ) \s* \( /gx) {
                my $call = $1;

                next if $call =~ /^\./;
                next if $call =~ /^do$/;
                next if $call =~ /^function$/;
                next if $call =~ /^if$/;
                next if $call =~ /^return$/;
                next if $call =~ /^while$/;

                push @{ $function{$current_function}{call_sequence} }, $1;
            }
        }
        else {
            push @out_lines, $_;
        }
    }
}

for my $name ( sort keys %function ) {
    say $name;
    say "    $_" for @{ $function{$name}{call_sequence} };
}

sub check_brace {
    state $func_in = 0;

    my $str = shift;

    my $brace_open  = $str =~ /{/g;
    my $brace_close = $str =~ /}/g;

    $func_in += $brace_open - $brace_close;

    return $func_in;
}
