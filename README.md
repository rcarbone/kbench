![logo] [] kbench
=================

kbench is a test suite to benchmark several hash table implementations.

Heavily based on [Heng Li's kudb] (https://github.com/rcarbone/kudb), originally written by Heng Li in 2009 and updated by Rocco Carbone in 2016.

kbench aims to extend kudb in both the number of test cases and hash table implementations under test.

[logo]: etc/kbench.png

# Results for the impatients

Data sorted by CPU time (unsigned keys, unsigned values)

Linux nuc 3.2.0-4-amd64 #1 SMP Debian 3.2.81-1 x86_64 GNU/Linux

Wed Sep 14 22:18:52 CEST 2016

| Rank | Implementation    | CPU (secs) | Memory (MB) |    #    | Notes     |
| ---- | ----------------- | ---------- | ----------- | ------- | --------- |
|    1 | ulib              |      0.260 |     232.528 |  625792 |           |
|    2 | khash             |      0.440 |     232.516 |  625792 |           |
|    3 | google-dense      |      0.490 |     249.068 |  625792 |           |
|    4 | mct-closed        |      0.520 |     248.924 |  625792 |           |
|    5 | rdestl            |      0.550 |     265.432 |  625792 |           |
|    6 | hhash             |      0.690 |     293.476 |  625792 |           |
|    7 | ccan              |      0.790 |     223.804 |  625792 |           |
|    8 | libevent          |      0.920 |     507.336 |  625792 |           |
|    9 | mct-linked        |      1.150 |     281.668 |  625792 |           |
|   10 | python            |      1.180 |     264.480 |  625792 |           |
|   11 | eastl             |      1.190 |     244.652 |  625792 |           |
|   12 | tommyds-fixed     |      1.240 |     788.716 |  625690 | Bug here! |
|   13 | gcc-libiberty     |      1.260 |     240.172 |  625792 |           |
|   14 | hashit-overflow   |      1.260 |     415.944 |  636334 | Bug here! |
|   15 | stb               |      1.320 |     231.992 |  625792 |           |
|   16 | hashit-open       |      1.380 |     346.448 |  625792 |           |
|   17 | CDS               |      1.460 |     252.224 |  625793 | Bug here! |
|   18 | sys-glib          |      1.460 |     228.368 |  625792 | **        |
|   19 | google-sparse     |      1.550 |     225.124 |  625792 |           |
|   20 | c-hashtable       |      1.580 |     257.076 |  625792 |           |
|   21 | c-algoritms       |      1.620 |     268.436 |  625792 |           |
|   22 | uthash            |      1.670 |     618.008 |  625792 |           |
|   23 | ghthash           |      1.700 |     362.480 |  625792 |           |
|   24 | Qt-hash           |      1.720 |     246.580 |  625792 |           |
|   25 | sys-tcl           |      1.720 |     256.964 |  625792 | **        |
|   26 | cfu               |      1.770 |     272.360 |  625792 |           |
|   27 | stl-unordered     |      1.800 |     244.640 |  625792 |           |
|   28 | tommyds-linear    |      1.810 |     732.960 |  625690 | Bug here! |
|   29 | tommyds-dynamic   |      1.870 |     747.984 |  625792 |           |
|   30 | generic-c-hashmap |      1.920 |     498.700 |  630572 | Bug here! |
|   31 | hashit-chain      |      1.930 |     300.468 |  625792 |           |
|   32 | sys-apr           |      1.930 |     256.596 |  625792 | **        |
|   33 | sys-boost         |      1.970 |     241.752 |  625792 | **        |
|   34 | sys-python        |      2.120 |     675.484 |  625792 | **        |
|   35 | apr               |      2.170 |     253.008 |  625792 |           |
|   36 | sys-LuaHashMap    |      2.560 |     281.352 |  625792 | **        |
|   37 | sglib             |      2.770 |     450.568 |  625792 |           |
|   38 | st                |      2.890 |     245.772 |  625792 |           |
|   39 | ruby-st           |      2.970 |     255.492 |  625792 |           |
|   40 | htable            |      3.040 |     541.132 |  625792 |           |
|   41 | google-c-dense    |      3.810 |     243.744 |  625792 |           |
|   42 | google-c-sparse   |      4.820 |     244.400 |  625792 |           |
|   43 | sys-perl          |      6.160 |     695.120 |  625792 | **        |
|   44 | stl-map           |      6.700 |     245.460 |  625792 |           |
|   45 | Qt-map            |      7.460 |     247.244 |  625792 |           |

** Pre-installation of Debian System Libraries is required
