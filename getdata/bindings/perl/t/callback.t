use GetData;
use strict;
use Test::More tests => 8;

# callback
sub callback {
  my ($pdata, $extra) = @_;

  print "\n";
  is ($extra, "extra stuff", "\$extra parameter good");
  is ($$pdata{'suberror'}, $GetData::E_FORMAT_BAD_LINE, "suberror good");
  is ($$pdata{'linenum'}, 2, "linenum good");
  ok ($$pdata{'filename'} =~ m"dirfile/format$", "filename good");

  $GetData::SYNTAX_IGNORE
}

# create the dirfile
system "rm -rf dirfile" if (-e "dirfile" and not -d "dirfile");
print "\n";
ok(-e "dirfile" or mkdir "dirfile");

open GLOB, ">dirfile/format" or die;
print GLOB "data RAW UINT16 8\nbad line\n" or die;
close GLOB or die;

my $d = &GetData::open("dirfile", $GetData::RDONLY, \&callback, "extra stuff");
print "\n";
ok (defined $d, "open created an object");
my $e = &GetData::error($d);
print "\n";
is ($e, $GetData::E_OK, "no error from open");
my $close_ret = $d->close();
print "\n";
is ($close_ret, 0, "close succeeded");

system "rm -rf dirfile";
